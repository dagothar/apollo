#include <ctime>


#include "init.h"
#include "display.h"
#include "control.h"
#include "hud.h"
#include "model.h"
#include "vectors.h"
#include "lander.h"
#include "simulink.h"
#include "sound.h"
#include "log.h"
#include "main.h"

//flagi programu
bool exit_flag = false;
bool pause_flag = false;

//stale fizyczne
double g = 1.622; //stala grawitacji
double b_atm = 0.0; //tarcie atmosfery

//glowne liczniki czasu
volatile clock_t rdt;
volatile double dt;
double t = 0.0;
double t_fps = 0.2;

/* glowna funkcja logiki programu */
void go()
{
     // wyznacz czas trwania poprzedniej petli
     dt = 1.0*(clock() - rdt)/CLOCKS_PER_SEC;
     
     //czy Simulink online?
     if(1.0*(clock() - sim_clock)/CLOCKS_PER_SEC > sim_timeout) {
                     if(simulink_online) message("Simulink offline", MSG_OK);
                     simulink_online = false;
     }

     if(dt >= exp_dt) {
           t_fps += dt;
           
           ctrl(); //przyjmij sterowanie
           
           if(!pause_flag) {
                           t += dt; //odswiez czas
                           
                           lander.go(); //fizyka ladownika
    
                           // loguj
                           if(logging && t > last_log + log_dt) {
                                      log();
                                      last_log = t;
                           }
    
                           //na wypadek zrestartowania czasu
                           if(mark_path && last_path > t) last_path = -1.0;
           }
           
           //mierz fps
           if(frames > 10) {
                     fps = 10.0 / t_fps;
                     frames = 0;
                     t_fps = 0.0;
           }
           //fps = frames / t;
        
           glutPostRedisplay(); //odswiez ekran
           make_sound(); //odtwarzaj dzwiek
           
           rdt = clock();
     }
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    srand(time(NULL));
    
    //interpretuj parametry linii komend
    cmd_line();
    
    //ustaw grafike
    init_gl(_argc, _argv);
    
    //ustaw dzwiek
    init_sound();
    
    glutSetWindow(window);
    
    //zarejestruj funkcje zmieniajaca rozmiar okna
    glutReshapeFunc(&resize);
    
    //zarejestruj funkcje wyswietlajaca
    glutDisplayFunc(&display);
    
    //zarejestruj funkcje rejestrujaca wcisniecie klawiszy
    glutKeyboardFunc(&keydown);
    
    //zarejestruj funkcje rejestrujaca puszczenie klawiszy
    glutKeyboardUpFunc(&keyup);
    
    //zarejestruj funkcje rejestrujaca wcisniecie klawiszy specjalnych
    glutSpecialFunc(&spcdown);
    glutSpecialUpFunc(&spcup);

    glutIdleFunc(&go);

    // otworz plik loga
    log_file.open("log.csv");
    log_file << "t, x, y, z, h, pitch, yaw, roll\n";
    
    //moon.generate(); //stworz powierzchnie
    moon.load(map_file); //wczytaj mape powierzchni
    lander.setup(C_STACK); //stworz ladownik
    lander.reset();
    
    //uruchom watki
    int i = 0;
    DWORD tid[2];
    HANDLE thread_handles[2];
    thread_handles[i] = CreateThread(NULL, 0, com_thread, NULL, 0, &tid[i]); ++i;
    //thread_handles[i] = CreateThread(NULL, 0, go_thread, NULL, 0, &tid[i]); ++i;
    //thread_handles[i] = CreateThread(NULL, 0, graph_thread, NULL, 0, &tid[i]); ++i;
    //thread_handles[i] = CreateThread(NULL, 0, com_thread, NULL, 0, &tid[i]); ++i;
    
    //zaczekaj na koniec watkow
    //WaitForMultipleObjects(1, thread_handles, TRUE, INFINITE);
    
    //glowna petla programu
    rdt = clock();
    message("      ---APOLLO---      ", MSG_OK);
    message("", MSG_OK);
    message("Wszystkie systemy sprawne...", MSG_INFO);
    glutMainLoop();
    
    return 0;
}
