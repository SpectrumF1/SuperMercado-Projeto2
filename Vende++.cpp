#include "Vende++.h"



VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){
	this->loja = loja;
	this->fichClientes = fichClients;
	this->fichProdutos = fichProdutos;
	this->fichTransacoes = fichTransacoes;
  
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
	loja.listarClientesOrdemAlfa();
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
	loja.listarProdutos();

}

void lerTransacoesTxt(VendeMaisMais &loja) {
		string numberOfLinesString;
		ifstream in_Stream;
		in_Stream.open(loja.fichTransacoes);
		if (!in_Stream.fail()) {
			getline(in_Stream, numberOfLinesString);
			for (unsigned int i = 0; i < stoi(numberOfLinesString); i++)
			{
				Transacao newTransaction(in_Stream);
				loja.transacoesVector.push_back(newTransaction);
			}
			in_Stream.close();
		}
		loja.listarTransacoesData();

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


void VendeMaisMais::removeClient(string idOrNameOfCliente) {
	unsigned int indexOfClient;
	string clientName;
	if (isalpha(idOrNameOfCliente.at(0))) {
		indexOfClient = getIndexByName(idOrNameOfCliente);
		clientName = clientesVector.at(indexOfClient).getNome();
		clientesVector.erase(clientesVector.begin() + indexOfClient);
		cout << "Cliente " << clientName << " Removido com Sucesso" << endl;
		}
	else if (isdigit(idOrNameOfCliente.at(0))) {
		indexOfClient = getIndexById(stoi(idOrNameOfCliente));
		clientName = clientesVector.at(indexOfClient).getNome();
		clientesVector.erase(clientesVector.begin() + indexOfClient);
		cout << "Cliente " << clientName << " Removido com Sucesso" << endl;
	}
	return;
}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(unsigned int clienteIndex){
	cout << clientesVector.at(clienteIndex);
}

//edit client
void editClientByIndex(unsigned int indexOfCliente, VendeMaisMais &supermercado) {
	char changeName, changeDate, changeAmount;
	clientesHeader();
	cout << supermercado.clientesVector.at(indexOfCliente);
	cout << "Alterar Nome ? (y/n): ";
	changeName = leCharYorN();
	if (changeName == 'y' || changeName == 'Y') {
		string newName;
		cout << "Insira um novo nome: ";
		getline(cin, newName);
		supermercado.clientesVector.at(indexOfCliente).setNome(newName);
		supermercado.listarClientesOrdemAlfa();
	}
	cout << "Alterar Data de Adesao? (y/n): ";
	changeDate = leCharYorN();
	if (changeDate == 'y' || changeDate == 'Y') {
		string newDate;
		cout << "Insira a nova data de adesao: ";
		getline(cin, newDate);
		Data novaDate(newDate);
		supermercado.clientesVector.at(indexOfCliente).setDataAdesao(novaDate);
	}
	cout << "Alterar montante de compras? (y/n): ";
	changeAmount = leCharYorN();
	if (changeAmount == 'y' || changeAmount == 'Y') {
		float newAmount;
		cout << "Insira o novo montante: ";
		newAmount = leFloat();
		supermercado.clientesVector.at(indexOfCliente).setVolCompras(newAmount);
	}
	cout << "Cliente Editado com sucesso";
}

void editClient(string clientIdOrName, VendeMaisMais &supermercado) {
	unsigned int clienteIndex;
	if (isalpha(clientIdOrName.at(0))) //means that client is represented by Name
	{
		clienteIndex = supermercado.getIndexByName(clientIdOrName);
		if (clienteIndex != -1){
				editClientByIndex(clienteIndex, supermercado);
		}
		else
		{
			cout << "Cliente nao encontrado" << endl;
		}
	}
	else if (isdigit(clientIdOrName.at(0))) //means that client is represented by Id
	{
		clienteIndex = supermercado.getIndexById(stoi(clientIdOrName));
		if (clienteIndex != -1)
		{
				editClientByIndex(clienteIndex, supermercado);
		}
		else
		{
			cout << "Cliente nao encontrado" << endl;
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

void VendeMaisMais::addTransacao(Transacao newTransaction, unsigned int clienteIndex, float volCompras) {
	transacoesVector.push_back(newTransaction);
	clientesVector.at(clienteIndex).setVolCompras(volCompras);
	listarTransacoesData();
}

pair <int, int> VendeMaisMais::getIndexDataByData(Data date) {
	pair <unsigned int, unsigned int> indexPair(-1,-1);
	for (unsigned int dataIndex1 = 0; dataIndex1 < transacoesVector.size(); dataIndex1++)
	{
		if (date == transacoesVector.at(dataIndex1).getData())
		{
			indexPair.first = dataIndex1;
			for (unsigned int dataIndex2 = dataIndex1; dataIndex2 < transacoesVector.size(); dataIndex2++)
			{
				if (date == transacoesVector.at(dataIndex2).getData())
				{
					indexPair.second = dataIndex2;
				}
			}
			return indexPair;
		}
	}
	return indexPair;
}

pair <int, int> VendeMaisMais::getIndexDateByDateToDate(Data date1, Data date2) {
	pair <unsigned int, unsigned int> indexPair(-1, -1);
	for (unsigned int dataIndex1 = 0; dataIndex1 < transacoesVector.size(); dataIndex1++)
	{
		if (date1 < transacoesVector.at(dataIndex1).getData() || date1 == transacoesVector.at(dataIndex1).getData())
		{
			indexPair.first = dataIndex1;
			for (unsigned int dataIndex2 = dataIndex1; dataIndex2 < transacoesVector.size(); dataIndex2++)
			{
				if (date2 > transacoesVector.at(dataIndex2).getData() || date2 == transacoesVector.at(dataIndex2).getData())
				{
					indexPair.second = dataIndex1;
				}
			}
			return indexPair;
		}
	}
	return indexPair;
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
		<< "Estao disponiveis neste momento " << supermercado.produtosVector.size() << " tipos diferentes de produtos."
		<< endl;
	return out;
}


/*********************************
* Retorna os vectores
********************************/

// mostra o conteudo de uma loja
vector<Cliente> VendeMaisMais::getClientesVector() const{
	return clientesVector;

}
vector<Produto> VendeMaisMais::getProdutosVector() const{
	return produtosVector;

}
vector<Transacao> VendeMaisMais::getTransacoesVector() const{
	return transacoesVector;

}