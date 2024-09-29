// viatura.cpp

#include "viatura.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

// Declaração do mapa que armazenará as viaturas em memória
unordered_map<string, Viatura> inventorio;

// Localização do arquivo CSV que contém o inventário das viaturas
const string INVENTORY_FILE = "C:\\PI04\\CProjeto2Part2\\Projectotest\\StandViaturasInventorio.csv";

// Função para carregar o inventário de viaturas a partir de um arquivo CSV
void carregarInventorio(const string& filename) {
    ifstream file(filename);  // Abre o arquivo para leitura
    if (!file.is_open()) {  // Verifica se o arquivo foi aberto corretamente
        cerr << "Erro ao abrir o arquivo para carregar!" << endl;  // Mensagem de erro se falhar a abertura
        return;  // Retorna imediatamente em caso de erro
    }

    inventorio.clear();  // Limpa o inventário antes de carregar novos dados
    string line;
    while (getline(file, line)) {  // Lê cada linha do arquivo
        stringstream ss(line);  // Cria um stringstream para processar a linha
        Viatura viatura;
        // Extrai cada campo da linha usando o delimitador '/'
        getline(ss, viatura.id, '/');
        getline(ss, viatura.matricula, '/');
        getline(ss, viatura.marca, '/');
        getline(ss, viatura.modelo, '/');
        getline(ss, viatura.preco, '/');
        getline(ss, viatura.data, '/');
        inventorio[viatura.id] = viatura;  // Adiciona a viatura ao mapa usando o ID como chave
    }
    file.close();  // Fecha o arquivo após a leitura completa
}

// Função para salvar o inventário de viaturas de volta ao arquivo CSV
void salvarInventorio(const string& filename) {
    ofstream file(filename);  // Abre o arquivo para escrita
    if (!file.is_open()) {  // Verifica se o arquivo foi aberto corretamente
        cerr << "Erro ao abrir o arquivo para salvar!" << endl;  // Mensagem de erro se falhar a abertura
        return;  // Retorna imediatamente em caso de erro
    }

    // Itera sobre o mapa de viaturas e escreve cada uma no arquivo, separadas por '/'
    for (const auto& [id, viatura] : inventorio) {
        file << viatura.id << "/" << viatura.matricula << "/" << viatura.marca << "/"
             << viatura.modelo << "/" << viatura.preco << "/" << viatura.data << endl;
    }
    file.close();  // Fecha o arquivo após a escrita completa
}

// Função para exibir os detalhes de uma viatura específica
void exibirViatura(const Viatura& viatura) {
    // Formato de exibição dos dados da viatura
    cout << "ID: " << viatura.id << " | Matricula: " << viatura.matricula
         << " | Marca: " << viatura.marca << " | Modelo: " << viatura.modelo
         << " | Preço: " << viatura.preco << " | Data: " << viatura.data << endl;
}

// Função para mostrar todo o inventário de viaturas
void mostrarInventorio() {
    for (const auto& [id, viatura] : inventorio) {
        exibirViatura(viatura);  // Chama a função exibirViatura para cada viatura no inventário
    }
}

// Função para selecionar viaturas por marca e, opcionalmente, por modelo
void selecionarPorMarcaModelo() {
    string marca, modelo;
    cout << "Marca: ";
    cin >> marca;
    cout << "Modelo (pressione Enter para listar todos os modelos da marca): ";
    getline(cin >> ws, modelo);  // Permite que o modelo seja opcional usando getline para ler a linha inteira

    for (const auto& [id, viatura] : inventorio) {
        if (viatura.marca == marca && (modelo.empty() || viatura.modelo == modelo)) {
            exibirViatura(viatura);  // Exibe a viatura se corresponder à marca e, opcionalmente, ao modelo
        }
    }
}

// Função para selecionar viaturas por matrícula ou ID
void selecionarPorMatriculaOuId() {
    string matriculaOuId;
    cout << "Matricula ou ID: ";
    cin >> matriculaOuId;

    if (inventorio.find(matriculaOuId) != inventorio.end()) {
        exibirViatura(inventorio[matriculaOuId]);  // Exibe a viatura se o ID ou matrícula existirem no inventário
    } else {
        for (const auto& [id, viatura] : inventorio) {
            if (viatura.matricula == matriculaOuId) {
                exibirViatura(viatura);  // Exibe a viatura se a matrícula existir no inventário
                return;
            }
        }
        cout << "Viatura não encontrada." << endl;  // Mensagem se nenhuma viatura for encontrada
    }
}

// Função para modificar os detalhes de uma viatura existente
void modificarSelecao() {
    string id;
    cout << "ID da viatura a modificar: ";
    cin >> id;

    if (inventorio.find(id) != inventorio.end()) {
        Viatura& viatura = inventorio[id];  // Obtém uma referência para a viatura através do ID
        cout << "Nova Matricula: ";
        cin >> viatura.matricula;
        cout << "Nova Marca: ";
        cin >> viatura.marca;
        cout << "Novo Modelo: ";
        cin >> viatura.modelo;
        cout << "Novo Preço: ";
        cin >> viatura.preco;
        cout << "Nova Data (dia/mes/ano): ";
        cin >> viatura.data;
        cout << "Viatura modificada com sucesso." << endl;  // Mensagem de confirmação após a modificação
        salvarInventorio(INVENTORY_FILE);  // Salva as mudanças no inventário de viaturas
    } else {
        cout << "Viatura com ID " << id << " não encontrada." << endl;  // Mensagem se o ID não existir no inventário
    }
}

// Função para remover uma viatura do inventário por matrícula ou ID
void removerPorMatriculaOuId() {
    string matriculaOuId;
    cout << "Matricula ou ID: ";
    cin >> matriculaOuId;

    if (inventorio.erase(matriculaOuId) > 0) {
        cout << "Viatura removida com sucesso." << endl;  // Mensagem de confirmação se a viatura foi removida
        salvarInventorio(INVENTORY_FILE);  // Salva as mudanças no inventário de viaturas após a remoção
    } else {
        for (auto it = inventorio.begin(); it != inventorio.end(); ++it) {
            if (it->second.matricula == matriculaOuId) {
                inventorio.erase(it);  // Remove a viatura se a matrícula for encontrada
                cout << "Viatura removida com sucesso." << endl;  // Mensagem de confirmação após a remoção
                salvarInventorio(INVENTORY_FILE);  // Salva as mudanças no inventário de viaturas após a remoção
                return;
            }
        }
        cout << "Viatura não encontrada." << endl;  // Mensagem se a viatura não for encontrada no inventário
    }
}

// Função para validar o formato da matrícula de uma viatura
bool validarMatricula(const string& matricula) {
    regex formatoMatricula(R"([0-9a-zA-Z]+\s*-\s*[0-9a-zA-Z]+\s*-\s*[0-9a-zA-Z]+)");
    return regex_match(matricula, formatoMatricula);  // Retorna true se a matrícula corresponder ao padrão especificado
}

// Função para adicinar nova viatura
void adicionarNovaViatura() {
    Viatura novaViatura;
    do {
        cout << "ID: ";
        cin >> novaViatura.id;
        if (inventorio.find(novaViatura.id) != inventorio.end()) {
            cout << "ID já existe. Por favor, escolha outro." << endl; // Informa ao usuário que o ID já está em uso
        } else {
            break; // Sai do loop se o ID for único
        }
    } while (true);

    do {
        cout << "Matricula: ";
        cin >> novaViatura.matricula;
        if (!validarMatricula(novaViatura.matricula)) {
            cout << "Formato de matrícula inválido. Por favor, insira no formato correto (número ou letras - número ou letras - número ou letras)." << endl; // Informa ao usuário sobre o formato incorreto da matrícula
        } else {
            bool matriculaRepetida = false;
            for (const auto& [id, viatura] : inventorio) {
                if (viatura.matricula == novaViatura.matricula) {
                    cout << "Matrícula já existe. Por favor, escolha outra." << endl; // Informa ao usuário que a matrícula já está em uso
                    matriculaRepetida = true;
                    break;
                }
            }
            if (!matriculaRepetida) break; // Sai do loop se a matrícula for única
        }
    } while (true);

    cout << "Marca: ";
    cin >> novaViatura.marca;
    cout << "Modelo: ";
    cin >> novaViatura.modelo;
    cout << "Preço: ";
    cin >> novaViatura.preco;
    cout << "Data (dia/mes/ano): ";
    cin >> novaViatura.data;

    inventorio[novaViatura.id] = novaViatura; // Adiciona a nova viatura ao inventário usando o ID como chave
    cout << "Nova viatura adicionada com sucesso." << endl; // Confirmação ao usuário de que a viatura foi adicionada com sucesso
    salvarInventorio(INVENTORY_FILE); // Salva as alterações no arquivo de inventário
}