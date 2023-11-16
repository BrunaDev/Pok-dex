#include<iostream>
#include <locale.h>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

// Definindo os tipos de atributos
string atributos_base[3] = {"Normal", "Fogo", "�gua"};

// Definindo a estrutura do Pok�mon
typedef struct pokemon {
    int numero;
    string nome;
    int tipo; // Deve ser uma das op��es em atributos_base
    string pokebola;
} Pokemon;

// Definindo a estrutura do n� da �rvore bin�ria
struct treenode {
    Pokemon info;
    treenode* esquerda;
    treenode* direita;
};

typedef treenode* treenodeptr;

// Fun��es

// Inserir Pok�mon na �rvore bin�ria de busca
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

// Encontrar o menor n� em uma sub�rvore
treenodeptr tMenor(treenodeptr &raiz) {
    treenodeptr t;
    t = raiz;
    if (t->esquerda == NULL) {
        raiz = raiz->direita;
        return t;
    } else
        return tMenor(raiz->esquerda);
}

// Remover Pok�mon da �rvore
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

// Destruir a �rvore liberando a mem�ria
void tDestruir(treenodeptr &raiz) {
    if (raiz != NULL) {
        tDestruir(raiz->esquerda);
        tDestruir(raiz->direita);
        delete raiz;
    }
    raiz = NULL;
}

// Procurar um Pok�mon na �rvore por nome
treenodeptr tPesq(treenodeptr &raiz, string nome) {
    if (raiz == NULL || raiz->info.nome == nome)
        return raiz;

    if (nome < raiz->info.nome)
        return tPesq(raiz->esquerda, nome);

    return tPesq(raiz->direita, nome);
}

int main() {
    setlocale(LC_ALL, "");

    treenodeptr raiz = NULL;

    cout << "Bem vindo ao sistema do Pok�dex";

    int op = 4;

    do {
        cout << "\n\t\tMenu\n\t1> Cadastrar novo Pok�mon\n\t2> Procurar Pok�mon\n\t3> Mostrar em ordem alfab�tica dos tipos\n\t4> Contar quantos Pok�mon do tipo\n\t5> Remover Pok�mon\n\n\t6> Sair\n";

        do {
            cout << "Entre com a op��o desejada: ";
            cin >> op;
            if (op > 6 || op < 1)
                cout << "Op��o inv�lida!" << endl;
        } while (op > 6 || op < 1);

        if (op == 1) {
            // Cadastrar novo Pok�mon
            cout << "\n\tCadastro de Pok�mon" << endl;

            Pokemon novoPokemon;
            cout << "Informe o nome do Pok�mon: ";
            cin >> novoPokemon.nome;
            cout << "Informe o tipo (1-Normal; 2-Fogo; 3-�gua): ";
            cin >> novoPokemon.tipo;
            cout << "Informe o n�mero de identifica��o: ";
            cin >> novoPokemon.numero;
            cout << "Informe a pok�bola: ";
            cin >> novoPokemon.pokebola;

            inserir_pokemon(raiz, novoPokemon);
        } else if (op == 2) {
            // Procurar Pok�mon por nome
            cout << "\n\tProcurar Pok�mon (por nome)" << endl;

            string nomePokemon;
            cout << "Informe o nome do Pok�mon: ";
            cin >> nomePokemon;

            treenodeptr encontrado = tPesq(raiz, nomePokemon);

            if (encontrado == NULL)
                cout << "Pok�mon n�o encontrado!" << endl;
            else
                cout << "Pok�mon encontrado!" << endl;
        } else if (op == 3) {
            // Ordenar e imprimir a estrutura por ordem alfab�tica dos tipos
            cout << "\n\tOrdenar e imprimir a estrutura por ordem alfab�tica dos tipos" << endl;

            // Implementar ordena��o e impress�o por ordem alfab�tica dos tipos
        } else if (op == 4) {
            // Contar quantos Pok�mon tem de determinado tipo
            cout << "\n\tContar quantos Pok�mon tem de determinado tipo" << endl;

            int tipoDesejado;
            cout << "Tipo desejado (1-Normal; 2-Fogo; 3-�gua): ";
            cin >> tipoDesejado;

            // Implementar a contagem de Pok�mon do tipo desejado
        } else if (op == 5) {
            // Remover Pok�mon
            cout << "\n\tRemover Pok�mon" << endl;

            string nomeRemover;
            cout << "Informe o nome do Pok�mon a ser removido: ";
            cin >> nomeRemover;

            int resultadoRemover = tRemove(raiz, nomeRemover);

            if (resultadoRemover == 0)
                cout << "Pok�mon removido com sucesso!" << endl;
            else
                cout << "Pok�mon n�o encontrado para remo��o." << endl;
        }

    } while (op != 6);

    cout << "Obrigado por utilizar o sistema do Pok�dex!" << endl;

    tDestruir(raiz);

    return 0;
}