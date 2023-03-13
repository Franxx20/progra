#ifndef CLASE1_H
#define CLASE1_H

class Clase1
{
	private:
		int valor1;
	public:
		Clase1(int valor = 0);
		virtual ~Clase1();
		virtual int getValo1() = 0;
};

#endif // CLASE1_H
