#include <iostream>
#include <Windows.h>
#include "Gracz.h"
#include "Plansza.h"

using namespace std;

Gracz::Gracz() : Plansza(), nick("Hello") { }
string Gracz::wpisz_nick(){
	cout << "\nPodaj nick: ";
	cin >> nick;
	return nick;
}

// metoda wypisuje plansze ze statkami gracza i naglowek
void Gracz::wypisz_plansze() {
	cout << "\n       Twoja plansza:     " << endl;
	Plansza::wypisz_plansze_ok();
}

// komputer strzela losowa w plansze gracza
bool Gracz::strzel_komp() {
	Sleep(1000);
	char los_litera = (char)((rand() % 10) + 65); // komputer losuje wspolrzedna literowa
	int los_liczba = (rand() % 10) + 1; // komputer losuje wspolrzedna liczbowa
	return Plansza::strzel_w_gracza(los_litera, los_liczba, licznik_zat_pol);

}
