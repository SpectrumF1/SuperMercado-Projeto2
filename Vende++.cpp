#include "Vende++.h"


VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){

  // A IMPLEMENTAR 
}

/*********************************
 * Gestao de Clientes
 ********************************/  

// lista os clientes por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const{
	sort(clientes.begin(), clientes.end(), less<Cliente>());
	return;

}


void VendeMaisMais::removeClient(unsigned int idCliente) {
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes.at(i).getId == idCliente)
		{
			clientes.erase(clientes.begin() + i);
		}
	}
	return;
}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome){



}


int VendeMaisMais::getIndexById(unsigned int idOfClient) {
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes.at(i).getId() == idOfClient)
		{
			return i;
		}
	}
	return -1;
}

int VendeMaisMais::getIndexByName(string nameOfClient) {
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes.at(i).getNome() == nameOfClient)
		{
			return i;
		}
	}
	return -1;
}

/*********************************
 * Gestao de Produtos
 ********************************/  

// listar os produto por ordem alfabetica crescente
void VendeMaisMais::listarProdutos() const{
	sort(produtos.begin(), produtos.end(), less<Produto>());
	return;

}

/*********************************
* Gestao de Transacoes
********************************/

// listar as transacoes por ordem alfabetica crescente de data
void VendeMaisMais::listarTransacoesData() const {
	sort(transacoes.begin(), transacoes.end(), less<Transacao>());
	return;
}



/*********************************
 * Preservar Informacao
 ********************************/  

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges() const{
	vector <Cliente> clientesTemp;
	vector <Transacao> transacoesTemp;
	string line;
	ifstream fileIn;
	ofstream fileOut;
	char decision;

	//guardar clientes
	fileIn.open(fichClientes);
	getline(cin, line);
	for (unsigned int i = 4 * stoi(line, nullptr, 10); i > 0; i -= 4)
	{
		Cliente newClient(fileIn);
		clientesTemp.push_back(newClient);
	}
	fileIn.close();
	if (clientes != clientesTemp)
	{
		cout << "Deseja Guarda as Alteracoes Feitas aos Clientes? (y/n)";
		cin >> decision;
		while (!(decision == 'Y' || decision == 'y' || decision == 'N' || decision == 'n'))
		{
			cout << endl << "Se Sim digite 'Y', caso contrario digite 'N': ";
			cin >> decision;
		}

		//alteracao
		if (decision == 'Y' || decision == 'y')
		{
			fileOut.open(fichClientes);
			for (unsigned int i = 0; i < clientes.size(); i++)
			{
				clientes.at(i).save(fileOut);
			}
			fileOut.close();
		}
		else 
		{
			cout << "Nenhuma Alteracao Guardada!";
		}
	}

	//guarda transacoes
	fileIn.open(fichTransacoes);
	getline(cin, line);
	for (unsigned int i = 4 * stoi(line, nullptr, 10); i > 0; i--)
	{
		Transacao newTransaction(fileIn);
		transacoesTemp.push_back(newTransaction);
	}
	fileIn.close();
	if (transacoes != transacoesTemp){
		cout << "Deseja Guarda as Alteracoes Feitas as Transacoes? (y/n)";
		cin >> decision;
		while (!(decision == 'Y' || decision == 'y' || decision == 'N' || decision == 'n'))
		{
			cout << endl << "Se Sim digite 'Y', caso contrario digite 'N': ";
			cin >> decision;
		}

		//alteracao
		if (decision == 'Y' || decision == 'y')
		{
			fileOut.open(fichTransacoes);
			for (unsigned int i = 0; i < transacoes.size(); i++)
			{
				transacoes.at(i).save(fileOut);
			}
			fileOut.close;
		}
		else
		{
			cout << "Nenhuma Alteracao Guardada!";
		}
	}
}

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma loja
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado){

  // A IMPLEMENTAR 

}
