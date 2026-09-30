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
// Sustituciones
// ============================================================

string ejercicio1(const string& c) {

    if (c == "j") return "i";
    else if (c == "h") return "i";
    else if (c == "k") return "l";
    else if (c == "u") return "v";
    else if (c == "w") return "v";
    else if (c == "y") return "z";

    return c;
}


// ============================================================
// EJERCICIO 2
// Eliminar tildes
// UTF-8
// ============================================================

string ejercicio2(const string& c) {

    if (c == "á") return "a";
    else if (c == "é") return "e";
    else if (c == "í") return "i";
    else if (c == "ó") return "o";
    else if (c == "ú") return "u";

    else if (c == "Á") return "A";
    else if (c == "É") return "E";
    else if (c == "Í") return "I";
    else if (c == "Ó") return "O";
    else if (c == "Ú") return "U";

    else if (c == "ñ") return "n";
    else if (c == "Ñ") return "N";

    return c;
}


// ============================================================
// EJERCICIO 3
// Convertir a mayúsculas
// UTF-8
// ============================================================

string ejercicio3(const string& c) {

    // Letras ASCII
    if (c >= "a" && c <= "z") {
        return string(1, c[0] - ('a' - 'A'));
    }

    // Letras UTF-8
    if (c == "á") return "Á";
    if (c == "é") return "É";
    if (c == "í") return "Í";
    if (c == "ó") return "Ó";
    if (c == "ú") return "Ú";

    if (c == "ñ") return "Ñ";

    return c;
}


// ============================================================
// EJERCICIO 4
// Eliminar espacios y signos de puntuación
// ============================================================

bool ejercicio4(const string& c) {

    // Espacios
    if (c == " " ||
        c == "\n" ||
        c == "\r" ||
        c == "\t") {

        return true;
    }

    // Signos ASCII
    if (c == "." ||
        c == "," ||
        c == ";" ||
        c == ":" ||
        c == "!" ||
        c == "?" ||
        c == "-" ||
        c == "(" ||
        c == ")" ||
        c == "\"" ||
        c == "'") {

        return true;
    }

    // Signos UTF-8
    if (c == "¡" ||
        c == "¿" ||
        c == "…" ||
        c == "“" ||
        c == "”" ||
        c == "‘" ||
        c == "’") {

        return true;
    }

    return false;
}


// ============================================================
// Leer un carácter UTF-8 completo
// ============================================================

string leerUTF8(ifstream& archivo) {

    char c;

    if (!archivo.get(c)) {
        return "";
    }

    unsigned char uc = static_cast<unsigned char>(c);

    // ASCII: 0xxxxxxx
    if (uc < 128) {
        return string(1, c);
    }

    // UTF-8 de 2 bytes: 110xxxxx
    if ((uc & 0xE0) == 0xC0) {

        string resultado;
        resultado += c;

        char siguiente;

        if (archivo.get(siguiente)) {
            resultado += siguiente;
        }

        return resultado;
    }

    // UTF-8 de 3 bytes: 1110xxxx
    if ((uc & 0xF0) == 0xE0) {

        string resultado;
        resultado += c;

        char siguiente;

        if (archivo.get(siguiente)) {
            resultado += siguiente;
        }

        if (archivo.get(siguiente)) {
            resultado += siguiente;
        }

        return resultado;
    }

    // UTF-8 de 4 bytes: 11110xxx
    if ((uc & 0xF8) == 0xF0) {

        string resultado;
        resultado += c;

        char siguiente;

        if (archivo.get(siguiente)) {
            resultado += siguiente;
        }

        if (archivo.get(siguiente)) {
            resultado += siguiente;
        }

        if (archivo.get(siguiente)) {
            resultado += siguiente;
        }

        return resultado;
    }

    return string(1, c);
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

    string resultado;

    int contador = 0;
    int caracteresTotales = 0;

    // Leer carácter por carácter UTF-8
    while (true) {

        string caracter = leerUTF8(inFile);

        if (caracter.empty()) {
            break;
        }

        // Agregar el carácter completo
        resultado += caracter;

        // Contar UN carácter UTF-8
        contador++;
        caracteresTotales++;

        // Cada 20 caracteres
        if (contador == 20) {

            resultado += "AQUI";

            // "AQUI" tiene 4 caracteres
            caracteresTotales += 4;

            contador = 0;
        }
    }

    inFile.close();


    // ========================================================
    // Completar hasta que la cantidad de CARACTERES sea
    // múltiplo de 4
    // ========================================================

    while (caracteresTotales % 4 != 0) {

        resultado += 'X';
        caracteresTotales++;
    }


    // Escribir resultado
    outFile << resultado;

    outFile.close();


    cout << "\nEjercicio 9 completado." << endl;

    cout << "Caracteres finales: "
         << caracteresTotales
         << endl;

    cout << "Es multiplo de 4?: "
         << (caracteresTotales % 4 == 0 ? "SI" : "NO")
         << endl;
}

// ============================================================
// PROCESAR ARCHIVO
// ============================================================

bool processFile(const string& inputPath,
                 const string& outputPath,
                 int cmd) {

    ifstream inFile(inputPath, ios::binary);
    ofstream outFile(outputPath, ios::binary);

    if (!inFile || !outFile) {

        cerr << "Error: No se pudo abrir el archivo." << endl;

        return false;
    }

    string caracter;

    while (true) {

        caracter = leerUTF8(inFile);

        if (caracter.empty()) {
            break;
        }

        // EJERCICIO 1
        if (cmd == 1) {

            caracter = ejercicio1(caracter);
        }

        // EJERCICIO 2
        else if (cmd == 2) {

            caracter = ejercicio2(caracter);
        }

        // EJERCICIO 3
        else if (cmd == 3) {

            caracter = ejercicio3(caracter);
        }

        // EJERCICIO 4
        else if (cmd == 4) {

            if (ejercicio4(caracter)) {
                continue;
            }
        }

        outFile << caracter;
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

    cout << "[6] Archivo: Metodo Kasiski...\n";
    kasiski("output/HERALDOSNEGROS_pre.txt", "output/Trigramas.txt");

    //FALTANTES
    cout << "[7] UNICODE-8 o UTF-8 (ya procesado)\n";
    cout << "[8] UNICODE-8230 - No posible\n";
    
    
    cout << "[9] Insercion de la cadena AQUI...\n";
    ejercicio9("output/HERALDOSNEGROS_pre.txt","output/Ejercicio9.txt");


    cout << "\n========================================\n";
    cout << "        PROCESAMIENTO FINALIZADO\n";
    cout << "========================================\n";

    return 0;
}