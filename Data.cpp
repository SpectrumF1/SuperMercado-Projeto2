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
bool validData(string dateString) {
	string month, day, year;
	unsigned int iDay, iMonth, iYear;
	unsigned int minYear = 2000;
	size_t pos1;
	size_t pos2;
	if (dateString.size() <8 || dateString.size() > 10) {
		return false;
	}
	if (dateString.find('/') != string::npos) {
		pos1 = dateString.find("/");
		if (dateString.find("/", pos1 + 1) == string::npos) {
			return false;
		}
		pos2 = dateString.find("/", pos1 + 1);
	}
	else if (dateString.find('-') != string::npos) {
		pos1 = dateString.find("-");
		if (dateString.find("-", pos1 + 1) == string::npos) {
			return false;
		}
		pos2 = dateString.find("-", pos1 + 1);
	}
	else if (dateString.find(' ') != string::npos) {
		pos1 = dateString.find(" ");
		if (dateString.find(" ", pos1 + 1) == string::npos) {
			return false;
		}
		pos2 = dateString.find(" ", pos1 + 1);
	}
	else {
		return false; 
	}
		month = dateString.substr(pos1 + 1, (pos2 - pos1) - 1);
		if (pos1 == 4) { //significa que data esta representada na forma yyyy/mm/dd
			year = dateString.substr(0, pos1);
			day = dateString.substr(pos2 + 1);
		}
		else if (pos1 < 4) { //significa que data esta representada na forma dd/mm/yyyy
			day = dateString.substr(0, pos1);
			year = dateString.substr(pos2 + 1);
		}
		iDay = stoi(day);
		iMonth = stoi(month);
		iYear = stoi(year);
		if (iMonth < 1 || iMonth > 12) {
			return false;
		}
		if (iYear < minYear) {
			return false;
		}
		if (iDay < 1 || iDay > getNumOfDays(iMonth, iYear)) {
			return false;
		}
		assert(iDay > 0 && iDay <= getNumOfDays(iMonth, iYear) && iMonth > 0 && iMonth <= 12 && iYear >= minYear);
	return true;	
}

Data::Data()
{
	dia = 1;
	mes = 1;
	ano = 2000;
	day = "01";
	month = "01";
	year = "2000";
}

Data::Data(string dateString){ // data na forma DD/MM/AAAA Or DD-MM-AAAA or DD MM AAAA Or AAAA MM DD Or AAAA-MM-DD Or AAAA/MM/DD
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

string Data::getDay() const {
	return day;
}

string Data::getMonth() const {
	return month;
}

string Data::getYear() const {
	return year;
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

void Data::setData(string data) {
	Data newData(data);
	this->ano = newData.ano;
	this->mes = newData.mes;
	this->dia = newData.dia;
}

void Data::save(ofstream & out) const{
	out << dia << "/" << mes << "/" << ano;
}

ostream& operator<<(ostream& out, const Data & data){
	out << data.dia << "/" << data.mes << "/" << data.ano;
	return out;
}

bool operator==(const Data &data1, const Data &data2) {
	if (data1.dia == data2.dia && data1.ano == data2.ano && data1.mes == data2.mes)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator>(const Data & data1, const Data & data2) {
	if (data1.ano > data2.ano)
	{
		return true;
	}
	else if (data1.ano < data2.ano)
	{
		return false;
	}
	else
	{
		if (data1.mes > data2.mes)
		{
			return true;
		}
		else if (data1.mes < data2.mes)
		{
			return false;
		}
		else
		{
			if (data1.dia > data2.dia)
			{
				return true;
			}
			else if (data1.dia < data2.dia)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
}

bool operator<(const Data & data1, const Data & data2) {
	if (data1.ano < data2.ano)
	{
		return true;
	}
	else if (data1.ano > data2.ano)
	{
		return false;
	}
	else
	{
		if (data1.mes < data2.mes)
		{
			return true;
		}
		else if (data1.mes > data2.mes)
		{
			return false;
		}
		else
		{
			if (data1.dia < data2.dia)
			{
				return true;
			}
			else if (data1.dia > data2.dia)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
}
