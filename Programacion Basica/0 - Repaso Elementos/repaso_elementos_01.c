/* De esta forma incluimos bibliotecas en nuestro programa,
 es ideal solo incluirlas en el archivo que las utiliza. */
#include <stdio.h>


/* Las macros son porciones de codigo que se copian en donde 
 han sido llamadas durante la compilacion. */
#define MAX_SIZE 			27 //Puden ser una simple constante,
#define print_array(X,Y)	printf("(%d;%d)\n", X, Y) //O una linea de codigo (falta un tipo mas que se incluye en la parte 2).


/* El encabezado de una funcion esta compuesto por:
tipo_que_devuelve nombre_de_funcion (tipo_de_argumento nombre_de_argumento, ...) */
int main() { //Debe existir una funcion llamada main que retorne un int para que funcione el programa.
	
	/* Las variables son declaradas como:
	tipo nombre = valor_asignado; */
	char c = 'A';
	float f; //Aunque tambien pueden asignarse despues de ser declaradas.
	int i, n = 4; //Se pueden declarar multiples variables del mismo tipo en una linea.

	/* Las arrays(vectores) son declarados igual que una variable pero seguidos con [] indicando su tamaño. */
	int array[16]; //Pueden ser NO inicializadas en la declaracion (contienen basura),
	int array_2[9] = {0}; //Inicializadas en 0 para todos sus elementos,
	int array_3[6] = {1,2}; //Inicializadas en 1 y 2 para sus dos primeros elementos y 0 para el resto,
	int array_4[3] = {1,2,3}; //O inicializar todos sus elementos.

	/* En C, strings(cadenas) son una array de tipo char. */
	char string[] = "Hola mundo"; //El tamaño puede ser calculado durante la compilacion en base a 
								  //la cantidad de elementos incluidos (En este caso seria 11, 10 por la cadena y 1 por el caracter nulo '\0')
	char string_2[4+1] = {'H','o','l','a','\0'};

	printf("Comienza el programa.\n"); //\n indica un salto de linea


	int late_var; //Las variables solo pueden ser declaradas al principio de un bloque.
	/* A que nos referimos con un bloque?
	Bloque le decimos al rango que tiene una variable de validez, ejemplo: */
	{	//Importante atencion a los {}, ya que son esto los que definen el rango del bloque.
		int h = 7; //Se crea la variable h.
		printf("h vale: %d\n", h); //Se utiliza la variable h.
	} //La variable h se destruye.
	printf("h vale: %d\n", h); //NO COMPILA, la variable h ya no existe en este bloque(rango).

	/* Si bien el ejemplo anterior no funciona, late_var no va a tener problemas en funcionar,
	asi que porque no se puede declarar despues de usar una funcion?
	Porque en Programacion se corrige en base al compilador de C ISO C90, tambien conocido como
	ANSI C, creado en 1989, y en este tiempo el compilador de C no era capaz de poder crear una variable
	en el medio(o final) del bloque.
	Tampoco soportaba comentarios con // o arrays de valores dinamicos definidos por un vector, 
	como var_int[tam], siendo tam una variable con valor definido durante runtime(tiempo de ejecucion). */


	/* Loops, empezemos por for:
	(inicializamos la variable que itera; condicion para terminar la iteracion; incrementamos o decrementamos la variable)
	la variable no puede ser creada en el for, debe ser creada al principio del bloque. */
	for(i = 0; i < 3; i++) {
		print_array(i, array_4[i]); //En las macros no se incluye el ; porque se agrega en cuanto se usan.
	}

	for(i = 0; i < MAX_SIZE && n < 20; i++, n++) { //Tambien pueden agregarse multiple variables en cada parametro separados por una coma
		array[i] = n;							   //O condiciones con los operadores logicos and(&&) y or(||).
	}

	/* while solo requiere una condicion para terminar. */ 
	while(c != 'F') {
		if(n < 10) {
			break; //Tambien podemos salir del loop temprano con break.
		}
		c++; n--;
	}
	printf("Valor de c y n despues del while\n");
	printf("c: %c, n: %d\n", c, n);

	/* do-while primero realiza el codigo y luego verifica la condicion. */
	do {
		n++;
		if(n > 40) {
			c++;
			continue; //Omite la actual iteracion y continua con la siguiente.
		}
	} while(n != 45 && c < 'Z');
	printf("Valor de c y n despues del do-while\n");
	printf("c: %c, n: %d\n", c, n);
	
	return 0; //Main debe siempre devolver un 0 al final si todo funciono correctamente.
}