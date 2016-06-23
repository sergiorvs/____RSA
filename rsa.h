#ifndef RSA_H
#define RSA_H
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

typedef long _L;

class RSA
{
private:
    string alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    _L N;  //N=p*q (multiplicacion de numeros aleotorios y primos);
    _L phi_N; //phi_N=(p-1)*(q-1);
    _L clave_privada;//inversa de clave_publica mod phi_N;
    bool Primo(_L);
    _L Generar_Aleotorios(_L bits);
    void Generar_Clave(_L bits);
public:
    _L clave_publica;//Numero aleotorio coprimo con phi_N   exponente;
    RSA(_L bits);//Receptor
    RSA(_L n,_L e);//n y clave publica como parametro Emisor;
    _L mod(_L,_L);
    _L GCD(_L,_L);
    _L inversa(_L a,_L b);
    _L expo_mod(_L a,_L e,_L n);  //a^e mod n
    string cifrar_mensaje(string texto_plano);
    string descifrar_mensaje(string mensaje_cifrado);
};


#endif // RSA_H
