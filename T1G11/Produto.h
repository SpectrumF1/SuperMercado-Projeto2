#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>


using namespace std;



class Produto {
	
 private:
  string nome;
  float custo;


 public:
  Produto(ifstream & in);
  string getNome() const;
  float getCusto() const;
  
  friend ostream& operator<<(ostream& out, const Produto & prod); // mostra um produto
  friend bool operator<(const Produto &prod1, const Produto &prod2); // compara 2 produtos (1 produto e mais pequeno que outro se o seu nome for "alfabeticamente inferior"
};


