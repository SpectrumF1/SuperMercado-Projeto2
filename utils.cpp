#include "utils.h"


void clearScreen(){
	for (unsigned int i = 0; i < ALTURA_ECRA; i++){
		cout << endl;
	}
}


unsigned short int leUnsignedShortInt(unsigned short int minValue, unsigned short int  maxValue){
	unsigned int short newInt;
	cout << "Insira um valor: ";
	while (!(cin >> newInt) || newInt > maxValue || newInt < minValue) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido. Introduza um novo unsigned short int: ";
	}
	cin.ignore();
	cout << endl;
	return newInt;
}


int leInteiro(int min, int max){
	int newInt;
	cout << "Insira um valor: ";
	while(!(cin >> newInt) || newInt > max || newInt < min) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido. Introduza um novo int: ";
	}
	cin.ignore();
	cout << endl;
	return newInt;
}

unsigned int leUnsignedInt() {
	unsigned int newUnsignedInt;
	cout << "Insira um valor: ";
	while (!(cin >> newUnsignedInt)) {
		cout << endl;
		cin.clear();
		cin.ignore();

		cout << "Valor invalido, insira um novo valor unsigned int: ";
	}
	cin.ignore();
	cout << endl;
	return newUnsignedInt;
}
int leInt() {
	int newInt;
	cout << "Insira um valor: ";
	while (!(cin >> newInt)) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido, insira um novo valor unsigned int: ";
	}
	cin.ignore();
	cout << endl;
	return newInt;
}
float leFloat() {
	float newFloat;
	cout << "Insira um novo valor: ";
	while (!(cin >> newFloat)) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Valor invalido, insira um novo valor: ";
	}
	cin.ignore();
	cout << endl;
	return newFloat;
}
char leCharYorN() {
	char newChar;
	cout << "Insira o caracter: ";
	while (!(cin >> newChar) || (newChar != 'n' && newChar != 'N' && newChar != 'Y' && newChar != 'y')) {
		cout << endl;
		cin.clear();
		cin.ignore();
		cout << "Caracter invalido, insira um novo caracter: ";
	}
	cin.ignore();
	cout << endl;
	return newChar;
}


void clientesHeader() {
	cout << TAB << "Id" << TAB_BIG << "Nome" << TAB_BIG << "Data Adesao" << TAB << "Vol.Compras" << endl;
}

void transacoesHeader() {
	cout << TAB << "ID" << TAB_BIG << "Data" << TAB_BIG << "Produtos" << endl;
}