#include <stdio.h>
#include <string.h>
typedef struct informacoes {
    char *token; 
    char *lexema;
    int lexema_size;
    int linha;
    int coluna; 
    } informacoes;

int conta_vetor (char vet[] );
void q0 (char ch, informacoes tokens);
void q1 (char ch, informacoes tokens);
void q2 (char ch, informacoes tokens);
void q3 (char ch, informacoes tokens);
void q4 (char ch, informacoes tokens);
void q5 (char ch, informacoes tokens);
void q6 (char ch, informacoes tokens);
void q7 (char ch, informacoes tokens);
void q8 (char ch, informacoes tokens);
void q9 (char ch, informacoes tokens);
void q10 (informacoes tokens);
void q11 (char ch, informacoes tokens);
void q12 (char ch, informacoes tokens);
void q13 (char ch, informacoes tokens);
void q14 (char ch, informacoes tokens);
void q15 (char ch, informacoes tokens);
void q16 (char ch, informacoes tokens);
void q17 (char ch, informacoes tokens);
void q18 (char ch, informacoes tokens);



int main(void) {
  informacoes var;
  
  
  var.token = "" ; 
  
  
  q9('"',var);

  return 0;
}

int conta_vetor (char vet[] ){
    int i=0;
    while(vet[i]){
        i++;
    }
    return i ; 
}
void q9 (char ch, informacoes tokens){
    char vet[255];
    int i ;
    char c = 'o';
    // if(ch == '?'){
    //     tokens.token = "?"; 
    //     q0('=',tokens);
    // }else if(ch == '#'){
    //     tokens.token = "#"; 
    //     q16('#',tokens);
        
    // }else if(ch == '|'){
    //   tokens.token = "|"; 
    //     q8('|',tokens);
    // }else if(ch == '@'){
    //   tokens.token = "@"; 
    //     q12(' ',tokens);
    // }else if(ch == '&'){
    //   tokens.token = "&"; 
    //     q3(' ',tokens);
    // }else if(ch == '='||ch == '>'||ch == '<'){
    //     vet[0] = ch;
    //     tokens.token = ""; 
    //     tokens.token = vet; 
    //     q11(' ',tokens);
    // }else if(ch == '/'||ch == '%'||ch == '['||ch == ']'||ch == '{'||ch == '}'||ch == ';'||ch == ','){
    //     vet[0] = ch;
    //     tokens.token = ""; 
    //     tokens.token = vet; 
    //     q10(tokens);
    // }else
     if(ch == '"'){
        tokens.token = "\""; 
        // q10(tokens);
        printf("estamos em q9:");
        scanf("%c",&c);
        q2(c,tokens);
    }
  
}

void q0 (char ch, informacoes tokens){
  char vet[255];
      int i ;
      if(ch == '='){
        strcpy(vet,tokens.token);
        // i =  conta_vetor(vet);
        strcat(vet, "=");
          tokens.token = ""; 
          tokens.token = vet; 
          q10(tokens);
      }

}
void q8 (char ch, informacoes tokens){
  char vet[255];
      int i ;
      if(ch == '|'){
        strcpy(vet,tokens.token);
        // i =  conta_vetor(vet);
        strcat(vet, "|");
          tokens.token = ""; 
          tokens.token = vet; 
          q10(tokens);
      }else{
      printf("erro carracrte: %c nao esperado",ch);
      }

}
void q16 (char ch, informacoes tokens){
  char vet[255];
      int i ;
      if(ch == '#'){
        strcpy(vet,tokens.token);
        // i =  conta_vetor(vet);
        strcat(vet, "#");
          tokens.token = ""; 
          tokens.token = vet; 
          q10(tokens);
      }else if(ch != ' '){
          q10(tokens);
      }else{
        printf("erro carracrte: %c nao esperado",ch);
      }
  }

void q12 (char ch, informacoes tokens){
  char vet[255];
      int i ;
      if(ch == '@'){
        strcpy(vet,tokens.token);
        // i =  conta_vetor(vet);
        strcat(vet, "@");
          tokens.token = ""; 
          tokens.token = vet; 
          q10(tokens);
      }else if(ch != ' '){
          q10(tokens);
      }else{
        printf("erro carracrte: %c nao esperado",ch);
      }

}
void q3 (char ch, informacoes tokens){
  char vet[255];
      int i ;
      if(ch == '&'){
        strcpy(vet,tokens.token);
        // i =  conta_vetor(vet);
        strcat(vet, "&");
          tokens.token = ""; 
          tokens.token = vet; 
          q10(tokens);
      }else if(ch == ' '){
        printf("espaço nao esperado");
      }else{
        printf("erro carracrte: %c nao esperado",ch);
      }

}
void q11 (char ch, informacoes tokens){
  char vet[255];
      int i ;
      if(ch == '='){
        strcpy(vet,tokens.token);
        // i =  conta_vetor(vet);
        strcat(vet, "=");
          tokens.token = ""; 
          tokens.token = vet; 
          q10(tokens);
      }else if(ch == ' '){
          q10(tokens);
      }else{
        printf("erro carracrte: %c nao esperado",ch);
      }

}
void q2 (char ch, informacoes tokens){
  char vet[255];
      int i ;
      char c;
      // if(ch == '\\'){
      //   strcpy(vet,tokens.token);
      //   i =  conta_vetor(vet);
      //   vet[i+1] = ch ;
      //   // strcat(vet, "=");
      //     tokens.token = ""; 
      //     tokens.token = vet; 
      //     q1('a',tokens);
      // }else
       if(ch !='\\'||ch != '\'' ){
        strcpy(vet,tokens.token);
        i =  conta_vetor(vet);
        vet[i] = ch ;
        tokens.token = ""; 
        tokens.token = vet;
        printf("estamos em q2:");
        scanf("%c",&c);
        // q7(c,tokens);
      }
      // else{
      //   printf("erro carracrte: %c nao esperado",ch);
      // }

}
void q1 (char ch, informacoes tokens){
  char vet[255];
      int i ;
      char c;
      if(ch !='\\'||ch != '\'' ){
        strcpy(vet,tokens.token);
        i =  conta_vetor(vet);
        vet[i] = ch ;
          tokens.token = ""; 
          tokens.token = vet; 
          printf("dentro de q1:");
           scanf("%c",&c);
          q7(c,tokens);
      }else{
        printf("erro carracrte: %c nao esperado",ch);
      }

}
void q7 (char ch, informacoes tokens){
  char vet[255];
      int i ;
      char c;
      printf("%c\n",ch);
       if(ch == '"'){
        strcpy(vet,tokens.token);
        i =  conta_vetor(vet);
        vet[i] = ch ;
          tokens.token = ""; 
          tokens.token = vet; 
          printf("dentro de q7 depois de \" \n ");
          q10(tokens);
      }else if(ch !='\\'||ch != '\''||ch != '"' ){
        strcpy(vet,tokens.token);
        i =  conta_vetor(vet);
        vet[i] = ch ;
        tokens.token = ""; 
        tokens.token = vet; 
        printf("estamos em q7 dentro de nao \\:");
      scanf("%c",&c);
        q7(c,tokens);
      }else if(ch == '\\'){
        strcpy(vet,tokens.token);
        i =  conta_vetor(vet);
        vet[i] = ch ;
          tokens.token = ""; 
          tokens.token = vet; 
          printf("dentro de q7 depois de \\ :");
           scanf("%c",&c);
          q1(c,tokens);
      }else{
        printf("erro carracrte: %c nao esperado",ch);
      }

}
void q10 ( informacoes tokens){

        printf("%s\n",tokens.token);

}
