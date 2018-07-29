#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void transforma(char str[]){
   char resultado[80] = "";
   char *token;
   char s[2] = "@";

   token = strtok(str, s);


     if(!strcmp(token,"PALAVRA_RESERVADA")){
    	token = strtok(NULL, s);
    	if(!strcmp(token,"int")){
    		strcat(resultado,"T_INT@");
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
    		strcat(resultado,"T_WHILE@");
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
    		strcat(resultado,"T_IF@");
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
    		strcat(resultado,"T_ELSE@");
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
    		strcat(resultado,"T_RETURN@");
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
    		strcat(resultado,"T_BOLL@");
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
    		strcat(resultado,"T_DOUBLE@");
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
    		strcat(resultado,"T_VOID@");
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
    		strcat(resultado,"T_INTEIRO@");
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
    		strcat(resultado,"T_PONTO_FLUTUANTE@");
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
    		strcat(resultado,"T_STRING@");
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
    		strcat(resultado,"T_BOOL_LITERAL@");
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
    		strcat(resultado,"T_ID@");
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
    		strcat(resultado,"T_PONTO_VIRGULA@");
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
    		strcat(resultado,"T_ABRE_PARENTESES@");
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
    		strcat(resultado,"T_FECHA_PARENTESES@");
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
    		strcat(resultado,"T_ABRE_CHAVES@");
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
    		strcat(resultado,"T_FECHA_CHAVES@");
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
    		strcat(resultado,"T_VIRGULA@");
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
    		strcat(resultado,"T_ATRIBUICAO@");
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
	    		strcat(resultado,"T_OP_BOOLEANO@");
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
	    		strcat(resultado,"T_OP_ARITMETICO@");
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
    		strcat(resultado,"T_OPERADOR_RELACIONAL@");
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
    		strcat(resultado,"T_OP_INCREMENTO@");
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
     
 
	
}


int main () {
   char str[80] = "PALAVRA_RESERVADA@int@1@1";
   char str1[80] = "IDENTIFICADOR@main@1@5";
   char str2[80] = "ABRE_PARENTESES@(@1@9";
   char str3[80] = "FECHA_PARENTESES@)@1@10";
   char str4[80] = "ABRE_CHAVES@{@1@12";
   char str5[80] = "PALAVRA_RESERVADA@return@2@5";
   char str6[80] = "INTEIRO@0@2@12";
   char str7[80] = "PONTO_VIRGULA@;@2@13";
   char str8[80] = "FECHA_CHAVES@}@3@1";


   transforma(str);
   transforma(str1);
   transforma(str2);
   transforma(str3);
   transforma(str4);
   transforma(str5);
   transforma(str6);
   transforma(str7);
   transforma(str8);
  
   
   return(0);
}