/*Marco_Agustin_Marcelo_42572925*/

#ifndef VECTORENTEROS_H
#define VECTORENTEROS_H

#include <iostream>

class VectorEnteros
{
	private:
		int *vec;
		size_t tam;

	public:
		VectorEnteros();
		VectorEnteros(int *ve, size_t tam);

		VectorEnteros& agregar(int *ve, size_t tam);

		VectorEnteros& operator =(const VectorEnteros& ve1);
		friend VectorEnteros operator +(VectorEnteros& ve1, VectorEnteros& ve2);
		friend VectorEnteros operator +(VectorEnteros& ve1, const int& n);
		friend std::ostream& operator <<(std::ostream& out, const VectorEnteros& vec);
};

#endif // VECTORENTEROS_H
