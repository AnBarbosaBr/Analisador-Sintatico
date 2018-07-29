#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Exemplo para a linguagem:
// S -> F
// S -> ( S + F )
// F -> a
// GLOBAIS:

char* syntaxTree;

typedef struct Token {
    char tokenName[255]; // ajustar tamanho do char para corresponder ao maior token,
    char lexema[255];
    int linha;
    int coluna;
} Token;

Token listaDeTokens[2024];
int lastToken = 0;
int currentToken = -1;



void compilaS();
void compilaF();
void eat(Token token, char* token_esperado);
Token GetCurrentToken();
void AdvanceToken();
int ehFinal();
void throwSyntaxError(Token erro);
void AddStartToSyntaxTree(char* tokenName);
void AddEndToSyntaxTree(char* tokenName);
void AddLexemaToSyntaxTree(Token token);

Token* AddToTokenList(char *tokenName, char *tokenLexema, int linha, int coluna);
int tokenEh(Token t, char* tokenName);

void casoDeTesteSucesso(){
    AddToTokenList("(", "(", 1, 0);
    AddToTokenList("a", "1", 2, 0); 
    AddToTokenList("+", "+", 3, 0);
    AddToTokenList("a", "2", 4, 0);
    AddToTokenList(")", ")", 5, 0);
}

void casoDeTeste_Falha1(){
    //AddToTokenList("(", "(", 1, 0);
    AddToTokenList("a", "1", 2, 0); 
    AddToTokenList("+", "+", 3, 0);
    AddToTokenList("a", "2", 4, 0);
    AddToTokenList(")", ")", 5, 0);
}

void casoDeTeste_Falha2(){
    AddToTokenList("(", "(", 1, 0);
    AddToTokenList("a", "1", 2, 0); 
    AddToTokenList("+", "+", 3, 0);
    AddToTokenList("a", "2", 4, 0);
    //AddToTokenList(")", ")", 5, 0);
}

void casoDeTeste_Falha3(){
    AddToTokenList("(", "(", 1, 0);
    AddToTokenList("a", "1", 2, 0); 
    AddToTokenList("+", "+", 3, 0);
    //AddToTokenList("a", "2", 4, 0);
    AddToTokenList(")", ")", 5, 0);
}
void casoDeTeste_Falha4(){
    AddToTokenList("(", "(", 1, 0);
    AddToTokenList("a", "1", 2, 0); 
    //AddToTokenList("+", "+", 3, 0);
    AddToTokenList("a", "2", 4, 0);
    AddToTokenList(")", ")", 5, 0);
}


void casoDeTeste_Sucesso2(){
    AddToTokenList("(", "(", 1, 0);
    AddToTokenList("(", "(", 2, 0);
    AddToTokenList("a", "5", 3, 0);
    AddToTokenList("+", "+", 4, 0);
    AddToTokenList("a", "1", 5, 0);
    AddToTokenList(")", ")", 6, 0); 
    AddToTokenList("+", "+", 7, 0);
    AddToTokenList("a", "2", 8, 0);
    AddToTokenList(")", ")", 9, 0);
}

void casoDeTeste_Falha5(){
    AddToTokenList("(", "(", 1, 0);
    AddToTokenList("(", "(", 2, 0);
    AddToTokenList("a", "5", 3, 0);
    AddToTokenList("+", "+", 4, 0);
    AddToTokenList("a", "1", 5, 0);
    AddToTokenList(")", ")", 6, 0); 
    AddToTokenList("+", "+", 7, 0);
    AddToTokenList("a", "2", 8, 0);
    AddToTokenList(")", ")", 9, 0);
    AddToTokenList(")", ")", 10, 0);
}
int main(int argc, char **argv) {

    casoDeTeste_Falha5();
    // Sempre começa com S.
    AdvanceToken();
    compilaS();
    if(!ehFinal()){
        throwSyntaxError(GetCurrentToken());;
    }
    printf("\nAnalise Completa. Essa sequencia de tokens respeita a Gramatica.\n");


}


void compilaS(){
    Token token = GetCurrentToken();
      AddStartToSyntaxTree("S");
    if(tokenEh(token, "(")){ // seguimos a regra "S-> ( S + F )"
        eat(GetCurrentToken(), "(");
        compilaS();
        eat(GetCurrentToken(), "+");
        compilaF();
        //printf("Analisando ultimo item: %s", GetCurrentToken().lexema);
        eat(GetCurrentToken(), ")");
    } else{
        compilaF();
    }
    AddEndToSyntaxTree("S");
}




void compilaF(){
    Token token = GetCurrentToken();
    AddStartToSyntaxTree("F");
    if(tokenEh(token, "a")) {
        eat(GetCurrentToken(), "a");
    } else {
        throwSyntaxError(token);
    }
    AddEndToSyntaxTree("F");
}


void eat(Token token, char* token_esperado)
{
    if(tokenEh(token, token_esperado)) {
        AddStartToSyntaxTree(token.tokenName);
        AddLexemaToSyntaxTree(token);
        AddEndToSyntaxTree(token.tokenName);
        AdvanceToken();
    }

    else {
        throwSyntaxError(token);
    }
}


Token GetCurrentToken(){
    return listaDeTokens[currentToken];
}

// Retorna verdadeiro se não há diferenças entre t.tokenName e tokenName.
int tokenEh(Token t, char* tokenName){
    return (strcmp(t.tokenName, tokenName) == 0);
}

void AdvanceToken(){
    currentToken++;
    // if(ehFinal()){
    //     printf("Arquivo analisado com sucesso. Essa sintaxe eh valida.");
    //     exit(EXIT_SUCCESS);
    // }
}

int ehFinal(){
    return (currentToken==lastToken);
}


void throwSyntaxError(Token erro){
    fprintf(stderr, "Linguagem nao aceita. Erro no token %s na linha %d col %d\n", erro.lexema, erro.linha, erro.coluna);
    exit(EXIT_FAILURE);;
}


void AddStartToSyntaxTree(char* tokenName){
    printf("<");
    printf(tokenName);
    printf("> \n");
}
void AddEndToSyntaxTree(char* tokenName){
    printf("</");
    printf(tokenName);
    printf(">\n");
}

void AddLexemaToSyntaxTree(Token token){
    printf("%s\n", token.lexema);
}
Token* AddToTokenList(char *tokenName, char *tokenLexema, int linha, int coluna){
    Token *tok = malloc(sizeof(Token));
    strcpy(tok->tokenName, tokenName);
    strcpy(tok->lexema, tokenLexema);
    tok->linha = linha;
    tok->coluna = coluna;
    listaDeTokens[lastToken++] = *tok;
    return tok;
}