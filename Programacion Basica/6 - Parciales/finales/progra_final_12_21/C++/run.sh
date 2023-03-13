g++ -g -Wall -Werror -pedantic -c medicion.cpp -o medicion.o  
g++ -g -Wall -Werror -pedantic -c main.cpp -o main.o
g++ -o main main.o medicion.o

valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./main