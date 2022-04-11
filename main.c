#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(void) {
  int option;
  Lista lista = iniciarLista();


  do {
    printf("\n");
    printf("\n");
    printf("\n");
    printf(" ______            __                              __   \n");
    printf("|   __ |.-----..--|  |.-----..--.--..-----..-----.|  |_ \n");
    printf("|    __/|  _  ||  _  ||  _  ||  |  ||  -__||__ --||   _|\n");
    printf("|___|   |_____||_____||__   ||_____||_____||_____||____|\n");
    printf("                         |__|                           \n");
    printf("\n");
    printf("\n");
    printf("\n");

    printf(" 1 - Tocar\n 2 - Próximo\n 3 - Adicionar\n 4 - Remover\n 5 - Shuffle\n 6 - Exibir playlist\n 0 - Sair\n  Opção: ");

    scanf("%d", &option);

    switch(option) {
      case 0:
        printf("\nSee you space cowboy...");
        break;
      case 1:
        exibirAtual(lista);
        break;
      case 2:
        exibirProximo(lista);
        break;
      case 3:
        adicionar(lista);
        break;
      case 4:
        remover(lista);
        break;
      case 5:
        shuffle(lista);
        break;
      case 6:
        exibirLista(lista);
        break;
      default:
        printf("\nDificuldade cognitiva? não se preocupe, tenho todo o tempo do mundo... tente novamente\n");
        break;
    }
  } while (option != 0);
  return 0;
}