#include <openssl/sha.h>
#include <cstring>
#include <stdio.h>

using namespace std;

string hash_information(string texto_string) {
    unsigned char hashResultante[32];
    char texto[texto_string.length() + 1];

    strcpy(texto, texto_string.c_str());

    SHA256((const unsigned char*) texto, strlen(texto), hashResultante);

    string result = "";
    for (int i= 0; i < 32; i++) {
        char car[2];
        sprintf(car, "%.2x", hashResultante[i]);
        result += (string) car;
    }
    return result;
}
