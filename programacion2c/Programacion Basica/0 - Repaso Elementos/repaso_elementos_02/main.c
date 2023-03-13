/* ----------------------------------------------------------------------------------- */
/* Header dentro de <...> son buscados en una carpeta especial del sistema con todas las
   librerias instaladas por defecto, "..." indica que tiene que buscar el header dentro
   de la direccion actual de este archivo fuente. */
#include <stdio.h>
#include <string.h>
#include "header.h"
/* ----------------------------------------------------------------------------------- */
/* Funciones privadas - Son todas las funciones declaradas y desarrolladas en el mismo
   archivo fuente, usualmente son funciones a las cuales no se desean ser accedidas por
   un archivo externo. */
int crear_archivo_de_texto(const char *filename);
void parsear_texto(GameData *p_gd, char *str);
/* ----------------------------------------------------------------------------------- */
int main() {
	const char *in_filename = "archivo_de_texto.txt"; //String constante
	const char *out_filename = "archivo_binario.bin";

	FILE *in_txt, *out_bin; //Puntero a archivos, punteros se vera en Programacion.
	float rc; //rc = return code nombre estandar para guardar el resultado de una funcion.
	GameData game;
	char line_str[LINE_SIZE]; 
	char game_name[NAME_SIZE+1]; //+1 por el caracter nulo ('\0')

	if(!crear_archivo_de_texto(in_filename)) {
		puts("[ERROR] - No se pudo crear archivo de texto"); //Incluye el \n por defecto
		return PROGRAM_ERROR;
	}

	/* Hay multiples formas de abrir un archivo las 4 principales son:
	rt = read text;wt = write text;wb = write byte; rb = read byte
	-Se ve en mas detalle en Programacion- */
	in_txt = fopen(in_filename, "rt");
	/* Si por alguna razon fallo al abrir el archivo la funcion retorna NULL */
	if(in_txt == NULL) {
		puts("[ERROR] - No se pudo abrir archivo de texto");
		return FILE_ERROR;
	}

	out_bin = fopen(out_filename, "wb");
	if(!out_bin) { //!var es igual a var == NULL o var == 0
		puts("[ERROR] - No se pudo crear el archivo binario");
		fclose(in_txt); //Cerramos los archivos abiertos para evitar memory leaks.
		return FILE_ERROR;
	}

	print_ui("\t     Games Database"); //multiline macro
	/* Con fgets podemos leer un stream de datos y guardarlos en una cadena de
	tamaño N. En este caso leemos una linea del archivo de texto y la guardamos en
	la cadena line_str. */
	while(fgets(line_str, sizeof(line_str), in_txt)) {
		parsear_texto(&game, line_str); //Llena la variable struct con los datos de la cadena.
		/* fwrite escribe a un archivo binario n veces los datos de una variable de tamaño s.
		En este caso escribe una vez los datos de la variable game al archivo binario. */
		fwrite(&game, sizeof(GameData), 1, out_bin);
		/* %N#, donde N es un numero entero y # el tipo de dato (d,f,c,s,u,...)
		 es una forma de generar N espacios entre el caracter anterior a % y la variable. */
		printf("%d|%7.2f|%c|%15s\n", game.nro, game.price, game.genre, game.name);
	}

	/* Una vez que terminamos con los archivos debemos cerrarlos para evitar memory leaks. */
	fclose(in_txt);
	fclose(out_bin);

	print_ui("Escriba EXIT para salir del programa");
	do {
		/* Ahora utilizamos fgets para leer input del usuario en lugar de un achivo. */
		if(!fgets(game_name, NAME_SIZE, stdin)) {
			puts("[ERROR] Por favor ingrese un nombre valido");
			continue;
		}
		/* Removemos el caracter \n introducido por fgets al presionar Enter.
		strcspn nos da el indice del caracter buscado en la string. */
		game_name[strcspn(game_name, "\n")] = '\0';

		rc = get_game_price(game_name, out_filename);
		if(rc == FILE_ERROR) {
			puts("[ERROR] - No se pudo obtener el precio del juego");
			return PROGRAM_ERROR;
		}
		else if(!rc) {
			printf("No se encontro el juego \"%s\"\n", game_name);
		}
		else {
			printf("El precio del juego %s es: %.2f$\n", game_name, rc);
		}

	} while(strncmp(game_name, "EXIT", NAME_SIZE) != 0);
	/* strncmp compara N caracteres de dos cadenas, devuelve 0 si son iguales,
	<0 si la segundo es mayor a la primera y >0 si la primera es mayor. */

	print_ui("\t\tBye bye~");

	return 0;
	/* stream: Es una interfaz que generaliza distinto tipos de buffers/entrada de datos,
	Ya sea un archivo, datos de un periferico o de la memoria principal.
	En C stream son representados como punteros a archivos FILE* */
}
/* ----------------------------------------------------------------------------------- */
int crear_archivo_de_texto(const char *filename)
{
	int i;
	FILE *txt_file;
	const char *aux[] = { //Matriz de strings
		/* nro|price|genere|name */
		"69420|9999.99|E|ELDEN RING",
		"12357|654.98|S|COD",
		"23156|456.32|B|LOL",
		"45678|124.42|E|ELDEN RING 2",
	};

	txt_file = fopen(filename, "wt");
	if(!txt_file) {
		return 0;
	}

	/* Tamaño de la array = sizeof(array)/sizeof(primer_elemenot_de_array) 
	La funcion sizeof() se calcula durante la compilacion, asi que durante la ejecucion
	del programa va a contener un valor fijo. */
	for(i = 0; i < sizeof(aux)/sizeof(aux[0]); i++) {
		/* fprintf funciona igual que printf, pero como primer parametro tiene el stream
		en el cual se va a escribir los datos. */
		fprintf(txt_file, "%s\n", aux[i]);
	}

	fclose(txt_file);
    return 1;
}
/* ----------------------------------------------------------------------------------- */
void parsear_texto(GameData *p_gd, char *str)
{
	/* Busca la primer ocurrencia del caracter y devuelve un puntero a ese lugar. */
	char *aux = strchr(str, '\n');
	*aux = '\0'; //Anula el caracter \n y todo lo que le siguiera.

	if(!*str) {
		return; //Si la cadena esta vacia nos volvemos.
	}

	aux = strrchr(str, '|'); //Buscamos la ultima aparicion del caracter |
	/* Copia al primer argumento lo del segundo, +1 para omitir el caracter | */
	strcpy(p_gd->name, aux + 1);
	*aux = '\0'; //Anula el caracter | y todo lo que le siguiera.

	aux = strrchr(str, '|');
	/* sscanf lee los datos de una cadena y los guarda en otras variables de la forma 
	indicada en el segundo argumento.
	En este caso guardo lo que apunte aux en genre como un char.*/
	sscanf(aux + 1, "%c", &p_gd->genre);
	*aux = '\0'; //Anula el caracter | y todo lo que le siguiera.

	aux = strrchr(str, '|');
	sscanf(aux + 1, "%f", &p_gd->price);
	*aux = '\0'; //Anula el caracter | y todo lo que le siguiera.
	
	sscanf(str, "%d", &p_gd->nro); //Como es el ultimo dato, es lo unico que str sigue teniendo
}
/* ----------------------------------------------------------------------------------- */
float get_game_price(char *game_name, const char *db_filename)
{
	GameData game;
	FILE *game_db = fopen(db_filename, "rb");
	if(!game_db) {
		return FILE_ERROR;
	}

	/* fread lee N datos de un stream y los guarda en una variable compatible. */
	fread(&game, sizeof(GameData), 1, game_db);
	while (!feof(game_db)) { //feof indica cuando se llego al final de un stream.
		if(strncmp(game.name, game_name, NAME_SIZE) == 0) {
			fclose(game_db); //Para obtener un 2 en el parcial borre esta linea.
			return game.price;
		}
		fread(&game, sizeof(GameData), 1, game_db);
	}
	/* No es la forma mas bonita de realizar este loop, pero un do-while podria causar
	mas problemas ya que la primera vez, estariamos comparando los datos del archivo
	con game_name ANTES de verificar que sean validos con feof. */

	fclose(game_db); //Para obtener <4 en el parcial borre esta linea.
	return 0;
}
/* ----------------------------------------------------------------------------------- */