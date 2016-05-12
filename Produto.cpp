#include "Produto.h"


Produto::Produto(ifstream & in){ // nome ; custo
	string line;
	getline(in, line);
	nome = line.substr(0, line.find(" "));
	custo = stof(line.substr(line.find(";") + 2, line.size() - line.find(";")));
}

string Produto::getNome() const {
  return nome;
}

float Produto::getCusto() const {
  return custo;
}


ostream& operator<<(ostream& out, const Produto & prod){
	out << prod.nome << " ; " << prod.custo
		<< endl;
	return out;

}


bool operator<(const Produto &prod1, const Produto &prod2){
	return prod1.nome < prod2.nome;
}
