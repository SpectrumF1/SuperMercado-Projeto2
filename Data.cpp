#include "Data.h"


Data::Data(string dataStr){ // data na forma DD/MM/AAA
  // A IMPLEMENTAR
}

int Data::getDia() const{
  return dia;
}

int Data::getMes() const{
  return mes;
}

int Data::getAno() const{
  return ano;
}

void Data::setDia(int dia){
	this->dia = dia;
}

void Data::setMes(int mes){
	this->mes = mes;
}

void Data::setAno(int ano){
	this->ano = ano;
}

void Data::save(ofstream & out) const{
  // A IMPLEMENTAR
}

ostream& operator<<(ostream& out, const Data & data){
  // A IMPLEMENTAR
}
