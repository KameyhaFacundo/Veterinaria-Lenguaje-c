#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct{
	int dia,mes,anio;
}fecha;

typedef struct{
	char mascota[50];
        char duenio[50];
        fecha ut;
		fecha up;
	char servicio[50];
}cliente;


typedef struct {
	char s[50];
	float precio;
}serv;

int menu();
void apertura(char c[]);
void alta_solicitud(char c[],cliente cl);
cliente ingresar_cliente(char lservicio[]);
fecha leer_fecha();
void nuevo_servicio(char nombre[]);
void mostrar_lista(char c[]);
void mostrar_estructura(cliente cl);
void mostrar_servicios(char nombre[]);
void modificar_turno(char nombre[],char lservicio[]);
int control(char c[]);
int palabra(char c[]);
int control_fechas(fecha f1,fecha f2);
fecha fecha_actual();
void servicios_basicos(char c[]);


int main(int argc,char*argv[]){
    
	system("clear || cls");
	
   int op;
   char c[]="veterinaria.dat",lservicio[]="servicios.dat";
   cliente cl;
   fecha f;

   apertura(c);

	do{
		printf("\t\n\n" );
		printf("\t----||| VETERINARIA |||----\n" );
		op=menu();


		switch(op){
			case 1:
				cl=ingresar_cliente(lservicio);
				alta_solicitud(c,cl);
				break;
			case 2:
				nuevo_servicio(lservicio);
				break;
			case 3:
				mostrar_lista(c);
				break;
			case 4:
				modificar_turno(c,lservicio);
				break;
			case 5:
				printf("\nFin del programa...\n\n");
				break;
			default:
				printf("\nOpcion incorrecta !\n\n");
				break;
		}
		
	}while(op!=5);
return 0;
}

int menu(){
		int op;

		printf("\n1. Alta solicitud de turnos");
		printf("\n2. Alta de nuevos servicios");
		printf("\n3. Mostrar agenda");
		printf("\n4. Modificar turno");
		printf("\n5. Salir del programa\n");
		printf("\n Ingrese una OPCION : ");
		scanf("%d",&op);

return op;
}


void apertura(char c[]){
	FILE *p;

		p=fopen(c,"r");

     if(p==NULL){
        printf("Error: El archivo no existe. Se creara\n");

		p=fopen(c,"wt");

	 if(p==NULL){
		printf("\nError: Es imposible crear el archivo.. Fin del progrma");
		exit(0);
		}
	}
	fclose(p);
}

void alta_solicitud(char c[],cliente cl){
    FILE *p;
	p=fopen(c,"a");
		if(p==NULL){
			printf("\nError: No se a podido acceder al archivo\n");
		}
		else{
			fwrite(&cl,sizeof(cl),1,p);
			printf("\nDato guardado con exito..");
			
fclose(p);
     		}
}

cliente ingresar_cliente(char lservicio[]){
    cliente c;
	fecha a;
	char op;
	a=fecha_actual();
		printf("\nIngrese nombre del animal : ");
		fgetc(stdin);
		scanf("%[^\n]",c.mascota);
	
	do{
		printf("Ingrese nombre del duenio : ");
		fgetc(stdin);
		scanf("%[^\n]",c.duenio);
	  if(palabra(c.duenio)==0){
			printf("\nError: La palabra ingresada debe contener solo letras. Intentelo nuevamente.\n");
	   }
  	  }while(palabra(c.duenio)==0);
				
		mostrar_servicios(lservicio);
				
	do{
		printf("\nIngrese el servicio solicitado : ");
		fgetc(stdin);
		scanf("%[^\n]",c.servicio);
		if(control(c.servicio)==0){
			printf("\nError : El servicio ingresado no existe.\n");
		}
	}while(control(c.servicio)==0);
		printf("\n Es la primera vez que viene S/N : ");
		fgetc(stdin);
		scanf("%c",&op);
	if(toupper(op)=='S'){
		c.ut=fecha_actual();
	do{
       	printf("\n Ingrese la fecha del proximo turno: ");
       	c.up=leer_fecha();
	if(control_fechas(c.ut,c.up)==0||control_fechas(a,c.up)==0 ){
		printf("\nError: La fecha ingresada no es valida.\n");
	}
	}while (control_fechas(c.ut,c.up)==0||control_fechas(a,c.up)==0 );
			
	}
	if(toupper(op)=='N'){
	  do{
		printf("\n Ingrese la fecha del ultimo turno: ");
		c.ut=leer_fecha();
	if( control_fechas(c.ut,a)==0 ){
		printf("\nError: La fecha ingresada no es valida.\n");
	}
	}while ( control_fechas(c.ut,a)==0);
				
	do{
        printf("\n--Ingrese la fecha del proximo turno--\n");
        c.up=leer_fecha();
	if(control_fechas(c.ut,c.up)==0||control_fechas(a,c.up)==0 ){
		printf("\nError : La fecha ingresada no es valida.\n");
	}
	}while (control_fechas(c.ut,c.up)==0||control_fechas(a,c.up)==0 );
	}

   return c;
	 
}


fecha leer_fecha(){
   fecha f;

  do{
		printf("\nAnio : ");
		scanf("%d",&f.anio);
		if(f.anio<1000 || f.anio>2030){
			printf("\nError: El dato ingresado no es valido.\n");
		}
	}while(f.anio<1000 || f.anio>2030);
	do{
		printf("Mes : ");
        scanf("%d",&f.mes);
		if(f.mes<=0 || f.mes>12){
		printf("\nError: El dato ingresado no es valido.\n");
		}

    }while(f.mes<=0 || f.mes>12);
    
	if(f.mes==2){
		do{
		printf("Dia : ");
		scanf("%d",&f.dia);
		if(f.dia<=0 || f.dia>28){
			printf("\nError: El dato ingresado no es valido.\n");
		}
		}while(f.dia<=0 || f.dia>28);

	}
	else{
	    do{
			printf("Dia : ");
			scanf("%d",&f.dia);
			
			if(f.dia<=0 || f.dia>31){
				printf("\nError: El dato ingresado no es valido.\n");
			}
		
		}while(f.dia<=0 || f.dia>31);
	}
	return f;
}

void nuevo_servicio(char lservicio[]){
	FILE *p;

	char s1[]="Peinado",s2[]="Banio",s3[]="Corte de pelos higienicos",c;
	  serv sr;
	if(fopen(lservicio,"rb")==NULL){
		printf("\nEror: No se pudo abrir el archivo. Se creara uno nuevo...\n");
		p=fopen(lservicio,"a");

		strcpy(sr.s,s1);
		sr.precio=50;
		fwrite(&sr,sizeof(sr),1,p);

		strcpy(sr.s,s2);
		sr.precio=100.3;
		fwrite(&sr,sizeof(sr),1,p);

		strcpy(sr.s,s3);
		sr.precio=200;
		fwrite(&sr,sizeof(sr),1,p);
		fclose(p);
	}
	else{
		p=fopen(lservicio,"at");
		printf("\nDesea ver el listado de servicios S/N:");
		fgetc(stdin);
		scanf("%c",&c);
		if(toupper(c)=='S'){
				mostrar_servicios(lservicio);
		}
		do{
			printf("\nNuevo servicio:");
			fgetc(stdin);
			scanf("%[^\n]",sr.s);
			if(palabra(sr.s)==0){
				printf("\nError: La palabra ingresada solo debe contener letras. Intentelo nuevamente.\n");
			}
	}while(palabra(sr.s)==0);
		printf("\nPrecio: ");
		scanf("%f",&sr.precio);
		fwrite(&sr,sizeof(sr),1,p);
		printf("\nDato guardado con exito.\n");
	}
	fclose(p);
}

void mostrar_lista(char c[]){
	FILE *p;
	p=fopen(c,"rb");
	fecha f;
	f=fecha_actual();
	int b=0;
	long i,t;
    cliente cl;
	fseek(p,0,2);
	t=ftell(p)/sizeof(cl);
	rewind(p);
	
    printf("\n\t--- Listado del dia %d/%d/%d ---\n",f.dia,f.mes,f.anio);

	for(i=0;i<t;i++){
			
		fread(&cl,sizeof(cl),1,p);
		if(f.dia==cl.up.dia && f.mes==cl.up.mes && f.anio==cl.up.anio){
			mostrar_estructura(cl);
			printf("\n\n");
			b++;
		}	
	}
	if(b==0)
		printf("\nError: No hay pacientes este dia.\n");
}


void modificar_turno(char nombre[],char lservicio[]){
	FILE *p=fopen(nombre,"rt+");
	char busq[50];
	cliente cl;
	int b=0;
	long i,t;

	printf("\nIngrese el nombre de la mascota o del duenio\n");

	fgetc(stdin);
	scanf("%[^\n]",busq);

	fseek(p,0,2);
	t=ftell(p)/sizeof(cl);
	rewind(p);
	for(i=0;i<t;i++){
		fread(&cl,sizeof(cl),1,p);
		
		if(strcmp(cl.mascota,busq)==0 || strcmp(cl.duenio,busq)==0){
			fseek(p,ftell(p)-sizeof(cl),0);
			cl=ingresar_cliente(lservicio);
			fwrite(&cl,sizeof(cl),1,p);
			b++;
		}

	}
	if(b!=0){
	printf("\nLos datos fueron modificados con exito.\n");
	}
	else{
		printf("\nError: No se encontro %s en el registro.\n",busq);
	}
	fclose(p);
}


void mostrar_estructura(cliente cl){

	printf("\nNombre de la mascota : %s", cl.mascota);
	printf("\nNombre del duenio: %s", cl.duenio);
	printf("\nServicio Solicitado : %s", cl.servicio);
	printf("\nFecha del ultimo turno: %d/%d/%d",cl.ut.dia,cl.ut.mes,cl.ut.anio);
	printf("\nFecha del proximo turno: %d/%d/%d",cl.up.dia,cl.up.mes,cl.up.anio);
}


void mostrar_servicios(char lservicio[]){
	FILE *p=fopen(lservicio,"rb");
	serv servicio;
	if(fopen(lservicio,"rb")==NULL){
		printf("\nError: No se pudo abrir el archivo. Se creara uno nuevo...\n");
		servicios_basicos(lservicio);
		p=fopen(lservicio,"rb");
		long i,t;
		fseek(p,0,2); 
		t=ftell(p)/sizeof(lservicio);
		rewind(p);
		printf("\n\t-----SERVICIOS ACTUALES------\n");

		for(i=0;i<t;i++){
			fread(&servicio,sizeof(servicio),1,p);
			printf("NOMBRE= %s------>> PRECIO= $%.4f\n",servicio.s,servicio.precio);
		}
		fclose(p);
	}
	else{
		long i,t;
		fseek(p,0,2);
		t=ftell(p)/sizeof(servicio);
		rewind(p);
		printf("\n\t-----SERVICIOS ACTUALES------\n");

		for(i=0;i<t;i++){
			fread(&servicio,sizeof(servicio),1,p);
			printf("NOMBRE= %s , PRECIO= $%.4f\n",servicio.s,servicio.precio);
		}
		fclose(p);
	}
}


int control(char c[]){
	char nombre[]="servicios.dat";
	FILE *p=fopen(nombre,"rt");
	serv servicio;
	int b=0;
	long t,i;
	fseek(p,0,2);
	t=ftell(p)/sizeof(servicio);
	rewind(p);

	for(i=0;i<t;i++){
		fread(&servicio,sizeof(servicio),1,p);
		if(strcmp(servicio.s,c)==0){
			b++;
		}

	}
	if(b!=0){return 1;}
	else{return 0;}
}


int palabra(char c[]){

	int i,b=0;
	for(i=0;i<strlen(c);i++){
		if(islower(c[i]) || isupper(c[i]) || isspace(c[i])){
				b++;
		}
	}
	if(b==strlen(c))
		return 1;
	else
		return 0;
}


int control_fechas(fecha u, fecha p){
	int b;
		if(u.anio>p.anio){
			b=0;
		}
		else{
			if (u.anio<p.anio) {
				b=1;
			}
			else{
				if(u.mes>p.mes){
					b=0;
				}
				else{
					if(u.mes<p.mes){
						b=1;
					}
					else{
						if(u.dia>p.dia){
							b=0;
						}
						else{
							b=1;
						}
					}
				}
			}
		}

return b;
}


fecha fecha_actual(){
		fecha a;
		time_t t;
 		struct tm *tm;

 		t=time(NULL);
		tm=localtime(&t);

		a.dia=tm->tm_mday;
		a.mes=tm->tm_mon+1;
		a.anio=1900+tm->tm_year;
return a;
}


void servicios_basicos(char c[]){
	FILE *p=fopen(c,"ab");
	char s1[]="Peinado",s2[]="Banio",s3[]="Corte de pelos";
	serv sr;

	strcpy(sr.s,s1);
	sr.precio=50;
	fwrite(&sr,sizeof(sr),1,p);

	strcpy(sr.s,s2);
	sr.precio=100.3;
	fwrite(&sr,sizeof(sr),1,p);
	strcpy(sr.s,s3);
	sr.precio=200;
	fwrite(&sr,sizeof(sr),1,p);
	fclose(p);

}
