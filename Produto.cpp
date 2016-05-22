#include "Produto.h"


Produto::Produto(ifstream & in){ // nome ; custo
	string line;
	getline(in, line);
	if (line.find_first_of(";") == line.find_last_of(";"))
	{
		nome = line.substr(0, line.find(";") - 1);
		custo = stof(line.substr(line.find(";") + 2, line.size() - line.find(";")));
	}
	else
	{
		cout << "Ficheiro de produtos invalido, corrige manualmente." << endl;
		exit(1);
	}
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
