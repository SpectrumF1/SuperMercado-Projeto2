#include "utils.h"


void clearScreen(){
	for (unsigned int i = 0; i < ALTURA_ECRA; i++){
		cout << endl;
	}
}


unsigned short int leUnsignedShortInt(unsigned short int minValue, unsigned short int  maxValue){
	unsigned int short newInt;
	cin >> newInt;
	while (newInt < minValue || newInt > maxValue || cin.fail()){
		cin.clear();
		cin.ignore();
		cout << "Introduza o novo short int: ";
		cin >> newInt;
		cout << endl;
	}
	cin.ignore();
 //Implementado

}


int leInteiro(int min, int max){

  // A IMPLEMENTAR

}
