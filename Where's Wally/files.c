#include <stdio.h>

int main()
{
  FILE *file;
  file = fopen("teste.txt", "w");
  /* A função fopen passa o endereco de mem para o ponteiro.
  Precisam ser passados 2 argumetos:
  1- Diretório do meu arquivo(no windows trocando"\" por "\\") ou nomedoarquivo.tipo;
  2- "r" - Ler arquivo.
     "w" - Escrever no arquivo.
     "a" - anexar algo ao arquivo.
  */
  fprintf(file, "Apenas um teste");
  /*
  Função para printar no arquivo.
  possíveis passagens de argumentos:
  1- fprintf(ponteirodoarquivo, "mensagem");
  2- fprintf(ponteirodoarquivo, "tipo de variavel", variaveis);
  ex: fprintf(file, "%d:%s\n", x, palavra);
  */
  fclose(file);
  /*Por prevenção é sugerido utilizar o fclose para limpar a memoria reservada
  para criação do nomedoarquivo*/

  return 0;
}
//-------------------------------------------------------------------------------------------
#include <stdio.h>

int main()
{
  FILE *file;
  file = fopen("teste.txt", "r");

  int x,y,z;

  if(file == NULL) // = se o ponteiro file apontar para um endereço nulo
  {
    printf("Arquivo não pôde ser Aberto\n");
  }
  //esse if serve para o controle caso o arquivo não exista;

  fscanf(file,"%d %d %d", &x, &y, &z);
  /*
  Função para Ler dados de um arquivo já existente;
  3 argumentos:
  fscanf(ponteirodoarquivo,"tipo de dado",variáveis);

  */

  printf("%d %d %d\n", x, y, z);

  fclose(file);

  return 0;
}
//-------------------------------------------------------------------------------------------
#include <stdio.h>

int main()
{
  FILE *file;
  file = fopen("teste.txt", "r");

  if(file == NULL)
  {
    printf("Não foi possível abrir o arquivo\n");

  }

  char frase[100];
//ex: fgets(variavel(%s),tamanho,ponteirodoarquivo)
  while(fgets(frase, 100, file) != NULL)
  {
    printf("%s",frase);
  }
  /*
  fgets é uma função gets para arquivos.
  serve para armazenar string - mais apropriado p/ quando n se sabe exatamente a
  formatação do arquivo.
  pode ser usado a função fscanf, porém é mais apropriada p/ quando se sabe a
  formatação e quando se tem diferentes tipos de variaveis no mesmo arquivo.
  */
  fgets(variavel, tamanho, ponteirodoarquivo);

  printf("\n");

  fclose(file);

  return 0;
}
//-------------------------------------------------------------------------------------------

#include <stdio.h>

int main()
{
  FILE *file;
  file = fopen("teste.txt", "a");

  if(file == NULL)
  {
    printf("Não foi possível abrir o arquivo\n");

  }
  fprintf(); //apenas adiciona algo ao arquivo(não apaga anterior);


  fclose(file);

  return 0;
}
//-------------------------------------------------------------------------------------------
//função stdin: funciona como especie de arquivo de dados direto do teclado
#include <stdio.h>

int main()
{
  char x[100];

  fgets(x,100,stdin);

  return 0;
}

//-------------------------------------------------------------------------------------------
//Funcoes comuns:

fscanf(ponteirodoarquivo,"tipo de dado",variáveis);
//Ler dados de um arquivo já existente
fprintf(ponteirodoarquivo, "mensagem");
fprintf(ponteirodoarquivo, "tipo de variavel", variaveis);
//printar dados em um arquivo
fgets(variavel, tamanho, ponteirodoarquivo);
//Ler strings-similar a fscanf
fputs(variavel,ponteirodoarquivo);
//printar strings-similar a fprintf
fputc(variavel,ponteirodoarquivo);
//adiciona um char ao arquivo
fgetc(ponteirodoarquivo);
//lê o caractere da primeira posicao do arquivo
string.h:
strcmp() - comparar
#include <stdio.h>
#include <string.h>

int main () {
   char str1[15];
   char str2[15];
   int ret;


   strcpy(str1, "abcdef");
   strcpy(str2, "ABCDEF");

   ret = strcmp(str1, str2);

   if(ret < 0) {
      printf("str1 is less than str2");
   } else if(ret > 0) {
      printf("str2 is less than str1");
   } else {
      printf("str1 is equal to str2");
   }

   return(0);
}
strcpy(dest, mensagem/variavelorig)-
