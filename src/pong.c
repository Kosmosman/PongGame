#include <stdio.h>
#define HEIGHT 25              // Высота поля
#define LENGHT 80              // Ширина поля
#define PLATFORM 3             // Ширина платформы
#define BALL_SIZE 1                 // Размер мяча

int locate_rocket_1(int pos, char ch);
int locate_rocket_2(int pos, char ch);
int locate_ball(char ch);
void print_field(int pos_1, int pos_2, int pos_ball_x, int poss_ball_y);
int vector_x(int own);
int vector_y(int op);
int change_owner(int plat_1, int plat_2, int x, int y);

int main(void) {
    int count, sc_1 = 0, sc_2 = 0, owner, flag_y = -1, flag_x;
    int rocket_1 = 12, rocket_2 = 12, ball_y = 12, ball_x;
    char command;
    printf("Добро пожаловать в понг! Выберите стартующего игрока (1 или 2): ");
    while ((scanf("%d", &owner) != 1) || ((owner != 1) && (owner != 2)) || getchar() != '\n') {
        printf("Некорректное значение! ");
            while ((getchar() != '\n'));
    }
    ball_x = 1 ? 3 : LENGHT - 3;            // Определение начального положения мяча по оси Х
    flag_x = vector_x(owner);
    printf("Введите любую клавишу для старта игры (только не кнопку выключения компьютера :)  ");
    while (sc_1 < 21 && sc_2 < 21) {
        scanf("%c", &command);
        while (getchar() != '\n');
        rocket_1 = locate_rocket_1(rocket_1, command);
        rocket_2 = locate_rocket_2(rocket_2, command);
        ball_y += flag_y;
        ball_x += flag_x;
        if (ball_y <= 2 && ball_y >= 26)            // Изменяет направление мяча по оси Y, если мяч достиг верхней или нижней стенки
            flag_y *= -1;
        flag_x = vector_x(owner);
        owner = change_owner(rocket_1, rocket_2, ball_x, ball_y);
        print_field(rocket_1, rocket_2, ball_x, ball_y);
    }
        return 0;
}

void print_field(int pos_1, int pos_2, int pos_ball_x, int pos_ball_y) {                // Печатает поле со всем объектами
    int count, flag_1 = 0, flag_ball = 0;
    for (count = 1; count <= LENGHT; count++)
        printf("-");
    printf("\n");
    for (count = 1; count <= HEIGHT - 2; count++){
        printf("|");
        if ((count >= pos_1) && (count < pos_1 + PLATFORM)) {
            printf("#");
            flag_1 = 1;
        } else {
            flag_1 = 0;
        }
        if (pos_ball_y == count) {
            printf("%*c", pos_ball_x - 2 - flag_1, 'o');
            flag_ball == pos_ball_x - 2 - flag_1;
        } else {
            flag_ball == 0;
        }
        if ((count >= pos_2) && (count < pos_2 + PLATFORM)) {
            printf("%*c|", LENGHT - 3 - flag_1 - flag_ball, '#');
            printf("\n");
        } else {
            printf("%*c\n", LENGHT - 2 - flag_1 - flag_ball, '|');
        }
    }
    for (count = 1; count <= LENGHT; count++)
        printf("-");
    printf("\n");
}

int locate_rocket_1(int pos, char ch) {             // Определяет позицию левой ракетки после ввода команды
    int res = pos;
    if (ch == 'z')
        if (pos < HEIGHT - 4)
            return ++res;
        else
            return res;
    else if (ch == 'a')
        if (pos > 1)
            return --res;
        else
            return res;
}

int locate_rocket_2(int pos, char ch) {             // Определяет позицию правой ракетки после ввода команды
    int res = pos;
    if (ch == 'm')
        if (pos < HEIGHT - 4)
            return ++res;
        else
            return res;
    else if (ch == 'k')
        if (pos > 1)
            return --res;
        else
            return res;
}

int vector_x(int own) {                               // Определяет направление движения мяча по оси Х
    int flag;
    flag = (own == 1) ? 1 : -1;
    return flag;
}
   
int change_owner(int plat_1, int plat_2, int x, int y) {                   // Определяет того, к кому направляется мяч
    int res;
    if ((y == LENGHT - 3) && ((x >= plat_2) && x < (plat_2 + PLATFORM)))
        return res = 1;
    if ((y == 3) && ((x >= plat_1) && x < (plat_1 + PLATFORM)))
        return res = 2;
}
    
