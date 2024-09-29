#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <cstdlib> // Para a função system()
#include "login.h"

using namespace std;

// Função para ler a senha sem ecoar no console
string getPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') { // _getch() lê um caractere sem ecoar no console
        if (ch == '\b') { // Se o usuário pressionar backspace
            if (!password.empty()) {
                cout << "\b \b"; // Remove o último caractere da tela
                password.pop_back();
            }
        } else {
            password += ch;
            cout << '*'; // Ecoa um asterisco no console
        }
    }
    cout << endl;
    return password;
}

// Função para realizar o login
bool login() {
    string username, password;
    int attempts = 3;

    ifstream file("C:\\PI04\\CProjeto2Part2\\Projectotest\\UserData.csv");
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo UserData.csv" << endl;
        return false;
    }

    vector<string> user;
    vector<string> pass;

    string line, word;
    getline(file, line); // Descartar o cabeçalho

    // Lendo dados de usuário e senha do arquivo CSV
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, word, ','); // username
        user.push_back(word);
        getline(ss, word, ','); // password
        pass.push_back(word);
    }

    file.close();

    // Loop para tentativas de login
    while (attempts > 0) {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        password = getPassword();

        bool authenticated = false;

        // Verificando as credenciais fornecidas com as do arquivo CSV
        for (size_t i = 0; i < user.size(); ++i) {
            if (username == user[i] && password == pass[i]) {
                authenticated = true;
                break;
            }
        }

        if (authenticated) {
            // Limpa a tela após o login bem-sucedido
            system("cls"); // Para Windows
            // system("clear"); // Para sistemas Unix-like (Linux, macOS)

            return true;
        } else {
            attempts--;
            if (attempts > 0) {
                cout << "Login falhou! Você tem " << attempts << " tentativas restantes." << endl;
            } else {
                cout << "Login falhou! Nenhuma tentativa restante. Programa encerrado." << endl;
            }
        }
    }

    return false;
}
