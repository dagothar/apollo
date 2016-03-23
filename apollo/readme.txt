


           _/_/_/                      _/   _/
         _/    _/                     _/   _/
        _/    _/   _/_/_/   _/_/_/   _/   _/   _/_/_/
       _/_/_/_/   _/  _/   _/  _/   _/   _/   _/  _/ 
      _/    _/   _/  _/   _/  _/   _/   _/   _/  _/  
     _/    _/   _/_/_/   _/_/_/   _/   _/   _/_/_/   
               _/                                    
              _/                                     
             _/       Adam Wolniakowski 2011     
                                            
    --------------------------------------------------

1. Linia komend

	apollo.exe [-h host] [-m mapfile] [-mk 0.0] [-me 0.0] [-g 0.0] [-b 0.0]



	-h host		Adres IP komputera, na kt�rym uruchomiony jest wsp�pracuj�cy model Simulinka.
			Domy�lnie localhost.

	-m		Nazwa pliku zawierajacego mape wysokosci powierzchni.

	-mk 		Generator mapy; parametr opisujacy maksymalne poczatkowe zmiany wysokosci.

	-me		Generator mapy; parametr opisujacy redukcje zmian wysokosci w kolejnych krokach.

	-g		Stala grawitacji [m/s^2].

	-b		Opor atmosferyczny [Ns/m].



2. Sterowanie

 
G��wne

 [esc]		Zako�cz program	   
 p		W��cz/wy��cz pauz�	   
 m		Wygeneruj now� map�
 n		W��cz/wy��cz d�wi�k
 [tab]		Sterowanie WSAD: kamera/l�downik	
   


Kamera

 w		Kamera w g�r�	   
 s		Kamera w d�	   
 a		Kamera w lewo	   
 d		Kamera w prawo	   
 z		Przybli� kamer�	   
 x		Oddal kamer�	   
 c		Ustaw kamer� w po�o�eniu pocz�tkowym
 f		W��cz tryb pierwszej osoby



Wy�wietlanie	
   
 v		Poka� wektory orientacji, pr�dko�ci i przyspieszenia oraz �lad na powierzchni	   
 b		Poka� trajektori� ruchu	   



Sterowanie l�downikiem	   

 g		Umie�� l�downik w po�o�eniu pocz�tkowym na wysoko�ci 0.0	   
 o		Umie�� l�downik w po�o�eniu pocz�tkowym na wysoko�ci 1000.0
 j		Umie�� l�downik w po�o�eniu losowym na wysoko�ci 1500.0
[spacja]	Silnik g��wny: 100% (chwilowo)	   
 *		Silnik g��wny: 100%	   
 /		Silnik g��wny: 0%	   
 +, =		Silnik g��wny: +5%	   
 -		Silnik g��wny: -5%	   
 ','		Zmie� tryb RCS: rotacja/translacja	   
 8/w		Pochyl l�downik do przodu	Przesu� l�downik do przodu	   
 2/s		Pochyl l�downik do ty�u		Przesu� l�downik do ty�u	   
 4/a		Przechyl l�downik w lewo	Przesu� l�downik w lewo	   
 6/d		Przechyl l�downik w prawo	Przesu� l�downik w prawo	   
 1/q		Odchyl l�downik w lewo		Przesu� l�downik do do�u	   
 3/e		Odchyl l�downik w prawo		Przesu� l�downik do g�ry	   
 5		W��cz/wy��cz killrot	   
 u		W��cz/wy��cz zrzut paliwa silnika g��wnego	 


  
Wsp�praca z Simulinkiem
	   
 r		Wy�lij sygna� 'reset' do Simulinka	   
   
 F1		W��cz prze��cznik 1. (monostabilny)	   
 F2		W��cz prze��cznik 2. (monostabilny)	   
 F3		W��cz prze��cznik 3. (monostabilny)	   
 F4		W��cz prze��cznik 4. (monostabilny)	   
 F5		W��cz/wy��cz prze��cznik 5. (bistabilny)	   
 F6		W��cz/wy��cz prze��cznik 6. (bistabilny)	   
 F7		W��cz/wy��cz prze��cznik 7. (bistabilny)	   
 F8		W��cz/wy��cz prze��cznik 8. (bistabilny)	
   
 [g�ra], [d�]	Wybierz parametr do edycji	   
 [Insert]	Zmie� tryb edycji parametr�w: inkrementalny/logarytmiczny	   
 [lewo], [prawo]Zmniejsz/zwi�ksz parametr o 1.0 / razy 1.1	   
 +CTRL		Zmniejsz/zwi�ksz parametr o 0.1	   
 +SHIFT		Zmniejsz/zwi�ksz parametr o 10.0	   
 [Home]		Ustaw parmetr na 0.0	 
