#include "Transacao.h"



unsigned int Transacao::getIdCliente() const{
  return idCliente;
}



Transacao::Transacao(ifstream & in){ // le uma transacao na forma de  idcliente ; data ; lista produtos
	string line;
	getline(cin, line);
	idCliente = stoi(line.substr(0, line.find_first_of(";")), nullptr, 10);
	data = line.substr(line.find_first_of(";")+1, 10);


}

void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
  // A IMPLEMENTAR
}


ostream& operator<<(ostream& out, const Transacao & trans){

  // A IMPLEMENTAR
}
