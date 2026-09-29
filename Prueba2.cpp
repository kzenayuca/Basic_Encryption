#include <iostream>
#include <fstream>
#include <string>


char  ejercicio1(char n){
    if(n == 'j') return 'i';
	else if(n == 'h') return 'i';
	else if(n == 'ñ') return 'n';
	else if(n == 'k') return 'l';
	else if(n == 'u') return 'v';
	else if(n == 'w') return 'v';
	else if(n == 'y') return 'z';
	else return n;
}

char ejercicio2(char n){

    //Eliminar las tildes del texto blanco y reemplazarlas por sus equivalentes sin tilde
    /*
á –> \xA0; 
é –> \x82; 
í –> \xA1; 
ó –> \xA2; 
ú –> \xA3; 
ñ –> \xA4; 
Ñ –> \xA5;
á -> 160; 
é -> 130; 
í -> 161; 
ó -> 162; 
ú -> 163; 
ñ -> 164;
    */
   if(n == '\xA0') return 'a';
	else if(n == '\x82') return 'e';
    else if(n == '\xA1') return 'i';
    else if(n == '\xA2') return 'o';
    else if(n == '\xA3') return 'u';
    else if(n == '\xA4') return 'n';
    else if(n == '\xA5') return 'N';
	else if(n == 160) return 'a';
	else if(n == 130) return 'e';
	else if(n == 161) return 'i';
	else if(n == 162) return 'o';
	else if(n == 163) return 'u';
	else if(n == 164) return 'n';
	else if(n == 165) return 'N';
	else return n;

}

char ejercicio3(char n){
    //Convertir todas las letras a mayúsculas
    if(n >= 'a' && n <= 'z') {
        return n - ('a' - 'A'); // Convert to uppercase
    }
    return n;
}

char ejercicio4(char n){
    //Eliminar los espacios en blanco y los signos de puntuación
    if(n == ' ' || n == '.' || n == ',' || n == ';' || n == ':' || n == '!' || n == '?' || n == '-' || n == '(' || n == ')' || n == '"' || n == '\'') {
        return '\0'; // Return null character to indicate removal
    }
    return n;
}
//Ejercicios 5
void frecuencias(const std::string& inputPath){
    //Implementar una funcion que calcule una 
    //tabla de frecuencias para cada letra de la A a Z.

    //Devuelve = diccionario cuyos indices son las letras analizadas y vuyos valores son las frecuecnias de las mismas en el texto (numero de veces que aparecen) Resaltar los cinco caracteres con mayor frecuencia
    std::ifstream inFile(inputPath, std::ios::binary);

    if (!inFile) {
        std::cerr << "Error: Could not open the specified files." << std::endl;
        return;
    }
    char ch;
    while (inFile.get(ch)) {

    }

    inFile.close();
    
}


//METODO KASISKI Ejercicio 6
//Recorre el texto preprocesaso y halla los trigramas en el mismo
// (sucesion de tres letras seguidas que se repiten) 
//y las distancias (numero de caracteres entre ellos) 
//entre los trigramas
void kasiski(const std::string& inputPath){
   
    std::ifstream inFile(inputPath, std::ios::binary);

    if (!inFile) {
        std::cerr << "Error: Could not open the specified files." << std::endl;
        return;
    }
    char ch;
    while (inFile.get(ch)) {

    }

    inFile.close();
}

void ejercicio7(){
    //volver a preprocesar el archivo cambiando cada caracter segun UNICODE-8
}

void ejercicio8(){
    //Volver a preprocesar el archivo cambiado cada caracter segun
    //UNICODE-8230
}

void ejercicio9(){
    //Volver a preprocesar el archivo insetando la cadena AQUÍ cada 20 caracteres,
    //texto resultante debera contener un numero de caracteres
    //que sea multiplo de 4, si es neccesario rellenar al final
    //con caracteres X segun se necesite
}


bool processFile(const std::string& inputPath, const std::string& outputPath, int cmd) {
    // RULE 1: Open both input and output files strictly in BINARY mode
    std::ifstream inFile(inputPath, std::ios::binary);
    std::ofstream outFile(outputPath, std::ios::binary);

    if (!inFile || !outFile) {
        std::cerr << "Error: Could not open the specified files." << std::endl;
        return false;
    }
    char ch;
    while (inFile.get(ch)) {
        if (cmd == 1) {
            ch = ejercicio1(ch);
        } else if (cmd == 2) {
            ch = ejercicio2(ch);
        }
        outFile.put(ch);
    }

    inFile.close();
    outFile.close();

    return true;
}

int main() {
    std::string sourceFile = "txt/TextoClaro.txt";
    std::string cipherFile = "txt/TextoEncriptado.dat";


    std::cout << "Encrypting " << sourceFile << "..." << std::endl;
    if (processFile(sourceFile, cipherFile, 1)) {
        std::cout << "Success! File generated at: " << cipherFile << std::endl;
    }

    // ->>>>>>>>>>>>>>>To decrypt, simply run it backward on the encrypted file: (It doesnt work)
    processFile("txt/TextoEncriptado.dat", "txt/TextoDesencriptado.txt",1);

    return 0;
}
