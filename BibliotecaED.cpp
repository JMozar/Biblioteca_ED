#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <windows.h>
#define color SetConsoleTextAttribute
using namespace std;
fstream Esc;
fstream Lec;

string nombre;
int libPres=0;
int codU;
int codigoEst;
float pond;

struct solicitud{
	//int  codLibro;
	char nom[15];
	int  codAlumno;
	float pond;
	bool tipo;	
	struct solicitud *sgte;
	struct solicitud *ante;
};
typedef struct solicitud *TpListaSol;

struct usuario{
	string nombre;
	int libPres, cod;
	float pond;
}; usuario estudiante[10084];

struct nodoL{
	char nom[15], mat[15];
	bool est;
	struct nodoL *sgte;
	struct nodoL *hij;
};
typedef struct nodoL *TpListaL;

TpListaSol crearNodoSol(char tipo[]){
	TpListaSol nuevoS=NULL;	
	srand(time(NULL));
	nuevoS=new(struct solicitud);
	cout<<endl;
	nuevoS->codAlumno=codigoEst;
	nuevoS->pond=pond;
	//nuevoS->nom = tipo;
	strcpy(nuevoS->nom,tipo);
	nuevoS->sgte=NULL;
	nuevoS->ante=NULL;
	return nuevoS;
}

TpListaL crearNodoL(){
	int e;
	TpListaL nuevo=NULL;
	nuevo=new(struct nodoL);
	
	system("cls");

	cout<<"********************************************************";
	cout<<"\n\t\t  SISTEMA DE BIBLIOTECA\n";
	cout<<"********************************************************\n\n";
	cout<<"Ingresar nombre --->";cin>>nuevo->nom;
	if(e==1) nuevo->est=true;
	else nuevo->est=false;
	nuevo->sgte=NULL;
	nuevo->hij=NULL;
	return nuevo;
}

void crearNodoPadre(TpListaL &nodoP){
	int e;	
	cout<<"Ingresar materia--->";cin>>nodoP->mat;
	
	cout<<"Ingrese el estado"<<endl;
	cout<<"1 = Muy solicitado / 0 = Poco solicitado --->";cin>>e;
	if(e==1) nodoP->est=true;
	else nodoP->est=false;
	
	//nodoP->est=false; //falso prederteminado, borra y descomenta las lineas de arriba
}

void copyL(TpListaL padre, TpListaL &hijo){
	strcpy(hijo->mat, padre->mat);
	hijo->est = padre->est;
}

TpListaL buscarL(TpListaL &libros, char tip[]){
	TpListaL p=libros, n=NULL;
	
	if(libros == NULL)
		return p;
		
	else{		
		while(p->sgte != NULL){	
			if(strcmp(tip,p->nom)==0){	
				if(p->hij==NULL){
					return n;
				}
				else{
					return p;
				}		
			}	
			p=p->sgte;
		}
		if(strcmp(tip,p->nom)==0){
			if(p->hij==NULL){
				return n;
			}
			else{
				return p;
			}	
		}
	}
	return n;
}

void agregarHijo(TpListaL nuevo, TpListaL &p){
	if(p->hij == NULL)
	p->hij=nuevo;
			
	else{
		while(p->hij!=NULL){
			p=p->hij;						
		}
		p->hij=nuevo;			
	}
}

//agrega un nodo libro al final de una lista simple
void librosPrestados(TpListaL &lista, TpListaL extraido){
	TpListaL nuevo=NULL,p=lista;
	//creamos nuevo nodo
	nuevo=extraido;

	//ir al final de la lista

	if(lista == NULL){
		lista = nuevo;
	}else{
		while(p->sgte!=NULL){
			p=p->sgte;
		}
		p->sgte=nuevo;
	}
	
};

//ver libros prestados en lista simple
void verListaLibrosPrestados(TpListaL p){
	cout<<"========================================================";
	cout<<"\n>>>>>>>>>          LIBROS PRESTADOS          <<<<<<<<<"<<endl;
	cout<<"========================================================"<<endl;
	cout<<" Nombre Libro\t\t\tMateria"<<endl;
	cout<<"========================================================"<<endl;
	int i=0;
	while(p!=NULL){
		cout<<" "<<i+1<<")"<<p->nom<<"\t\t\t"<<p->mat<<endl;
		p=p->sgte;
		i++;
	}
	cout<<endl;
}
	

void InsertaFinalSol(TpListaSol &lista, char tip[]){
	TpListaSol nuevo=NULL, p=lista;
	nuevo=crearNodoSol(tip);	
		if(lista == NULL)
		lista = nuevo;
	else{
		while(p->sgte != NULL)
				p=p->sgte;
		p->sgte = nuevo;
		nuevo->ante =p;		
	}	
}

void encolarL(TpListaL &libros){
	TpListaL nuevo=NULL, p=libros;
	nuevo=crearNodoL();

	if(libros == NULL){
		crearNodoPadre(nuevo);
		libros = nuevo;
	}
		
	else{		
		while(p->sgte != NULL){	
			if(strcmp(nuevo->nom,p->nom)==0){	
				copyL(p,nuevo);
            	agregarHijo(nuevo, p);
			
				return;
			}	
			p=p->sgte;
		}
		if(strcmp(nuevo->nom,p->nom)==0){
			copyL(p,nuevo);	
            agregarHijo(nuevo, p);
			
			return;
		}
		crearNodoPadre(nuevo);		
		p->sgte =nuevo;
	}	
}

void eliminarInicio(TpListaSol &lista){
	TpListaSol t=lista;
	// Si se tiene un solo nodo en la lista
	
	if(t->sgte == NULL ){
		lista = NULL;
	}
	else{
		t->sgte->ante =NULL;
		t = t->sgte;
	}
	//cout<<"Realizado correctamente"<<endl;
	delete(t);
}

void encolar(TpListaSol &cola, char tip[]){
	TpListaSol nuevo = NULL, p = cola;
	nuevo = crearNodoSol(tip);
	//ir al final de la ista
	
	if(cola == NULL)
		cola = nuevo;
	else{
		while(p->sgte != NULL)
			p=p->sgte;
		p->sgte =nuevo;	
		
	}	
}

void desencolar(TpListaSol &cola){
	TpListaSol t=cola;
	cola=cola->sgte;
	cout<<"\nSolicitud eliminado es "<<t->nom<<endl<<endl;
	delete(t);
}

void verListaSol(TpListaSol lista){
	int i=0;
	cout<<"========================================================";
	cout<<"\n>>>>>>>>>             SOLICITUDES             <<<<<<<<<"<<endl;
	cout<<"========================================================"<<endl<<endl;
	cout<<"   CodAlumno   -  titLibro   -  Pond "<<endl<<endl;
	while( lista != NULL){
		cout<<" "<<i+1<<") "<<lista->codAlumno<<"---------"<<lista->nom<<"---------"<<lista->pond<<endl;		
		lista=lista->sgte;
		i++;
	}
	cout<<endl;
}

TpListaSol primeraSol(TpListaSol lista){
	TpListaSol tmp=lista;
	if(tmp != NULL){
		return tmp;
	}else{
		return NULL;
	}
	
}

void verLibrosI(TpListaL p){
    TpListaL temp=NULL;
    
	while( p != NULL){
		temp = p;

		cout<<p->nom<<"("<< p->mat<< ")";
		
		if(temp->hij != NULL){
		   	temp=temp->hij;	    
			while( temp != NULL){
				cout<<" --> "<<temp->nom<<"("<< temp->mat<< ")";
				temp=temp->hij;	
	        }
		}
		
		cout<<endl;
		p=p->sgte;
	}
}

TpListaL sacarLibro(TpListaL &libros){
	TpListaL p=libros, l=NULL;
	
	if(p->hij == NULL){
		cout<<"Error libreria vac�a"<<endl;
		return l;
    }
    
	else{
		while(p->hij!=NULL){
			l=p;
			p=p->hij;							
		}
		l->hij=NULL;
		cout<<"\nNodo extraido es --> "<<p->nom<<"("<< p->mat<< ")"<<endl;
		p->hij = NULL;		
	}
	
	return p;	
}

TpListaL popLibro(TpListaL &libros, char tip[]){
	TpListaL p=libros;

	if(libros == NULL)
		return p;
	else{		
		while(p->sgte != NULL){	
			if(strcmp(tip,p->nom)==0){		
				return sacarLibro(p);	
			}	
			p=p->sgte;
		}
		if(strcmp(tip,p->nom)==0){
			return sacarLibro(p);	
		}		
	}	
}

void ordenarBurbujaSol(TpListaSol lista){	
    TpListaSol actual = lista , siguiente=NULL;
    int aux1,aux2;
	char aux3[15];
    
    while(actual->sgte != NULL){
        siguiente = actual->sgte;
        while(siguiente!=NULL){
            if(actual->pond < siguiente->pond){
                  //ordenar Promedios
				aux1 = siguiente->pond;
				siguiente->pond = actual->pond;
				actual->pond = aux1;
				
				aux2 = siguiente->codAlumno;
				siguiente->codAlumno= actual->codAlumno;
				actual->codAlumno = aux2;
				
				//aux3 = siguiente->nom;
				strcpy(aux3,siguiente->nom);
				//siguiente->codLibro= actual->codLibro;
				strcpy(siguiente->nom,actual->nom);
				//actual->codLibro = aux3;
				strcpy(actual->nom,aux3);
    
            }
            siguiente = siguiente->sgte;                    
        }    
        actual = actual->sgte;
        siguiente = actual->sgte;           
    }    
}

//FUNCIONES DE ARCHIVOS

//funcion que trae los datos de un alumno desde el .txt
bool login(fstream &Lec){
	Lec.open("Estudiantes.txt", ios::in);
	string nom,codigo,prome,codigoAux;
	bool encontrado = false;
			
	cout<<"Digite su codigo: ";
	cin>>codigoAux;
	
	Lec>>nom;
	while(!Lec.eof() && !encontrado){
		Lec>>codigo;
		Lec>>prome;
		if(codigo==codigoAux){
			
			cout<<"Nombre---"<<nom<<endl;
			cout<<"Codigo"<<codigo<<endl;
			cout<<"Promedio--"<<prome<<endl;
			
			//asignamos los datos a las variables globales
			
    		stringstream promefloat(prome);promefloat>>pond;
			nombre=nom;
			stringstream codint(codigo);codint>>codigoEst;
			
			cout<<"--------------------------"<<endl;
			encontrado=true;
		}

		Lec>>nom;		
	}
	Lec.close();
	/*
	if(encontrado==false){
		cout<<"Codigo no encontrado."<<endl;
	}
	*/
	return encontrado;
	
}

//funcion que verifica que no se reitan los codigos
bool verifica(string cod)
{
    ifstream leer("Estudiantes.txt", ios::in);
    string nom,codigo,prome;
    leer >> nom;
    while (!leer.eof())
    {
        
        leer >> codigo;
        leer >> prome;
        if (codigo == cod) //si el codigo si existe en el archivo
        {
            //system("color 0c");
            cout << "\n\nNo puede ingresarse el registro,\nCedula ya existente.\n\n";
            leer.close(); 
            return false; 
        }
        leer >> nom; 
    }
    // Si Cedula no esta en el registro, entonces
    leer.close(); 

    cout << "\n\nRegistro Ingresado con exito\n\n";
    return true;  
}

//funcion que agrega un nuevo registro al txt
void agregar(fstream &esc)
{
    string Nombre, Codigo, Promedio;
    float promeAux;
    // Crea el archivo Personas.txt o le a�ade datos si ya esta creado
    esc.open("Estudiantes.txt", ios::out | ios::app);

	cout<<"********************************************************";
	cout<<"\n\t\t  SISTEMA DE BIBLIOTECA\n";
	cout<<"********************************************************\n\n";

    cout << "-> Digite el Nombre: \t\t\t";
    cin >> Nombre;
    cout << "-> Digite No. Codigo de estudiante: \t";
    cin >> Codigo;
	do{
		cout << "-> Digite No. de promedio: \t\t";
    	cin >> Promedio;
    	stringstream promefloat(Promedio);promefloat>>promeAux;	
	}while(promeAux<0 || promeAux>20);
    	
    
    
    // Verificar que Cedula no este ya ingresada
    if (verifica(Codigo))
    {
        esc << Nombre << " " << Codigo << " " << Promedio <<"\n";
    }
    esc.close();
}



void menuPrincipal(){
    system("cls");
    cout<<"\t\t BIENVENIDO A LA BIBLIOTECA\n\n";
	cout<<"1.- Ingresar"<<endl;
	cout<<"2.- Registrar nuevo estudiante"<<endl;
	cout<<"3.- Ingresar como administrador."<<endl;
	cout<<"0.- Salir"<<endl<<endl;	
	cout<<"Ingrese Opcion---> ";
}

void menuAdministrador(){
	system("cls");
	
	cout<<"********************************************************";
	cout<<"\n\t\t  SISTEMA DE BIBLIOTECA\n";
	cout<<"********************************************************\n\n";
	cout<<"1.- Insertar libro"<<endl;
	cout<<"2.- Ver libros disponibles"<<endl;
	cout<<"3.- Ver lista de libros prestados"<<endl<<endl;
	
	cout<<"========================================================";
	cout<<"\n>>>>>>>>>SOLICITUDES - LIBROS MUY solicitados<<<<<<<<<"<<endl;
	cout<<"========================================================"<<endl<<endl;
		
	cout<<"4.- Ver solicitudes (Libros Muy solicitados)"<<endl;
	cout<<"5.- Aceptar siguiente solicitud"<<endl;
	cout<<"6.- Denegar siguiente solicitud"<<endl<<endl;
	
	cout<<"========================================================";
	cout<<"\n>>>>>>>>>>>>SOLICITUDES DE LIBROS COMUNES<<<<<<<<<<<<<"<<endl;
	cout<<"========================================================"<<endl<<endl;
	
	cout<<"7.- Ver solicitudes (Comunes)"<<endl;
	cout<<"8.- Aceptar siguiente solicitud"<<endl;
	cout<<"9.- Denegar siguiente solicitud"<<endl;
	
	
	cout<<"0.- Salir"<<endl<<endl;
	
	cout<<"Ingrese Opcion---> ";
}
void menuUsuario (){
	system("cls");
	
	cout<<"********************************************************";
	cout<<"\n\t\t  SISTEMA DE BIBLIOTECA\n";
	cout<<"********************************************************\n\n";
	
	cout<<"-Ponderado ACTUAL:\t "<<pond<<endl;
	cout<<"-Nombre de estudiante:\t "<<nombre<<endl;
	cout<<"-Codigo de estudiante:\t "<<codigoEst<<endl<<endl;

	cout<<"========================================================";
	cout<<"\n>>>>>>>>>               OPCIONES               <<<<<<<<<"<<endl;
	cout<<"========================================================";
	cout<<"\n1.- Ver libros disponibles"<<endl;
	cout<<"2.- Crear solicitud"<<endl;
	cout<<"0.- Salir"<<endl;
	cout<<"========================================================"<<endl<<endl;
	
	cout<<"Ingrese Opcion---> ";
}

int main(){
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	color(hConsole, 241);
	TpListaL libros=NULL,temp=NULL, prestamos = NULL;
	//TpListaL almacen=NULL;
	TpListaSol solicitudNormal=NULL;
	TpListaSol solicitudProm =NULL;
	int opc, opcSist, pos, busca, reemp, opcReg;
    string nomUsu;
	int codUsu;	

	do{ 
        menuPrincipal();
        cin>>opc;
        switch(opc){
            case 1:{
                system("cls");
                
				cout<<"********************************************************";
				cout<<"\n\t\t  SISTEMA DE BIBLIOTECA\n";
				cout<<"********************************************************\n\n";
				
                if(login(Lec)== true){
                	
                	
                    do{
                        menuUsuario();
		                cin>>opcSist;
                        switch(opcSist){
							case 1:
								system("cls");
								cout<<"\n********************************************************";
								cout<<"\n>>>>>>>>>>>>>>>>>>>>LISTA DE LIBROS<<<<<<<<<<<<<<<<<<<<<"<<endl;
								cout<<"********************************************************\n\n";
								verLibrosI(libros);
								cout<<endl<<endl;
								system("pause");
								break;
							case 2:
								
								char tip[15];
								cout<<"Ingresa el titulo del libro que deseas solicitar"<<endl;
								cin>>tip;
								//temp=buscarL(libros, tip);
								if(buscarL(libros,tip)!=NULL){
									if(buscarL(libros,tip)->est==true){
										InsertaFinalSol(solicitudProm,tip);
										//verListaSol(solicitudProm);
										ordenarBurbujaSol(solicitudProm);
										verListaSol(solicitudProm);
									}
									else{
										encolar(solicitudNormal,tip);
										verListaSol(solicitudNormal);
									}
								}
								else{
									cout<<"No existe este libro";
								}
								system("pause");
								break;
							system("pause");
							break;
                        }
                    }while(opcSist != 0);
                }
                else
                    cout<<"Sus credenciales no son correctas"<<endl;
                system("pause");
                break;
            }
            
            case 2:{
                system("cls");
                agregar(Esc);
                cout<<"Usted se ha registrado en el sistema"<<endl;
                //system("pause");
                break;
            }
			case 3:{
				do{
                   menuAdministrador();
		           cin>>opcSist;
                   switch(opcSist){
                       case 1:{
						encolarL(libros);
		    			cout<<"\n********************************************************";
						cout<<"\n>>>>>>>>>>>>>>>>>>>>LISTA DE LIBROS<<<<<<<<<<<<<<<<<<<<<"<<endl;
						cout<<"********************************************************\n\n";
						verLibrosI(libros);
						cout<<endl<<endl;
						system("pause");
						break;
					}
					case 2:
						system("cls");
						cout<<"\n********************************************************";
						cout<<"\n>>>>>>>>>>>>>>>>>>>>LISTA DE LIBROS<<<<<<<<<<<<<<<<<<<<<"<<endl;
						cout<<"********************************************************\n\n";
						verLibrosI(libros);
						cout<<endl<<endl;
						system("pause");
						break;
					case 3:
						system("cls");
						verListaLibrosPrestados(prestamos);
						system("pause");
						break;
					case 4:
						system("cls");
						cout<<"SOLICITUDES DE LIBROS(muy solicitados)"<<endl;
						verListaSol(solicitudProm);
						system("pause");
						break;
					case 5:
						system("cls");
						//aceptar solicitud
						if(primeraSol(solicitudProm)!=NULL){
							if(buscarL(libros, primeraSol(solicitudProm)->nom)!=NULL){
							TpListaL extraido = popLibro(libros, primeraSol(solicitudProm)->nom);
							librosPrestados(prestamos,extraido);
							cout<<"Solicitud Aprobada"<<endl<<endl;
							
							verListaLibrosPrestados(prestamos);
							//eliminarInicio(solicitudProm);
							}else{
							cout<<"Este libro ya fue prestado. Solicitud denegada."<<endl;
							}
							
							//eliminarInicio(solicitudProm);
							desencolar(solicitudProm);
							//cout<<"Solicitud eliminada"<<endl;
						}else{
							cout<<"No hay ninguna solicitud de libro"<<endl;
						}		
						system("pause");
						break;
					case 6:
						//denegar solicitud
						if(primeraSol(solicitudProm)!=NULL){
							desencolar(solicitudProm);
							cout<<"Solicitud denegada"<<endl;
							
						}else{
							cout<<"No hay ninguna solicitud de libro"<<endl;
						}
						system("pause");
						break;
					case 7:
						system("cls");
						cout<<"SOLICITUDES DE LIBROS(comunes)"<<endl;
						verListaSol(solicitudNormal);
						system("pause");
						break;
					case 8:
						system("cls");
						//aceptar solicitud
						if(primeraSol(solicitudNormal)!=NULL){
							if(buscarL(libros, primeraSol(solicitudNormal)->nom)!=NULL){
							//popLibro(libros, primeraSol(solicitudNormal)->nom);
							TpListaL extraido = popLibro(libros, primeraSol(solicitudNormal)->nom);
							librosPrestados(prestamos,extraido);
							cout<<extraido->nom<<endl;
							cout<<"Solicitud Aprobada"<<endl<<endl;
							
							verListaLibrosPrestados(prestamos);
							
							//eliminarInicio(solicitudProm);
							}else{
							cout<<"Este libro ya fue prestado. Solicitud denegada."<<endl;
							}
							
							//eliminarInicio(solicitudNormal);
							desencolar(solicitudNormal);
							//cout<<"Solicitud eliminada"<<endl;
						}else{
							cout<<"No hay ninguna solicitud de libro"<<endl;
							//eliminarInicio(solicitudNormal);
						}		
						system("pause");
						break;
					case 9:
						//denegar solicitud
						if(primeraSol(solicitudNormal)!=NULL){
							//eliminarInicio(solicitudNormal);
							desencolar(solicitudNormal);
							cout<<"Solicitud denegada"<<endl;
							
						}else{
							cout<<"No hay ninguna solicitud de libro"<<endl;
						}
						system("pause");
						break;
					
                    }
                }while(opcSist != 0);
			}
        }
	}while(opc != 0);
		
	return 0;	
}


