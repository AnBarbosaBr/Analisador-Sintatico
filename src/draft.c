#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define PROCESSANDO "em processamento"
#define NOVO_TOKEN "estado inicial"
#define ERRO_TOKEN "ocorreu um erro"

#define IDENTIFICADOR "IDENTIFICADOR"
#define NUMERO "NUMERO"

#define PONTO_VIRGULA "PONTO_VIRGULA"
#define VIRGULA "VIRGULA"
#define ABRE_PARENTESES "ABRE_PARENTESES"
#define FECHA_PARENTESES "FECHA_PARENTESES"
#define ABRE_CHAVES "ABRE_CHAVES"
#define FECHA_CHAVES "FECHA_CHAVES"
#define ATRIBUICAO "ATRIBUICAO"
#define OPERADOR "OPERADOR"

typedef struct informacoes {
    char token[255]; // ajustar tamanho do char para corresponder ao maior token,
    char lexema[255];
    int linha;
    int coluna; 
    } informacoes;

void analyse(char *arquivo);
void analiseLexica(FILE *fb);
void consomeEspacos(char ch, struct informacoes *token, int *numeroDeTokens);
informacoes analisaNaoEspacos(char ch, struct informacoes *token, int *numeroDeTokens);
void imprimeToken(informacoes token);



int main(int argc, char **argv){

    printf(" Iniciando operacao \n");
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
    informacoes tokenRetornado;
    int numeroDeTokens = 0;
    tokenContador.linha = 1;  // linhas são numeradas de 1 em diante.
    tokenContador.coluna = 1; // colunas são numeradas de 1 em diante.
    strcpy(tokenContador.token, NOVO_TOKEN); // token no estado inicial.

    while((ch = fgetc(fp)) != EOF)
    {
        // Se estamos processando algum token
        if(strcmp(tokenContador.token , NOVO_TOKEN) != 0){
            if(isspace(ch)){ // Encontramos um espaço, 
                    //terminamos o processamento.
                    imprimeToken(tokenContador);
                    // voltamos a buscar outro token
                    setToken(&tokenContador, NOVO_TOKEN, "");
            } 
        }  


        // Se estamos procurando um novo token, 
        if( (strcmp(tokenContador.token, NOVO_TOKEN) == 0) ) {
            // Se encontramos espaços
            if(isspace(ch)){
                    consomeEspacos(ch, &tokenContador, &numeroDeTokens);
            } else{ // Se encontramos caractere
                tokenContador = analisaNaoEspacos(ch, &tokenContador, &numeroDeTokens);
                // Se o token não estiver mais PROCESSANDO, imprimimos o resultado.
                  
        }}
    }
    printf("Linhas %d e Colunas %d\n" ,tokenContador.linha, tokenContador.coluna);
}


void consomeEspacos(char ch, informacoes *tokens, int *numeroDeTokens)
{
    if(ch == '\n')
    {
        tokens->linha++;
        tokens->coluna = 0;
    } else {
        tokens->coluna++;
    }
}
/*
informacoes stubInfo(informacoes *tokens)
{
    informacoes tokenARetornar = { .token = "PROCESSANDO", 
                                    .lexema = "",
                                    .linha = tokens->linha,
                                    .coluna = tokens->coluna
                                    };
    return tokenARetornar;
}
*/
void setTokenValue(informacoes *token, char *novoValor)
{
    strcpy(token->token, novoValor);
}

void appendToLexema(informacoes *token, char aAnexar)
{
    // Criar uma maneira de "adicionar" o caractere ao lexema.
    // Essa não funciona direito.
    printf("Anexando %c ao lexema %c\n", aAnexar, *token->lexema);
    strcat(token->lexema, &aAnexar);
}
informacoes analisaNaoEspacos(char ch, informacoes *tokens, int *numeroDeTokens)
{
    assert(!isspace(ch));
    if(strcmp(tokens->token, NOVO_TOKEN)==0){ //estado inicial
        if(isalnum(ch))
        {
            processaNewAlfaNumerico(ch, tokens);
        } else
        {
            processaNewSimbolo(ch, tokens);
        }
    } else
    {
        if(isalnum(ch))
        {
            processaNewAlfaNumerico(ch, tokens);
        } else
        {
            processaNewSimbolo(ch, tokens);
        } 
    }
    printf("\n processamento %c  -  ", ch);
    tokens->coluna++;

    return *tokens;
}

void setToken(informacoes *token, char *newToken, char *newLexema)
{
    strcpy(token->token , newToken);
    strcpy(token->lexema , newLexema);
}
void processaNewAlfaNumerico(char ch, informacoes *token)
{
    if(isalpha(ch))
    {
        setTokenValue(token, IDENTIFICADOR);
        appendToLexema(token, ch);
    }
    if(isdigit(ch)){
        setTokenValue(token, NUMERO);
        appendToLexema(token, ch);
    }
}

void processaNewSimbolo(char ch, informacoes *token)
{
    switch (ch)
    {
        case ';': setToken(token, PONTO_VIRGULA , &ch); break;
        case '(': setToken(token, ABRE_PARENTESES , &ch); break;
        case ')': setToken(token, FECHA_PARENTESES , &ch); break;
        case '{': setToken(token, ABRE_CHAVES, &ch); break;
        case '}': setToken(token, FECHA_CHAVES, &ch); break;
        case ',': setToken(token, VIRGULA, &ch); break;
        case '=': setToken(token, ATRIBUICAO, &ch); break;
        case '-': setToken(token, OPERADOR, &ch); break;
        case '*': setToken(token, OPERADOR, &ch); break;
        case '/': setToken(token, OPERADOR, &ch); break;
        case '+': setToken(token, OPERADOR, &ch); break;
    }
}


void imprimeToken(informacoes token){
    printf("%s @ %s @ %d @ %d\n", token.token, token.lexema,
                             token.linha, token.coluna);
}