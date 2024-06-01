//////////////////////////////////////////////////////////////////////////
//			Karolina Binka			Statki			Uzytkownik			//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Uzytkownik.h"

using namespace std;

string Gracz::wpisz_nick(){
	cout << "\nPodaj nick: ";
	//////////////////////////////////// nie dziala ustawienie (set'er) pustego nicku na "anonim"//////////
	//do {
	//	cin >> Uzytkownik::nick;
	//} while (getchar() != '\n');
	cin >> Gracz::nick;
	return Gracz::nick;
}

int main() {


	return 0;
}