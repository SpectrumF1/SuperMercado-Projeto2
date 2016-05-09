#include "Transacao.h"



unsigned int Transacao::getIdCliente() const{
  return idCliente;
}



Transacao::Transacao(ifstream & in){ // le uma transacao na forma de  idcliente ; data ; lista produtos
	string line, products;
	getline(cin, line);
	idCliente = stoi(line.substr(0, line.find_first_of(";")), nullptr, 10);
	data = line.substr(line.find_first_of(";")+1, 10);

	//define uma string de todos os produtos a serem tratados
	products = line.substr(line.find_last_of(";") + 2, line.length() - line.find_last_of(";") - 2);
	products.append(", ");

	//passa os produtos da string para um vetor de produtos
	while (!(products.empty()))
	{
		produtos.push_back(products.substr(0, products.find_first_of(",")));
		products.erase(0, products.find_first_of(",") + 2);
	}

}

void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
  // A IMPLEMENTAR
}


ostream& operator<<(ostream& out, const Transacao & trans){

  // A IMPLEMENTAR
}
