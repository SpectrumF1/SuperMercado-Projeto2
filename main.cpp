#include <iostream>
#include <string>
#include <vector>

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"


int main(){
  string loja, fichClients, fichProdutos, fichTransacoes;

  // pede a informacoo sobre o nome da loja e os 3 ficheiros com
  // informacao de clientes, produtos e transacoes

  //--------------------------------------------apagar comment---------------------------------------------------
  //if(! infoInicial(loja, fichClients, fichProdutos, fichTransacoes))
  //  return(-1);
  //--------------------------------------------apagar comment---------------------------------------------------

  loja = "Spectrum";
  fichClients = "clientes.txt";
  fichProdutos = "produtos.txt";
  fichTransacoes = "transacoes.txt";

  // cria uma loja
  VendeMaisMais supermercado(loja, fichClients, fichProdutos, fichTransacoes);
  
  // atualiza vetores
  lerClientesTxt(supermercado);
  lerProdutosTxt(supermercado);
  lerTransacoesTxt(supermercado);
  supermercado.setMaxClientesId();
  unsigned int maxId;
  maxId = supermercado.getMaxClientesId();

  cout << "Informacao da loja '" << loja << " do supermercado Vende++:" << endl;
  cout << supermercado << endl;  // mostra estatisticas da loja

  opcoesIniciais(supermercado); // menu inicial com as grandes opcoes
				// que implementam as funcioanlidades
				// disponibilizadas

  return 0;
}
