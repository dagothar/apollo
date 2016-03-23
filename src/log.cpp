#include "log.h"

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//zapis danych do pliku
bool logging = false; //czy logowac?
double last_log = -1.0; //czas zapisania ostatniego loga
std::ofstream log_file; //plik z danymi

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//funkcja logowania
void log()
{
    //czas
    log_file << t << ", ";
    
    //polozenie
    log_file << lander.pos.x << ", " << lander.pos.y << ", " << lander.pos.z - 3.0 << ", " << lander.h << ", "; // jest nas wielu - bedzie wiecej
    
    //katy eulera - pitch, yaw, roll
    log_file << lander.fi_euler.x << ", " << lander.fi_euler.y << ", " << lander.fi_euler.z << '\n';
}
