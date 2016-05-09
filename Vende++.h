#pragma once

#include <iostream>
#include <string>
#include <map>
#include<algorithm>


#include "defs.h"
#include "Data.h"
#include "Cliente.h"
#include "Transacao.h"
#include "Produto.h"
#include "utils.h"


using namespace std;

class VendeMaisMais{
 private:
  string loja; // nome da loja
  string fichClientes, fichProdutos, fichTransacoes; // nome dos ficheiros de clientes, produtos e transacoes
  bool transacoesAlteradas; // flag que fica a true se for preciso guardar no final as transacoes
  bool clientesAlterados; // flag que fica a true se for preciso guardar no final os clienets
  unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior identificador
  vector<Cliente> clientes; // vetor que guarda a informacao dos clientes existentes
  vector<Produto> produtos; // vetor que guarda a informacao dos produtos disponiveis
  vector<Transacao> transacoes; // vetor que guarda a informacao das transacoes efetuadas
  map<string, int> clienteIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
  map<string, int> produtoIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
  multimap<int, int> transacaoIdx; // multimap para "traduzir" o identificador do
				   // cliente nos indices das suas
				   // transacoes no vetor de
				   // transacoes

 public:
  VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
  void listarClientesOrdemAlfa() const;
  void listarProdutos() const;
  void listarTransacoesData() const;
  void removeClient(unsigned int idCliente);
  void mostraInformacaoCliente(string nome);
  int getIndexById(unsigned int idOfClient);
  int getIndexByName(string nameOfClient);
  void saveChanges() const;

  friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
};
