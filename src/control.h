#ifndef _CONTROL_H
#define _CONTROL_H

#include "main.h"
#include "map.h"
#include "log.h"
#include "msg.h"

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//sterowanie WSADem
extern bool WSAD_flag; //0 - steruje ladownikem, 1 - steruje kamera

//tryb sterowania
enum SteeringType { ROT, TRANS }; //tryby RCS
extern SteeringType steering;

//sterowania
extern double w_main; //sterowanie glownym silnikiem
extern double w_space; //sterowanie od spacji


//parametry edycji zmiennych Simulinka
const double sim_p_inc = 1.0;
const double sim_p_log = 1.1;

extern bool sim_p_mode; //tryb edycji: 0-inkrementalny, 1-logarytmiczny
extern unsigned short sim_p; //wybrany do edycji parametr Simulinka

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//obsluga klawiatury - zarejestruj wcisniecie klawisza
void keydown(unsigned char key, int x, int y); //tutaj sterowanie wejsc bistabilnych

//obsluga klawiatury - zarejestruj puszczenie klawisza 
void keyup(unsigned char key, int x, int y);

//obsluga klawiatury - klawisze specjalne
void spcdown(int key, int x, int y);
void spcup(int key, int x, int y);

//obsluga wejscia od uzytkownika
void ctrl(); //sterowanie wejsc monostabilnych

#endif
