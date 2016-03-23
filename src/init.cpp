#include "init.h"

//uchwyt glownego okna
int window;

//stan klawiszy
volatile bool keys[256];

//interpretuj parametry linii komend
void cmd_line()
{
     bool generate_map = false;
     for(int i = 0; i < _argc; ++i) {
             std::string cmd = _argv[i];
             
             if(cmd == "-h" && _argc > i+1) sim_host = _argv[++i]; //zmiana hosta
             if(cmd == "-m" && _argc > i+1) map_file = _argv[++i]; //wybor pliku mapy
             if(cmd == "-mg" ) generate_map = true; //wybor pliku mapy
             if(cmd == "-mk" && _argc > i+1) map_kh = atof(_argv[++i]); //generacja mapy 1.
             if(cmd == "-me" && _argc > i+1) map_eh = atof(_argv[++i]); //generacja mapy 2.
             if(cmd == "-g" && _argc > i+1) g = atof(_argv[++i]); //zmiana grawitacji
             if(cmd == "-b" && _argc > i+1) b_atm = atof(_argv[++i]); //zmiana atmosfery
             if(cmd == "-ton") turbulence = true; //wlacz/wylacz turbulencje
             if(cmd == "-toff") turbulence = false;
     }
     
     if(generate_map) moon.generate();
}

//funkcja odpowiadajaca na zmiane rozmiaru okna
void resize(int width, int height)
{
    if(height == 0) height = 1;
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (double)width / (double)height, 0.1, 1000000.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//wczytywanie tekstur
/*GLuint load_texture(const char *filename)
{
    GLuint t;
    
    SDL_Surface *gfx = IMG_Load(filename);
    
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, gfx->w, gfx->h, 0, GL_RGB, GL_UNSIGNED_BYTE, gfx->pixels);
    
    return t;
}*/

//inicjalizuj GL
void init_gl(int &argc, char *argv[])
{
    glutInit(&argc, argv);
    
    // tryb rgba + przezroczystosc + bufor z + podwojne buforowanie
    glutInitDisplayMode(GLUT_RGB | GL_DOUBLE | GLUT_DEPTH);
    
    // ustaw okno
    glutInitWindowSize(screenw, screenh);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Apollo");
    
    glClearColor(0.0, 0.0, 10.0*b_atm, 0.0);
    glClearDepth(1.0);
    
    // tryb cieniowania
    glShadeModel(GL_SMOOTH);
    
    // korekcja perspektywiczna
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    
    // wlacz testowanie z
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    //obcinaj tylne sciany poligonow
    glCullFace(GL_BACK);
    
    // ustaw widok
    // projekcja
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (double)screenw / (double)screenh, 0.1, 100000.0);
    
    // widok
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // ustaw parametry swiatla
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    
    // tryb tekstury
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // zastap kolor tekstura a nie zmiksuj
    
    // wczytaj tekstury
    //texture_moon = load_texture("moon.bmp");
    
    //wczytaj modele
    if(!SetCurrentDirectory("data")) {
                                     MessageBox(NULL, "Nie znaleziono katalogu!", "B³¹d", MB_OK);
                                     exit(-1);
    }
    
    stack_model.load("lander.obj");
    aps_model.load("lander2.obj");
    
    
    SetCurrentDirectory("..");
     
    
    // wyczysc stany klawiszy
    for(int i = 0; i < 256; ++i) keys[i] = false;
    
    // ignoruj automatyczne powtarzanie klawiszy
    glutIgnoreKeyRepeat(1);
    
    // wlacz przenikanie
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //okragle punkty
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10.0);
}
