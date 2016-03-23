#include "hud.h"

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//pokaz hud w trybie fpp
void Lander::draw_hud()
{
     std::string text; //zmienne pomocnicze
     std::stringstream aux;
     aux.precision(1);
     aux.setf(std::ios::fixed, std::ios::floatfield);
     aux.setf(std::ios::right);
    
     //ustaw widok orto
     glMatrixMode(GL_PROJECTION);
     glPushMatrix();
     glLoadIdentity();
     glOrtho(-screenw/2, screenw/2, -screenh/2, screenh/2, -10.0, 10.0);
     glMatrixMode(GL_MODELVIEW);
     glPushMatrix();
     glLoadIdentity();
     glEnable(GL_COLOR_MATERIAL);
     
     glColor4f(hud_color[0], hud_color[1], hud_color[2], hud_color[3]);

     //informacje
     //wysokosc
     #define X -125.0
     #define Y 25.0
     #define W 75.0
     #define H 20.0
     glBegin(GL_LINE_LOOP);
     glVertex2f(X, Y);
     glVertex2f(X+W, Y);
     glVertex2f(X+W, Y+H);
     glVertex2f(X, Y+H);
     glEnd();
     aux << "H:  " << std::setw(5) << h;
     getline(aux, text);
     glutPrint(X+5.0, Y+5.0, 1.0, text_font, text);
     aux.clear(); text.clear();
     
     //predkosc spadania
     #define X -125.0
     #define Y -45.0
     #define W 75.0
     #define H 20.0
     glBegin(GL_LINE_LOOP);
     glVertex2f(X, Y);
     glVertex2f(X+W, Y);
     glVertex2f(X+W, Y+H);
     glVertex2f(X, Y+H);
     glEnd();
     aux << "VV: " << std::setw(5) << dpos.z;
     getline(aux, text);
     glutPrint(X+5.0, Y+5.0, 1.0, text_font, text);
     aux.clear(); text.clear();
     
     //predkosc do przodu
     #define X 50.0
     #define Y -45.0
     #define W 75.0
     #define H 20.0
     glBegin(GL_LINE_LOOP);
     glVertex2f(X, Y);
     glVertex2f(X+W, Y);
     glVertex2f(X+W, Y+H);
     glVertex2f(X, Y+H);
     glEnd();
     double vh = sqrt(dpos.x*dpos.x + dpos.y*dpos.y);
     aux << "VH: " << std::setw(5) << vh;
     getline(aux, text);
     glutPrint(X+5.0, Y+5.0, 1.0, text_font, text);
     aux.clear(); text.clear();
     
     //pitch
     aux << "P: " << std::setw(6) << fi_euler.x;
     getline(aux, text);
     glutPrint(-25.0, -3.0, 1.0, text_font, text);
     aux.clear(); text.clear();
     //yaw
     aux << "Y: " << std::setw(6) << fi_euler.y;
     getline(aux, text);
     glutPrint(-150.0, -3.0, 1.0, text_font, text);
     aux.clear(); text.clear();
     //roll
     aux << "R: " << std::setw(6) << fi_euler.z;
     getline(aux, text);
     glutPrint(100.0, -3.0, 1.0, text_font, text);
     aux.clear(); text.clear();
     
     //wskazniki poziomu (trojkaty)
     glBegin(GL_LINE_LOOP);
     glVertex2f(-75.0, 10.0);
     glVertex2f(-50.0, 0.0);
     glVertex2f(-75.0, -10.0);
     glEnd();
     glBegin(GL_LINE_LOOP);
     glVertex2f(75.0, 10.0);
     glVertex2f(50.0, 0.0);
     glVertex2f(75.0, -10.0);
     glEnd();
                     
     //wskaznik horyzontu
     double y = M_PI * fi_euler.y/180.0;
     double p = M_PI * fi_euler.x/180.0;
     double r = M_PI * fi_euler.z/180.0;
     double a = sqrt(2)*screenh;
     double sp = sin(p);
     double sr = sin(r); double cr = cos(r);
     
     glBegin(GL_LINES);
     glVertex2f(a*sp*sr-50.0*cr, -a*sp*cr-50.0*sr);
     glVertex2f(a*sp*sr+50.0*cr, -a*sp*cr+50.0*sr);
     
     //podzialka pitch
     for(int i = -90; i < 90; i +=5 ) {
             double pi = p + M_PI * i/180.0;
             sp = sin(pi);
             double w = 25.0 - 2.0*(abs(i)%10); //szerokosc kreski
             glVertex2f(a*sp*sr-w*cr, -a*sp*cr-w*sr);
             glVertex2f(a*sp*sr+w*cr, -a*sp*cr+w*sr);
     }
     glEnd();
     
     glDisable(GL_COLOR_MATERIAL);
     glMatrixMode(GL_PROJECTION);
     glPopMatrix();
     glMatrixMode(GL_MODELVIEW);
     glPopMatrix();
}

//wyswietla panel informacji
void Lander::draw_info()
{
     //ustaw widok orto
     glMatrixMode(GL_PROJECTION);
     glPushMatrix();
     glLoadIdentity();
     glOrtho(0.0, screenw, 0.0, screenh, -10.0, 10.0);
    
     glMatrixMode(GL_MODELVIEW);
     glPushMatrix();
     glLoadIdentity();
    
     glEnable(GL_COLOR_MATERIAL);
     
     double fuel = bar_h * get_main_fuel(); //wysokosci slupkow paliwa i ciagu
     double rcs = bar_h * get_rcs_fuel();
     double u_thr = bar_h * (w_main + w_space);
     if(u_thr > bar_h) u_thr = bar_h;
     double thr = bar_h * get_thrust();
     
     //makra pomocnicze
     //#define X
     //#define Y
     //#define W
     //#define H
     
     glBegin(GL_QUADS);
        //tlo huda
        glColor4f(info_color[0], info_color[1], info_color[2], info_color[3]);
        
        //tlo wskaznikow
        #define X gui_iwin_x
        #define Y gui_iwin_y
        #define W gui_iwin_w
        #define H gui_iwin_h
        glVertex2f(X, Y+H);
        glVertex2f(X+W, Y+H);
        glVertex2f(X+W, Y);
        glVertex2f(X, Y);
        
        //tlo informacji o czasie i fps
        #define X gui_twin_x
        #define Y gui_twin_y
        #define W gui_twin_w
        #define H gui_twin_h
        glVertex2f(X, Y+H);
        glVertex2f(X+W, Y+H);
        glVertex2f(X+W, Y);
        glVertex2f(X, Y);
        
        //tlo panelu parametrow
        #define X gui_pwin_x
        #define Y gui_pwin_y
        #define W gui_pwin_w
        #define H gui_pwin_h
        glVertex2f(X, Y+H);
        glVertex2f(X+W, Y+H);
        glVertex2f(X+W, Y);
        glVertex2f(X, Y);
        
        //tlo panelu wiadomosci
        #define X gui_mwin_x
        #define Y gui_mwin_y
        #define W gui_mwin_w
        #define H gui_mwin_h
        glVertex2f(X, Y+H);
        glVertex2f(X+W, Y+H);
        glVertex2f(X+W, Y);
        glVertex2f(X, Y);
        
        //pasek paliwa dps
        #define X (gui_iwin_x + 10)
        #define Y (gui_iwin_y + 110)
        glColor4f(dps_fuel_color[0], dps_fuel_color[1], dps_fuel_color[2], dps_fuel_color[3]);
        glVertex2f(X, Y+fuel);
        glVertex2f(X+bar_w, Y+fuel);
        glVertex2f(X+bar_w, Y);
        glVertex2f(X, Y);
        glColor4f(bar_color[0], bar_color[1], bar_color[2], bar_color[3]); //tlo slupka
        glVertex2f(X, Y+bar_h);
        glVertex2f(X+bar_w, Y+bar_h);
        glVertex2f(X+bar_w, Y);
        glVertex2f(X, Y);

        //pasek paliwa rcs    
        #define X (gui_iwin_x + 50)
        #define Y (gui_iwin_y + 110)
        glColor4f(rcs_fuel_color[0], rcs_fuel_color[1], rcs_fuel_color[2], rcs_fuel_color[3]);
        glVertex2f(X, Y+rcs);
        glVertex2f(X+bar_w, Y+rcs);
        glVertex2f(X+bar_w, Y);
        glVertex2f(X, Y);
        glColor4f(bar_color[0], bar_color[1], bar_color[2], bar_color[3]); //tlo slupka
        glVertex2f(X, Y+bar_h);
        glVertex2f(X+bar_w, Y+bar_h);
        glVertex2f(X+bar_w, Y);
        glVertex2f(X, Y);
    
        //pasek ciagu silnika glownego
        #define X (gui_iwin_x + 90)
        #define Y (gui_iwin_y + 110)
        glColor4f(thr_color[0], thr_color[1], thr_color[2], thr_color[3]);
        glVertex2f(X, Y+thr);
        glVertex2f(X+bar_w, Y+thr);
        glVertex2f(X+bar_w, Y);
        glVertex2f(X, Y);
        glColor4f(bar_color[0], bar_color[1], bar_color[2], bar_color[3]); //tlo slupka
        glVertex2f(X, Y+bar_h);
        glVertex2f(X+bar_w, Y+bar_h);
        glVertex2f(X+bar_w, Y);
        glVertex2f(X, Y);
    glEnd();
    
    //narysuj wskaznik ciagu (trojkat)
    glBegin(GL_TRIANGLES);
       #define X (gui_iwin_x + 90)
       #define Y (gui_iwin_y + u_thr + 110)
       glColor4f(text_color[0], text_color[1], text_color[2], text_color[3]);
       glVertex2f(X-5, Y+5);
       glVertex2f(X+5, Y);
       glVertex2f(X-5, Y-5);
    glEnd();
    
    //narysuj wskaznik parametru
    glBegin(GL_TRIANGLES);
       #define X (gui_pwin_x + 60)
       #define Y (gui_pwin_y + 15 + 15*sim_p)
       glColor4f(text_color[0], text_color[1], text_color[2], text_color[3]);
       glVertex2f(X, Y+5);
       glVertex2f(X, Y-5);
       glVertex2f(X+10, Y);
    glEnd();
    
    //wyswietl stan przelacznikow
    #define X (gui_pwin_x + 10)
    #define Y(L) (gui_pwin_y + 10 + 15*L)
    glBegin(GL_QUADS);
       for(int i = 0; i < sim_n_param; ++i) {
               if(sim_out.flags & (SIM_M_0<<i))
                  glColor4f(thr_color[0], thr_color[1], thr_color[2], thr_color[3]);
               else
                  glColor4f(bar_color[0], bar_color[1], bar_color[2], bar_color[3]);
                  
               glVertex2f(X, Y(i)+10);
               glVertex2f(X+10, Y(i)+10);
               glVertex2f(X+10, Y(i));
               glVertex2f(X, Y(i));
       }
    glEnd();
    
    //podpisz slupki
    glColor4f(text_color[0], text_color[1], text_color[2], text_color[3]);
    #define X (gui_iwin_x)
    #define Y (gui_iwin_y + 110)
    glutPrint(X+10, Y, text_scale, text_font, "DPS");
    glutPrint(X+50, Y, text_scale, text_font, "RCS");
    glutPrint(X+90, Y, text_scale, text_font, "THR");
    
    //wyswietl dane
    std::string text; //zmienne pomocnicze
    std::stringstream aux;
    aux.precision(1);
    aux.setf(std::ios::fixed, std::ios::floatfield);
    aux.setf(std::ios::right);
    
    #define X (gui_twin_x + 10)
    #define Y (gui_twin_y + 4)
    
    //czas symulacji i fps
    aux << "T:" << std::setw(8) << t << " FPS: " << std::setw(5) << fps;
    getline(aux, text); glutPrint(X, Y, text_scale, text_font, text);
    aux.clear(); text.clear();
    
    //pokaz informacje
    #define X (gui_iwin_x + 10)
    #define Y(L) (gui_iwin_y + 85 - 15*L)
    
    //pokaz pozycje landownika
    aux << "X: " << std::setw(6) << pos.x << " Y: " << std::setw(6) << pos.y << " Z: " << std::setw(6) << pos.z << " H: " << std::setw(6) << h;
    getline(aux, text);
    glutPrint(X, Y(0), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    //pokaz predkosc ladownika
    //wyliczamy predkosc w poziomie, pionie i absolutna
    double vertical_speed = dpos.z;
    double horizontal_speed = sqrt(dpos.x * dpos.x + dpos.y * dpos.y);
    double speed = sqrt(vertical_speed * vertical_speed + horizontal_speed * horizontal_speed);
    
    aux << "V[m/s]: " << std::setw(6) << speed << " VV: " << std::setw(6) << vertical_speed << " VH: " << std::setw(6) << horizontal_speed;
    getline(aux, text);
    glutPrint(X, Y(1), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    //pokaz katy ladownika
    aux << "PITCH: " << std::setw(5) << fi_euler.x << " YAW: " << std::setw(5) << fi_euler.y << " ROLL: " << std::setw(5) << fi_euler.z;
    getline(aux, text);
    glutPrint(X, Y(2), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    //predkosc katowa
    aux << "DP: " << std::setw(5) << dfi_euler.x << " DY: " << std::setw(5) << dfi_euler.y << " DR: " << std::setw(5) << dfi_euler.z;
    getline(aux, text);
    getline(aux, text);
    glutPrint(X, Y(3), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    //ryb rcs
    aux << "Tryb RCS: " << (steering == ROT ? "rotacja" : "translacja");
    getline(aux, text);
    glutPrint(X, Y(4), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    //ryb sterowania WSAD
    aux << "WSAD: " << (WSAD_flag ? "kamera" : "ladownik");
    getline(aux, text);
    glutPrint(X, Y(5), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    //pokaz parametry
    #define X (gui_pwin_x + 30)
    #define Y(L) (gui_pwin_y + 10 + 15*L)
    
    aux << "<F1       P1: " << std::setw(8) << sim_out.param[0];
    getline(aux, text);
    glutPrint(X, Y(0), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    aux << "<F2       P2: " << std::setw(8) << sim_out.param[1];
    getline(aux, text);
    glutPrint(X, Y(1), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    aux << "<F3       P3: " << std::setw(8) << sim_out.param[2];
    getline(aux, text);
    glutPrint(X, Y(2), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    aux << "<F4       P4: " << std::setw(8) << sim_out.param[3];
    getline(aux, text);
    glutPrint(X, Y(3), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    aux << "<F5       P5: " << std::setw(8) << sim_out.param[4];
    getline(aux, text);
    glutPrint(X, Y(4), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    aux << "<F6       P6: " << std::setw(8) << sim_out.param[5];
    getline(aux, text);
    glutPrint(X, Y(5), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    aux << "<F7       P7: " << std::setw(8) << sim_out.param[6];
    getline(aux, text);
    glutPrint(X, Y(6), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    aux << "<F8       P8: " << std::setw(8) << sim_out.param[7];
    getline(aux, text);
    glutPrint(X, Y(7), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    aux << "Tryb edycji: " << (sim_p_mode ? "LOG" : "INC");
    getline(aux, text);
    glutPrint(X, Y(8), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    aux << "Simulink: " << sim_host << (simulink_online ? " ONLINE" : " OFFLINE");
    getline(aux, text);
    glutPrint(X, Y(9), text_scale, text_font, text);
    aux.clear(); text.clear();
     
    aux << "PARAMETRY DLA SIMULINKA";
    getline(aux, text);
    glutPrint(X, Y(10), text_scale, text_font, text);
    aux.clear(); text.clear();
    
    //pauza, i czy ladownik rozbity
    if(!is_alive() || pause_flag) {
        glColor4f(msg_color[0], msg_color[1], msg_color[2], msg_color[3]);
        aux << (pause_flag ? " PAUSED" : "CRASHED");
        getline(aux, text);
        glutPrint(360, 294, text_scale, text_big_font, text);
        aux.clear(); text.clear();
    }
    
    //wyswietl wiadomosci
    display_messages();
    
    #undef X
    #undef Y
    #undef W
    #undef H
    
    glDisable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
