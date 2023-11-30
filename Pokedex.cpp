//Integrantes:                           TEMA 01 - POKÉDEX
//Bruna Magalhães
// Lilyan Aparecida
// Kawan dos Reis

#include<iostream>
#include <locale.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <climits>

using namespace std;

// Definindo os tipos de atributos
string atributos_base[3] = {"Normal", "Fogo", "Água"};

// Definindo a estrutura do Pokémon
typedef struct pokemon
{
	int numero;
	string nome;
	int tipo; // Deve ser uma das opções em atributos_base
	string pokebola;
} Pokemon;

// Definindo a estrutura do nó da árvore binária
struct treenode
{
	Pokemon info;
	treenode* esquerda;
	treenode* direita;
};

// Estrutura para armazenar informações sobre o caminho mais curto
struct CaminhoMaisCurto
{
    vector<int> caminho;
    int comprimento;
    string tipoPercurso; // Adicionado para armazenar o tipo de percurso
};

typedef treenode* treenodeptr;

// Funções
// Função para percurso em ordem
void percursoEmOrdem(treenodeptr raiz)
{
    if (raiz != NULL)
    {
        percursoEmOrdem(raiz->esquerda);
        cout << raiz->info.numero << " ";
        percursoEmOrdem(raiz->direita);
    }
}

// Função para percurso pós-ordem
void percursoPosOrdem(treenodeptr raiz)
{
    if (raiz != NULL)
    {
        percursoPosOrdem(raiz->esquerda);
        percursoPosOrdem(raiz->direita);
        cout << raiz->info.numero << " ";
    }
}

// Função para percurso pré-ordem
void percursoPreOrdem(treenodeptr raiz)
{
    if (raiz != NULL)
    {
        cout << raiz->info.numero << " ";
        percursoPreOrdem(raiz->esquerda);
        percursoPreOrdem(raiz->direita);
    }
}

// Função auxiliar para encontrar o caminho mais curto até um Pokémon
CaminhoMaisCurto encontrarCaminhoMaisCurtoAux(treenodeptr raiz, int numeroPokemon, string tipoPercursoAtual)
{
    CaminhoMaisCurto caminhoMaisCurtoAtual, caminhoMaisCurtoEsquerda, caminhoMaisCurtoDireita;

    if (raiz == NULL)
    {
        // Se chegarmos a uma folha da árvore, retornamos um caminho infinito
        caminhoMaisCurtoAtual.caminho.push_back(-1);
        caminhoMaisCurtoAtual.comprimento = INT_MAX;
        caminhoMaisCurtoAtual.tipoPercurso = tipoPercursoAtual;
        return caminhoMaisCurtoAtual;
    }

    if (tipoPercursoAtual == "Em Ordem")
    {
        caminhoMaisCurtoEsquerda = encontrarCaminhoMaisCurtoAux(raiz->esquerda, numeroPokemon, "Em Ordem");
        caminhoMaisCurtoDireita = encontrarCaminhoMaisCurtoAux(raiz->direita, numeroPokemon, "Em Ordem");
    }
    else if (tipoPercursoAtual == "Pós Ordem")
    {
        caminhoMaisCurtoEsquerda = encontrarCaminhoMaisCurtoAux(raiz->esquerda, numeroPokemon, "Pós Ordem");
        caminhoMaisCurtoDireita = encontrarCaminhoMaisCurtoAux(raiz->direita, numeroPokemon, "Pós Ordem");
    }
    else if (tipoPercursoAtual == "Pré Ordem")
    {
        caminhoMaisCurtoEsquerda = encontrarCaminhoMaisCurtoAux(raiz->esquerda, numeroPokemon, "Pré Ordem");
        caminhoMaisCurtoDireita = encontrarCaminhoMaisCurtoAux(raiz->direita, numeroPokemon, "Pré Ordem");
    }

    // Escolhemos o caminho mais curto entre as subárvores esquerda e direita
    if (caminhoMaisCurtoEsquerda.comprimento < caminhoMaisCurtoDireita.comprimento)
        caminhoMaisCurtoAtual = caminhoMaisCurtoEsquerda;
    else
        caminhoMaisCurtoAtual = caminhoMaisCurtoDireita;

    // Verificamos se o caminho atual até a raiz é mais curto
    caminhoMaisCurtoAtual.caminho.insert(caminhoMaisCurtoAtual.caminho.begin(), raiz->info.numero);

    // Atualizamos o comprimento do caminho atual
    caminhoMaisCurtoAtual.comprimento = caminhoMaisCurtoAtual.caminho.size();
    caminhoMaisCurtoAtual.tipoPercurso = tipoPercursoAtual;

    return caminhoMaisCurtoAtual;
}

// Função para encontrar o caminho mais curto até um Pokémon na árvore
CaminhoMaisCurto encontrarCaminhoMaisCurto(treenodeptr raiz, int numeroPokemon)
{
    // Inicializamos com um caminho infinito
    CaminhoMaisCurto caminhoMaisCurtoFinal;
    caminhoMaisCurtoFinal.caminho.push_back(-1);
    caminhoMaisCurtoFinal.comprimento = INT_MAX;

    // Encontramos o caminho mais curto para cada tipo de percurso
    CaminhoMaisCurto caminhoMaisCurtoEmOrdem = encontrarCaminhoMaisCurtoAux(raiz, numeroPokemon, "Em Ordem");
    CaminhoMaisCurto caminhoMaisCurtoPosOrdem = encontrarCaminhoMaisCurtoAux(raiz, numeroPokemon, "Pós Ordem");
    CaminhoMaisCurto caminhoMaisCurtoPreOrdem = encontrarCaminhoMaisCurtoAux(raiz, numeroPokemon, "Pré Ordem");

    // Comparamos os caminhos e escolhemos o mais curto
    if (caminhoMaisCurtoEmOrdem.comprimento < caminhoMaisCurtoFinal.comprimento)
        caminhoMaisCurtoFinal = caminhoMaisCurtoEmOrdem;
    if (caminhoMaisCurtoPosOrdem.comprimento < caminhoMaisCurtoFinal.comprimento)
        caminhoMaisCurtoFinal = caminhoMaisCurtoPosOrdem;
    if (caminhoMaisCurtoPreOrdem.comprimento < caminhoMaisCurtoFinal.comprimento)
        caminhoMaisCurtoFinal = caminhoMaisCurtoPreOrdem;

    return caminhoMaisCurtoFinal;
}

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

// Remover Pokémon da árvore por pokebola
int tRemovePorPokebola(treenodeptr &raiz, string pokebola)
{
	treenodeptr p;
	if (raiz == NULL)
		return 1; // Retorna 1 se a árvore estiver vazia

	if (pokebola == raiz->info.pokebola)
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
	else if (pokebola < raiz->info.pokebola)
		return tRemovePorPokebola(raiz->esquerda, pokebola);
	else
		return tRemovePorPokebola(raiz->direita, pokebola);
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

	return cont;
}

// Implementação da função para mostrar em ordem alfabética dos tipos
void mostrarPorTipo(treenodeptr raiz, int tipoDesejado)
{
	if (raiz != NULL)
	{
		mostrarPorTipo(raiz->esquerda, tipoDesejado);

		// Exibe os Pokémon apenas se forem do tipo desejado
		if (raiz->info.tipo == tipoDesejado)
		{
			cout << "Nome: " << raiz->info.nome << ", Tipo: " << atributos_base[tipoDesejado - 1] << ", Numero: " << raiz->info.numero << ", Pokebola: " << raiz->info.pokebola << endl;
		}

		mostrarPorTipo(raiz->direita, tipoDesejado);
	}
}


// Implementação da função para mostrar por pokebola
void mostrarPorPokebola(treenodeptr raiz, string pokebolaDesejada)
{
	if (raiz != NULL)
	{
		mostrarPorPokebola(raiz->esquerda, pokebolaDesejada);
		if (raiz->info.pokebola == pokebolaDesejada)
		{
			cout << "Nome: " << raiz->info.nome << ", Tipo: " << atributos_base[raiz->info.tipo - 1] << ", Numero: " << raiz->info.numero << ", Pokebola: " << raiz->info.pokebola << endl;
		}
		mostrarPorPokebola(raiz->direita, pokebolaDesejada);
	}
}

int main()
{
	setlocale(LC_ALL, "");

	treenodeptr raiz = NULL;

	cout << "Bem vindo ao sistema do Pokédex";

	int op = 8;

	do
	{
		cout << "\n\t\tMenu\n\t1> Cadastrar novo Pokémon\n\t2> Procurar Pokémon\n\t3> Mostrar em ordem alfabética\n\t4> Contar Pokémons\n\t5> Pokémons por pokebola\n\t6> Remover Pokémon\n\t7> Percurso mais rápido\n\n\t0> Sair\n";

		do
		{
			cout << "Entre com a opção desejada: ";
			cin >> op;
			if (op < 0 || op > 7)
				cout << "Opção inválida!" << endl;
		}
		while (op < 0 || op > 7);

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



			for (int i = 3; i >= 1; --i)  
			{
				cout << "\nPokémons do tipo " << atributos_base[i - 1] << ":" << endl;
				mostrarPorTipo(raiz, i);
			}
		}
		else if (op == 4)
		{
			// Contar quantos Pokémon tem de determinado tipo
			cout << "\n\tContar quantos Pokémon tem de determinado tipo" << endl;

			int tipoDesejado;
			cout << "Tipo desejado (1-Normal; 2-Fogo; 3-Água): ";
			cin >> tipoDesejado;

			int encontrado = Contabiliza_Tipo(raiz, tipoDesejado);

			if (encontrado == 0)
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
			//Separar por pokebola
			cout << "\n\tPokémons por pokebola" << endl;

			string pokebolaDesejada;
			cout << "Informe a pokebola desejada: ";
			cin >> pokebolaDesejada;

			cout << "\nPokémons na pokebola " << pokebolaDesejada << ":" << endl;
			mostrarPorPokebola(raiz, pokebolaDesejada);
		}
		else if (op == 6)
		{
			// Remover Pokémon por pokebola
			cout << "\n\tRemover Pokémon por pokebola" << endl;

			string pokebolaRemover;
			cout << "Informe a pokebola do pokémon a ser removido: ";
			cin >> pokebolaRemover;

			// Tenta remover o Pokémon e exibe uma mensagem adequada
			int resultadoRemover = tRemovePorPokebola(raiz, pokebolaRemover);

			if (resultadoRemover == 0)
				cout << "Pokémon removido com sucesso!" << endl;
			else
				cout << "Pokémon não encontrado para remoção." << endl;
		}
		else if (op == 7)
		{
    		// Encontrar caminho mais curto até um Pokémon
    cout << "\n\tEncontrar Caminho Mais Curto até um Pokémon\n";

    int numeroPokemon;
    cout << "Informe o número do Pokémon desejado: ";
    cin >> numeroPokemon;

    CaminhoMaisCurto caminhoMaisCurto = encontrarCaminhoMaisCurto(raiz, numeroPokemon);

    if (caminhoMaisCurto.comprimento != INT_MAX)
    {
        cout << "Caminho Mais Curto Encontrado (" << caminhoMaisCurto.tipoPercurso << "): ";
        for (int i = 0; i < caminhoMaisCurto.caminho.size(); ++i)
        {
            cout << caminhoMaisCurto.caminho[i];
            if (i < caminhoMaisCurto.caminho.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "Pokémon não encontrado na árvore." << endl;
    }
		}
	}while (op != 0);

	cout << "Obrigado por utilizar o sistema do Pokédex!" << endl;

	// Libera a memória da árvore antes de encerrar o programa
	tDestruir(raiz);

	return 0;
}
