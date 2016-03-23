#ifndef _MAP_H
#define _MAP_H

#include <GL/glut.h>

#include "model.h"
#include "vectors.h"
#include "init.h"
#include "msg.h"
#include "main.h"

/*---------------------------------------------------------------
         KOLORY I STALE
---------------------------------------------------------------*/
//kolor powierzchni
const GLfloat moon_ambdiff[4]  = { 0.30, 0.30, 0.30, 1.0 };
const GLfloat moon_specular[4] = { 0.05, 0.05, 0.05, 1.0 };
const GLfloat moon_shin = 0.0;

//parametry powierzchni
const int n_nodes = 256; //ilosc wezlow mapy powierzchni (potega 2)
const double node_size = 30.0; //dlugosc pojedynczej krawedzi

//parametry generatora fraktalnego
extern double map_kh; //maksymalna wysokosc poczatkowych odchylen
extern double map_eh; //co ile zmniejszac odchylenie w kolejnym kroku

/*---------------------------------------------------------------
         STRUKTURA
---------------------------------------------------------------*/
class Map {
      public:
             //konstruktory
             Map();
             
             //glowne funkcje
             void generate(); //generuje dane
             void load(const char *filename); //wczytaj z pliku
             void save(const char *filename); //zapisz do pliku
             void display(); //wyswietla mape
             
             double get_height(double x, double y); //znajdz wysokosc w punkcie (x, y)
             
      private:
              double hmap[n_nodes+1][n_nodes+1]; //mapa wysokosci
              GLuint display_list; //lista wyswietlania
              
              //funkcje pomocnicze
              double noise(double amp); //szum
              
              void square(int x, int y, int step, double amp); //generator fraktalny
              void diamond(int x, int y, int step, double amp);
              
              void prepare(); //przygotowuje liste wyswietlania
};

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//mapa
extern Map moon;

//nazwa pliku z mapa
extern char *map_file;

#endif
