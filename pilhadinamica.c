/*
* Utilizando a estrutura de pilhas dinâmica, resolva o problema de decidir se
* uma dada sequência de parênteses e colchetes está bem-formada (ou seja,
* parênteses e colchetes são fechados na ordem inversa àquela em que foram
* abertos). Por exemplo, a sequência ( ( ) [ ( ) ] ) está bem formada, enquanto
* que a sequência ( [ ) ] está malformada.
*/

/*
* =====RESPOSTA=====
* Uma possivel solucao esta na seguinte estrategia:
* 1- A cada ( ou [ lido, empilha este caractere
* 2- A cada ) ou ] lido, desempilha um caractere
*  2.1- Se o caractere desempilhado for o tipo correto de simbolo de fechar, continue analisando
*  2.2- Se for o tipo incorreto encerre a analise, pois a expressao esta mal formada
* 3- Ao final, verifique se a pilha ficou vazia
*  3.1 Se estiver vazia, a analise foi um sucesso: expressao bem formada
*  3.2 Se ainda há elementos na pilha, faltou fechar algum colchete ou parentese, logo expressao mal formada
* FIM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da pilha
typedef struct no_pilha
{
	char dado;
	struct no_pilha *anterior;
} no;

typedef struct pilha
{
	no *topo;
	int tamanho;

} tpilha;

// Cria pilha
tpilha *cria_pilha()
{
	tpilha *p = (tpilha *)malloc(sizeof(tpilha));
	p->topo = NULL;
	p->tamanho = 0;

	return p;
}

// Insere elemento no topo da pilha
void push(tpilha *p, char elemento)
{
	no *aux = (no *)malloc(sizeof(no));

	aux->dado = elemento;
	aux->anterior = p->topo;

	p->tamanho++;
	p->topo = aux;
}

// Testa se a pilha está vazia
int vazia(tpilha *p)
{
	if (p->tamanho == 0)
		return 1;
	else
		return 0;
}

// Remove elemento do topo da pilha
char pop(tpilha *p)
{
	char dado='a'; // Caractere qualquer, a ser retornado caso a pilha esteja vazia
	if (!vazia(p))
	{
		no *aux = p->topo;
		dado = aux->dado;

		p->topo = aux->anterior;
		p->tamanho--;

		free(aux);
	}
	return dado;
}

void libera_pilha(tpilha *p)
{
	while (!vazia(p))
	{
		pop(p);
	}
	free(p);
}

char testar_bem_formada(char *sequencia)
{
	tpilha *p = cria_pilha();
	char aux;

	for (int i = 0; i < strlen(sequencia); i++)
	{
		if (sequencia[i] == '(' || sequencia[i] == '[')
			push(p, sequencia[i]);
		else if (sequencia[i] == ')' || sequencia[i] == ']')
		{
			aux = pop(p);

			if (aux == '(' && sequencia[i] != ')')
			{
				libera_pilha(p);
				return 'n';
			}
			else if (aux == '[' && sequencia[i] != ']')
			{
				libera_pilha(p);
				return 'n';
			}
		}
	}
	if (vazia(p))
	{
		libera_pilha(p);
		return 's';
	}

	libera_pilha(p);
	return 'n';
}

int main()
{
	char sequencia[64];
	char bem_formada;

	printf("Digite uma sequencia de colchetes e parenteses:\n> ");
	scanf(" %s", sequencia);

	bem_formada = testar_bem_formada(sequencia);

	if (bem_formada == 's')
		printf("A sequencia esta bem formada\n\n");
	else
		printf("A sequencia esta mal formada\n\n");

	return 0;
}