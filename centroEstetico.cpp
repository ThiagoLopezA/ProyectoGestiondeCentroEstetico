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
struct Profesional
{
	int id;
	int dni;
	char telefono[25];
	int puntaje=0;
};
struct Usuario
{
	char usuario[50];
	char clave[50];
	char ApeyNom[50];
	Profesional profesional;
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
	char nombreProfesional[50];
	char ApeyNom[60];
	fecha Fecha;
	int dni;
	char detalle[380];
	bool atendido=0;
	bool hoy=0;
};
struct estado
{
	bool status=0;
	char ApeyNom[50];
	int id;	
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
	int menu(fecha aux, bool bandFec);	//Menu principal.
	void getFecha(fecha &aux);
	void moduloEspacio(estado &profesional, fecha aux, bool bandFec); //Menu del modulo de espacios con usuario logueado.
	void moduloRecepcion(estado &recepcionista, fecha aux, bool bandFec); //Menu del modulo de recepcionistas.
	void moduloAdmin(fecha aux, bool bandFec); //Menu del modulo de administracion.
	
	//Funciones de menus
	void login(estado &profesional,estado &recepcionista,int mod); //inicio de sesion de profesionales/recepcionistas.

	//Funciones del modulo espacio.
	void getListaTurnos(fecha fActual,estado profesional);
	void getObservacion(estado profesional,fecha fActual);
	
	//Funciones del modulo recepcion.
	void getCliente(FILE *cliente);
	void getTurno(FILE *turnos, FILE *profe, FILE *cliente);
	void getListado(FILE *cliente);
	void getAtencionesPorFecha();
	
	//Funciones del modulo administracion.
	void registrar(FILE *profes,FILE *recep,int mod);
	void getName(char ApeyNom[50],bool profesional);
	void getPass(char password[50],bool profesional);
	void getUser (char user[50],bool profesional);
	void getAtencionesPorProf();
	void getPuntaje();
	void getRanking();
	void fichaTecnica();
	
	// Var global
	Turnos turno; // Registro para turnos.
	FILE *cliente;
	FILE *turnos;
	FILE *profe;
	FILE *recep;
	FILE *temporal;
	
	// Main
int main()
{
	setlocale(LC_ALL, "spanish");
	
	int Menu,ModEspacio,ModRecep,ModAdmin;
	estado profesional;
	estado recepcionista;
	bool sesionProf,sesionRecep,bandFec=0;
	fecha fActual;

	getFecha(fActual);
	do
	{
		Menu=menu(fActual, bandFec);
		switch(Menu)
		{
			case 1:
				{
					if(profesional.status!=1)
					{
						login(profesional,recepcionista,1); // El numero de modulo va a hacer q varie el archivo donde busque el usuario.
						if(profesional.status==1)
						{
							moduloEspacio(profesional,fActual,bandFec);
						}
					}
					else
					{
						moduloEspacio(profesional,fActual,bandFec);	
					}
					break;
				}
			case 2:
				{
					if(recepcionista.status!=1)
					{
						login(profesional,recepcionista,2);
						if(recepcionista.status==1)
						{
							moduloRecepcion(recepcionista,fActual,bandFec);
						}
					}
					else
					{
						moduloRecepcion(recepcionista,fActual,bandFec);
					}
					break;
				}
			case 3:
				{
					moduloAdmin(fActual,bandFec);
					break;
				}
			case 4:
				{
					
					getFecha(fActual);
					bandFec=1;
					break;
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
	printf("\n\t\t[Error] - El numero ingresado debe ser entero, reintente.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
void eNumInval()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - El numero ingresado no es valido.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
void eUsuario()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - El usuario o clave no es valida.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
void eConjunto(int min, int may)
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - El numero debe estar entre %i y %i.\n",min,may);
	printf("\n\t======================================================================\n\n");
	system("pause");
}
void eChar()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - El caracter es incorrecto, solo se acepta (S o N)\n");
	printf("\n\t======================================================================\n\n");
	system("pause");	
}
void eNegativo()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - No se permiten los numeros negativos.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");		
}
void eVacio()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - No se permite saltear este campo.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
void eUsuario2()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - El usuario debe tener:\n\t-Entre 6 y 10 caracteres.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");	
}
void eUsuario3()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - El nombre de usuario no esta disponible.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
void eUsuario4()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - El nombre de usuario debe contener:\n\t-Empezar con minuscula\n\t-Tener al menos 2 letras mayusculas\n\t-Tener como maximo 3 digitos.\n\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
void eClave()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - La clave debe estar.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");	
}
void eEncontrar()
{
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\t\t[Error] - No se encontro a la persona reintente.\n");
	printf("\n\t======================================================================\n\n");
	system("pause");
}
	
	//Encabezados
void encabezado(fecha aux, bool bandFec)
{
	
	if(bandFec == 0)
	{
		printf("\n\t======================================================================\n");
		printf("\t\t\t     |Proyecto Centro Estetico|\n");
		printf("\t\tPrograma para ayudar a la atencion y gestion de pacientes\n\t\t\t\tdel centro estetico.");
		printf("\n\t======================================================================\n");
		printf("\n\tFecha: %02i/%02i/%i",aux.dia,aux.mes,aux.anio);
		putchar('\n');
		for (int i=0; i < 87; i++) {
		putchar('_');
		}
	}
	else 
	{
		printf("\n\t======================================================================\n");
		printf("\t\t\t     |Proyecto Centro Estetico|\n");
		printf("\t\tPrograma para ayudar a la atencion y gestion de pacientes\n\t\t\t\tdel centro estetico.");
		printf("\n\t======================================================================\n");
		printf("\n\tFecha Actualizada: %02i/%02i/%i",aux.dia,aux.mes,aux.anio);
		putchar('\n');
		for (int i=0; i < 87; i++) {
		putchar('_');
		}
	}
}
void encRegCl()
{	
	printf("\n\t======================================================================\n");
	printf("\n\t\t   Registro de Cliente\n");
	printf("\n\t======================================================================\n\n");
}
void encRegT()
{	
	printf("\n\t======================================================================\n");
	printf("\n\t\t   Registro de Turno\n");
	printf("\n\t======================================================================\n\n");
}
void encRegUserProf()
{
	printf("\n\t======================================================================\n");
	printf("\n\t\t   Registro de usuario profesional\n");
	printf("\n\t======================================================================\n\n");
}
void encRegUserRec()
{
	printf("\n\t======================================================================\n");
	printf("\n\t\t   Registro de usuario recepcionista\n");
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
int menu(fecha aux, bool bandFec)
{
	float x;
	bool entero,opcValida,error=0;
	
	do
	{
		system("cls");
		encabezado(aux,bandFec);
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
void login(estado &profesional,estado &recepcionista,int mod)
{
	Usuario profes;
	Usuario rec;
	Usuario aux;
	bool error,encontrado=0;
	int cmp;
	
	switch(mod)
	{
		case 1:
			{

					do
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t\t   >Iniciar sesion como profesional<\n");
						printf("\n\t======================================================================\n");
						printf("\n\tUsuario: ");
						_flushall();
						gets(profes.usuario);
						cmp=strcmp(profes.usuario,"");
						if(cmp==0)
						{
							system("cls");
							printf("\n\t======================================================================\n");
							printf("\n\t[Error] - No se puede cargar un valor vacio.\n");
							printf("\n\t======================================================================\n\n\n");
							system("pause");
							error=1;
						}
						else
						{
							error=0;
						}
					}while(error!=0);
		
					do
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t\t   >Iniciar sesion como profesional<\n");
						printf("\n\t======================================================================\n");
						printf("\n\tUsuario: ");
						puts(profes.usuario);
						printf("\n\tContrasenia: ");
						_flushall();
						gets(profes.clave);
						cmp=strcmp(profes.clave,"");
						if(cmp==0)
						{
							system("cls");
							printf("\n\t======================================================================\n");
							printf("\n\t[Error] - No se puede cargar un valor vacio.\n");
							printf("\n\t======================================================================\n\n\n");
							system("pause");
							error=1;
						}
					}while(error!=0);
					
					profe=fopen("Profesionales.dat","ab+");
					if(profe == NULL )
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t[Error] - No se pudo abrir el archivo 'Profesionales.dat'.\n");
						printf("\n\t======================================================================\n\n\n");
						system("pause");
						exit(1);
					}
					
					rewind(profe);
					fread(&aux,sizeof(Usuario),1,profe);
					while(!feof(profe))
					{
						cmp=strcmp(aux.usuario,profes.usuario);
						if(cmp==0)
						{
							encontrado=1;
							cmp=strcmp(aux.clave,profes.clave);
							if(cmp==0)
							{
								system("cls");
								printf("\n\t======================================================================\n");
								printf("\n\t\t   Bienvenido ");
								puts(aux.ApeyNom);
								printf("\n\t======================================================================\n\n\n");
								system("pause");
							}
							else
							{
								system("cls");
								printf("\n\t======================================================================\n");
								printf("\n\t[Error] - Clave incorrecta\n");
								printf("\n\t======================================================================\n\n\n");
								system("pause");
							}
							break;
						}
						fread(&aux,sizeof(Usuario),1,profe);
					}
					
					if(encontrado!=1)
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t[Error] - El usuario no se encuentra en la base de datos.\n");
						printf("\n\t======================================================================\n\n\n");
						system("pause");
					}
					else
					{
						profesional.status=1;
						strcpy(profesional.ApeyNom,aux.ApeyNom);
						profesional.id=aux.profesional.id;
					}
					fclose(profe);
				break;
			}
		case 2:
			{
					do
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t\t   >Iniciar sesion como recepcionista<\n");
						printf("\n\t======================================================================\n");
						printf("\n\tUsuario: ");
						_flushall();
						gets(rec.usuario);
						cmp=strcmp(rec.usuario,"");
						if(cmp==0)
						{
							system("cls");
							printf("\n\t======================================================================\n");
							printf("\n\t[Error] - No se puede cargar un valor vacio.\n");
							printf("\n\t======================================================================\n\n\n");
							system("pause");
							error=1;
						}
					}while(error!=0);
		
					do
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t\t   >Iniciar sesion como recepcionista<\n");
						printf("\n\t======================================================================\n");
						printf("\n\tUsuario: ");
						puts(rec.usuario);
						printf("\n\tContrasenia: ");
						_flushall();
						gets(rec.clave);
						cmp=strcmp(rec.clave,"");
						if(cmp==0)
						{
							system("cls");
							printf("\n\t======================================================================\n");
							printf("\n\t[Error] - No se puede cargar un valor vacio.\n");
							printf("\n\t======================================================================\n\n\n");
							system("pause");
							error=1;
						}
					}while(error!=0);
					
					recep=fopen("Recepcionistas.dat","ab+");
					if(recep==NULL)
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t[Error] - No se pudo abrir el archivo 'Recepcionistas.dat'.\n");
						printf("\n\t======================================================================\n\n\n");
						system("pause");
						exit(1);
					}
					
					rewind(recep);
					fread(&aux,sizeof(Usuario),1,recep);
					while(!feof(recep))
					{
						cmp=strcmp(aux.usuario,rec.usuario);
						if(cmp==0)
						{
							encontrado=1;
							cmp=strcmp(aux.clave,rec.clave);
							if(cmp==0)
							{
								system("cls");
								printf("\n\t======================================================================\n");
								printf("\n\t\t   Bienvenido ");
								puts(aux.ApeyNom);
								printf("\n\t======================================================================\n\n\n");
								system("pause");
							}
							else
							{
								system("cls");
								printf("\n\t======================================================================\n");
								printf("\n\t[Error] - Clave incorrecta\n");
								printf("\n\t======================================================================\n\n\n");
								system("pause");
							}
							break;
						}
						fread(&aux,sizeof(Usuario),1,recep);
					}
					
					if(encontrado!=1)
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t[Error] - El usuario no se encuentra en la base de datos.\n");
						printf("\n\t======================================================================\n");
						system("pause");
					}
					else
					{
						recepcionista.status=1;
						strcpy(recepcionista.ApeyNom,aux.ApeyNom);
					}
					fclose(recep);
				break;
			}
	}
	
	
	
	
	
	
}
void moduloEspacio(estado &profesional,fecha aux, bool bandFec)
{
	float x;
	bool entero,opcValida,error;
	int opc;
	FILE *turnos;
	FILE *Clientes;
	do
	{
		system("cls");
		encabezado(aux, bandFec);
		printf("\n\n\tModulo Espacios: \n\n");
		printf("\tUsuario : ");
		puts(profesional.ApeyNom);
		printf("\n\t[1]. Cerrar sesion.\n");
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
				profesional.status=0;
				break;
			}
		case 2:
			{
				getListaTurnos(aux,profesional);
				break;
			}
		case 3:
			{
				getObservacion(profesional,aux);
				break;
			}
	}
}
void moduloRecepcion(estado &recepcionista,fecha aux, bool bandFec)
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
		encabezado(aux, bandFec);
		printf("\n\n\tModulo del recepcionista: \n\n");
		printf("\tUsuario : ");
		puts(recepcionista.ApeyNom);
		printf("\n\t[1]. Cerrar sesion.\n");
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
				recepcionista.status=0;
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
		case 4:
			{
				getAtencionesPorFecha();
				break;
			}
		case 5:
			{
				getListado(cliente);
				break;
			}
	}
}
void moduloAdmin(fecha aux, bool bandFec)
{
	float x;
	bool entero,opcValida,error;
	int opcion;
	do
	{
		
		system("cls");
		encabezado(aux, bandFec);
		printf("\n\n\tModulo Administracion: \n\n");
		printf("\t[1]. Registrar Profesional.\n");
		printf("\t[2]. Registrar Usuario Recepcionista.\n");
		printf("\t[3]. Atenciones por profesional.\n");
		printf("\t[4]. Ranking de profesionales por atenciones.\n");
		printf("\t[5]. Ficha tecnica de turnos.\n");
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

	opcion=x;
	
	switch(opcion)
	{
		case 1:
			{
				registrar(profe,recep,1);
				break;
			}
		case 2:
			{
				registrar(profe,recep,2);
				break;
			}
		case 3:
			{
				getAtencionesPorProf();
				break;
			}
		case 4:
			{
				getRanking();
				break;
			}
		case 5:
			{
				fichaTecnica();
			}
	}
}

// Modulo Espacios //
void getListaTurnos(fecha fActual,estado profesional)
{
	Turnos archivo[100];
	int i=0,cmp,numLista=0,longitud;

	
	turnos=fopen("Turnos.dat","ab+");
	if(turnos == NULL)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t[Error] - El archivo 'Turnos.dat' no se pudo abrir...\n");
		printf("\n\t======================================================================\n");
		system("pause");
		exit(1);	
	}	
	
	fread(&archivo[i],sizeof(Turnos),1,turnos);

	while(!feof(turnos))
	{
		i++;
		fread(&archivo[i],sizeof(Turnos),1,turnos);
	}
	fclose(turnos);
	
	if(i==0)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t[Error] - No hay turnos registrados.\n");
		printf("\n\t======================================================================\n");
	
	}	
	else
	{	
		
		for(int j=0;j<=i;j++)
		{
			if(archivo[j].Fecha.dia==fActual.dia)
			{
				if(archivo[j].Fecha.mes==fActual.mes)
				{
					if(archivo[j].Fecha.anio==fActual.anio)
					{
						archivo[j].hoy=1;
					}
				}
			}
		}
			
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t\t   Lista de turnos de hoy: \n");
		printf("\n\t======================================================================\n");
		
		for(int m=0;m<=i;m++)
		{
			if(archivo[m].hoy==1 and archivo[m].atendido==0)
			{
				cmp=strcmp(archivo[m].nombreProfesional,profesional.ApeyNom);
				if(cmp == 0)
				{
					printf("\n\t%02i.- ",numLista+1);
					puts(archivo[m].ApeyNom);
					numLista++;
				}
			}
		}
	}
	printf("\n\t======================================================================\n\n\n");
	system("pause");
}
void getObservacion(estado profesional,fecha fActual)
{
	char nombrePaciente[60];
	int cmp, pos, edad;
	bool error, encontrado=0;
	Turnos infoTurnos[100];
	Cliente infoPaciente;
	int i=0, longitud, x=0;
	Usuario infoProfesionales[100];
	do
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\tDigite el nombre del paciente: ");
		_flushall();
		gets(nombrePaciente);
		cmp=strcmp(nombrePaciente,"");
		if(cmp == 0)
		{
			error=1;
			eVacio();
		}
		else
		{
			error=0;
		}
	}while(error!=0);
	
	turnos=fopen("Turnos.dat","ab+");
	if(turnos == NULL)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t[Error] - No se pudo abrir el archivo 'temp.dat'...\n");
		printf("\n\t======================================================================\n\n");
		system("pause");
		exit(1);
	}
	
	fread(&infoTurnos[i],sizeof(Turnos),1,turnos);
	
	while(!feof(turnos))
	{   
		i++;	//Error esta mierda no aumenta por alguna razón
		fread(&infoTurnos[i],sizeof(Turnos),1,turnos);
	}
	fclose(turnos);

	for(int j=0; j<i; j++)
	{
		if(infoTurnos[j].atendido==0)
		{
			if(infoTurnos[j].Fecha.dia==fActual.dia && infoTurnos[j].Fecha.mes==fActual.mes && infoTurnos[j].Fecha.anio==fActual.anio)
			{
				cmp=strcmp(infoTurnos[j].nombreProfesional,profesional.ApeyNom);
				if(cmp==0)
				{
					cmp=strcmp(infoTurnos[j].ApeyNom,nombrePaciente);
					if(cmp==0)
					{
						encontrado=1;
						pos=j;
					}
				}
			}	
		}
	}
	
	if(encontrado!=1)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t[Error] - No hay ningun turno para hoy con ese paciente...\n");
		printf("\n\t======================================================================\n\n");
		system("pause");
	}
	else
	{
		cliente=fopen("Clientes.dat","ab+");
		if(cliente == NULL)
		{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t[Error] - No se pudo abrir el archivo 'Clientes.dat'...\n");
		printf("\n\t======================================================================\n\n");
		system("pause");
		exit(1);
		}
		
		fread(&infoPaciente,sizeof(Cliente),1,cliente);
		while(!feof(cliente))
		{
			cmp=strcmp(infoPaciente.ApeyNom,infoTurnos[pos].ApeyNom);
			if(cmp == 0)
			{
				break;
			}
			fread(&infoPaciente,sizeof(Cliente),1,cliente);
		}
		fclose(cliente);
		
		do
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\tNombre del paciente: ");
			puts(infoTurnos[pos].ApeyNom);
			printf("\tDNI: %i",infoPaciente.dni);
			printf("\n\tDomicilio: ");
			puts(infoPaciente.domicilio);
			edad=(fActual.anio)-(infoPaciente.fNacimiento.anio);
			printf("\tEdad: %i",edad);
			printf("\n\tPeso: %.2f\n",infoPaciente.peso);
			printf("\n\t======================================================================\n");
			printf("\n\tObservacion: ");
			_flushall();
			gets(infoTurnos[pos].detalle);
			cmp=strcmp(infoTurnos[pos].detalle,"");
			if(cmp==0)
			{
				error=1;
				eVacio();
			}
			else
			{
				infoTurnos[pos].atendido=1;
				infoTurnos[pos].hoy=0;
				error=0;			
			}
		}while(error!=0);
		
		temporal=fopen("turnosActualizados.dat","ab+");
		if(temporal == NULL)
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t[Error] - No se pudo abrir el archivo 'turnosActualizados.dat'...\n");
			printf("\n\t======================================================================\n\n");
			system("pause");
			exit(1);
		}
		
		for(int k=0;k<i;k++)
		{
			fwrite(&infoTurnos[k],sizeof(Turnos),1,temporal);
		}
		fclose(temporal);
		remove("Turnos.dat");
		rename("turnosActualizados.dat","Turnos.dat");	
	}

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
			printf("\n\tFecha de Nacimiento: DD/MM/AAAA\n");
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
			printf("\n\tFecha de Nacimiento: %02i/MM/AAAA\n",temp.fNacimiento.dia);
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
			printf("\n\tFecha de Nacimiento: %02i/%02i/AAAA\n",temp.fNacimiento.dia,temp.fNacimiento.mes);
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
	char auxNombre[50];
	bool salir,encontrado;
	Usuario auxiliar;
	
	do
	{
		do
		{
			do // P- Prof del turno
			{
				system("cls");
				encRegT();
				printf("\n\tNombre del profesional: ");
				_flushall();
				gets(auxNombre);
				cmp=strcmp(auxNombre,"");
				if(cmp==0)
				{
					eVacio();
					error=1;
				}
				else
				{
					error=0;
				}
			}while(error!=0);
			
			profe=fopen("Profesionales.dat","ab+");
			
			if(profe == NULL)
			{
				system("cls");
				printf("\n\t======================================================================\n");
				printf("\n\t[Error] - No se pudo abrir el archivo 'Profesionales.dat'\n");
				printf("\n\t======================================================================\n");
				system("pause");
				exit(1);
			}
			fread(&auxiliar,sizeof(Usuario),1,profe);
			while(!feof(profe))
			{
				cmp=strcmp(auxiliar.ApeyNom,auxNombre);
				if(cmp==0)
				{
					encontrado=1;
				}
				fread(&auxiliar,sizeof(Usuario),1,profe);
			}
			fclose(profe);
			if(encontrado==1)
			{
				error=0;
				strcpy(temp.nombreProfesional,auxNombre);
			}
			else
			{
				error=1;
				system("cls");
				printf("\n\t======================================================================\n");
				printf("\n\tEl profesional no se encontro.\n");
				printf("\n\t======================================================================\n");
				system("pause");
			}
		}while(error!=0);
		
		//P- DNI del Cliente
		do
		{
			system("cls");
			encRegT();
			printf("\n\tDNI del Cliente (8 digitos): ");
			scanf("%d",&temp.dni);
			if(temp.dni<10000000 or temp.dni>99999999)
			{
				error=1;
				eConjunto(10000000,99999999);
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
					encontrado=0;
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
			printf("\n\tFecha de Turno : DD/MM/AAAA");
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
			printf("\n\tFecha de Turno : %02i/MM/AAAA",temp.Fecha.dia);
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
			printf("\n\tFecha de Turno : %02i/%02i/AAAA",temp.Fecha.dia,temp.Fecha.mes);
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
			printf("\n\tProfesional : ");
			puts(auxNombre);
			printf("\tDni : %i",temp.dni);
			printf("\n\tPaciente: ");
			puts(temp.ApeyNom);
			printf("\tFecha de Turno : %02i/%02i/%i\n\n",temp.Fecha.dia,temp.Fecha.mes,temp.Fecha.anio);
			printf("\n\t======================================================================");
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
		printf("\n\t==============\n");
		fread(&temp,sizeof(Cliente),1,cliente);
	}
	printf("\n\n");
	system("pause");
}
void getAtencionesPorFecha()
{
	char nombreDoctor[50];
	fecha fechaDeAtencion;
	int cmp;
	bool error, hayTurnos=0, validar,confirmar,buscar,encontrado=0;
	Turnos temp;
	float aux;
	Usuario auxiliar;
	
		do
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\tIngrese el nombre del doctor: ");
			_flushall();
			gets(nombreDoctor);
			cmp=strcmp(nombreDoctor,"");
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
			
		profe=fopen("Profesionales.dat","ab+");
		if(profe==NULL)
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t[Error] - No se pudo abrir el archivo 'Profesionales.dat'...\n");
			printf("\n\t======================================================================\n");
			system("pause");
			exit(1);
		}
		fread(&auxiliar,sizeof(Usuario),1,profe);
		while(!feof(profe))
		{
			cmp=strcmp(auxiliar.ApeyNom,nombreDoctor);
			if(cmp==0)
			{
				encontrado=1;
			}
			fread(&auxiliar,sizeof(Usuario),1,profe);
		}
		fclose(profe);
		if(encontrado!=1)
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t[Error] - No se encontro al doctor en la base de datos...\n");
			printf("\n\t======================================================================\n");
			system("pause");
		}
		else
		{
			do
			{
				do
				{
					system("cls");
					printf("\n\t======================================================================\n");
					printf("\n\tIngrese el nombre del doctor: ");
					puts(nombreDoctor);
					printf("\n\tIngrese la fecha: DD/MM/AAAA");
					printf("\n\tDia: ");
					scanf("%f",&aux);
					validar=valOpc(aux,1,30);
					if(validar!=1)
					{
						error=1;
						eConjunto(1,30);
					}
					else
					{
						error=0;
						fechaDeAtencion.dia=aux;
					}	
				}while(error!=0);
				
				
				do
				{
					system("cls");
					printf("\n\t======================================================================\n");
					printf("\n\tIngrese el nombre del doctor: ");
					puts(nombreDoctor);
					printf("\n\tIngrese la fecha: %02i/MM/AAAA",fechaDeAtencion.dia);
					printf("\n\tMes: ");
					scanf("%f",&aux);
					validar=valOpc(aux,1,12);
					if(validar!=1)
					{
						error=1;
						eConjunto(1,12);
					}
					else
					{
						error=0;
						fechaDeAtencion.mes=aux;
					}	
				}while(error!=0);
				
				
				do
				{
					system("cls");
					printf("\n\t======================================================================\n");
					printf("\n\tIngrese el nombre del doctor: ");
					puts(nombreDoctor);
					printf("\n\tIngrese la fecha: %02i/%02i/AAAA",fechaDeAtencion.dia,fechaDeAtencion.mes);
					printf("\n\tAnio: ");
					scanf("%f",&aux);
					validar=valOpc(aux,2000,3000);
					if(validar!=1)
					{
						error=1;
						eConjunto(2000,3000);
					}
					else
					{
						error=0;
						fechaDeAtencion.anio=aux;
					}	
				}while(error!=0);
				
				do
				{
					system("cls");
					printf("\n\t======================================================================\n");
					printf("\n\tIngrese el nombre del doctor: ");
					puts(nombreDoctor);
					printf("\n\tFecha: %02i/%02i/%i",fechaDeAtencion.dia,fechaDeAtencion.mes,fechaDeAtencion.anio);
					printf("\n\t======================================================================\n");
					printf("\n\tEsta informacion es correcta? (S/N): ");
					_flushall();
					scanf("%c",&confirmar);	
					if(confirmar!='S' and confirmar!='N')
					{
						error=1;
						eChar();
					}
					else
					{
						if(confirmar=='S')
						{
							buscar=1;
							error=0;
						}
						else
						{
							buscar=0;
							error=0;
						}
					}
				}while(error!=0);
	
			}while(buscar!=1);
	
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\tInforme de atenciones de: ");
		puts(nombreDoctor);
		printf("\n\tEn la fecha: %02i/%02i/%i",fechaDeAtencion.dia,fechaDeAtencion.mes,fechaDeAtencion.anio);
		printf("\n\t======================================================================\n");
		turnos=fopen("Turnos.dat","ab+");
		if(turnos==NULL)
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t[Error] - No se pudo abrir el archivo 'Turnos.dat'...\n");
			printf("\n\t======================================================================\n");
			system("pause");
			exit(1);
		}
		fread(&temp,sizeof(Turnos),1,turnos);
		while(!feof(turnos))
		{
			hayTurnos=1;
			if(temp.atendido=1)
			{
				if(temp.Fecha.dia==fechaDeAtencion.dia && temp.Fecha.mes==fechaDeAtencion.mes && temp.Fecha.anio==fechaDeAtencion.anio)
				{
					cmp=strcmp(temp.nombreProfesional,nombreDoctor);
					if(cmp==0)
					{
						printf("\n\n\tPaciente: ");
						puts(temp.ApeyNom);
						printf("\n\tObservacion: ");
						puts(temp.detalle);
						printf("\n\t==============\n");
					}
				}
			}
			fread(&temp,sizeof(Turnos),1,turnos);
		}
		fclose(turnos);
		if(hayTurnos!=1)
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\tEl profesional no recibio a ningun paciente ese dia.\n");
			printf("\n\t======================================================================\n");
		}
		printf("\n\n");
		system("pause");
	}
}
// Modulo Administracion //
void getUser(char user[50],bool profesional)
{
	int cmp,longitud,contadorNum=0,contadorMay=0;
	char aux;
	bool error;
	
	do
	{
		do
		{
			system("cls");
			if(profesional==true)
			{
				encRegUserProf();
			}
			else
			{
				encRegUserRec();
			}
			printf("\n\tIngrese el usuario: ");
			_flushall();
			gets(user);
			cmp=strcmp(user,"");
			if(cmp==0)
			{
				system("cls");
				printf("\n\t[Error] - No se permite un valor vacio\n\n");
				system("pause");
				error=1;
			}	
			else
			{
				error=0;
			}
		}while(error!=0);
		
		longitud=strlen(user);
		if(longitud<6 or longitud>10)
		{
			system("cls");
			if(longitud<6)
			{
				printf("\n\t[Error] - El usuario debe tener como minimo 6 digitos.\n\n");
	
			}
			else
			{
				printf("\n\t[Error] - El usuario debe tener como maximo 10 digitos.\n\n");
			}
			system("pause");
			error=1;
		}
		else
		{
			for(int j=0;j<longitud;j++)
			{
				if(j==0)
				{
					aux=toupper(user[j]);
					if(aux==user[j])
					{
						system("cls");
						printf("\n\t[Error] - El nombre debe empezar con minuscula\n\n");
						system("pause");
						error=1;
						//break;
					}	
				}
				if(isdigit(user[j])!=0)
				{
					contadorNum++;
				}
				if(contadorNum>3)
				{
					system("cls");
					printf("\n\t[Error] - No se puede poner mas de 3 numeros.\n\n");
					system("pause");
					error=1;
					contadorNum=0;
					//break;
				}
				aux=toupper(user[j]);
				if(aux==user[j])
				{
					contadorMay++;
				}
			}
			if(contadorMay<2)
			{
				system("cls");
				printf("\n\t[Error] - El usuario debe tener almenos 2 mayusculas.\n\n");
				system("cls");
				error=1;
				//break;
			}
		}
	}while(error!=0);
}
void getPass(char password[50],bool profesional)
{
	int cmp,longitud;
	bool error;
	int aux,contadorABC=0,contadorNum=0;
	
	do
	{
		do
		{
			system("cls");
			if(profesional==true)
			{
				encRegUserProf();
			}
			else
			{
				encRegUserRec();
			}
			printf("\n\t Inserte contrasenia: ");
			_flushall();
			gets(password);
			cmp=strcmp(password,"");
			if(cmp==0)
			{
				error=1;
				system("cls");
				printf("\n\tLa contrsenia no puede estar vacia.\n\n");
				system("pause");
			}
			else
			{
				error=0;
			}
		}while(error!=0);
		
		longitud=strlen(password);
		
		if(longitud<6 or longitud>32)
		{
			error=1;
			system("cls");
			if(longitud<6)
			{
				printf("\n\t[Error]- La contrasenia debe tener almenos 6 digitos.\n\n");
			}
			else
			{
				printf("\n\t[Error] - La contrasenia debe tener como maximo 32 digitos.\n\n");
			}
			system("pause");
		}
		else
		{
			for(int i=0;i<longitud;i++)
			{
				if(ispunct(password[i])!=0)
				{
					system("cls");
					printf("\n\t[Error] - No se permiten signos de puntuacion.\n\n");
					system("pause");
					error=1;
					break;
				}
				else
				{
					if(isalpha(password[i])!=0 or isdigit!=0)
					{
						if(isalpha(password[i])!=0)
						{
							if(i>=1)
							{
								aux=(toupper(password[i-1]))-(toupper(password[i]));
								if(aux==-1)
								{
									contadorABC++;
								}
								else
								{
									contadorABC=0;
								}
								if(contadorABC>2)
								{
									system("cls");
									printf("\n\t[Error] - No se puede colocar 2 letras alfabeticamente consecutivas.\n\n");
									system("pause");
									error=1;
									break;
								}
							}	
						}
						else
						{
							if(contadorNum==0)
							{
								contadorNum++;
							}
							else
							{
								if(isdigit(password[i-1])!=0)
								{
									contadorNum++;
								}
								else
								{
									contadorNum=0;
								}
							}
							
							if(contadorNum>3)
							{
								system("cls");
								printf("\n\t[Error] - La contrasenia no puede tener mas de 3 numeros seguidos\n\n");
								system("pause");
								error=1;
								break;
							}
								
						}
					}
				}
			}
		}
	}while(error!=0);
}
void getName(char ApeyNom[50],bool profesional)
{
	int cmp;
	bool error;
	do
	{
		system("cls");
		if(profesional==true)
		{
			encRegUserProf();
		}
		else
		{
			encRegUserRec();
		}
		printf("\n\t Inserte nombre y apellido: ");
		_flushall();
		gets(ApeyNom);
		cmp=strcmp(ApeyNom,"");
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
}
void getProfesional(Profesional temp)
{
	FILE *temporal;
	Usuario aux;
	int cmp;
	bool error;
	
	do
	{
		error=0;
		system("cls");
		encRegUserProf();
		printf("\n\tInserte el id del profesional: ");
		scanf("%i",&temp.id);
		if(temp.id<0)
		{
			eNegativo();
			error=1;
		}
		else
		{
			temporal=fopen("Profesionales.dat","ab+");
			if(temporal == NULL)
			{
				system("cls");
				printf("\n\t======================================================================\n");
				printf("\n\t[Error] - No se pudo abrir el archivo 'Profesionales.dat'\n");
				printf("\n\t======================================================================\n");
				system("pause");
				exit(1);
			}
			fread(&aux,sizeof(Usuario),1,temporal);
			while(!feof(temporal))
			{
				if(aux.profesional.id==temp.id)
				{
					error=1;
					system("cls");
					printf("\n\t======================================================================\n");
					printf("\n\t[Error] - El id ya esta en uso.\n");
					printf("\n\t======================================================================\n");
					system("pause");
				}
				fread(&aux,sizeof(Usuario),1,temporal);
			}
			fclose(temporal);
		}
	}while(error!=0);
	
	
	do
	{
		system("cls");
		encRegUserProf();
		printf("\n\tInserte el DNI del profesional: ");
		scanf("%i",&temp.dni);
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
	
	do
	{
		system("cls");
		encRegUserProf();
		printf("\n\tInsertar el numero de telefono: ");
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
}
void registrar(FILE *profes,FILE *recep,int mod)
{
	char user[50];
	char password[50];
	char ApeyNom[50];
	Profesional temp;
	Usuario aux;
	Usuario verificado;
	bool error;
	int cmp;
	
	switch(mod)
	{
		case 1:
			{
				do
				{
					getUser(user,true);
					getPass(password,true);
					getName(ApeyNom,true);
					getProfesional(temp);
					profes=fopen("Profesionales.dat","ab+");
					if(profes==NULL)
					{
						system("cls");
						encRegUserProf();
						printf("\n\t======================================================================\n");
						printf("\n\t\t[Error] - no se pudo abrir el archivo 'Profesionales.dat'\n");
						printf("\n\t======================================================================\n");
						system("pause");
						exit(1);
					}
					fread(&aux,sizeof(Usuario),1,profes);
					while(!feof(profes))
					{
						cmp=strcmp(user,aux.usuario);
						if(cmp==0)
						{
							system("cls");
							encRegUserProf();
							printf("\n\t======================================================================\n");
							printf("\n\t[Error] - El usuario ya esta tomado, intente nuevamente...\n\n");
							printf("\n\t======================================================================\n");
							system("pause");
							error=1;
						}
						fread(&aux,sizeof(Usuario),1,profes);
					}	
				}while(error!=0);
				
				strcpy(verificado.usuario,user);
				strcpy(verificado.clave,password);
				strcpy(verificado.ApeyNom,ApeyNom);
				verificado.profesional.id=temp.id;
				verificado.profesional.dni=temp.dni;
				strcpy(verificado.profesional.telefono,temp.telefono);
				
				fwrite(&verificado,sizeof(Usuario),1,profes);
				fclose(profes);	
				break;
			}
		case 2:
			{
				do
				{
					getUser(user,false);
					getPass(password,false);
					getName(ApeyNom,false);
					recep=fopen("Recepcionistas.dat","ab+");
					if(recep==NULL)
					{
						system("cls");
						printf("\n\t======================================================================\n");
						printf("\n\t\t[Error] - no se pudo abrir el archivo 'Recepcionistas.dat'\n");
						printf("\n\t======================================================================\n");
						system("pause");
						exit(1);
					}
					fread(&aux,sizeof(Usuario),1,recep);
					while(!feof(recep))
					{
						cmp=strcmp(user,aux.usuario);
						if(cmp==0)
						{
							system("cls");
							printf("\n\t======================================================================\n");
							printf("\n\t[Error] - El usuario ya esta tomado, intente nuevamente...\n\n");
							printf("\n\t======================================================================\n");
							system("pause");
							error=1;
						}
						fread(&aux,sizeof(Usuario),1,recep);
					}	
				}while(error!=0);
				
				strcpy(verificado.usuario,user);
				strcpy(verificado.clave,password);
				strcpy(verificado.ApeyNom,ApeyNom);
				
				fwrite(&verificado,sizeof(Usuario),1,recep);
				fclose(profes);	
				break;
			}
	}
}
void getAtencionesPorProf()
{
	char nombreDoctor[50];
	int cmp;
	bool error, hayTurnos=0,encontrado=0;
	Turnos temp;
	float aux;
	Usuario auxiliar;
	
		do
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\tIngrese el nombre del doctor: ");
			_flushall();
			gets(nombreDoctor);
			cmp=strcmp(nombreDoctor,"");
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
			
		profe=fopen("Profesionales.dat","ab+");
		if(profe==NULL)
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t[Error] - No se pudo abrir el archivo 'Profesionales.dat'...\n");
			printf("\n\t======================================================================\n");
			system("pause");
			exit(1);
		}
		fread(&auxiliar,sizeof(Usuario),1,profe);
		while(!feof(profe))
		{
			cmp=strcmp(auxiliar.ApeyNom,nombreDoctor);
			if(cmp==0)
			{
				encontrado=1;
			}
			fread(&auxiliar,sizeof(Usuario),1,profe);
		}
		fclose(profe);
		if(encontrado!=1)
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t[Error] - No se encontro al doctor en la base de datos...\n");
			printf("\n\t======================================================================\n");
			system("pause");
		}
		else
		{
			turnos=fopen("Turnos.dat","ab+");
			if(turnos==NULL)
			{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t[Error] - No se pudo abrir el archivo 'Profesionales.dat'...\n");
			printf("\n\t======================================================================\n");
			system("pause");
			exit(1);
			}
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\tAtenciones hecha por ");
			puts(nombreDoctor);
			printf("\n\t======================================================================\n");
			fread(&temp,sizeof(Turnos),1,turnos);
			while(!feof(turnos))
			{
				hayTurnos=1;
				if(temp.atendido==1)
				{
					cmp=strcmp(temp.nombreProfesional,nombreDoctor);
					if(cmp==0)
					{
						printf("\n\n\tPaciente: ");
						puts(temp.ApeyNom);
						printf("\n\tObservacion: ");
						puts(temp.detalle);
						printf("\n\t==============\n");
					}
				}
				fread(&temp,sizeof(Turnos),1,turnos);
			}
			fclose(turnos);
			if(hayTurnos!=1)
			{
				system("cls");
				printf("\n\t======================================================================\n");
				printf("\n\tEl profesional no recibio a ningun paciente ese dia.\n");
				printf("\n\t======================================================================\n");
			}
			system("pause");
		}
}

void getRanking()
{
	Usuario archivos[100];
	Usuario aux;
	int i=0, n=0;
	Turnos infoTurnos[100];
	int cmp;
	
	profe=fopen("Profesionales.dat","ab+");
	if(profe == NULL)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t[Error] - No se pudo abrir el archivo 'Profesionales.dat'...\n");
		printf("\n\t======================================================================\n");
		system("pause");
		exit(1);
	}
	
	fread(&archivos[i],sizeof(Usuario),1,profe);
	while(!feof(profe))
	{
		i++;
		fread(&archivos[i],sizeof(Usuario),1,profe);
	}
	fclose(profe);
	if(i==0)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t[Error] - No se encuentra ningun profesional registrado...\n");
		printf("\n\t======================================================================\n");
		system("pause");
	}
	else
	{
		
		turnos=fopen("Turnos.dat","ab+");
		if(turnos==NULL)
		{
			system("cls");
			printf("\n\t======================================================================\n");
			printf("\n\t[Error] - No se pudo abrir el archivo 'Turnos.dat'...\n");
			printf("\n\t======================================================================\n");
			system("pause");
			exit(1);
		}
		
		fread(&infoTurnos[n],sizeof(Turnos),1,turnos);
		while(!feof(turnos))
		{
			n++;
			fread(&infoTurnos[n],sizeof(Turnos),1,turnos);
		}
		fclose(turnos);
		
		for(int o=0; o<n; o++)
		{
			for(int l=0; l<i; l++)
			{
				cmp=strcmp(infoTurnos[o].nombreProfesional,archivos[l].ApeyNom);
				if(cmp == 0)
				{
					if(infoTurnos[o].atendido==1)
					{
						archivos[l].profesional.puntaje++;
					}
				}
			}
		}
		/*
		for(int k=0; k<=i; k++)
		{
			for (int j=0; j<=i;j++)
			{
				if(archivos[j].profesional.puntaje > archivos[j+1].profesional.puntaje)
				{
					strcpy(aux.usuario,archivos[j].usuario);
					strcpy(aux.clave,archivos[j].clave);
					strcpy(aux.ApeyNom,archivos[j].ApeyNom);
					aux.profesional.id=archivos[j].profesional.id;
					aux.profesional.dni=archivos[j].profesional.dni;
					strcpy(aux.profesional.telefono,archivos[j].profesional.telefono);
					aux.profesional.puntaje=archivos[j].profesional.puntaje;
					
					strcpy(archivos[j].usuario,archivos[j+1].usuario);
					strcpy(archivos[j].clave,archivos[j+1].clave);
					strcpy(archivos[j].ApeyNom,archivos[j+1].ApeyNom);
					archivos[j].profesional.id=archivos[j+1].profesional.id;
					archivos[j].profesional.dni=archivos[j+1].profesional.dni;
					strcpy(archivos[j].profesional.telefono,archivos[j+1].profesional.telefono);
					archivos[j].profesional.puntaje=archivos[j+1].profesional.puntaje;
					
					strcpy(archivos[j+1].usuario,aux.usuario);
					strcpy(archivos[j+1].clave,aux.clave);
					strcpy(archivos[j+1].ApeyNom,aux.ApeyNom);
					archivos[j+1].profesional.id=aux.profesional.id;
					archivos[j+1].profesional.dni=aux.profesional.dni;
					strcpy(archivos[j+1].profesional.telefono,aux.profesional.telefono);
					archivos[j+1].profesional.puntaje=aux.profesional.puntaje;			
				}
			}
		} 
		*/
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t\t   [Ranking de profesionales por atenciones]\n");
		printf("\n\t======================================================================\n");
		for(int m=0;m<i;m++)
		{
			printf("\n\tNro %02i.- ",m+1);
			puts(archivos[m].ApeyNom);
			printf("\tPuntaje: %02i\n",archivos[m].profesional.puntaje);
			printf("\n\t============\n");
		}
		system("pause");
	}
	
}

// Para revisar cada parametro de un turno en caso de q no este apareciendo
void fichaTecnica()
{
	Turnos lector;
	
	turnos=fopen("Turnos.dat","ab+");
	if(turnos == NULL)
	{
		system("cls");
		printf("\n\t======================================================================\n");
		printf("\n\t[Error] - No se pudo abrir el archivo 'Turnos.dat'...\n");
		printf("\n\t======================================================================\n");
		system("pause");
	}
	system("cls");
	printf("\n\t======================================================================\n");
	printf("\n\tFicha tecnica de los turnos\n");
	printf("\n\t======================================================================\n");
	fread(&lector,sizeof(Turnos),1,turnos);
	while(!feof(turnos))
	{
		printf("\n\tNombre del profesional: ");
		puts(lector.nombreProfesional);
		printf("\tNombre del paciente: ");
		puts(lector.ApeyNom);
		printf("\tFecha: %02i/%02i/%i\n",lector.Fecha.dia,lector.Fecha.mes,lector.Fecha.anio);
		printf("\tDNI del paciente: %i",lector.dni);
		printf("\n\tObservacion del profesional: ");
		puts(lector.detalle);
		printf("\tAtendido: %i\n",lector.atendido);
		printf("\n\t=====\n");
		fread(&lector,sizeof(Turnos),1,turnos);
	}
	fclose(turnos);
	printf("\n\n");
	system("pause");
}


