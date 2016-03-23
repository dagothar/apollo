#ifndef _SOUND_H
#define _SOUND_H

#include <windows.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "display.h"
#include "main.h"

/*---------------------------------------------------------------
         LISTA DZWIEKOW
---------------------------------------------------------------*/
//maksymalna glosnosc silnikow
const int snd_DSP_max = 32;
const int snd_RCS_max = 16;

enum {
     SND_NULL, //offset
     SND_DPS,
     SND_RCS,
     SND_CRASH,
     SND_N //tylko dla wyznaczenia dlugosci
};

//dzwiek wlaczony?
extern bool no_sound;

//lista dzwiekow
extern Mix_Chunk *sounds[SND_N];

//poziom glosnosci silnikow
extern double dps_sound_lvl;
extern double rcs_sound_lvl;

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//inicjalizuj dzwiek
void init_sound();

//odtwarzaj dzwiek
void make_sound();

//dzwiek eksplozji
void crash_sound();

#endif
