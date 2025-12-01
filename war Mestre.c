#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Definições de constantes
#define MAX_NOME 30
#define MAX_COR 10
#define MAX_MISSAO 100
#define MIN_TROPAS 1
#define MIN_TERRITORIOS 2
#define DADO_MAX 6
#define NUM_MISSOES 5

// funções
void limparBuffer();
void cadastrarTerritorios(struct Territorio* territorios, int quantidade);
void exibirTerritorios(struct Territorio* territorios, int quantidade);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void exibirMenuAtaque(struct Territorio* territorios, int quantidade, char* missaoJogador);
void inicializarMissoes(char* missoes[]);
void atribuirMissao(char** destinoMissao, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho);
void exibirMissao(char* missao);
void liberarMemoria(struct Territorio* territorios, char* missao);

// Função para limpar buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para inicializar o vetor de missões
void inicializarMissoes(char* missoes[]) {
    missoes[0] = "Conquistar pelo menos 3 territorios";
    missoes[1] = "Eliminar todas as tropas da cor vermelha";
    missoes[2] = "Controlar mais da metade dos territorios";
    missoes[3] = "Ter pelo menos 10 tropas no total";
    missoes[4] = "Conquistar 2 territorios seguidos em um turno";
}

// Função para uma missão aleatória ao jogador
void atribuirMissao(char** destinoMissao, char* missoes[], int totalMissoes) {
    // Sorteia um índice aleatório
    int indice = rand() % totalMissoes;
    
    // Aloca memória para armazenar a missão do jogador
    *destinoMissao = (char*)malloc(MAX_MISSAO * sizeof(char));
    
    if (*destinoMissao == NULL) {
        printf("ERRO: Falha ao alocar memoria para missao!\n");
        exit(1);
    }
    
    // Copia a missão sorteada para a variável do jogador
    strcpy(*destinoMissao, missoes[indice]);
}

// Função para verificar se a missão foi cumprida
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    if (missao == NULL || mapa == NULL) {
        return 0;
    }
    
    // Missão 1: Conquistar pelo menos 3 territórios
    if (strstr(missao, "Conquistar pelo menos 3 territorios") != NULL) {
        int territoriosConquistados = 0;
        
        for (int i = 0; i < tamanho; i++) {
            // Verifica se o território pertence ao jogador (cor azul como exemplo)
            if (strcmp(mapa[i].cor, "azul") == 0) {
                territoriosConquistados++;
            }
        }
        
        return territoriosConquistados >= 3;
    }
    
    // Missão 2: Eliminar todas as tropas da cor vermelha
    if (strstr(missao, "Eliminar todas as tropas da cor vermelha") != NULL) {
        int temVermelho = 0;
        
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0) {
                temVermelho = 1;
                break;
            }
        }
        
        return !temVermelho; // Missão cumprida se não houver vermelho
    }
    
    // Missão 3: Controlar mais da metade dos territórios
    if (strstr(missao, "Controlar mais da metade dos territorios") != NULL) {
        int territoriosJogador = 0;
        
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) {
                territoriosJogador++;
            }
        }
        
        return territoriosJogador > (tamanho / 2);
    }
    
    // Missão 4: Ter pelo menos 10 tropas no total
    if (strstr(missao, "Ter pelo menos 10 tropas no total") != NULL) {
        int totalTropas = 0;
        
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) {
                totalTropas += mapa[i].tropas;
            }
        }
        
        return totalTropas >= 10;
    }
    
    // Missão 5: Conquistar 2 territórios seguidos em um turno
    // Esta missão requer rastreamento entre turnos
    // considerando que se o jogador tiver pelo menos 2 territorios
    if (strstr(missao, "Conquistar 2 territorios seguidos em um turno") != NULL) {
        int territoriosConquistados = 0;
        
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) {
                territoriosConquistados++;
            }
        }
        
        // Para simplificar, consideramos cumprida se tiver 2+ territorios
        return territoriosConquistados >= 2;
    }
    
    return 0; // Missão não reconhecida
}

// Função para exibir a missão do jogador
void exibirMissao(char* missao) {
    if (missao != NULL) {
        printf("\n*-*-* SUA MISSAO ESTRATEGICA *-*-*\n");
        printf("%s\n", missao);
        printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    }
}

// Função de cadastro territorios
void cadastrarTerritorios(struct Territorio* territorios, int quantidade) {
    printf("\n*-*-* CADASTRO DE %d TERRITORIOS *-*-*\n\n", quantidade);
    
    for(int i = 0; i < quantidade; i++) {
        printf("\n-*-*- Cadastro do Territorio %d -*-*-\n", i + 1);
        
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, MAX_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, MAX_COR, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        
        printf("Digite a quantidade de tropas (minimo %d): ", MIN_TROPAS);
        scanf("%d", &territorios[i].tropas);
        limparBuffer();
        
        if (territorios[i].tropas < MIN_TROPAS) {
            printf("Ajustando para minimo de %d tropa.\n", MIN_TROPAS);
            territorios[i].tropas = MIN_TROPAS;
        }
    }
}

// Função para exibir todos os territorios
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

// Função de ataque entre dois territorios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante, dadoDefensor;
    static int conquistasSeguidas = 0; // Para missão 5
    
    printf("\n*-*-* SIMULACAO DE ATAQUE *-*-*\n");
    printf("ATACANTE: %s (Cor: %s, Tropas: %d)\n", 
           atacante->nome, atacante->cor, atacante->tropas);
    printf("DEFENSOR: %s (Cor: %s, Tropas: %d)\n", 
           defensor->nome, defensor->cor, defensor->tropas);
    
    if (atacante->tropas < 2) {
        printf("ERRO: Atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }
    
    dadoAtacante = (rand() % DADO_MAX) + 1;
    dadoDefensor = (rand() % DADO_MAX) + 1;
    
    printf("\nDADOS SORTEADOS:\n");
    printf("  Atacante: %d\n", dadoAtacante);
    printf("  Defensor: %d\n", dadoDefensor);
    
    if (dadoAtacante >= dadoDefensor) {
        printf("\n-*-*->> RESULTADO: ATACANTE VENCEU! <<-*-*-\n");
        
        defensor->tropas--;
        
        printf("Defensor perdeu 1 tropa. Tropas restantes: %d\n", defensor->tropas);
        
        if (defensor->tropas <= 0) {
            printf("\n-*-*->> CONQUISTA! O territorio %s foi conquistado! <<-*-*-\n", defensor->nome);
            
            strcpy(defensor->cor, atacante->cor);
            
            int tropasParaMover = atacante->tropas / 2;
            if (tropasParaMover < 1) tropasParaMover = 1;
            
            atacante->tropas -= tropasParaMover;
            defensor->tropas = tropasParaMover;
            
            printf("Atacante moveu %d tropas para o territorio conquistado.\n", tropasParaMover);
            printf("Tropas do atacante no territorio original: %d\n", atacante->tropas);
            
            conquistasSeguidas++;
        } else {
            conquistasSeguidas = 0;
        }
    } else {
        printf("\n-*-*->> RESULTADO: DEFENSOR VENCEU! <<-*-*-\n");
        
        atacante->tropas--;
        conquistasSeguidas = 0;
        
        printf("Atacante perdeu 1 tropa. Tropas restantes: %d\n", atacante->tropas);
    }
    
    printf("*-*-* FIM DA BATALHA *-*-*\n\n");
}

// Função para exibir menu de ataque e gerenciar as batalhas
void exibirMenuAtaque(struct Territorio* territorios, int quantidade, char* missaoJogador) {
    int continuar = 1;
    int escolhaAtacante, escolhaDefensor;
    int turno = 1;
    
    printf("\n*-*-* FASE DE BATALHAS *-*-*\n");
    printf("Regras:\n");
    printf("- Atacante precisa de pelo menos 2 tropas\n");
    printf("- Empate favorece o atacante\n");
    printf("- Se atacante vencer: defensor perde 1 tropa\n");
    printf("- Se defensor vencer: atacante perde 1 tropa\n");
    printf("- Se defensor chegar a 0 tropas: territorio e conquistado\n");
    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    
    while (continuar) {
        printf("\n*-*-* TURNO %d *-*-*\n", turno);
        
        // Verifica se a missão foi cumprida
        if (verificarMissao(missaoJogador, territorios, quantidade)) {
            printf("\n**************************************************\n");
            printf("PARABENS! VOCE CUMPRIU SUA MISSAO!\n");
            printf("Missao: %s\n", missaoJogador);
            printf("VOCE E O VENCEDOR!\n");
            printf("**************************************************\n");
            break;
        }
        
        exibirTerritorios(territorios, quantidade);
        
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
        
        if (escolhaAtacante < 1 || escolhaAtacante > quantidade) {
            printf("Escolha invalida! Tente novamente.\n");
            continue;
        }
        
        struct Territorio* atacante = &territorios[escolhaAtacante - 1];
        
        if (atacante->tropas < 2) {
            printf("Este territorio nao tem tropas suficientes para atacar (minimo: 2)!\n");
            continue;
        }
        
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
        
        atacar(atacante, defensor);
        
        // Verifica novamente após o ataque
        if (verificarMissao(missaoJogador, territorios, quantidade)) {
            printf("\n**************************************************\n");
            printf("PARABENS! VOCE CUMPRIU SUA MISSAO!\n");
            printf("Missao: %s\n", missaoJogador);
            printf("VOCE E O VENCEDOR!\n");
            printf("**************************************************\n");
            break;
        }
        
        printf("Deseja realizar outro ataque neste turno? (1-Sim / 0-Nao): ");
        scanf("%d", &continuar);
        limparBuffer();
        
        turno++;
    }
}

// Função para liberar memória alocada dinamicamente
void liberarMemoria(struct Territorio* territorios, char* missao) {
    if (territorios != NULL) {
        free(territorios);
        printf("Memoria dos territorios liberada com sucesso!\n");
    }
    
    if (missao != NULL) {
        free(missao);
        printf("Memoria da missao liberada com sucesso!\n");
    }
}

int main() {
    struct Territorio* territorios = NULL;
    char* missaoJogador = NULL;
    char* missoes[NUM_MISSOES];
    int quantidade;
    
    // gerador de números aleatórios
    srand(time(NULL));
    
    printf("*-*-* MUNDO WAR - SISTEMA DE BATALHAS COM MISSOES *-*-*\n\n");
    
    // Inicializa o vetor de missões
    inicializarMissoes(missoes);
    
    // Atribui uma missão aleatória ao jogador
    atribuirMissao(&missaoJogador, missoes, NUM_MISSOES);
    
    // Exibe a missão do jogador
    exibirMissao(missaoJogador);
    
    // Solicita a quantidade de territorios
    printf("Quantos territorios deseja cadastrar? (minimo %d): ", MIN_TERRITORIOS);
    scanf("%d", &quantidade);
    limparBuffer();
    
    if (quantidade < MIN_TERRITORIOS) {
        printf("Quantidade minima de territorios e %d. Usando %d territorios.\n", 
               MIN_TERRITORIOS, MIN_TERRITORIOS);
        quantidade = MIN_TERRITORIOS;
    }
    
    // Alocação DINÂMICA de memória usando calloc
    territorios = (struct Territorio*)calloc(quantidade, sizeof(struct Territorio));
    
    if (territorios == NULL) {
        printf("ERRO: Nao foi possivel alocar memoria para territorios!\n");
        if (missaoJogador != NULL) free(missaoJogador);
        return 1;
    }
    
    // Cadastra os territorios
    cadastrarTerritorios(territorios, quantidade);
    
    // Exibe os territorios cadastrados
    printf("\n*-*-* TERRITORIOS CADASTRADOS *-*-*\n");
    exibirTerritorios(territorios, quantidade);
    
    // Inicia a fase de batalhas
    exibirMenuAtaque(territorios, quantidade, missaoJogador);
    
    // Exibe o estado final dos territórios
    printf("\n*-*-* ESTADO FINAL DOS TERRITORIOS *-*-*\n");
    exibirTerritorios(territorios, quantidade);
    
    // Verificação final da missão
    if (!verificarMissao(missaoJogador, territorios, quantidade)) {
        printf("\n*-*-* MISSAO NAO CONCLUIDA *-*-*\n");
        printf("Sua missao era: %s\n", missaoJogador);
        printf("Continue tentando na proxima partida!\n");
    }
    
    // Libera a memória alocada dinamicamente
    liberarMemoria(territorios, missaoJogador);
    
    printf("\nPrograma encerrado. Ate a proxima batalha!\n");
    return 0;
}