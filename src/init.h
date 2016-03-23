#ifndef _INIT_H
#define _INIT_H

#include "vectors.h"
#include "display.h"
#include "map.h"
#include "main.h"

/*---------------------------------------------------------------
         KOLORY
---------------------------------------------------------------*/
//kolory
const float thr_color[4]      = { 0.5, 0.0, 0.0, 0.7 };
const float bar_color[4]      = { 1.0, 1.0, 1.0, 0.3 };
const float dps_fuel_color[4] = { 0.0, 0.5, 0.0, 0.7 };
const float rcs_fuel_color[4] = { 0.5, 0.5, 0.0, 0.7 };
const float info_color[4]     = { 0.1, 0.1, 0.1, 0.4 };
const float hud_color[4]      = { 0.87,0.73,0.13,1.0 };
const float text_color[4]     = { 1.0, 1.0, 1.0, 1.0 };
const float msg_color[4]      = { 1.0, 0.0, 0.0, 1.0 };
const float f_shinn           = 0.1;

// kolory
const float no_emiss[4]       = { 0.0, 0.0, 0.0, 0.0 };
const float dps_color[4]      = { 0.0, 0.0, 0.5, 0.0 };
const float aps_color[4]      = { 0.5, 0.5, 0.5, 0.0 };
const float rcs_color[4]      = { 0.5, 0.5, 0.5, 0.0 };
const float max_plume_alpha   = 0.25;

// swiatlo
const GLfloat light_ambient[4]  = { 0.2, 0.2, 0.2, 1.0 };
const GLfloat light_diffuse[4]  = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat light_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat light_position[4] = { -5000.0, -5000.0, 4000.0, 1.0 };

//uchwyt glownego okna
extern int window;

/*---------------------------------------------------------------
         ZMIENNE GLOBALNE
---------------------------------------------------------------*/
//aktualny stan klawiszy
extern volatile bool keys[256];

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//interpretuj parametry linii komend
void cmd_line();
    
//zmiana rozmiaru okna
void resize(int width, int height);

//wczytywanie tekstur
GLuint load_texture(const char *filename);

//inicjalizuj GL
void init_gl(int &argc, char *argv[]);

#endif
