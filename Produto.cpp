#include "Produto.h"


Produto::Produto(ifstream & in){ // nome ; custo
	string line;
	getline(cin, line);
	nome = line.substr(0, line.find(";") - 1);
	custo = stof(line.substr(line.find(";") + 2, line.size() - line.find(";")));
}

string Produto::getNome() const {
  return nome;
}

float Produto::getCusto() const {
  return custo;
}

ostream& operator<<(ostream& out, const Produto & prod){


  // A IMPLEMENTAR

}


bool operator<(const Produto &prod1, const Produto &prod2){
  // A IMPLEMENTAR
}
