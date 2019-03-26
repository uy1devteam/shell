
options= -Wall -Wextra
do : kwin
fonctionlogique.o: fonctionlogique.cpp fonctionlogique.h
	g++ -c ${options} -o fonctionlogique.o fonctionlogique.cpp
symbol.o: symbol.cpp symbol.h
	g++ -c ${options} -o symbol.o symbol.cpp
etat.o: etat.cpp etat.h symbol.h
	g++ -c ${options} -o etat.o etat.cpp
combinaison.o: combinaison.cpp combinaison.h
	g++ -c ${options} -o combinaison.o combinaison.cpp
fonctions.o: fonctions.cpp header.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
kwin: main.o fonctions.o combinaison.o etat.o symbol.o fonctionlogique.o
	g++ -o kwin main.o fonctions.o combinaison.o etat.o symbol.o fonctionlogique.o
clean:
	rm -rf *.o
