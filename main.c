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
void add(void);
void Del(void);
void out(void);
void edit(void);
void chenge_books(void);

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
      case 3:
        edit();
      break;
      case 4:
        chenge_books();
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
  printf("The number of all available books (no more than all) > ");
  scanf("%d", &database[Number].availablebooks);
  if (database[Number].allbooks < database[Number].availablebooks) {
     printf("Enter another count of available books (later value is not true): ");
     scanf("%d", &database[Number].availablebooks);
  }

  books = fopen("books.csv", "a"); // запишем все в файл для дальнейшей работы
    fprintf(books, "%lld;%s;%s;%d;%d\n", database[Number].id, database[Number].autors,
      database[Number].name, database[Number].allbooks, database[Number].availablebooks);
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

  for (nd; nd < Number; nd++) { // сдвигаем элементы массива после удаляемого на 1 ячейку назад и записываем в файл
    database[nd].id = database[nd + 1].id;
    strncpy(database[nd].autors, database[nd + 1].autors, 100);
    strncpy(database[nd].name, database[nd + 1].name, 100);
    database[nd].allbooks = database[nd + 1].allbooks;
    database[nd].availablebooks = database[nd + 1].availablebooks;
  }
    for (int x = 1; x < (Number + 1); x++) { 
    fprintf(books, "%lld;%s;%s;%d;%d\n", database[x].id, database[x].autors, 
      database[x].name, database[x].allbooks, database[x].availablebooks);
  }
  fclose(books);
  Number--;
  printf("successfully deleted\n");
}

void out (void) 
{
  Number = 1;
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
    printf("%15d\n", database[Number].availablebooks);
    Number++;
    fscanf(books, "%lld;", &database[Number].id);
  }
  fclose(books);
}

 void edit(void) {
  int editnum = 1;
  int poisk = 0;
  long long idedit = 0;

  books = fopen("books.csv", "w");
  while (poisk == 0) {
    printf("Enter ID fo the edited book: ");
    scanf("%lld", &idedit);
    for (int k = 1; k < Number; k++) {
      if (idedit ==  database[k].id) {
        poisk = 1;
        editnum = k;
      }
    }
    if (poisk == 0) {
      printf("book with this ID was not found\n");
    }
  }
  for (int x = 1; x < editnum; x++) {
    fprintf(books, "%lld;%s;%s;%d;%d\n", database[x].id, database[x].autors, 
      database[x].name, database[x].allbooks, database[x].availablebooks);
  }
  printf("New autors > ");
  scanf("%s", database[editnum].autors);
  printf("New name of a book > ");
  scanf("%s", database[editnum].name);
  fprintf(books, "%lld;%s;%s;%d;%d\n", database[editnum].id, database[editnum].autors, 
      database[editnum].name, database[editnum].allbooks, database[editnum].availablebooks);

  for (editnum; editnum < Number; editnum++) {
 fprintf(books, "%lld;%s;%s;%d;%d\n", database[editnum + 1].id, database[editnum + 1].autors, 
      database[editnum + 1].name, database[editnum + 1].allbooks, database[editnum + 1].availablebooks);
      }
  fclose(books);
  printf("successfully edited\n");
 }

 void chenge_books(void) {
  long long idchange = 0;
  int changenum = 0;
  int poisk = 0;

  books = fopen("books.csv", "w");
  while (poisk == 0) {
    printf("Enter ID of the book which  count u want to chenge: ");
    scanf("%lld", &idchange);
    for (int k = 1; k < Number; k++) {
      if (idchange == database[k].id) {
        poisk = 1;
        changenum = k;
      }
    }
    if (poisk == 0) {
      printf("book with this ID was not found\n");
    }
  }
  for (int x = 1; x < changenum; x++) {
    fprintf(books, "%lld;%s;%s;%d;%d\n", database[x].id, database[x].autors, 
      database[x].name, database[x].allbooks, database[x].availablebooks);
  }
  printf("Enter new count of all books: ");
  scanf("%d", &database[changenum].allbooks);
  if (database[changenum].allbooks < database[changenum].availablebooks) {
     printf("Enter new count of available books (later value is not true): ");
     scanf("%d", &database[changenum].availablebooks);
  }

  fprintf(books, "%lld;%s;%s;%d;%d\n", database[changenum].id, database[changenum].autors, 
      database[changenum].name, database[changenum].allbooks, database[changenum].availablebooks);
  for (changenum; changenum < Number; changenum++) {
    fprintf(books, "%lld;%s;%s;%d;%d\n", database[changenum + 1].id, database[changenum + 1].autors, 
      database[changenum + 1].name, database[changenum + 1].allbooks, database[changenum + 1].availablebooks);
  }
  fclose(books);
 }
