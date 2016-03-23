#include "lander.h"
#include <iomanip>

//ladownik
Lander lander;

//flagi
bool turbulence = true; //czy wlaczone zaburzenia pracy silnika

/*---------------------------------------------------------------
         SILNIK
---------------------------------------------------------------*/
Engine::Engine()
{
}

Engine::Engine(Lander *_ship, EngineType _type, double _x, double _y, double _z, double _vx, double _vy, double _vz) :
    ship(_ship), type(_type), u(0.0), x(0.0), x_T(0.0), position(_x, _y, _z), vthrust(_vx, _vy, _vz),  turb_rot(), turb_dy(0.0)
{
    switch(type) {
                 case DPS:
                      k = e_dps_k;
                      T = e_main_T;
                      fuel_source = &ship->main_fuel;
                      flow_rate = dps_flow_rate;
                      f_color[0] = dps_color[0];
                      f_color[1] = dps_color[1];
                      f_color[2] = dps_color[2];
                      break;
                      
                 case APS:
                      k = e_aps_k;
                      T = e_main_T;
                      fuel_source = &ship->main_fuel;
                      flow_rate = aps_flow_rate;
                      f_color[0] = aps_color[0];
                      f_color[1] = aps_color[1];
                      f_color[2] = aps_color[2];
                      break;
                      
                 case RCS:
                      k = e_rcs_k;
                      T = e_rcs_T;
                      fuel_source = &ship->rcs_fuel;
                      flow_rate = rcs_flow_rate;
                      f_color[0] = rcs_color[0];
                      f_color[1] = rcs_color[1];
                      f_color[2] = rcs_color[2];
                      break;
                      
                 case DUMP:
                      k = e_dump_k;
                      T = e_dump_T;
                      fuel_source = &ship->main_fuel;
                      flow_rate = dmp_flow_rate;
                      f_color[0] = dps_fuel_color[0];
                      f_color[1] = dps_fuel_color[1];
                      f_color[2] = dps_fuel_color[2];
                      break;
                      
                 default:
                        k = 0.0;
                        T = 1.0;
    }
}

void Engine::go()
{
     //wyznacz stan silnika wg. modelu
     dx = u - x_T;
     x += dt * dx;
     x_T = x/T;
     
     //pobierz paliwo
     double flow = x_T*flow_rate;
     if(*fuel_source < flow) flow = *fuel_source; //jezeli brakuje paliwa, pobierz tylko tyle ile jest
     *fuel_source -= dt * flow;
     x_T = flow/flow_rate; //wez poprawke na brak paliwa
     
     //wyznacz ciag wyjsciowy
     y = k*x_T;
     
     //oblicz zaklocenia - losowa zmiana kata wektora ciagu
     Vector turb_vthrust;
     if(turbulence) {
                    //jezeli zmiana w danym kroku
                    if(0.1*(rand()%1000) < turb_change_chance) {
                                         turb_rot.from_euler(1.0-0.01*(rand()%200), 1.0-0.01*(rand()%200), 1.0-0.01*(rand()%200));
                                         turb_dy = 1.0+turb_thrust-0.01*(rand()%200)*turb_thrust;
                    }
                    turb_vthrust =  turb_rot.get_conjugate() * vthrust;
                    y *= turb_dy;
     } else
                    turb_vthrust = vthrust;
     
     //sila w ukladzie ladownika
     ship->d2pos += turb_vthrust * y;
     
     //moment w ukladzie ladownika
     ship->d2fi += position * turb_vthrust * y;
     
     //wyznacz poziom dzwieku
     if(type == DPS && x_T > dps_sound_lvl) dps_sound_lvl = x_T;
     if(type == RCS && x_T > rcs_sound_lvl) rcs_sound_lvl = x_T;

     // jezeli to RCS, wylacz
     if(type == RCS || type == DUMP) u = 0.0;
}

void Engine::display()
{
     glPushMatrix();
     
     f_color[3] = x_T*max_plume_alpha; //przezroczystosc
        
     glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, f_color);
     glMaterialfv(GL_FRONT, GL_SPECULAR, f_color);
     glMaterialfv(GL_FRONT, GL_EMISSION, f_color);
     glMaterialfv(GL_FRONT, GL_SHININESS, &f_shinn);
        
     GLUquadricObj *flame = gluNewQuadric();
     //gluQuadricOrientation(flame, GLU_INSIDE);
     //gluQuadricNormals(flame, GLU_FLAT);
     gluQuadricDrawStyle(flame, GLU_FILL);
        
     glTranslatef(position.x, position.y, position.z);
        
     if(vthrust.z > 0.0) glRotatef(180.0, 1.0, 0.0, 0.0); //zrobic dla dowolnych katow a nie tylko 90n
     glRotatef(vthrust.x * -90.0, 0.0, 1.0, 0.0);
     glRotatef(vthrust.y * 90.0, 1.0, 0.0, 0.0);
        
     if(type == DPS || type == APS) gluCylinder(flame, 0.5, 1.8, 1.0, 32, 32);
     else gluCylinder(flame, 0.05, 0.4, 1.0, 32, 32);
        
     GLUquadricObj *disk = gluNewQuadric();
     //gluQuadricOrientation(disk, GLU_INSIDE);
     //gluQuadricNormals(disk, GLU_FLAT);
     gluQuadricDrawStyle(disk, GLU_FILL);
     glTranslatef(0.0, 0.0, 1.0);
     if(type == DPS || type == APS) gluDisk(disk, 0.0, 1.8, 32, 32);
     else gluDisk(disk, 0.0, 0.4, 32, 32);
        
     glPopMatrix();
}

void Engine::reset()
{
     y = x_T = x = u = 0.0;
}

void Engine::set_thrust(double _u)
{
    u = _u;
    
    if(u < 0.0) u = 0.0;
    if(u > 1.0) u = 1.0;
}

double Engine::get_thrust()
{
       return x_T;
}

double Engine::get_u()
{
       return u;
}

/*---------------------------------------------------------------
         LADOWNIK
---------------------------------------------------------------*/
Lander::Lander()
{
}

void Lander::setup(LCon conf)
{
     engines.clear();
     
     switch(conf) {
                  case C_APS:
                       //ustaw model
                       model = &aps_model;
     
                       //ustaw wartosci poczatkowe
                       radius = 2.0;
                       mass_dry = l_a_mass_dry;
                       main_fuel_max = l_aps_max;
                       rcs_fuel_max = l_rcs_max;
                
                       //ustaw silniki
                       // E_MAIN
                       engines.push_back(*(new Engine(this, APS, 0.0, 0.0, -2.5, 0.0, 0.0, 1.0)));
                       // E_U1
                       engines.push_back(*(new Engine(this, RCS, 1.32, 1.32, 1.57, 0.0, 0.0, -1.0)));
                       // E_U2
                       engines.push_back(*(new Engine(this, RCS, 1.32, -1.32, 1.57, 0.0, 0.0, -1.0)));
                       // E_U3
                       engines.push_back(*(new Engine(this, RCS, -1.32, -1.32, 1.57, 0.0, 0.0, -1.0)));
                       // E_U4
                       engines.push_back(*(new Engine(this, RCS, -1.32, 1.32, 1.57, 0.0, 0.0, -1.0)));
                       // E_D1
                       engines.push_back(*(new Engine(this, RCS, 1.32, 1.32, 1.09, 0.0, 0.0, 1.0)));
                       // E_D2
                       engines.push_back(*(new Engine(this, RCS, 1.32, -1.32, 1.09, 0.0, 0.0, 1.0)));
                       // E_D3
                       engines.push_back(*(new Engine(this, RCS, -1.32, -1.32, 1.09, 0.0, 0.0, 1.0)));
                       // E_D4
                       engines.push_back(*(new Engine(this, RCS, -1.32, 1.32, 1.09, 0.0, 0.0, 1.0)));
                       // E_F1
                       engines.push_back(*(new Engine(this, RCS, 1.65, 1.4, 1.3, -1.0, 0.0, 0.0)));
                       // E_F2
                       engines.push_back(*(new Engine(this, RCS, 1.65, -1.4, 1.3, -1.0, 0.0, 0.0)));
                       // E_B1
                       engines.push_back(*(new Engine(this, RCS, -1.65, 1.4, 1.3, 1.0, 0.0, 0.0)));
                       // E_B2
                       engines.push_back(*(new Engine(this, RCS, -1.65, -1.4, 1.3, 1.0, 0.0, 0.0)));
                       // E_L1
                       engines.push_back(*(new Engine(this, RCS, 1.65, 1.4, 1.3, 0.0, -1.0, 0.0)));
                       // E_L2
                       engines.push_back(*(new Engine(this, RCS, -1.65, 1.4, 1.3, 0.0, -1.0, 0.0)));
                       // E_R1
                       engines.push_back(*(new Engine(this, RCS, 1.65, -1.4, 1.3, 0.0, 1.0, 0.0)));
                       // E_R2
                       engines.push_back(*(new Engine(this, RCS, -1.65, -1.4, 1.3, 0.0, 1.0, 0.0)));
                       // E_DUMP
                       engines.push_back(*(new Engine(this, DUMP, 0.0, 1.0, -1.7, 0.0, 0.0, 1.0)));
                       
                       break;
                       
                  default:
                  case C_STACK:
                       //ustaw model
                       model = &stack_model;
     
                       //ustaw wartosci poczatkowe
                       radius = 3.0;
                       mass_dry = l_d_mass_dry;
                       main_fuel_max = l_dps_max;
                       rcs_fuel_max = l_rcs_max;
                
                       //ustaw silniki
                       // E_MAIN
                       engines.push_back(*(new Engine(this, DPS, 0.0, 0.0, -2.5, 0.0, 0.0, 1.0)));
                       // E_U1
                       engines.push_back(*(new Engine(this, RCS, 1.32, 1.32, 1.57, 0.0, 0.0, -1.0)));
                       // E_U2
                       engines.push_back(*(new Engine(this, RCS, 1.32, -1.32, 1.57, 0.0, 0.0, -1.0)));
                       // E_U3
                       engines.push_back(*(new Engine(this, RCS, -1.32, -1.32, 1.57, 0.0, 0.0, -1.0)));
                       // E_U4
                       engines.push_back(*(new Engine(this, RCS, -1.32, 1.32, 1.57, 0.0, 0.0, -1.0)));
                       // E_D1
                       engines.push_back(*(new Engine(this, RCS, 1.32, 1.32, 1.09, 0.0, 0.0, 1.0)));
                       // E_D2
                       engines.push_back(*(new Engine(this, RCS, 1.32, -1.32, 1.09, 0.0, 0.0, 1.0)));
                       // E_D3
                       engines.push_back(*(new Engine(this, RCS, -1.32, -1.32, 1.09, 0.0, 0.0, 1.0)));
                       // E_D4
                       engines.push_back(*(new Engine(this, RCS, -1.32, 1.32, 1.09, 0.0, 0.0, 1.0)));
                       // E_F1
                       engines.push_back(*(new Engine(this, RCS, 1.65, 1.4, 1.3, -1.0, 0.0, 0.0)));
                       // E_F2
                       engines.push_back(*(new Engine(this, RCS, 1.65, -1.4, 1.3, -1.0, 0.0, 0.0)));
                       // E_B1
                       engines.push_back(*(new Engine(this, RCS, -1.65, 1.4, 1.3, 1.0, 0.0, 0.0)));
                       // E_B2
                       engines.push_back(*(new Engine(this, RCS, -1.65, -1.4, 1.3, 1.0, 0.0, 0.0)));
                       // E_L1
                       engines.push_back(*(new Engine(this, RCS, 1.65, 1.4, 1.3, 0.0, -1.0, 0.0)));
                       // E_L2
                       engines.push_back(*(new Engine(this, RCS, -1.65, 1.4, 1.3, 0.0, -1.0, 0.0)));
                       // E_R1
                       engines.push_back(*(new Engine(this, RCS, 1.65, -1.4, 1.3, 0.0, 1.0, 0.0)));
                       // E_R2
                       engines.push_back(*(new Engine(this, RCS, -1.65, -1.4, 1.3, 0.0, 1.0, 0.0)));
                       // E_DUMP
                       engines.push_back(*(new Engine(this, DUMP, 0.0, 1.0, -1.7, 0.0, 0.0, 1.0)));

                       break;
     }
     
     //"zyje"
     alive = true;
     killrot = false;
     fuel_dump = false;
     fuel_25 = fuel_10 = false;
     rcs_25 = rcs_10 = false;
     
     //wyzeruj komendy
     w_main = 0.0;
     u_main = 0.0; //silnik glowny
     u_rot = Vector(); //sterowanie rotacja
     u_trans = Vector(); //sterowanie translacja
     
     //wylacz silniki
     std::vector<Engine>::iterator i;
     for(i = engines.begin(); i != engines.end(); ++i) i->reset();
    
     //ustaw poczatkowa ilosc paliwa
     main_fuel = main_fuel_max;
     rcs_fuel = rcs_fuel_max;
    
     //oblicz startowa mase i moment bezwladnosci
     mass = mass_dry + main_fuel + rcs_fuel;
     I = mass * l_I_per_mass;
}

void Lander::reset()
{
     //"zyje"
     alive = true;
     killrot = false;
     fuel_dump = false;
     fuel_25 = fuel_10 = false;
     rcs_25 = rcs_10 = false;

     //ustaw poczatkowe wartosci polozenia
     pos = Vector(0.0, 0.0, moon.get_height(0.0, 0.0) + 3.0);
     fi.from_euler(0.0, 0.0, 0.0);
     
     //wyzeruj komendy
     w_main = 0.0;
     u_main = 0.0; //silnik glowny
     u_rot = Vector(); //sterowanie rotacja
     u_trans = Vector(); //sterowanie translacja
     
     //wylacz silniki
     std::vector<Engine>::iterator i;
     for(i = engines.begin(); i != engines.end(); ++i) i->reset();
     
     //wyzeruj predkosci
     dpos = Vector();
     dfi = Quaternion();
     fi_euler_p = Vector();
    
     //ustaw poczatkowa ilosc paliwa
     main_fuel = main_fuel_max;
     rcs_fuel = rcs_fuel_max;
    
     //oblicz startowa mase i moment bezwladnosci
     mass = mass_dry + main_fuel + rcs_fuel;
     I = mass * l_I_per_mass;
     
     //skasuj sciezke ladownika
     path.clear();
}

void Lander::kill()
{
     alive = false; //ustaw zabicie
     
     //wyzeruj komendy
     u_main = 0.0; //silnik glowny
     u_rot = Vector(); //sterowanie rotacja
     u_trans = Vector(); //sterowanie translacja
     
     //wylacz silniki
     std::vector<Engine>::iterator i;
     for(i = engines.begin(); i != engines.end(); ++i) i->reset();
     
     //ustaw zerowa ilosc paliwa
     main_fuel = 0.0;
     rcs_fuel = 0.0;
     
     //efekt dzwiekowy
     //poziom glosnosci silnikow 0
     dps_sound_lvl = 0.0;
     rcs_sound_lvl = 0.0;
     crash_sound();
     
     message("Ladownik rozbity", MSG_ALRM);
}

void Lander::display()
{
     glPushMatrix();
     
     // ustaw odpowiednio kat i polozenie
     glTranslatef(pos.x, pos.y, pos.z);
     Matrix m;
     fi.to_matrix(m);
     glMultMatrixf(m);
     
     // wyswietl model
     glEnable(GL_LIGHTING);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     
     model->display();
    
     // wyswietl wydechy silnikow po kolei
     //glPopMatrix();
     std::vector<Engine>::iterator i;
     for(i = engines.begin(); i != engines.end(); ++i) i->display();
     
     glDisable(GL_CULL_FACE);
     glDisable(GL_DEPTH_TEST);
     glDisable(GL_LIGHTING);
     
     //wektor polozenia
     if(show_vectors) {
                      glEnable(GL_COLOR_MATERIAL);
                      glColor4f(0.0, 0.0, 1.0, 1.0);
                      
                      glBegin(GL_LINES);
                         glVertex3f(0.0, 0.0, 0.0);
                         glVertex3f(10.0, 0.0, 0.0);
                      glEnd();
                      
                      glDisable(GL_COLOR_MATERIAL);
     }
    
     glPopMatrix();
}

void Lander::order(double _u_main, Vector _u_rot, Vector _u_trans)
{
     u_main = _u_main;
     u_rot = _u_rot;
     u_trans = _u_trans;
     
     //ogranicz
     if(u_main < 0.0) u_main = 0.0; if(u_main > 1.0) u_main = 1.0;
     if(u_rot.x < -1.0) u_rot.x = -1.0; if(u_rot.x > 1.0) u_rot.x = 1.0;
     if(u_rot.y < -1.0) u_rot.y = -1.0; if(u_rot.y > 1.0) u_rot.y = 1.0;
     if(u_rot.z < -1.0) u_rot.z = -1.0; if(u_rot.z > 1.0) u_rot.z = 1.0;
     if(u_trans.x < -1.0) u_trans.x = -1.0; if(u_trans.x > 1.0) u_trans.x = 1.0;
     if(u_trans.y < -1.0) u_trans.y = -1.0; if(u_trans.y > 1.0) u_trans.y = 1.0;
     if(u_trans.z < -1.0) u_trans.z = -1.0; if(u_trans.z > 1.0) u_trans.z = 1.0;
}

void Lander::kill_rot()
{
     if(killrot) { //jezeli wlaczony
                 bool stop = true;
                 if(dfi.y > 0.0005) u_rot.x = 1.0, stop = false;
                 if(dfi.y < -0.0005) u_rot.x = -1.0, stop = false;
                 if(dfi.x > 0.0005) u_rot.z = -1.0, stop = false;
                 if(dfi.x < -0.0005) u_rot.z = 1.0, stop = false;
                 if(dfi.z > 0.0005) u_rot.y = 1.0, stop = false;
                 if(dfi.z < -0.0005) u_rot.y = -1.0, stop = false;
        
                 if(stop) killrot = false; //zakoncz, jezeli nie ma rotacji
     }
}

void Lander::sim_input()
{
     if(simulink_online) {
                         u_main += sim_in.u_main;
                         u_rot.x += sim_in.u_pitch;
                         u_rot.y += sim_in.u_yaw;
                         u_rot.z += sim_in.u_roll;
     }
}

void Lander::steer()
{     
     //zrealizuj sterowanie - wlacza odpowiednie silniki
     engines[E_MAIN].set_thrust(u_main); //silnik glowny
     
     //pochylenie
     if(u_rot.x > 0.0) {
                engines[E_D1].set_thrust(u_rot.x);
                engines[E_D2].set_thrust(u_rot.x);
                engines[E_U3].set_thrust(u_rot.x);
                engines[E_U4].set_thrust(u_rot.x);
     } else if(u_rot.x < 0.0) {
                engines[E_U1].set_thrust(-u_rot.x);
                engines[E_U2].set_thrust(-u_rot.x);
                engines[E_D3].set_thrust(-u_rot.x);
                engines[E_D4].set_thrust(-u_rot.x);
     }
     
     //odchylenie
     if(u_rot.y > 0.0) {
                engines[E_F2].set_thrust(u_rot.y);
                engines[E_B1].set_thrust(u_rot.y);
                engines[E_L1].set_thrust(u_rot.y);
                engines[E_R2].set_thrust(u_rot.y);
     } else if(u_rot.y < 0.0) {
                engines[E_F1].set_thrust(-u_rot.y);
                engines[E_B2].set_thrust(-u_rot.y);
                engines[E_L2].set_thrust(-u_rot.y);
                engines[E_R1].set_thrust(-u_rot.y);
     }
     
     //przechylenie
     if(u_rot.z > 0.0) {
                engines[E_U2].set_thrust(u_rot.z);
                engines[E_U3].set_thrust(u_rot.z);
                engines[E_D1].set_thrust(u_rot.z);
                engines[E_D4].set_thrust(u_rot.z);
     } else if(u_rot.z < 0.0) {
                engines[E_U1].set_thrust(-u_rot.z);
                engines[E_U4].set_thrust(-u_rot.z);
                engines[E_D2].set_thrust(-u_rot.z);
                engines[E_D3].set_thrust(-u_rot.z);
     }
     
     //translacja x
     if(u_trans.x > 0.0) {
                engines[E_B1].set_thrust(1.0);
                engines[E_B2].set_thrust(1.0);
                engines[E_D1].set_thrust(1.0);
                engines[E_D2].set_thrust(1.0);
     } else if(u_trans.x < 0.0) {
                engines[E_F1].set_thrust(1.0);
                engines[E_F2].set_thrust(1.0);
                engines[E_D3].set_thrust(1.0);
                engines[E_D4].set_thrust(1.0);
     }
     
     //translacja y
     if(u_trans.y > 0.0) {
                engines[E_L1].set_thrust(1.0);
                engines[E_L2].set_thrust(1.0);
                engines[E_D2].set_thrust(1.0);
                engines[E_D3].set_thrust(1.0);
     } else if(u_trans.y < 0.0) {
                engines[E_R1].set_thrust(1.0);
                engines[E_R2].set_thrust(1.0);
                engines[E_D1].set_thrust(1.0);
                engines[E_D4].set_thrust(1.0);
     }
     
     //translacja z
     if(u_trans.z > 0.0) {
                engines[E_D1].set_thrust(1.0);
                engines[E_D2].set_thrust(1.0);
                engines[E_D3].set_thrust(1.0);
                engines[E_D4].set_thrust(1.0);
     } else if(u_trans.z < 0.0) {
                engines[E_U1].set_thrust(1.0);
                engines[E_U2].set_thrust(1.0);
                engines[E_U3].set_thrust(1.0);
                engines[E_U4].set_thrust(1.0);
     }
     
     //zrzut paliwa
     if(fuel_dump) engines[E_DUMP].set_thrust(1.0);
}
 
void Lander::go()
{
     //jezeli rozbity, pomin
     if(!alive) return;
     
     kill_rot();
     sim_input();
     steer(); //realizuj sterowania
     
     //oblicz nowa mase i moment
     mass = mass_dry + main_fuel + rcs_fuel;
     I = mass * l_I_per_mass;
    
     //wyzeruj przyspieszenia liniowe i katowe
     d2pos = Vector();
     d2fi = Vector();

     //poziom glosnosci 0
     dps_sound_lvl = 0.0;
     rcs_sound_lvl = 0.0;
     
     //zbierz przyspieszenia od silnikow
     std::vector<Engine>::iterator eng;
     for(eng = engines.begin(); eng != engines.end(); ++eng) eng->go();
     d2pos /= mass;    
     d2fi /= I;
    
     //przeksztalc do ukladu globalnego
     d2pos = fi.get_conjugate() * d2pos;
    
     // dodaj przyspieszenie grawitacyjne
     d2pos.z -= g;
     d2pos -= dpos * b_atm;

     //odswiez predkosci
     dpos += d2pos * dt;
     dfi += d2fi * dt;
    
     //odswiez polozenia
     pos += dpos * dt;
     fi -= dfi * fi * 0.5 * dt;
     fi.normalise();
    
     //oblicz katy Eulera
     fi_euler = fi.to_euler();
     dfi_euler = (fi_euler - fi_euler_p)*(1/dt);
     fi_euler_p = fi_euler;
    
     //brak paliwa?
     if(get_main_fuel() < 0.25 && !fuel_25) fuel_25 = true, message("Zostalo 25% paliwa APS/DPS", MSG_WARN);
     if(get_main_fuel() < 0.1 && !fuel_10) fuel_10 = true, message("Zostalo 10% paliwa APS/DPS", MSG_ALRM);
     if(get_rcs_fuel() < 0.25 && !rcs_25) fuel_25 = true, message("Zostalo 25% paliwa RCS", MSG_WARN);
     if(get_rcs_fuel() < 0.1 && !rcs_10) fuel_10 = true, message("Zostalo 10% paliwa RCS", MSG_ALRM);
     
     //kolizja z powierzchnia?
     h = pos.z - moon.get_height(pos.x, pos.y) - radius;

     if(h <= 0.0) {
                   pos.z = moon.get_height(pos.x, pos.y) + radius; //pulap poczatkowy
                   h = 0.0;
                   if(dpos.magnitude() > crash_speed) {
                                       std::stringstream aux; std::string text;
                                       aux << "Kolizja - predkosc: " << dpos.magnitude() << " m/s";
                                       getline(aux, text);
                                       message(text, MSG_WARN);
                                       kill();
                   }
                   dpos = Vector(); //wyzeruj predkosci
                   dfi = Quaternion();
    }
    
     //zapis sciezki
     if(t > last_path + path_dt) {
          path.push_back(lander.pos);
          if(path.size() > max_path) path.erase(path.begin());
          last_path = t;
     }
}

void Lander::set_position(double x, double y, double z)
{
    pos = Vector(x, y, z);
}

void Lander::set_orientation(double p, const double y, const double r)
{
     fi.from_euler(p, y, r);
}

bool Lander::is_alive()
{
     return alive;
}

void Lander::toggle_killrot()
{
     killrot = !killrot;
     if(killrot) message("Wlaczony KILLROT", MSG_INFO);
}

void Lander::toggle_dump()
{
     fuel_dump = !fuel_dump;
     if(fuel_dump) message("Wlaczony zrzut paliwa!", MSG_WARN); else
                             message("Wylaczony zrzut paliwa", MSG_INFO);
}

double Lander::get_thrust()
{
       return engines[E_MAIN].get_thrust();
}

double Lander::get_main_fuel()
{
       return main_fuel/main_fuel_max;
}

double Lander::get_rcs_fuel()
{
       return rcs_fuel/rcs_fuel_max;
}
