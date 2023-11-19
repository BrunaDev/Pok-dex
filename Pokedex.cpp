#include<iostream>
#include <locale.h>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

// Definindo os tipos de atributos
string atributos_base[3] = {"Normal", "Fogo", "Água"};

// Definindo a estrutura do Pokémon
typedef struct pokemon{
	int numero;
	string nome;
	int tipo; // Deve ser uma das opções em atributos_base
	string pokebola;
} Pokemon;

// Definindo a estrutura do nó da árvore binária
struct treenode{
	Pokemon info;
	treenode* esquerda;
	treenode* direita;
};

typedef treenode* treenodeptr;

// Funções

// Inserir Pokémon na árvore binária de busca
void inserir_pokemon(treenodeptr &raiz, Pokemon p)
{
	if (raiz == NULL)
	{
		// Cria um novo nó se a raiz for nula
		raiz = new treenode;
		raiz->info = p;
		raiz->esquerda = NULL;
		raiz->direita = NULL;
	}
	else
	{
		// Navega para a esquerda se o nome do Pokémon for menor que o nome na raiz,
		// caso contrário, navega para a direita.
		if (p.nome < raiz->info.nome)
		{
			inserir_pokemon(raiz->esquerda, p);
		}
		else
		{
			inserir_pokemon(raiz->direita, p);
		}
	}
}

// Encontrar o menor nó em uma subárvore
treenodeptr tMenor(treenodeptr &raiz)
{
	treenodeptr t;
	t = raiz;
	if (t->esquerda == NULL)
	{
		// Encontrou o menor nó, atualiza a raiz e retorna o nó encontrado
		raiz = raiz->direita;
		return t;
	}
	else
		return tMenor(raiz->esquerda);
}

// Remover Pokémon da árvore
int tRemove(treenodeptr &raiz, string nome)
{
	treenodeptr p;
	if (raiz == NULL)
		return 1; // Retorna 1 se a árvore estiver vazia

	if (nome == raiz->info.nome)
	{
		p = raiz;
		if (raiz->esquerda == NULL)
			raiz = raiz->direita;
		else if (raiz->direita == NULL)
			raiz = raiz->esquerda;
		else
		{
			p = tMenor(raiz->direita);
			raiz->info = p->info;
		}
		delete p;
		return 0; // Retorna 0 indicando que a remoção foi bem-sucedida
	}
	else if (nome < raiz->info.nome)
		return tRemove(raiz->esquerda, nome);
	else
		return tRemove(raiz->direita, nome);
}

// Destruir a árvore liberando a memória
void tDestruir(treenodeptr &raiz)
{
	if (raiz != NULL)
	{
		// Libera recursivamente a memória dos nós da árvore
		tDestruir(raiz->esquerda);
		tDestruir(raiz->direita);
		delete raiz;
	}
	raiz = NULL; // Atualiza a raiz para NULL após destruir a árvore
}

// Procurar um Pokémon na árvore por nome
treenodeptr tPesq(treenodeptr &raiz, string nome)
{
	if (raiz == NULL || raiz->info.nome == nome)
		return raiz;

	if (nome < raiz->info.nome)
		return tPesq(raiz->esquerda, nome);

	return tPesq(raiz->direita, nome);
}

// Procurar um Pokémon na árvore por nome
int Contabiliza_Tipo(treenodeptr raiz, int tipoDesejado)
{
    int cont = 0;

    if (raiz != NULL)
    {
       
        if (tipoDesejado < raiz->info.tipo)
        {
            cont += Contabiliza_Tipo(raiz->esquerda, tipoDesejado);
        }
        else if (tipoDesejado > raiz->info.tipo)
        {
            cont += Contabiliza_Tipo(raiz->direita, tipoDesejado);
        }
        else
        {
            cont++;
            cont += Contabiliza_Tipo(raiz->esquerda, tipoDesejado);
            cont += Contabiliza_Tipo(raiz->direita, tipoDesejado);
        }
    }
    if(raiz == NULL && cont == 0)
	{
		return -1;
	}

    return cont;
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

int main()
{
	setlocale(LC_ALL, "");

	treenodeptr raiz = NULL;

	cout << "Bem vindo ao sistema do Pokédex";

	int op = 4;

	do
	{
		cout << "\n\t\tMenu\n\t1> Cadastrar novo Pokémon\n\t2> Procurar Pokémon\n\t3> Mostrar em ordem alfabética dos tipos\n\t4> Contar quantos Pokémon por tipo\n\t5> Remover Pokémon\n\n\t6> Sair\n";

		do
		{
			cout << "Entre com a opção desejada: ";
			cin >> op;
			if (op > 6 || op < 1)
				cout << "Opção inválida!" << endl;
		}
		while (op > 6 || op < 1);

		if (op == 1)
		{
			// Cadastrar novo Pokémon
			cout << "\n\tCadastro de Pokémon" << endl;

			Pokemon novoPokemon;

			// Solicita informações do novo Pokémon ao usuário
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

			// Insere o novo Pokémon na árvore
			inserir_pokemon(raiz, novoPokemon);
		}
		else if (op == 2)
		{
			// Procurar Pokémon por nome
			cout << "\n\tProcurar Pokémon (por nome)" << endl;

			string nomePokemon;
			cout << "Informe o nome do Pokémon: ";
			cin >> nomePokemon;

			// Procura o Pokémon na árvore e exibe uma mensagem adequada
			treenodeptr encontrado = tPesq(raiz, nomePokemon);

			if (encontrado == NULL)
				cout << "Pokémon não encontrado!" << endl;
			else
				cout << "Pokémon encontrado!" << endl;
		}
		else if (op == 3)
		{
			// Ordenar e imprimir a estrutura por ordem alfabética dos tipos
			cout << "\n\tOrdenar e imprimir a estrutura por ordem alfabética dos tipos" << endl;

			for (int i = 1; i <= 3; ++i)   // 3 tipos de Pokémon
			{
				cout << "\nPokémons do tipo " << atributos_base[i - 1] << ":" << endl;
				mostrarPorTipo(raiz, i);
			}

			// Implementar ordenação e impressão por ordem alfabética dos tipos
		}
		else if (op == 4)
		{
			// Contar quantos Pokémon tem de determinado tipo
			cout << "\n\tContar quantos Pokémon tem de determinado tipo" << endl;

			int tipoDesejado;
			cout << "Tipo desejado (1-Normal; 2-Fogo; 3-Água): ";
			cin >> tipoDesejado;

			int encontrado = Contabiliza_Tipo(raiz, tipoDesejado);

			if (encontrado == -1)
				cout << "Não existe esse tipo de pokémon cadastrado!" << endl;
			else
			{
				if(encontrado > 1)
					cout << "Tem " << encontrado << " pokémons" << endl;
				else
				{
					cout << "Tem " << encontrado << " pokémon" << endl;
				}
			}

		}
		else if (op == 5)
		{
			// Remover Pokémon
			cout << "\n\tRemover Pokémon" << endl;

			string nomeRemover;
			cout << "Informe o nome do pokémon a ser removido: ";
			cin >> nomeRemover;

			// Tenta remover o Pokémon e exibe uma mensagem adequada
			int resultadoRemover = tRemove(raiz, nomeRemover);

			if (resultadoRemover == 0)
				cout << "Pokémon removido com sucesso!" << endl;
			else
				cout << "Pokémon não encontrado para remoção." << endl;
		}

	}
	while (op != 6);

	cout << "Obrigado por utilizar o sistema do Pokédex!" << endl;

	// Libera a memória da árvore antes de encerrar o programa
	tDestruir(raiz);

	return 0;
}
