


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



	-h host		Adres IP komputera, na którym uruchomiony jest wspó³pracuj¹cy model Simulinka.
			Domyœlnie localhost.

	-m		Nazwa pliku zawierajacego mape wysokosci powierzchni.

	-mk 		Generator mapy; parametr opisujacy maksymalne poczatkowe zmiany wysokosci.

	-me		Generator mapy; parametr opisujacy redukcje zmian wysokosci w kolejnych krokach.

	-g		Stala grawitacji [m/s^2].

	-b		Opor atmosferyczny [Ns/m].



2. Sterowanie

 
G³ówne

 [esc]		Zakoñcz program	   
 p		W³¹cz/wy³¹cz pauzê	   
 m		Wygeneruj now¹ mapê
 n		W³¹cz/wy³¹cz d¿wiêk
 [tab]		Sterowanie WSAD: kamera/l¹downik	
   


Kamera

 w		Kamera w górê	   
 s		Kamera w dó³	   
 a		Kamera w lewo	   
 d		Kamera w prawo	   
 z		Przybli¿ kamerê	   
 x		Oddal kamerê	   
 c		Ustaw kamerê w po³o¿eniu pocz¹tkowym
 f		W³¹cz tryb pierwszej osoby



Wyœwietlanie	
   
 v		Poka¿ wektory orientacji, prêdkoœci i przyspieszenia oraz œlad na powierzchni	   
 b		Poka¿ trajektoriê ruchu	   



Sterowanie l¹downikiem	   

 g		Umieœæ l¹downik w po³o¿eniu pocz¹tkowym na wysokoœci 0.0	   
 o		Umieœæ l¹downik w po³o¿eniu pocz¹tkowym na wysokoœci 1000.0
 j		Umieœæ l¹downik w po³o¿eniu losowym na wysokoœci 1500.0
[spacja]	Silnik g³ówny: 100% (chwilowo)	   
 *		Silnik g³ówny: 100%	   
 /		Silnik g³ówny: 0%	   
 +, =		Silnik g³ówny: +5%	   
 -		Silnik g³ówny: -5%	   
 ','		Zmieñ tryb RCS: rotacja/translacja	   
 8/w		Pochyl l¹downik do przodu	Przesuñ l¹downik do przodu	   
 2/s		Pochyl l¹downik do ty³u		Przesuñ l¹downik do ty³u	   
 4/a		Przechyl l¹downik w lewo	Przesuñ l¹downik w lewo	   
 6/d		Przechyl l¹downik w prawo	Przesuñ l¹downik w prawo	   
 1/q		Odchyl l¹downik w lewo		Przesuñ l¹downik do do³u	   
 3/e		Odchyl l¹downik w prawo		Przesuñ l¹downik do góry	   
 5		W³¹cz/wy³¹cz killrot	   
 u		W³¹cz/wy³¹cz zrzut paliwa silnika g³ównego	 


  
Wspó³praca z Simulinkiem
	   
 r		Wyœlij sygna³ 'reset' do Simulinka	   
   
 F1		W³¹cz prze³¹cznik 1. (monostabilny)	   
 F2		W³¹cz prze³¹cznik 2. (monostabilny)	   
 F3		W³¹cz prze³¹cznik 3. (monostabilny)	   
 F4		W³¹cz prze³¹cznik 4. (monostabilny)	   
 F5		W³¹cz/wy³¹cz prze³¹cznik 5. (bistabilny)	   
 F6		W³¹cz/wy³¹cz prze³¹cznik 6. (bistabilny)	   
 F7		W³¹cz/wy³¹cz prze³¹cznik 7. (bistabilny)	   
 F8		W³¹cz/wy³¹cz prze³¹cznik 8. (bistabilny)	
   
 [góra], [dó³]	Wybierz parametr do edycji	   
 [Insert]	Zmieñ tryb edycji parametrów: inkrementalny/logarytmiczny	   
 [lewo], [prawo]Zmniejsz/zwiêksz parametr o 1.0 / razy 1.1	   
 +CTRL		Zmniejsz/zwiêksz parametr o 0.1	   
 +SHIFT		Zmniejsz/zwiêksz parametr o 10.0	   
 [Home]		Ustaw parmetr na 0.0	 
