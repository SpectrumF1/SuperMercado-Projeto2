#include "utils.h"


void clearScreen(){
	for (unsigned int i = 0; i < ALTURA_ECRA; i++){
		cout << endl;
	}
}


unsigned short int leUnsignedShortInt(unsigned short int minValue, unsigned short int  maxValue){
	unsigned int short newInt;
	while (!cin >> newInt) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido. Introduza um novo unsigned short int: ";
	}

}


int leInteiro(int min, int max){
	int newInt;
	while(!cin >> newInt) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido. Introduza um novo int: ";
	}
	return newInt;
}
