#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int debugar = 0;


typedef struct informacoes {
    char token[255]; 
    char lexema[255];
    int lexema_size;
    int linha;
    int coluna; 
    } informacoes;

void imprimeToken(informacoes token);
void imprimeEstado(char *retornoDoEstado, informacoes *token);

void imprimeEVolta(int caracteres, char *retornoDoEstado, informacoes *info);
void setTokenValue(informacoes* info, char* newValue);
void setLexemaValue(informacoes* info, char* newLexema);
void setLinhaValue(informacoes* info, int newLineNumber);
void setColunaValue(informacoes* info, int colunaValue);
void quebrarLinha(informacoes* info);
void appendToLexema(informacoes *token, char aAnexar);
void incrementarColunas(informacoes* info);
void limpaLexema(informacoes* info);


int conta_vetor (char vet[] );
void q0 (char ch, informacoes *token);
void q1 (char ch, informacoes *token);
void q2 (char ch, informacoes *token);
void q3 (char ch, informacoes *token);
void q4 (char ch, informacoes *token);
void q5 (char ch, informacoes *token);
void q6 (char ch, informacoes *token);
void q7 (char ch, informacoes *token);
void q8 (char ch, informacoes *token);
void q9 (char ch, informacoes *token); // ESTADO_INICIAL
void q10 (char analisado, informacoes *token); // FINAL OUTROS
void q11 (char ch, informacoes *token); // Final OPERADOR RELACIONAL
void q12 (char ch, informacoes *token); // Final OPERADOR
void q13 (char ch, informacoes *token);
void q14 (char ch, informacoes *token); // Final INTEIRO
void q15 (char ch, informacoes *token); // Final PONTO FLUTUANTE
void q16 (char ch, informacoes *token); // Final OPERADOR
void q17 (char ch, informacoes *token); // Final IDENTIFICADOR
void q18 (char ch, informacoes *token); // Final PONTO FLUTUANTE
void q19 (char ch, informacoes *token); // Estado = Final, ou proximo é relacional.

void estadoErro (char ignorado, informacoes *token); // Esse estado imprime uma mensagem de erro
void estadoFinal (char ignorado, informacoes *token); // Esse estado imprime o resultado obtido
void lancaErro(char errado, informacoes *token);

#define ESTADO_INICIAL 9
#define ESTADO_FINAL 20
#define ESTADO_ERRO 21

// Funcoes 
typedef void (* funcaoEstado)(char ch, informacoes *token);
funcaoEstado estados[] = { q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15, q16, q17, q18, q19, estadoFinal, estadoErro };
int estadoAtual;
void mudaEstado(int novoEstado);
void processaEspacoEmEstadoFinal(char espaco, char *retornoDoEstado, informacoes* info);
void consomeEspacos(char espaco, informacoes* tokens);
void analiseLexica(FILE *fp);    

char buffer[1024];
int bufferGravado = 0;
int bufferLido = 0; 


int main(int argc, char **argv) {
    
    estadoAtual = ESTADO_INICIAL;
    printf(" Iniciando operacao \n");
    char *fileDir;
    if(argc > 1)    { // Foi informado um caminho.
        fileDir = argv[1];
        if(isdigit(*fileDir))
        {
            debugar = 1;
            fileDir = "../Testes/teste1.jl";
        }
        if (argc>2)
        {
            debugar = 1;
        }
    }

            // não foi informado um arquivo,
    else{   // provavelmente estamos testando a aplicação
        fileDir = "../Testes/teste1.jl";
        //fileDir = "../Testes/testeAndre.txt";
    }
    
    FILE *file_pointer = fopen(fileDir, "rt");

    if(file_pointer == NULL){
        printf("Erro enquanto tentava ler o arquivo %s\n", fileDir);
        exit(1);
    }
    else{
        
        if(debugar) printf("Pronto para iniciar a análise lexica de %s", fileDir);
        analiseLexica(file_pointer);
    }
    
    return 0;
  
  

  return 0;
}


void analiseLexica(FILE *fp) { 
    
    if(fp == NULL){
        printf("Erro enquanto tentava ler o arquivo %s\n", fp);
        exit(1);
    }
    
    char ch;
    informacoes var;
    if(debugar) printf("Iniciando analise lexica\n");
    
    var.linha = 1;  // linhas são numeradas de 1 em diante.
    var.coluna = 1; // colunas são numeradas de 1 em diante.
    setTokenValue(&var, "NOVO_TOKEN"); // token no estado inicial.
    if(debugar) printf("Iniciando while\n");
   
   //  scanf("%d", &x);
    while((ch = fgetc(fp)) != EOF && bufferGravado < 1024)
    {
        // Executamos a função do Estado atual.
        // Exemplo: executamos q0(ch, var), ou q1(ch, var)
        // a função é definida pela variavel global estadoAtual;
        //printf("Chamado funcao de estados para o estado numero %d\n", estadoAtual);
        if(bufferGravado < 1020)
        {
            buffer[bufferGravado++] = ch;
        }
        
        if(bufferGravado >= 1020) // Vamos ler o buffer
        {
            while(bufferLido < bufferGravado)
            {
                if(debugar) printf("Analisando caractere '%c', no estado '%d'\n", buffer[bufferLido], estadoAtual);
                estados[estadoAtual](buffer[bufferLido++] , &var);
            }
            bufferLido = 0;
            bufferGravado = 0;
        }
        
    }
    // Se terminamos de ler o arquivo antes de esgotar o buffer
    if(bufferLido<bufferGravado)
    {
        while(bufferLido < bufferGravado)
            {
                if(debugar) printf("Analisando caractere '%c', no estado '%d'\n", buffer[bufferLido], estadoAtual);
               //f if(debugar) printf("\t Linha: '%d', Coluna '%d'\n", var.linha, var.coluna);
                estados[estadoAtual](buffer[bufferLido++] , &var);
            }
        bufferLido = 0;
        bufferGravado = 0;
    }
    if(debugar) printf("Linhas %d e Colunas %d\n" ,var.linha, var.coluna); 
    /**/
}



void q0 (char analisado,  informacoes *token) {
    printf("TODO: Implementar estado 0\n");
}

void q1 (char analisado,  informacoes *token) {
    printf("TODO: Implementar estado 1\n");
}

void q2 (char analisado,  informacoes *token) {
    //printf("Iniciando estado 2\n");
    estadoAtual = 10;
    
}

void q3 (char analisado,  informacoes *token) {
    printf("TODO: Implementar estado 3\n");
}

void q4  (char analisado,  informacoes *token) {
    printf("TODO: Implementar estado 4\n");
}

void q5  (char analisado,  informacoes *token) {
    printf("TODO: Implementar estado 5\n");
}

void q6  (char analisado,  informacoes *token) {
      if(isspace(analisado))
    {
        processaEspacoEmEstadoFinal(analisado, "PONTO_FLUTUANTE", token);
        return;
    }
    if(isdigit(analisado))
    {
        appendToLexema(token, analisado);
        mudaEstado(18);
    } else {
        imprimeEVolta(1, "PONTO_FLUTUANTE", token);
    }
}

void q7 (char analisado,  informacoes *token) {
    printf("TODO: Implementar estado 7\n");
}

void q8 (char analisado,  informacoes *token) {
    printf("TODO: Implementar estado 8\n");
}

// Estado Inicial
void q9 (char analisado,  informacoes *token) {
    //scanf("Continue");
    setTokenValue(token, "");
    setLexemaValue(token, "");
    if(isspace(analisado))    {
        consomeEspacos(analisado, token);
        return;
    }

    incrementarColunas(token);
    if(isalnum(analisado))    {
        appendToLexema(token, analisado);
        if(isalpha(analisado)) {
            mudaEstado(17);
        } else if(isdigit(analisado)) {
            mudaEstado(14);
        }
    } else {

        switch (analisado) {
            case '#':
                lancaErro(analisado, token);
                return;

            case ';': 
                setTokenValue(token, "PONTO_VIRGULA"); 
                mudaEstado(10);break;
            case '(': 
                setTokenValue(token, "ABRE_PARENTESES"); 
                mudaEstado(10);break;
            case ')': 
                setTokenValue(token, "FECHA_PARENTESES"); 
                mudaEstado(10);break;
            case '{': 
                setTokenValue(token, "ABRE_CHAVES");
                mudaEstado(10); break;
            case '}': 
                setTokenValue(token, "FECHA_CHAVES"); 
                mudaEstado(10); break;
            case ',': 
                setTokenValue(token, "VIRGULA"); 
                mudaEstado(10); break;
            case '-': 
                setTokenValue(token, "OPERADOR"); 
                mudaEstado(10); break;
            case '*': 
                setTokenValue(token, "OPERADOR");
                mudaEstado(10); break;
            case '/': 
                setTokenValue(token, "OPERADOR");
                mudaEstado(10); break;
            case '+': 
                setTokenValue(token, "OPERADOR");
                mudaEstado(16); break;
            case '=':
                setTokenValue(token, "ATRIBUIÇÃO"); 
                mudaEstado(19);
                break;
            case '>':
            case '<':
                setTokenValue(token, "OPERADOR_RELACIONAL");
                mudaEstado(11);
                break;
            case '.':
                setTokenValue(token, "PONTO_FLUTUANTE");
                mudaEstado(5);
                break;
        }
    

    } // TODO: Complementar.
}

void q10 (char ignorado, informacoes *token) {
    
    if(isspace(ignorado))
    {
        estadoFinal(ignorado, token);
    } else
    {
        imprimeEVolta(1, token->token, token);
        return;
    }
    
}


void q11 (char analisado,  informacoes *token) {
    // TODO: Implementar
}


void q12 (char analisado,  informacoes *token) {
    // TODO: Implementar
}


void q13 (char analisado,  informacoes *token) {
    // TODO: Implementar
}


void q14 (char analisado,  informacoes *token) {
    if(isspace(analisado))
    {
        setTokenValue(token, "INTEIRO");
        mudaEstado(9);
    } else if(isdigit(analisado)) {
        mudaEstado(14);
    } else if( analisado == '.') 
    {
        mudaEstado(15);
    } else {  
        imprimeEVolta(1, "INTEIRO", token);
        return;
    }
            
    appendToLexema(token, analisado);
}


void q15 (char analisado,  informacoes *token) {
    if(isspace(analisado))
    {
        processaEspacoEmEstadoFinal(analisado, "PONTO_FLUTUANTE", token);
        return;
    }
    if(isdigit(analisado))
    {
        appendToLexema(token, analisado);
        mudaEstado(18);
    } else {
        imprimeEVolta(1, "PONTO_FLUTUANTE", token);
    }
}


void q16 (char analisado,  informacoes *token) {
    // TODO: Implementar
}


void q17 (char analisado,  informacoes *token) {
   //    printf ("%c ", analisado);
    if(analisado == '('){
        imprimeEVolta(1, "IDENTIFICADOR", token);
        return;
    }
    if(analisado == '{'){
        imprimeEVolta(1, "ABRE_CHAVES", token);
        return;
        }

    if(isspace(analisado))     {
     //   printf("Q17 isSPACE \n");
        processaEspacoEmEstadoFinal(analisado, "IDENTIFICADOR", token);
        return;
    }

    incrementarColunas(token);
    if( isalnum(analisado) || analisado=='_' ) {
        mudaEstado(17);
        appendToLexema(token, analisado);
    } else {
        imprimeEVolta(1, "IDENTIFICADOR", token);
    }

    
    
}


void q18 (char analisado,  informacoes *token) {
    if(isspace(analisado))
    {
        processaEspacoEmEstadoFinal(analisado, "PONTO_FLUTUANTE", token);
        return;
    }
    if(isdigit(analisado))
    {
        appendToLexema(token, analisado);
        return;
    } 
    if(analisado=='e' || analisado=='E'){
        appendToLexema(token, analisado);
        mudaEstado(6);
        return;
    }
    imprimeEVolta(1, "PONTO_FLUTUANTE", token);
}

void q19 (char analisado,  informacoes *token) {
    if(isspace(analisado))     {
     //   printf("Q17 isSPACE \n");
        processaEspacoEmEstadoFinal(analisado, "ATRIBUIÇÃO", token);
        return;
    }
    if(analisado == '=')
    {
        appendToLexema(token, analisado);
        imprimeEstado("OPERADOR_RELACIONAL", token);
        mudaEstado(ESTADO_INICIAL);
    }
}
// Auxiliares

void estadoFinal (char ignorado, informacoes *token)
{
 //   printf("Iniciando estado final.");
    imprimeToken(*token);  
    mudaEstado(ESTADO_INICIAL);
      
}

void lancaErro(char errado, informacoes *token)
{
    informacoes erro;
    erro.linha = token->linha;
    erro.coluna = token->coluna;
    setLexemaValue(&erro, &errado);
    setTokenValue(&erro, "ERRO");
    if(debugar) {
        printf("Erro em Linha %d, Coluna %d, Token %s, Lexema %s.",
                erro.linha, erro.coluna, erro.lexema, erro.token);   
    }
    
    imprimeToken(erro);
    mudaEstado(ESTADO_INICIAL);    
}
void estadoErro (char ignorado, informacoes *token)
{
     if(debugar) {
        printf("Iniciando estado de erro.\n");   
    }
    imprimeToken(*token);
    lancaErro(ignorado, token);
}
int  append(char *s, size_t size, char c) {
    // printf("Adicionando '%c' - append\n", *s);
     if(strlen(s) + 1 >= size) {
         printf ("Erro no tamanho do lexema.\n");
          return 1;
     }
     int len = strlen(s);
     s[len] = c;
     s[len+1] = '\0';
     return 0;
}

void appendToLexema(informacoes *token, char aAnexar)
{
   //printf("Adicionando '%c' - appendToLexema\n", aAnexar);
    size_t currentLexemaSize = token->lexema_size;
    token->lexema_size++;
    append(token->lexema, token->lexema_size, aAnexar);
}


void imprimeToken(informacoes token){
    int linha = token.linha;
    int coluna = token.coluna - token.lexema_size + 1;

    printf("%s@%s@%d@%d\n", token.token, token.lexema,
                             linha, coluna);
}

void setTokenValue(informacoes* info, char* newValue)
{
    strcpy(info->token, newValue);
}

void setLexemaValue(informacoes* info, char* newLexema)
{
    strcpy(info->lexema, newLexema);
    info->lexema_size = strlen(newLexema)+1;
    //printf("Setando lexema = %s, tamanho %d\n", info->lexema, info->lexema_size);
}

void setLinhaValue(informacoes* info, int newLineNumber)
{
    info->linha = newLineNumber;
}

void setColunaValue(informacoes* info, int colunaValue)
{
    info->coluna = colunaValue;
}

void quebrarLinha(informacoes* info)
{ 
    info->linha = info->linha + 1;
    info->coluna = 0;
}

void incrementarColunas(informacoes* info)
{
    info->coluna = info->coluna + 1;
}




void mudaEstado(int novoEstado)
{
    if(debugar) printf("Indo do estado %d para %d ... ", estadoAtual, novoEstado);
    estadoAtual = novoEstado;
    if(debugar) printf("Estou no estado %d\n", estadoAtual);
    
}

void finalisaAnalise(char* tokenImpresso, informacoes* info)
{
    setTokenValue(info, tokenImpresso);
    mudaEstado(ESTADO_FINAL);
}

void consomeEspacos(char espaco, informacoes* tokens)
{
    if(espaco == '\n')     {
        quebrarLinha(tokens);
       
    } else {
        incrementarColunas(tokens);
    }
}

void imprimeEstado(char *retornoDoEstado, informacoes *token)
{
    setTokenValue(token, retornoDoEstado);
    imprimeToken(*token);
}
void processaEspacoEmEstadoFinal(char espaco, char *retornoDoEstado, informacoes* info)
{
    consomeEspacos(espaco, info);
    setTokenValue(info, retornoDoEstado);
    imprimeToken(*info);
    mudaEstado(ESTADO_INICIAL);

}

void imprimeEVolta(int retorno, char *retornoDoEstado, informacoes *info)
{
    
        setTokenValue(info, retornoDoEstado);
    imprimeToken(*info);
    bufferLido = bufferLido - retorno;
    if(debugar) printf("imprimeEVolta - proximo caractere a ler %c\n", buffer[bufferLido]);
    mudaEstado(ESTADO_INICIAL);
}
    