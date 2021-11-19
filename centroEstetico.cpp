// Proyecto gestion de centro estetico.
// Thiago Lopez Alderete, Legajo: 53840
// Juan Diego Demichelis, Legajo: 53820
	
// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Struct

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
	fecha Fecha;
	int dni;
	char detalle[380];
};


// Prototipos

	//Validaciones
	bool valEnt(float x);  // Valida que el numero ingresado sea entero.
	bool valOpc(float x, int min, int may); // Valida que la opcion ingresada se encuentre en el rango de las validas.
	
	
	//Mensajes
	void eEntero(); // Mensaje para cuando el numero ingresado no es entero.
	void eNumInval(); // Mensaje para cuando el numero ingresado es invalido.
	void eUsuario(); // Mensaje para cuando el inicio de sesion es incorrecto.
	void eConjunto(int min, int may); // Mensaje para cuando el numero no esta en un conjunto de numeros validos.
	void eChar(); // Mensaje para cuando el caracter de decision es incorrecto.
	//Menus
	void encabezado(); // Encabezado de los menus.
	int menu(fecha aux);	//Menu principal.
	void getFecha(fecha &aux);
	void moduloEspacio(int &profesional, fecha aux); //Menu del modulo de espacios con usuario logueado.
	void moduloRecepcion(int &recepcionista, fecha aux); //Menu del modulo de recepcionistas.
	void moduloAdmin(fecha aux); //Menu del modulo de administracion.
	
	//Funciones de menus
	bool login(int &profesional,int mod); //inicio de sesion de profesionales/recepcionistas.
	
		//Funciones del modulo espacio.
		
		
		//Funciones del modulo recepcion.
		
		//Funciones del modulo administracion.

// Var global


// Main

int main()
{
	setlocale(LC_ALL, "spanish");
	
	int Menu,ModEspacio,ModRecep,ModAdmin;
	int profesional=0; // Este representara el id del profesional que inicio sesion.
	int recepcionista=0; // Este represente el id del recepcionista que inicio sesion.
	bool sesionProf,sesionRecep;
	FILE *recep;
	FILE *profe;
	FILE *clientes;
	FILE *turnos;
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
	}while(Menu!=4);
	
	
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

void encabezado(fecha aux)
{

	printf("\n\t======================================================================\n");
	printf("\t\t\t     |Proyecto Centro Estetico|\n");
	printf("\t\tPrograma para ayudar a la atencion y gestion de pacientes\n\t\t\t\tdel centro estetico.");
	printf("\n\t======================================================================\n");
	printf("\t\tFecha: %02i/%02i/%i",aux.dia,aux.mes,aux.anio);
	putchar('\n');
	for (int i=0; i < 87; i++) {
		putchar('_');
	}
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
		printf("\t[4]. Salir.\n");
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
	}
}

void moduloRecepcion(int &recepcionista,fecha aux)
{
	float x;
	bool entero,opcValida,error;
	int opc;
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
		printf("\t[5]. Volver al menu principal.\n");
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
	opc=x;	
	switch(opc)
	{
		case 1:
			{
				recepcionista=0;
				break;
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
		printf("\n\tIngrese una opción: ");
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



