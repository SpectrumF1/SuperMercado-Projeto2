#include "Menus.h"
#include "Vende++.h"



bool infoInicial(string &loja, string &fichClientes, string &fichProdutos, string &fichTransacoes){
	ifstream fileTeste;
	cout << "Indique o Nome da Loja." << endl;
	cin >> loja;
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
  cout << TAB << "3 - Editar cliente" << endl;
  cout << TAB << "4 - Remover cliente" << endl;
  cout << TAB << "5 - Voltar ao menu inicial" << endl << endl;
  cout << TAB << "Qual a sua opcao: ";
  opcao = leUnsignedShortInt(1, 5);

  if(opcao == 5)
    return 0;

  return opcao;
}


void opcoesGestaoClientes(VendeMaisMais & supermercado){
	unsigned int opcao, clienteIndex;
  string nome;
  string clienteNameOrId;
  while((opcao = menuGestaoClientes()))
    switch (opcao){
    case 1: supermercado.listarClientesOrdemAlfa();
		system("pause");
      break;
    case 2: cout << "Qual o nome do cliente: ";
      getline(cin, nome);
	  clienteIndex = supermercado.getIndexByName(nome);
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
		cout << "Introduza o Id ou o Nome do cliente a editar: ";
		getline(cin, clienteNameOrId);
		editClient(clienteNameOrId, supermercado);
      break;
    case 4:
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
	string data;
	vector <string> prodVector;
	bool continuaCompra = true;
	char decision;
	float volCompra;

  while((opcao = menuGestaoTransacoes()))
	  switch (opcao)
	  {
	  case 1:
		  cout << "Id do Cliente?" << endl;
		  idCliente = leUnsignedInt();
		  clienteIndex = supermercado.getIndexById(idCliente);
		  if (clienteIndex != -1)
		  {
			  cout << "Introduza a data da transacao:";
			  getline(cin, data);

			  clearScreen();
			  for (unsigned int i = 0; i < supermercado.getProdutosVector().size(); i++)
			  {
				  cout << i << "). " << supermercado.getProdutosVector().at(i);
			  }
			  cout << "Que produto deseja?" << endl;
			  produtoIndex = leUnsignedInt();
			  while (produtoIndex < 0 && produtoIndex >= supermercado.getProdutosVector().size())
			  {
				  cout << "Valor Mal Introduzido" << endl << endl;
				  cout << endl << "Intruduz um Produto :";
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
					  clearScreen();
					  for (unsigned int i = 0; i < supermercado.getProdutosVector().size(); i++)
					  {
						  cout << i << "). " << supermercado.getProdutosVector().at(i);
					  }
					  cout << "Que produto deseja?" << endl;
					  produtoIndex = leUnsignedInt();
					  while (produtoIndex < 0 && produtoIndex >= supermercado.getProdutosVector().size())
					  {
						  cout << "Valor Mal Introduzido" << endl << endl;
						  cout << endl << "Intruduz um Produto :";
						  produtoIndex = leUnsignedInt();
					  }
					  prodVector.push_back(supermercado.getProdutosVector().at(produtoIndex).getNome());
					  volCompra += supermercado.getProdutosVector().at(produtoIndex).getCusto();
				  }
				  else
				  {
					  continuaCompra = false;
				  }
			  }
			  supermercado.getTransacoesVector().push_back(Transacao::Transacao(idCliente, data, prodVector));
			  supermercado.getClientesVector().at(clienteIndex).setVolCompras(volCompra);
		  }
		  else
		  {
			  cout << "Cliente nao existe." << endl;
			  system("PAUSE");
		  }
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
	case 5:
		transacoesHeader();
		for (unsigned int i = 0; i < supermercado.getTransacoesVector().size(); i++)
		{
			cout << supermercado.getTransacoesVector().at(i) << endl;
		}
		system("PAUSE");
		break;
    }
  return;
}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuRecomendacao(){

	return 0;
}

void opcoesRecomendacao(VendeMaisMais & supermercado){
  unsigned int opcao;

  while((opcao = menuRecomendacao()))
    switch (opcao){
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
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
  cout << TAB << "Qual a sua opcao: ";
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
    case 2: supermercado.listarProdutos();
      break;
    case 3: opcoesGestaoTransacoes(supermercado);
      break;
    case 4: opcoesRecomendacao(supermercado);
      break;
    }

  supermercado.saveChanges();
}
