// Proyecto gestion de centro estetico.
// Thiago Lopez Alderete, Legajo: 53840
// Juan Diego Demichelis, Legajo: 53820
	
// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <ctype.h>

// Struct

struct auxiliar
{
	char ApeyNom[60];
	int posicion;
};
struct fecha
{
	int dia;
	int mes;
	int anio;
};

struct Usuario
{
	char usuario[10];
	char clave[10];
	char ApeyNom[60];
};

struct Profesional
{
	char ApeyNom[60];
	int id;
	int dni;
	char telefono[25];
};

struct Cliente
{
	char ApeyNom[60];
	char domicilio[60];
	int dni;
	char localidad[60];
	fecha fNacimiento;
	float peso;
	char telefono[25];
};

struct Turnos
{
	int idProfesional;
	char ApeyNom[60];
	fecha Fecha;
	int dni;
	char detalle[380];
	bool atendido=0;
};


// Prototipos

	//Validaciones
	bool valEnt(float x);  // Valida que el numero ingresado sea entero.
	bool valOpc(float x, int min, int may); // Valida que la opcion ingresada se encuentre en el rango de las validas.
	bool valFec(int x, int min, int max); // Valida si el campo de la fecha esta en el limite establecido.
	
	//Mensajes
	void eEntero(); // Mensaje para cuando el numero ingresado no es entero.
	void eNumInval(); // Mensaje para cuando el numero ingresado es invalido.
	void eUsuario(); // Mensaje para cuando el inicio de sesion es incorrecto.
	void eConjunto(int min, int may); // Mensaje para cuando el numero no esta en un conjunto de numeros validos.
	void eChar(); // Mensaje para cuando el caracter de decision es incorrecto.
	//Menus
	void encabezado(); // Encabezado de los menus.
	void encRegCl(); // Encabezado Registo de Cliente
	void encRegT(); // Encabezado Registo de Turno
	int menu(fecha aux);	//Menu principal.
	void getFecha(fecha &aux);
	void moduloEspacio(int &profesional, fecha aux); //Menu del modulo de espacios con usuario logueado.
	void moduloRecepcion(int &recepcionista, fecha aux); //Menu del modulo de recepcionistas.
	void moduloAdmin(fecha aux); //Menu del modulo de administracion.
	
	//Funciones de menus
	bool login(int &profesional,int mod); //inicio de sesion de profesionales/recepcionistas.

	//Funciones del modulo espacio.
	void getListaTurnos(FILE *turnos,fecha fActual,FILE *Clientes);
	
	//Funciones del modulo recepcion.
	void getCliente(FILE *cliente);
	void getTurno(FILE *turnos, FILE *profe, FILE *cliente);
	void getListado(FILE *cliente);
	//Funciones del modulo administracion.

// Var global
Turnos turno; // Registro para turnos.
FILE *cliente;
FILE *turnos;
FILE *profe;
// Main

int main()
{
	setlocale(LC_ALL, "spanish");
	
	int Menu,ModEspacio,ModRecep,ModAdmin;
	int profesional=0; // Este representara el id del profesional que inicio sesion.
	int recepcionista=0; // Este represente el id del recepcionista que inicio sesion.
	bool sesionProf,sesionRecep;
	fecha fActual;

	
	getFecha(fActual);
	do
	{
		Menu=menu(fActual);
		switch(Menu)
		{
			case 1:
				{
					if(profesional==0)
					{
						sesionProf=login(profesional,1); // El numero de modulo va a hacer q varie el archivo donde busque el usuario.
						if(sesionProf==1)
						{
							moduloEspacio(profesional,fActual);
						}
					}
					else
					{
						moduloEspacio(profesional,fActual);	
					}
					break;
				}
			case 2:
				{
					if(recepcionista==0)
					{
						sesionRecep=login(recepcionista,2);
						if(sesionRecep==1)
						{
							moduloRecepcion(recepcionista,fActual);
						}
					}
					else
					{
						moduloRecepcion(recepcionista,fActual);
					}
					
				}
			case 3:
				{
				
				}
		}
	}while(Menu!=5);
	
	
}

// Funciones

	//Validaciones

bool valEnt(float x)
{
	int entero;
	float decimal;
	
	entero=x/1;
	decimal=x-entero;
		
	if(decimal!=0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
		
bool valOpc(float x, int min, int may)
{
	if(x<min || x>may)
	{			
		return 0;
	}
	else
	{
		return 1;
	}
}

bool valFec(float x, int min, int max)
{
	bool vEnt,vOpc;
	
	vEnt=valEnt(x);
	vOpc=valOpc(x,min,max);
	
	if(vEnt==1 and vOpc==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

	//Mensajes
	
void eEntero()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #001:\n\t\tEl numero ingresado debe ser entero, reintente.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}

void eNumInval()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #002:\n\t\tEl numero ingresado no es valido.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}

void eUsuario()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #003:\n\t\tEl usuario o clave no es valida.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}

void eConjunto(int min, int may)
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #004:\n\t\tEl numero debe estar entre %i y %i.\n",min,may);
	printf("\n\t======================================================================\n\n");
	system("pause");
}

void eChar()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #005:\n\t\tEl caracter es incorrecto, solo se acepta (S o N)\n");
	printf("\n\t======================================================================\n\n");
	system("pause");	
}

void eNegativo()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #006:\n\t\tNo se permiten los numeros negativos.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");		
}

void eVacio()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #007:\n\t\tNo se permite saltear este campo.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}

void eUsuario2()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #008:\n\t\tEl usuario debe tener:\n\t-Entre 6 y 10 caracteres.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");	
}
void eUsuario3()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #009:\n\t\tEl nombre de usuario no esta disponible.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
void eUsuario4()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #010:\n\t\tEl nombre de usuario debe contener:\n\t-Empezar con minuscula\n\t-Tener al menos 2 letras mayusculas\n\t-Tener como maximo 3 digitos.\n\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
void eClave()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #011:\n\t\tLa clave debe estar.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");	
}
void eEncontrar()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\tError #012:\n\t\tNo se encontro a la persona reintente.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
	//Encabezados
void encabezado(fecha aux)
{

	printf("\n\t======================================================================\n");
	printf("\t\t\t     |Proyecto Centro Estetico|\n");
	printf("\t\tPrograma para ayudar a la atencion y gestion de pacientes\n\t\t\t\tdel centro estetico.");
	printf("\n\t======================================================================\n");
	printf("\n\t\tFecha: %02i/%02i/%i",aux.dia,aux.mes,aux.anio);
	putchar('\n');
	for (int i=0; i < 87; i++) {
		putchar('_');
	}
}
void encRegCl()
{	
	printf("\n\t======================================================================\n");
	printf("\n\t\tRegistro de Cliente\n");
	printf("\n\t======================================================================\n\n");
}

void encRegT()
{	
	printf("\n\t======================================================================\n");
	printf("\n\t\tRegistro de Turno\n");
	printf("\n\t======================================================================\n\n");
}
	//Menus
	
void getFecha(fecha &aux)
{
	bool esEntero,fechaValida, error=0;
	float temp;
	char band;
	bool salir;
	
	do
	{	
		do
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t\t\t     Bienvenido usuario!\n");	
			printf("\n\t======================================================================\n");
			printf("\n\tIngrese la fecha actual: DD/MM/AAAA");
			printf("\n\tDigite el dia: ");
			scanf("%f",&temp);
			esEntero=valEnt(temp);
			fechaValida=valOpc(temp,1,31);
			if(esEntero!=1 or fechaValida!=1)
			{
				eConjunto(1,31);
				error=1;
			}
			else
			{
				error=0;
				aux.dia=temp;
			}
		}while(error!=0);
		
		do
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t\t\t     Bienvenido usuario!\n");	
			printf("\n\t======================================================================\n");
			printf("\n\tIngrese la fecha actual: %02i/MM/AAAA",aux.dia);
			printf("\n\tDigite el mes: ");
			scanf("%f",&temp);
			esEntero=valEnt(temp);
			fechaValida=valOpc(temp,1,12);
			if(esEntero!=1 or fechaValida!=1)
			{
				error=1;
				eConjunto(1,12);
			}
			else
			{
				error=0;
				aux.mes=temp;
			}
		}while(error!=0);
		
		do
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t\t\t     Bienvenido usuario!\n");	
			printf("\n\t======================================================================\n");
			printf("\n\tIngrese la fecha actual: %02i/%02i/AAAA",aux.dia,aux.mes);
			printf("\n\tDigite el anio: ");
			scanf("%f",&temp);
			esEntero=valEnt(temp);
			fechaValida=valOpc(temp,2000,3000);
			if(esEntero!=1 or fechaValida!=1)
			{
				error=1;
				eConjunto(2000,3000);
			}
			else
			{
				error=0;
				aux.anio=temp;
			}
		}while(error!=0);
		
		do
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t\t\t     Bienvenido usuario!\n");	
			printf("\n\t======================================================================\n");
			printf("\n\tIngrese la fecha actual: %02i/%02i/%i",aux.dia,aux.mes,aux.anio);
			printf("\n\tEsta seguro que esta es la fecha correcta? (S/N): ");
			_flushall();
			scanf("%c",&band);
			if(band!='S' and band!='N')
			{
				error=1;
				eChar();
			}
			else
			{
				error=0;
				if(band=='S')
				{
					salir=1;
				}
				else
				{
					salir=0;
				}
			}
		}while(error!=0);
		

	}while(salir!=1);
	
}

int menu(fecha aux)
{
	float x;
	bool entero,opcValida,error=0;
	
	do
	{
		system("cls");
		encabezado(aux);
		printf("\n\n\tMenu principal: \n\n");
		printf("\t[1]. Modulo Espacios.\n");
		printf("\t[2]. Modulo Recepcion.\n");
		printf("\t[3]. Modulo Administracion.\n");
		printf("\t[4]. Cambiar fecha Actual.\n");
		printf("\t[5]. Salir.\n");
		printf("\n\tIngrese una opcion: ");
		scanf("%f",&x);
		entero=valEnt(x);
		opcValida=valOpc(x,1,5);
		if(entero!=1 or opcValida!=1)
		{
			error=1;
			if(entero!=1)
			{
				eEntero();
			}
			else
			{
				eNumInval();
			}
		}
		else
		{
			error=0;
		}
	}while(error!=0);
	
	return x;		
}

bool login(int &profesional,int mod)
{
	Usuario prof;
	int comp,comp1;
	
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t\t   >Iniciar sesion como profesional:<\n");
	printf("\n\tUsuario: ");
	_flushall();
	gets(prof.usuario);
	printf("\n\tClave: ");
	_flushall();
	gets(prof.clave);
	
	comp=strcmp(prof.usuario,"adm");
	comp1=strcmp(prof.clave,"123");
	
	
	if(comp!=0 or comp1!=0)
	{
		eUsuario();
		return 0;
	}
	else
	{
		profesional=1;
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t\tBienvenido Usuario Administrador\n");
		printf("\n\t======================================================================\n\n");
		system("pause");
		return 1;
	}

}

void moduloEspacio(int &profesional,fecha aux)
{
	float x;
	bool entero,opcValida,error;
	int opc;
	FILE *turnos;
	FILE *Clientes;
	
	do
	{
		
		system("cls");
		encabezado(aux);
		printf("\n\n\tModulo Espacios: \n\n");
		printf("\tID de la sesion: %i\n\n",profesional);
		printf("\t[1]. Cerrar sesion.\n");
		printf("\t[2]. Visualizar lista de espera de turnos.\n");
		printf("\t[3]. Registrar evolucion del tratamiento.\n");
		printf("\t[4]. Volver al menu principal.\n");
		printf("\n\tIngrese una opcion: ");
		scanf("%f",&x);
		entero=valEnt(x);
		opcValida=valOpc(x,1,4);
		if(entero!=1 or opcValida!=1)
		{
			error=1;
			if(entero!=1)
			{
				eEntero();
			}
			else
			{
				eNumInval();
			}
		}
		else
		{
			error=0;
		}
	}while(error!=0);
	
	opc=x;
	
	switch(opc)
	{
		case 1:
			{
				profesional=0;
				break;
			}
		case 2:
			{
				getListaTurnos(turnos,aux,Clientes);
				break;
			}
	}
}

void moduloRecepcion(int &recepcionista,fecha aux)
{
	float x;
	bool entero,opcValida,error;
	int opc;
	FILE *profes;
	FILE *clientes;
	FILE *turnos;
	
	do
	{
		
		system("cls");
		encabezado(aux);
		printf("\n\n\tModulo del recepcionista: \n\n");
		printf("\tID de la sesion: %i\n\n",recepcionista);
		printf("\t[1]. Cerrar sesion.\n");
		printf("\t[2]. Registrar cliente.\n");
		printf("\t[3]. Registrar turno.\n");
		printf("\t[4]. Listado de atenciones por profesional y fecha.\n");
		printf("\t[5]. Listado de clientes.\n");
		printf("\t[6]. Volver al menu principal.\n");
		printf("\n\tIngrese una opcion: ");
		scanf("%f",&x);
		entero=valEnt(x);
		opcValida=valOpc(x,1,6);
		if(entero!=1 or opcValida!=1)
		{
			error=1;
			if(entero!=1)
			{
				eEntero();
			}
			else
			{
				eNumInval();
			}
		}
		else
		{
			error=0;
		}
	}while(error!=0);
	opc=x;	
	switch(opc)
	{
		case 1:
			{
				recepcionista=0;
				break;
			}
		case 2:
			{
				getCliente(cliente);
				break;
			}
		case 3:
			{
				getTurno(turnos,profe,cliente);
				break;
			}
		case 5:
			{
				getListado(cliente);
			}
	}
}

void moduloAdmin(fecha aux)
{
	float x;
	bool entero,opcValida,error;
	
	do
	{
		
		system("cls");
		encabezado(aux);
		printf("\n\n\tModulo Administracion: \n\n");
		printf("\t[1]. Registrar Profesional.\n");
		printf("\t[2]. Registrar Usuario Recepcionista.\n");
		printf("\t[3]. Atenciones por profesional.\n");
		printf("\t[4]. Ranking de profesionales por atenciones.\n");
		printf("\t[5]. Volver al menu principal.\n");
		printf("\n\tIngrese una opciÃ³n: ");
		scanf("%f",&x);
		entero=valEnt(x);
		opcValida=valOpc(x,1,5);
		if(entero!=1 or opcValida!=1)
		{
			error=1;
			if(entero!=1)
			{
				eEntero();
			}
			else
			{
				eNumInval();
			}
		}
		else
		{
			error=0;
		}
	}while(error!=0);

}

// Modulo Espacios //


/*
	int idProfesional;
	fecha Fecha;
	int dni;
	char detalle[380];
	bool atendido=0;
*/

void getListaTurnos(FILE *turnos,fecha fActual,FILE *Clientes)
{
	//1. Listar los turnos, por nombre;
	//2. Dar la opcion de obtener por nombre;
	//3. Verificar que el nombre este bien;
	//4. Dar observacion;
	//5. Sumar un punto para el ranking;
	
	Turnos temp[50];
	Cliente temp2[50];
	auxiliar temp3[50];
	char aux[60];
	int i=0,j=0,l=0,t=0,posicion,pos,cmp,edad;
	bool encontrado=0,error=0;
	
	
	turnos=fopen("Turnos.dat","ab+");
	if(turnos == NULL)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\tHa ocurrido un error, el archivo Turnos.dat no se puede abrir.\n");			
		printf("\n\t======================================================================\n");
		system("pause");	
		exit(1);
	}
	
	rewind(turnos);
	fread(&temp[i],sizeof(Turnos),1,turnos);
	while(!feof(turnos))
	{
		i++;
		fread(&temp[i],sizeof(Turnos),1,turnos);	
	}
	fclose(turnos);
	
	Clientes=fopen("Clientes.dat","ab+");
	if(Clientes == NULL)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\tHa ocurrido un error, el archivo Clientes.dat no se puede abrir.\n");			
		printf("\n\t======================================================================\n");
		system("pause");	
		exit(1);
	}
	
	rewind(Clientes);
	fread(&temp2[j],sizeof(Cliente),1,Clientes);
	while(!feof(turnos))
	{
		j++;
		fread(&temp2[j],sizeof(Cliente),1,Clientes);	
	}
	fclose(Clientes);
	
	do
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t\t   Listado de turnos de hoy\n");			
		printf("\n\t======================================================================\n");
		for(int k=0;k<i;k++)
		{
			if((temp[k].Fecha.dia==fActual.dia) and (temp[k].Fecha.mes==fActual.mes) and (temp[k].Fecha.anio==fActual.anio) and (temp[k].atendido==0))
			{
					printf("\n\t%02i.- ",l);
					puts(temp[k].ApeyNom);
					strcpy(temp3[t].ApeyNom,temp[k].ApeyNom);
					temp3[t].posicion=k;
					t++;
					l++;
					
			}
		}
		if(l<=0)
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t\t  No hay turnos en la lista de espera\n");			
			printf("\n\t======================================================================\n");	
			system("pause");
			error=0;
		}
		else
		{
			printf("\n\t========\n");
			printf("\n\tSeleccionar paciente por nombre: ");
			_flushall();
			gets(aux);
			cmp=strcmp(aux,"");
			if(cmp==0)
			{
				eVacio();
				error=1;
			}
			else
			{
				for(int p=0;p<j;p++)
				{
					cmp=strcmp(aux,temp2[p].ApeyNom);
					if(cmp==0)
					{
						encontrado=1;
						posicion=p;
					}
				}
				if(encontrado!=1)
				{
					system("cls");
					eEncontrar();
					system("pause");
					error=1;
				}
				else
				{
					do
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t\t   Paciente: ");
						puts(temp2[posicion].ApeyNom);			
						printf("\n\t======================================================================\n");
						printf("\n\tDNI: %i\n",temp2[posicion].dni);
						printf("\n\tDomicilio: ");
						puts(temp2[posicion].domicilio);
						
						edad=(fActual.anio)-(temp2[posicion].fNacimiento.anio);
						
						printf("\n\tEdad: %i\n",edad);
						printf("\n\tPeso: %.2f",temp2[posicion].peso);
						printf("\n\t======================================================================\n");
						for(int n=0;n<t;n++)
						{
							if(temp3[n].ApeyNom==temp2[posicion].ApeyNom)
							{
								pos=temp3[n].posicion;
							}
						}
						printf("\n\tObservacion: ");
						_flushall();
						gets(temp[pos].detalle);
						cmp=strcmp(temp[pos].detalle,"");
						if(cmp==0)
						{
							error=1;
						}	
						else
						{
							error=0;
							temp[pos].atendido=1;
						}
					}while(error!=0);	
				}
			}
		}
	}while(error!=0);
	
	FILE *temporal;
	temporal=fopen("temp.dat","ab+");
	for(int z=0;z<i;z++)
	{
		fwrite(&temp[z],sizeof(Turnos),1,temporal);
	}
	fclose(temporal);
	
	remove("Turnos.dat");
	rename("temp.dat","Turnos.dat");	
}
	



// Modulo Recepcion //

void getCliente(FILE *cliente)
{

	bool v, error,cmp;
	Cliente temp; // reg temporal para cargar clientes para evitar el uso de una var global.
	float aux;
	char conf;
	bool salir;
	
	do
	{
		//P- Apellido y nombre
		do
		{
			system("cls");
			encRegCl();
			printf("\n\tApellido y Nombre : ");
			_flushall();
			gets(temp.ApeyNom);
			cmp=strcmp(temp.ApeyNom,"");
			if(cmp==0)
			{
				error=1;
				eVacio();
			}	
			else
			{
				error=0;
			}
		}while(error!=0);
	
		
		//P- Localidad
		do
		{
			system("cls");
			encRegCl();
			printf("\n\tLocalidad : ");
			_flushall();
			gets(temp.localidad);
			cmp=strcmp(temp.localidad,"");
			if(cmp==0)
			{
				error=1;
				eVacio();
			}	
			else
			{
				error=0;
			}
		}while(error!=0);
	
		
		//P- Domicilio
		do
		{
			system("cls");
			encRegCl();
			printf("\n\tDomicilio : ");
			_flushall();
			gets(temp.domicilio);
			cmp=strcmp(temp.domicilio,"");
			if(cmp==0)
			{
				error=1;
				eVacio();
			}	
			else
			{
				error=0;
			}
		}while(error!=0);
	
		
		//P- DNI
		do
		{
			system("cls");
			encRegCl();
			printf("\n\tDni(8 digitos): ");
			scanf("%d",&temp.dni);
			if(temp.dni<1000000 or temp.dni<9999999)
			{
				error=1;
				eConjunto(1000000,9999999);
			}
			else
			{
				error=0;
			}
		}while(error!=0);
	
		//P- Fecha de nacimiento
		
		//dia
		do
		{
			system("cls");
			encRegCl();
			printf("\n\tFecha de Nacimiento : ");
			printf("\n\tDia : ");
			scanf("%f",&aux);
			v = valFec(aux,1,30);
			if(v!=1)
			{
				error=1;
				eConjunto(1,30);
			}
			else
			{
				error=0;
				temp.fNacimiento.dia=aux;
			}
		}while(error!=0);
		//mes
		do
		{
			system("cls");
			encRegCl();
			printf("\n\tFecha de Nacimiento : ");
			printf("\n\tMes : ");
			scanf("%f",&aux);
			v = valFec(aux,1,12);
			if(v!=1)
			{
				error=1;
				eConjunto(1,12);
			}
			else
			{
				error=0;
				temp.fNacimiento.mes=aux;
			}
		}while(error!=0);
		//anio
		do
		{
			system("cls");
			encRegCl();
			printf("\n\tFecha de Nacimiento : ");
			printf("\n\tAnio : ");
			scanf("%f",&aux);
			v = valFec(aux,2000,3000);
			if(v!=1)
			{
				error=1;
				eConjunto(2000,3000);
			}
			else
			{
				error=0;
				temp.fNacimiento.anio=aux;
			}
		}while(error!=0);
		
		//P- Peso
		
		do
		{
			system("cls");
			encRegCl();
			printf("\n\tPeso : ");
			scanf("%f",&temp.peso);
			if(temp.peso<0)
			{
				error=1;
				eNegativo();
			}
			else
			{
				error=0;
			}
		}while(error!=0);
		
		//P - Num. de telefono
		do
		{
			system("cls");
			encRegCl();
			printf("\n\tNro. de Telefono: ");
			_flushall();
			gets(temp.telefono);
			cmp=strcmp(temp.telefono,"");
			if(cmp==0)
			{
				error=1;
				eVacio();
			}
			else
			{
				error=0;
			}
		}while(error!=0);
	
		// Confirmacion
		
		do
		{
			system("cls");
			encRegCl();
			printf("\n\t-------------------\n");
			printf("\n\tApellido y Nombre : ");
			puts(temp.ApeyNom);
			printf("\n\tLocalidad : ");
			puts(temp.localidad);
			printf("\n\tDomicilio : ");
			puts(temp.domicilio);
			printf("\n\tDni : %i",temp.dni);
			printf("\n\n\tFecha de Nacimiento : %02i/%02i/%i",temp.fNacimiento.dia,temp.fNacimiento.mes,temp.fNacimiento.anio);
			printf("\n\n\tPeso : %.2f",temp.peso);
			printf("\n\n\tNro. de Telefono : ");
			puts(temp.telefono);
			printf("\n\tConfime si todo es valido (S/N): ");
			scanf("%c",&conf);
			if(conf!='S' and conf!='N')
			{
				error=1;
				eChar();
			}
			else
			{
				error=0;
				if(conf=='S')
				{
					salir=1;
				}
				else
				{
					salir=0;
				}
			}
		}while(error!=0);
	
	}while(salir!=1);
	
	cliente=fopen("Clientes.dat","ab+");
	if(cliente == NULL)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\tHa ocurrido un error, el archivo Profesionales.dat no se puede abrir.\n");
		printf("\n\t======================================================================\n");			
		system("pause");
		exit(1);
	}
	fwrite(&temp,sizeof(Cliente),1,cliente);
	fclose(cliente);	
}

void getTurno(FILE *turnos, FILE *profe, FILE *cliente)
{
	bool v, error,cmp;
	Turnos temp; // reg temporal para cargar clientes para evitar el uso de una var global.
	Profesional temp1;
	Cliente temp2;
	float aux;
	char conf;
	bool salir,encontrado;
	
	do
	{
		//P- Id Del Profesional
		/*
		do
		{
			system("cls");
			encRegT();
			printf("\n\tId. Del Profesional : ");
			scanf("%f",&aux);
			cmp = valEnt(aux);
			if(cmp==0)
			{
				error=1;
				eEntero();
			}	
			else
			{
				temp.idProfesional= 1;
				profe = fopen("Profesionales.dat","ab+");
				if(profe == NULL)
				{
					system("cls");
					printf("\n\t======================================================================\n");
					printf("\n\tHa ocurrido un error, el archivo Profesionales.dat no se puede abrir.\n");
					printf("\n\t======================================================================\n");
					system("pause");
					exit(1);
				}
				else
				{
					error=1;
					fread(&temp1,sizeof(Profesional),1,profe);
					while(!feof(profe) or error != 0)
					{
						if(temp.idProfesional == temp1.id)
						{
							error=0;
						}
						else
						{
							fread(&temp1,sizeof(Profesional),1,profe);

						}
					}
					if(error != 0)
					{
						printf("\n\tEl Id. de Profesional ingresado no existe en la Base de Datos");
					}
				}
				fclose(profe);
			}
		}while(error!=0);
		*/
		
		//P- DNI del Cliente
		do
		{
			system("cls");
			encRegT();
			printf("\n\tDni del Cliente (8 digitos): ");
			scanf("%d",&temp.dni);
			if(temp.dni<1000000 or temp.dni<9999999)
			{
				error=1;
				eConjunto(1000000,9999999);
			}
			else
			{
				error=0;
				cliente = fopen("Clientes.dat","ab+");
				if(cliente == NULL)
				{
					system("cls");
					printf("\n\t======================================================================\n");
					printf("\n\tHa ocurrido un error, el archivo Clientes.dat no se puede abrir.\n");
					printf("\n\t======================================================================\n");
					system("pause");	
					exit(1);
				}
				else
				{
					fread(&temp2,sizeof(Cliente),1,cliente);
					while(!feof(cliente))
					{
						if(temp.dni == temp2.dni)
						{
							encontrado=1;
							strcpy(temp.ApeyNom,temp2.ApeyNom);
						}
						fread(&temp2,sizeof(Cliente),1,cliente);
					}
					if(encontrado != 1)
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\tEl DNI de Cliente ingresado no existe en la Base da Datos\n");
						printf("\n\t======================================================================\n");
						system("pause");
						error=1;
					}
					else
					{
						error=0;
					}
					fclose(cliente);
				}
			}
		}while(error!=0);
	
		//P- Fecha de Turno
		
		//dia
		do
		{
			system("cls");
			encRegT();
			printf("\n\tFecha de Turno : ");
			printf("\n\tDia : ");
			scanf("%f",&aux);
			v = valFec(aux,1,30);
			if(v!=1)
			{
				error=1;
				eConjunto(1,30);
			}
			else
			{
				error=0;
				temp.Fecha.dia=aux;
			}
		}while(error!=0);
		//mes
		do
		{
			system("cls");
			encRegT();
			printf("\n\tFecha de Turno : ");
			printf("\n\tMes : ");
			scanf("%f",&aux);
			v = valFec(aux,1,12);
			if(v!=1)
			{
				error=1;
				eConjunto(1,12);
			}
			else
			{
				error=0;
				temp.Fecha.mes=aux;
			}
		}while(error!=0);
		//anio
		do
		{
			system("cls");
			encRegT();
			printf("\n\tFecha de Turno : ");
			printf("\n\tAnio : ");
			scanf("%f",&aux);
			v = valFec(aux,2000,3000);
			if(v!=1)
			{
				error=1;
				eConjunto(2000,3000);
			}
			else
			{
				error=0;
				temp.Fecha.anio=aux;
			}
		}while(error!=0);
		
		
	
		// Confirmacion
		
		do
		{
			system("cls");
			encRegT();
			printf("\n\t-------------------\n");
			printf("\n\tId. de Profesional : 1");
			printf("\n\tDni : %i",temp.dni);
			printf("\n\tFecha de Turno : %02i/%02i/%i",temp.Fecha.dia,temp.Fecha.mes,temp.Fecha.anio);
			printf("\n\n\tConfime si todo es valido (S/N): ");
			_flushall();
			scanf("%c",&conf);
			if(conf!='S' and conf!='N')
			{
				error=1;
				eChar();
			}
			else
			{
				error=0;
				if(conf=='S')
				{
					salir=1;
				}
				else
				{
					salir=0;
				}
			}
		}while(error!=0);
	
	}while(salir!=1);
	
	turnos=fopen("Turnos.dat","ab+");
	fwrite(&temp,sizeof(Turnos),1,turnos);
	fclose(turnos);	
	
	//El detalle del turno se carga cuando se haya realizado la visita//
}

void getListado(FILE *cliente)
{
	Cliente temp;
	
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t   LISTADO DE CLIENTES\n");
	printf("\n\t======================================================================\n");
	cliente=fopen("Clientes.dat","ab+");
	rewind(cliente);
	fread(&temp,sizeof(Cliente),1,cliente);
	while(!feof(cliente))
	{
		printf("\n\n\t------\n");
		printf("\n\tCliente: ");
		puts(temp.ApeyNom);
		printf("\tDomicilio: ");
		puts(temp.domicilio);
		printf("\tDNI: %i",temp.dni);
		printf("\n\tLocalidad: ");
		puts(temp.localidad);
		printf("\tFecha de nacimiento: %02i/%02i/%i.\n",temp.fNacimiento.dia,temp.fNacimiento.mes,temp.fNacimiento.anio);
		printf("\tPeso: %.2f",temp.peso);
		printf("\n\tTelefono: ");
		puts(temp.telefono);
		printf("\n\n");
		fread(&temp,sizeof(Cliente),1,cliente);
	}
	system("pause");
}
// Modulo Administracion //

/*
void registrar(FILE *profes,FILE *recep,int mod)
{
	char usuario[10];
	char clave[10];
	bool min;
	int c=0,cd=0,n,cmp; // c contador de mayusculas, cd contador de digitos
	Usuario temp;
	
	if(mod==1)
	{
		do
		{
				system("cls");
				printf("\n\t======================================================================\n");
				printf("\n\tRegistro de usuario profesional\n");
				printf("\n\tUsuario: ");
				_flushall();
				gets(usuario);
				n=strlen(usuario);
				if(n<6 or n>10)
				{
					error=1;
					eUsuario();
				}
				else
				{
					cmp=strcmp(usuario,"");
					if(cmp==0)
					{
						error=1;
						eVacio();
					}
					else
					{
						if(usuario[0]==tolower(usuario[0]))
						{
							min=1;
						}
						for(int i=0;i<n+1;i++)
						{
							if(usuario[i]==toupper(usuario[i]))
							{
								c++;
							}
							if(!isalpha(usuario[i]))
							{
								cd++;
							}
						}
						if(min==1 and c>=2 and cd==3)
						{
							profes=fopen("Profesionales.dat","ab+");
							if(profes==NULL)
							{
								system("cls");
								printf("\n\t======================================================================\n");
								printf("\n\tHa ocurrido un error, el archivo Profesionales.dat no se puede abrir.\n");
								printf("\n\t======================================================================\n");
								system("pause");
								exit(1);
							}
							else
							{
								fread(&temp,sizeof(Usuario),1,profes);
								while(!feof(profes))
								{
									cmp=strcmp(usuario,temp.usuario);
									if(cmp==0)
									{
										error=1;
										eUsuario2();
									}
								}
								if(error!=1)// Recien pide la contraseña
								{
									do
									{
										system("cls");
										printf("\n\t======================================================================\n");
										printf("\n\tRegistro de usuario profesional\n");
										printf("\n\tUsuario: ");
										puts(usuario);
										printf("\nContraseña: ")
										_flushall();
										gets(clave);
										cmp=strlen(clave);
										if(cmp<6 or cmp>32)
										{
											eClave();
										}
									}while(error!=0);
								}
							}
						}
						else
						{
							
						}
					}
				}
				
		}while(error!=0);

	}
}
*/

