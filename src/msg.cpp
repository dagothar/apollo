#include "msg.h"

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//wektor wiadomosci
std::vector<Message> msg_list;

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//wyswietla kolejna wiadomosc
void message(std::string msg, MsgType type)
{
     Message t;
     t.text = msg;
     t.type = type;
     
     msg_list.insert(msg_list.begin(), t);
     if(msg_list.size() > max_messages) msg_list.erase(msg_list.end());
}

//czysci bufor wiadomosci
void clear_messages()
{
     
}

//wyswietla wiadomosci
void display_messages()
{
     #define X (gui_mwin_x + 10)
     #define Y(L) (gui_mwin_y + 10 + 15*L)
     
     std::vector<Message>::iterator i;
     int j = 0;
     
     for(i = msg_list.begin(); i != msg_list.end(); ++i, j++) {
           glColor4f(msg_colors[i->type][0], msg_colors[i->type][1], msg_colors[i->type][2], msg_colors[i->type][3]);
           glutPrint(X, Y(j), text_scale, text_font, i->text);
     }
}
