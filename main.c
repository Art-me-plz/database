#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSIZEOFBASE 30

struct book
{
  long int id;
  char autors[20];
  char name[30];
  int allbooks;
  int availablebooks;
};

struct book database[MAXSIZEOFBASE]; /*здесь будет вся информация базы данных*/

int Number; /* Количество занятых элементов в массиве */

int menu();
void add (void);
void print (void);

int main(int argc, char const *argv[])
{
  Number = 0;
  int from_menu = menu();
  int num = 0;
  struct book* sp = calloc(1, sizeof(struct book));
  while(from_menu)
  {
    switch(from_menu)
    {
      case 1:
        add();
        from_menu = menu();
      break;
      case 3:
        print();
        from_menu = menu();
      break;
    }
  }
  return 0;
}

void add (void)
{
      if (Number == MAXSIZEOFBASE - 1)
      {
        fprintf(stderr, "u can't add one more book\n");
        return;
      }
      srand(time(NULL));
      database[Number].id = rand();
      printf("autors > ");
      scanf("%s", database[Number].autors);
      printf("name of a book > ");
      scanf("%s", database[Number].name);
      printf("The number of all this books > ");
      scanf("%d", &database[Number].allbooks);
      printf("The number of all available books (not more than all) > ");
      scanf("%d", &database[Number].availablebooks);
      Number ++;
  }

int menu()
{
  int menu;
  while(1)
  {
    puts("Menu");
    puts("1 - add");
    puts("2 - delite");
    puts("3 - list");
    puts("0 - to quite");
    char c = getchar();
    switch(c)
    {
      case '1': menu = 1; break;
      case '2': menu = 2; break;
      case '3': menu = 3; break;
      case '0': menu = 0; break;
      default: puts("Unknow simbol"); while (c != '\n') c = getchar(); continue;
    }
    while (c != '\n') c = getchar();
    break;
  }
  
  return menu;
}

void print( void ) {
    int i;

  printf(" N  id         Autors              Name of book            All   Available\n");
  for (i = 0; i < Number; i ++) {
    printf("%2d. %11ld %-20s %-30s %-5d %-5d\n", i + 1, database[i].id, database[i].autors, 
      database[i].name, database[Number].allbooks,
      database[Number].availablebooks); 
  }
}

