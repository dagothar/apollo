#ifndef _HUD_H
#define _HUD_H

#include <iomanip>
#include <GL/glut.h>

#include "main.h"
#include "control.h"
#include "display.h"
#include "simulink.h"
#include "log.h"

/*---------------------------------------------------------------
         STALE
---------------------------------------------------------------*/
//wymiary slupkow
const int bar_w = 20; //szerokosc slupka
const int bar_h = 100; //wysokosc slupka

//polozenie panelu informacji
const int gui_iwin_x = 10;
const int gui_iwin_y = 360;
const int gui_iwin_w = 260;
const int gui_iwin_h = 220;

//polozenie panelu czasu
const int gui_twin_x = 600;
const int gui_twin_y = 570;
const int gui_twin_w = 190;
const int gui_twin_h = 20;

//polozenie panelu parametrow
const int gui_pwin_x = 10;
const int gui_pwin_y = 10;
const int gui_pwin_w = 260;
const int gui_pwin_h = 185;

//polozenie okna kamery dodatkowej
const int gui_cwin_x = 605;
const int gui_cwin_y = 10;
const int gui_cwin_w = 185;
const int gui_cwin_h = 185;

//polozenie okna wiadomosci
const int gui_mwin_x = 280;
const int gui_mwin_y = 10;
const int gui_mwin_w = 315;
const int gui_mwin_h = 90;


/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//wyswietla informacje w panelu
//void Lander::draw_info();

//wyswietla hud w trybie fpp
//void Lander::draw_hud();

#endif
