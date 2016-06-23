#include "rsa.h"

//*************************Public**************************************

RSA::RSA(_L bits)
{
    Generar_Clave(bits);
}

RSA::RSA(_L n,_L e)
{
    N=n;
    clave_publica=e;
}

_L RSA::GCD(_L x,_L y)
{
    if(x>y)
    {
        _L z;
        z=x;
        x=y;
        y=z;

    }
    _L g=1;
    while((x&1)==0 && (y&1)==0)
    {
        x=x>>1;
        y=y>>1;
        g*=2;

    }
    while(x!=0)
    {
         while((x&1)==0)
         {
             x=x>>1;
         }
          while((y&1)==0)
          {
              y=y>>1;
          }
          _L t=abs(x-y)>>1;
          if(x>=y)
          {
              x=t;
          }else{y=t;}
    }
    return (g*y);
}

_L RSA::inversa(_L a,_L b)
{
    _L r1=a, r2=b , s1=1, s2=0, t1=0, t2=1;
    _L q=0,r=0,s=0,t=0;
        while(r2>0){
            q=r1/r2;
            r=r1-(q*r2);
            r1=r2;
            r2=r;

            s=s1-(q*s2);
            s1=s2;
            s2=s;

            t=t1-(q*t2);
            t1=t2;
            t2=t;
        }

        while(t1<0){
            t1=a+t1;//para que la inversa no sea negativa;
        }
        return t1;
}

_L RSA::expo_mod(_L a, _L e ,_L n)
{
    //**********Primera linea de la tabla********************
        _L r_mod_2=mod(e,2);
        _L e_cuad=a;
        _L r_mod_n=a;
        e=e>>1; ///corrimiento de bits(divicion entre dos)
        r_mod_2=mod(e,2);
    //**********El resto de las lineas*************************/
        while(e>0){
            e_cuad=mod(e_cuad*e_cuad,n); ///modulo(elevar_^2 a si mismo, N)
            if(r_mod_2==1){
                r_mod_n=mod(e_cuad*r_mod_n,n);
            }
            e=e>>1;
            r_mod_2=mod(e,2);
        }
        //cout<<endl<<r_mod_n<<endl;
        return r_mod_n;
}

string RSA::cifrar_mensaje(string mensaje)
{
    string mensaje_Cifrado;
    for(unsigned int i=0;i<mensaje.size();i++)
    {
        mensaje_Cifrado+=to_string(expo_mod(alfabeto.find(mensaje[i]),clave_publica,N));
    }
    return mensaje_Cifrado;
}

//¿Reconocer de que tamaño es un numero?
//solo descifra una letra..
string RSA::descifrar_mensaje(string mensaje_cifrado)
{
    string texto_plano;
    texto_plano+=alfabeto[expo_mod(stol(mensaje_cifrado),clave_privada,N)];

    return texto_plano;
}



//*************************Private*********************************

_L RSA::mod(_L a,_L b)
{
    _L q;
    q=a/b;
    if(a<0)
    {
        q--;
    }
    return a-b*q;
}

bool RSA::Primo(_L num)
{
    _L cont=0;
    for(_L i=1;i<=num;i++)
    {
        if(mod(num,i)==0){cont++;}
    }
    if(cont==2){return 1;}
    return 0;
}

_L RSA::Generar_Aleotorios(_L bits)
{
   // srand(time(NULL));
    return rand()%bits;
}




void RSA::Generar_Clave(_L bits)
{
    _L p;
    _L q;
    srand(time(NULL));
    do
    {
        p=Generar_Aleotorios(bits);
        cout<<p<<endl;
    }while(Primo(p)!=1);
    cout<<"p: "<<p<<endl;
    do
    {
        q=Generar_Aleotorios(bits);
    }while(!Primo(q) && q!=p);
    cout<<"q: "<<q<<endl;
    N=p*q;
    phi_N=(p-1)*(q-1);

    do
    {
        clave_publica=Generar_Aleotorios(bits);
    }while(GCD(clave_publica,phi_N)!=1);

    clave_privada=mod(inversa(phi_N,clave_publica),phi_N);

    ofstream entrada;
    entrada.open("claves.txt",ios::out);
    if(entrada.fail()){cout<<"el archivo no se abrio correctamente"<<endl;}
    else
    {
        //cout<<"Hola!!!"<<endl;
        entrada<<N<<endl<<clave_publica;
        entrada.close();
    }
}





