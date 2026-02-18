/*Дан файл, содержащий сведения о постройках.
Структура записи: название, местоположение, тип постройки, архитектор,год постройки.
Вывести сведения о сооружениях определенного типа, например, «собор», построенных до указанного века. Найти самый старый архитектурный памятник.*/
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
    list buildings = NULL;
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
            case 49: 
                puts("\nYou select insert");
                buildings = new_node(buildings, input_building());
                break;
            case 50: 
                puts("\nYou select show");
                show(buildings);
                break;
            case 51: puts("\nYou select filter"); break;
            case 52: puts("\nYou select search"); break;
            case 53: 
                puts("\nYou select delete");
                buildings = delete_node(buildings);
                break;
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

DataType input_building(void)
{
    struct building building;
    char* ptmp;

    // 1. Название
    puts("Enter name:");
    fgets(building.name, 30, stdin);
    ptmp = strchr(building.name, '\n');
    if (ptmp) *ptmp = '\0';
    else while (getchar() != '\n');

    // 2. Местоположение
    puts("Enter location:");
    fgets(building.location, 50, stdin);
    ptmp = strchr(building.location, '\n');
    if (ptmp) *ptmp = '\0';
    else while (getchar() != '\n');

    // 3. Тип (например, "собор")
    puts("Enter type:");
    fgets(building.type, 15, stdin);
    ptmp = strchr(building.type, '\n');
    if (ptmp) *ptmp = '\0';
    else while (getchar() != '\n');

    // 4. Архитектор
    puts("Enter architect:");
    fgets(building.architect, 30, stdin);
    ptmp = strchr(building.architect, '\n');
    if (ptmp) *ptmp = '\0';
    else while (getchar() != '\n');

    // 5. Год
    puts("Enter year:");
    // Используем %d, так как год — целое число (int)
    // Добавляем %*c, чтобы съесть Enter после ввода числа
    scanf("%d%*c", &building.year);

    return building;
}

list new_node(list head, DataType building)
{
    list temp = (list)malloc(sizeof(struct node));
    temp->data = building;
    temp->next = head;
    return temp;
}

void show(list cur)
{
    int k = 0;
    system("CLS");
    if (cur == NULL)
    {
        puts("List is empty");
        getchar();
        return;
    }
    puts("------------------------------------------------------------------------------------------------------");
    puts("|  N |            Name            |      Location      |      Type     |      Architect     |  Year  |");
    puts("------------------------------------------------------------------------------------------------------");
    while (cur)
    {
        printf("|%3d | %-26s | %-18s | %-13s | %-18s | %6d |\n",
            ++k,
            cur->data.name,
            cur->data.location,
            cur->data.type,
            cur->data.architect,
            cur->data.year);
        cur = cur->next;
    }
    puts("------------------------------------------------------------------------------------------------------");
    getchar();
}

list delete_node(list head)
{
    struct node* temp;
    if (head)
    {
        temp = head;
        head = head->next;
        free(temp);
        puts("Deleted");
    }
    if (head == NULL)
        puts("List is empty");
    getchar();
    return head;
}