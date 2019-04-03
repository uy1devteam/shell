lib= -lreadline
options= -Wall -Wextra -g
do : shell
commandes.o: commandes.cpp commandes.h commande.h header.h
	g++ -c ${options} -o commandes.o commandes.cpp
commande.o: commande.cpp commande.h header.h 
	g++ -c ${options} -o commande.o commande.cpp
fonctions.o: fonctions.cpp header.h commande.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
shell: main.o fonctions.o commande.o commandes.o
	g++ -o shell main.o fonctions.o commande.o commandes.o ${lib} 
clean:
	rm -rf *.o