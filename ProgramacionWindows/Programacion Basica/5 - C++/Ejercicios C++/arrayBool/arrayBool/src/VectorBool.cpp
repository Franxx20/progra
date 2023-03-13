#include "VectorBool.h"

VectorBool::VectorBool(unsigned bytes):bytes(bytes)
{
	vec = new bool[bytes];
}

VectorBool::VectorBool(const VectorBool& v1):bytes(v1.bytes)
{
	vec = new bool[bytes];
	for(unsigned i = 0; i < bytes; i++) {
		vec[i] = v1[i];
	}
}

VectorBool::~VectorBool()
{
	delete []vec;
}

bool& VectorBool::operator [](const int pos) const
{
	return this->vec[pos];
}

VectorBool& VectorBool::operator =(const VectorBool& otherVec)
{
	if(bytes != otherVec.bytes) {
		delete []vec;
		bytes = otherVec.bytes;
		vec = new bool[bytes];
	}

	for(unsigned i = 0; i < bytes; i++) {
		vec[i] = otherVec[i];
	}

	return *this;
}

VectorBool VectorBool::operator &(const VectorBool& otherVec)
{
	if(bytes != otherVec.bytes) {
		throw std::length_error("Error en tamaños");
	}

	VectorBool aux(bytes);

	for(unsigned i = 0; i < bytes; i++) {
		aux[i] = otherVec[i] && vec[i];
	}

	return aux;
}

std::ostream& operator <<(std::ostream& out, const VectorBool& vec)
{
	unsigned i;
	out << "[";
	for(i = 0; i < vec.bytes-1; i++) {
		out << vec[i] << ", ";
	}
	out << vec[i] << "]";

	return out;
}
