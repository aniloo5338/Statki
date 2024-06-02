#include <iostream>
#include <string>
#include "Komputer.h"
#include "Plansza.h"

using namespace std;

Komputer::Komputer() : Plansza() {}

template <typename T>
bool zakres(T zmienna, T min, T max) {
	if (zmienna<min || zmienna>max) {
		return true;
	}
	return false;
}

/// <summary>
/// komputer losuje ustawienie 10 statkow
/// </summary>
void Komputer::losuj_statki() {
	int liczba_statkow = 1;
	for (int i = 3; i >= 0; --i) {
		for (int j = i; j < 4; ++j) {
			int orient_w = rand() % 2;
			char x_w = (char)((rand() % 10) + 65);
			int y_w = (rand() % 10) + 1;
			if (!wypelnij_statkiem(i + 1, orient_w, x_w, y_w)) --j;
			
			system("cls");
		}
	}
}

// metoda wypisuje pusta plansze komputera, na ktorej widac tylko oddane strzaly i trafione statki
void Komputer:: wypisz_plansze() {
	cout << "     Plansza Komputera:    " << endl;
	Komputer::wypisz_plansze_strzel();
}

void Komputer::wypisz_plansze_strzel() {
	cout << "     A B C D E F G H I J  " << endl;
	cout << "     ";
	for (int k = 0; k < 10; ++k) { cout << "_ "; }
	cout << "\n";
	for (int i = 1; i < 11; ++i) {
		cout.width(2);
		cout << i << "  ";
		for (int j = 1; j < 11; ++j) {
			cout << "|";
			switch (tab_do_strzelania[i][j]) {
			case 0:
				cout << "_";
				break;
			case 1:
				cout << "O";
				break;
			case 2:
				cout << "X";
				break;
			case 3:
				cout << "*";
				break;
			default:
				cout << "_";
				break;
			}
		}
		cout << "|\n";
	}
}

bool czyBlednaLitera(char& wczyt_litera){
	//char wczyt_litera;
	return (scanf_s("%c", &wczyt_litera) != 1 || zakres(wczyt_litera, 'A', 'J') || getchar() != '\n');
}

bool czyBlednaLiczba(int& wczyt_liczba) {
	//int wczyt_liczba;
	return (scanf_s("%d", &wczyt_liczba) != 1 || zakres(wczyt_liczba, 1, 10) || getchar() != '\n');
}

// wykonaj ruch z wypisem planszy
void Komputer::wykonaj_ruch_wypis() {
	char wczyt_litera;
	int wczyt_liczba;
	bool czy_trafiony = true;
	do {
		cout << "\nPodaj dwie wspolrzedne, po kazdej enter (A-J, 1-10)" << endl;
		while (czyBlednaLitera(wczyt_litera)) {
			cout << "Bledne dane. Podaj jeszcze raz: ";
			while (getchar() != '\n');
		}
		while (czyBlednaLiczba(wczyt_liczba)) {
			cout << "Bledne dane. Podaj jeszcze raz: ";
			while (getchar() != '\n');
		}
		czy_trafiony = strzel(wczyt_litera, wczyt_liczba, licznik_zat_pol);
		cout << "\nTrafionych: " << licznik_zat_pol;
		system("cls");
		Komputer::wypisz_plansze_strzel();
	} while (czy_trafiony);
}
