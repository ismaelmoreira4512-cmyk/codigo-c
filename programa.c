#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CAPACIDADE_INICIAL 2

struct Cliente {
    char nome[50];
    int idade;
    char email[50];
};

void linha() {
    printf("========================================\n");
}

void titulo(char texto[]) {
    linha();
    printf(" %-38s\n", texto);
    linha();
}

void lerNome(char nome[]) {
    while (1) {
        printf("Nome   : ");

        if (!fgets(nome, 50, stdin)) continue;

        nome[strcspn(nome, "\n")] = '\0';

        if (strlen(nome) > 0) return;

        printf("Nome invalido!\n");
    }
}

int lerIdade() {
    char buffer[20];
    int idade;

    while (1) {
        printf("Idade  : ");

        if (!fgets(buffer, sizeof(buffer), stdin)) continue;

        idade = atoi(buffer);

        if (idade > 0 && idade < 130) return idade;

        printf("Idade invalida!\n");
    }
}

void lerEmail(char email[]) {
    int ok;

    while (1) {
        printf("Email  : ");

        if (!fgets(email, 50, stdin)) continue;

        email[strcspn(email, "\n")] = '\0';

        if (strlen(email) == 0) {
            printf("Email invalido!\n");
            continue;
        }

        ok = strchr(email, '@') != NULL;

        if (ok) return;

        printf("Email invalido!\n");
    }
}

int compararTexto(char a[], char b[]) {
    int i = 0;

    while (a[i] && b[i]) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) {
            return 0;
        }
        i++;
    }

    return a[i] == '\0' && b[i] == '\0';
}

void cadastrarCliente(struct Cliente **clientes, int *total, int *capacidade) {

    if (*total == *capacidade) {

        int novaCap = (*capacidade) * 2;

        struct Cliente *temp =
            realloc(*clientes, novaCap * sizeof(struct Cliente));

        if (!temp) {
            printf("Erro de memoria!\n");
            return;
        }

        *clientes = temp;
        *capacidade = novaCap;
    }

    titulo("CADASTRO DE CLIENTE");

    lerNome((*clientes)[*total].nome);
    (*clientes)[*total].idade = lerIdade();
    lerEmail((*clientes)[*total].email);

    (*total)++;

    linha();
    printf(" Cliente cadastrado!\n");
    linha();
}

void listarClientes(struct Cliente *clientes, int total) {

    if (total == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }

    titulo("LISTA DE CLIENTES");

    for (int i = 0; i < total; i++) {

        printf("\nCliente %d\n", i + 1);
        linha();

        printf("Nome   : %s\n", clientes[i].nome);
        printf("Idade  : %d\n", clientes[i].idade);
        printf("Email  : %s\n", clientes[i].email);

        linha();
    }
}

void buscarCliente(struct Cliente *clientes, int total) {

    char nomeBusca[50];
    int encontrado = 0;

    titulo("BUSCAR CLIENTE");

    printf("Nome: ");
    if (!fgets(nomeBusca, sizeof(nomeBusca), stdin)) return;

    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {

        if (compararTexto(clientes[i].nome, nomeBusca)) {

            linha();
            printf("Cliente encontrado!\n");
            linha();

            printf("Nome   : %s\n", clientes[i].nome);
            printf("Idade  : %d\n", clientes[i].idade);
            printf("Email  : %s\n", clientes[i].email);

            linha();
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nCliente nao encontrado.\n");
    }
}

void editarCliente(struct Cliente *clientes, int total) {

    char nomeBusca[50];
    int encontrado = 0;

    titulo("EDITAR CLIENTE");

    printf("Nome: ");
    if (!fgets(nomeBusca, sizeof(nomeBusca), stdin)) return;

    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {

        if (compararTexto(clientes[i].nome, nomeBusca)) {

            linha();

            lerNome(clientes[i].nome);
            clientes[i].idade = lerIdade();
            lerEmail(clientes[i].email);

            linha();
            printf("Atualizado!\n");
            linha();

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nCliente nao encontrado.\n");
    }
}

void removerCliente(struct Cliente *clientes, int *total) {

    char nomeBusca[50];
    int encontrado = 0;

    titulo("REMOVER CLIENTE");

    printf("Nome: ");
    if (!fgets(nomeBusca, sizeof(nomeBusca), stdin)) return;

    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {

        if (compararTexto(clientes[i].nome, nomeBusca)) {

            for (int j = i; j < *total - 1; j++) {
                clientes[j] = clientes[j + 1];
            }

            (*total)--;

            linha();
            printf("Removido com sucesso!\n");
            linha();

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nCliente nao encontrado.\n");
    }
}

int main() {

    int opcao;
    int totalClientes = 0;
    int capacidade = CAPACIDADE_INICIAL;

    struct Cliente *clientes =
        malloc(capacidade * sizeof(struct Cliente));

    if (!clientes) {
        printf("Erro de memoria!\n");
        return 1;
    }

    do {

        titulo("SISTEMA DE CLIENTES");

        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Editar\n");
        printf("5 - Remover\n");
        printf("0 - Sair\n");

        linha();
        printf("Opcao: ");

        char buffer[10];
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            opcao = 0;
        } else {
            opcao = atoi(buffer);
        }

        switch (opcao) {

            case 1:
                cadastrarCliente(&clientes, &totalClientes, &capacidade);
                break;

            case 2:
                listarClientes(clientes, totalClientes);
                break;

            case 3:
                buscarCliente(clientes, totalClientes);
                break;

            case 4:
                editarCliente(clientes, totalClientes);
                break;

            case 5:
                removerCliente(clientes, &totalClientes);
                break;
        }

    } while (opcao != 0);

    free(clientes);

    return 0;
}