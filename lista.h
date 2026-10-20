#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Equipamento {
	int codigo_solicitacao;
	char codigo_equipamento[7];
	char nome_equipamento[21];
	int prioridade;
	int periodo;
} Equipamento;

typedef struct NoEquipamento {
	Equipamento e;
	struct NoEquipamento *prox;
} NoEquipamento;

typedef struct Lista {
	NoEquipamento *inicio;
} Lista;

Lista criar_lista();
NoEquipamento *criar_no(Equipamento e);

int codigo_existe(Lista *l, int codigo);
Equipamento *encontrar_equipamento(Lista *l, int codigo);

void liberar_lista(Lista *l);
void inserir_solicitacao(Lista *l);
void remover_solicitacao(Lista *l);
void consultar_solicitacao(Lista *l);
void alterar_prioridade(Lista *l);
void exibir_tudo(Lista *l);
void exibir_ordem(Lista *l);

Equipamento ler_equipamento() {
	Equipamento e;

	printf("Código da solicitação: ");
	scanf("%d", &e.codigo_solicitacao);
	getc(stdin);

	printf("Código do equipamento: ");
	scanf("%6s", e.codigo_equipamento);
	getc(stdin);

	printf("Nome do equipamento: ");
	scanf("%20s", e.nome_equipamento);
	getc(stdin);

	do {
		printf("Prioridade (1 - Alta, 2 - Média, 3 - Baixa): ");
		scanf("%d", &e.prioridade);
		getc(stdin);
	} while (e.prioridade < 1 || e.prioridade > 3);

	int limite_maximo;

	if (e.prioridade == 1) {
		limite_maximo = 7;
	} else if (e.prioridade == 2) {
		limite_maximo = 15;
	} else {
		limite_maximo = 20;
	}

	do {
		printf("Período (1 a %d dias): ", limite_maximo);
		scanf("%d", &e.periodo);
		getc(stdin);
		if (e.periodo < 1 || e.periodo > limite_maximo) {
			printf("[ERRO] Para a prioridade %d, o período deve ser entre 1 e "
				   "%d dias!\n",
				   e.prioridade, limite_maximo);
		}
	} while (e.periodo < 1 || e.periodo > limite_maximo);

	return e;
}

Lista criar_lista() {
	Lista l;
	l.inicio = NULL;
	return l;
}

NoEquipamento *criar_no(Equipamento e) {
	NoEquipamento *ne = (NoEquipamento *)malloc(sizeof(NoEquipamento));
	ne->e = e;
	ne->prox = NULL;
	return ne;
}

int codigo_existe(Lista *l, int codigo) {
	NoEquipamento *aux = l->inicio;
	while (aux && aux->e.codigo_solicitacao != codigo)
		aux = aux->prox;
	return aux != NULL;
}

void liberar_lista(Lista *l) {
	NoEquipamento *aux = l->inicio;

	while (aux) {
		NoEquipamento *prox = aux->prox;
		free(aux);
		aux = prox;
	}

	l->inicio = NULL;
}

void inserir_solicitacao(Lista *l) {
	NoEquipamento *no = criar_no(ler_equipamento());

	if (!codigo_existe(l, no->e.codigo_solicitacao)) {
		if (l->inicio == NULL ||
			no->e.codigo_solicitacao < l->inicio->e.codigo_solicitacao) {
			no->prox = l->inicio;
			l->inicio = no;
		} else {
			NoEquipamento *aux = l->inicio;

			while (aux->prox &&
				   aux->prox->e.codigo_solicitacao < no->e.codigo_solicitacao) {
				aux = aux->prox;
			}
			if (aux->prox == NULL) {
				aux->prox = no;
			} else {
				no->prox = aux->prox;
				aux->prox = no;
			}
		}
	} else {
		printf("Código de solicitação já existe.\n");
		free(no);
	}
}

void remover_solicitacao(Lista *l) {
	int codigo;

	printf("Código de solicitação do equipamento a remover: ");
	scanf("%d", &codigo);

	NoEquipamento *aux = l->inicio;
	NoEquipamento *anterior = NULL;

	while (aux && aux->e.codigo_solicitacao != codigo) {
		anterior = aux;
		aux = aux->prox;
	}

	if (aux == NULL) {
		printf("Solicitação não encontrada.\n");
	} else {
		if (anterior == NULL) {
			l->inicio = aux->prox;
		} else {
			anterior->prox = aux->prox;
		}

		free(aux);
	}
}

void imprimir_equipamento(Equipamento e) {
	printf("Código da solicitação: %d\n", e.codigo_solicitacao);

	printf("Código do equipamento: %s\n", e.codigo_equipamento);

	printf("Nome do equipamento: %s\n", e.nome_equipamento);

	printf("Prioridade: %d\n", e.prioridade);

	printf("Período: %d\n", e.periodo);
}

Equipamento *encontrar_equipamento(Lista *l, int codigo) {
	NoEquipamento *aux = l->inicio;
	Equipamento *resultado = NULL;

	while (aux != NULL && aux->e.codigo_solicitacao != codigo) {
		aux = aux->prox;
	}

	if (aux != NULL) {
		resultado = &aux->e;
	}

	return resultado;
}

void alterar_prioridade(Lista *l) {
	int codigo;
	printf("\nCódigo de solicitação: ");
	scanf("%d", &codigo);

	if (!codigo_existe(l, codigo)) {
		printf("Solicitação não encontrada.\n");
	} else {
		Equipamento *e = encontrar_equipamento(l, codigo);

		do {
			printf("\nNova Prioridade (1 - Alta, 2 - Média, 3 - Baixa): ");
			scanf("%d", &e->prioridade);
		} while (e->prioridade < 1 || e->prioridade > 3);

		int limite_maximo;
		if (e->prioridade == 1) {
			limite_maximo = 7;
		} else if (e->prioridade == 2) {
			limite_maximo = 15;
		} else {
			limite_maximo = 20;
		}

		do {
			printf("\nNovo Período (1 a %d dias): ", limite_maximo);
			scanf("%d", &e->periodo);
			if (e->periodo < 1 || e->periodo > limite_maximo) {
				printf("[ERRO] Para a prioridade %d, o período deve ser entre "
					   "1 e %d dias!\n",
					   e->prioridade, limite_maximo);
			}
		} while (e->periodo < 1 || e->periodo > limite_maximo);
		printf("\nPrioridade e período alterados com sucesso!\n");
	}
}

void consultar_solicitacao(Lista *l) {
	int codigo;
	printf("Código de solicitação: ");
	scanf("%d", &codigo);

	NoEquipamento *aux = l->inicio;

	while (aux && aux->e.codigo_solicitacao != codigo) {
		aux = aux->prox;
	}

	if (aux == NULL) {
		printf("Solicitação não encontrada.\n");
	} else {
		imprimir_equipamento(aux->e);
	}
}

void exibir_tudo(Lista *l) {
	NoEquipamento *aux = l->inicio;
	while (aux) {
		imprimir_equipamento(aux->e);
		aux = aux->prox;
	}
}

void exibir_ordem(Lista *l) {
	Lista lista_auxiliar;
	NoEquipamento *atual_principal;
	NoEquipamento *atual_auxiliar;
	NoEquipamento *anterior;
	NoEquipamento *novo;
	NoEquipamento *proximo;
	int inserido;

	lista_auxiliar = criar_lista();
	atual_principal = l->inicio;

	while (atual_principal) {
		novo = (NoEquipamento *)malloc(sizeof(NoEquipamento));
		novo->e = atual_principal->e;
		novo->prox = NULL;
		inserido = 0;

		if (lista_auxiliar.inicio == NULL) {
			lista_auxiliar.inicio = novo;
			inserido = 1;
		} else {
			atual_auxiliar = lista_auxiliar.inicio;
			anterior = NULL;

			while (atual_auxiliar && !inserido) {
				if (novo->e.prioridade < atual_auxiliar->e.prioridade ||
					(novo->e.prioridade == atual_auxiliar->e.prioridade &&
					 novo->e.periodo < atual_auxiliar->e.periodo) ||
					(novo->e.prioridade == atual_auxiliar->e.prioridade &&
					 novo->e.periodo == atual_auxiliar->e.periodo &&
					 novo->e.codigo_solicitacao <
						 atual_auxiliar->e.codigo_solicitacao)) {
					if (anterior == NULL) {
						novo->prox = lista_auxiliar.inicio;
						lista_auxiliar.inicio = novo;
					} else {
						novo->prox = atual_auxiliar;
						anterior->prox = novo;
					}

					inserido = 1;
				} else {
					anterior = atual_auxiliar;
					atual_auxiliar = atual_auxiliar->prox;
				}
			}

			if (!inserido) {
				anterior->prox = novo;
			}
		}

		atual_principal = atual_principal->prox;
	}

	atual_auxiliar = lista_auxiliar.inicio;

	while (atual_auxiliar) {
		imprimir_equipamento(atual_auxiliar->e);
		atual_auxiliar = atual_auxiliar->prox;
	}

	atual_auxiliar = lista_auxiliar.inicio;

	while (atual_auxiliar) {
		proximo = atual_auxiliar->prox;
		free(atual_auxiliar);
		atual_auxiliar = proximo;
	}
}

#endif
