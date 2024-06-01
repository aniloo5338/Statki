#pragma once
#include <string>

using namespace std;

class Plansza {
public:
	Plansza();
	void wypisz_plansze_ok();
	bool wypelnij_statkiem(int dl, int orient, char x, int y);
	void ustaw_statki();
	bool czy_puste_poz(int dl, char x, int y);
	bool czy_puste_pion(int dl, char x, int y);
	bool strzel(char x, int y, int &wsk);
	bool wykonaj_ruch();
	bool strzel_w_gracza(char x, int y, int& wsk);
	int get_licznik() { return licznik_zat_pol; }
	virtual void wypisz_plansze() = 0;
protected:
	int tab[12][12];
	int tab_do_strzelania[12][12];
	int licznik_zat_pol;
};

/*
0 - "_", puste pole
1 - "O", statek postawiony
2 - "X", statek trafiony
3 - ".", "pudlo"
9 - "_", puste pole, nie moga tu stanac inne statki
*/
