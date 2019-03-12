
options= -Wall -Wextra
do : harmo
fonctions.o: fonctions.cpp header.h
	g++ -c ${options} -o fonctions.o fonctions.cpp 
main.o: main.cpp header.h 
	g++ -c ${options}  -o main.o  main.cpp  
harmo: main.o fonctions.o
	g++ -o harmo main.o fonctions.o
clean:
	rm -rf *.o
