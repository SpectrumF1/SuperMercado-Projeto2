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
	int indexOfClient = -1;
	string clientName;
	if (isalpha(idOrNameOfCliente.at(0)))
	{
		indexOfClient = getClientesIndexByName(idOrNameOfCliente);
		if (indexOfClient != -1)
		{
			clientName = clientesVector.at(indexOfClient).getNome();
			clientesVector.erase(clientesVector.begin() + indexOfClient);
			clienteNameToId.erase(clientName);
			updateMatriz();
			cout << "Cliente " << clientName << " Removido com Sucesso" << endl;
		}
		else
		{
			cout << "Cliente nao encontrado" << endl;
		}
	}
	else if (isdigit(idOrNameOfCliente.at(0))) {
		indexOfClient = getClientesIndexById(stoi(idOrNameOfCliente));
		if (indexOfClient != -1)
		{
			clientName = clientesVector.at(indexOfClient).getNome();
			clientesVector.erase(clientesVector.begin() + indexOfClient);
			clienteNameToId.erase(clientName);
			updateMatriz();
			cout << "Cliente " << clientName << " Removido com Sucesso" << endl;
		}
		else
		{
			cout << "Cliente nao encontrado" << endl;
		}
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
	cout << "Cliente Editado com sucesso" << endl;
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

	//criacao de vetor de correspondecia de id's e cria��o de matriz
	for (unsigned int i = 0; i < clientesVector.size(); i++)
	{
		matrizIndexToId[i] = clientesVector.at(i).getId(); // fazer corresponder index da Matriz a Id de Cliente;
		matrizIdToIndex[clientesVector.at(i).getId()] = i; // fazer corresponder id De Cliente a index na Matriz
		matriz.push_back(vector <int>(produtosVector.size(), 0)); //inicializar cada linha da matriz a false.
	}

	for (unsigned int i = 0; i < transacoesVector.size(); i++) //Para cada transacao
	{
		equal = getClientesIndexById(transacoesVector.at(i).getIdCliente()); // equal fica com o index de cada cliente, -1 se o cliente j� n�o
		//existir no ficheiro dos clientes, mas as suas transacoes ainda se mant�m
		if (equal == -1) //se o cliente ja nao existir
		{
			matrizIndexToId[matriz.size()] = transacoesVector.at(i).getIdCliente(); //Atualizar os maps
			matrizIdToIndex[transacoesVector.at(i).getIdCliente()] = matriz.size();
			matriz.push_back(vector <int>(produtosVector.size(), 0)); //Acrescentar mais uma linha � matriz para o cliente que j� n�o existe
		}
	}

	//alteracao da matriz para valores
	for (unsigned int matrizClienteIndex = 0; matrizClienteIndex < matriz.size(); matrizClienteIndex++) //percorre os clientes na matriz
	{
		for (unsigned int transactionIndex = 0; transactionIndex < transacoesVector.size(); transactionIndex++) //percore o vetor de transacoes
		{
			if (matrizIndexToId.at(matrizClienteIndex) == transacoesVector.at(transactionIndex).getIdCliente()) // se Id de cliente na matriz = id Cliente no vetor de transacoes
			{ // ent�o � necess�rio por os valores a "true" para esse cliente
				for (unsigned int transacoesProdutoIndex = 0; transacoesProdutoIndex < transacoesVector.at(transactionIndex).getProdutosVector().size(); transacoesProdutoIndex++)
				{ //percorre os produtos daquela transacao 1 a 1
					for (unsigned int matrizProdutoIndex = 0; matrizProdutoIndex < produtosVector.size(); matrizProdutoIndex++)
					{ // percorre as colunas da matriz(produtos) 1 a 1
						if (transacoesVector.at(transactionIndex).getProdutosVector().at(transacoesProdutoIndex) == produtosVector.at(matrizProdutoIndex).getNome())
						{ // se o produto no vetor de transacoes = produto associado � coluna da matriz
							matriz.at(matrizClienteIndex).at(matrizProdutoIndex)++; //coloca esse produto a true para esse cliente
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
	IndexId = -1;
	for (unsigned int i = 0; i < matrizIndexToId.size(); i++)
	{
		if (clienteId == matrizIndexToId.at(i))
		{
			IndexId = i;
		}
	}

	if (IndexId != -1)
	{
		//analise da matriz
		for (unsigned int iid = 0; iid < matriz.size(); iid++)
		{
			analysis.push_back(MatrizHitVec());
			for (unsigned int iproducts = 0; iproducts < produtosVector.size(); iproducts++)
			{
				if ((matriz.at(IndexId).at(iproducts) > 0) && (matriz.at(iid).at(iproducts) > 0))
				{
					analysis.at(iid).hit++;
				}
				else if (!(matriz.at(IndexId).at(iproducts) > 0) && (matriz.at(iid).at(iproducts) > 0))
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
	}
	else
	{
		produtoRecomendacao = "Cliente nao encontrado";
	}

	return produtoRecomendacao;
}

string VendeMaisMais::matrizRecomendacaoBottom10() {
	string produtoRecomendacao;
	bool productBuyByBottom10 = true;
	bool validade = true;
	vector <unsigned int> productsBuyByAllBottom10;
	vector <unsigned int> indexClientesInteressantesVector;
	vector <unsigned int> indexClientesInteressantesVectorTemp;
	vector <int> nProdutosCompradosInteressantes(matriz.at(0).size(), 0);
	vector <int> nProdutosCompradosInteressantesTemp(matriz.at(0).size(), 0);
	unsigned int clientIndexOnBottom10 = 0;
	unsigned int indexClientesInteressante;
	unsigned int indexProdutoRecomendacao;
	int maxNProduto = 0x80000000;

	/*DEBUGGING ZONE*/
	//Header (produtos iniciais)
	cout << "ID";
	for (unsigned int produtosIndex = 0; produtosIndex < produtosVector.size(); produtosIndex++)
	{
		cout << setw(5) << produtosVector.at(produtosIndex).getNome().at(0) << produtosVector.at(produtosIndex).getNome().at(1); // imprimir apenas as iniciais
	}

	for (unsigned int linha = 0; linha < matriz.size(); linha++)
	{
		cout << endl;
		cout << matrizIndexToId.at(linha);
		for (unsigned int coluna = 0; coluna < produtosVector.size(); coluna++)
		{
			if (matrizIndexToId.at(linha) >= 10 && coluna == 0)
			{
				cout << setw(5) << matriz.at(linha).at(coluna);
			}
			else
			{
				cout << setw(6) << matriz.at(linha).at(coluna);
			}
		}
	}
	cout << endl << endl;

	cout << endl << "IdB-  ";
	for (unsigned int i = 0; i < bottom10Vector.size(); i++)
	{
		cout << bottom10Vector.at(i).getId() << "; ";
	}
	cout << endl;
	/*END OF DEBUGGING ZONE*/

	clock_t t = clock();
	//inicializa considerando que todos s�o clientes interessantes
	for (unsigned int i = 0; i < matriz.size(); i++)
	{
		if (clientIndexOnBottom10 < bottom10Vector.size())
		{
			if (matrizIndexToId.at(i) != bottom10Vector.at(clientIndexOnBottom10).getId())
			{
				indexClientesInteressantesVector.push_back(i);
			}
			else
			{
				clientIndexOnBottom10++;
			}
		}
		else
		{
			indexClientesInteressantesVector.push_back(i);
		}
	}
	indexClientesInteressantesVectorTemp = indexClientesInteressantesVector;

	for (unsigned int productIndexOnMatrix = 0; productIndexOnMatrix < matriz.at(0).size(); productIndexOnMatrix++)
	{
		productBuyByBottom10 = true;
		clientIndexOnBottom10 = 0;
		indexClientesInteressante = 0;
		for (unsigned int clientIndexOnMatrix = 0; clientIndexOnMatrix < matriz.size(); clientIndexOnMatrix++)
		{
			if (clientIndexOnMatrix == matrizIdToIndex.at(bottom10Vector.at(clientIndexOnBottom10).getId())) //analisa a matrix quando bottom10
			{
				if (matriz.at(clientIndexOnMatrix).at(productIndexOnMatrix) == 0)
				{
					productBuyByBottom10 = false;
				}
				if (clientIndexOnBottom10 < bottom10Vector.size()-1)
				{
					clientIndexOnBottom10++;
				}

			}
			else //analisa a matrix quando outros clientes
			{
				int n = matriz.at(clientIndexOnMatrix).at(productIndexOnMatrix);
				if (n == 0) //se n�o tiver comprado o produto
				{
					if (indexClientesInteressante < indexClientesInteressantesVectorTemp.size())
					{
						if (indexClientesInteressantesVectorTemp.at(indexClientesInteressante) == clientIndexOnMatrix)
						{
							for (unsigned int i = 0; i < productIndexOnMatrix; i++)
							{
								nProdutosCompradosInteressantesTemp.at(i) -= matriz.at(clientIndexOnMatrix).at(i);
							}
							if (indexClientesInteressantesVectorTemp.size() == 1)
							{
								indexClientesInteressantesVectorTemp.clear();
							}
							else
							{
								indexClientesInteressantesVectorTemp.erase(indexClientesInteressantesVectorTemp.begin() + indexClientesInteressante);
							}
						}
					}
				}
				else //se tiver comprado o produto
				{
					for (unsigned int i = 0; i < indexClientesInteressantesVectorTemp.size(); i++)
					{
						if (indexClientesInteressantesVectorTemp.at(i) == clientIndexOnMatrix)
						{
							nProdutosCompradosInteressantes.at(productIndexOnMatrix) += matriz.at(clientIndexOnMatrix).at(productIndexOnMatrix);
						}
					}
					if (indexClientesInteressante + 1 < indexClientesInteressantesVectorTemp.size())
					{
						if (indexClientesInteressantesVectorTemp.at(indexClientesInteressante) == clientIndexOnMatrix)
						{
							indexClientesInteressante++;
						}
					}
				}
			}
		} // end ciclo dos clientes
		if (productBuyByBottom10)
		{
			productsBuyByAllBottom10.push_back(productIndexOnMatrix);
			indexClientesInteressantesVector = indexClientesInteressantesVectorTemp;
			nProdutosCompradosInteressantes = nProdutosCompradosInteressantesTemp;
		}
		else
		{
			indexClientesInteressantesVectorTemp = indexClientesInteressantesVector;
			nProdutosCompradosInteressantesTemp = nProdutosCompradosInteressantes;
		}
	}
// end ciclo dos produtos
	
	if (indexClientesInteressantesVector.size() == 0)
	{
		produtoRecomendacao = "Impossivel efetuar publicidade";
	}
	else
	{
		for (unsigned int indexMaxProduto = 0; indexMaxProduto < nProdutosCompradosInteressantes.size(); indexMaxProduto++)
		{
			if (produtosCompradosBottom10.at(indexMaxProduto) == 0 && maxNProduto < nProdutosCompradosInteressantes.at(indexMaxProduto) && !(nProdutosCompradosInteressantes.at(indexMaxProduto) == 0))
			{
				maxNProduto = nProdutosCompradosInteressantes.at(indexMaxProduto);
				indexProdutoRecomendacao = indexMaxProduto;
			}
		}
		if (maxNProduto == 0x80000000)
		{
			int diferencaNProdutosInteressantesBottom10;
			for (unsigned int indexMaxProduto = 0; indexMaxProduto < nProdutosCompradosInteressantes.size(); indexMaxProduto++)
			{
				diferencaNProdutosInteressantesBottom10 = nProdutosCompradosInteressantes.at(indexMaxProduto) - produtosCompradosBottom10.at(indexMaxProduto);
				if (maxNProduto < diferencaNProdutosInteressantesBottom10 && !(nProdutosCompradosInteressantes.at(indexMaxProduto) == 0))
				{
					maxNProduto = diferencaNProdutosInteressantesBottom10;
					indexProdutoRecomendacao = indexMaxProduto;
				}
			}
		}
		produtoRecomendacao = produtosVector.at(indexProdutoRecomendacao).getNome();
	}

	t = clock() - t;
	cout << setprecision(9) << (float)t / CLOCKS_PER_SEC << endl;

	//debug
	cout << setw(4) << "NPI- ";
	for (unsigned i = 0; i < nProdutosCompradosInteressantes.size(); i++)
	{
		cout << setw(6) << nProdutosCompradosInteressantes.at(i);
	}
	cout << endl;
	cout << setw(4) << "NPB- ";
	for (unsigned i = 0; i < produtosCompradosBottom10.size(); i++)
	{
		cout << setw(6) << produtosCompradosBottom10.at(i);
	}

	
	cout << endl << "IdxI- ";
	for (unsigned int i = 0; i < indexClientesInteressantesVector.size(); i++)
	{
		cout << indexClientesInteressantesVector.at(i) << "; ";
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


string VendeMaisMais::matrizRecomendacaoBottom102() {
vector <vector <unsigned int>> newMatrix(clientesVector.size(), vector<unsigned int>(produtosVector.size())); //matriz de clientes e produtos mas que regista quantas vezes o produto foi comprado
vector<unsigned int> vectorOfClientesInteressantes; //guarda os Id's deles
vector<unsigned int> vectorOfBottom10Clients; //guarda os Id's
map<unsigned int, unsigned int> mapOfProdutosCompradosPelosBottom10; //key -> indexProduto ; second -> frequencia
map<unsigned int, unsigned int> mapOfProdutosCompradosPelosClientesInteressantes; //key -> indexProduto ; second -> frequencia
map<unsigned int, bool> mapOfProdutosComunsAosBottom10; //key -> indexProduto ; second -> booleano que determina se o produto � ou n�o comum.
map<unsigned int, unsigned int> mapOfNumberOfDifferentProductsBoughtByEachClient;
map<unsigned int, unsigned int> mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10;
map<unsigned int, bool> mapEnableToBeClienteInteressante;
string produtoRecomendado = "";
bool enableToBeClienteInteressante = true;
bool recomendacaoFeita = false;
unsigned int numeroProdutosComunsAosBottom10 = 0;

//um produto � comum aos bottom 10 se tiver frequencia = VectorOfBottom10Clients.size()

//inicializacao da matriz
for (unsigned int indexC = 0; indexC < clientesVector.size(); indexC++)
{
	for (unsigned int indexP = 0; indexP < produtosVector.size(); indexP++)
	{
		for (unsigned int indexT = 0; indexT < transacoesVector.size(); indexT++)
		{
			for (unsigned int indexPonT = 0; indexPonT < transacoesVector.at(indexT).getProdutosVector().size(); indexPonT++)
			{
				if (transacoesVector.at(indexT).getIdCliente() != clientesVector.at(indexC).getId())
				{
					break; //avancar para proxima transacao
				}
				if (transacoesVector.at(indexT).getProdutosVector().at(indexPonT) != produtosVector.at(indexP).getNome())
				{
					continue; //avancar para proximo produto
				}
				else
				{
					newMatrix.at(indexC).at(indexP)++;
				}
			}
		}
	}
}


//preencher VectorOfBottom10Clients
for (unsigned int index = 0; index < bottom10Vector.size(); index++)
{
	vectorOfBottom10Clients.push_back(bottom10Vector.at(index).getId());
}

//preencher mapProdutosCompradosPelosBottom10 e mapProdutosComunsAosBottom10
for (unsigned int indexPonMap = 0; indexPonMap < produtosVector.size(); indexPonMap++)
{
	mapOfProdutosComunsAosBottom10[indexPonMap] = true;
}
for (unsigned int indexPonM = 0; indexPonM < produtosVector.size(); indexPonM++)
{
	for (unsigned int indexConM = 0; indexConM < clientesVector.size(); indexConM++)
	{
		for (unsigned int indexConBottom10V = 0; indexConBottom10V < vectorOfBottom10Clients.size(); indexConBottom10V++)
		{
			if (clientesVector.at(indexConM).getId() == vectorOfBottom10Clients.at(indexConBottom10V))
			{
				mapOfProdutosCompradosPelosBottom10[indexPonM] += newMatrix.at(indexConM).at(indexPonM);
				if (newMatrix.at(indexConM).at(indexPonM) == 0)
				{
					mapOfProdutosComunsAosBottom10[indexPonM] = false;
				}
			}

		}
	}
}


//atualizar o mapOfNumberOfDifferentProductsBoughtByEachClient
for (unsigned int indexConM = 0; indexConM < newMatrix.size(); indexConM++)
{
	for (unsigned int indexPonM = 0; indexPonM < produtosVector.size(); indexPonM++)
	{
		if (newMatrix.at(indexConM).at(indexPonM)> 0)
		{
			mapOfNumberOfDifferentProductsBoughtByEachClient[indexConM]++;
		}
	}
}

//inicializar o mapEnableToBeClienteInteressante a true;
for (unsigned int i = 0; i < clientesVector.size(); i++)
{
	mapEnableToBeClienteInteressante[i] = true;
}
//initializar o vetor vectorOfClientesInteressantes
//Um cliente � interessante se comprou todos os produtos comuns dos bottom 10 +1
for (unsigned int indexConM = 0; indexConM < newMatrix.size(); indexConM++)
{
	if (find(bottom10Vector.begin(), bottom10Vector.end(), clientesVector.at(indexConM)) != bottom10Vector.end())
	{
		mapEnableToBeClienteInteressante[indexConM] = false;
		continue; //se o cliente for bottom10 avan�ar para o proximo cliente (prox linha da matriz)
	}
	for (unsigned int indexPonM = 0; indexPonM < produtosVector.size(); indexPonM++)
	{
		if ((mapOfProdutosComunsAosBottom10[indexPonM] == true))
		{
			//se produto for comprado por bottom10 mas nao pelo cliente a analisar
			mapEnableToBeClienteInteressante[indexConM] = false;

		}
	}
}

//initializar o map mapOfProdutosCompradosPelosClientesInteressantes
for (unsigned int produtoIndex = 0; produtoIndex < produtosVector.size(); produtoIndex++)
{
	for (unsigned int clientIndex = 0; clientIndex < clientesVector.size(); clientIndex++)
	{
		if (mapEnableToBeClienteInteressante[clientIndex] == true)
		{
			//indica quantas vezes cada produto foi comprado pelos clientes interessantes
			mapOfProdutosCompradosPelosClientesInteressantes[produtoIndex] += newMatrix.at(clientIndex).at(produtoIndex);
		}
	}
}



//initializar o map mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10;
for (unsigned int produtoIndex = 0; produtoIndex < produtosVector.size(); produtoIndex++)
{
	for (unsigned int clientIndex = 0; clientIndex < clientesVector.size(); clientIndex++)
	{
		mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10[produtoIndex] += newMatrix.at(clientIndex).at(produtoIndex);
	}
}


unsigned int currentMax = 0;
unsigned int indexOfMax = 0;
//encontrar maximo dentro do map anterior e ir verificando se foi ou nao comprado pelos bottom10
for (auto it = mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10.begin(); it != mapFrequenciaProdClientesIntDiffentesProdComunsAosBottom10.end(); it++)
{
	if (it->second > currentMax)
	{
		indexOfMax = it->first;
		if (mapOfProdutosCompradosPelosBottom10[indexOfMax] == 0)
		{
			//significa que nenhum bottom10 comprou o produto
			currentMax = it->second;
			recomendacaoFeita = true;
		}
	}
}
if (recomendacaoFeita == true)
{
	produtoRecomendado = produtosVector.at(indexOfMax).getNome();
}
else
{ //significa que temos de fazer outra vez
	map<unsigned int, int> mapDifferenceBetweenProductsBoughtByClientesInteressantesAndBottom10;
	for (unsigned int indexOnMaps = 0; indexOnMaps < produtosVector.size(); indexOnMaps++)
	{
		int freqClientesInteressantes = mapOfProdutosCompradosPelosClientesInteressantes[indexOnMaps];
		int freqBottom10 = mapOfProdutosCompradosPelosBottom10[indexOnMaps];
		mapDifferenceBetweenProductsBoughtByClientesInteressantesAndBottom10[indexOnMaps] = (freqClientesInteressantes);
	}
	//pesquisar pela diferenca maxima
	int currentMax = 0;
	unsigned int indexOfMax = 0;
	for (auto it = mapDifferenceBetweenProductsBoughtByClientesInteressantesAndBottom10.begin(); it != mapDifferenceBetweenProductsBoughtByClientesInteressantesAndBottom10.end(); it++)
	{
		if (it->second > currentMax)
		{
			indexOfMax = it->first;
			currentMax = it->second;
		}
	}
	produtoRecomendado = produtosVector.at(indexOfMax).getNome();
}

return produtoRecomendado;

}