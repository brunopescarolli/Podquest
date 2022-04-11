

typedef struct CPodcast {
  char nome[64];
  int id;
} CPodcast;

typedef CPodcast Podcast;

typedef struct Episodio {
  Podcast podcast;

  char nome[64];
  int id;
  char arrPalavraChave[];
} Episodio;

typedef struct Celula {
  struct Celula * proximo;
  struct Celula * anterior;

  Episodio * episodio;
} Celula;

typedef struct Cabeca {
  Celula * atual;
  Celula * inicio;
  Celula * fim;
  Podcast podcasts[16];
  int shuffle;

} Cabeca;
typedef Cabeca * Lista;

void adicionar(Lista lista);

void remover(Lista lista);

void exibirAtual(Lista lista);

void shuffle(Lista lista);

void exibirProximo(Lista lista);

void exibirRelatorio(Lista lista);

int procurarPodcast(Lista lista, int idPodcast);

Lista iniciarLista();

void remove_newline_ch(char *line);

void exibirLista(Lista lista);

void exibirPodcasts(Lista lista);

void resetar(Lista lista);

void exibirLista(Lista lista);