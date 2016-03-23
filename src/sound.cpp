#include "sound.h"

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//dzwiek wlaczony?
bool no_sound = false;

//lista dzwiekow
Mix_Chunk *sounds[SND_N];

//poziom glosnosci silnikow
double dps_sound_lvl = 0.0;
double rcs_sound_lvl = 0.0;
    
/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//inicjalizuj dzwiek
void init_sound()
{
     SDL_Init(SDL_INIT_AUDIO);
     Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
     
     //wczytaj pliki
     sounds[SND_DPS] = Mix_LoadWAV("data/dps.wav");
     if(!sounds[SND_DPS]) {
                           MessageBox(NULL, "Nie znaleziono pliku!", "B³¹d", MB_OK);
                           exit(-1);
     }
     sounds[SND_RCS] = Mix_LoadWAV("data/rcs.wav");
     if(!sounds[SND_RCS]) {
                           MessageBox(NULL, "Nie znaleziono pliku!", "B³¹d", MB_OK);
                           exit(-1);
     }
     sounds[SND_CRASH] = Mix_LoadWAV("data/crash.wav");
     if(!sounds[SND_CRASH]) {
                           MessageBox(NULL, "Nie znaleziono pliku!", "B³¹d", MB_OK);
                           exit(-1);
     }
     
     //silnik glowny
     Mix_PlayChannel(1, sounds[SND_DPS], -1);
     Mix_Volume(1, 0);
     
     //silniki RCS
     Mix_PlayChannel(2, sounds[SND_RCS], -1);
     Mix_Volume(2, 0);
}

//odgrywa dzwiek
void make_sound()
{
     if(!no_sound && !camera_mode) {
                   Mix_Resume(-1);

                   Mix_Volume(1, dps_sound_lvl * MIX_MAX_VOLUME/3);
                   Mix_Volume(2, rcs_sound_lvl * MIX_MAX_VOLUME/4);
     } else {
            Mix_Pause(-1);
     }
}

//dzwiek eksplozji
void crash_sound()
{
     if(!no_sound && !camera_mode) {
                   Mix_Volume(3, MIX_MAX_VOLUME/4);
                   Mix_PlayChannel(3, sounds[SND_CRASH], 0);
     }
}
