#include "Vende++.h"



VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){
	this->loja = loja;
	this->fichClientes = fichClients;
	this->fichProdutos = fichProdutos;
	this->fichTransacoes = fichProdutos;
  
}

/*********************************
* Ler Ficheiros
********************************/

// Le ficheiros e guarda nos vetores

void lerClientesTxt(VendeMaisMais &loja) {
	ifstream inStream(loja.fichClientes);
	string line;

	if (inStream.is_open())
	{
		getline(inStream, line);
		for (unsigned int i = 4*stoi(line, nullptr, 10); i > 0; i-=4)
		{
			Cliente newclient(inStream);
			loja.clientesVector.push_back(newclient);
		}
		inStream.close();
	}
}

void lerProdutosTxt(VendeMaisMais &loja) {
	string numberOfLinesString;
	ifstream inStream;
	inStream.open(loja.fichProdutos);
	if (!inStream.fail()) {
		getline(inStream, numberOfLinesString);
		for (unsigned int i = 0; i < stoi(numberOfLinesString); i++)
		{
			Produto newProduct(inStream);
			loja.produtosVector.push_back(newProduct);
		}
		inStream.close();
	}
	
	return;
}

void lerTransacoesTxt(VendeMaisMais &loja) {
		string numberOfLinesString;
		ifstream inStream;
		inStream.open(loja.fichTransacoes);
		if (!inStream.fail()) {
			getline(inStream, numberOfLinesString);
			for (unsigned int i = 0; i < stoi(numberOfLinesString); i++)
			{
				Transacao newTransaction(inStream);
				loja.transacoesVector.push_back(newTransaction);
			}
			inStream.close();
		}
		
		return;

}


/*********************************
 * Gestao de Clientes
 ********************************/  

// lista os clientes por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa(){
	sort(clientesVector.begin(), clientesVector.end(), less<Cliente>());
	cout << "Clientes ordenados com sucesso por ordem alfabetica" << endl;
	return;

}


void VendeMaisMais::removeClient(unsigned int idCliente) {
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		if (clientesVector.at(i).getId() == idCliente)
		{
			clientesVector.erase(clientesVector.begin() + i);
		}
	}
	return;
}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome){
	for (unsigned int i = 0; i < clientesVector.size(); i++) {
		if (clientesVector.at(i).getNome() == nome) {
			cout << clientesVector.at(i);
			break;
		}
	}

}


int VendeMaisMais::getIndexById(unsigned int idOfClient) {
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		if (clientesVector.at(i).getId() == idOfClient)
		{
			return i;
		}
	}
	return -1;
}

int VendeMaisMais::getIndexByName(string nameOfClient) {
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		if (clientesVector.at(i).getNome() == nameOfClient)
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
void VendeMaisMais::listarProdutos(){
	sort(produtosVector.begin(), produtosVector.end(), less<Produto>());
	cout << "Produtos ordenados com sucesso por ordem alfabetica" << endl;
	return;

}

/*********************************
* Gestao de Transacoes
********************************/

// listar as transacoes por ordem alfabetica crescente de data
void VendeMaisMais::listarTransacoesData() {
	sort(transacoesVector.begin(), transacoesVector.end(), less<Transacao>());
	cout << "Transacoes ordenadas com sucesso por data" << endl;
	return;
}



/*********************************
 * Preservar Informacao
 ********************************/  

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges() const{
	string line;
	ofstream fileOut;
	char decision;

	//guardar clientes
	if (clientesAlterados)
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
			for (unsigned int i = 0; i < clientesVector.size(); i++)
			{
				clientesVector.at(i).save(fileOut);
			}
			fileOut.close();
		}
		else 
		{
			cout << "Nenhuma Alteracao Guardada!";
		}
	}

	//guarda transacoes

	if (transacoesAlteradas){
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
			for (unsigned int i = 0; i < transacoesVector.size(); i++)
			{
				transacoesVector.at(i).save(fileOut);
			}
			fileOut.close();
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

	out << "A loja tem " << supermercado.clientesVector.size() << " clientes."
		<< endl
		<< "Foram efetuadas no total " << supermercado.transacoesVector.size() << " transacoes."
		<< endl
		<< "Estao disponiveis neste momento" << supermercado.produtosVector.size() << "tipos diferentes de produtos."
		<< endl;
	return out;
}
