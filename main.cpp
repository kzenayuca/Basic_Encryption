#include <iostream>
#include <string>
#include <fstream>
using namespace std;

char ejercicio1(char n);
void ejercicio2();
void ejercicio3();
void ejercicio4();


int main(){

	string Name = "TextoClaro.txt";
	ifstream archivo(Name);
	ofstream salida("Ejercicio1.txt");
 	if(!archivo.is_open()){
		cerr << "Error! No se abrio correctamente\n";
		return 1;
 	}
	if(!salida.is_open()){
		cerr << "Error\n";
		return 1;
	}


	char c;

	while(archivo.get(c)){
		salida.put(ejercicio1(c));
	}

	archivo.close();
	salida.close();

	//Preprocesado
	//Funciones sobre el texto claro antes del algoritmo
	
		// Modificaion del alfabeto por sustitucion
		// Inclusion de caracteres nulos
		// Eliminacion de no significativos. SPACE and .
		//Reemplazo de carretillas: Remplazar palabras o frases muy comunes
		//Reemplazo numerico: Caracteres a valores numericos ASCI UNICODE-8


}



char ejercicio1(char n){
	//sustituciones en el texto
	//j x i
	//h x i
	//ñ x n
	//k x l
	//u x v
	//w x v
	//y x z
	if(n == 'j') return 'i';
	else if(n == 'h') return 'i';
	else if(n == 'ñ') return 'n';
	else if(n == 'k') return 'l';
	else if(n == 'u') return 'v';
	else if(n == 'w') return 'v';
	else if(n == 'y') return 'z';
	else return n;
}

void ejercicio2(){
	//eliminar tildes del texto
	//

}

void ejercicio3 () {
	//Convertir a mayusculas el texto
}

void ejercicio4(){
	//Elimine los espacios en blanco y los signos de puntuacion
	//Guardar como "HERALDOSNEGROS_pre.txt"
}


void ejercicio5(){
	//more difficult
}