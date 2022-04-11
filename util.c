#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "util.h"

static int idPodcast = 1;


void inserePodcastNoFim(Lista lista, Podcast podcast) {
  for(int i = 0; i < sizeof(lista->podcasts)/sizeof(Podcast); i++) {
   if(lista->podcasts[i].id == -1) {
     lista->podcasts[i] = podcast;
     break;
   }
  }
}

Lista copiaLista(Lista lista) {
  Lista nova = iniciarLista(); 
  for(Celula * aux = lista->inicio; aux != NULL; aux = aux->proximo) {
    if(nova->inicio == NULL) {
      nova->inicio = aux;
      nova->fim = aux;
      nova->atual = aux;
    }
    else {
      nova->atual->proximo = aux;
      nova->atual = nova->atual->proximo;
    }
  }

  nova->atual = nova->inicio;
  return nova;
}

int procuraPodcast(Lista lista, Podcast * podcast) {
  int tamanho = sizeof(lista->podcasts) / sizeof(Podcast);
  for(int i = 0; i < tamanho; i++)  {
    if(lista->podcasts[i].nome == podcast->nome) {
      return i;
    }
  }
  return -1;
}

Celula * criaCelula(Lista lista) {
  Episodio * novoEp = malloc(sizeof(Episodio));
  Celula * nova = malloc(sizeof(Celula));
  Podcast podcast;
  
  printf("\nDigite o id do podcast, só para facilitar minha vida mesmo :) : ");
  scanf("%d", &novoEp->id);
  getchar();
  
  printf("\nDigite o nome do episódio: ");
  fgets(novoEp->nome, 64, stdin);
  remove_newline_ch(novoEp->nome);

  printf("\nDigite o nome do podcast: ");
  fgets(podcast.nome, 64, stdin);
  remove_newline_ch(podcast.nome);
  podcast.id = idPodcast;

  novoEp->podcast = podcast;

  nova->episodio = novoEp;

  return nova;
}



void resetar(Lista lista) { 
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->atual = NULL;
}

void resetarCelula(Celula * celula) {
  celula->anterior = NULL;
  celula->proximo = NULL;
}



void adicionar(Lista lista) {  
  Celula * nova = criaCelula(lista);
  int indicePodcast;

  indicePodcast = procuraPodcast(lista, &nova->episodio->podcast);

  if(indicePodcast == -1) {
    inserePodcastNoFim(lista, nova->episodio->podcast);
    idPodcast++;
  } else {
    nova->episodio->podcast = lista->podcasts[indicePodcast];
  }

  if(lista->inicio == NULL) {    
    lista->inicio = nova;
    lista->fim = nova;
    lista->atual = nova;

    nova->anterior = NULL;
    nova->proximo = NULL;


  } else {
    nova->anterior = lista->fim;
    nova->proximo = NULL;
    lista->fim->proximo = nova;
    lista->fim = nova;
  }
  int r = rand() % 3; 
  
  system("clear");
  
  switch(r){
    case 0:
      printf("\nGosto é gosto né, mesmo assim adicionei\n");
    break;
    case 1:
      printf("\nEsse até que é legalzinho, adicionado\n");
    break;
    case 2:
      printf("\nOra ora, vindo de você até me surpreendi pelo bom gosto, adicionado\n");
    break;
      
  }
  
}

void exibirAtual(Lista lista) {
  system("clear");
  if(lista->atual != NULL) {
    printf("Tocando3 episódio %s do podcast %s", lista->atual->episodio->nome, lista->atual->episodio->podcast.nome);
    
  }
  else {
    printf("\nVocê quer mesmo tocar nada? mesmo que queira muito, não é possível, adicione algo antes\n");
  }
}

void exibirProximo(Lista lista) {
  system("clear");
  Celula * aux = lista->atual;
  Episodio * ep;

  if(aux != NULL && aux->proximo != NULL) {
    if(lista->shuffle == 1) {
      if(aux->proximo->proximo != NULL) {
        lista->atual = lista->atual->proximo->proximo;
      }
      else if(aux->proximo == lista->fim) {
        lista->atual = lista->inicio;
      }
      else if(aux == lista->fim) {
        printf("\nSegundo os meus calculos... acho que acabou a fila\n");
        return;
      }
      ep = lista->atual->episodio;
  
      printf("Próximo: %d - %s (%s)", ep->id, ep->nome, ep->podcast.nome);
    }
    else {

      lista->atual = lista->atual->proximo;
      ep = lista->atual->episodio;
      printf("Próximo: %d - %s (%s)", ep->id, ep->nome, ep->podcast.nome);
      
    }
  }
  else {
    printf("\nSegundo os meus calculos... acho que acabou a fila\n");
  }

}

Lista iniciarLista() {
  Lista lista = malloc(sizeof(Lista));

  lista->atual = NULL;
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->shuffle = 0;

  for(int i = 0; i < sizeof(lista->podcasts)/sizeof(Podcast); i++) {
    Podcast pdc;
    pdc.id = -1;
    lista->podcasts[i] = pdc;
  }

  return lista;
}

void remove_newline_ch(char *line)
{
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}

void exibirLista(Lista lista) {
  system("clear");
  if(lista->inicio != NULL) {
    for(Celula * aux = lista->inicio; aux != NULL; aux=aux->proximo) {
      Episodio * ep = aux->episodio;
      Episodio * epAtual = lista->atual->episodio;

      if(ep->id == epAtual->id && ep->podcast.id == epAtual->podcast.id) {
      printf("%d - %s (%s) || Tocando agora\n", ep->id, ep->nome, ep->podcast.nome);
        
      }
      else {
      printf("%d - %s (%s)\n", ep->id, ep->nome, ep->podcast.nome);
        
      }
    }
  }
  else {
    printf("Não sou nenhum especialista, mas acho que está vazio");
  }
  
}

void remover(Lista lista) {
  system("clear");
  if(lista->inicio != NULL && lista->atual != NULL && lista->fim != NULL) {
    
    int idEpisodio, idPodcast;
    Celula * removido;
    printf("Digite o número do episódio: ");
    scanf("%d", &idEpisodio);
    getchar();
    printf("\nDigite o id do podcast: ");
    printf("\n");
    scanf("%d", &idPodcast);
    getchar();
    
      if(lista->inicio->proximo == NULL) {
        if(lista->inicio->episodio->id == idEpisodio && lista->inicio->episodio->podcast.id) {
          removido = lista->inicio;
          resetar(lista);
          printf("Episódio %d do podcast %s obliterado, me sinto até mais leve", removido->episodio->id, removido->episodio->podcast.nome);
          return;
        }
      }

      else {
        for(Celula * aux = lista->inicio; aux != NULL; aux = aux->proximo){
          if(lista->inicio->episodio->id == idEpisodio && lista->inicio->episodio->podcast.id == idPodcast) {
              removido = lista->inicio;
              lista->inicio = lista->inicio->proximo;
            if(lista->atual->episodio->id == idEpisodio && lista->atual->episodio->podcast.id == idPodcast ) {
              lista->atual = lista->atual->proximo;
            }
              printf("Episódio %d do podcast %s obliterado, me sinto até mais leve", removido->episodio->id, removido->episodio->podcast.nome);
              resetarCelula(removido);
            }
            
          else if(aux->proximo->episodio->id == idEpisodio && aux->proximo->episodio->podcast.id == idPodcast) {
            removido = aux->proximo;
            aux->proximo = aux->proximo->proximo;
            resetarCelula(removido);
            
            if(lista->atual->episodio->id == idEpisodio && lista->atual->episodio->podcast.id == idPodcast ) {
              lista->atual = lista->atual->proximo;
            }
            printf("Episódio %d do podcast %s obliterado, me sinto até mais leve", removido->episodio->id, removido->episodio->podcast.nome);
            resetarCelula(removido);
            return;
          }
        }
      }
    }
  else {
    printf("Corajoso da sua parte tentar remover algo vazio");
  }
  
}

void shuffle(Lista lista) {
  system("clear");
  if(lista->shuffle == 0) {
    lista->shuffle = 1;
    
    printf("Finalmente uma oportunidade de mostrar o que aprendi em vegas, ativei o shuffle");    
  }
  else {
    lista->shuffle = 0;

    printf("Odeio coisas ordenadas, mas ja que você insiste, shuffle desativado");
  }
}

void exibirPodcasts(Lista lista) {
  system("clear");
  for(int i = 0; i < sizeof(lista->podcasts)/sizeof(Podcast); i++) {
    Podcast podcast = lista->podcasts[i];

    if(podcast.id > 0 && podcast.id < 100) {
      printf("%d - %s\n", podcast.id, podcast.nome); 
      return;
    }
  }
  printf("Não sou nenhum especialista, mas acho que está vazio");
  
}
