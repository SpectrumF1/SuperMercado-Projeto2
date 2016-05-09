#include "Cliente.h"


Cliente::Cliente(ifstream & in){
	string line;
	in.open("clientes.txt");
	if (in.fail())
	{
		cerr << "Erro a abrir ficheiro";
		exit(1);
	}
	else
	{
		getline(cin, line);
		if (line.empty())
		{
			cout << "Formarto Nao Valido";
		}
		else
		{
			for (int i = 4 * stoi(line, nullptr, 10); i < 0; i -= 4)
			{
				getline(cin, line);
			}
		}
	}
}


string Cliente::getNome() const{
  return nome;
}

unsigned int Cliente::getId() const{
  return id;
}

float Cliente::getVolCompras() const{
  return volCompras;
}

void Cliente::save(ofstream & out) const{

  // A IMPLEMENTAR

}

ostream& operator<<(ostream& out, const Cliente & cli){
  // A IMPLEMENTAR
}


bool operator<(const Cliente &cli1, const Cliente &cli2){
  // A IMPLEMENTAR
}
