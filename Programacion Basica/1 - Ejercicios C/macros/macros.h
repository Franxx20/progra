#define ABS(x)    			(x) >= 0? (x) : (x) * (-1)
#define PARTE_ENTERA(x) 	   	(int)(x)
#define PARTE_DECIMAL(x)		ABS((x) - PARTE_ENTERA(x))
#define REDONDEO(x)			(PARTE_DECIMAL(x) >= 0.5)? \
					(PARTE_ENTERA(x) + 1) : PARTE_ENTERA(x)

#define ESNUMERO(n)			((n) >= '0' && (n) <= '9')
#define ESMAYUS(A)			((A) >= 'A' && (A) <= 'Z')
#define ESMINUS(a)			((a) >= 'a' && (a) <= 'z')
#define ESLETRA(a)			(ESMAYUS(a) || ESMINUS(a))

#define AMAYUS(a)			(ESMINUS(a)? ((a) - 32) : (a))
#define AMINUS(A)			(ESMAYUS(A)? ((A) + 32) : (A))
