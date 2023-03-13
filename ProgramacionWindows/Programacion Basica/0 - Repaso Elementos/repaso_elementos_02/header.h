/* ----------------------------------------------------------------------------------- */
/* Junto con el #endif al final indican al compilador que ya existe una copia de este
   header en el programa y no debe volverla a incluir en el caso que varios archivos
   la esten llamando. */
#ifndef HEADER_H
#define HEADER_H
/* ----------------------------------------------------------------------------------- */
#define FILE_ERROR -1
#define PROGRAM_ERROR -2
#define NAME_SIZE 15
#define LINE_SIZE 80 //Tiene que ser lo suficientemente grande para leer una linea del archivo
/* ----------------------------------------------------------------------------------- */
/* En la parte anterior dije que faltaba un tipo mas de macro y es esta, la macro 
   multilineal. Funciona similar a una funcion, tiene un nombre, puede contener varios
   argumentos (aunque no especifica su tipo), el cuerpo del codigo esta encerrado entre {}
   y cada linea de codigo debe terminar con ; Aparte al terminar cada linea debe incluirse
   el caracter \ al final. */
#define print_ui(str) {									\
	puts("----------------------------------------");	\
	puts(str);											\
	puts("----------------------------------------");	\
}
/* ----------------------------------------------------------------------------------- */
/* Una estructura funciona como una forma primitiva de objetos, contiene multiple 
   variables de distinto tipos. */
struct s_game_data {
	int nro;
	float price;
	char genre;
	char name[NAME_SIZE+1]; //+1 por el caracter nulo ('\0')
};
/* Typdef permite crear un alias de la siguiente forma: "typdef keyword alias"
   y permite reducir la verbosidad del codigo, en este caso pasamos de crear un struct
   como: struct s_game_data variable
   a: GameData variable */
typedef struct s_game_data GameData;
/* ----------------------------------------------------------------------------------- */
/* Funciones publicas - Son todas las funciones declaradas dentro del header (.h) que 
   luego son desarrolladas en un archivo fuente (.c) usualmente del mismo nombre.
   Esta funciones pueden ser accedidas por otros archivos fuentes que incluyan este
   header como una libreria para su programa. */
float get_game_price(char *game_name, const char *db_filename);
/* ----------------------------------------------------------------------------------- */
#endif
/* ----------------------------------------------------------------------------------- */