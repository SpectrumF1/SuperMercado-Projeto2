#PROJETO 2 - SUPERMERCADOS VENDE++
##Disciplina - Programação
###Projeto realizado por:
João Filipe Lopes de Carcalho - 1º ano MIEIC - up201504875
Renato Alexandre Sousa Campos - 1º ano MIEIC - up201504942

##Trabalho Completo, ou seja implementado todo o que nos era pedido.

##Decisões Tomadas :
* 1 - Sistema de Recomendações para cliente alvo:
		- Relativamente ao ponto 6 do PDF sobre o sistema de recomendação :
"Sugira ao cliente alvo o produto mais frequente da lista que recolheu no ponto 
anterior e que ele não tenha comprado." - Obtivemos um vetor com os clientes
que satisfazem as seguintes duas condições: compraram o maior número de produtos
comprados pelo cliente alvo e compraram pelo menos um produto não comprado pelo
cliente alvo. A esse clientes vamos chamar "Clientes Aptos". Dos "Clientes Aptos"
retiramos um vetor com os produtos candidatos a serem recomendados. Agora chegamos
a uma ambiguidade : A frequencia associada a um produto deve ser obtida tendo em
conta todos os clientes, ou apenas os "Clientes Aptos". Perante isto, optamos por
associar a frequencia de um produto ao somatorio do número de vezes que foi comprado 
por cada cliente, visto que assim podemos ter em conta o facto de um cliente ter 
comprado o mesmo produto várias vezes.

* 2 - Sistema de Recomendação para bottom10:
		- Relativamente ao ponto 6 do PDF sobre o sistema de recomendação para os
bottom10 Clientes : "Se não houver nenhum produto nessas condições proponha o
produto mais frequente entre os clientes interessantes e menos frequente entre
os Bottom10." - Para realizar isto calculamos a diferença entre a frequencia que
um produto é comprado pelos clientes interessantes e a frequencia com que esse
produto é comprado pelos clientes bottom10, para todos os produtos. O produto
que após os cálculos obtiver diferença máxima é o produto recomendado. No caso
de a diferença máxima ser comum a mais do que um produto, é recomendado o produto
que surgir primeiro por ordem alfabética.
		- Caso haja menos de 11 clientes, o nosso sistema indica que é impossível
efetuar recomendação, porque não faz sentido aplicar o sistema de bottom10 nesta
situação.


* 3 - Adição e edição de Clientes
		- Sempre que é adicionado um cliente colocamos o volume de compras desse
cliente a zero, para mantermos os ficheiros de clientes consistentes com as
transações. Ao editar um cliente não permitimos que seja alterado o seu volume
de compras, pois o volume de compras está sempre relacionado com as suas transações.

* 4 - Optimização de sistema de bottom10
		- Ao realizar a análise dos bottom10 deparamo-nos com código escrito por nós
completamente ilegível e díficil de analisar. Por isso realizamos dois sistemas novos
de recomendação para os bottom10 com lógicas de programação um pouco diferentes e com
código mais limpo (nomes de variáveis mais apropriados e código comentado). Corremos
testes de eficiência (com timers) e reparamos que um sistema demorava cerca de 10x mais 
tempo do que o outro a correr (88ms vs 850ms) e naturalmente optamos pelo sistema mais 
rápido. 
