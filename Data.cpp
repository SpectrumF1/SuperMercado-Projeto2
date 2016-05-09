#include "Data.h"


bool checkBissexto(unsigned int ano) {
	if (((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0))
		return true;
	return false;
}
int getNumOfDays(unsigned int mes, unsigned int ano) {
	if (mes == 2) {
		if (checkBissexto(ano))
			return 29;
		else
			return 28;
	}
	else if (mes <= 7) // testa até Julho
		if (mes % 2 != 0)
			return 31;
		else
			return 30;
	else if (mes <= 12) // testa até dezembro
		if (mes % 2 == 0)
			return 31;
		else
			return 30;
}

Data::Data(string dateString){ // data na forma DD/MM/AAA
	if (dateString.find('/') != string::npos) {
		size_t pos1 = dateString.find("/");
		size_t pos2 = dateString.find("/", pos1 + 1);
		month = dateString.substr(pos1 + 1, (pos2 - pos1) - 1);

		if (pos1 == 4) { //significa que data esta representada na forma yyyy/mm/dd
			year = dateString.substr(0, pos1);
			day = dateString.substr(pos2 + 1);

		}
		else if (pos1 < 4) { //significa que data esta representada na forma dd/mm/yyyy
			day = dateString.substr(0, pos1);
			year = dateString.substr(pos2 + 1);
		}
		if (day.length() == 1) {
			day = '0' + day;
		}
		if (month.length() == 1) {
			month = '0' + month;
		}
	}
	else if (dateString.find('-') != string::npos) {

		size_t pos1 = dateString.find("-");
		size_t pos2 = dateString.find("-", pos1 + 1);
		month = dateString.substr(pos1 + 1, (pos2 - pos1) - 1);

		if (pos1 == 4) { //significa que data esta representada na forma yyyy/mm/dd
			year = dateString.substr(0, pos1);
			day = dateString.substr(pos2 + 1);

		}
		else if (pos1 < 4) { //significa que data esta representada na forma dd/mm/yyyy
			day = dateString.substr(0, pos1);
			year = dateString.substr(pos2 + 1);
		}
		if (day.length() == 1) {
			day = '0' + day;
		}
		if (month.length() == 1) {
			month = '0' + month;
		}

	}
	else if (dateString.find(" ") != string::npos) {
		size_t pos1 = dateString.find(" ");
		size_t pos2 = dateString.find(" ", pos1 + 1);
		month = dateString.substr(pos1 + 1, (pos2 - pos1) - 1);

		if (pos1 == 4) { //significa que data esta representada na forma yyyy/mm/dd
			year = dateString.substr(0, pos1);
			day = dateString.substr(pos2 + 1);

		}
		else if (pos1 < 4) { //significa que data esta representada na forma dd/mm/yyyy
			day = dateString.substr(0, pos1);
			year = dateString.substr(pos2 + 1);
		}
		if (day.length() == 1) {
			day = '0' + day;
		}
		if (month.length() == 1) {
			month = '0' + month;
		}
	}
	dia = stoi(day);
	mes = stoi(month);
	ano = stoi(year);
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
	out << dia << "/" << mes << "/" << ano;
}

ostream& operator<<(ostream& out, const Data & data){
	out << data.dia << "/" << data.mes << "/" << data.ano;
	return out;
}
