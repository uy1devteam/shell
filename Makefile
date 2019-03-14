
options= -Wall -Wextra
do : shell
fonctions.o: fonctions.cpp header.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
shell: main.o fonctions.o
	g++ -o shell main.o fonctions.o
clean:
	rm -rf *.o
