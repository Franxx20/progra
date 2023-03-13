#ifndef VECTORBOOL_H
#define VECTORBOOL_H

#include <iostream>

class VectorBool
{
	private:
		bool *vec;
		unsigned bytes;

	public:
		VectorBool(unsigned bytes = 0);
		VectorBool(const VectorBool& v1); ///Remueve deprecated error
		~VectorBool();

		bool& operator [](const int pos) const;
		VectorBool& operator =(const VectorBool& otherVec);
		VectorBool operator &(const VectorBool& otherVec);
		friend std::ostream& operator <<(std::ostream& out, const VectorBool& vec);
};

#endif // VECTORBOOL_H
