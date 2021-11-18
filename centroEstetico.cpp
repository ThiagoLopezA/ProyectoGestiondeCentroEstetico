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
	//Menus
	void encabezado(); // Encabezado de los menus.
	int menu();	//Menu principal.
	
	void moduloEspacio(int &profesional); //Menu del modulo de espacios con usuario logueado.
	int moduloRecepcion(); //Menu del modulo de recepcionistas.
	int moduloAdmin(); //Menu del modulo de administracion.
	
	//Funciones de menus
	
		//Funciones del modulo espacio.
		bool loginProf(int &profesional); //inicio de sesion de profesionales.
		
		//Funciones del modulo recepcion.
		
		//Funciones del modulo administracion.

// Main

int main()
{
	setlocale(LC_ALL, "spanish");
	
	int Menu,ModEspacio,ModRecep,ModAdmin;
	int profesional=0; // Este representara el id del profesional que inicio sesion.
	int recepcionista=0; // Este represente el id del recepcionista que inicio sesion.
	bool sesionProf;
	FILE *recep;
	FILE *profe;
	FILE *clientes;
	FILE *turnos;

	
	
	do
	{
		Menu=menu();
		switch(Menu)
		{
			case 1:
				{
					if(profesional==0)
					{
						sesionProf=loginProf(profesional);
						if(sesionProf==1)
						{
							moduloEspacio(profesional);
						}
					}
					else
					{
						moduloEspacio(profesional);	
					}
					break;
				}
			case 2:
				{
					
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
	
	//Menus

void encabezado()
{

	printf("\n\t======================================================================\n");
	printf("\t\t\t     |Proyecto Centro Estetico|\n");
	printf("\t\tPrograma para ayudar a la atencion y gestion de pacientes\n\t\t\t\tdel centro estetico.");
	printf("\n\t======================================================================\n");
	putchar('\n');
	for (int i=0; i < 87; i++) {
		putchar('_');
	}
}

int menu()
{
	float x;
	bool entero,opcValida,error=0;
	
	do
	{
		system("cls");
		encabezado();
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

bool loginProf(int &profesional)
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

void moduloEspacio(int &profesional)
{
	float x;
	bool entero,opcValida,error;
	int opc;
	
	do
	{
		
		system("cls");
		encabezado();
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

int moduloRecepcion()
{
	float x;
	bool entero,opcValida,error;
	
	do
	{
		
		system("cls");
		encabezado();
		printf("\n\n\tModulo del recepcionista: \n\n");
		printf("\t[1]. Iniciar Sesion.\n");
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
	return x;
}

int moduloAdmin()
{
	float x;
	bool entero,opcValida,error;
	
	do
	{
		
		system("cls");
		encabezado();
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
	return x;
}



