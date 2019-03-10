
options= -Wall -Wextra
do : count
fonctions.o: fonctions.cpp header.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
count: main.o fonctions.o
	g++ -o count main.o fonctions.o
clean:
	rm -rf *.o
