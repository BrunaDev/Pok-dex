                                //TEMA 01 - POK�DEX

//Integrantes:  
//Bruna Magalh�es
// Lilyan Oliveira
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
string atributos_base[3] = {"Normal", "Fogo", "�gua"};

// Definindo a estrutura do Pok�mon
typedef struct pokemon
{
	int numero;
	string nome;
	int tipo; // Deve ser uma das op��es em atributos_base
	string pokebola;
} Pokemon;

// Definindo a estrutura do n� da �rvore bin�ria
struct treenode
{
	Pokemon info;
	treenode* esquerda;
	treenode* direita;
};

// Estrutura para armazenar informa��es sobre o caminho mais curto
struct CaminhoMaisCurto
{
    vector<int> caminho;
    int comprimento;
    string tipoPercurso; // Adicionado para armazenar o tipo de percurso
};

typedef treenode* treenodeptr;

// Fun��es
// Fun��o para percurso em ordem
void percursoEmOrdem(treenodeptr raiz)
{
    if (raiz != NULL)
    {
        percursoEmOrdem(raiz->esquerda);
        cout << raiz->info.numero << " ";
        percursoEmOrdem(raiz->direita);
    }
}

// Fun��o para percurso p�s-ordem
void percursoPosOrdem(treenodeptr raiz)
{
    if (raiz != NULL)
    {
        percursoPosOrdem(raiz->esquerda);
        percursoPosOrdem(raiz->direita);
        cout << raiz->info.numero << " ";
    }
}

// Fun��o para percurso pr�-ordem
void percursoPreOrdem(treenodeptr raiz)
{
    if (raiz != NULL)
    {
        cout << raiz->info.numero << " ";
        percursoPreOrdem(raiz->esquerda);
        percursoPreOrdem(raiz->direita);
    }
}

// Fun��o auxiliar para encontrar o caminho mais curto at� um Pok�mon
CaminhoMaisCurto encontrarCaminhoMaisCurtoAux(treenodeptr raiz, int numeroPokemon, string tipoPercursoAtual)
{
    CaminhoMaisCurto caminhoMaisCurtoAtual, caminhoMaisCurtoEsquerda, caminhoMaisCurtoDireita;

    if (raiz == NULL)
    {
        // Se chegarmos a uma folha da �rvore, retornamos um caminho infinito
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
    else if (tipoPercursoAtual == "P�s Ordem")
    {
        caminhoMaisCurtoEsquerda = encontrarCaminhoMaisCurtoAux(raiz->esquerda, numeroPokemon, "P�s Ordem");
        caminhoMaisCurtoDireita = encontrarCaminhoMaisCurtoAux(raiz->direita, numeroPokemon, "P�s Ordem");
    }
    else if (tipoPercursoAtual == "Pr� Ordem")
    {
        caminhoMaisCurtoEsquerda = encontrarCaminhoMaisCurtoAux(raiz->esquerda, numeroPokemon, "Pr� Ordem");
        caminhoMaisCurtoDireita = encontrarCaminhoMaisCurtoAux(raiz->direita, numeroPokemon, "Pr� Ordem");
    }

    // Escolhemos o caminho mais curto entre as sub�rvores esquerda e direita
    if (caminhoMaisCurtoEsquerda.comprimento < caminhoMaisCurtoDireita.comprimento)
        caminhoMaisCurtoAtual = caminhoMaisCurtoEsquerda;
    else
        caminhoMaisCurtoAtual = caminhoMaisCurtoDireita;

    // Verificamos se o caminho atual at� a raiz � mais curto
    caminhoMaisCurtoAtual.caminho.insert(caminhoMaisCurtoAtual.caminho.begin(), raiz->info.numero);

    // Atualizamos o comprimento do caminho atual
    caminhoMaisCurtoAtual.comprimento = caminhoMaisCurtoAtual.caminho.size();
    caminhoMaisCurtoAtual.tipoPercurso = tipoPercursoAtual;

    return caminhoMaisCurtoAtual;
}

// Fun��o para encontrar o caminho mais curto at� um Pok�mon na �rvore
CaminhoMaisCurto encontrarCaminhoMaisCurto(treenodeptr raiz, int numeroPokemon)
{
    // Inicializamos com um caminho infinito
    CaminhoMaisCurto caminhoMaisCurtoFinal;
    caminhoMaisCurtoFinal.caminho.push_back(-1);
    caminhoMaisCurtoFinal.comprimento = INT_MAX;

    // Encontramos o caminho mais curto para cada tipo de percurso
    CaminhoMaisCurto caminhoMaisCurtoEmOrdem = encontrarCaminhoMaisCurtoAux(raiz, numeroPokemon, "Em Ordem");
    CaminhoMaisCurto caminhoMaisCurtoPosOrdem = encontrarCaminhoMaisCurtoAux(raiz, numeroPokemon, "P�s Ordem");
    CaminhoMaisCurto caminhoMaisCurtoPreOrdem = encontrarCaminhoMaisCurtoAux(raiz, numeroPokemon, "Pr� Ordem");

    // Comparamos os caminhos e escolhemos o mais curto
    if (caminhoMaisCurtoEmOrdem.comprimento < caminhoMaisCurtoFinal.comprimento)
        caminhoMaisCurtoFinal = caminhoMaisCurtoEmOrdem;
    if (caminhoMaisCurtoPosOrdem.comprimento < caminhoMaisCurtoFinal.comprimento)
        caminhoMaisCurtoFinal = caminhoMaisCurtoPosOrdem;
    if (caminhoMaisCurtoPreOrdem.comprimento < caminhoMaisCurtoFinal.comprimento)
        caminhoMaisCurtoFinal = caminhoMaisCurtoPreOrdem;

    return caminhoMaisCurtoFinal;
}

// Inserir Pok�mon na �rvore bin�ria de busca
void inserir_pokemon(treenodeptr &raiz, Pokemon p)
{
	if (raiz == NULL)
	{
		// Cria um novo n� se a raiz for nula
		raiz = new treenode;
		raiz->info = p;
		raiz->esquerda = NULL;
		raiz->direita = NULL;
	}
	else
	{
		// Navega para a esquerda se o nome do Pok�mon for menor que o nome na raiz,
		// caso contr�rio, navega para a direita.
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

// Encontrar o menor n� em uma sub�rvore
treenodeptr tMenor(treenodeptr &raiz)
{
	treenodeptr t;
	t = raiz;
	if (t->esquerda == NULL)
	{
		// Encontrou o menor n�, atualiza a raiz e retorna o n� encontrado
		raiz = raiz->direita;
		return t;
	}
	else
		return tMenor(raiz->esquerda);
}

// Remover Pok�mon da �rvore por pokebola
int tRemovePorPokebola(treenodeptr &raiz, string pokebola)
{
	treenodeptr p;
	if (raiz == NULL)
		return 1; // Retorna 1 se a �rvore estiver vazia

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
		return 0; // Retorna 0 indicando que a remo��o foi bem-sucedida
	}
	else if (pokebola < raiz->info.pokebola)
		return tRemovePorPokebola(raiz->esquerda, pokebola);
	else
		return tRemovePorPokebola(raiz->direita, pokebola);
}

// Destruir a �rvore liberando a mem�ria
void tDestruir(treenodeptr &raiz)
{
	if (raiz != NULL)
	{
		// Libera recursivamente a mem�ria dos n�s da �rvore
		tDestruir(raiz->esquerda);
		tDestruir(raiz->direita);
		delete raiz;
	}
	raiz = NULL; // Atualiza a raiz para NULL ap�s destruir a �rvore
}

// Procurar um Pok�mon na �rvore por nome
treenodeptr tPesq(treenodeptr &raiz, string nome)
{
	if (raiz == NULL || raiz->info.nome == nome)
		return raiz;

	if (nome < raiz->info.nome)
		return tPesq(raiz->esquerda, nome);

	return tPesq(raiz->direita, nome);
}

// Procurar um Pok�mon na �rvore por nome
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

// Implementa��o da fun��o para mostrar em ordem alfab�tica dos tipos
void mostrarPorTipo(treenodeptr raiz, int tipoDesejado)
{
	if (raiz != NULL)
	{
		mostrarPorTipo(raiz->esquerda, tipoDesejado);

		// Exibe os Pok�mon apenas se forem do tipo desejado
		if (raiz->info.tipo == tipoDesejado)
		{
			cout << "Nome: " << raiz->info.nome << ", Tipo: " << atributos_base[tipoDesejado - 1] << ", Numero: " << raiz->info.numero << ", Pokebola: " << raiz->info.pokebola << endl;
		}

		mostrarPorTipo(raiz->direita, tipoDesejado);
	}
}


// Implementa��o da fun��o para mostrar por pokebola
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

	cout << "Bem vindo ao sistema do Pok�dex";

	int op = 8;

	do
	{
		cout << "\n\t\tMenu\n\t1> Cadastrar novo Pok�mon\n\t2> Procurar Pok�mon\n\t3> Mostrar em ordem alfab�tica\n\t4> Contar Pok�mons\n\t5> Pok�mons por pokebola\n\t6> Remover Pok�mon\n\t7> Percurso mais r�pido\n\n\t0> Sair\n";

		do
		{
			cout << "Entre com a op��o desejada: ";
			cin >> op;
			if (op < 0 || op > 7)
				cout << "Op��o inv�lida!" << endl;
		}
		while (op < 0 || op > 7);
			
		
		if (op == 1)
        {
            // Cadastrar novo Pok�mon
            cout << "\n\tCadastro de Pok�mon" << endl;

            Pokemon novoPokemon;

            cin.ignore();
            cout << "Informe o nome do Pok�mon: ";
            getline(cin, novoPokemon.nome);

            bool tipoValido = false;
            do {
                cout << "Informe o tipo (1-Normal; 2-Fogo; 3-�gua): ";
                cin >> novoPokemon.tipo;

                if (novoPokemon.tipo >= 1 && novoPokemon.tipo <= 3) {
                    tipoValido = true;
                } else {
                    cout << "Tipo inv�lido! Por favor, insira um tipo v�lido (1 a 3)." << endl;
                }
            } while (!tipoValido);

            cout << "Informe o n�mero de identifica��o: ";
            cin >> novoPokemon.numero;
            cin.ignore();
            cout << "Informe a pok�bola: ";
            getline(cin, novoPokemon.pokebola);

            inserir_pokemon(raiz, novoPokemon);
        }
        else if (op == 2)
        {
            // Procurar Pok�mon por nome
            cout << "\n\tProcurar Pok�mon (por nome)" << endl;

            cin.ignore(); // Limpa o buffer do teclado
            string nomePokemon;
            cout << "Informe o nome do Pok�mon: ";
            getline(cin, nomePokemon);

            // Procura o Pok�mon na �rvore e exibe uma mensagem adequada
            treenodeptr encontrado = tPesq(raiz, nomePokemon);

            if (encontrado == NULL)
                cout << "Pok�mon n�o encontrado!" << endl;
            else
                cout << "Pok�mon encontrado!" << endl;
        }
			
		else if (op == 3)
		{
			// Ordenar e imprimir a estrutura por ordem alfab�tica dos tipos
			cout << "\n\tOrdenar e imprimir a estrutura por ordem alfab�tica dos tipos" << endl;



			for (int i = 3; i >= 1; --i)  
			{
				cout << "\nPok�mons do tipo " << atributos_base[i - 1] << ":" << endl;
				mostrarPorTipo(raiz, i);
			}
		}
		else if (op == 4)
		{
			// Contar quantos Pok�mon tem de determinado tipo
			cout << "\n\tContar quantos Pok�mon tem de determinado tipo" << endl;

			int tipoDesejado;
			cout << "Tipo desejado (1-Normal; 2-Fogo; 3-�gua): ";
			cin >> tipoDesejado;

			int encontrado = Contabiliza_Tipo(raiz, tipoDesejado);

			if (encontrado == 0)
				cout << "N�o existe esse tipo de pok�mon cadastrado!" << endl;
			else
			{
				if(encontrado > 1)
					cout << "Tem " << encontrado << " pok�mons" << endl;
				else
				{
					cout << "Tem " << encontrado << " pok�mon" << endl;
				}
			}

		}
		else if (op == 5)
		{
			//Separar por pokebola
			cout << "\n\tPok�mons por pokebola" << endl;

			string pokebolaDesejada;
			cout << "Informe a pokebola desejada: ";
			cin >> pokebolaDesejada;

			cout << "\nPok�mons na pokebola " << pokebolaDesejada << ":" << endl;
			mostrarPorPokebola(raiz, pokebolaDesejada);
		}
		else if (op == 6)
		{
			// Remover Pok�mon por pokebola
			cout << "\n\tRemover Pok�mon por pokebola" << endl;

			string pokebolaRemover;
			cout << "Informe a pokebola do pok�mon a ser removido: ";
			cin >> pokebolaRemover;

			// Tenta remover o Pok�mon e exibe uma mensagem adequada
			int resultadoRemover = tRemovePorPokebola(raiz, pokebolaRemover);

			if (resultadoRemover == 0)
				cout << "Pok�mon removido com sucesso!" << endl;
			else
				cout << "Pok�mon n�o encontrado para remo��o." << endl;
		}
		else if (op == 7)
		{
    		// Encontrar caminho mais curto at� um Pok�mon
    cout << "\n\tEncontrar Caminho Mais Curto at� um Pok�mon\n";

    int numeroPokemon;
    cout << "Informe o n�mero do Pok�mon desejado: ";
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
        cout << "Pok�mon n�o encontrado na �rvore." << endl;
    }
		}
	}while (op != 0);

	cout << "Obrigado por utilizar o sistema do Pok�dex!" << endl;

	// Libera a mem�ria da �rvore antes de encerrar o programa
	tDestruir(raiz);

	return 0;
}
