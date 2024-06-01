#include <iostream>
#include "Uzytkownik.h"

using namespace std;

string Gracz::wpisz_nick(){
	cout << "\nPodaj nick: ";
	cin >> Gracz::nick;
	return Gracz::nick;
}

int main() { return 0; }
