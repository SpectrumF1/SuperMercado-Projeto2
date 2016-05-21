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
	loja.updateMapProdutoNameToIndex();
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
		for (unsigned int i = 0; i < loja.clientesVector.size();i++){
			loja.updateVolComprasByTransactions(i);
		}
		loja.updateBottom10();
		
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
	clientesAlterados = true;
	return;
}

// lista os clientes por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa(){
	sort(clientesVector.begin(), clientesVector.end(), less<Cliente>());
	//cout << "Clientes ordenados com sucesso por ordem alfabetica" << endl;
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
	bool isValidData = false;
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
		while (isValidData == false) {
			getline(cin, newDate);
			isValidData = validData(newDate);
			if (!isValidData) {
				cout << "Data invalida, insira a data outra vez: ";
			}
		}
		isValidData = false;
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


void VendeMaisMais::updateVolComprasByTransactions(unsigned int indexOfClientToUpdate) {
	float sumOfVolCompras = 0;
	float epsilon = 0.001;
	for (unsigned int indexInTransactions = 0; indexInTransactions < transacoesVector.size(); indexInTransactions++) {
		vector<string> actualProductsVector = transacoesVector.at(indexInTransactions).getProdutosVector();
		if (clientesVector.at(indexOfClientToUpdate).getId() == transacoesVector.at(indexInTransactions).getIdCliente()) {
			for (int indexInActualProductsVector = 0; indexInActualProductsVector < actualProductsVector.size(); indexInActualProductsVector++) {
				for (unsigned int indexInProductsVector = 0; indexInProductsVector < produtosVector.size(); indexInProductsVector++) {
					if (actualProductsVector.at(indexInActualProductsVector) == produtosVector.at(indexInProductsVector).getNome()) {
						sumOfVolCompras += produtosVector.at(indexInProductsVector).getCusto();
						break;
					}
				}
			}
		}
	}
	if (abs(clientesVector.at(indexOfClientToUpdate).getVolCompras() - sumOfVolCompras) >= epsilon)
	{
		clientesVector.at(indexOfClientToUpdate).setVolCompras(sumOfVolCompras);
		clientesAlterados = true;
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
	bottom10Vector.clear();
	unsigned int clientWithMaxVolCompras;
	float clienteVolCompras;
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		clienteVolCompras = clientesVector.at(i).getVolCompras();
		if (vectorLoad < 10)
		{
			if (clienteVolCompras >= max10VolCompras)
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
				max10VolCompras = 0;
				for (unsigned int indexMax = 0; indexMax < bottom10Vector.size(); indexMax++)
				{
					clienteVolCompras = bottom10Vector.at(indexMax).getVolCompras();
					if (clienteVolCompras >= max10VolCompras)
					{
						max10VolCompras = clienteVolCompras;
						clientWithMaxVolCompras = indexMax;
					}
				}
			}
		}
	}
	sort(bottom10Vector.begin(), bottom10Vector.end(), less<Cliente>());
	produtosCompradosBottom10.resize(produtosVector.size(), 0);
	pair <multimap<unsigned int, unsigned int>::iterator, multimap<unsigned int, unsigned int>::iterator> iterador;
	string productName;
	int produtoIndex;
	for (unsigned int i = 0; i < bottom10Vector.size(); i++)
	{
		iterador = transacaoIdToIndex.equal_range(bottom10Vector.at(i).getId());
		for (multimap<unsigned int, unsigned int>::iterator it = iterador.first; it != iterador.second; it++)
		{
			for (unsigned int j = 0; j < transacoesVector.at(it->second).getProdutosVector().size(); j++)
			{
				productName = transacoesVector.at(it->second).getProdutosVector().at(j);
				produtoIndex = produtoNameToIndex.at(productName);
				produtosCompradosBottom10.at(produtoIndex)++;
			}
		}
	}
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
	
	matrizNProdutos.clear(); // VETOR
	matrizNProdutos.resize(produtosVector.size());
	matrizIndexToId.clear(); //MAP
	matrizIdToIndex.clear();
	matriz.clear();

	//criacao de vetor de correspondecia de id's e criação de matriz
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		matrizIndexToId[i] = clientesVector.at(i).getId(); // fazer corresponder index da Matriz a Id de Cliente;
		matrizIdToIndex[clientesVector.at(i).getId()] = i; // fazer corresponder id De Cliente a index na Matriz
		matriz.push_back(vector <bool>(produtosVector.size(), false)); //inicializar cada linha da matriz a false.
	}

	for (unsigned int i = 0; i < transacoesVector.size(); i++) //Para cada transacao
	{
		equal = getClientesIndexById(transacoesVector.at(i).getIdCliente()); // equal fica com o index de cada cliente, -1 se o cliente já não
		//existir no ficheiro dos clientes, mas as suas transacoes ainda se mantém
		if (equal == -1) //se o cliente ja nao existir
		{
			matrizIndexToId[matriz.size()] = transacoesVector.at(i).getIdCliente(); //Atualizar os maps
			matrizIdToIndex[transacoesVector.at(i).getIdCliente()] = matriz.size();
			matriz.push_back(vector <bool>(produtosVector.size(), false)); //Acrescentar mais uma linha à matriz para o cliente que já não existe
		}
	}

	//alteracao da matriz para valores "true"
	for (unsigned int matrizClienteIndex = 0; matrizClienteIndex < matriz.size(); matrizClienteIndex++) //percorre os clientes na matriz
	{
		for (unsigned int transactionIndex = 0; transactionIndex < transacoesVector.size(); transactionIndex++) //percore o vetor de transacoes
		{
			if (matrizIndexToId.at(matrizClienteIndex) == transacoesVector.at(transactionIndex).getIdCliente()) // se Id de cliente na matriz = id Cliente no vetor de transacoes
			{ // então é necessário por os valores a "true" para esse cliente
				for (unsigned int transacoesProdutoIndex = 0; transacoesProdutoIndex < transacoesVector.at(transactionIndex).getProdutosVector().size(); transacoesProdutoIndex++)
				{ //percorre os produtos daquela transacao 1 a 1
					for (unsigned int matrizProdutoIndex = 0; matrizProdutoIndex < produtosVector.size(); matrizProdutoIndex++)
					{ // percorre as colunas da matriz(produtos) 1 a 1
						if (transacoesVector.at(transactionIndex).getProdutosVector().at(transacoesProdutoIndex) == produtosVector.at(matrizProdutoIndex).getNome())
						{ // se o produto no vetor de transacoes = produto associado à coluna da matriz
							matriz.at(matrizClienteIndex).at(matrizProdutoIndex) = true; //coloca esse produto a true para esse cliente
							matrizNProdutos.at(matrizProdutoIndex)++; //incrementa o vetor que regista quantas vezes cada produto foi comprado
							break; // seguir para proximo produto do vetor transacoes
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

	/*DEBUGGING ZONE
	//Header (produtos iniciais)
	cout << "ID";
	for (unsigned int produtosIndex = 0; produtosIndex < produtosVector.size(); produtosIndex++) {
		cout << setw(5) << produtosVector.at(produtosIndex).getNome().at(0) << produtosVector.at(produtosIndex).getNome().at(1); // imprimir apenas as iniciais
	}
	
	for (unsigned int linha = 0; linha < matriz.size(); linha++) {
		cout << endl;
		cout << matrizIndexToId.at(linha);
		for (unsigned int coluna = 0; coluna < produtosVector.size(); coluna++) {
			if (matrizIndexToId.at(linha) >= 10 && coluna == 0) {
				cout << setw(5) << matriz.at(linha).at(coluna);
			}
			else {
				cout << setw(6) << matriz.at(linha).at(coluna);
			}
		}
	}


	cout << endl << endl;
	/*END OF DEBUGGING ZONE*/

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
	vector <vector <unsigned int>> newMatrix(clientesVector.size(), vector<unsigned int> (produtosVector.size())); //matriz de clientes e produtos mas que regista quantas vezes o produto foi comprado
	vector<unsigned int> vectorOfClientesInteressantes; //guarda os Id's deles
	vector<unsigned int> vectorOfBottom10Clients; //guarda os Id's
	map<unsigned int, unsigned int> mapOfProdutosCompradosPelosBottom10; //key -> indexProduto ; second -> frequencia
	map<unsigned int, unsigned int> mapOfProdutosCompradosPelosClientesInteressantes; //key -> indexProduto ; second -> frequencia
	map<unsigned int, bool> mapOfProdutosComunsAosBottom10; //key -> indexProduto ; second -> booleano que determina se o produto é ou não comum.
	map<unsigned int, unsigned int> mapOfNumberOfDifferentProductsBoughtByEachClient;
	map<unsigned int, unsigned int> mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10;
	map<unsigned int, bool> mapEnableToBeClienteInteressante;
	string produtoRecomendado = "";
	bool enableToBeClienteInteressante = true;
	bool recomendacaoFeita = false;
	unsigned int numeroProdutosComunsAosBottom10 = 0;

	//um produto é comum aos bottom 10 se tiver frequencia = VectorOfBottom10Clients.size()

	//inicializacao da matriz
	for (unsigned int indexC = 0; indexC < clientesVector.size(); indexC++) {
		for (unsigned int indexP = 0; indexP < produtosVector.size(); indexP++) {
			for (unsigned int indexT = 0; indexT < transacoesVector.size(); indexT++) {
				for (unsigned int indexPonT = 0; indexPonT < transacoesVector.at(indexT).getProdutosVector().size(); indexPonT++) {
					if (transacoesVector.at(indexT).getIdCliente() != clientesVector.at(indexC).getId()) {
						break; //avancar para proxima transacao
					}
					if (transacoesVector.at(indexT).getProdutosVector().at(indexPonT) != produtosVector.at(indexP).getNome()) {
						continue; //avancar para proximo produto
					}
					else {
						newMatrix.at(indexC).at(indexP)++;
					}
				}
			}
		}
	}
	//debugMatrix
	cout << "Id";
	for (unsigned int i = 0; i < produtosVector.size(); i++) {
		cout << setw(6) << produtosVector.at(i).getNome().at(0) << produtosVector.at(i).getNome().at(1) << produtosVector.at(i).getNome().at(2);
	}
	for (unsigned int indexC = 0; indexC < newMatrix.size(); indexC++) {
		cout << endl << clientesVector.at(indexC).getId();
		for (unsigned int indexP = 0; indexP < produtosVector.size(); indexP++) {
			if (indexP == 0 && clientesVector.at(indexC).getId() >= 10) {
				cout << setw(7) << newMatrix.at(indexC).at(indexP);
			}
			else {
				cout << setw(8) << newMatrix.at(indexC).at(indexP);
			}
		}
	}
	cout << endl;



	//preencher VectorOfBottom10Clients
	for (unsigned int index= 0; index < bottom10Vector.size(); index++) {
		vectorOfBottom10Clients.push_back(bottom10Vector.at(index).getId());
	}

	//preencher mapProdutosCompradosPelosBottom10 e mapProdutosComunsAosBottom10
	for (unsigned int indexPonMap = 0; indexPonMap < produtosVector.size(); indexPonMap++) {
		mapOfProdutosComunsAosBottom10[indexPonMap] = true;
	}
	for (unsigned int indexPonM = 0; indexPonM < produtosVector.size(); indexPonM++) {
		for (unsigned int indexConM = 0; indexConM < clientesVector.size(); indexConM++) {
			for (unsigned int indexConBottom10V = 0; indexConBottom10V < vectorOfBottom10Clients.size(); indexConBottom10V++) {
				if (clientesVector.at(indexConM).getId() == vectorOfBottom10Clients.at(indexConBottom10V)) {
					mapOfProdutosCompradosPelosBottom10[indexPonM] += newMatrix.at(indexConM).at(indexPonM);
					if (newMatrix.at(indexConM).at(indexPonM) == 0) {
						mapOfProdutosComunsAosBottom10[indexPonM] = false;
					}
				}

			}
		}
	}
	//debug zone
	cout << endl;
	cout << "Id's dos Bottom 10: ";
	for (unsigned int i = 0; i < vectorOfBottom10Clients.size(); i++) {
		cout << setw(5) << vectorOfBottom10Clients.at(i);
	}
	cout << endl;
	cout << "Map de Produtos Comuns aos Bottom 10 (indexProduto - frequencia)" << endl;
	for (auto it = mapOfProdutosComunsAosBottom10.begin(); it != mapOfProdutosComunsAosBottom10.end(); it++) {
		cout << it->first << " - " << it->second << endl;
	}//
	cout << "Map de Produtos Comprados pelos Bottom 10 (indexProduto - frequencia)" << endl;
	for (auto it = mapOfProdutosCompradosPelosBottom10.begin(); it != mapOfProdutosCompradosPelosBottom10.end(); it++) {
		cout << it->first << " - " << it->second << endl;
	}
	//

	//atualizar o numero de produtos comuns aos bottom10
	for (unsigned int index = 0; index < produtosVector.size(); index++) {
		if (mapOfProdutosCompradosPelosBottom10[index] == true) {
			numeroProdutosComunsAosBottom10++;
		}
	}
	//debug zone
	cout << endl << "Numero de Produtos Comuns aos Bottom 10: " << numeroProdutosComunsAosBottom10 << endl;
	//
	//atualizar o mapOfNumberOfDifferentProductsBoughtByEachClient
	for (unsigned int indexConM = 0; indexConM < newMatrix.size(); indexConM++) {
		for (unsigned int indexPonM = 0; indexPonM < produtosVector.size(); indexPonM++) {
			if (newMatrix.at(indexConM).at(indexPonM)> 0) {
				mapOfNumberOfDifferentProductsBoughtByEachClient[indexConM]++;
			}
		}
	}
	//debug zone
	cout << "Map com numero de produtos diferentes comprados por cada cliente(indexProduto - frequencia)" << endl;
	for (auto it = mapOfNumberOfDifferentProductsBoughtByEachClient.begin(); it != mapOfNumberOfDifferentProductsBoughtByEachClient.end(); it++) {
		cout << it->first << " - " << it->second << endl;
	}
	//

	//inicializar o mapEnableToBeClienteInteressante a true;
	for (unsigned int i = 0; i < clientesVector.size(); i++) {
		mapEnableToBeClienteInteressante[i] = true;
	}
	//initializar o vetor vectorOfClientesInteressantes
	//Um cliente é interessante se comprou todos os produtos comuns dos bottom 10 +1
	for (unsigned int indexConM = 0; indexConM < newMatrix.size(); indexConM++) {
		if (find(bottom10Vector.begin(), bottom10Vector.end(), clientesVector.at(indexConM)) != bottom10Vector.end()) {
			mapEnableToBeClienteInteressante[indexConM] = false;
			continue; //se o cliente for bottom10 avançar para o proximo cliente (prox linha da matriz)
		}
		for (unsigned int indexPonM = 0; indexPonM < produtosVector.size(); indexPonM++) {
			if ((mapOfProdutosComunsAosBottom10[indexPonM] == true) && (newMatrix.at(indexConM).at(indexPonM) == 0)) {
				//se produto for comprado por bottom10 mas nao pelo cliente a analisar
				mapEnableToBeClienteInteressante[indexConM] = false;
				break; //avancar para proximo cliente
				
			}
		}
	}

	


	//verificar os maps para ter a certeza que os clientes interessantes compraram todos os produtos comuns aos bottom10 +1
	for (unsigned int clientIndex = 0; clientIndex < clientesVector.size(); clientIndex++) {
		if (mapEnableToBeClienteInteressante[clientIndex] == true && mapOfNumberOfDifferentProductsBoughtByEachClient[clientIndex] <= numeroProdutosComunsAosBottom10) {
			//significa que o cliente nao é interessante
			mapEnableToBeClienteInteressante[clientIndex] == false;
		}
	}
	//debugzone
	cout << endl << "Map that tells us if a client(indexClient - bool) is interesting" << endl;
	for (auto it = mapEnableToBeClienteInteressante.begin(); it != mapEnableToBeClienteInteressante.end(); it++) {
		cout << it->first << " - " << it->second << endl;
	}


	//

	//NESTE PONTO SABEMOS QUEM SAO OS CLIENTES INTERESSANTES

	//initializar o map mapOfProdutosCompradosPelosClientesInteressantes
	for (unsigned int produtoIndex = 0; produtoIndex < produtosVector.size(); produtoIndex++) {
		for (unsigned int clientIndex = 0; clientIndex < clientesVector.size(); clientIndex++) {
			if (mapEnableToBeClienteInteressante[clientIndex] == true) {
				//indica quantas vezes cada produto foi comprado pelos clientes interessantes
				mapOfProdutosCompradosPelosClientesInteressantes[produtoIndex] += newMatrix.at(clientIndex).at(produtoIndex);
			}
		}
	}
	//DebugZone
	cout << endl << "Map de produtos comprados pelos clientes interessantes (indexProduto - frequencia)" << endl;
	for (auto it = mapOfProdutosCompradosPelosClientesInteressantes.begin(); it != mapOfProdutosCompradosPelosClientesInteressantes.end(); it++) {
		cout << it->first << " - " << it->second << endl;
	}
	//


	//initializar o map mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10;
	for (unsigned int produtoIndex = 0; produtoIndex < produtosVector.size(); produtoIndex++) {
		if (mapOfProdutosComunsAosBottom10[produtoIndex] == true) { //Se produto for comum aos bottom10 avanca para o proximo produto
			continue;
		}
		for (unsigned int clientIndex = 0; clientIndex < clientesVector.size(); clientIndex++) {
			mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10[produtoIndex] += newMatrix.at(clientIndex).at(produtoIndex);
		}
	}

	//Debug Zone
	cout << endl << "Map que conta a frequencia de cada produto comprado pelos clientes interessantes e ignora os produtos comuns aos bottom 10 (indexProduto - frequencia)" << endl;
	for (auto it = mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10.begin(); it != mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10.end(); it++) {
		cout << it->first << " - " << it->second << endl;
	}

	unsigned int currentMax = 0;
	unsigned int indexOfMax = 0;
	//encontrar maximo dentro do map anterior e ir verificando se foi ou nao comprado pelos bottom10
	for (auto it = mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10.begin(); it != mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10.end(); it++) {
		if (it->second > currentMax) {
			indexOfMax = it->first;
			if (mapOfProdutosCompradosPelosBottom10[indexOfMax] == 0) {
				//significa que nenhum bottom10 comprou o produto
				currentMax = it->second;
				recomendacaoFeita = true;
			}
		}
	}
	if (recomendacaoFeita == true) {
		produtoRecomendado = produtosVector.at(indexOfMax).getNome();
	}
	else { //significa que temos de fazer a diferenca entre os maps
		map<unsigned int, int> mapDifferenceBetweenProductsBoughtByClientesInteressantesAndBottom10;
		for (unsigned int indexOnMaps = 0; indexOnMaps < produtosVector.size(); indexOnMaps++) {
			int freqClientesInteressantes = mapOfProdutosCompradosPelosClientesInteressantes[indexOnMaps];
		    int freqBottom10 = mapOfProdutosCompradosPelosBottom10[indexOnMaps];
			mapDifferenceBetweenProductsBoughtByClientesInteressantesAndBottom10[indexOnMaps] = (freqClientesInteressantes - freqBottom10);
		}
		//pesquisar pela diferenca maxima
		int currentMax = 0;
		unsigned int indexOfMax = 0;
		for (auto it = mapDifferenceBetweenProductsBoughtByClientesInteressantesAndBottom10.begin(); it != mapDifferenceBetweenProductsBoughtByClientesInteressantesAndBottom10.end(); it++) {
			if (it->second > currentMax) {
				indexOfMax = it->first;
				currentMax = it->second;
			}
		}
		produtoRecomendado = produtosVector.at(indexOfMax).getNome();
	}

	return produtoRecomendado;

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
		cout << "Deseja Guarda as Alteracoes Feitas aos Clientes? (y/n): ";
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
			fileOut << clientesVector.size() << endl;
			for (unsigned int i = 0; i < clientesVector.size(); i++)
			{
				clientesVector.at(i).save(fileOut);
			}
			fileOut.close();
		}
		else 
		{
			cout << endl << "Nenhuma Alteracao Guardada!" << endl;
		}
	}

	//guarda transacoes

	if (transacoesAlteradas){
		cout << "Deseja Guarda as Alteracoes Feitas as Transacoes? (y/n): ";
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
			fileOut << transacoesVector.size() << endl;
			for (unsigned int i = 0; i < transacoesVector.size(); i++)
			{
				transacoesVector.at(i).save(fileOut);
			}
			fileOut.close();
		}
		else
		{
			cout << endl << "Nenhuma Alteracao Guardada!" << endl;
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

