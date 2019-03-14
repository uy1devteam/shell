lib= -lreadline
options= -Wall -Wextra
do : shell
commande.o: commande.cpp commande.h header.h 
	g++ -c ${options} -o commande.o commande.cpp
fonctions.o: fonctions.cpp header.h commande.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
shell: main.o fonctions.o commande.o
	g++ -o shell main.o fonctions.o commande.o ${lib} 
clean:
	rm -rf *.o