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
list filter(list);  /*сведения о сооружениях определенного типа*/
void search(list);  /*поиск самой старой постройки*/
list delete_node(list);  /*удаление первого узла списка*/
void any_key(); /*Press any key*/
char* read_string(char*, int); /*Ввод переменных*/

int main()
{
    char file[50];
    list buildings = NULL;
    puts("Enter the file name:");
    gets(file);
    buildings = read_file(file);
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
            case 51: 
                puts("\nYou select filter");
                show(filter(buildings));
                break;
            case 52: 
                puts("\nYou select search");
                if (buildings == NULL) 
                {
                    puts("List is empty");
                }
                else
                {
                    search(buildings);
                }
                break;
            case 53: 
                puts("\nYou select delete");
                buildings = delete_node(buildings);
                break;
            default:
                puts("Wrong value");
                printf("%d", menu);
                break;
        }
        any_key();
    } while (1);
    if (write_file(file, buildings))
        puts("File saved");
    return 0;
}

DataType input_building(void)
{
    struct building building;
    char* ptmp;

    // 1. Название
    puts("Enter name:");
    read_string(building.name, 30);

    // 2. Местоположение
    puts("Enter location:");
    read_string(building.location, 50);

    // 3. Тип (например, "собор")
    puts("Enter type:");
    read_string(building.type, 15);
   
    // 4. Архитектор
    puts("Enter architect:");
    read_string(building.architect, 30);

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
    return head;
}

list read_file(char* filename)
{
    FILE* f;
    DataType building;
    list head = NULL, cur;
    if ((f = fopen(filename, "rb")) == NULL)
    {
        puts("File not found. List is empty.");
        any_key();
        return NULL;
    }
    if (fread(&building, sizeof(building), 1, f))
        head = new_node(NULL, building);
    else
        return NULL;
    cur = head;
    while (fread(&building, sizeof(building), 1, f))
    {
        cur->next = new_node(NULL, building);
        cur = cur->next;
    }
    fclose(f);
    return head;
}

int write_file(char* filename, list head)
{
    FILE* f;
    if ((f = fopen(filename, "wb")) == NULL)
    {
        perror("Error create file");
        any_key();
        return 0;
    }
    while (head)
    {
        if (fwrite(&head->data, sizeof(DataType), 1, f))
            head = head->next;
        else
            return 0;
    }
    return 1;
}

void search(list cur)
{
    if (cur == NULL) 
    {
        puts("List is empty");
        return;
    }

    list oldest = cur; // Предполагаем, что первый — самый старый
    list temp = cur->next;

    while (temp) 
    {
        if (temp->data.year < oldest->data.year) 
        {
            oldest = temp;
        }
        temp = temp->next;
    }

    // Вывод результата
    puts("\nOldest building found:");
    printf("Name: %s, Year: %d, Location: %s\n",
        oldest->data.name,
        oldest->data.year,
        oldest->data.location);
}

void any_key()
{
    puts("\nPress any key...");
    getch();
}

char* read_string(char* temp, int len)
{
    char* ptmp;

    fgets(temp, len, stdin);
    ptmp = strchr(temp, '\n');
    if (ptmp) *ptmp = '\0';
    else while (getchar() != '\n');

    return temp;
}


list filter(list head)
{
    char type[15];
    int century;
    list filtered_list = NULL;

    puts("Enter building type:");
    read_string(type, 15);
    puts("Enter century:");
    scanf("%d%*c", &century);

    int maxyear = (century - 1) * 100;

    list temp = head;
    while (temp)
    {
        if (strcmp(temp->data.type, type) == 0 && temp->data.year < maxyear)
        {
            filtered_list = new_node(filtered_list, temp->data);
        }
        temp = temp->next;    
    }

    return filtered_list;
}
