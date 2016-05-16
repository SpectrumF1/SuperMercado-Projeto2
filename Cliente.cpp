#include "Cliente.h"
#include <algorithm>
using namespace std;

Cliente::Cliente() {
	Data newData;
	id = NULL;
	nome = "";
	volCompras = NULL;
}
Cliente::Cliente(ifstream & in){
	string line;
	getline(in, line);
	id = stoi(line, nullptr, 10);
	getline(in, line);
	nome = line;
	getline(in, line);
	dataAdesao = line;
	getline(in, line);
	volCompras = stof(line);

}
Cliente::Cliente(unsigned int newId, string newNome, Data newData, float newVolCompras){
	id = newId;
	nome = newNome;
	dataAdesao = newData;
	volCompras = newVolCompras;
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
	out << id << endl
		<< nome << endl
		<< dataAdesao << endl
		<< volCompras << endl;
	return;

}

ostream& operator<<(ostream& out, const Cliente & cli){
	out << cli.id << " - "
		<< cli.nome << " - "
		<< cli.dataAdesao << " - "
		<< fixed << setprecision(2) << cli.volCompras << endl;
	return out;

}

bool operator<(const Cliente &cli1, const Cliente &cli2){
	return cli1.nome < cli2.nome;
}
void Cliente::setId(unsigned int newId){
	id = newId;
}

void Cliente::setNome(string newName){
	nome = newName;
	return;
}
void Cliente::setDataAdesao(Data newDate){
	dataAdesao = newDate;
	return;
}
void Cliente::setVolCompras(float newVolCompras){
	volCompras = newVolCompras;
	return;
}

