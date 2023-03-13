#ifndef TESTCLASE_H
#define TESTCLASE_H


class testClase
{
    public:
        testClase();
        virtual ~testClase();
        testClase(const testClase& other);
        testClase& operator=(const testClase& other);

        char * Getnombre() { return nombre; }
        int Getnum() { return num; }

    protected:
        int num;

    private:
        char * nombre;
};

#endif // TESTCLASE_H
