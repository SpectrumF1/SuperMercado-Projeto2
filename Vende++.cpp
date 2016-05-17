#include "Vende++.h"
#include <map>



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
	loja.updateMapClienteNameToId();
	loja.updateBottom10();
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
		loja.updateMapTransacaoIdToIndex();
		loja.updateMatriz();
}
void VendeMaisMais::setMaxClientesId() {
	int temporaryMax = 0;
	for (unsigned int indexClientes = 0; indexClientes < clientesVector.size(); indexClientes++) {
		if (clientesVector.at(indexClientes).getId() > temporaryMax) {
			temporaryMax = clientesVector.at(indexClientes).getId();
		}
	}
	for (unsigned int indexTransacoes = 0; indexTransacoes < transacoesVector.size(); indexTransacoes++) {
		if (transacoesVector.at(indexTransacoes).getIdCliente() > temporaryMax) {
			temporaryMax = transacoesVector.at(indexTransacoes).getIdCliente();
		}
	}
	maxClientesId = temporaryMax;
}
unsigned int VendeMaisMais::getMaxClientesId() {
	return maxClientesId;
}


/*********************************
 * Gestao de Clientes
 ********************************/  

void VendeMaisMais::addCliente(Cliente newCliente) {
	clientesVector.push_back(newCliente);
	updateMatriz();
	clientesAlterados = true;
	return;
}

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
		indexOfClient = getClientesIndexByName(idOrNameOfCliente);
		clientName = clientesVector.at(indexOfClient).getNome();
		clientesVector.erase(clientesVector.begin() + indexOfClient);
		clienteNameToId.erase(clientName);
		updateMatriz();
		cout << "Cliente " << clientName << " Removido com Sucesso" << endl;
		}
	else if (isdigit(idOrNameOfCliente.at(0))) {
		indexOfClient = getClientesIndexById(stoi(idOrNameOfCliente));
		clientName = clientesVector.at(indexOfClient).getNome();
		clientesVector.erase(clientesVector.begin() + indexOfClient);
		clienteNameToId.erase(clientName);
		updateMatriz();
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
		supermercado.clienteNameToId.erase(supermercado.clientesVector.at(indexOfCliente).getNome());
		supermercado.clientesVector.at(indexOfCliente).setNome(newName);
		supermercado.clienteNameToId[newName] = indexOfCliente;
		supermercado.listarClientesOrdemAlfa();
		supermercado.clientesAlterados = true;
	}
	cout << "Alterar Data de Adesao? (y/n): ";
	changeDate = leCharYorN();
	if (changeDate == 'y' || changeDate == 'Y') {
		string newDate;
		cout << "Insira a nova data de adesao: ";
		getline(cin, newDate);
		Data novaDate(newDate);
		supermercado.clientesVector.at(indexOfCliente).setDataAdesao(novaDate);
		supermercado.clientesAlterados = true;
	}
	cout << "Alterar montante de compras? (y/n): ";
	changeAmount = leCharYorN();
	if (changeAmount == 'y' || changeAmount == 'Y') {
		float newAmount;
		cout << "Insira o novo montante: ";
		newAmount = leFloat();
		supermercado.clientesVector.at(indexOfCliente).setVolCompras(newAmount);
		supermercado.clientesAlterados = true;
	}
	cout << "Cliente Editado com sucesso";
}

void editClient(string clientIdOrName, VendeMaisMais &supermercado) {
	unsigned int clienteIndex;
	if (isalpha(clientIdOrName.at(0))) //means that client is represented by Name
	{
		clienteIndex = supermercado.getClientesIndexByName(clientIdOrName);
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
		clienteIndex = supermercado.getClientesIndexById(stoi(clientIdOrName));
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


int VendeMaisMais::getClientesIndexById(unsigned int idOfClient) {
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		if (clientesVector.at(i).getId() == idOfClient)
		{
			return i;
		}
	}
	return -1;
}

int VendeMaisMais::getClientesIndexByName(string nameOfClient) {
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		if (clientesVector.at(i).getNome() == nameOfClient)
		{
			return i;
		}
	}
	return -1;
}

void VendeMaisMais::updateBottom10() {
	float max10VolCompras = 0;
	int vectorLoad = 0;
	unsigned int clientWithMaxVolCompras;
	float clienteVolCompras;
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		clienteVolCompras = clientesVector.at(i).getVolCompras();
		if (vectorLoad < 10)
		{
			if (clienteVolCompras > max10VolCompras)
			{
				max10VolCompras = clienteVolCompras;
				clientWithMaxVolCompras = vectorLoad;
			}
			bottom10Vector.push_back(clientesVector.at(i));
			vectorLoad++;
		}
		else
		{
			if (clienteVolCompras < max10VolCompras)
			{
				bottom10Vector[clientWithMaxVolCompras] = clientesVector.at(i);
				max10VolCompras = clienteVolCompras;
			}
		}
	}
	sort(bottom10Vector.begin(), bottom10Vector.end(), less<Cliente>());
}

vector<Cliente> VendeMaisMais::getBottom10() {
	return bottom10Vector;
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

void VendeMaisMais::mostraProdutos() {
	clearScreen();
	for (unsigned int i = 0; i < produtosVector.size(); i++)
	{
		cout << i << "). " << produtosVector.at(i);
	}
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
	unsigned int newVolCompras;
	newVolCompras = clientesVector.at(clienteIndex).getVolCompras() + volCompras;
	transacoesVector.push_back(newTransaction);
	clientesVector.at(clienteIndex).setVolCompras(newVolCompras);
	listarTransacoesData();
	updateMapTransacaoIdToIndex();
	updateMatriz();
	transacoesAlteradas = true;
}

pair <int, int> VendeMaisMais::getIndexDataByData(Data date) {
	pair <int, int> indexPair(-1,-1);
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
	pair <int, int> indexPair(-1, -1);
	for (unsigned int dataIndex1 = 0; dataIndex1 < transacoesVector.size(); dataIndex1++)
	{
		if (date1 < transacoesVector.at(dataIndex1).getData() || date1 == transacoesVector.at(dataIndex1).getData())
		{
			indexPair.first = dataIndex1;
			for (unsigned int dataIndex2 = dataIndex1; dataIndex2 < transacoesVector.size(); dataIndex2++)
			{
				if (date2 > transacoesVector.at(dataIndex2).getData() || date2 == transacoesVector.at(dataIndex2).getData())
				{
					indexPair.second = dataIndex2;
				}
			}
			return indexPair;
		}
	}
	return indexPair;
}


/*********************************
* Gestao de Recomendacoes
********************************/

void VendeMaisMais::updateMatriz() {
	unsigned int equal = 0;
	
	matrizNProdutos.clear();
	matrizNProdutos.resize(produtosVector.size());
	matrizIndexToId.clear();

	//criacao de vetor de correspondecia de id's e criação de matriz
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		matrizIndexToId[i] = clientesVector.at(i).getId();
		matrizIdToIndex[clientesVector.at(i).getId()] = i;
		matriz.push_back(vector <bool>(produtosVector.size(), false));
	}

	for (unsigned int i = 0; i < transacoesVector.size(); i++)
	{
		equal = getClientesIndexById(transacoesVector.at(i).getIdCliente());
		if (equal == -1)
		{
			matrizIndexToId[matriz.size()] = transacoesVector.at(i).getIdCliente();
			matrizIdToIndex[transacoesVector.at(i).getIdCliente()] = matriz.size();
			matriz.push_back(vector <bool>(produtosVector.size(), false));
		}
	}

	//alteracao da matriz para valores "true"
	for (unsigned int matrizClienteIndex = 0; matrizClienteIndex < matriz.size(); matrizClienteIndex++)
	{
		for (unsigned int transactionIndex = 0; transactionIndex < transacoesVector.size(); transactionIndex++)
		{
			if (matrizIndexToId.at(matrizClienteIndex) == transacoesVector.at(transactionIndex).getIdCliente())
			{
				for (unsigned int transacoesProdutoIndex = 0; transacoesProdutoIndex < transacoesVector.at(transactionIndex).getProdutosVector().size(); transacoesProdutoIndex++)
				{
					for (unsigned int matrizProdutoIndex = 0; matrizProdutoIndex < produtosVector.size(); matrizProdutoIndex++)
					{
						if (transacoesVector.at(transactionIndex).getProdutosVector().at(transacoesProdutoIndex) == produtosVector.at(matrizProdutoIndex).getNome())
						{
							matriz.at(matrizClienteIndex).at(matrizProdutoIndex) = true;
							matrizNProdutos.at(matrizProdutoIndex)++;
							matrizProdutoIndex = produtosVector.size();
						}
					}
				}
			}
		}
	}
}


struct MatrizHitVec {
	int hit;
	vector <int> vec;
};

string VendeMaisMais::matrizRecomendacao(unsigned int clienteId) {
	string produtoRecomendacao;
	int IndexId;
	int max = -1;
	int maxid = -1;
	int maxprod = -1;
	int maxprodid = -1;
	vector <MatrizHitVec> analysis;
	vector <int> maxidVEC;

	//encotra o index do cliente a publicitar
	for (unsigned int i = 0; i < matrizIndexToId.size(); i++)
	{
		if (clienteId == matrizIndexToId.at(i))
		{
			IndexId = i;
		}
	}

	//analise da matriz
	for (unsigned int iid = 0; iid < matriz.size(); iid++)
	{
		analysis.push_back(MatrizHitVec());
		for (unsigned int iproducts = 0; iproducts < produtosVector.size(); iproducts++)
		{
			if (matriz.at(IndexId).at(iproducts) && matriz.at(iid).at(iproducts))
			{
				analysis.at(iid).hit++;
			}
			else if (!(matriz.at(IndexId).at(iproducts)) && matriz.at(iid).at(iproducts))
			{
				analysis.at(iid).vec.push_back(iproducts);
			}
		}
	}

	//encontra cliente mais parecido
	for (unsigned int i = 0; i < analysis.size(); i++)
	{
		if (max < analysis.at(i).hit && (!analysis.at(i).vec.empty()))
		{
			max = analysis.at(i).hit;
			maxid = i;
		}
	}
	for (unsigned int i = 0; i < analysis.size(); i++)
	{
		if (max == analysis.at(i).hit && (!analysis.at(i).vec.empty()))
		{
			maxidVEC.push_back(i);
		}
	}

	//encontra produto com mais frequencia
	int Nprod;
	if (maxidVEC.size() >= 1)
	{
		for (unsigned int i = 0; i < maxidVEC.size(); i++)
		{
			for (unsigned int j = 0; j < analysis.at(maxidVEC.at(i)).vec.size(); j++)
			{
				unsigned int NproductsIndex = analysis.at(maxidVEC.at(i)).vec.at(j);
				Nprod = matrizNProdutos.at(NproductsIndex);
				if (maxprod < Nprod)
				{
					maxprod = Nprod;
					maxprodid = j;
					maxid = maxidVEC.at(i);
				}
			}
		}
		produtoRecomendacao = produtosVector.at(analysis.at(maxid).vec.at(maxprodid)).getNome();
	}

	return produtoRecomendacao;
}

string VendeMaisMais::matrizRecomendacaoBottom10() {
	string produtoRecomendacao;
	unsigned int clientIndexOnMatrix;
	bool productBuyByBottom10 = true;
	vector <unsigned int> productsBuyByAllBottom10;
	vector <unsigned int> indexClientesInteressantesVector;
	vector <unsigned int> indexClientesInteressantesVectorTemp;
	unsigned int lastClientIndex = 0;

	for (unsigned int productIndexOnMatrix = 0; productIndexOnMatrix < matriz.at(0).size(); productIndexOnMatrix++)
	{
		productBuyByBottom10 = true;
		for (unsigned int clienteIndexOnBottom10 = 0; clienteIndexOnBottom10 < bottom10Vector.size(); clienteIndexOnBottom10++)
		{
			clientIndexOnMatrix = matrizIdToIndex.at(bottom10Vector.at(clienteIndexOnBottom10).getId());
			if (!matriz.at(clientIndexOnMatrix).at(productIndexOnMatrix))
			{
				break; //verificar se faz mesmo o break pretendido
				productBuyByBottom10 = false;
			}
			for (unsigned int indexOnMatrixClientsInteresting = lastClientIndex; indexOnMatrixClientsInteresting < clientIndexOnMatrix; indexOnMatrixClientsInteresting++)
			{
				if (matriz.at(indexOnMatrixClientsInteresting).at(productIndexOnMatrix))
				{
					indexClientesInteressantesVectorTemp.push_back(indexOnMatrixClientsInteresting);
				}
			}
			lastClientIndex = clientIndexOnMatrix+1;
		}
		if (productBuyByBottom10)
		{
			productsBuyByAllBottom10.push_back(productIndexOnMatrix);
			indexClientesInteressantesVector.insert(indexClientesInteressantesVector.begin(), indexClientesInteressantesVectorTemp.begin(), indexClientesInteressantesVectorTemp.end());
		}
		else
		{
			indexClientesInteressantesVectorTemp.clear();
		}

	}



	return produtoRecomendacao;
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
			cout << "Nenhuma Alteracao Guardada!" << endl;
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


/*********************************
* Maps
********************************/

// update do map entre nome e id de cliente
void VendeMaisMais::updateMapClienteNameToId() {
	for (unsigned int clienteIndex = 0; clienteIndex < clientesVector.size(); clienteIndex++)
	{
		clienteNameToId[clientesVector.at(clienteIndex).getNome()] = clientesVector.at(clienteIndex).getId();
	}
}

void VendeMaisMais::updateMapProdutoNameToIndex() {
	for (unsigned int produtoIndex = 0; produtoIndex < produtosVector.size(); produtoIndex++)
	{
		produtoNameToIndex[produtosVector.at(produtoIndex).getNome()] = produtoIndex;
	}
}

void VendeMaisMais::updateMapTransacaoIdToIndex() {
	for (unsigned int  transacaoIndex = 0; transacaoIndex < transacoesVector.size(); transacaoIndex++)
	{
		transacaoIdToIndex.insert(pair<unsigned int, unsigned int> (transacoesVector.at(transacaoIndex).getIdCliente(), transacaoIndex));

	}
}

int VendeMaisMais::ClienteNameToId(string clienteName) {
	if (clienteNameToId.find(clienteName) != clienteNameToId.end())
	{
		return clienteNameToId.find(clienteName)->second;
	}
	else {
		return -1;
	}
}
int VendeMaisMais::ProdutoNameToIndex(string produtoName) {
	if (produtoNameToIndex.find(produtoName) != produtoNameToIndex.end())
	{
		return produtoNameToIndex.find(produtoName)->second;
	}
	else
	{
		return -1;
	}
}
pair <std::multimap<unsigned int, unsigned int>::iterator, std::multimap<unsigned int, unsigned int>::iterator> VendeMaisMais::TransacaoIdToIndex(unsigned int clienteId) {
	return transacaoIdToIndex.equal_range(clienteId);
}

