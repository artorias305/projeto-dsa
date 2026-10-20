#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

void print_menu() {
	printf(
		"======================================================================"
		"\nEscolha uma opção:\n\t1 - Inserir uma solicitação de "
		"manutenção\n\t2 - Remover uma solicitação\n\t3 - Consultar uma "
		"solicitação\n\t4 - Alterar a prioridade e/ou período de uma "
		"solicitação\n\t5 - Exibir a ordem da realização da manutenção\n\t6 "
		"- Exibir todas as solicitações\n\t0 - Finalizar"
		"\n===================================================================="
		"=="
		"\nEscolha: ");
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	int escolha = -1;

	Lista lista = criar_lista();

	do {
		print_menu();
		scanf("%d", &escolha);

		switch (escolha) {
		case 1:
			inserir_solicitacao(&lista);
			break;
		case 2:
			remover_solicitacao(&lista);
			break;
		case 3:
			consultar_solicitacao(&lista);
			break;
		case 4:
			alterar_prioridade(&lista);
			break;
		case 5:
			exibir_ordem(&lista);
			break;
		case 6:
			exibir_tudo(&lista);
			break;
		default:
			if (escolha != 0) {
				printf("Escolha inválida.\n");
			}
			break;
		}
	} while (escolha != 0);

	liberar_lista(&lista);

	return 0;
}
