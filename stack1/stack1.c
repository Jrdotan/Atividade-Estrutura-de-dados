#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sds.h> // biblioteca pra strings dinâmicas (segura)
#include <string.h> // apesar de eu usar isso para algumas funções, não é uma biblioteca segura.

/* sistema para registrar carros estacionados com o uso de pilha de memória
 - Patrocinado por: Melhor aula de sábado*/

#define TRUE 0
#define FALSE 1
#define Max_Len 150
#define Max_Vac 10

typedef struct // Estrutura para receber dados de carro
{

  sds placa;
  sds modelo;
  int ano;
  

}Carro;

  void Get_flush() //Função que limpa o input de newlines
{
   int c;
    while ((c = getchar()) != '\n' && c != EOF);  
}


typedef struct //Estrutura para criar a pilha e apontar para o topo da mesma
{
  Carro Cars[Max_Vac];
  int top;
}Pilha;


void inicializar(Pilha *Stk, Carro *cars) //inicializa valor de todos os carros antes de estacionar
{

 


  Stk->top = -1;
  
  //inicializa variaveis e strings utilizando strings dinâmicas
  for(int i = 0; i<Max_Vac; i++){
   Stk->Cars[i].ano = 0;
    Stk->Cars[i].placa = sdsnewlen("AAA0000", 7);
    Stk->Cars[i].modelo = sdsnewlen("AAA0000", 7);
}
}
    
  





int Pilha_Vazia(Pilha *Stk) //checa se a pilha está vazia
{
  
  return Stk->top == -1;
}

int Pilha_Cheia(Pilha *Stk) //checa se a pilha está cheia
{
  return Stk->top == Max_Vac - 1;
}

int quantidade_vagas(Pilha *Stk) //Retorna a quantidade de vagas restando para estacionar carros
{
 int Vacs = 0;
   if (Pilha_Vazia(Stk)) {
        return Max_Vac; 
    }


  for (int i = 0; i<Max_Vac; i++) {
    if (Stk->Cars[i].ano == 0) {
      Vacs++;  

    }
    
  }

  return Vacs;
}

void imprime_pilha(Pilha *Stk) //Imprime dados dos carros estacionados no momento
{

  printf("=====================§\n");
  for(int i=0; i<Max_Vac; i++)
  {
 if(Stk->Cars[i].ano != 0){
    printf("Placa: %s\n", Stk->Cars[i].placa);
    printf("Modelo: %s\n",  Stk->Cars[i].modelo);
    printf("Ano: %d\n",  Stk->Cars[i].ano);


    printf("\n");
    }
  }
printf("=====================§\n");

 
}


  
void Libera_Carro(Pilha *Stk) //Libera memória alocada em carros 
{
    for (int i = 0; i < Max_Vac; i++) {
        if (Stk->Cars[i].modelo != NULL) {
            sdsfree(Stk->Cars[i].placa);
            sdsfree(Stk->Cars[i].modelo);
        }
    }
}





void estacionar(Pilha *Stk, Carro *Car, int Vacs) //Estaciona novos carros

{

 

  if(Pilha_Cheia(Stk))
  {
    printf("Pilha cheia cumpadre, aperte ENTER pra continuar\n");

    return;
  }

     // checa se variaveis da pilha tem valores nelas e limpa
    if (Stk->Cars[Stk->top+1].placa != NULL) {
        sdsfree(Stk->Cars[Stk->top+1].placa);
    }
    if (Stk->Cars[Stk->top+1].modelo != NULL) {
        sdsfree(Stk->Cars[Stk->top+1].modelo);
    }
  
  
  Car->placa = sdsnewlen("", Max_Len - 1);
  Car->modelo = sdsnewlen("", Max_Len - 1);
  if(Car->placa == NULL ||  Car->modelo == NULL){
    printf("memory couldnt be allocated\n");
    exit(FALSE);
  }
 
  printf("\nInforme a placa do veículo: \n");
  fgets(Car->placa,Max_Len - 1, stdin);
  Car->placa[strcspn(Car->placa, "\n")] = '\0';
  
  

  printf("\nInforme o nome do modelo do veículo: \n");
  fgets(Car->modelo, Max_Len - 1, stdin);
  Car->modelo[strcspn(Car->modelo, "\n")] = '\0';

  
  printf("Informe o ano de origem do veículo: \n");
  scanf("\n%d", &Car->ano);





  
    printf("Carro de placa %s, modelo %s, ano %d foi estacionado com sucesso!\n", Car->placa, Car->modelo, Car->ano);
  Stk->top++;

   Stk->Cars[Stk->top] = *Car; 

   //Imprime pilha e quantidade de vagas restantes após inserir novo carro
  imprime_pilha(Stk); 
  Vacs = quantidade_vagas(Stk);

  printf("Vagas restantes: %d\n", Vacs);

 
  




}

Carro Carro_sair(Pilha *Stk, Carro *Car ) // registra saída de veículos
{
  int Vacs;
  Carro Temp_car;
    if(Pilha_Vazia(Stk))
  {


    printf("Pilha vazia\n");
    return (Carro) {"XXX000", "XXX000", 0};
    
  }
  
 printf("Carro de placa %s, modelo %s, ano %d Saiu!\n", Stk->Cars[Stk->top].placa, Stk->Cars[Stk->top].modelo,Stk->Cars[Stk->top].ano);

  if (Stk->Cars[Stk->top].placa != NULL) {
    sdsfree(Stk->Cars[Stk->top].placa);
  }
  if (Stk->Cars[Stk->top].modelo != NULL) {
    sdsfree(Stk->Cars[Stk->top].modelo);
  }



 
  Stk->Cars[Stk->top].placa = sdsnewlen("XXX0000", 7);
  Stk->Cars[Stk->top].modelo = sdsnewlen("XXX0000", 7);
  Stk->Cars[Stk->top].ano = 0;
  Stk->top--;

  if(Pilha_Vazia(Stk))
  {


    printf("Pilha vazia\n");
    return (Carro) {"XXX000", "XXX000", 0};
    
  }
  
 
  

 //Imprime pilha e quantidade de vagas restantes após retirar carro 
  imprime_pilha(Stk);

   Vacs = quantidade_vagas(Stk);

  printf("Vagas restantes: %d\n", Vacs);


 Temp_car = Stk->Cars[Stk->top];
  
  
 
  


  

  return Temp_car;
}


void imprime_tudo(Pilha *Stk) //Imprime valores de todos os espaços inicializados, com ou sem carros
{

  printf("=====================§\n");
  for(int i=0; i<Max_Vac; i++)
  {
    printf("Sign: %s\n", Stk->Cars[i].placa);
    printf("Model: %s\n",  Stk->Cars[i].modelo);
    printf("Year: %d\n",  Stk->Cars[i].ano);


    printf("\n"); 
  }
printf("=====================§\n");

  printf("thats all folks\n");
}

  


int main(int argc, char *argv[])
{
  
  char choose;
  
  Pilha Stk;
  
  Carro Car;
  int i = 0;


inicializar(&Stk, &Car); //chama função que inicializa pilha


  /* Loop principal, pode estacionar, registrar saída ou 
   * Imprimir todos os valores dos carros registrados. loop continua até usúario apertar ESC*/
  do
  {
  printf("digite 'a' para estacionar veículo, 'b' para retirar veículo, 'c' para imprimir todas as vagas e ESC 2x para sair\n");
  scanf("%c", &choose);

  switch (choose){ 
  
    case 'a':
        Get_flush();
      estacionar(&Stk, &Car, i);
     
      
    break;

    case 'b':
      Carro_sair(&Stk,&Car);
         

      break;

    case 'c':

      imprime_tudo(&Stk);

      break;

   default:
      printf("Input invalido, aperte ENTER pra continuar\n");
      
    break;
    }
  
  
  }while((getchar())!=27);

  
 Libera_Carro(&Stk); // chama a função para liberar memória
  
  return EXIT_SUCCESS;
}
