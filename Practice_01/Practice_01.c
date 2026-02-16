/*Дан файл, содержащий сведения о постройках.
Структура записи: название, местоположение, тип постройки, архитектор,год постройки.
Вывести сведения о сооружениях определенного типа, например, «собор», построенных до указанного века. Найти самый старый архитектурный памятник.*/
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct building
{
    char name[30];
    char location[50];
    char type[15];
    char architect[30];
    int year;
};

typedef struct building DataType;

struct node
{
       DataType data;
       struct node * next;
};

typedef struct node * list;

DataType input_building(void);   /*ввод данных*/
list read_file(char* filename);   /*чтение данных из файла в список*/
list new_node(list, DataType);     /*создание узла*/
int write_file(char* filename, list); /*запись содержимого списка в файл*/
void show(list);  /*вывод содержимого списка на экран*/
void filter(list);  /*сведения о сооружениях определенного типа*/
void search(list);  /*поиск самой старой постройки*/
list delete_node(list);  /*удаление первого узла списка*/

int main()
{
    int menu;
    do
    {
        system("CLS"); /* для windows, для linux system("clear") */
        puts("Choose an action:\n");
        puts("1. Insert");
        puts("2. Show");
        puts("3. Filter");
        puts("4. Search");
        puts("5. Delete");
        puts("6. Exit");
        menu = getch();
        if (menu == 54)
            break;
        switch (menu)
        {
            case 49: puts("\nYou select insert"); break;
            case 50: puts("\nYou select show"); break;
            case 51: puts("\nYou select filter"); break;
            case 52: puts("\nYou select search"); break;
            case 53: puts("\nYou select delete"); break;
            default:
                puts("Wrong value");
                printf("%d", menu);
                break;
        }
        puts("\nPress any key...");
        getch();
    } while (1);
    return 0;
}

