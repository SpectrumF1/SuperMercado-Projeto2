#include "utils.h"


void clearScreen(){
	for (unsigned int i = 0; i < ALTURA_ECRA; i++){
		cout << endl;
	}
}


unsigned short int leUnsignedShortInt(unsigned short int minValue, unsigned short int  maxValue){
	unsigned int short newInt;
	cout << "Insira um valor: ";
	while (!cin >> newInt || newInt > maxValue || newInt < minValue) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido. Introduza um novo unsigned short int: ";
	}

}


int leInteiro(int min, int max){
	int newInt;
	cout << "Insira um valor: ";
	while(!cin >> newInt || newInt > max || newInt < min) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido. Introduza um novo int: ";
	}
	return newInt;
}

unsigned int leUnsignedInt() {
	unsigned int newUnsignedInt;
	cout << "Insira um valor: ";
	while (!cin >> newUnsignedInt) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido, insira um novo valor unsigned int: ";
	}
	return newUnsignedInt;
}
int leInt() {
	int newInt;
	cout << "Insira um valor: ";
	while (!cin >> newInt) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido, insira um novo valor unsigned int: ";
	}
	return newInt;
}
