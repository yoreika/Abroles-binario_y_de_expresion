#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>

using namespace std;
int cont=0;
typedef struct nodo *auxNodo;
int numNodos = 0; // nummero de nodos del arbol ABB
int numK = 0, k;     //  nodos menores que un numero k ingresado
/*---------  Estructura del arbol  -------*/
typedef struct nodo{
     int nro;
     struct nodo *izq, *der;
}*ABB;



//-----Declaración de funciones
void limpiar(char[],int), pasar(char[],char[]),
     conv_pre(char[],char[]), conv_pos(char[],char[]),
     rec_exp(char[]), inver(char[],char[]);
int verif(char[]), tama(char[]), sim(char),
    prio(char,char);

//-----Variables globales
char Simb[4][2]={{'(',')'},{'/','*'},{'-','+'},{'^','\0'}},
     expr[50], pila[50], expr_c[50], epre[50], epos[50],
     elem, simb;
int i, j, n, tope, val, cont1, cont2, v;

//-----Inicio del programa
iniciar(){
system("cls");
  limpiar(expr,50);
  limpiar(pila,50);
  limpiar(expr_c,50);
  limpiar(epre,50);
  limpiar(epos,50);
  fflush(stdin); 
   printf("Introduzca la ecuacion: ");
  for(i=0;(expr[i]=getchar())!='\n';++i);
  inver(expr_c,expr);
  conv_pre(expr_c,epre);
  printf("\n la ecuacion Prefija es: %s \n\n",epre);
  pasar(expr_c,expr);
  conv_pos(expr_c,epos);
  printf("\n la ecuacion Posfija es:  %s ",epos);
  int x, y, a, b;
   
  	for(a=0; a<strlen(expr); a++){
		        for(b=0;b<strlen(epre);b++){
		     	if (expr[a]==epre[b]){
		     		int kk=0;
		     		initwindow(800,800);//creating line
		     		setcolor(YELLOW);
		     		circle(100+kk,50+kk,20);	 // hacer circulos
                    outtextxy(98+kk,50+kk,expr); // imprecion de frase
					kk=50;	
		        }
	            }
           }
  system("pause");
  
}

//-----Limpia la variable
void limpiar(char a[], int n){
  for(i=0;i<n;i++){
    a[i]='\0';
  }
}

//-----Pasa de una variable a otra
void pasar(char a[], char b[]){
  int n1, n2;
  n1=tama(a);
  n2=tama(b);
  if(n1>n2){
    for(i=0;i<n1;i++){
      a[i]=b[i];
    }
  }
  if(n1<n2){
    for(i=0;i<n2;i++){
      a[i]=b[i];
    }
  }
}

//-----Cuenta cuantos caracteres hay en la variable
int tama(char var[]){
  for(n=0;var[n]!='\0';++n);
  return(n);
}

//-----Verifica si no le faltan paréntesis a la función
int verif(char ex[]){
  val=0;
  n=tama(ex);
  if(n>0){
    tope=0;
    cont1=cont2=0;
    for(i=0;i<n;i++){
      elem=ex[i];
      if(elem=='('){
        pila[tope]=elem;
        tope+=1;
        pila[tope]='\0';
      }
      else{
        if(elem==')'){
          if(tope>0){
            if(pila[tope-1]=='('){
              tope-=1;
              pila[tope]='\0';
            }
          }
          else{
            pila[tope]=elem;
            tope+=1;
            pila[tope]='\0';
          }
        }
      }
    }
    if(tope>0){
      for(i=0;i<tope;i++){
        if(pila[i]=='('){
          cont1+=1;
        }
        if(pila[i]==')'){
          cont2+=1;
        }
      }
      if(cont1<cont2){
        val=2;
      }
      if(cont1>cont2){
        val=1;
      }
    }
    else{
      val=3;
    }
  }
  else{
    val=0;
  }
  return(val);
}

//-----Conversión de la función a prefija
void conv_pre(char ex[], char epre[]){
  char expre[50];
  limpiar(expre,50);
  conv_pos(ex,expre);
  inver(epre,expre);
}

//-----Conversión de la función a postfija
void conv_pos(char ex[], char epos[]){
  tope=-1;
  n=tama(ex);
  while(ex[0]!='\0'){
    simb=ex[0];
    rec_exp(ex);
    n-=1;
    if(simb=='('){
      tope+=1;
      pila[tope]=simb;
    }
    else{
      if(simb==')'){
        while(pila[tope]!='('){
          int x=tama(epos);
          epos[x]=pila[tope];
          pila[tope]='\0';
          tope-=1;
        }
        pila[tope]='\0';
        tope-=1;
      }
      else{
        if(sim(simb)==0){
          int x=tama(epos);
          epos[x]=simb;
        }
        else{
          if(tama(pila)>0){
            while(prio(simb,pila[tope])<=0){
              int x=tama(epos);
              epos[x]=pila[tope];
              pila[tope]='\0';
              tope-=1;
              if(tope<0){
                break;
              }
            }
          }
          tope+=1;
          pila[tope]=simb;
        }
      }
    }
  }
  while(tope>=0){
    int x=tama(epos);
    epos[x]=pila[tope];
    pila[tope]='\0';
    tope-=1;
  }
}

//-----Recorre los caracteres un lugar
void rec_exp(char a[]){
  int x=tama(a);
  for(i=0;i<(x-1);i++){
    a[i]=a[i+1];
  }
  a[i]='\0';
}

//-----Verifica si es un operador
int sim(char s){
  v=0;
  for(i=0;i<4;i++){
    for(j=0;j<2;j++){
      if(s==Simb[i][j]){
        v=1;
      }
    }
  }
  return(v);
}

//-----Verifica la prioridad para colocar en la pila
int prio(char s1, char s2){
  int p1, p2;
  p1=p2=0;
  for(i=0;i<4;i++){
    for(j=0;j<2;j++){
      if(s1==Simb[i][j]){
        p1=i;
      }
      if(s2==Simb[i][j]){
        p2=i;
      }
    }
  }
  if(p1<p2){
    i=-1;
  }
  else{
    if(p1==p2){
      i=0;
    }
    else{
      i=1;
    }
  }
  return(i);
}

//-----Invierte la función completa
void inver(char a[], char b[]){
  int x=tama(b);
  n=0;
  for(i=(x-1);i>=0;i--){
    simb=b[i];
    if(simb==')'){
      a[n]='(';
    }
    else{
      if(simb=='('){
        a[n]=')';
      }
      else{
        a[n]=simb;
      }
    }
    n++;
  }
}



/* ---------- Estructura de la cola ---------*/
int Vacio(ABB r){
   return r==NULL;
}
struct nodoCola{
    ABB ptr;
    struct nodoCola *sgte;
};
struct cola{

    struct nodoCola *delante;
    struct nodoCola *atras;
};
void presentacion() //presentacion del estudiante
{
     system("cls");
     system("color f9");   // poner color a la consola
     cout << "\n\t\t   UNIVERSIDAD TECNOLOGICA DE PANAMA \n\n";
     cout << "\t FACULTAD DE INGENIERIA  DE SISTEMAS COMPUTACIONALES  \n\n";
     cout << "\t            ESTRUCTURA DE DATOS II  \n";
     cout << "\t                   PROYECTO I   \n\n\n";
     cout << "\t         PROFESOR: NICHOLAS BELIZ OSORIO   \n\n";
     cout << "\t         INTEGRANTE: YOREIKA PONCE  \n\n\n";
     cout << "\t                 II SEMESTRE\n";
     system("pause");  // hacer pausa y presionar una tecla para continuar

}
void menu1() // menu principal
{
     //system("cls");   // para limpiar pantalla
     cout << endl;
     cout << "\t___________________________________________\n";
     cout << "\t      PROYECTO I    \n\n\n";
     cout << "\t    YOREIKA PONCE      \n\n";
     cout << "\t [1]arbol binario general  \n";
     cout << "\t [2]arbol de expresion \n";
     cout << "\t___________________________________________\n";
     cout << "\n\t     Opcion :  ";
}
void menu2() // menu de arbol binario
{
     system("cls");   // para limpiar pantalla
     cout << endl;
     cout << "\t___________________________________________\n";
     cout << "\t   ARBOL BINARIO GENERAL \n\n\n";
     cout << "\t      YOREIKA PONCE        \n\n";
     cout << "\t [1]ingrese un numero       \n";
     cout << "\t [2]eliminar un numero      \n";
     cout << "\t [3]informacion del arbol   \n";
     cout << "\t [4]informacion de un nodo  \n";
     cout << "\t [5]ver el arbol            \n";
     cout << "\t [6]recorridos              \n";
     cout << "\t [7]atras                   \n";
     cout << "\t___________________________________________\n";
     cout << "\n\t     Opcion :  ";
}
void menu3() // menu de arbol de expresion
{
     system("cls");   // para limpiar pantalla
     cout << endl;
     cout << "\t___________________________________________\n";
     cout << "\t   ARBOL DE EXPRESION    \n\n\n";
     cout << "\t      YOREIKA PONCE        \n\n";
     cout << "\t [1]ingrese una expresion    \n";
     cout << "\t [2]ver arbol                \n";
     cout << "\t [3]recorridos               \n";
     cout << "\t [4]atras                    \n";
     cout << "\t___________________________________________\n";
     cout << "\n\t     Opcion :  ";
}
void inicializaCola(struct cola &q)
{
    q.delante = NULL;
    q.atras = NULL;
}
void encola(struct cola &q, ABB n)
{
     struct nodoCola *p;
     p = new(struct nodoCola);
     p->ptr = n;
     p->sgte = NULL;
     if(q.delante==NULL)
         q.delante = p;
     else
         (q.atras)->sgte = p;
     q.atras = p;
}
ABB desencola(struct cola &q)
{
    struct nodoCola *p;
    p = q.delante;
    ABB n = p->ptr;
    q.delante = (q.delante)->sgte;
    delete(p);
    return n;
}
ABB crearNodo(int x)
{
     ABB nuevoNodo = new(struct nodo);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}
void insertar(ABB &arbol, int x)
{
     if(arbol==NULL){
           arbol = crearNodo(x);
           cout<<"\n\t  Insertado..!"<<endl<<endl;
     }
     else if(x < arbol->nro)
          insertar(arbol->izq, x);
     else if(x > arbol->nro)
          insertar(arbol->der, x);
}
void preOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          cout << arbol->nro <<" ";
          preOrden(arbol->izq);
          preOrden(arbol->der);
     }
}
void enOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          cout << arbol->nro << " ";
          enOrden(arbol->der);
     }
}
void postOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          enOrden(arbol->der);
          cout << arbol->nro << " ";
     }
}
ABB unirABB(ABB izq, ABB der)
{
    if(izq==NULL) return der;
    if(der==NULL) return izq;

    ABB centro = unirABB(izq->der, der->izq);
    izq->der = centro;
    der->izq = izq;
    return der;
}
void elimina(ABB &arbol, int x)
{
     if(arbol==NULL){
         cout <<"no existe el nodo"<<endl; 
	     return;}
      if(x<arbol->nro)
         elimina(arbol->izq, x);
     else if(x>arbol->nro)
         elimina(arbol->der, x);
     else if(x==arbol->nro) {
         ABB p = arbol;
         arbol = unirABB(arbol->izq, arbol->der);
         delete p;
		  cout<<"eliminado"<<endl;
		 }    
}
void verArbol(ABB arbol, int n)
{
     if(arbol==NULL)
          return;
     verArbol(arbol->der, n+1);

     for(int i=0; i<n; i++)
         cout<<"       ";

     numNodos++;
     cout<< arbol->nro <<endl;

     verArbol(arbol->izq, n+1);
}
int nivelAB(ABB arbol)
{
    int AltIzq, AltDer;

    if(arbol==NULL){
    return 0;
	}
    else
    {
        AltIzq = nivelAB(arbol->izq);
        AltDer = nivelAB(arbol->der);

        if(AltIzq>AltDer)
            return AltIzq+1;
        else
            return AltDer+1;
    }
}
int contarHojas(ABB arbol)
{
        if (arbol==NULL)
        {
         return 0;
        }
        if ((arbol->der ==NULL)&&(arbol->izq ==NULL))
        {
         cout<<arbol->nro<<" ";

        }
        else
        {
		return 	contarHojas(arbol->izq) + contarHojas(arbol->der);
        }
}
void bus_hijos(ABB arbol, int dato)
{

     if(arbol==NULL)
       
	   return ;

     if(dato<arbol->nro){
     	bus_hijos(arbol->izq, dato);
	 }
     else if(dato> arbol->nro)
         bus_hijos(arbol->der, dato);

     else {

     if ((arbol->der ==NULL)&&(arbol->izq ==NULL)){
         cout<<"hijo izquierdo null"<<endl;
         cout<<"\t\t\t\t hijo derecho null"<<endl;
         }
     else if ((arbol->der ==NULL)&&(arbol->izq !=NULL)){
     	arbol=arbol->izq;
    	cout<<"hijo izquierdo "<< arbol->nro<<" "<<endl;
        cout<<"\t\t\t\t hijo derecho null"<<endl;
         }
	 else if ((arbol->der !=NULL)&&(arbol->izq ==NULL)){
       	cout<<"hijo izquierdo null"<<endl;
       	arbol=arbol->der;
         cout<<"\t\t\t\t hijo derecho "<<arbol->nro<<" ";
		 }
       else if ((arbol->der !=NULL)&&(arbol->izq !=NULL)){
       	arbol=arbol->izq;
         cout<<"hijo izquierdo "<< arbol->nro<<" ";
         arbol=arbol->der;
         cout<<"\t\t\t\t hijo derecho "<<arbol->nro<<" ";
         }
         }

}
void camino(ABB arbol, int dato)
{

     if(arbol==NULL)
      return ;
     if(dato<arbol->nro){
     cout<<arbol->nro<<" ";
     cont++;
     camino(arbol->izq, dato);
	 }

     else if(dato> arbol->nro){
     cout<<arbol->nro<<" ";
     cont++;
      camino(arbol->der, dato);
	 }

     else if(dato==arbol->nro){
     cout<<arbol->nro<<" ";
     cont++;
	 }

}
int bus_padre(ABB arbol, int dato)
{
 int padre=0;

   while(!Vacio(arbol))
   {
      if(dato==arbol->nro)
         {
             return padre; // dato encontrado  (2)
         }
      else if(dato<arbol->nro)
        {
            padre=arbol->nro;
            arbol= arbol->izq;  // (3)
        }
      else if(dato>arbol->nro)
        {
          padre=arbol->nro;
          arbol= arbol->der; // (4)
        }
}
   cout << " El nodo no existe  ";
   return 0; // No esta en arbol (1)
}
int bus_hermano(ABB arbol, int dato)
{
   auxNodo aux;
   int hermano=0;
   int padre =bus_padre(arbol,dato);

         if(arbol==NULL){
         return 0;}

         else if(padre <arbol->nro)
         {
         arbol = arbol->izq;  // (3)
         }
         else if(padre >arbol->nro)
         {
         arbol =arbol->der; // (4)
         }


       if(padre == arbol->nro)
        {
        while(arbol!=NULL)
        {
        if(dato==arbol->nro)
        {
        return hermano; // dato encontrado  (2
        }
         else if(dato<arbol->nro)
        {
        aux = arbol->der;
         if (aux!=NULL)
         {
                        hermano = aux->nro;  // (3)
                    }
                    else
                    {
                        return 0;
                    }
                    arbol = arbol->izq;
                }
             else if(dato > arbol->nro)
                {
                    aux = arbol->izq;
                    if (aux!=NULL)
                    {
                        hermano = aux->nro;
                    }
                    else
                    {
                        return 0;
                    }
                    arbol= arbol->der; // (4)
                }
             }
         }

   return 0; // No esta en arbol (1)
   }
void grado(ABB arbol, int dato)
{

     if(arbol==NULL)
       cout<<"arbol vacio"<<endl;
     if(dato<arbol->nro)
     	grado(arbol->izq, dato);
     else if(dato> arbol->nro)
         grado(arbol->der, dato);
     else {
     if ((arbol->der ==NULL)&&(arbol->izq ==NULL))
         cout<<"grado 0"<<endl;
     else if ((arbol->der ==NULL)&&(arbol->izq !=NULL))
         cout<<"grado 1 "<<endl;
	 else if ((arbol->der !=NULL)&&(arbol->izq ==NULL))
       	 cout<<"grado 1"<<endl;
     else if ((arbol->der !=NULL)&&(arbol->izq !=NULL))
         cout<<"grado 2 "<<endl;
}

}


int main()
{

	
	ABB arbol = NULL;
	int hermano=0;
    int nivel=0 ;
	int x, y, a, b;
    int *hijo=0;
    int dato;
    int salir=0;
    int m=0;
    int op, op2;
	int op_1; // opcion del menu 1 principal
	int op_2; //opcion del menu 2 arbol binario general
	int op_3; // opcion del menu 3 arbol de expresion
    presentacion(); // impresion de la presnetacion
    system("cls"); //limpiamos la pantalla
    system("color f9");   // poner color a la consola

do{     // inicio del ciclo do
     system("cls"); //limpiamos la pantalla
     menu1();// impresion del menu 1
	 cin>> op_1;  // lectua del op_1
     cout << endl;	// salto de linea
     switch(op_1) //inicio del switch
     {


case 1:
      	do{
     	system("cls"); //limpiamos la pantalla
        menu2(); // impresion del menu 2
     	cin>> op_2;  // lectua del op_1
        cout << endl;	// salto de linea
        switch(op_2){
          	case 1:
          		    cout << " Ingrese valor   : ";  cin>> x; // leyendo valor para insertar en el arbol
                    insertar( arbol, x);                   // llamando a la funcion insertar en arbol
                    system("pause");                       // hacer pausa y presionar una tecla para continuar
                    break;
          	case 2:
          		    cout<<" Valor a eliminar  : "; cin>> x; // leyendo el valor a eliminar
                    elimina(arbol, x);                     // llamndo a la funcion eliminar
                    system("pause");                       // hacer pausa y presionar una tecla para continuar
                    break;
          	case 3:
                    nivel = nivelAB(arbol);                    // guarda el valor del nivel
                    cout << " la altura es    : "<< nivel-1;  // la altura es nivel- 1
                    cout << "\n nodos hojas   : "; contarHojas(arbol);
                    cout << "\n nivel         : "<<nivel;
                    cout << "\narbol lleno o completp :";
                    cout <<endl;
                    system("pause");                         // hacer pausa y presionar una tecla para continuar
                    nivel=0;
                    break;
          	case 4:
          		   cout << "\n ingrese el nodo a buscar : ";  cin>> dato;          // nodo a buscar
          	       cout << "\n camino para llegar       : ";  camino(arbol,dato);  // camino para llegar a ese nodo
          	       cout << "\n longitud del camino      : "<<cont-1<<" ";
          	       cout << "\n grado del nodo           : ";grado(arbol,dato);
          	       cout << "\n hijo                     : ";bus_hijos(arbol,dato);      // hijos del nodo buscado
          	       cout << "\n padre                    : "<<bus_padre(arbol,dato)<<endl;
                   cout << "\n hermano                  : "<<bus_hermano(arbol,dato)<<endl;
          	       system("pause");  // hacer pausa y presionar una tecla para continuar
          	       break;
          	case 5:
          		   verArbol(arbol, 0);
          		   system("pause");  // hacer pausa y presionar una tecla para continuar
                   break;
          	case 6:
          		cout<<" in_orden  :";
          		enOrden(arbol);      // llamando a la funcion enorden
          		cout << endl;
          		cout<<" pre_orden :";
          		preOrden(arbol);      // llamando a la funcion preorden
          		cout << endl;
          		cout<<" pre_orden :";
          		postOrden(arbol);      // llamando a la funcion postorden
          		cout << endl;
          		system("pause");  // hacer pausa y presionar una tecla para continuar
          		break;
          	case 7:
          		break;
          	default: cout << "Ingrese una opcion valida\n";
                break;	
                system("pause");  // hacer pausa y presionar una tecla para continuar
            	} // fn switch
           
	             }while(op_2!=7); // fin do
	           system("pause");
   break;      
case 2:
iniciar();
break;  

}//fin switch
} while(op_1<3); // fin del do
cout << "\t_________________  GRACIAS _________________________\n";
}






