# Makefile

OBJS=Vende++.o Cliente.o Transacao.o Produto.o Menus.o Data.o utils.o

all: main

main: $(OBJS) main.cpp
	g++ main.cpp -I. $(OBJS) -o main

Vende++.o: Vende++.cpp
	g++ -c Vende++.cpp

Cliente.o: Cliente.cpp
	g++ -c Cliente.cpp

Transacao.o: Transacao.cpp
	g++ -c Transacao.cpp

Produto.o: Produto.cpp
	g++ -c Produto.cpp

Menus.o: Menus.cpp
	g++ -c Menus.cpp

utils.o: utils.cpp
	g++ -c utils.cpp

clean:
	rm -f Vende *.o

