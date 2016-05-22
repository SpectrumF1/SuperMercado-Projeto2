#include <iostream>
#include <string>
#include <vector>

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"

#include <windows.h>
#include <windef.h>
#include <WinUser.h>


int main(){
  string loja, fichClients, fichProdutos, fichTransacoes;

  //tratamento da janela
  HWND hwnd = GetConsoleWindow();
  RECT desktop;
  const HWND hDesktop = GetDesktopWindow();
  GetWindowRect(hDesktop, &desktop);
  MoveWindow(hwnd, desktop.right * 0.2, desktop.bottom * 0.2, desktop.right * 0.6, desktop.bottom * 0.6, TRUE);
  HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD max_size = GetLargestConsoleWindowSize(screen);
  int console_x = max_size.X*desktop.right*0.6 / desktop.right - 1;
  int console_y = max_size.Y*desktop.bottom*0.6 / desktop.bottom - 1;
  if (console_x < 56)
  {
	  console_x = max_size.X*desktop.right*0.9 / desktop.right + 3;
	  console_y = max_size.Y*desktop.bottom*0.9 / desktop.bottom - 1;
	  MoveWindow(hwnd, desktop.right * 0.025, desktop.bottom * 0.025, desktop.right * 0.95, desktop.bottom * 0.9, TRUE);
  }
  else if (console_y <= 15)
  {
	  console_y = max_size.Y*desktop.bottom*0.9 / desktop.bottom - 1;
	  MoveWindow(hwnd, desktop.right * 0.2, desktop.bottom * 0.1, desktop.right * 0.6, desktop.bottom * 0.8, TRUE);
  }


  // pede a informacoo sobre o nome da loja e os 3 ficheiros com
  // informacao de clientes, produtos e transacoes
  if(! infoInicial(loja, fichClients, fichProdutos, fichTransacoes))
  return(-1);


  loja = "Spectrum";
  //fichClients = "clientes.txt";
  //fichProdutos = "produtos.txt";
  //fichTransacoes = "transacoes.txt";

  // cria uma loja
  VendeMaisMais supermercado(loja, fichClients, fichProdutos, fichTransacoes);
  
  // atualiza vetores
  lerClientesTxt(supermercado);
  lerProdutosTxt(supermercado);
  lerTransacoesTxt(supermercado);
  supermercado.setMaxClientesId();
  unsigned int maxId;
  maxId = supermercado.getMaxClientesId();

  cout << endl << endl << "Informacao da loja '" << loja << " do supermercado Vende++:" << endl;
  cout << supermercado << endl;  // mostra estatisticas da loja

  system("pause");

  opcoesIniciais(supermercado); // menu inicial com as grandes opcoes
				// que implementam as funcioanlidades
				// disponibilizadas

  return 0;
}
