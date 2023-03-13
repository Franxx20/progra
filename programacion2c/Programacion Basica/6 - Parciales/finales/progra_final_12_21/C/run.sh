gcc -g -Wall -Werror -pedantic -c lista/lista.c -o bin/lista_obj.o
gcc -g -Wall -Werror -pedantic main.c bin/lista_obj.o -o bin/main
valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes bin/main
