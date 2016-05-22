#include "Menus.h"
#include "Vende++.h"



bool infoInicial(string &loja, string &fichClientes, string &fichProdutos, string &fichTransacoes){
	ifstream fileTeste;
	cout << "Indique o Nome da Loja." << endl;
	getline(cin, loja);
	while (loja.size() == 0)
	{
		getline(cin, loja);
	}
	cout << "Indique o Nome do Ficheiro com os Dados dos Clientes, Incluindo a Extencao." << endl;
	cin >> fichClientes;
	while (fichClientes.find(".txt") != fichClientes.length() - 4)
	{
		cout << "Volte a indicar o Nome." << endl;
		cin >> fichClientes;
	}
	fileTeste.open(fichClientes);
	if (fileTeste.fail())
	{
		return false;
	}
	fileTeste.close();

	cout << "Indique o Nome do Ficheiro com os Dados dos Produtos, Incluindo a Extencao." << endl;
	cin >> fichProdutos;
	while (fichProdutos.find(".txt") != fichProdutos.length() - 4)
	{
		cout << "Volte a Indicar o Nome." << endl;
		cin >> fichProdutos;
	}
	fileTeste.open(fichProdutos);
	if (fileTeste.fail())
	{
		return false;
	}
	fileTeste.close();

	cout << "Indique o Nome do Ficheiro com os Dados das Transacoes, Incluindo a Extencao." << endl;
	cin >> fichTransacoes;
	while (fichTransacoes.find(".txt") != fichTransacoes.length() - 4)
	{
		cout << "Volte a Indicar o Nome." << endl;
		cin >> fichTransacoes;
	}
	fileTeste.open(fichTransacoes);
	if (fileTeste.fail())
	{
		return false;
	}
	fileTeste.close();
  
	return true;
}

/******************************************
 * Gestao de Clientes
 ******************************************/
unsigned short int menuGestaoClientes(){
  unsigned short int opcao;

  clearScreen();
  cout << TAB_BIG << "Menu Gestao Clientes" << endl;
  cout << endl;
  cout << TAB << "1 - Listar clientes" << endl;
  cout << TAB << "2 - Ver informacao cliente" << endl;
  cout << TAB << "3 - Adicionar cliente" << endl;
  cout << TAB << "4 - Editar cliente" << endl;
  cout << TAB << "5 - Remover cliente" << endl;
  cout << TAB << "6 - Voltar ao menu inicial" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
  opcao = leUnsignedShortInt(1, 6);

  if(opcao == 6)
    return 0;

  return opcao;
}


void opcoesGestaoClientes(VendeMaisMais & supermercado){
	unsigned int opcao, clienteIndex;
  string nome;
  string clienteNameOrId;
  unsigned int nextId = supermercado.getMaxClientesId() + 1;
  string newName;
  Data newDataAdesao;
  string newDataString;
  float newVolCompras;
  Cliente newCliente;
  bool isValidData = false;
  
  while((opcao = menuGestaoClientes()))
    switch (opcao){
    case 1: 
		clientesHeader();
		for (unsigned int i = 0; i < supermercado.getClientesVector().size(); i++)
		{
			supermercado.mostraInformacaoCliente(i);
		}
		system("pause");
      break;
    case 2: cout << "Qual o nome do cliente: ";
      getline(cin, nome);
	  while (nome.size() == 0)
	  {
		  getline(cin, nome);
	  }
	  clienteIndex = supermercado.getClientesIndexByName(nome);
	  if (clienteIndex != -1)
	  {
		  supermercado.mostraInformacaoCliente(clienteIndex);
	  }
	  else
	  {
		  cout << "Cliente nao existe." << endl;
	  }
	  system("pause");
      break;
	case 3:
		cout << "Nome do novo cliente: ";
		getline(cin, newName);
		while (newName.size() == 0)
		{
			getline(cin, newName);
		}
		cout << endl;
		cout << "Data Adesao: ";
		while (isValidData == false) {
			getline(cin, newDataString);
			isValidData = validData(newDataString);
			if (!isValidData) {
				cout << "Data invalida, insira a data outra vez: ";
			}
		}
		isValidData = false;
		newDataAdesao.setData(newDataString);
		cout << endl;
		newVolCompras = 0;
		newCliente.setId(nextId);
		nextId++;
		newCliente.setNome(newName);
		newCliente.setDataAdesao(newDataAdesao);
		newCliente.setVolCompras(newVolCompras);
		supermercado.addCliente(newCliente);
		supermercado.listarClientesOrdemAlfa();
		supermercado.updateMatriz();
		supermercado.updateBottom10();
		cout << "Cliente Adicionado com sucesso" << endl;
		system("pause");
		break;
    case 4:
		cout << "Introduza o Id ou o Nome do cliente a editar: ";
		getline(cin, clienteNameOrId);
		while (clienteNameOrId.size() == 0)
		{
			getline(cin, clienteNameOrId);
		}

		editClient(clienteNameOrId, supermercado);
		system("pause");
      break;
    case 5:
		cout << "Introduza o Id ou o Nome do cliente a remover: ";
		getline(cin, clienteNameOrId);
		while (clienteNameOrId.size() == 0)
		{
			getline(cin, clienteNameOrId);
		}
		supermercado.removeClient(clienteNameOrId);
		system("pause");
      break;
    }
}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuGestaoTransacoes() {
	unsigned short int opcao;

	clearScreen();
	cout << TAB_BIG << "Menu Gestao Transacoes" << endl;
	cout << endl;
	cout << TAB << "1 - Efetuar Compra" << endl;
	cout << TAB << "2 - Visualizar Transacoes de um cliente" << endl;
	cout << TAB << "3 - Visualizar Transacoes de um dia" << endl;
	cout << TAB << "4 - Visualizar Transacoes entre duas datas" << endl;
	cout << TAB << "5 - Visualizar Transacoes (todas)" << endl;
	cout << TAB << "6 - Regressar ao Menu Inicial" << endl;
	opcao = leUnsignedShortInt(1, 6);
	if (opcao == 6) {
		return 0;
	}
	return opcao;
}

void opcoesGestaoTransacoes(VendeMaisMais & supermercado){
	unsigned int opcao, idCliente, produtoIndex, clienteIndex;
	string dataString, nameString;
	vector <string> prodVector;
	bool continuaCompra = true;
	bool isValidData = false;
	char decision;
	float volCompra;
	Data date, date1, date2;
	pair <multimap<unsigned int, unsigned int>::iterator, multimap<unsigned int, unsigned int>::iterator> iterador;
	pair <int, int> indexDatas;

  while((opcao = menuGestaoTransacoes()))
	  switch (opcao)
	  {
	  case 1:
		  cout << "Id do Cliente?" << endl;
		  idCliente = leUnsignedInt();
		  clienteIndex = supermercado.getClientesIndexById(idCliente);
		  if (clienteIndex != -1)
		  {
			  cout << "Introduza a data da transacao:";
			  while (isValidData == false) 
			  {
				  getline(cin, dataString);
				  isValidData = validData(dataString);
				  if (!isValidData)
				  {
					  cout << "Data invalida, insira a data outra vez: ";
				  }
			  }
			  isValidData = false;
			  supermercado.mostraProdutos();
			  cout << "Que produto deseja?" << endl;
			  produtoIndex = leUnsignedInt();
			  while (produtoIndex < 0 || produtoIndex >= supermercado.getProdutosVector().size())
			  {
				  cout << "Valor Mal Introduzido" << endl;
				  cout << "Intruduz um Produto : ";
				  produtoIndex = leUnsignedInt();
			  }
			  prodVector.push_back(supermercado.getProdutosVector().at(produtoIndex).getNome());
			  volCompra = supermercado.getProdutosVector().at(produtoIndex).getCusto();

			  //continuar compra
			  while (continuaCompra)
			  {
				  cout << "Deseja adicionar um produto? (y/n)";
				  cin >> decision;
				  while (!(decision == 'Y' || decision == 'y' || decision == 'N' || decision == 'n'))
				  {
					  cout << endl << "Se Sim digite 'Y', caso contrario digite 'N': ";
					  cin >> decision;
				  }

				  //alteracao
				  if (decision == 'Y' || decision == 'y')
				  {
					  supermercado.mostraProdutos();
					  cout << "Que produto deseja?" << endl;
					  cin >> produtoIndex;
					  while (cin.fail())
					  {
						  cin.clear();
						  cin.ignore(1000, '\n');
						  cout << "Valor mal introduzido" << endl;
						  cin >> produtoIndex;
					  }
					  while (produtoIndex < 0 || produtoIndex >= supermercado.getProdutosVector().size())
					  {
						  cout << "Valor Mal Introduzido" << endl;
						  cout << "Que produto deseja?";
						  cin >> produtoIndex;
						  while (cin.fail())
						  {
							  cin.clear();
							  cin.ignore(1000, '\n');
							  cout << "Valor mal introduzido" << endl;
							  cin >> produtoIndex;
						  }
					  }
					  prodVector.push_back(supermercado.getProdutosVector().at(produtoIndex).getNome());
					  volCompra += supermercado.getProdutosVector().at(produtoIndex).getCusto();
				  }
				  else
				  {
					  continuaCompra = false;
				  }
			  }
			  supermercado.addTransacao(Transacao::Transacao(idCliente, dataString, prodVector), clienteIndex, volCompra);
		  }
		  else
		  {
			  cout << "Cliente nao existe." << endl;
			  system("PAUSE");
		  }
      break;
    case 2:
		cout << "Introduz o nome do cliente: ";
		getline(cin, nameString);
		transacoesHeader();
		iterador = supermercado.TransacaoIdToIndex(supermercado.ClienteNameToId(nameString));
		for (multimap<unsigned int, unsigned int>::iterator it = iterador.first; it != iterador.second; it++)
		{
			cout << supermercado.getTransacoesVector().at(it->second);
		}
		system("pause");
      break;
    case 3:
		cout << "Introduz a data que pretende: ";
		while (isValidData == false) {
			getline(cin, dataString);
			isValidData = validData(dataString);
			if (!isValidData) {
				cout << "Data invalida, insira a data outra vez: ";
			}
		}
		isValidData = false;
		date.setData(dataString);
		indexDatas = supermercado.getIndexDataByData(date);
		if (indexDatas.first != -1)
		{
			transacoesHeader();
			for (unsigned int i = indexDatas.first; i <= indexDatas.second; i++)
			{
				cout << supermercado.getTransacoesVector().at(i);
			}
		}
		else
		{
			cout << "Data nao encontrada" << endl;
		}
		system("pause");
      break;
    case 4:
		cout << "Introduz a primeira data que pretende:";
		while (isValidData == false) {
			getline(cin, dataString);
			isValidData = validData(dataString);
			if (!isValidData) {
				cout << "Data invalida, insira a data outra vez: ";
			}
		}
		isValidData = false;
		date1.setData(dataString);
		cout << "Introduz a segunda data que pretende:";
		while (isValidData == false) {
			getline(cin, dataString);
			isValidData = validData(dataString);
			if (!isValidData) {
				cout << "Data invalida, insira a data outra vez: ";
			}
		}
		isValidData = false;
		date2.setData(dataString);
		indexDatas = supermercado.getIndexDateByDateToDate(date1, date2);
		if (indexDatas.first != -1 && indexDatas.second != -1)
		{
			transacoesHeader();
			for (unsigned int i = indexDatas.first; i <= indexDatas.second; i++)
			{
				cout << supermercado.getTransacoesVector().at(i);
			}
		}
		else
		{
			cout << "Nenhum transacao encontrada no intervalo especificado!" << endl;
		}
		system("pause");
      break;
	case 5:
		transacoesHeader();
		for (unsigned int i = 0; i < supermercado.getTransacoesVector().size(); i++)
		{
			cout << supermercado.getTransacoesVector().at(i);
		}
		system("PAUSE");
		break;
    }
  return;
}

/******************************************
 * Menu de Recomendacoes
 ******************************************/
unsigned short int menuRecomendacao(){
	unsigned short int opcao;

	clearScreen();
	cout << TAB_BIG << "Recomendacoes" << endl;
	cout << endl;
	cout << TAB << "1 - Recomendacao para um cliente" << endl;
	cout << TAB << "2 - Recomendacao para os Bottom10" << endl;
	cout << TAB << "3 - Regressar ao Menu Inicial" << endl << endl;
	opcao = leUnsignedShortInt(1, 3);

	if (opcao == 3)
		return 0;

	return opcao;
}

void opcoesRecomendacao(VendeMaisMais & supermercado) {
	unsigned int opcao;
	int clienteId;
	string clientNameOrId;
	vector<unsigned int> bottom10Vec;
	while ((opcao = menuRecomendacao()))
		switch (opcao)
		{
		case 1:
			cout << "Introduz o id ou o nome do cliente: ";
			getline(cin, clientNameOrId);
			while (clientNameOrId.size() == 0)
			{
				cout << "Introduz o id ou o nome do cliente: ";
				getline(cin, clientNameOrId);
			}
			if (isalpha(clientNameOrId.at(0)))
			{
				clienteId = supermercado.ClienteNameToId(clientNameOrId);
				if (clienteId != -1)
				{
					cout << "O produto a comprar e: " << supermercado.matrizRecomendacao(clienteId) << endl;
				}
				else
				{
					cout << "Cliente nao existe..." << endl;
				}
			}
			else if (isdigit(clientNameOrId.at(0)))
			{
				clienteId = stoi(clientNameOrId);
				cout << "O produto a comprar e: " << supermercado.matrizRecomendacao(clienteId) << endl;
			}
			system("pause");
			break;
		case 2:
			if (supermercado.getClientesVector().size() > 10)
			{
				cout << "O produto a recomendar para os bottom10 e: " << supermercado.matrizRecomendacaoBottom10() << endl;
				cout << "O produto a recomendar para os bottom10 e: " << supermercado.matrizRecomendacaoBottom102() << endl;
			}
			else
			{
				cout << "Impossivel efectuar publicidade" << endl;
			}
			system("pause");
			break;
		}
}

/******************************************
 * Menu Inicial
 ******************************************/
unsigned short int menuInicial(){
  unsigned short int opcao;

  clearScreen();
  cout << TAB_BIG << "Menu Inicial" << endl;
  cout << endl;
  cout << TAB << "1 - Gestao de clientes" << endl;
  cout << TAB << "2 - Listar produtos disponiveis" << endl;
  cout << TAB << "3 - Gestao de transacoes" << endl;
  cout << TAB << "4 - Recomendacoes" << endl;
  cout << TAB << "5 - Sair do programa" << endl << endl;
  opcao = leUnsignedShortInt(1, 5);

  if(opcao == 5)
    return 0;

  return opcao;
}

void opcoesIniciais(VendeMaisMais & supermercado){
  unsigned int opcao;
  while((opcao = menuInicial()))
    switch (opcao){
    case 1: opcoesGestaoClientes(supermercado);
      break;
	case 2: supermercado.mostraProdutos();
		system("pause");
      break;
    case 3: opcoesGestaoTransacoes(supermercado);
      break;
    case 4: opcoesRecomendacao(supermercado);
      break;
    }

  supermercado.saveChanges();
}
