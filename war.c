#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];     // Nome do território (até 29 caracteres + \0)
    char cor[10];      // Cor do exército (até 9 caracteres + \0)
    int tropas;        // Quantidade de tropas
};

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // Declaração do vetor para armazenar 5 territórios
    struct Territorio territorios[5];
    
    printf("*-*-* CADASTRO TERRITORIAL MUNDO WAR *-*-*\n\n");
    
    // Entrada de dados - cadastro dos territórios
    for(int i = 0; i < 5; i++) {
        printf("\n-*-*- Cadastro do Territorio %d -*-*-\n", i + 1);
        
        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        // UMA ÚNICA limpeza de buffer após o scanf
        limparBuffer();
        
        printf("\n"); 
    }
    
    // Mostrando dados cadastrados
    printf("\n*-*-* DADOS DOS TERRITORIOS CADASTRADOS *-*-*\n\n");
    
    for(int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do exercito: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("\n");
    }
    
    return 0;
}
