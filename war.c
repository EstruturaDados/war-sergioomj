#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];     // Nome do território (até 29 caracteres + \0)
    char cor[10];      // Cor do exército (até 9 caracteres + \0)
    int tropas;        // Quantidade de tropas
};

int main() {
    // Vetor para armazenar 5 territórios
    struct Territorio territorios[5];
    char buffer[10]; // Buffer auxiliar para limpar entrada numérica
    
    printf("*-*-* CADASTRO TERRITORIAL MUNDO WAR *-*-*\n\n");
    
    // Entrada de dados - cadastro dos territórios
    for(int i = 0; i < 5; i++) {
        // (i+1) Transforma posição 0 em 1 e assim sucessivamente
        printf("\n-*-*- Cadastro do Territorio %d -*-*-\n", i + 1);
        
        // Limpa o buffer do teclado antes de cada leitura
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        // Leitura do nome do território com fgets
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);
        // Remove o \n do final se existir
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        // Leitura da cor do exército com fgets
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);
        // Remove o \n do final se existir
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        // Leitura da quantidade de tropas com scanf, melhor para numeros
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        // Limpa o buffer após o scanf para preparar próxima iteração
        while ((c = getchar()) != '\n' && c != EOF);
        
        // Linha em branco para melhorar organização e visualização
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