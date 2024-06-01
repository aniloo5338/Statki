#pragma once

#include <iostream>
#include <string>

using namespace std;

class Gracz {
	string nick;
	int wynik;
public:
	int get_wynik() { return wynik; }
	void set_nick() { if (nick == "\n") nick = "anonim"; }
	string wpisz_nick();
};
