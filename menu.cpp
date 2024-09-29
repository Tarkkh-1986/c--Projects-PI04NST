#include <iostream>
#include <functional>
#include <map>
#include "viatura.h"  // Inclui o arquivo de cabeçalho para as funções relacionadas às viaturas
#include "login.h"    // Inclui o arquivo de cabeçalho para as funções relacionadas ao login

using namespace std;

// Função que exibe o menu principal e permite interação com o usuário
void menu() {
    // Mapa que associa opções do menu a funções correspondentes
    map<int, function<void()>> menuOpcoes = {
        {1, mostrarInventorio},            // Opção 1: Mostrar todo o inventário
        {2, selecionarPorMarcaModelo},     // Opção 2: Selecionar viaturas por marca/modelo
        {3, selecionarPorMatriculaOuId},   // Opção 3: Selecionar viaturas por matrícula ou ID
        {4, modificarSelecao},             // Opção 4: Modificar uma viatura selecionada
        {5, removerPorMatriculaOuId},      // Opção 5: Remover uma viatura por matrícula ou ID
        {6, adicionarNovaViatura}          // Opção 6: Adicionar uma nova viatura ao inventário
    };

    int opcao;
    do {
        // Exibe o menu formatado
        cout << "\n************************************\n";
        cout << "*           Menu de Selecao         *\n";
        cout << "************************************\n";
        cout << "*  1. Mostrar todo o inventorio     *\n";
        cout << "*  2. Selecionar atraves de marca/modelo *\n";
        cout << "*  3. Selecionar atraves de matricula ou id *\n";
        cout << "*  4. Selecionar e modificar viatura *\n";
        cout << "*  5. Remover atraves da matricula/id *\n";
        cout << "*  6. Adicionar nova viatura        *\n";
        cout << "*  7. Sair do programa             *\n";
        cout << "************************************\n";
        cout << "Escolha uma opcao: ";

        // Leitura da opção escolhida pelo usuário
        cin >> opcao;

        // Verifica se a opção existe no mapa
        if (menuOpcoes.find(opcao) != menuOpcoes.end()) {
            menuOpcoes[opcao]();  // Chama a função correspondente à opção selecionada
        } else if (opcao != 7) {
            cout << "Opcao invalida. Tente novamente." << endl;  // Mensagem de opção inválida
        }
    } while (opcao != 7);  // Repete até que o usuário escolha a opção de sair

    cout << "Saindo do programa..." << endl;  // Mensagem de encerramento do programa
}

int main() {
    if (!login()) {  // Realiza o login e verifica se foi bem-sucedido
        cout << "Excesso de tentativas de login falhadas. Programa encerrado." << endl;  // Mensagem de falha no login
        return 1;  // Encerra o programa com código de erro
    }

    // Carrega o inventário de viaturas a partir de um arquivo CSV
    carregarInventorio("C:\\PI04\\CProjeto2Part2\\Projectotest\\StandViaturasInventorio.csv");

    // Exibe o menu principal para o usuário interagir
    menu();

    return 0;  // Encerra o programa com sucesso
}
