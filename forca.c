#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <stdlib.h>
#include <time.h>

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;


void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

void chuta() {
    char chute;
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra) {
    int achou = 0; 

    for(int j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca() {
    int erros = qtderros();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
    
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        int achou = jachutou(palavrasecreta[i]);

        if(achou) {
            printf("%c ", palavrasecreta[i]);
        }
        else {
            printf("_ ");
        }
    }
    printf("\n");
}

void escolhepalavra() {
    FILE* arquivopalavras;
    
    arquivopalavras = fopen("palavras.txt", "r");
        if(!arquivopalavras) {
        printf("Sem arquivo de palavras no diretório\n");
    }
    
    int qtdpalavras;
    fscanf(arquivopalavras, "%d", &qtdpalavras);

    srand(time(0));
    int numeroaleatorio = rand();

    int posicaopalavra = numeroaleatorio % qtdpalavras;

    for(int i = 0; i <= posicaopalavra; i++) {
        fscanf(arquivopalavras, "%s", palavrasecreta);
    }

    fclose(arquivopalavras);
    
}

void adicionapalavra() {
    char quero;
    printf("Deseja adicionar uma nova palavras ao jogo? (S/N)\n");
    scanf(" %c", &quero);

    if(quero == 'S') {
        FILE* arquivopalavras;

        arquivopalavras = fopen("palavras.txt", "r+");
        if(!arquivopalavras) {
            printf("Erro. Arquivo de texto não encontrado no diretório!");
            exit(1);
        }

        printf("Digite a palavras que deseja adicionar:\n");
        char palavraadicionada[TAMANHO_PALAVRA];
        scanf("%s", palavraadicionada);

        int qtd;
        fscanf(arquivopalavras, "%d", &qtd);
        qtd++;

        fseek(arquivopalavras, 0, SEEK_SET);
        fprintf(arquivopalavras, "%d", qtd);

        fseek(arquivopalavras, 0, SEEK_END);
        fprintf(arquivopalavras, "\n%s", palavraadicionada);

        fclose(arquivopalavras);
    }
    else {
        printf("Fim de Jogo!");
    }
}

int qtderros() {
    int erros = 0;
    
    for(int i = 0; i < chutesdados; i++) {
        int existe = 0;
        
        for(int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {
                existe = 1;
                break;
            }
        }

        if(!existe) {
            erros++;
        }
    }

    return erros;
}

int enforcou() {
    qtderros();

    return qtderros() >= 5;
}

int acertou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

int main() {
    
    abertura();
    escolhepalavra();

    do {
        
        desenhaforca();
        chuta();
        
    } while(!acertou() && !enforcou());

    if(acertou()) {
        printf("\nParabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    }
    else{
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
}