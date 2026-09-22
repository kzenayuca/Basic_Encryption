#include <iostream>
#include <fstream>
#include <string>

bool processFile(const std::string& inputPath, const std::string& outputPath) {
    // RULE 1: Open both input and output files strictly in BINARY mode
    std::ifstream inFile(inputPath, std::ios::binary);
    std::ofstream outFile(outputPath, std::ios::binary);

    if (!inFile || !outFile) {
        std::cerr << "Error: Could not open the specified files." << std::endl;
        return false;
    }

    char ch;
    // RULE 2: Use .get() instead of ">>" so spaces and newlines are not discarded
    while (inFile.get(ch)) {
        
        // RULE 3: Cast to unsigned char before performing math operations
        // This ensures the byte wraps predictably between 0 and 255.
        unsigned char rawByte = static_cast<unsigned char>(ch);
        
        // Apply the cryptographic mutation (XOR cipher)
        // Running the same XOR operation a second time will decrypt it perfectly.
        unsigned char encryptedByte = rawByte;

        // Cast it back to raw char and write directly to disk
        outFile.put(static_cast<char>(encryptedByte));
    }

    inFile.close();
    outFile.close();
    return true;
}

int main() {
    std::string sourceFile = "secret.txt";
    std::string cipherFile = "encrypted.dat";
    //char mySecretKey = 'K'; // Your single-byte encryption key

    std::cout << "Encrypting " << sourceFile << "..." << std::endl;
    if (processFile(sourceFile, cipherFile)) {
        std::cout << "Success! File generated at: " << cipherFile << std::endl;
    }

    // To decrypt, simply run it backward on the encrypted file:
    processFile("encrypted.dat", "decrypted.txt");

    return 0;
}
