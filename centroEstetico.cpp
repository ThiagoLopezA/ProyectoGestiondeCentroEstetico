// Proyecto gesti�n de centro estetico.
// Thiago L�pez Alderete, Legajo:
// Juan Diego Demichelis, Legajo:
	
// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Struct



// Prototipos

	//Validaciones
	bool valEnt(float x);  // Valida que el numero ingresado sea entero.
	bool valOpc(float x, int min, int may); // Valida que la opcion ingresada se encuentre en el rango de las validas.
	
	//Mensajes
	void eEntero(); // Mensaje para cuando el numero ingresado no es entero.
	void eNumInval(); // Mensaje para cuando el numero ingresado es invalido.
	
	//Men�s
	void encabezado(); // Encabezado de los menus.
	int menu();	//Men� principal.
	int moduloEspacio(); //Men� del modulo de espacios.
	int moduloRecepcion(); //Men� del modulo de recepcionistas.
	int moduloAdmin(); //Men� del modulo de administraci�n.

// Main

int main()
{
	setlocale(LC_ALL, "spanish");
	
	int Menu,ModEspacio,ModRecep,ModAdmin;
	
	do
	{
		Menu=menu();
		switch(Menu)
		{
			case 1:
				{
					ModEspacio=moduloEspacio();
					switch(ModEspacio)
					{
						case 1:
							{
								break;
							}
						case 2:
							{
								break;
							}
						case 3:
							{
								break;
							}
					}
					break;
				}
			case 2:
				{
					ModRecep=moduloRecepcion();
					break;
				}
			case 3:
				{
					ModAdmin=moduloAdmin();
					break;
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
	
	//Men�s

void encabezado()
{

	printf("\n\t======================================================================\n");
	printf("\t\t\t     |Proyecto Centro Estetico|\n");
	printf("\t\tPrograma para ayudar a la atenci�n y gesti�n de pacientes\n\t\t\t\tdel centro estetico.");
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
		printf("\n\n\tMen� principal: \n\n");
		printf("\t[1]. M�dulo Espacios.\n");
		printf("\t[2]. M�dulo Recepci�n.\n");
		printf("\t[3]. M�dulo Administraci�n.\n");
		printf("\t[4]. Salir.\n");
		printf("\n\tIngrese una opci�n: ");
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

int moduloEspacio()
{
	float x;
	bool entero,opcValida,error;
	
	do
	{
		
		system("cls");
		encabezado();
		printf("\n\n\tM�dulo Espacios: \n\n");
		printf("\t[1]. Iniciar Sesi�n.\n");
		printf("\t[2]. Visualizar lista de espera de turnos.\n");
		printf("\t[3]. Registrar evoluci�n del tratamiento.\n");
		printf("\t[4]. Volver al men� principal.\n");
		printf("\n\tIngrese una opci�n: ");
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

int moduloRecepcion()
{
	float x;
	bool entero,opcValida,error;
	
	do
	{
		
		system("cls");
		encabezado();
		printf("\n\n\tM�dulo del recepcionista: \n\n");
		printf("\t[1]. Iniciar Sesi�n.\n");
		printf("\t[2]. Registrar cliente.\n");
		printf("\t[3]. Registrar turno.\n");
		printf("\t[4]. Listado de atenciones por profesional y fecha.\n");
		printf("\t[5]. Volver al men� principal.\n");
		printf("\n\tIngrese una opci�n: ");
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
		printf("\n\n\tM�dulo Administraci�n: \n\n");
		printf("\t[1]. Registrar Profesional.\n");
		printf("\t[2]. Registrar Usuario Recepcionista.\n");
		printf("\t[3]. Atenciones por profesional.\n");
		printf("\t[4]. Ranking de profesionales por atenciones.\n");
		printf("\t[5]. Volver al men� principal.\n");
		printf("\n\tIngrese una opci�n: ");
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

