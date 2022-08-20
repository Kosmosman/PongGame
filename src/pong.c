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
    int count, sc_1 = 0, sc_2 = 0;
    int rocket_1 = 12, rocket_2 = 12;
    char command;
    while (sc_1 < 21 && sc_2 < 21) {
        scanf("%c", &command);
        while (getchar() != '\n');
        rocket_1 = locate_rocket_1(rocket_1, command);
        printf("rocet_1 = %d\n", rocket_1);
        rocket_2 = locate_rocket_2(rocket_2, command);
        print_field(rocket_1, rocket_2);
    }
        return 0;
}

void print_field(int pos_1, int pos_2) {                // Печатает поле
    int count, flag_1 = 1;
    for (count = 1; count <= LENGHT; count++)
        printf("-");
    printf("\n");
    for (count = 1; count <= HEIGHT; count++){
        printf("|");
        if ((count >= pos_1) && (count < pos_1 + PLATFORM)) {
            printf("#");
            flag_1 = 1;
        } else {
            flag_1 = 0;
        }
        if ((count >= pos_2) && (count < pos_2 + PLATFORM)) {
            printf("%*c|", LENGHT - 2 - flag_1, '#');
            printf("\n");
        } else {
            printf("%*c\n", LENGHT - 1 - flag_1, '|');
            
        }
            
    }
    for (count = 1; count <= LENGHT; count++)
        printf("-");
    printf("\n");
}

int locate_rocket_1(int pos, char ch) {             // Определяет позицию левой ракетки после ввода команды
    int res = pos;
    if (ch == 'z') {
        return ++res;
    } else if (ch == 'a') {
        return --res;
    }
}

int locate_rocket_2(int pos, char ch) {             // Определяет позицию левой ракетки после ввода команды
    int res = pos;
    if (ch == 'm') {
        return ++res;
    } else if (ch == 'k') {
        return --res;
    }
}
