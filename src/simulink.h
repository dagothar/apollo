#ifndef _SIM_H
#define _SIM_H

#include <windows.h>
#include "PracticalSocket.h"

#include "main.h"
#include "lander.h"

/*---------------------------------------------------------------
         STALE
---------------------------------------------------------------*/
//parametry komunikacji
const short unsigned recv_port = 12003; //na jakim porcie odbior
const short unsigned send_port = 12001; //na jakim porcie nadawanie
const double sim_timeout = 0.5; //po ilu sek. uznac Simulink za odlaczony

const unsigned int sim_f_mask = 0x00; //jake flagi moze zapisac Simulink(nie dziala)
const short sim_n_param = 8; //ilosc parametrow wysylanych z programu do Simulinka

//bity flag wyjsciowych do Simulinka
enum SimSwitch {
     SIM_RESET = 0x01, //flagi programu
     SIM_ALIVE = 0x02,
     SIM_PAUSE = 0x04,
     SIM_M_0 = 0x10, //przelaczniki monostabilne
     SIM_M_1 = 0x20,
     SIM_M_2 = 0x40,
     SIM_M_3 = 0x80,
     SIM_B_0 = 0x100, //przelaczniki bistabilne
     SIM_B_1 = 0x200,
     SIM_B_2 = 0x400,
     SIM_B_3 = 0x800
};

/*---------------------------------------------------------------
         DEFINICJE TYPOW
---------------------------------------------------------------*/
//typ struktury dla danych wejsciowych
typedef struct {
        unsigned int flags;
        
        double u_main; //sterowanie glownym silnikiem
        double u_pitch; //sterowanie pochyleniem
        double u_yaw; //sterowanie odchyleniem
        double u_roll; //sterowanie przechyleniem
} InData;

//typ struktury dla danych wyjsciowych
typedef struct {
        unsigned int flags;
 
        double dps, rcs; //pozostale paliwo/max.paliwo
        
        double x, y, z, h; //polozenie
        double dx, dy, dz; //predkosc
        
        double pitch, yaw, roll; //orientacja
        double dpitch, dyaw, droll; //predkosc katowa
        
        double param[sim_n_param]; //parametry wysylane do Simulinka
} OutData;

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
extern std::string sim_host; //adres na ktorym dziala Simulink

extern InData sim_in; //bufor wejsciowy
extern OutData sim_out; //bufor wyjsciowy

extern bool simulink_online; //czy Simulink online
extern clock_t sim_clock; //czas ostatniej komunikacji

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
DWORD WINAPI com_thread(LPVOID param); //glowny watek komunikacji z Simulinkiem

void com_update(); //update danych wejsciowych i wyjsciowych

#endif
