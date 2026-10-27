#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

void print_menu() {
    printf(
        "\n \n"
        "\t===========================================================================\n"
        "\t \tEscolha uma opcao:\n"
        "\t \t \t1 - Inserir uma solicitacao de manutencao\n"
        "\t \t \t2 - Remover uma solicitacao\n"
        "\t \t \t3 - Consultar uma solicitacao\n"
        "\t \t \t4 - Alterar a prioridade e/ou periodo de uma solicitacao\n"
        "\t \t \t5 - Exibir a ordem da realizacao da manutencao\n"
        "\t \t \t6 - Exibir todas as solicitacoes\n"
        "\t \t \t0 - Finalizar\n"
        "\t===========================================================================\n"
        "\nEscolha: "
    );
}

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	int escolha = -1;

	Lista lista = criar_lista();
	clear();

	do {
		print_menu();
		scanf("%d", &escolha);

		switch (escolha) {
		case 1:
		    clear();
			int adicionado = inserir_solicitacao(&lista);
			clear();
			if (adicionado) {
			    printf("\n \t \t============= SOLICITAÇÃO ADICIONADA COM SUCESSO =============");
			} else {
                printf("\n \t \t============= CÓDIGO DE SOLICITAÇÃO JÁ EXISTE =============");
			}
			break;
		case 2:
		    clear();
			int removido = remover_solicitacao(&lista);
			clear();
			if (removido) {
			    printf("\n \t \t============= SOLICITAÇÃO REMOVIDA COM SUCESSO =============");
			} else {
                printf("\n \t \t============= SOLICITAÇÃO NÃO ENCONTRADA =============");
			}
			break;
		case 3:
		    clear();
			consultar_solicitacao(&lista);
			break;
		case 4:
		    clear();
			int alterado = alterar_prioridade(&lista);
			clear();
			if (alterado) {
			    printf("\n \t \t============= PRIORIDADE ALTERADA COM SUCESSO =============");
			} else {
			    printf("\n \t \t============= SOLICITAÇÃO NÃO ENCONTRADA =============");
			}
			break;
		case 5:
		    clear();
			exibir_ordem(&lista);
			break;
		case 6:
	        clear();
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
