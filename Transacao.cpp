#include "Transacao.h"

Transacao::Transacao(unsigned int clientId, string transactionDateString, vector <string> productVEC) {
	idCliente = clientId;
	Data data(transactionDateString);
	produtosVector = productVEC;

}

Transacao::Transacao(ifstream & in) { // le uma transacao na forma de  idcliente ; data ; lista produtos
	string line, products;
	getline(in, line);
	idCliente = stoi(line.substr(0, line.find_first_of(" ")), nullptr, 10);
	data = line.substr(line.find_first_of(";") + 1, 10);

	//define uma string de todos os produtos a serem tratados
	products = line.substr(line.find_last_of(";") + 2, line.length() - line.find_last_of(";") - 2);
	products.append(", ");

	//passa os produtos da string para um vetor de produtos
	while (!(products.empty()))
	{
		produtosVector.push_back(products.substr(0, products.find_first_of(",")));
		products.erase(0, products.find_first_of(",") + 2);
	}
}

unsigned int Transacao::getIdCliente() const{
  return idCliente;
}

unsigned int Transacao::getDataInt() const {
	string dataString;
	dataString = data.getYear();
	dataString.append(data.getMonth());
	dataString.append(data.getDay());
	return stoi(dataString, nullptr, 10);
}

vector<string> Transacao::getProdutosVector() const {
	return produtosVector;
}


void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
	out << idCliente << " ; " << data << " , ";
	for (unsigned int i = 0; i < produtosVector.size(); i++)
	{
		if (i = 0) out << produtosVector.at(i);
		else out << "," << produtosVector.at(i);
	}
	out << endl;
}

ostream& operator<<(ostream& out, const Transacao & trans){
	out << trans.idCliente << " ; " << trans.data << " , "	;
	for (unsigned int i = 0; i < trans.produtosVector.size(); i++)
	{
		if (i = 0) out << trans.produtosVector.at(i);
		else out << ", " <<  trans.produtosVector.at(i);
	}
	out << endl;
	return out;

}


bool operator<(const Transacao &trans1, const Transacao &trans2) {
	return trans1.getDataInt() < trans2.getDataInt();
}
