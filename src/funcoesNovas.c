void imprimeToken(informacoes token);
void setTokenValue(informacoes* info, char* newValue);
void setLexemaValue(informacoes* info, char* newLexema);
void setLinhaValue(informacoes* info, int newLineNumber);
void setColunaValue(informacoes* info, int colunaValue);
void quebrarLinha(informacoes* info);
void appendToLexema(informacoes *token, char aAnexar);
void incrementaColuna(informacoes* info);


#typedef ESTADO_FINAL 19;
#typedef ESTADO_ERRO 20;



// Funcao a ser implementada para mudar o estado.
void mudaEstado(int novoEstado);






// IMPLEMENTACAO



void estadoFinal (char ignorado, informacoes *token)
{
    printf("Iniciando estado final.");
    imprimeToken(*token);    
}


int  append(char*s, size_t size, char c) {
     if(strlen(s) + 1 >= size) {
         printf ("Erro no tamanho do lexema.");
          return 1;
     }
     int len = strlen(s);
     s[len] = c;
     s[len+1] = '\0';
     return 0;
}

void appendToLexema(informacoes *token, char aAnexar)
{
    // Criar uma maneira de "adicionar" o caractere ao lexema.
    // Essa não funciona direito.
   // printf("Appending to lekema: %c" , aAnexar);
    size_t currentLexemaSize = token->lexema_size;
    token->lexema_size++;
    append(token->lexema, currentLexemaSize, aAnexar);
}


void imprimeToken(informacoes token){
    printf("%s @ %s @ %d @ %d\n", token.token, token.lexema,
                             token.linha, token.coluna);
}

void setTokenValue(informacoes* info, char* newValue)
{
    strcpy(info->token, newValue);
}

void setLexemaValue(informacoes* info, char* newLexema)
{
    strcpy(info->lexema, newLexema);
    info->lexema_size = strlen(info->lexema);
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

void incrementaColuna(informacoes* info)
{
    info->coluna = info->coluna + 1;
}


void mudaEstado(int novoEstado)
{
    estadoAtual = novoEstado;
}