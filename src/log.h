#ifndef _LOG_H
#define _LOG_H

#include "main.h"
#include "lander.h"

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//zapis danych do pliku
extern bool logging; //czy logowac?
const double log_dt = 0.1; //co ile logowac dane
extern double last_log; //czas zapisania ostatniego loga
extern std::ofstream log_file; //plik z danymi

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//funkcja logowania do pliku
void log();

#endif
