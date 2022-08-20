#include <stdio.h>
#define HEIGHT 25              // Высота поля
#define LENGHT 80              // Ширина поля
#define PLATFORM 3             // Ширина платформы
#define BALL 1                 // Размер мяча

int locate_rocket_1(int pos, char ch);
int locate_rocket_2(int pos, char ch);
int locate_ball(char ch);
void print_field(int pos_1, int pos_2);

int main(void) {
    int i, sc_1 = 0, sc_2 = 0;
    int rocket_1 = 12, rocket_2 = 12;
    char command;
    while (sc_1 < 21 && sc_2 < 21) {
        scanf("%c", &command);
        getchar();
        rocket_1 = locate_rocket_1 (rocket_1, command);
        print_field(rocket_1, rocket_2);
        /*for (i = 1; i <= LENGHT; i++)
            printf("-");
        printf("\n");
        for (i = 1; i <= HEIGHT; i++){
            printf("|");
            if ((i >= rocket_1) && (i < rocket_1 + PLATFORM))
                printf("#");
            if ((i >= rocket_2) && (i < rocket_2 + PLATFORM))
                printf("%*c|\n", LENGHT - 3, '#');
            else
                printf("%*c\n", LENGHT - 1, '|');
        }
        for (i = 1; i <= LENGHT; i++)
            printf("-");
        printf("\n");*/
    }
        return 0;
}

void print_field(int pos_1, int pos_2) {                // Печатает поле
    int i, flag_1 = 1;
    for (i = 1; i <= LENGHT; i++)
        printf("-");
    printf("\n");
    for (i = 1; i <= HEIGHT; i++){
        printf("|");
        if ((i >= pos_1) && (i < pos_1 + PLATFORM)) {
            printf("#");
            flag_1 = 0;
        } else {
            flag_1 = 1;
        }
        if ((i >= pos_2) && (i < pos_2 + PLATFORM)) {
            printf("%*c", LENGHT - 3  - flag_1, '#');
            printf("|\n");
        } else {
            printf("%*c\n", LENGHT - flag_1, '|');
            
        }
            
    }
    for (i = 1; i <= LENGHT; i++)
        printf("-");
    printf("\n");
}

int locate_rocket_1(int pos, char ch) {             // Определяет позицию левой ракетки после ввода команды
    if (ch == 'a')
        return pos++;
    else if (ch == 'z')
        return pos--;
    else
        while (getchar() != '\n');
}
