#include "control.h"

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//sterowania
double w_main; //sterowanie glownym silnikiem
double w_space; //sterowanie od spacji
double w_pitch, w_yaw, w_roll; //sterowania obrotow
double w_x, w_y, w_z; //sterowania translacji

//sterowanie WSADem
bool WSAD_flag = true; //0 - steruje ladownikem, 1 - steruje kamera

//tryb sterowania RCS
SteeringType steering = ROT;

bool sim_p_mode; //tryb edycji: 0-inkrementalny, 1-logarytmiczny
unsigned short sim_p; //wybrany do edycji parametr Simulinka

/*---------------------------------------------------------------
        FUNKCJE
---------------------------------------------------------------*/
//obsluga klawiatury - zarejestruj puszczenie klawisza 
void keyup(unsigned char key, int x, int y)
{
    keys[key] = false;
}

//obsluga klawiatury - zarejestruj wcisniecie klawisza
void keydown(unsigned char key, int x, int y)
{
     keys[key] = true;
     
     //sterowania bistabilne
     switch(key) {
                 case 27: //esc
                      log_file.close();
        
                      glutDestroyWindow(window);
                      exit(0);
                      break;
                      
                 case 'p':
                      pause_flag = !pause_flag;
                      message(string("Pauza ")+string(pause_flag?"wlaczona":"wylaczona"), MSG_INFO);
                      break;
                      
                 case 9: //tab
                      WSAD_flag = !WSAD_flag;
                      break;
                      
                 case 'n':
                      no_sound = !no_sound;
                      message(string("Dzwiek ")+string(!no_sound?"wlaczony":"wylaczony"), MSG_INFO);
                      break;
                      
                 case 'f':
                      camera_mode = !camera_mode;
                      break;
                      
                 case '+':
                 case '=':
                      w_main += 0.05;
                      if(w_main > 1.0) w_main = 1.0;
                      break;
                      
                 case '-':
                      w_main -= 0.05;
                      if(w_main < 0.0) w_main = 0.0;
                      break;
                      
                 case ',':
                      if(steering == ROT) {
                                  steering = TRANS;
                                  message("RCS: translacja", MSG_INFO);
                      } else {
                             steering = ROT;
                             message("RCS: rotacja", MSG_INFO);
                      }
                      break;
                      
                 case 'l':
                      logging = !logging;
                      message(string("Logowanie ")+string(logging?"wlaczone":"wylaczone"), MSG_INFO);
                      break;
                      
                 case 'b':
                      mark_path = !mark_path;
                      break;
                      
                 case 'v':
                      show_vectors = !show_vectors;
                      break;
                      
                 case 'o':
                      lander.setup(C_STACK);
                      lander.reset();
                      lander.set_position(0.0, 0.0, 1000.0);
                      message("Ladownik nad powierzchnia", MSG_INFO);
        
                      frames = 0;
                      t = 0.0;
                      break;
                      
                 case 'g':
                      lander.setup(C_STACK);
                      lander.reset();
                      message("Ladownik na ziemi", MSG_INFO);
        
                      frames = 0;
                      t = 0.0;
                      break;
        
                 case 'u':
                      lander.toggle_dump();
                      break;
                      
                 case 'm':
                      show_aux_cam = !show_aux_cam;
                      break;
                      
                 case 'k':
                      lander.kill();
                      break;
                      
                 case 'j':
                      lander.setup(C_APS);
                      w_main = 1.0;
                      //lander.reset();
                      //lander.set_position(0.0, 0.0, 1500.0);
                      //lander.set_orientation(rand()%180-90, rand()%360-180, rand()%360-180);
                      break;
                      
                 case '5':
                      lander.toggle_killrot();
                      break;
    }
}

void spcdown(int key, int x, int y)
{
     double dp = sim_p_inc;
     if(glutGetModifiers() & GLUT_ACTIVE_CTRL) dp /= 10.0;
     if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) dp *= 10.0;
     
     switch(key) {
                 case GLUT_KEY_LEFT:
                      if(sim_p_mode)
                                    sim_out.param[sim_p] *= 1.0/sim_p_log;
                      else
                                    sim_out.param[sim_p] -= dp;
                      break;
                      
                 case GLUT_KEY_RIGHT:
                      if(sim_p_mode)
                                    sim_out.param[sim_p] *= sim_p_log;
                      else
                                    sim_out.param[sim_p] += dp;
                      break;
                      
                 case GLUT_KEY_UP:
                      sim_p = sim_p < sim_n_param-1 ? sim_p+1 : 0;
                      break;
                      
                 case GLUT_KEY_DOWN:
                      sim_p = sim_p > 0 ? sim_p-1 : sim_n_param-1;
                      break;
                      
                 case GLUT_KEY_HOME:
                      sim_out.param[sim_p] = 0.0;
                      break;
                                       
                 case GLUT_KEY_INSERT:
                      sim_p_mode = !sim_p_mode;
                      break;
                      
                 case GLUT_KEY_F1:
                      sim_out.flags |= SIM_M_0; break;
                      
                 case GLUT_KEY_F2:
                      sim_out.flags |= SIM_M_1; break;
                      
                 case GLUT_KEY_F3:
                      sim_out.flags |= SIM_M_2; break;
                      
                 case GLUT_KEY_F4:
                      sim_out.flags |= SIM_M_3; break;
                      
                 case GLUT_KEY_F5:
                      sim_out.flags ^= SIM_B_0; break;
                      
                 case GLUT_KEY_F6:
                      sim_out.flags ^= SIM_B_1; break;
                      
                 case GLUT_KEY_F7:
                      sim_out.flags ^= SIM_B_2; break;
                      
                 case GLUT_KEY_F8:
                      sim_out.flags ^= SIM_B_3; break;
     }
}

void spcup(int key, int x, int y)
{
     switch(key) {
                 case GLUT_KEY_F1:
                      sim_out.flags &= ~SIM_M_0; break;
                      
                 case GLUT_KEY_F2:
                      sim_out.flags &= ~SIM_M_1; break;
                      
                 case GLUT_KEY_F3:
                      sim_out.flags &= ~SIM_M_2; break;
                      
                 case GLUT_KEY_F4:
                      sim_out.flags &= ~SIM_M_3; break;
                      }
}

//obsluga wejscia
void ctrl()
{
     //zeruj RCS
     w_pitch = w_yaw = w_roll = 0.0; //normalnie 0
     w_x = w_y = w_z = 0.0; //normalnie 0
     
     // praca kamery
     if(WSAD_flag) {
                   if(keys['w']) camera_pitch -= dt * camera_angle_per_sec;
                   if(keys['s']) camera_pitch += dt * camera_angle_per_sec;
                   if(keys['a']) camera_yaw += dt * camera_angle_per_sec;
                   if(keys['d']) camera_yaw -= dt * camera_angle_per_sec;
     } else {
            if(keys['w']) steering == ROT ? w_pitch += -1.0 : w_x += 1.0;
            if(keys['s']) steering == ROT ? w_pitch += 1.0 : w_x += -1.0;
            if(keys['q']) steering == ROT ? w_yaw += -1.0 : w_z += -1.0;
            if(keys['e']) steering == ROT ? w_yaw += 1.0 : w_z += 1.0;
            if(keys['a']) steering == ROT ? w_roll += -1.0 : w_y += -1.0;
            if(keys['d']) steering == ROT ? w_roll += 1.0 : w_y += 1.0;
     }
    
     // przyblizanie i oddalanie kamery
     if(keys['x']) {
                   c_pos.x *= 1.0 + dt;
                   if(c_pos.x < -2000.0) c_pos.x = -2000.0;
     }
     if(keys['z']) {
                   c_pos.x /= 1.0 + dt;
                   if(c_pos.x > -10.0) c_pos.x = -10.0;
     }
     
     //reset kamery
     if(keys['c']) reset_camera();
    
     // kontrola silnika
     w_space = 0.0;
     if(keys[' ']) w_space = 1.0;
     if(keys['*'] || keys[']']) w_main = 1.0;
     if(keys['/'] || keys['[']) w_main = 0.0;
    
     if(keys['8']) steering == ROT ? w_pitch += -1.0 : w_x += 1.0;
     if(keys['2']) steering == ROT ? w_pitch += 1.0 : w_x += -1.0;
     if(keys['1']) steering == ROT ? w_yaw += -1.0 : w_z += -1.0;
     if(keys['3']) steering == ROT ? w_yaw += 1.0 : w_z += 1.0;
     if(keys['4']) steering == ROT ? w_roll += -1.0 : w_y += -1.0;
     if(keys['6']) steering == ROT ? w_roll += 1.0 : w_y += 1.0;
    
     lander.order(w_main+w_space, Vector(w_pitch, w_yaw, w_roll), Vector(w_x, w_y, w_z));
     
     if(keys['r']) sim_out.flags |= SIM_RESET; else sim_out.flags &= ~SIM_RESET;
}
