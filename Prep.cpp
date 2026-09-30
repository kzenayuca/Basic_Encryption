#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;


// ============================================================
// EJERCICIO 1
// ============================================================

char ejercicio1(char n) {

    if (n == 'j') return 'i';
    else if (n == 'h') return 'i';
    else if (n == 'k') return 'l';
    else if (n == 'u') return 'v';
    else if (n == 'w') return 'v';
    else if (n == 'y') return 'z';
    else return n;
}


// ============================================================
// EJERCICIO 2
// Eliminar tildes
// Los valores corresponden a CP850, no a UTF-8.
// ============================================================

char ejercicio2(char n) {

    unsigned char c = static_cast<unsigned char>(n);

    if (c == 160) return 'a'; // á
    else if (c == 130) return 'e'; // é
    else if (c == 161) return 'i'; // í
    else if (c == 162) return 'o'; // ó
    else if (c == 163) return 'u'; // ú
    else if (c == 164) return 'n'; // ñ
    else if (c == 165) return 'N'; // Ñ

    return n;
}


// ============================================================
// EJERCICIO 3
// Convertir a mayúsculas
// ============================================================

char ejercicio3(char n) {

    if (n >= 'a' && n <= 'z') {
        return n - ('a' - 'A');
    }

    return n;
}


// ============================================================
// EJERCICIO 4
// Eliminar espacios y signos de puntuación
// ============================================================

char ejercicio4(char n) {

    if (n == ' ' ||
        n == '.' ||
        n == ',' ||
        n == ';' ||
        n == ':' ||
        n == '!' ||
        n == '?' ||
        n == '-' ||
        n == '(' ||
        n == ')' ||
        n == '"' ||
        n == '\'' ||
        n == '\n' ||
        n == '\r' ||
        n == '\t') {

        return '\0';
    }

    return n;
}


// ============================================================
// EJERCICIO 5
// TABLA DE FRECUENCIAS
// ============================================================

void frecuencias(const string& inputPath, const string& outputPath = "") {

    ifstream inFile(inputPath, ios::binary);
    ofstream outFile(outputPath, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    // Frecuencia de A-Z
    int frecuencia[26] = {0};

    char ch;

    while (inFile.get(ch)) {

        if (ch >= 'A' && ch <= 'Z') {
            frecuencia[ch - 'A']++;
        }
        else if (ch >= 'a' && ch <= 'z') {
            frecuencia[ch - 'a']++;
        }
    }

    inFile.close();

    outFile << "========================================\n";
    outFile << "TABLA DE FRECUENCIAS\n";
    outFile << "========================================\n";


    for (int i = 0; i < 26; i++) {

        outFile << static_cast<char>('A' + i)
             << " : "
             << frecuencia[i]
             << endl;
    }


    // Crear vector para ordenar las frecuencias
    vector<pair<char, int>> ordenadas;

    for (int i = 0; i < 26; i++) {
        ordenadas.push_back({
            static_cast<char>('A' + i),
            frecuencia[i]
        });
    }


    // Ordenar de mayor a menor
    sort(
        ordenadas.begin(),
        ordenadas.end(),
        [](const pair<char, int>& a,
           const pair<char, int>& b) {

            return a.second > b.second;
        }
    );


    // Mostrar las 5 más frecuentes
    outFile << "\n========================================\n";
    outFile << "     CINCO LETRAS MAS FRECUENTES\n";
    outFile << "========================================\n";

    for (int i = 0; i < 5; i++) {

        outFile << i + 1
             << ". "
             << ordenadas[i].first
             << " -> "
             << ordenadas[i].second
             << " veces"
             << endl;
    }

    outFile.close();
}


// ============================================================
// EJERCICIO 6
// ATAQUE DE KASISKI
// Buscar trigramas repetidos y sus distancias
// ============================================================

void kasiski(const string& inputPath, const string& outputPath = "") {

    ifstream inFile(inputPath, ios::binary);
    ofstream outFile(outputPath, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string texto;
    char ch;

    while (inFile.get(ch)) {

        if (ch >= 'A' && ch <= 'Z') {
            texto += ch;
        }
        else if (ch >= 'a' && ch <= 'z') {
            texto += ch - ('a' - 'A');
        }
    }

    inFile.close();


    outFile << "\n========================================\n";
    outFile << "             ATAQUE KASISKI\n";
    outFile << "========================================\n";


    // Guardamos cada trigramas y las posiciones donde aparece
    map<string, vector<int>> posiciones;


    // Recorrer el texto buscando trigramas
    for (int i = 0; i + 2 < static_cast<int>(texto.length()); i++) {

        string trigram = texto.substr(i, 3);

        posiciones[trigram].push_back(i);
    }


    // Buscar los trigramas repetidos
    bool encontrados = false;

    for (const auto& elemento : posiciones) {

        const string& trigram = elemento.first;
        const vector<int>& pos = elemento.second;


        // Solo nos interesan los que aparecen más de una vez
        if (pos.size() > 1) {

            encontrados = true;

            outFile << "\nTrigrama: " << trigram << endl;

            outFile << "Posiciones: ";

            for (int p : pos) {
                outFile << p << " ";
            }

            outFile << endl;

            outFile << "Distancias: ";

            for (size_t i = 1; i < pos.size(); i++) {

                int distancia = pos[i] - pos[i - 1];

                outFile << distancia << " ";
            }

            outFile << endl;
        }
    }


    if (!encontrados) {
        outFile << "\nNo se encontraron trigramas repetidos.\n";
    }
    outFile.close();
}


// ============================================================
// EJERCICIO 7
// Repetir los Ejerici1os 1 a 4 cambiado cada caracter segun UNICODE-8/UTF-8
// ============================================================

void ejercicio7() {

    cout << "\nEjercicio 7 pendiente.\n";
}


// ============================================================
// EJERCICIO 8
// Repetir los Ejercicios 1 a 4 cambiado cada caracter según UNICODE-8230

//Ejercicio sin mucho sentido, OMITIR
// ============================================================

void ejercicio8() {

    cout << "\nEjercicio 8 pendiente.\n";
}


// ============================================================
// EJERCICIO 9
// Insertar AQUÍ cada 20 caracteres
// y completar hasta múltiplo de 4
// ============================================================

void ejercicio9(const string& inputPath,
                const string& outputPath) {

    ifstream inFile(inputPath, ios::binary);
    ofstream outFile(outputPath, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string texto;
    char ch;

    while (inFile.get(ch)) {
        texto += ch;
    }

    inFile.close();


    string resultado;

    int contador = 0;

    for (char c : texto) {

        resultado += c;
        contador++;

        if (contador == 20) {

            resultado += "AQUI";

            contador = 0;
        }
    }


    // Completar hasta múltiplo de 4
    while (resultado.length() % 4 != 0) {
        resultado += 'X';
    }


    outFile << resultado;

    outFile.close();


    cout << "\nEjercicio 9 completado." << endl;
    cout << "Caracteres finales: "
         << resultado.length()
         << endl;

    cout << "¿Es multiplo de 4?: "
         << (resultado.length() % 4 == 0 ? "SI" : "NO")
         << endl;
}



bool processFile(const string& inputPath,
                 const string& outputPath,
                 int cmd) {

    ifstream inFile(inputPath, ios::binary);
    ofstream outFile(outputPath, ios::binary);

    if (!inFile || !outFile) {

        cerr << "Error: No se pudo abrir el archivo." << endl;

        return false;
    }


    char ch;

    while (inFile.get(ch)) {

        if (cmd == 1) {
            ch = ejercicio1(ch);
        }

        else if (cmd == 2) {
            ch = ejercicio2(ch);
        }

        else if (cmd == 3) {
            ch = ejercicio3(ch);
        }

        else if (cmd == 4) {
            ch = ejercicio4(ch);
        }


        // Si ejercicio4 indica eliminar
        // no escribimos el caracter.
        if (ch != '\0') {
            outFile.put(ch);
        }
    }


    inFile.close();
    outFile.close();

    return true;
}


int main() {

    string sourceFile = "txt/TextoClaro.txt";

    cout << "========================================\n";
    cout << "     PREPROCESAMIENTO DE TEXTO\n";
    cout << "========================================\n";


    cout << "\n[1] Realizando las sustituciones iniciales...\n";

    processFile(sourceFile,"output/Ejercicio1.txt",1);

    cout << "[2] Eliminando tildes...\n";

    processFile("output/Ejercicio1.txt","output/Ejercicio2.txt",2);

    cout << "[3] Convirtiendo a mayusculas...\n";

    processFile("output/Ejercicio2.txt","output/Ejercicio3.txt",3);

    cout << "[4] Eliminando espacios y puntuacion...\n";

    processFile("output/Ejercicio3.txt","output/HERALDOSNEGROS_pre.txt",4);
    
    cout << "[5] Archivo: Tabla de Frecuencias...\n";
    frecuencias("output/HERALDOSNEGROS_pre.txt", "output/TablaFrecuencias.txt");

    cout << "[6] Archivo: Método Kasiski...\n";
    kasiski("output/HERALDOSNEGROS_pre.txt", "output/Trigramas.txt");

    //FALTANTES
    cout << "[7] FFFFFFUNICODE-8...\n";
    cout << "[8] FFFFFFFFUNICODE-8230...\n";
    
    
    cout << "[9] Inserción de la cadena AQUÍ...\n";
    ejercicio9("output/HERALDOSNEGROS_pre.txt","output/Ejercicio9.txt");


    cout << "\n========================================\n";
    cout << "        PROCESAMIENTO FINALIZADO\n";
    cout << "========================================\n";

    return 0;
}