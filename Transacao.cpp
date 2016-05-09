#include "Transacao.h"

Transacao::Transacao() {
	unsigned int clientId;
	string transactionDateString;
	string newProduct;
	bool keepAddingProducts = true;
	cout << "Introduza o id do cliente: ";
	idCliente = leUnsignedInt();
	cout << "Insira a data da transacao: ";
	getline(cin, transactionDateString);
	cout << endl;
	Data data(transactionDateString);
	cout << "Insira o id do produto (inserir '0' para parar) : ";
	cout << endl;
	while (keepAddingProducts) {
		getline(cin, newProduct);
		if (stoi(newProduct) == 0) {
			keepAddingProducts = false;
		}
		else {
			produtosVector.push_back(newProduct);
		}
	}
	
}

Transacao::Transacao(ifstream & in) { // le uma transacao na forma de  idcliente ; data ; lista produtos
	string line, products;
	getline(cin, line);
	idCliente = stoi(line.substr(0, line.find_first_of(";")), nullptr, 10);
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


unsigned int Transacao::getIdCliente() const{
  return idCliente;
}

unsigned int Transacao::getDataInt() const {
	string dataString;
	dataString = data.getAno;
	dataString.append(data.getMes);
	dataString.append(data.getDia);
	return stoi(dataString, nullptr, 10);
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
	return trans1.getDataInt < trans2.getDataInt;
}
