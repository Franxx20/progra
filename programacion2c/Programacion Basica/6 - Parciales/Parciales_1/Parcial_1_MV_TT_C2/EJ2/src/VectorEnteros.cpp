/*Marco_Agustin_Marcelo_42572925*/

#include "VectorEnteros.h"
#include <stdlib.h>

VectorEnteros::VectorEnteros()
{
	this->tam = 0;
	this->vec = new int[0];
}


VectorEnteros::VectorEnteros(int *ve, size_t tam)
{
	this->tam = tam;
	this->vec = ve;
}

VectorEnteros& VectorEnteros::agregar(int *ve, size_t tam)
{
	size_t i;
	size_t old_tam = this->tam;
	this->tam += tam;
	for(i = old_tam; i < this->tam; i++) {
		this->vec[i] = ve[i];
	}

	return *this;
}

VectorEnteros& VectorEnteros::operator =(const VectorEnteros& ve1)
{
	size_t i;
	this->tam = ve1.tam;
	this->vec = new int[this->tam];


	for(i = 0; i < ve1.tam; i++) {
		this->vec[i] = ve1.vec[i];
	}
	return *this;
}


VectorEnteros operator +(VectorEnteros& ve1, VectorEnteros& ve2)
{
	size_t i;
	VectorEnteros aux;

	aux.tam = ve1.tam + ve2.tam;
	aux.vec = new int[aux.tam];

	for(i = 0; i < ve1.tam; i++) {
		aux.vec[i] = ve1.vec[i];
	}

	for(i = 0; i < ve2.tam; i++) {
		aux.vec[i+ve1.tam] = ve2.vec[i];
	}

	return aux;
}

VectorEnteros operator +(VectorEnteros& ve1, const int& n)
{
	size_t i;
	VectorEnteros aux;

	aux.tam = ve1.tam + 1;
	aux.vec = new int[aux.tam];

	for(i = 0; i < ve1.tam; i++) {
		aux.vec[i] = ve1.vec[i];
	}

	aux.vec[i] = n;

	return aux;
}


std::ostream& operator <<(std::ostream& out, const VectorEnteros& vec)
{
	size_t i;

	out << "[";
	for(i = 0; i < vec.tam; i++) {
		out << vec.vec[i] << ", ";
	}
	out << "]";

	return out;
}
