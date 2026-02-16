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
    char file[50];
    int menu;
    list building = NULL;
    puts("Enter the file name");
    gets(file);
    building = read_file(file);
    do
    {
        system("CLS"); /* для windows, для linux system("clear") */
        puts("1. Insert");
        puts("2. Show");
        puts("3. Search");
        puts("4. Delete");
        puts("5. Exit");
        scanf("%d%*c", &menu);
        switch (menu)
        {
        case 1: building = new_node(building, input_building()); break;
        case 2: show(building); break;
        case 3: 
        {
            int year;
            if (building == NULL)
            {
                puts("List is empty");
                getchar();
                break;
            }
            puts("Year?");
            scanf("%f%*c", &year);
            search(building, year); break;
        }
        case 4: building = delete_node(building);
        }
    } while (menu != 5);
    if (write_file(file, building))
        puts("File saved");
    else
        puts("File not saved");
    delete_list(building);
    return 0;
}