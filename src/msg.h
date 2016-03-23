#ifndef _MSG_H
#define _MSG_H

#include <vector>
#include <string>
#include <GL/glut.h>

#include "main.h"
#include "init.h"

/*---------------------------------------------------------------
         STALE
---------------------------------------------------------------*/
//typy wiadomosci
enum MsgType {
     MSG_OK,
     MSG_INFO,
     MSG_WARN,
     MSG_ALRM,
     _MSG_N
};

//definicja typu wiadomosci
typedef struct {
        std::string text;
        MsgType type;
} Message;

//maksymalna ilosc wiadomosci
const int max_messages = 5;

//kolory wiadomosci
const GLfloat msg_colors[_MSG_N][4] =
{
      {0.0, 1.0, 0.0, 1.0},
      {1.0, 1.0, 1.0, 1.0},
      {1.0, 1.0, 0.0, 1.0},
      {1.0, 0.0, 0.0, 1.0}
};

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//wektor wiadomosci
extern std::vector<Message> msg_list;

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//wyswietla kolejna wiadomosc
void message(std::string msg, MsgType type);

//czysci bufor wiadomosci
void clear_messages();

//wyswietla wiadomosci
void display_messages();

#endif
