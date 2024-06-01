#include <cstdlib>
#include <iostream>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Plansza.h"

using namespace std;

Plansza::Plansza() : licznik_zat_pol(19) {
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			tab[i][j] = 0;
		}
	}
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			tab_do_strzelania[i][j] = 0;
		}
	}
}

template <typename T>
bool zakres(T zmienna, T min, T max) {
	return (zmienna<min || zmienna>max);
}

void Plansza::wypisz_plansze_ok() {
	cout << "     A B C D E F G H I J  " << endl;
	cout << "     ";
	for (int k = 0; k < 10; ++k) 
		cout << "_ ";
	
	cout << "\n";
	for (int i = 1; i < 11; ++i) {
		cout.width(2);
		cout << i << "  ";
		for (int j = 1; j < 11; ++j) {
			cout << "|";
			switch (tab[i][j]) {
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

// metoda zwraca false, gdy nie uda sie poprawnie rozstawic statkow
bool Plansza::wypelnij_statkiem(int dl, int orient, char x, int y) {
	// sprawdzenie zakresu tablicy: czy poczatek statku nie wychodzi poza kwadrat A1, A10, J10, J1
	if ((int)(x - 'A') + 1 < 1 || (int)(x - 'A') + 1 > 10 || y < 1 || y > 10) { return false; }
	if (orient == 0) { // statek poziomy
		// sprawdzenie zakresu tablicy (dl. statku + wspolrzedna literowa)
		if (dl + (int)(x - 'A') > 10 || !czy_puste_poz(dl, x, y)) { return false; }
		// uzupelnij dana komorke w tablicy liczba 1 (1 - "X", statek postawiony)
		for (int i = 0; i < dl; ++i) { // statek dlugosci dl
			int pom = (int)(x - 'A') + i;
			tab[y][pom + 1] = 1;
			tab[y - 1][pom + 1] = tab[y + 1][pom + 1] = 9;
		}
		// uzupelnij 3 kratki wzdluz lewej krawedzi liczba 9 (9 - "_", puste pole, nie moga tu stanac inne statki)
		tab[y - 1][(int)(x - 'A')] = tab[y][(int)(x - 'A')] = tab[y + 1][(int)(x - 'A')] = 9;
		// uzupelnij 3 kratki wzdluz prawej krawedzi liczba 9 (9 - "_", puste pole, nie moga tu stanac inne statki)
		tab[y - 1][(int)(x - 'A') + dl + 1] = tab[y][(int)(x - 'A') + dl +1] = tab[y + 1][(int)(x - 'A') + dl+1] = 9;
		return true;
	}
	else if (orient == 1) { // statek pionowy
		// sprawdzenie zakresu tablicy (dl. statku + wspolrzedna liczbowa)
		if (dl + y - 1 > 10 || !czy_puste_pion(dl, x, y)) { return false; }
		// uzupelnij dana komorke w tablicy liczba 1 (1 - "X", statek postawiony)
		for (int i = 0; i < dl; ++i) { // statek dlugosci dl
			int pom = (int)(x - 'A');
			tab[y + i][pom + 1] = 1;
			tab[y + i][pom] = tab[y + i][pom + 2] = 9;
		}
		tab[y - 1][(int)(x - 'A')] = tab[y - 1][(int)(x - 'A') + 1] = tab[y - 1][(int)(x - 'A') + 2] = 9;
		tab[y + dl][(int)(x - 'A')] = tab[y + dl][(int)(x - 'A') + 1] = tab[y + dl][(int)(x - 'A') + 2] = 9;
		return true;
	}
	else return false;
}

void Plansza::ustaw_statki() {
	//ustaw 10 statkow
	//petla zwieksza liczbe ustawianych statkow i zmniejsza iczbe ich masztow
	int liczba_statkow = 0;
	for (int i = 3; i >= 0; --i) {
		liczba_statkow++;
		for (int j = i; j < 4; ++j) {
		cout << liczba_statkow << " statki o liczbie masztow: " << i + 1 << endl;
			int orient_w;
			char x_w;
			int y_w;
			cout << "orientacje (0 - poziomy, 1 - pionowy) = " << endl;
			// kontrola poprawnosci danych
			while (scanf_s("%d", &orient_w) != 1 || zakres(orient_w, 0, 1) || getchar() != '\n') {
				cout << "Bledne dane. Podaj jeszcze raz: ";
				while (getchar() != '\n');
			}
			cout << "wspolrzedna literowa (od A do J) = " << endl;
			while (scanf_s("%c", &x_w) != 1 || zakres(x_w, 'A', 'J') || getchar() != '\n') {
				cout << "Bledne dane. Podaj jeszcze raz: ";
				while (getchar() != '\n');
			}
			cout << "wspolrzedna liczbowa (od 1 do 10) = " << endl;
			while (scanf_s("%d", &y_w) != 1 || zakres(y_w, 1, 10) || getchar() != '\n') {
				cout << "Bledne dane. Podaj jeszcze raz: ";
				while (getchar() != '\n');
			}
			if (!wypelnij_statkiem(i + 1, orient_w, x_w, y_w)) {
				cout << "Bledne dane. Podaj jeszcze raz: " << endl;
				system("pause");
				--j;
			}
			// wyczysc ekran
			system("cls");
			wypisz_plansze_ok();
		}
	}
}

// metoda zwraca false, gdy pole jest zajete, nie mozna postawic statku
bool Plansza::czy_puste_poz(int dl, char x, int y) {
	// statek poziomy
	for (int i = 0; i < dl; ++i) {
		int pom = (int)(x - 'A') + i;
		if (tab[y][pom + 1] == 1 || tab[y][pom + 1] == 9) {
			return false;
		}
	}
	return true;
}

// metoda zwraca false, gdy pole jest zajete, nie mozna postawic statku
bool Plansza::czy_puste_pion(int dl, char x, int y) {
	// statek pionowy
	for (int i = 0; i < dl; ++i) {
		int pom = (int)(x - 'A');
		if (tab[y + i][pom + 1] == 1 || tab[y + i][pom + 1] == 9) {
			return false;
		}
	}
	return true;
}

// strzel w te plansze. uwaga: gracz strzela na planszy p_komp
bool Plansza::strzel(char x, int y, int& wsk) {
	int pom = (int)(x - 'A');
	if ((int)(x - 'A') + 1 < 1 || (int)(x - 'A') + 1 > 10 || y < 1 || y > 10) {
		cout << "Bledne dane.";
		return false;
	}
	if (tab[y][pom + 1] == 1) {
		// aktualizacja tablicy do strzelania (2 - "X", statek trafiony) i tab zwyklej
		tab_do_strzelania[y][pom + 1] = tab[y][pom + 1] = 2;
		cout << "Trafiony!";
		// zmienne pomocnicze, sasiednie kratki od trafionej (prawo, lewo, gora, dol)
		int l = tab[y - 1][pom + 1];
		int p = tab[y + 1][pom + 1];
		int g = tab[y][pom];
		int d = tab[y][pom + 2];
		// trafiony zatopiony - zatopiony, gdy sasiednie kratki nie sa niezbitymi statkami
		if (l == 1 || p == 1 || g == 1 || d == 1) {
			;
		}
		else cout << " Zatopiony!";
		wsk++;
		Sleep(1500);
		return true;
	}
	else if (tab[y][pom + 1] == 2) {
		cout << "Pudlo!";
		Sleep(1500);
		return false;
	}
	else {
		// aktualizacja tablicy do strzelania (3 - ".", "pud³o")
		tab_do_strzelania[y][pom + 1] = 3;
		cout << "Pudlo!";
		Sleep(1500);
		return false;
	}
}

bool Plansza::strzel_w_gracza(char x, int y, int& wsk) {
	int pom = (int)(x - 'A');
	if ((int)(x - 'A') + 1 < 1 || (int)(x - 'A') + 1 > 10 || y < 1 || y > 10) {
		cout << "Bledne dane.";
		return false;
	}
	if (tab[y][pom + 1] == 1) {
		// aktualizacja tablicy do strzelania (2 - "X", statek trafiony)
		tab[y][pom + 1] = 2;
		cout << "Trafiony!";
		Sleep(1000);
		wsk++;
		return true;
	}
	else if (tab[y][pom + 1] == 2) {
		cout << "Pudlo!";
		Sleep(1500);
		return false;
	}
	else {
		// aktualizacja tablicy do strzelania (3 - "*", "pud³o")
		tab[y][pom + 1] = 3;
		cout << "Pudlo!";
		Sleep(1500);
		return false;
	}
}

bool Plansza::wykonaj_ruch() {
	// uzytkownik sztrzela w plansze komputera
	cout << "\nPodaj dwie wspolrzedne, po kazdej enter (A-J, 1-10)" << endl;
	char wczyt_litera;
	int wczyt_liczba;
	while (scanf_s("%c", &wczyt_litera) != 1 || zakres(wczyt_litera, 'A', 'J') || getchar() != '\n') {
		cout << "Bledne dane. Podaj jeszcze raz: ";
		while (getchar() != '\n');
	}
	while (scanf_s("%d", &wczyt_liczba) != 1 || zakres(wczyt_liczba, 1, 10) || getchar() != '\n') {
		cout << "Bledne dane. Podaj jeszcze raz: ";
		while (getchar() != '\n');
	}
	cout << "\nTrafionych: " << licznik_zat_pol << endl;
	return strzel(wczyt_litera, wczyt_liczba, licznik_zat_pol);
}
