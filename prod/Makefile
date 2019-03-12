
options= -Wall -Wextra
do : prod
fonctions.o: fonctions.cpp header.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
prod: main.o fonctions.o
	g++ -o prod main.o fonctions.o
clean:
	rm -rf *.o
