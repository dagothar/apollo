#include "map.h"

//mapa
Map moon;

//nazwa pliku z mapa
char *map_file = "data/map.dat";

//parametry generatora fraktalnego
double map_kh = 250.0; //maksymalna wysokosc poczatkowych odchylen
double map_eh = 0.55; //co ile zmniejszac odchylenie w kolejnym kroku

//tekstura Ksiezyca
GLuint texture_moon; //nieuzywane

Map::Map()
{
}

//szum
double Map::noise(double amp)
{
       return 0.01 * amp * (rand()%200 - 100);
}             
              
//szum Perlina 2d krok square
void Map::square(int x, int y, int step, double amp)
{
	if(step > 0) {
            //p. srodkowy
		    hmap[x][y] = 0.25*(hmap[x-step][y-step]+hmap[x-step][y+step]+hmap[x+step][y-step]+hmap[x+step][y+step]) + noise(amp);

		    diamond(x-step, y, step, amp);
		    diamond(x+step, y, step, amp);
		    diamond(x, y-step, step, amp);
		    diamond(x, y+step, step, amp);
	}
}

//szum Perlina 2d krok diamond
void Map::diamond(int x, int y, int step, double amp)
{
	if(step > 0) {
		double sum = 0;
		int n = 0;
		if(x > 0) sum += hmap[x-step][y], ++n;
		if(x < n_nodes) sum += hmap[x+step][y], ++n;
		if(y > 0) sum += hmap[x][y-step], ++n;
		if(y < n_nodes) sum += hmap[x][y+step], ++n;
		
		hmap[x][y] = sum / n + noise(amp);
		
		step = step >> 1;
		
		if(step > 0) {
			if(x >= step && y >= step) square(x-step, y-step, step, amp * map_eh);
			if(x >= step && y <= n_nodes-step) square(x-step, y+step, step, amp * map_eh);
			if(x <= n_nodes-step && y >= step) square(x+step, y-step, step, amp * map_eh);
			if(x <= n_nodes-step && y <= n_nodes-step) square(x+step, y+step, step, amp * map_eh);
		}
	}
}

//wygeneruj mape
void Map::generate()
{
     //losowe odksztalcenia
     /*for(int x = 0; x < n_nodes; ++x)
             for(int y = 0; y < n_nodes; ++y)
                     map_nodes[x][y] = 2.5 - 0.05*(rand()%100);
                     */
                     
     //funkcja(test)
     //for(int x = 0; x < n_nodes; ++x)
             //for(int y = 0; y < n_nodes; ++y)
                     //hmap[x][y] = 5.0*(y-n_nodes/2)+(x-n_nodes/2)*(y-n_nodes/2);
                     //hmap[x][y] = (y-n_nodes/2)*(x-n_nodes/2);
                     //hmap[x][y] = 0.1*(y-n_nodes/2)*(y-n_nodes/2)*(y-n_nodes/2);
                     
     //krance
     hmap[0][0] = noise(map_kh);
     hmap[0][n_nodes] = noise(map_kh);
     hmap[n_nodes][0] = noise(map_kh);
     hmap[n_nodes][n_nodes] = noise(map_kh);
     
     square(n_nodes/2, n_nodes/2, n_nodes/2, map_kh);
     
     prepare();
     
     save(map_file);
}

//wczytaj z pliku
void Map::load(const char *filename)
{
     std::ifstream file(filename);
     
     //jezeli nie ma pliku, stworz mape
     if(!file) {
               generate();
               return;
     }

     std::string s;
     std::stringstream sstr;
     for(int i = 0; i < n_nodes+1; ++i) {
             if(getline(file, s)) {
                              sstr << s;
                              for(int j = 0; j < n_nodes+1; ++j) {
                                      sstr >> hmap[i][j];
                              }
                              sstr.clear();
             }
     }
     
     prepare();
     
     file.close();
}

//zapisz do pliku
void Map::save(const char *filename)
{
     std::ofstream file(filename);
     
     for(int i = 0; i < n_nodes+1; ++i) {
             for(int j = 0; j < n_nodes+1; ++j) {
                     file << hmap[i][j] << ' ';  
             }
             file << '\n';
     }
     
     file.close();
}

//wyswietla mape
void Map::display()
{
     glEnable(GL_LIGHTING);
     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     
     glCallList(display_list);

     glDisable(GL_CULL_FACE);
     glDisable(GL_DEPTH_TEST);
     glDisable(GL_LIGHTING);
}

//przygotuj liste wyswietlania
void Map::prepare()
{
     display_list = glGenLists(1);
     glNewList(display_list, GL_COMPILE);
     
     //ustaw material powierzchni
     glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, moon_ambdiff);
     glMaterialfv(GL_FRONT, GL_SPECULAR, moon_specular);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_emiss);
     glMaterialfv(GL_FRONT, GL_SHININESS, &moon_shin);
     
     glBegin(GL_TRIANGLES);
     for(int i = 0; i < n_nodes-1; ++i) for(int j = 0; j < n_nodes-1; ++j) {
             Vector p1((i-0.5*n_nodes)*node_size, -(j-0.5*n_nodes)*node_size, hmap[i][j]);
             Vector p2((i-0.5*n_nodes)*node_size, -(j-0.5*n_nodes+1)*node_size, hmap[i][j+1]);
             Vector p3((i-0.5*n_nodes+1)*node_size, -(j-0.5*n_nodes+1)*node_size, hmap[i+1][j+1]);
             Vector p4((i-0.5*n_nodes+1)*node_size, -(j-0.5*n_nodes)*node_size, hmap[i+1][j]);
             
             Vector n1 = (p2-p1)*(p3-p1); n1.normalise();
             glNormal3fv(n1.to_vertex().x);
             glVertex3fv(p1.to_vertex().x); glVertex3fv(p2.to_vertex().x); glVertex3fv(p3.to_vertex().x);
             
             Vector n2 = (p3-p1)*(p4-p1); n2.normalise();
             glNormal3fv(n2.to_vertex().x);
             glVertex3fv(p1.to_vertex().x); glVertex3fv(p3.to_vertex().x); glVertex3fv(p4.to_vertex().x);
     }
     glEnd();
     
     glEndList();
}

//znajdz wysokosc w punkcie (x, y)
double Map::get_height(double x, double y)
{
       y *= -1.0;
       //jakie to koordynaty mapy?
       double i = x/node_size + 0.5*n_nodes;
       double j = y/node_size + 0.5*n_nodes;
       
       int u = floor(i);
       int v = floor(j);
       
       if(u < 0 || v < 0 || u > n_nodes || v > n_nodes) return 0.0;
       
       //pochodne wzdluz osi y u gory i u dolu kratki
       double dy1 = (hmap[u][v+1] - hmap[u][v]);
       double dy10 = hmap[u][v] + (j-v)*dy1;
       double dy2 = (hmap[u+1][v+1] - hmap[u+1][v]);
       double dy20 = hmap[u+1][v] + (j-v)*dy2;
       
       //pochodna wzdluz osi x
       double dx = (dy20 - dy10);
       double dx0 = dy10 + (i-u)*dx;
       
       return dx0;
}
