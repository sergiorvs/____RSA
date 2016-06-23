#include "rsa.h"


int main()
{
    RSA Receptor(256);
    string mensaje;
    ifstream lectura;
    lectura.open("claves.txt");
    _L n,e;
    lectura>>n;
    lectura>>e;
    RSA Emisor(n,e);
    /*cout<<"imprimire lo del fichero"<<endl;
    cout<<n<<" "<<e;*/
    cout<<"INGRESE MENSAJE A CIFRAR: "<<endl;
    cin>>mensaje;
    string mensaje_encriptado=Emisor.cifrar_mensaje(mensaje);
    cout<<"El mensaje cifrado es: "<<mensaje_encriptado<<endl;
    cout<<"El mensaje descifrado es: "<<Receptor.descifrar_mensaje(mensaje_encriptado)<<endl;

    return 0;
}
