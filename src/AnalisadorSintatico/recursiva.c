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
void throwSyntaxError();
void AddStartToSyntaxTree(char* tokenName);
void AddEndToSyntaxTree(char* tokenName);
void AddLexemaToSyntaxTree(Token token);

Token* AddToTokenList(char *tokenName, char *tokenLexema);
int tokenEh(Token t, char* tokenName);

void casoDeTesteSucesso(){
    AddToTokenList("(", "(");
    AddToTokenList("a", "1"); 
    AddToTokenList("+", "+");
    AddToTokenList("a", "2");
    AddToTokenList(")", ")");
}

void casoDeTeste_Falha1(){
    //AddToTokenList("(", "(");
    AddToTokenList("a", "1"); 
    AddToTokenList("+", "+");
    AddToTokenList("a", "2");
    AddToTokenList(")", ")");
}

void casoDeTeste_Falha2(){
    AddToTokenList("(", "(");
    AddToTokenList("a", "1"); 
    AddToTokenList("+", "+");
    AddToTokenList("a", "2");
    //AddToTokenList(")", ")");
}

void casoDeTeste_Falha3(){
    AddToTokenList("(", "(");
    AddToTokenList("a", "1"); 
    AddToTokenList("+", "+");
    //AddToTokenList("a", "2");
    AddToTokenList(")", ")");
}

int main(int argc, char **argv) {

    casoDeTeste_Falha2();
    // Sempre começa com S.
    AdvanceToken();
    compilaS();
    if(!ehFinal()){
        throwSyntaxError();
    }


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
        throwSyntaxError();
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
        throwSyntaxError();
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


void throwSyntaxError(){
    fprintf(stderr, "%s\n", "Linguagem nao aceita.");
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
Token* AddToTokenList(char *tokenName, char *tokenLexema){
    Token *tok = malloc(sizeof(Token));
    strcpy(tok->tokenName, tokenName);
    strcpy(tok->lexema, tokenLexema);
    listaDeTokens[lastToken++] = *tok;
    return tok;
}