#pragma once

#include "Plansza.h";

using namespace std;

class Komputer : public Plansza {
public:
	Komputer();
	void losuj_statki();
	void wypisz_plansze();
	void wypisz_plansze_strzel();
	void wykonaj_ruch_wypis();
};