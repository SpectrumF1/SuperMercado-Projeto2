#include "Transacao.h"

Transacao::Transacao(unsigned int clientId, string transactionDateString, vector <string> productVEC) {
	Data date(transactionDateString);
	idCliente = clientId;
	data = date;
	produtosVector = productVEC;

}

Transacao::Transacao(ifstream & in) { // le uma transacao na forma de  idcliente ; data ; lista produtos
	string line, products;
	getline(in, line);
	if (line.find_first_of(";") != line.find_last_of(";"))
	{
		idCliente = stoi(line.substr(0, line.find_first_of(" ")), nullptr, 10);
		data = line.substr(line.find_first_of(";") + 2, 10);

		//define uma string de todos os produtos a serem tratados
		products = line.substr(line.find_last_of(";") + 2, line.length() - line.find_last_of(";") + 1);
		products.append(",");

		//passa os produtos da string para um vetor de produtos
		while (!(products.empty()))
		{
			produtosVector.push_back(products.substr(0, products.find_first_of(",")));
			products.erase(0, products.find_first_of(",") + 1);
		}
	}
	else
	{
		cout << "Ficheiro de produtos invalido, corrige manualmente." << endl;
		exit(EXIT_FAILURE);
	}	
}

unsigned int Transacao::getIdCliente() const{
  return idCliente;
}


Data Transacao::getData() const {
	return data;
}

vector<string> Transacao::getProdutosVector() const {
	return produtosVector;
}


void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
	out << idCliente << " ; " << data << " ; ";
	for (unsigned int i = 0; i < produtosVector.size(); i++)
	{
		if (i = 0) out << produtosVector.at(i);
		else out << "," << produtosVector.at(i);
	}
	out << endl;
}

ostream& operator<<(ostream& out, const Transacao & trans){
	out << trans.idCliente << " ; " << trans.data << " ; ";
	for (unsigned int i = 0; i < trans.produtosVector.size(); i++)
	{
		if (i == 0) out << trans.produtosVector.at(i);
		else out << ", " <<  trans.produtosVector.at(i);
	}
	out << endl;
	return out;

}


bool operator<(const Transacao &trans1, const Transacao &trans2) {
	return trans1.data < trans2.data;
}
