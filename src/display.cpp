#include "display.h"

//makra pomocnicze
#define X lander.pos.x
#define Y lander.pos.y
#define Z lander.pos.z

/*---------------------------------------------------------------
         PARAMETRY OKNA I KAMERY
---------------------------------------------------------------*/
//parametry kamery
Vector c_pos(-camera_initial_distance, 0.0, camera_initial_height); // poczatkowa pozycja kamery

double camera_pitch =  camera_initial_pitch ; //poczatkowe nachylenie kamery
double camera_yaw = camera_initial_yaw;

//tryb kamery
bool camera_mode = true; //0 - fpp, 1 - tpp

/*---------------------------------------------------------------
         ZMIENNE
---------------------------------------------------------------*/
//modele
Model stack_model; //caly ladownik
Model aps_model; //czlon aps
Model dps_model; //czlon dps

unsigned long frames = 0; //ilosc klatek w sumie
double fps; //ilosc klatek na sekunde

//czy pokazac wektory sil itp.
bool show_vectors = false;

//okno kamery dodatkowej
bool show_aux_cam = true;

//sciezka ruchu ladownika na ekranie
bool mark_path = false; //czy rysowac
double last_path = -1.0; //czas ostatniego dodania segmentu

/*---------------------------------------------------------------
         FUNKCJE
---------------------------------------------------------------*/
//wypisuje tekst na ekran
void glutPrint(double x0, double y0, double scale, void *font, std::string text)
{
    std::string::iterator i;
    
    double x = x0, y = y0;
    for(i = text.begin(); i != text.end(); ++i)
    {
        glRasterPos2f(x, y);
        glutBitmapCharacter(font, *i);
        x +=  glutBitmapWidth(font, *i);
    }
}

//resetuje kamere
void reset_camera()
{
     c_pos = Vector(-camera_initial_distance, 0.0, camera_initial_height);
     camera_pitch =  camera_initial_pitch ;
     camera_yaw = camera_initial_yaw;
}

//glowna funkcja wyswietlania 
void display()
{
    //wybierz viewport
    glViewport(0, 0, screenw, screenh);
    
    //wyczysc z bufor, projekcje i ekran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //ustaw kamere
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(camera_mode) { //tpp
                    gluLookAt(  X + c_pos.x, Y + c_pos.y, Z + c_pos.z, X, Y, Z, 0, 0, 1); // patrz Z NA
                    glTranslatef(X, Y, Z); // idz do ladownika
                    glRotatef(camera_pitch, 0.0, 1.0, 0.0); // i obroc kamere wokol tego punktu
                    glRotatef(camera_yaw, 0.0, 0.0, 1.0);
                    glTranslatef(-X, -Y, -Z); // wroc do zera
    } else { //fpp
                    gluLookAt(  X, Y, Z, X + 1.0, Y, Z, 0, 0, 1);
                    glTranslatef(X, Y, Z); // idz do ladownika
                    //glRotatef(camera_pitch, 0.0, 1.0, 0.0);
                    Matrix m;
                    lander.fi.get_conjugate().to_matrix(m);
                    glMultMatrixf(m);
                    glTranslatef(-X, -Y, -Z); // wroc do zera
    }
    
    //ustaw swiatlo
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_COLOR_MATERIAL);
    glColor4f(1.0, 1.0, 0.0, 0.75);
    glPointSize(100.0);
    glBegin(GL_POINTS);
    glVertex3f(light_position[0], light_position[1], light_position[2]);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    
    //wyswietl powierzchnie
    moon.display();
    
    //wyswietl ladownik
    if(camera_mode) lander.display();
    
    if(show_vectors) {
                     if(camera_mode) lander.draw_vectors();
                     else lander.draw_vectors_fpp();

                     //wyswietl slad na ziemi
                     lander.draw_shadow();
    }
    
    //jezeli zaznaczac sciezke
    if(mark_path && camera_mode) lander.draw_path();
    
    //pokaz informacje w panelu
    lander.draw_info();
    
    //pokaz hud
    if(!camera_mode) lander.draw_hud();
    
    //pokaz okno kamery dodatkowej
    if(show_aux_cam) lander.display_cam();
    
    // zakoncz rysowanie i wyrzuc wszystko na ekran
    glFlush();
    glutSwapBuffers();
    
    ++frames; //zwieksz ilosc klatek
}

//wyswietla obraz z kamery dodatkowej
void Lander::display_cam()
{
     //wybierz viewport
     glViewport(0, 0, screenw, screenh);
     
     //modyfikuj tylko fragment ekranu
     glEnable(GL_SCISSOR_TEST);
     glScissor(gui_cwin_x, gui_cwin_y, gui_cwin_w, gui_cwin_h);
     
     //wybierz viewport
     glViewport(gui_cwin_x+1, gui_cwin_y+1, gui_cwin_w-2, gui_cwin_h-2);
    
     //wyczysc z bufor, projekcje i ekran
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
     //ustaw kamere
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     
     gluLookAt(pos.x, pos.y, pos.z, pos.x, pos.y, pos.z - 1.0 , 1, 0, 0);
     glTranslatef(pos.x, pos.y, pos.z); // idz do ladownika
     //glRotatef(camera_pitch, 0.0, 1.0, 0.0);
     Matrix m;
     fi.get_conjugate().to_matrix(m);
     glMultMatrixf(m);
     glTranslatef(-pos.x, -pos.y, -pos.z); // wroc do zera
     
     //ustaw swiatlo
     glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
     //wyswietl powierzchnie
     moon.display();
     
     if(show_vectors) draw_shadow();
     
     glDisable(GL_SCISSOR_TEST);
}

//wyswietla sciezke ladownika
void Lander::draw_path()
{
     glEnable(GL_COLOR_MATERIAL);
     glColor4f(0.0, 1.0, 0.0, 1.0);
     
     glBegin(GL_LINES);
     std::vector<Vector>::iterator i;
     for(i = path.begin(); i < path.end(); ++i) {
           if(i != path.begin()) glVertex3f((i-1)->x, (i-1)->y, (i-1)->z);
                else glVertex3f(i->x, i->y, i->z);
           glVertex3f(i->x, i->y, i->z);
           }
     if(path.size() > 1) {
                    glVertex3f(path.back().x, path.back().y, path.back().z);
                    glVertex3f(X, Y, Z);
     }
     glEnd();
     
     glDisable(GL_COLOR_MATERIAL);
}

//wyswietla slad na ziemi
void Lander::draw_shadow()
{
     glEnable(GL_COLOR_MATERIAL);
     glColor4f(1.0, 0.0, 0.0, 1.0);
     
     glBegin(GL_LINE_LOOP);
        glVertex3f(X + 5.0, Y + 0.0, moon.get_height(X + 5.0, Y + 0.0));
        glVertex3f(X - 2.5, Y - 4.33, moon.get_height(X - 2.5, Y - 4.33));
        glVertex3f(X -2.5, Y + 4.33, moon.get_height(X -2.5, Y + 4.33));
     glEnd();
     
     glDisable(GL_COLOR_MATERIAL);
}

//wyswietla wektory predkosci itp.
void Lander::draw_vectors()
{
     glEnable(GL_COLOR_MATERIAL);
      
     //wyswietl kierunki wektorow predkosci i ciagu
     glBegin(GL_LINES);
        //wektor predkosci
        glColor4f(1.0, 1.0, 0.0, 1.0);
        glVertex3f(X, Y, Z);
        glVertex3f(X + lander.dpos.x, Y + lander.dpos.y, Z + lander.dpos.z);
        
        //wektor przyspieszenia
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex3f(X, lander.pos.y, lander.pos.z);
        glVertex3f(X + lander.d2pos.x, Y + lander.d2pos.y, Z + lander.d2pos.z);
     glEnd();
     
     glDisable(GL_COLOR_MATERIAL);
}

//wyswietla wektory predkosci itp. w trybie fpp
void Lander::draw_vectors_fpp()
{
     //kierunek wektora ciagu w trybie fpp
     Vector pg = lander.dpos;
     pg.normalise();
     pg = pg * 5.0;
     
     glEnable(GL_COLOR_MATERIAL);
     glColor4f(hud_color[0], hud_color[1], hud_color[2], hud_color[3]);
     
     glBegin(GL_POINTS);
        glVertex3f(X + pg.x, Y + pg.y, Z + pg.z);
     glEnd();
     
     glDisable(GL_COLOR_MATERIAL);
}
