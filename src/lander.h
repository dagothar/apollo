#ifndef _LANDER_H
#define _LANDER_H

#include <vector>
#include <GL/glut.h>
#include "main.h"
#include "init.h"
#include "model.h"
#include "vectors.h"
#include "map.h"
#include "simulink.h"
#include "msg.h"

/*---------------------------------------------------------------
         STALE LADOWNIKA
---------------------------------------------------------------*/
//konfiguracja statku
enum LCon {
     C_APS, //tylko czlon wstepujacy
     C_DPS, //tylko czlon zstepujacy
     C_STACK //oba czlony
};

//masy [kg]
const double l_d_mass_dry = 6244.0; //masa wlasna statku(APS+DPS)
const double l_a_mass_dry = 2347.0; //masa wlasna statku (APS)
const double l_dps_max = 8165.0; //masa paliwa glownego silnika DPS
const double l_aps_max = 2353.0; //masa paliwa glownego silnika DPS
const double l_rcs_max = 287.0; //masa paliwa silnikow rcs
const double l_I_per_mass = 2.0; //moment bezwladnosci=masa*l_I_per_mass

//predkosc przy jakiej ladownik ulega rozbiciu
const double crash_speed = 10.0; //[m/s]

//Model silnikow: G_e(s)=e_k/(e_T s + 1)
//max. ciag silnikow [N]
const double e_dps_k = 45040.0; //ciag silnika glownego czlonu ladujacego
const double e_aps_k = 16000.0;  //ciag silnika glownego czlonu wstepujacego
const double e_rcs_k = 441.0; //ciag silnikow rcs
const double e_dump_k = 1.0; //ciag przy zrzucie paliwa

//stale czasowe silnikow [s]
const double e_main_T = 0.5; //T silnika glownego
const double e_rcs_T = 0.1; //T silnikow rcs
const double e_dump_T = 1.0; //T przy zrzucie paliwa

//zuzycie paliwa przy maksymalnym ciagu [kg/s]
const double dps_flow_rate = 14.76; //silnik glowny DPS
const double aps_flow_rate = 5.24;  //silnik glowny APS
const double rcs_flow_rate = 0.16; //silniki rcs
const double dmp_flow_rate = 250.0; //zrzut paliwa

//silniki
//lista silnikow
enum Engines { E_MAIN, E_U1, E_U2, E_U3, E_U4, E_D1, E_D2, E_D3, E_D4, E_F1, E_F2, E_B1, E_B2, E_L1, E_L2, E_R1, E_R2, E_DUMP };
enum EngineType { DPS, APS, RCS, DUMP }; //typ silnika

//losowe zaburzenia pracy silnika
extern bool turbulence; //czy wlaczone zaburzenia pracy silnika
const double turb_thrust = 0.05; //procentowe odchylenia ciagu silnika
const double turb_max_angle = 0.5; //maksymalne odchylenie wektora ciagu
const double turb_change_chance = 15.0; //procent szans na zmiane wektora ciagu w danym kroku

/*---------------------------------------------------------------
         STRUKTURY
---------------------------------------------------------------*/
class Lander;

//silniki
class Engine {
      public:
             //konstruktory
             Engine();
             Engine(Lander *_ship, EngineType _type, double x, double y, double z, double vx, double vy, double vz);

             //glowne funkcje   
             void go(); //dzialanie
             void display(); //wyswietlenie wydechu
             
             //funkcje pomocnicze  
             void reset(); //reset stanu
             void set_thrust(double _u); //ustawia wartosc zadana
             double get_thrust(); //zwraca osiagniety % max. ciagu
             double get_u(); //zwraca zadana wartosc
    
    private:
            Lander *ship; //do jakiego statku przynalezy silnik
            
            EngineType type; //typ silnika
    
            Vector position; //polozenie silnika
            Vector vthrust; //kierunek wektora ciagu

            //parametry silnika
            double k, T; //ciag, stala czasowa
            
            double u; //wartosc zadana
            double dx, x; //stan pracy silnika
            double x_T; //pomocniczy stan pracy x_T=x/T
            double y; //ciag wyjsciowy
            
            //zaklocenia
            Quaternion turb_rot; //kat obrotu wektora ciagu przy obliczaniu zaklocen
            double turb_dy; //zmiana ciagu silnika
            
            //zmienne pomocnicze
            double *fuel_source; //zrodlo paliwa
            double flow_rate; //pobor paliwa
            float f_color[4]; //kolor wydechu
};

//ladownik
class Lander {
      public:
             //konstruktor
             Lander();
             
             //glowne funkcje
             void go(); //dzialanie
             void display(); //wyswietlenie
             
             //funkcje pomocnicze
             void setup(LCon conf); //wlasciwie inicjalizuje klase
             void reset(); //resetuje stan ladownika
             void kill(); //rozbij
             void order(double _u_main, Vector _u_rot, Vector _u_trans); //zadaje wejscie
             void set_position(double x, double y, double z); //ustawia nowe polozenie
             void set_orientation(double p, double y, double r); //ustawia nowa orientacje
             bool is_alive(); //zwraca stan ladownika
             void toggle_killrot(); //wlacza/wylacza killrot
             void toggle_dump(); //wlacza/wylacza zrzut paliwa
             double get_thrust(); //zwraca osiagniety % max ciagu glownego silnika
             double get_main_fuel(); //zwraca % pozostalego paliwa dps
             double get_rcs_fuel(); //zwraca % pozostalego paliwa rcs
             void draw_vectors(); //rysuje wektory
             void draw_vectors_fpp(); //jw. w trybi fpp
             void draw_info(); //wyswietla informacje o ladowniku
             void draw_hud(); //wyswietla hud w trybie fpp
             void draw_path(); //wyswietla sciezke
             void draw_shadow(); //wyswietla slad na ziemi
             void display_cam(); //wyswietla obraz z kamery

        private:
                //konfiguracja statku
                LCon configuration;
                
                //flagi
                bool alive; //czy zyje
                bool killrot; //czy wlaczony killrot
                bool fuel_dump; //zrzut paliwa?
                bool fuel_25, fuel_10; //flagi dla komunikatow
                bool rcs_25, rcs_10; 
                
                //wartosci wejsciowe
                double u_main; //silnik glowny
                Vector u_rot; //sterowanie rotacja
                Vector u_trans; //sterowanie translacja

                //polozenie, predkosc, przyspieszenie
                Vector pos;
                Vector dpos;
                Vector d2pos;
                double h; //wysokosc nad powierzchnia

                //polozenie, predkosc, przyspieszenie katowe    
                Quaternion fi;
                Quaternion dfi;
                Vector d2fi;
    
                //katy Eulera - pitch, yaw, roll - pochylenie, odchylenie, przechylenie
                Vector fi_euler; //orientacja
                Vector fi_euler_p; //poprzednia orientacja
                Vector dfi_euler; //predkosc obrotowa

                double mass, I; //masa, moment bezwladnosci
                double main_fuel; //pozostala ilosc paliwa silnika glownego
                double rcs_fuel; //pozostala ilosc paliwa RCS
                
                //wartosci poczatkowe
                double radius;
                double mass_dry; //masa bez palwa
                double main_fuel_max; //maksymalna ilosc paliwa glownego silnika
                double rcs_fuel_max; //maksymalna ilosc paliwa silnikow RCS
    
                Model *model; //model graficzny
    
                // silniki
                std::vector<Engine> engines;
                
                std::vector<Vector> path; //dane sciezki
                
                //funkcje
                void kill_rot(); //wbudowany autopilot killrot
                void sim_input(); //pobierz wartosci z Simulinka
                void steer(); //realizuje sterowania wlaczajac odpowiednie silniki

                //klasy i funkcje zaprzyjaznione
                friend class Engine;
                friend void display();
                friend void log();
                friend void com_update();
                friend void go();
};

//ladownik
extern Lander lander;

#endif
