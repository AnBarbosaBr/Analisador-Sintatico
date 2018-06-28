#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>



typedef struct informacoes {
    char token[255]; // ajustar tamanho do char para corresponder ao maior token,
    char lexema[255];
    int linha;
    int coluna; } informacoes;

void analyse(char *arquivo);
void analiseLexica(FILE *fb);
//void analisaEspacos(char ch, struct informacoes *token, int *numeroDeTokens);
void analisaNaoEspacos(char ch, struct informacoes *token, int *numeroDeTokens);




int main(int argc, char **argv){

    char *fileDir;
    if(argc > 1)    { // Foi informado um caminho.
        fileDir = argv[1];
    }

            // não foi informado um arquivo,
    else{   // provavelmente estamos testando a aplicação
        fileDir = "../Testes/teste1.jl";
    }
    

    analyse(fileDir);
    printf("Encerrando com Sucesso.");
    return 0;
}

void analyse(char *arquivo) {
    FILE *file_pointer = fopen(arquivo, "r");

    if(file_pointer == NULL){
        printf("Erro enquanto tentava ler o arquivo %s\n", arquivo);
        exit(1);
    }
    else{
        analiseLexica(file_pointer);
    }
}

void analiseLexica(FILE *fp) {
    
    char ch;
    informacoes tokenContador;
    int numeroDeTokens = 0;
    tokenContador.linha = 1;  // linhas são numeradas de 1 em diante.
    tokenContador.coluna = 1; // colunas são numeradas de 1 em diante.
    while((ch = fgetc(fp)) != EOF)
    {
        if(isspace(ch)){
            analisaEspacos(ch, &tokenContador, &numeroDeTokens);
        } else{
            analisaNaoEspacos(ch, &tokenContador, &numeroDeTokens);
        }
        
    }
    printf("Linhas %d e Colunas %d\n" ,tokenContador.linha, tokenContador.coluna);
}

void analisaEspacos(char ch, informacoes *tokens, int *numeroDeTokens)
{
    if(ch == '\n')
    {
        tokens->linha++;
        tokens->coluna = 0;
    } else {
        tokens->coluna++;
    }
}
void analisaNaoEspacos(char ch, informacoes *tokens, int *numeroDeTokens)
{
    tokens->coluna++;
    
}