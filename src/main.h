#ifndef _MAIN_H
#define _MAIN_H

/*---------------------------------------------------------------
         STALE GLOBALNE
---------------------------------------------------------------*/
const double exp_dt = 0.01; //zalozona czestosc odswiezania stanu

//stale fizyczne
extern double g; //stala grawitacji
extern double b_atm; //tarcie atmosfery

/*---------------------------------------------------------------
         ZMIENNE GLOBALNE
---------------------------------------------------------------*/
//flagi globalne
extern bool exit_flag; //koniec programu
extern bool pause_flag; //pauza

//glowne zmienne czasu
extern double t;
extern double t_fps; //licznik czasu do pomiaru fps
extern volatile double dt; //rzeczywiste dt

#endif
