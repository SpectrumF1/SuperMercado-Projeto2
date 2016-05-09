#include "Cliente.h"


Cliente::Cliente(ifstream & in){
	string line;
	getline(cin, line);
	id = stoi(line, nullptr, 10);
	getline(cin, line);
	nome = line;
	getline(cin, line);
	dataAdesao = line;
	getline(cin, line);
	volCompras = stof(line);

}


string Cliente::getNome() const{
  return nome;
}

unsigned int Cliente::getId() const{
  return id;
}
Data Cliente::getDataAdesao() const{
	return dataAdesao;
}

float Cliente::getVolCompras() const{
  return volCompras;
}

void Cliente::save(ofstream & out) const{

  

}

ostream& operator<<(ostream& out, const Cliente & cli){
	out << cli.id << endl
		<< cli.nome << endl
		<< cli.dataAdesao << endl
		<< cli.volCompras << endl;
	return out;

}


bool operator<(const Cliente &cli1, const Cliente &cli2){
  // A IMPLEMENTAR
}
void Cliente::setNome(string newName){
	nome = newName;
	cout << "Nome de cliente com id: " << id << ", editado com sucesso para: " << nome << endl;
}
void Cliente::setDataAdesao(Data newDate){
	dataAdesao = newDate;
	cout << "Data de adesao de cliente com id: " << id << ", editado com sucesso para: " << dataAdesao << endl;
}
void Cliente::setVolCompras(float newVolCompras){
	volCompras = newVolCompras;
	cout << "Vol. de Compras de cliente com id: " << id << ", editado com sucesso para: " << volCompras << endl;
}
