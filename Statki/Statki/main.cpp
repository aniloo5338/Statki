#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <fstream>
#include "Plansza.h"
#include "Gracz.h"
#include "Komputer.h"

using namespace std;

void wypisz_dwie_plansze(Gracz p_g, Komputer p_k) {
	system("cls");
	p_g.wypisz_plansze();
	p_k.wypisz_plansze();
}

void ruch_kompa(Gracz &p_g, Komputer &p_k) {
	cout << "\nTeraz ruch wykonuje komputer." << endl;
	while (p_g.strzel_komp()) {
		wypisz_dwie_plansze(p_g, p_k);
		if (p_k.get_licznik() == 20) {
			cout << "\nWygrywasz!";
			exit(0);
		}
		else if (p_g.get_licznik() == 20) {
			cout << "\nWygrywa komputer.";
			exit(0);
		}
	}
	Sleep(500);
	cout << "\nKoniec ruchu komputera." << endl;
	Sleep(1500);
}

bool ruch_gracza(Gracz &p_g, Komputer& p_k) {
	cout << "\nTwoj ruch.";
	while (p_k.wykonaj_ruch()) {
		wypisz_dwie_plansze(p_g, p_k);
		Sleep(500);
		if (p_k.get_licznik() == 20) {
			cout << "\nWygrywasz!";
			return false;
		}
		else if (p_g.get_licznik() == 20) {
			cout << "\nWygrywa komputer.";
			return false ;
		}
	}
	cout << "\nKoniec Twojego ruchu." << endl;
	Sleep(1500);
	return true;
}

int main() {
	srand ((unsigned int)time(NULL));
	// otworz plik do zapisu i do odczytu
	fstream plik;
	plik.open("zapis.txt", ios::in | ios::app);
	Gracz gracz;
	gracz.wpisz_nick();
	cout << "Czesc, " << gracz.get_nick() << "! Zagramy w statki?" << endl;
	// wybor - czy wczytac ostatnie wyniki
	cout << "Czy chcesz zobaczyc wynik ostatnich rozgrywek?" << endl;
	cout << "Tak - wybierz 1." << endl;
	cout << "Nie - wybierz inna liczbe." << endl;
	cout << "Twoj wybor: ";
	int wybor = 0;
	while (scanf_s("%d", &wybor) != 1 || getchar() != '\n') {
		cout << "Bledne dane. Podaj jeszcze raz: ";
		while (getchar() != '\n') ; 
	}
	if (wybor == 1) {
		if (plik.eof() || plik.is_open()) { // plik jest pusty
			cout << "\nPlik jest pusty.";
		}
		else { // plik nie jest pusty
			char linie[100];
			while (plik.getline(linie, 100)) {
				cout << linie << endl;
			}
			system("pause");
		}
	}
	Gracz p_gracz;
	p_gracz.wypisz_plansze();
	// ustaw statki
	cout << "\nUstaw swoje statki na planszy." << endl;
	cout << "Do ustawienia sa: 1 czteromasztowiec, 2 trzymasztowce, 3 dwumasztowce, 4 jednomasztowce" << endl;
	p_gracz.ustaw_statki();
	Komputer p_komp;
	p_komp.losuj_statki();
	p_gracz.wypisz_plansze();
	p_komp.wypisz_plansze();

	while (p_gracz.get_licznik() != 20 || p_komp.get_licznik() != 20) {
		// wypisanie dwoch plansz
		wypisz_dwie_plansze(p_gracz, p_komp);
		// gracz strzela w plansze komputera
		if (!ruch_gracza(p_gracz, p_komp)) break;
		// koniec ruchu gracza
		wypisz_dwie_plansze(p_gracz, p_komp);
		// komputer strzela w plansze gracza (losowo)
		ruch_kompa(p_gracz, p_komp);
		// koniec ruchu komputera
		wypisz_dwie_plansze(p_gracz, p_komp);
	}
	// sprawdzenie, czy ktoras ze stron juz wygrala
	if (p_komp.get_licznik() == 20 ) plik << "Rozgrywke wygral gracz " << gracz.get_nick() << ".\n";
	else if (p_gracz.get_licznik() == 20) plik << "Rozgrywke z graczem " << gracz.get_nick() << " wygral komputer.\n";
	plik.close();
	return 0;
}
