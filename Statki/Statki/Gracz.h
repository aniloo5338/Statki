#pragma once

#include <iostream>
#include <string>
#include "Plansza.h"

using namespace std;

class Gracz: public Plansza {
	string nick;
public:
	Gracz();
	void wypisz_plansze();
	bool strzel_komp();
	// deklaracje get'erow
	string get_nick() { return nick; }
	string wpisz_nick();

};

