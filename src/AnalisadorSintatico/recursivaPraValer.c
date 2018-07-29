#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


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

#define DEC_FUNCAO "DECLARAR_FUNCAO"
#define T_ABRE_PARENTESES "ABRE_PARENTESES"
#define T_FECHA_PARENTESES "FECHA_PARENTESES"
#define T_ID "IDENTIFICADOR"
#define T_INT "TIPO_INT"
#define T_BOOL "TIPO_BOOL"
#define T_DOUBLE "TIPO_DOUBLE"
#define T_VOID "TIPO_VOID"
#define TIPO "TIPO"
#define DEC_ARGUMENTOS "DECLARA_ARGUMENTOS"
#define BLOCO_FUNCAO "BLOCO_DE_FUNCAO"
#define T_VIRGULA "VIRGULA"
#define T_ABRE_CHAVES "ABRE_CHAVES"
#define T_FECHA_CHAVES "FECHA_CHAVES"
#define CONTEUDO_BLOCO_FUNCAO "CONTEUDO_BLOCO_FUNCAO"
#define PALAVRA_RESERVADA "PALAVRA_RESERVADA"
#define T_WHILE "WHILE_STATEMENT"
#define T_IF "IF_STATEMENT"
#define T_ELSE "ELSE_STATEMENT"
#define T_RETURN "RETURN_STATEMENT"
#define T_INTEIRO "LITERAL_INTEIRO"
#define T_PONTO_FLUTUANTE "LITERAL_DOUBLE"
#define T_STRING "LITERAL_STRING"
#define T_BOOL_LITERAL "BOOL_LITERAL"
#define T_OP_INCREMENTO "INCREMENTO"
#define T_OPERADOR_RELACIONAL "OPERADOR_RELACIONAL"
#define T_OP_ARITMETICO "OPERADOR_ARITMETICO"
#define T_OP_BOOLEANO "OPERADOR_BOOLEANO"
#define T_ATRIBUICAO "ATRIBUICAO"
#define T_VIRGULA "VIRGULA"
#define T_PONTO_VIRGULA "PONTO_VIRGULA"


char* transforma(char str[]);
void AddTokenFromLinha(char *linha);

void eat(char* token_esperado);
Token GetCurrentToken();
void AdvanceToken();
int ehFinal();
void throwSyntaxError(Token erro, char* mensagem);
void AddStartToSyntaxTree(char* tokenName);
void AddEndToSyntaxTree(char* tokenName);
void AddLexemaToSyntaxTree(Token token);

Token* AddToTokenList(char *tokenName, char *tokenLexema, int linha, int coluna);
Token TokenFromLinha(char *linha);
int tokenEh(Token t, char* tokenName);
int aceitaTerminais(Token token, char *terminaisAceitos[], int numeroDeTerminais);




//---------------- FUNCOES DOS NAO TERMINAIS
void compilaDeclararFuncao();
void compilaDecTipo();
void compilaTipo();
void compilaDecArgumentos();

void compilaBlocoFunc();
void compilaConteudoDeFuncao();

void teste1(){
    printf("Iniciando teste.");
    AddToTokenList("TIPO_INT", "int", 1, 1);
    AddToTokenList("IDENTIFICADOR", "main", 1, 5);
    AddToTokenList("ABRE_PARENTESES","(",1,9);
    AddToTokenList("FECHA_PARENTESES",")",1,10);
    AddToTokenList("ABRE_CHAVES","{",1,12);
    AddToTokenList("PALAVRA_RESERVADA","return",2,5);
    AddToTokenList("INTEIRO","0",2,12);
    AddToTokenList("PONTO_VIRGULA",";",2,13);
    AddToTokenList("FECHA_CHAVES","}",3,1);
}

void teste2(){
    printf("Iniciando teste.");
    AddToTokenList("TIPO_INT", "int", 1, 1);
    AddToTokenList("IDENTIFICADOR", "main", 1, 5);
    AddToTokenList("ABRE_PARENTESES","(",1,9);
    AddToTokenList("TIPO_INT", "int", 99,99);
    AddToTokenList("IDENTIFICADOR", "a", 99,99);

    AddToTokenList("TIPO_INT", "int", 99,99);
    AddToTokenList("IDENTIFICADOR", "a", 99,99);
    AddToTokenList("FECHA_PARENTESES",")",1,10);
    AddToTokenList("ABRE_CHAVES","{",1,12);
    AddToTokenList("PALAVRA_RESERVADA","return",2,5);
    AddToTokenList("INTEIRO","0",2,12);
    AddToTokenList("PONTO_VIRGULA",";",2,13);
    AddToTokenList("FECHA_CHAVES","}",3,1);

	
}

void readlines(char *str){
  char *p, *temp;
  p = strtok_r(str, "\n", &temp);
  do {
      AddTokenFromLinha(p);
  } while ((p = strtok_r(NULL, "\n", &temp)) != NULL);
}

void testeLeitura(){
    
    
}


int analyse(int argc, char **argv) {
    AdvanceToken();
    printf("Começando a analise.\n");
    compilaDeclararFuncao(); // Sempre começa com a declaração da função main.
    if(!ehFinal()){
        throwSyntaxError(GetCurrentToken(), "Ainda há tokens a analisar.");
    }
    printf("\nAnalise Completa. Essa sequencia de tokens respeita a Gramatica.\n");


}

int main(int argc, char **argv)
{
    char str[202400]; 
    int c;
    int i = 0; 
    while ((c = getchar()) != EOF)
        str[i++] = c;

    printf("%s\n", str);

	readlines(str);
    analyse(argc, argv);

    return 0;
}



void compilaDeclararFuncao(){
    AddStartToSyntaxTree(DEC_FUNCAO);
    compilaDecTipo();
    eat(T_ABRE_PARENTESES); 
    compilaDecArgumentos();
    eat(T_FECHA_PARENTESES);
    compilaBlocoFunc();
    AddEndToSyntaxTree(DEC_FUNCAO);
}

void compilaDecTipo(){
    compilaTipo();
    eat(T_ID);
}


void compilaTipo(){
    AddStartToSyntaxTree(TIPO);
    Token token = GetCurrentToken();

    char *primeiros[4] = {T_INT, T_BOOL, T_DOUBLE, T_VOID};
    int i;
    int rejeitado = aceitaTerminais(token, primeiros, 4);

    if(rejeitado==1) // Tokem não é um dos terminais.
    {
        throwSyntaxError(token, "COMPILA_TIPO");
    }
    AddEndToSyntaxTree(TIPO);
}

void compilaDecArgumentos(){
    AddStartToSyntaxTree(DEC_ARGUMENTOS);

    if(tokenEh(GetCurrentToken(), T_FECHA_PARENTESES)) {// não há mais argumentos;
        AddEndToSyntaxTree(DEC_ARGUMENTOS);
        return;
    } else { 
        compilaDecTipo(); // declaro um tipo
        while(!tokenEh(GetCurrentToken(), T_FECHA_PARENTESES))
        {
            eat(T_VIRGULA);
            compilaDecTipo();
        }
        AddEndToSyntaxTree(DEC_ARGUMENTOS);
        return;
    }
}

void compilaBlocoFunc(){
    printf("\nToken atual: %s", GetCurrentToken().tokenName);
    AddStartToSyntaxTree(BLOCO_FUNCAO);
    eat(T_ABRE_CHAVES);
    compilaConteudoDeFuncao();
    eat(T_FECHA_CHAVES);
    AddEndToSyntaxTree(BLOCO_FUNCAO);
}

// STUB. ACEITA TUDO ATÈ UM }
void compilaConteudoDeFuncao() {
    Token token = GetCurrentToken();
    AddStartToSyntaxTree(CONTEUDO_BLOCO_FUNCAO);
    while (!tokenEh(GetCurrentToken(), T_FECHA_CHAVES))
    {
        AdvanceToken();
    }
    if(tokenEh(token, T_FECHA_CHAVES)){

       AddEndToSyntaxTree(CONTEUDO_BLOCO_FUNCAO);
    }


}
// Retorna 0 e consome o token, se ele está na lista de terminais aceitos,
// senão retorna 1.
int aceitaTerminais(Token token, char *terminaisAceitos[], int numeroDeTerminais){
    int i;   
    for(i=0; i<numeroDeTerminais; i++){
        if(tokenEh(token, terminaisAceitos[i]))
        {
            eat(terminaisAceitos[i]);
            return 0;
        }
    }
    return 1;
}
void eat(char* token_esperado)
{
    Token token = GetCurrentToken();
    if(tokenEh(token, token_esperado)) {
        AddStartToSyntaxTree(token.tokenName);
        AddLexemaToSyntaxTree(token);
        AddEndToSyntaxTree(token.tokenName);
        AdvanceToken();
    }

    else {
        printf("ERRO: Token esperado: %s\n", token_esperado);
        throwSyntaxError(token, "");
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


void throwSyntaxError(Token erro, char *mensagem){
	fprintf(stderr, "%s\n", mensagem );
    fprintf(stderr, "Linguagem nao aceita. Erro no token %s(%s) na linha %d col %d\n", 
												erro.tokenName, 
												erro.lexema, 
												erro.linha, 
												erro.coluna);
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




char* transforma(char str[]){
   char resultado[80] = "";
   char *token;
   char s[2] = "@";

   token = strtok(str, s);


     if(!strcmp(token,"PALAVRA_RESERVADA")){
    	token = strtok(NULL, s);
    	if(!strcmp(token,"int")){
			strcat(resultado, T_INT);
    		strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	}else if(!strcmp(token,"while")){
    		strcat(resultado,T_WHILE);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	}else if(!strcmp(token,"if")){
    		strcat(resultado,T_IF);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	}else if(!strcmp(token,"else")){
    		strcat(resultado,T_ELSE);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	}else if(!strcmp(token,"return")){
    		strcat(resultado,T_RETURN);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	}else if(!strcmp(token,"bool")){
    		strcat(resultado,T_BOOL);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	}else if(!strcmp(token,"double")){
    		strcat(resultado,T_DOUBLE);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	}else if(!strcmp(token,"void")){
    		strcat(resultado,T_VOID);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	}
     }else if(!strcmp(token,"INTEIRO")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_INTEIRO);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"PONTO_FLUTUANTE")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_PONTO_FLUTUANTE);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"STRING")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_STRING);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"BOOL")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_BOOL_LITERAL);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"IDENTIFICADOR")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_ID);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"PONTO_VIRGULA")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_PONTO_VIRGULA);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"ABRE_PARENTESES")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_ABRE_PARENTESES);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"FECHA_PARENTESES")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_FECHA_PARENTESES);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"ABRE_CHAVES")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_ABRE_CHAVES);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"FECHA_CHAVES")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_FECHA_CHAVES);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"VIRGULA")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_VIRGULA);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"ATRIBUICAO")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_ATRIBUICAO);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"OPERADOR")){
	     token = strtok(NULL, s);
	    	if(!strcmp(token,"&&")||!strcmp(token,"||")){
	    		strcat(resultado,T_OP_BOOLEANO);
				strcat(resultado,"@");
	    		strcat(resultado,token);
	    		strcat(resultado,"@");
	    		token = strtok(NULL, s);
	    		strcat(resultado,token);
	    		strcat(resultado,"@");
	    		token = strtok(NULL, s);
	    		strcat(resultado,token);
	    		strcat(resultado,"@");
	    		printf("%s\n", resultado );
	    	}else if(!strcmp(token,"+")||!strcmp(token,"-")||!strcmp(token,"*")||!strcmp(token,"/")||!strcmp(token,"%")){
	    		strcat(resultado,T_OP_ARITMETICO);
				strcat(resultado,"@");
	    		strcat(resultado,token);
	    		strcat(resultado,"@");
	    		token = strtok(NULL, s);
	    		strcat(resultado,token);
	    		strcat(resultado,"@");
	    		token = strtok(NULL, s);
	    		strcat(resultado,token);
	    		strcat(resultado,"@");
	    		printf("%s\n", resultado );
	    	}
     }else if(!strcmp(token,"OPERADOR_RELACIONAL")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_OPERADOR_RELACIONAL);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else if(!strcmp(token,"INCREMENTO")){
     	token = strtok(NULL, s);
    		strcat(resultado,T_OP_INCREMENTO);
			strcat(resultado,"@");
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		token = strtok(NULL, s);
    		strcat(resultado,token);
    		strcat(resultado,"@");
    		printf("%s\n", resultado );
    	
     }else{
      printf( " else\n");

     }
     //printf("Transformação finalizada.\n");
     char* resposta = (char *) malloc(255);
	 //printf(" Retornando...");
     strcpy(resposta, resultado);
	 //printf(" Resposta >> %s <<", resposta);
    return resposta;
	
}


void AddTokenFromLinha(char *linha){
    printf("Processando linha %s -> ", linha);
	Token *tok = malloc(sizeof(Token));

    char original[255];
    strcpy(original, linha);
	char line[255];
	strcpy(line, transforma(original));

 //   printf("Linha %s add: %p\nLine: %s add: %p\n", linha, linha, line, line);
    char separador[2] = "@";
    char *nome = strtok(line, separador);
    char *lex = strtok(NULL, separador);
    char *clinha = strtok(NULL, separador);
    char *coluna = strtok(NULL, separador);
 //   printf("\n%s - %s - %s - %s\n", nome, lex, clinha,coluna);
    int numeroL = atoi(clinha);
    int numeroC = atoi(coluna);
 //   printf("\n%s - %s - %d - %d\n", nome, lex, numeroL,numeroC);

    strcpy(tok->tokenName, nome);
    strcpy(tok->lexema, lex);
    tok->linha = numeroL;
    tok->coluna = numeroC;

	printf("Adicionado token %s %s %d %d\n", nome, lex, numeroL, numeroC);
    listaDeTokens[lastToken++] = *tok;
}