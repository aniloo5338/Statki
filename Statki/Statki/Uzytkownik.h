#pragma once

#include <iostream>
#include <string>

using namespace std;

class Gracz {
	string nick;
	int wynik;
public:
	// deklaracje get'erow
	//string get_nick() { return nick; }
	int get_wynik() { return wynik; }
	// deklaracje set'erow
	/////////////////////////////////nie dziala pusty nick "anonim"////////////////////////////////
	void set_nick() { if (nick == "\n") nick = "anonim"; }

	string wpisz_nick();
};