/*
encriptado de texto mediante contrase�a
programa: codifix
version: 2.1
(C) 08/11/03 
Cristian Bagemihl
cristianb@iespana.es

Descripci�n:
Este programa nos sirve para encriptar cualquier tipo de texto,
el proceso de cifrado es el siguiente:
Se lee cada caracter de un archivo y simult�neamente se combina con un
caracter de la contrase�a sumando su valor en abc y se guarda directamente
en un archivo.

Bugs:
Pora notificar cualquir bug, actualizaci�n de este programa o para 
cualquier duda o comentario, por favor env�enme un email a 
cristianb@iespana.es 

Compilador:
Este programa se puede compilar perfectamente con el compilador gratuito
Dev-C++ 4.9.8.7 que se puede descargar de 
http://www.bloodshed.net/dev/devcpp.html



*/

#include <iostream>
#include <stdlib.h>
#include <io.h>
#include <stdio.h>
using namespace std;

int menu();

int main() // funci�n que se inicia al principio
{
	menu();
	return 0;
}


int codifix(int modo)
{
	FILE *file; 
	FILE *cript;
	bool open = false;
	
	char abc[] = " \n0123456789abcdefghijklmn�opqrstuvwxyz���������ABCDEFGHIJKLMN�OPQRSTUVWXYZ���������˿?!�.;,:-_()><&�$\\|@#~��/*-+=\"\b"; // abecedario
	char endline[] = "\n"; // salto de linea
	char nada[] = "";
	
	char filename[30];//bufer de nombre archivo
	char password[30];//bufer de contrase�a
	char car[2]; //bufer
	char ccod[1]; // buffer codificado
	
	
	int tabc = sizeof(abc) -2; // tama�o de abc
	int tcn, pcn, ccn = 0; // TextCharNumber, PasswordCharNumber, CodCharNumber
	int p=0;
	
	
	cout << "Funcion codificar/decodificar iniciada" << endl << endl;
	
	// preguntar por el archivo a codificar / decodificar
	
	cout << "Introducir nombre del archivo (30 car max) [no acepta espacios]" << endl;
	cin >> filename;
	cout << endl << endl;
	
	// abrir archivo
	
	if(access(filename,0) == 0) //comprobar si el archivo existe
	{
	open = true;
	}
	else {cout << "Arhivo (" << filename << ") no existe" << endl << endl;} 
	
	if(open == true)
	{
	
		// pedir contrase�a
		
		cout << "Introduce la contrasenya por favor [sin espacios]: ";
		cin >> password;
		cout << endl;
		
		// aqu� empieza lo que realmente codifica
		
		file = fopen(filename,"r+"); // abre el archivo introducido
		if(modo==0) // si codificamos abrimos el archivo codificado.txt
		cript = fopen("codificado.txt","w");
		if(modo==1) // si decodificamos abrimos el archivo decodificado.txt
		cript = fopen("decodificado.txt","w");
		
		
		while(!feof(file))// bucle que termina al acabar el archivo
		{
			fgets(car,2,file); // leemos un caracter y lo guardamos en car
			
			if(password[p] == nada[0]) p =0; // si el caracter correspondiente de la contrase�a es nulo se vuelve al primer caracter
			
			if(p==sizeof(password)) p=0; // si llegamos al �ltimo caracter de la contrase�a volvemos al primero
			
			for(int i = 0;i<=tabc;i++) // este bucle comprueba que n�mero le corresponde al caracter que se esta leyendo seg�n abc
			{
				if(abc[i] == car[0])
				tcn = i;
			}
			
			for(int t = 0;t<=tabc;t++) // este bucle comprueba que n�mero le corresponde al caracter "p" de la contrase�a seg�n abc
			{
				if(abc[t] == password[p])
				pcn = t;
			}
			
			if(modo==0) // codificar
			{
				ccn = tcn+pcn; // se codifica el caracter sumando los dos valores que antes se hayaron
				if(ccn > tabc) ccn = ccn - tabc; // si la suma supera el tama�o de abc se debe restarle abc, si no el caracter codificado no estar�a dentro de la memoria de abc y nos dar�a problemas al decodificar ;-)
			} // fin cod
			
			if(modo==1) // dcodificar
			{
				ccn = tcn-pcn; // para decodificar debemos hacer justo lo contrario que al codificar, o sea, restar estos valores
				if(ccn < 0) ccn = ccn + tabc;// si la suma supera el tama�o de abc se debe sumarle abc al contrario que al codificar
			} // fin dcod
			strcpy(ccod,nada);
			ccod[0] = abc[ccn]; // se guarda el caracter codificado en ccod
			ccod[1] = nada[0];
			cout << ccod << "  =  " << abc[ccn] << "   " << tcn+pcn << endl;
			fputs(ccod,cript); // se guarda el caracter en el archivo
			
			p++; // se aumenta en uno p para llegar al siguiente caracter de la contrase�a
		} // fin while
		fclose(file); // se cierra el archivo a codificar/decodificar
		fclose(cript); // se cierra el archivo codificado/decodificado
	}// fin open == true
		
	cout << endl << "Funcion codificar/decodificar termidad con exito" << endl;

} // fin codif




int menu() // funci�n que se encarga de construir el men� e iniciar la funci�n correspondiente
	{
	bool salir=false;
	bool select=false;
	char item[1];
	char items[] = "xcd";
	while(salir==false)
	{
		select = false;
		
		// Escribir el men�...
		
		cout << endl << endl;
		cout << "Menu" << endl;
		cout << "c --> Codificar" << endl;
		cout << "d --> Decodificar" << endl;
		cout << "x --> Salir" << endl << endl;
		
		cin >> item; // se lee el caracter
		
		cout << endl << endl;
		
		if(item[0] == items[0]) // salir
		{
			salir = true;
			select = true;
		}
		if(item[0] == items[1]) // codificar
		{
			select = true;
			codifix(0); // iniciamos la funci�n codifix en el modo "codificar"
		}
		if(item[0] == items[2]) // dcodificar
		{
			select = true;
			codifix(1); // iniciamos la funci�n codifix en el modo "decodificar"
		}
		if(select == false) // funcion no existe
		{
			system("cls");
			cout << "Esta opcion no existe" << endl << endl;
		}
	}
}
