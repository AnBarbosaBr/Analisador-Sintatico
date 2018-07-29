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
void AddEntToSyntaxTree(char* tokenName);
Token* AddToTokenList(char *tokenName, char *tokenLexema);


int main(int argc, char **argv) {

    AddToTokenList("a", "1"); 
    AddToTokenList("+", "+");
    AddToTokenList("a", "2");
    // Sempre começa com S.
    AdvanceToken();
    compilaS();
    


}


void compilaS(){
    Token token = GetCurrentToken();
      AddStartToSyntaxTree("S");
    if(tokenEh(token, '(')){ // seguimos a regra "S-> ( S + F )"
        eat(GetCurrentToken(), '(');
        compilaS();
        eat(GetCurrentToken(), '+');
        compilaF();
        eat(GetCurrentToken(), ')');
    } else{
        compilaF();
    }
    AddEndToSyntaxTree("S");
}




void compilaF(){
    Token token = GetCurrentToken();
    AddStartToSyntaxTree("F");
    if(tokenEh(token, 'a')) {
        eat(GetCurrentToken(), 'a');
    } else {
        throwSyntaxError();
    }
    AddEndToSyntaxTree("F");
}


void eat(Token token, char* token_esperado)
{
    if(tokenEh(token, token_esperado)) {
        AddStartToSyntaxTree(token.tokenName);
        AddLexemaToSyntaxTree(GetCurrentLexema());
        AddEndToSyntaxTree(token);
        AdvanceToken();
    }

    else {
        throwSyntaxError();
    }
}


Token GetCurrentToken(){
    return listaDeTokens[currentToken];
}


void AdvanceToken(){
    currentToken++;
    if(ehFinal()){
        print("Arquivo analisado com sucesso. Essa sintaxe é válida.");
        exit(EXIT_SUCCESS);
    }
}

int ehFinal(){
    return (currentToken==lastToken);
}


void throwSyntaxError(){
    fprintf(stderr, "%s\n", "Linguagem não aceita.");
    exit(EXIT_FAILURE);;
}


void AddStartToSyntaxTree(char* tokenName){
    print("(Start-");
    print(tokenName);
    println(")");
}
void AddEntToSyntaxTree(char* tokenName){
    print("(End-");
    print(tokenName);
    println(")");
}

Token* AddToTokenList(char *tokenName, char *tokenLexema){
    Token *tok = malloc(sizeof(Token));
    strcpy(tok->tokenName, tokenName);
    strcpy(tok->lexema, tokenLexema);
    listaDeTokens[lastToken++] = *tok;
    return tok;
}