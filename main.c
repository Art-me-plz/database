#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSIZEOFBASE 30

struct book
{
  long long id;
  char autors[20];
  char name[30];
  int allbooks;
  int availablebooks;
};

struct book database[MAXSIZEOFBASE]; //здесь будет вся информация базы данных
int Number = 1; // Количество занятых элементов в массиве
FILE* books; 

int menu(void);
void add (void);
void Del(void);
void out (void);

int main(int argc, char const *argv[])
{
  int from_menu = 0;
  
  while(from_menu != 5)
  {
    out();
    from_menu = menu();
    switch(from_menu)
    {
      case 1:
        add();
      break;
      case 2:
        Del();
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
  srand(time(NULL)); // для индивидуального номера используем случайное число
  database[Number].id = rand();
  printf("Autors > ");
  scanf("%s", database[Number].autors);
  printf("Name of a book > ");
  scanf("%s", database[Number].name);
  printf("The number of all this books > ");
  scanf("%d", &database[Number].allbooks);
  printf("The number of all available books (not more than all) > ");
  scanf("%d", &database[Number].availablebooks);

  books = fopen("books.csv", "w"); // запишем все в файл для дальнейшей работы
  for (int x = 1; x <= Number; x++) {
    fprintf(books, "%lld;%s;%s;%d;%d\n", database[x].id, database[x].autors,
      database[x].name, database[x].allbooks, database[x].availablebooks);
  }
  fclose(books);
  Number ++;
  printf("successfully added\n");
}

int menu()
{
  int i = 0;
  printf("select action:\n");
  printf("1) Add new book\n");
  printf("2) Delete the book\n");
  printf("3) Edit the information\n");
  printf("4) Change the number of books in the library\n");
  printf("5) Save and exit\n");
  printf("\n");
  printf(">>>");
  scanf("%d", &i);
  return i;
}

void Del()
{
  int poisk = 0; // переменная для поиска номера в массиве всей базы
  long long iddel = 0; // id удаляемого компонента
  int nd = 0; // (number_of_delete) номер в массиве всей базы 

  out();

  books = fopen("books.csv", "w");
  while (poisk == 0) { // ищем номер в массиве всей базы
    printf("Enter the ID of the book you want to delete: ");
    scanf("%lld", &iddel);
    for (int k = 0; k < Number; k++) {
      if (iddel == database[k].id) {
        poisk = 1;
        nd = k;
      }
    }
    if (poisk == 0) {
      printf("book with this ID was not found\n");
    }
  }
  poisk = 0;
  for (int x = 1; x < nd; x++) { // записываем все элементы до удаляемого в файл
    fprintf(books, "%lld;%s;%s;%d;%d\n", database[x].id, database[x].autors, 
      database[x].name, database[x].allbooks, database[x].availablebooks);
  }
  for (nd; nd < Number; nd++) { // сдвигаем элементы массива после удаляемого на 1 ячейку назад и записываем в файл
    database[nd].id = database[nd + 1].id;
    strncpy(database[nd].autors, database[nd + 1].autors, 100);
    strncpy(database[nd].name, database[nd + 1].name, 100);
    database[nd].allbooks = database[nd + 1].allbooks;
    database[nd].availablebooks = database[nd + 1].availablebooks;
    fprintf(books, "%lld;%s;%s;%d;%d\n", database[nd].id, database[nd].autors,
      database[nd].name, database[nd].allbooks, database[nd].availablebooks);
  }
  fclose(books);
  Number--;
  database[Number].id = NULL;
  printf("successfully deleted\n");
}

void out (void) 
{
  books = fopen("books.csv", "r");
  if (books == NULL) {
    printf("Failed to open the file");
  }
  char a[] = "ID";
  char b[] = "Autors";
  char c[] = "Name";
  char d[] = "All books";
  char e[] = "Available";
  printf("%19s%30s%30s%15s%17s\n", a,b,c,d,e);
  
  char mas[100];
  fscanf(books, "%lld;", &database[Number].id);
  int j = 0;
  while (database[Number].id > 0) {            //цикл вывода библиотеки
    printf("%19lld", database[Number].id);
    while ((mas[j] = fgetc(books)) != '\n') {
      if (mas[j] == ';') {
        mas[j] = '\0';
        printf("%30s", mas);
        strncpy(database[Number].autors, mas, 100);
        j = 0;
        break;
      }
      else j++;
    }
    while ((mas[j] = fgetc(books)) != '\n') {
      if (mas[j] == ';') {
        mas[j] = '\0';
        printf("%30s ", mas);
        strncpy(database[Number].name, mas, 100);
        j = 0;
        break;
      }
      else j++;
    }

    fscanf(books, "%d;%d", &database[Number].allbooks, &database[Number].availablebooks);
    printf("%13d ", database[Number].allbooks);
    printf("%15d\n", database[Number].allbooks);
    Number++;
    fscanf(books, "%lld;", &database[Number].id);
  }
  fclose(books);
}
