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
  vector<Cliente> clientesVector; // vetor que guarda a informacao dos clientes existentes
  vector<Produto> produtosVector; // vetor que guarda a informacao dos produtos disponiveis
  vector<Transacao> transacoesVector; // vetor que guarda a informacao das transacoes efetuadas
  map<string, int> clienteIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
  map<string, int> produtoIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
  multimap<int, int> transacaoIdx; // multimap para "traduzir" o identificador do cliente nos indices das suas transacoes no vetor de transacoes
  map<string, unsigned int> nomeProdutoToIndexMap;
  map<string, unsigned int> clienteNameToId;  // map para "traduzir" nome do cliente no ID dele no vetor de clientes
  map<string, unsigned int> produtoNameToIndex;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
  multimap<unsigned int, unsigned int> transacaoIdToIndex; // multimap para "traduzir" o identificador do cliente nos indices das suas transacoes no vetor de transacoes

 public:
  VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
  void listarClientesOrdemAlfa();
  void listarProdutos();
  void listarTransacoesData();
  void addTransacao(Transacao newTransaction, unsigned int clienteIndex, float volCompras);
  pair<int, int> getIndexDataByData(Data date);
  pair<int, int> getIndexDateByDateToDate(Data date1, Data date2);
  void mostraInformacaoCliente(unsigned int clienteIndex);
  int getClientesIndexById(unsigned int idOfClient);
  int getClientesIndexByName(string nameOfClient);
  void saveChanges() const;
  void removeClient(string idOrNameOfCliente);
  void updateNomeProdutoToIndexMap();
  int indiceProduto(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos
  friend class Produto;

  friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
  friend void lerClientesTxt(VendeMaisMais &loja);
  friend void lerProdutosTxt(VendeMaisMais &loja);
  friend void lerTransacoesTxt(VendeMaisMais &loja);

  vector<Cliente> getClientesVector() const;
  vector<Produto> getProdutosVector() const;
  vector<Transacao> getTransacoesVector() const;


  friend void editClientByIndex(unsigned int indexOfCliente, VendeMaisMais &supermercado);
  friend void editClient(string clientIdOrName, VendeMaisMais &supermercado);

  void updateMapClienteNameToId();
  void updateMapProdutoNameToIndex();
  void updateMapTransacaoIdToIndex();

  unsigned int ClienteNameToId(string clienteName);
  unsigned int ProdutoNameToIndex(string produtoName);
  pair <std::multimap<unsigned int, unsigned int>::iterator, std::multimap<unsigned int, unsigned int>::iterator> TransacaoIdToIndex(unsigned int clienteId);
};
