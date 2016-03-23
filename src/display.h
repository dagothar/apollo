#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <GL/glut.h>

#include "main.h"
#include "init.h"
#include "hud.h"
#include "lander.h"
#include "simulink.h"
#include "sound.h"

/*---------------------------------------------------------------
         PARAMETRY OKNA I KAMERY
---------------------------------------------------------------*/
//parametry okna graficznego
const double fov = 45;
const int screenw = 800;
const int screenh = 600;

//stale kamery
const double camera_angle_per_sec = 30.0;
const double camera_initial_distance = 50.0;
const double camera_initial_height = 3.0;
const double camera_initial_pitch = 0.0;
const double camera_initial_yaw = 0.0;

//pozycja kamery
extern Vector c_pos;
extern double camera_pitch;
extern double camera_yaw;

//tryb kamery
extern bool camera_mode; //0 - fpp, 1 - tpp

const double text_scale = 0.2; //skala tekstu
void * const text_font = GLUT_BITMAP_HELVETICA_12; //czcionka zwykla
void * const text_big_font = GLUT_BITMAP_HELVETICA_18; //czcionka duza

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//modele
extern Model stack_model; //caly ladownik
extern Model aps_model; //czlon aps
extern Model dps_model; //czlon dps

extern unsigned long frames; //ilosc klatek w sumie
extern double fps; //ilosc klatek na sekunde

//czy pokazac wektory sil itp.
extern bool show_vectors;

//okno kamery dodatkowej
extern bool show_aux_cam;

//sciezka ruchu ladownika na ekranie
const double path_dt = 0.5; //co ile sekund dodawac nowy segment
const int max_path = 250; //ile krokow zapamietac maksymalnie
extern bool mark_path; //czy rysowac
extern double last_path; //czas ostatniego dodania segmentu

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//glowna funkcja wyswietlania 
void display();

//wypisuje tekst na ekran
void glutPrint(double x0, double y0, double scale, void *font, std::string text);

//resetuj kamere
void reset_camera();

//wyswietla sciezke ladownika
//void Lander::draw_path();

//wyswietla slad na ziemi
//void Lander::draw_shadow();

//wyswietla wektory predkosci itp.
//void Lander::draw_vectors();

//wyswietla wektory predkosci itp. w trybie fpp
//void Lander::draw_vectors_fpp();

//wyswietla obraz z kamery dodatkowej
//void Lander::display_cam();

#endif
