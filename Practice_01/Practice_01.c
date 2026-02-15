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
}
