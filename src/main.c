/*
    B-Tree - Antonio Carlos Falcão Petri e Thiago Yonamine
    DC - UFSCar - São Carlos - 2015

    Essa é uma aplicação DEMO para apresentar a B-Tree desenvolvida.

    Cada chave inserida na B-Tree será associada à uma combinação de
    duas letras minúsculas, isto é, a recuperação de uma chave
    trará como retorno um valor do domínio 'aa', ..., 'zz'.

    Esses valores não são reaproveitados quando a chave associada é
    removida, limitando cada B-Tree à inserção/remoção de 676 chaves.

    Uso:
        $ make
        $ ./bin/btree
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "btree.h"
#include "btree_tools.h"

/*
    Define uma forma de limpar a tela do terminal,
    tanto no Linux quanto no Windows.
 */
#ifdef __linux__
    #define CLEAR() (system("clear"))
#elif _WIN32
    #define CLEAR() (system("cls"))
#endif

#define MSG_LEN 100

/*
    Imprime uma mensagem de cabeçalho
    compartilhada por todas as screens
 */
void print_header();

/*
    Tela de Home
    Permite acessar a screen de criação de B-Tree e a screen Sobre.
    Permite sair da aplicação.
 */
int home_screen();
/*
    Informações básicas sobre o projeto B-Tree e essa DEMO
 */
int about_screen();
/*
    Tela para definir a ordem da B-Tree a ser criada
 */
int run_screen();
/*
    Tela onde as operações INSERÇÃO, REMOÇÃO, PESQUISA, IMPRESSÃO serão executadas
 */
int running_screen();
/*
    Função auxiliar para gerar uma mensagem de "despedida"
 */
void goodbye();
/*
    Função auxiliar para gerar os valores que serão associados às chaves inseridas
 */
void populate_values();
/*
    A ordem das 3 primeiras screens deve ser RUN, ABOUT, EXIT.
    Os valores atribuídos à elas são utilizados na lógica interna do menu.
 */
typedef enum {
	RUN, ABOUT, EXIT, HOME, RUNNING
} screen;

/*
    Indica uma mensagem que será exibida no topo da próxima screen.
    É uma forma de comunicar mensagens ao usuário.
    O valor default (quando não há mensagens para exibir) deve ser o caracter '-'.
 */
char msg[MSG_LEN];
/*
    Ponteiro global para a B-Tree que será instanciada.
    Esse ponteiro é único, sendo sempre reaproveitado pela aplicação.
 */
BTree *tree;

/*
    Número máximo de chaves que podem ser inseridas em uma mesma DEMO/B-Tree
 */
int max_keys = 26*26;
/*
    Contador de quantas keys foram inseridas na B-Tree atual.
    É reiniciado sempre que a B-Tree é deletada.
 */
int n_keys;
/*
    Valores que serão associados às chaves da B-Tree.
    Os valores são duas letras minúsculas: 'aa', ..., 'zz',
    gerando 676 combinações diferentes.
 */
char values[26*26][3];

void populate_values() {
	int i, j;
	for (i = 0; i < 26; ++i) {
		for (j = 0; j < 26; ++j) {
			snprintf(values[i*26+j], 3, "%c%c", 'a'+i, 'a'+j);
		}
	}
}

int home_screen() {
	int opt;
	int n_items = 3;
	// Itens no menu
	char list[3][12] = { "Nova B-Tree", "Sobre", "Sair" };

	print_header();

	int i;
	for (i = 0; i < n_items; ++i) {
		printf(" %d) %s\n", i+1, list[i]);
	}
	printf("\n");
	printf(" Digite uma opção: ");
	scanf("%d%*c", &opt);

	if (opt < 1 || opt > n_items) {
		snprintf(msg, MSG_LEN, " Opção inválida.");
		return HOME;
	}

	return opt-1;
}

int about_screen() {
	print_header();
	printf( "---------------------------------------------------------\n" \
	        "--       Trabalho apresentado na disciplina ORI        --\n" \
	        "--       ministrada pelo Prof. Dr. Ricardo Cerri       --\n" \
	        "--             UFSCar - São Carlos - 2/2015            --\n" \
	        "---------------------------------------------------------\n");
	printf("\n");
	printf( "---------------------------------------------------------\n" \
	        "--        Essa é uma aplicação DEMO que insere         --\n" \
	        "--          chaves associando-as aos valores:          --\n" \
	        "--          \'aa\', \'ab\', ..., \'da\', ..., \'zz\'           --\n" \
	        "---------------------------------------------------------\n");
	printf("\n");

	printf(" Pressione ENTER para voltar ao menu. ");
	getchar();

	return HOME;
}

int run_screen() {
	print_header();

	int order;

	printf("  Um nó de uma B-Tree de ordem T deve ter no mínimo T-1\n" \
	       "               e no máximo 2*T filhos\n");
	printf("\n");
	printf(" Digite a ordem T da sua B-Tree: ");
	scanf("%d%*c", &order);

	// Única criação de uma B-Tree
	tree = btree_new(order);
	snprintf(msg, MSG_LEN, " B-Tree de ordem %d alocada.", order);

	return RUNNING;
}

int running_screen() {
	int n_items = 5;
	// Itens no menu
	char list[5][15] = { "Inserir", "Pesquisar", "Remover", "Imprimir DFS", "Voltar" };
	int opt;

	print_header();

	int i;
	for (i = 0; i < n_items; ++i) {
		printf(" %d) %s\n", i+1, list[i]);
	}

	printf("\n");
	printf(" Digite uma opção: ");
	scanf("%d%*c", &opt);

	int key;
	node_position pos;
	switch (opt) {
	case 1:                 // Inserir
		if (n_keys == max_keys) {
			snprintf(msg, MSG_LEN, " O máximo de chaves adicionáveis para essa demo é %d.", max_keys);
		}
		else {
			printf(" Digite uma CHAVE que será associada ao VALOR \'%s\': ", values[n_keys]);
			scanf("%d", &key);
			pos = btree_insert(tree, key, values[n_keys]);
			if (pos.node == NULL) {
				snprintf(msg, MSG_LEN, " Inserção falhou. A CHAVE %d já existe na B-Tree.", key);
			}
			else {
				snprintf(msg, MSG_LEN, " Inserção da CHAVE %d associada ao VALOR \'%s\' realizada com sucesso.",
				         key, values[n_keys]);
				n_keys++;
			}
		}
		break;
	case 2:                 // Pesquisar
		printf(" Digite uma CHAVE para pesquisar: ");
		scanf("%d", &key);
		pos = btree_find(tree, key);
		if (pos.node == NULL) {
			snprintf(msg, MSG_LEN, " A CHAVE %d não foi encontrada na B-Tree.", key);
		}
		else {
			snprintf(msg, MSG_LEN, " A CHAVE %d foi encontrada associada ao VALOR \'%s\'.",
			         key, (char*) pos.node->keys[pos.index]->value);
		}

		break;
	case 3:                 // Remover
		printf(" Digite uma CHAVE para remover: ");
		scanf("%d", &key);
		pos = btree_remove(tree, key);
		if (pos.node == NULL) {
			snprintf(msg, MSG_LEN, " A CHAVE %d não foi encontrada na B-Tree.", key);
		}
		else {
			snprintf(msg, MSG_LEN, " A CHAVE %d foi removida com sucesso.", key);
		}
		break;
	case 4:                 // Imprimir
		printf(" Executando uma DFS na B-Tree:\n");
		btree_dfs(tree);
		printf(" Pressione ENTER para continuar. ");
		getchar();
		break;
	case 5:                 // Voltar/Sair
		snprintf(msg, MSG_LEN, " Deletando B-Tree e voltando ao menu");
		goodbye();
		// Única deleção de uma B-Tree
		btree_delete_h(tree);
		return HOME;
		break;
	default:
		snprintf(msg, MSG_LEN, " Opção inválida");
		return RUNNING;
		break;
	}

	return RUNNING;
}

void print_header() {
	CLEAR();
	printf( "---------------------------------------------------------\n" \
	        "--                    B-Tree - v1.0                    --\n" \
	        "--                  Desenvolvido por:                  --\n" \
	        "--      Antonio Carlos Falcão Petri e Thiago Yonamine  --\n" \
	        "---------------------------------------------------------\n");

	printf("\n");

	if (strcmp(msg, "-")) {
		printf("%s\n\n", msg);
		snprintf(msg, MSG_LEN, "-");
	}
}

void goodbye() {
	// Apenas uma animação simples de "loading"
	print_header();
	int i;
	printf(" ");
	for (i = 0; i < 4; ++i) {
		printf(".");
		fflush(stdout);
		usleep(500000);
	}

	CLEAR();
}

int main() {
	screen next_screen = HOME;
	populate_values();
	snprintf(msg, MSG_LEN, "-");
	n_keys = 0;

	while (next_screen != EXIT) {
		switch (next_screen) {
		case HOME:
			next_screen = home_screen();
			break;
		case ABOUT:
			next_screen = about_screen();
			break;
		case RUN:
			next_screen = run_screen();
			break;
		case RUNNING:
			next_screen = running_screen();
			break;
		case EXIT:
			break;
		}
	}

	snprintf(msg, MSG_LEN, " Saindo da aplicação");
	goodbye();

	return 0;
}
