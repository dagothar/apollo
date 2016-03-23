#include "simulink.h"

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
std::string sim_host = "localhost"; //adres na ktorym dziala Simulink

InData sim_in; //bufor wejsciowy
OutData sim_out; //bufor wyjsciowy

bool simulink_online = false; //czy Simulink online
clock_t sim_clock; //czas ostatniej komunikacji

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
 //glowny watek komunikacji z Simulinkiem
DWORD WINAPI com_thread(LPVOID param)
{
      UDPSocket sockS;
      UDPSocket sockR(recv_port);
      
      short unsigned r_port;// = 12002;
      string t_host;
      
      while(!exit_flag) {
                        //odbior
                        sockR.recvFrom((void *)&sim_in, sizeof(sim_in), t_host, r_port);

                        com_update();

                        //wysylanie
                        sockS.sendTo((void *)&sim_out, sizeof(sim_out), sim_host, send_port);
                        
                        Sleep(1);
      }     

      return NULL;
}

//update danych wejsciowych i wyjsciowych
void com_update()
{
     if(!simulink_online) message("Simulink online", MSG_OK);
     
     simulink_online = true;
     sim_clock = clock();
     
     //ustaw flagi
     if(lander.is_alive()) sim_out.flags |= SIM_ALIVE; else sim_out.flags &= ~SIM_ALIVE;
     if(pause_flag) sim_out.flags |= SIM_PAUSE; else sim_out.flags &= ~SIM_PAUSE;
             
     //przekaz paliwo
     sim_out.dps = lander.get_main_fuel();
     sim_out.rcs = lander.get_rcs_fuel();
     
     //przekaz pozycje
     sim_out.x = lander.pos.x;
     sim_out.y = -lander.pos.y; //korekcja na odwrocenie osi
     sim_out.z = lander.pos.z; //korekcja na srodek masy
     sim_out.h = lander.h;
     
     //przekaz orientacje
     sim_out.pitch = lander.fi_euler.x;
     sim_out.yaw = lander.fi_euler.y;
     sim_out.roll = lander.fi_euler.z;
     
     //przekaz predkosc
     sim_out.dx = lander.dpos.x;
     sim_out.dy = -lander.dpos.y;
     sim_out.dz = lander.dpos.z;
     
     //przekaz predkosc katowa
     sim_out.dpitch = lander.dfi_euler.x;
     sim_out.dyaw = lander.dfi_euler.y;
     sim_out.droll = lander.dfi_euler.z;
}
