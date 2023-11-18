#include<iostream>
#include <locale.h>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

// Definindo os tipos de atributos
string atributos_base[3] = {"Normal", "Fogo", "Água"};

// Definindo a estrutura do Pokémon
typedef struct pokemon {
    int numero;
    string nome;
    int tipo; // Deve ser uma das opções em atributos_base
    string pokebola;
} Pokemon;

// Definindo a estrutura do nó da árvore binária
struct treenode {
    Pokemon info;
    treenode* esquerda;
    treenode* direita;
};

typedef treenode* treenodeptr;

// Funções

// Inserir Pokémon na árvore binária de busca
void inserir_pokemon(treenodeptr &raiz, Pokemon p) {
    if (raiz == NULL) {
        raiz = new treenode;
        raiz->info = p;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
    } else {
        if (p.nome < raiz->info.nome) {
            inserir_pokemon(raiz->esquerda, p);
        } else {
            inserir_pokemon(raiz->direita, p);
        }
    }
}

// Encontrar o menor nó em uma subárvore
treenodeptr tMenor(treenodeptr &raiz) {
    treenodeptr t;
    t = raiz;
    if (t->esquerda == NULL) {
        raiz = raiz->direita;
        return t;
    } else
        return tMenor(raiz->esquerda);
}

// Remover Pokémon da árvore
int tRemove(treenodeptr &raiz, string nome) {
    treenodeptr p;
    if (raiz == NULL)
        return 1;
    if (nome == raiz->info.nome) {
        p = raiz;
        if (raiz->esquerda == NULL)
            raiz = raiz->direita;
        else if (raiz->direita == NULL)
            raiz = raiz->esquerda;
        else {
            p = tMenor(raiz->direita);
            raiz->info = p->info;
        }
        delete p;
        return 0;
    } else if (nome < raiz->info.nome)
        return tRemove(raiz->esquerda, nome);
    else
        return tRemove(raiz->direita, nome);
}

// Destruir a árvore liberando a memória
void tDestruir(treenodeptr &raiz) {
    if (raiz != NULL) {
        tDestruir(raiz->esquerda);
        tDestruir(raiz->direita);
        delete raiz;
    }
    raiz = NULL;
}

// Procurar um Pokémon na árvore por nome
treenodeptr tPesq(treenodeptr &raiz, string nome) {
    if (raiz == NULL || raiz->info.nome == nome)
        return raiz;

    if (nome < raiz->info.nome)
        return tPesq(raiz->esquerda, nome);

    return tPesq(raiz->direita, nome);
}

// Implementação da função para mostrar em ordem alfabética dos tipos
void mostrarPorTipo(treenodeptr raiz, int tipoDesejado) {
    if (raiz != NULL) {
        mostrarPorTipo(raiz->esquerda, tipoDesejado);
        if (raiz->info.tipo == tipoDesejado) {
            cout << "Nome: " << raiz->info.nome << ", Tipo: " << atributos_base[raiz->info.tipo - 1] << ", Numero: " << raiz->info.numero << ", Pokebola: " << raiz->info.pokebola << endl;
        }
        mostrarPorTipo(raiz->direita, tipoDesejado);
    }
}

int main() {
    setlocale(LC_ALL, "");

    treenodeptr raiz = NULL;

    cout << "Bem vindo ao sistema do Pokédex";

    int op = 4;

    do {
        cout << "\n\t\tMenu\n\t1> Cadastrar novo Pokémon\n\t2> Procurar Pokémon\n\t3> Mostrar em ordem alfabética dos tipos\n\t4> Contar quantos Pokémon por tipo\n\t5> Remover Pokémon\n\n\t6> Sair\n";

        do {
            cout << "Entre com a opção desejada: ";
            cin >> op;
            if (op > 6 || op < 1)
                cout << "Opção inválida!" << endl;
        } while (op > 6 || op < 1);

        if (op == 1) {
            // Cadastrar novo Pokémon
            cout << "\n\tCadastro de Pokémon" << endl;

            Pokemon novoPokemon;
            
            cin.ignore();
            cout << "Informe o nome do Pokémon: ";
            getline(cin, novoPokemon.nome);
            cout << "Informe o tipo (1-Normal; 2-Fogo; 3-Água): ";
            cin >> novoPokemon.tipo;
            cout << "Informe o número de identificação: ";
            cin >> novoPokemon.numero;
            cin.ignore();
            cout << "Informe a pokébola: ";
            getline(cin, novoPokemon.pokebola);

            inserir_pokemon(raiz, novoPokemon);
        } else if (op == 2) {
            // Procurar Pokémon por nome
            cout << "\n\tProcurar Pokémon (por nome)" << endl;

            string nomePokemon;
            cout << "Informe o nome do Pokémon: ";
            cin >> nomePokemon;

            treenodeptr encontrado = tPesq(raiz, nomePokemon);

            if (encontrado == NULL)
                cout << "Pokémon não encontrado!" << endl;
            else
                cout << "Pokémon encontrado!" << endl;
        } else if (op == 3) {
            // Ordenar e imprimir a estrutura por ordem alfabética dos tipos
            cout << "\n\tOrdenar e imprimir a estrutura por ordem alfabética dos tipos" << endl;

            for (int i = 1; i <= 3; ++i) { // 3 tipos de Pokémon
                cout << "\nPokémons do tipo " << atributos_base[i - 1] << ":" << endl;
                mostrarPorTipo(raiz, i);
            }

            // Implementar ordenação e impressão por ordem alfabética dos tipos
        } else if (op == 4) {
            // Contar quantos Pokémon tem de determinado tipo
            cout << "\n\tContar quantos Pokémon tem de determinado tipo" << endl;

            int tipoDesejado;
            cout << "Tipo desejado (1-Normal; 2-Fogo; 3-Água): ";
            cin >> tipoDesejado;

            // Implementar a contagem de Pokémon do tipo desejado
        } else if (op == 5) {
            // Remover Pokémon
            cout << "\n\tRemover Pokémon" << endl;

            string nomeRemover;
            cout << "Informe o nome do Pokémon a ser removido: ";
            cin >> nomeRemover;

            int resultadoRemover = tRemove(raiz, nomeRemover);

            if (resultadoRemover == 0)
                cout << "Pokémon removido com sucesso!" << endl;
            else
                cout << "Pokémon não encontrado para remoção." << endl;
        }

    } while (op != 6);

    cout << "Obrigado por utilizar o sistema do Pokédex!" << endl;

    tDestruir(raiz);

    return 0;
}                                                                                                                              
