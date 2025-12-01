#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição  struct Territorio
struct Territorio {
    char nome[30];     // Nome do território (até 29 caracteres + \0)
    char cor[10];      // Cor do exército (até 9 caracteres + \0)
    int tropas;        // Quantidade de tropas
};

// funções
void limparBuffer();
void cadastrarTerritorios(struct Territorio* territorios, int quantidade);
void exibirTerritorios(struct Territorio* territorios, int quantidade);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);
void exibirMenuAtaque(struct Territorio* territorios, int quantidade);

// Função para limpar buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função de cadastrar territórios
void cadastrarTerritorios(struct Territorio* territorios, int quantidade) {
    printf("\n*-*-* CADASTRO DE %d TERRITORIOS *-*-*\n\n", quantidade);
    
    for(int i = 0; i < quantidade; i++) {
        printf("\n-*-*- Cadastro do Territorio %d -*-*-\n", i + 1);
        
        // Entrada do nome do território
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        // Entrada da cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas (minimo 1): ");
        scanf("%d", &territorios[i].tropas);
        limparBuffer();
        
        // Validação mínima de tropas
        if (territorios[i].tropas < 1) {
            printf("Ajustando para minimo de 1 tropa.\n");
            territorios[i].tropas = 1;
        }
    }
}

// Função exibir todos os territórios
void exibirTerritorios(struct Territorio* territorios, int quantidade) {
    printf("\n*-*-*-* MAPA DOS TERRITORIOS *-*-*-*\n");
    for(int i = 0; i < quantidade; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", 
               i + 1, 
               territorios[i].nome, 
               territorios[i].cor, 
               territorios[i].tropas);
    }
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
}

// Função de ataque entre dois territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante, dadoDefensor;
    
    printf("\n*-*-* SIMULACAO DE ATAQUE *-*-*\n");
    printf("ATACANTE: %s (Cor: %s, Tropas: %d)\n", 
           atacante->nome, atacante->cor, atacante->tropas);
    printf("DEFENSOR: %s (Cor: %s, Tropas: %d)\n", 
           defensor->nome, defensor->cor, defensor->tropas);
    
    // Verifica se o atacante tem tropas suficientes
    if (atacante->tropas < 2) {
        printf("ERRO: Atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }
    
    // Sorteio dos dados (1-6 como um dado real)
    dadoAtacante = (rand() % 6) + 1;
    dadoDefensor = (rand() % 6) + 1;
    
    printf("\nDADOS SORTEADOS:\n");
    printf("  Atacante: %d\n", dadoAtacante);
    printf("  Defensor: %d\n", dadoDefensor);
    
    // Lógica da batalha empate = atacante vence
    if (dadoAtacante >= dadoDefensor) {
        printf("\n--->> RESULTADO: ATACANTE VENCEU! <<---\n");
        
        // Atacante vence - defensor perde 1 tropa
        defensor->tropas--;
        
        printf("Defensor perdeu 1 tropa. Tropas restantes: %d\n", defensor->tropas);
        
        // Verifica se o defensor foi eliminado
        if (defensor->tropas <= 0) {
            printf("\n--->> CONQUISTA! O territorio %s foi conquistado! <<---\n", defensor->nome);
            
            // Transfere o território para o atacante
            strcpy(defensor->cor, atacante->cor);
            
            // Atacante move tropas para o território conquistado
            // (Mantém pelo menos 1 tropa no território original)
            int tropasParaMover = atacante->tropas / 2;
            if (tropasParaMover < 1) tropasParaMover = 1;
            
            atacante->tropas -= tropasParaMover;
            defensor->tropas = tropasParaMover;
            
            printf("Atacante moveu %d tropas para o territorio conquistado.\n", tropasParaMover);
            printf("Tropas do atacante no territorio original: %d\n", atacante->tropas);
        }
    } else {
        printf("\n--->> RESULTADO: DEFENSOR VENCEU! <<---\n");
        
        // Defensor vence - atacante perde 1 tropa
        atacante->tropas--;
        
        printf("Atacante perdeu 1 tropa. Tropas restantes: %d\n", atacante->tropas);
    }
    
    printf("*-*-* FIM DA BATALHA *-*-*\n\n");
}

// Função para exibir menu de ataque e gerenciar as batalhas
void exibirMenuAtaque(struct Territorio* territorios, int quantidade) {
    int continuar = 1;
    int escolhaAtacante, escolhaDefensor;
    
    printf("\n*-*-* FASE DE BATALHAS *-*-*\n");
    printf("Regras:\n");
    printf("- Atacante precisa de pelo menos 2 tropas\n");
    printf("- Empate favorece o atacante\n");
    printf("- Se atacante vencer: defensor perde 1 tropa\n");
    printf("- Se defensor vencer: atacante perde 1 tropa\n");
    printf("- Se defensor chegar a 0 tropas: territorio e conquistado\n");
    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    
    while (continuar) {
        // Exibe o mapa atual
        exibirTerritorios(territorios, quantidade);
        
        // Escolha do território atacante
        printf("ESCOLHA O TERRITORIO ATACANTE (1 a %d):\n", quantidade);
        printf("Territorios disponiveis para ataque (com pelo menos 2 tropas):\n");
        
        for (int i = 0; i < quantidade; i++) {
            if (territorios[i].tropas >= 2) {
                printf("  %d. %s (Cor: %s, Tropas: %d)\n", 
                       i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
            }
        }
        
        printf("\nDigite o numero do territorio atacante (0 para sair): ");
        scanf("%d", &escolhaAtacante);
        limparBuffer();
        
        if (escolhaAtacante == 0) {
            continuar = 0;
            printf("Fase de batalhas encerrada.\n");
            break;
        }
        
        // Valida escolha do atacante
        if (escolhaAtacante < 1 || escolhaAtacante > quantidade) {
            printf("Escolha invalida! Tente novamente.\n");
            continue;
        }
        
        struct Territorio* atacante = &territorios[escolhaAtacante - 1];
        
        if (atacante->tropas < 2) {
            printf("Este territorio nao tem tropas suficientes para atacar (minimo: 2)!\n");
            continue;
        }
        
        // Escolha do território defensor
        printf("\nESCOLHA O TERRITORIO DEFENSOR (1 a %d, exceto %d):\n", quantidade, escolhaAtacante);
        printf("Territorios que podem ser atacados (diferentes da cor %s):\n", atacante->cor);
        
        for (int i = 0; i < quantidade; i++) {
            if (i != (escolhaAtacante - 1) && strcmp(territorios[i].cor, atacante->cor) != 0) {
                printf("  %d. %s (Cor: %s, Tropas: %d)\n", 
                       i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
            }
        }
        
        printf("\nDigite o numero do territorio defensor: ");
        scanf("%d", &escolhaDefensor);
        limparBuffer();
        
        // Valida escolha do defensor
        if (escolhaDefensor < 1 || escolhaDefensor > quantidade) {
            printf("Escolha invalida! Tente novamente.\n");
            continue;
        }
        
        if (escolhaDefensor == escolhaAtacante) {
            printf("Nao pode atacar seu proprio territorio! Tente novamente.\n");
            continue;
        }
        
        struct Territorio* defensor = &territorios[escolhaDefensor - 1];
        
        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("Nao pode atacar um territorio da mesma cor! Tente novamente.\n");
            continue;
        }
        
        // Realiza o ataque
        atacar(atacante, defensor);
        
        // Pergunta se deseja continuar
        printf("Deseja realizar outro ataque? (1-Sim / 0-Nao): ");
        scanf("%d", &continuar);
        limparBuffer();
    }
}

// Função para liberar memória alocada dinamicamente
void liberarMemoria(struct Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("Memoria liberada com sucesso!\n");
    }
}

int main() {
    struct Territorio* territorios = NULL;
    int quantidade;
    
    // gerador de números aleatórios
    srand(time(NULL));
    
    printf("*-*-* MUNDO WAR - SISTEMA DE BATALHAS *-*-*\n\n");
    
    // Solicita a quantidade de territórios
    printf("Quantos territorios deseja cadastrar? (minimo 2): ");
    scanf("%d", &quantidade);
    limparBuffer();
    
    if (quantidade < 2) {
        printf("Quantidade minima de territorios e 2. Usando 2 territorios.\n");
        quantidade = 2;
    }
    
    // Alocação DINÂMICA de memória usando calloc
    territorios = (struct Territorio*)calloc(quantidade, sizeof(struct Territorio));
    
    if (territorios == NULL) {
        printf("ERRO: Nao foi possivel alocar memoria!\n");
        return 1;
    }
    
    // Cadastra os territórios
    cadastrarTerritorios(territorios, quantidade);
    
    // Exibe os territórios cadastrados
    printf("\n*-*-* TERRITORIOS CADASTRADOS *-*-*\n");
    exibirTerritorios(territorios, quantidade);
    
    // Inicia a fase de batalhas
    exibirMenuAtaque(territorios, quantidade);
    
    // Exibe o estado final dos territórios
    printf("\n*-*-* ESTADO FINAL DOS TERRITORIOS *-*-*\n");
    exibirTerritorios(territorios, quantidade);
    
    // Libera a memória alocada dinamicamente
    liberarMemoria(territorios);
    
    printf("\nPrograma encerrado. Ate a proxima batalha!\n");
    return 0;
}