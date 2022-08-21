// Copyright 2022 joaquind
#include <stdio.h>
#define HEIGHT 25              // Высота поля
#define LENGHT 80              // Ширина поля
#define PLATFORM 3             // Ширина платформы
#define BALL_SIZE 1            // Размер мяча
#define FINISH 21              // Победный счет
// ОПИСАНИЕ ФУНКЦИЙ НАПРОТИВ КАЖДОЙ ИЗ НИХ
int locate_rocket_1(int pos, char ch);     // pos - позиция ракетки
int locate_rocket_2(int pos, char ch);     // относительно оси Y
int locate_ball(char ch);                  // ch - вводима команда
void print_field(int pos_1, int pos_2, int pos_ball_x,  // pos_ball
                 int pos_ball_y, int score_1, int score_2);  // координаты мяча
int vector_x(int own);        // own - последняя прикасавшаяся ракетка
int change_owner(int own, int pos_1, int pos_2,
                 int pos_ball_x, int poss_ball_y);
int start_move(int pos_1, int pos_2, int poss_ball_x, int pos_ball_y);
int start_x(int own);
int angle(int pos_1, int pos_2, int poss_ball_x, int pos_ball_y);

int main(void) {
    int sc_1 = 0, sc_2 = 0, owner;
    int flag_y = -1, flag_x = 1, flag_start = 0, flag_angle = 0;
    int rocket_1 = 12, rocket_2 = 12;
    int ball_y = 14, ball_x;
    char command;
    printf("Добро пожаловать в понг! Выберите стартующего игрока (1 или 2): ");
    while ((scanf("%d", &owner) != 1) || ((owner != 1) &&
                                          (owner != 2)) || getchar() != '\n') {
        printf("Некорректное значение! ");
            while ((getchar() != '\n')) continue;
    }
    ball_x = start_x(owner), flag_x = vector_x(owner);
    printf("Введите любую клавишу для старта игры (q для выхода)\n");
    while (sc_1 < FINISH && sc_2 < FINISH) {
        scanf("%c", &command);
        if (command == '\n') fflush(stdout);
        else
            while (getchar() != '\n') continue;
        if (command == 'q') break;
        ball_y += flag_y, ball_x += flag_x;
        flag_angle = angle(rocket_1, rocket_2, ball_x, ball_y);
        if (flag_angle == 1) {               // Если мяч ударяет в угол
            flag_y *= -1, flag_x *= -1;
            rocket_1 = locate_rocket_1(rocket_1, command);
            rocket_2 = locate_rocket_2(rocket_2, command);
            ball_y += flag_y * 2, ball_x += flag_x * 2;
            owner = (owner == 1) ? 2 : 1;  // Меняем владельца мяча
            print_field(rocket_1, rocket_2, ball_x, ball_y, sc_1, sc_2);
            continue;
        }
        rocket_1 = locate_rocket_1(rocket_1, command);
        rocket_2 = locate_rocket_2(rocket_2, command);
        flag_start = start_move(rocket_1, rocket_2, ball_x, ball_y);
        if (flag_start == 1) {
            rocket_1 = 12, rocket_2 = 12;
            (owner == 1) ? sc_1++ : sc_2++;
            owner = (owner == 1) ? 2 : 1;     // Меняем владельца мяча
            ball_y = 13, ball_x = start_x(owner);
            flag_y *= -1, flag_x *= -1;
            print_field(rocket_1, rocket_2, ball_x, ball_y, sc_1, sc_2);
            continue;
        } else {
            if (ball_y <= 1 || ball_y >= HEIGHT - 2) {  // Изменяет направление
            flag_y *= -1;                               // мяча по оси Y,
            }                      // если мяч достиг верхней или нижней стенки
            owner = change_owner(owner, rocket_1, rocket_2, ball_x, ball_y);
        flag_x = vector_x(owner);
        }
        print_field(rocket_1, rocket_2, ball_x, ball_y, sc_1, sc_2);
    }
    if (sc_1 == FINISH && command != 'q')
        printf("Поздравляем первого игрока с победой!\n");
    else if (sc_1 == FINISH && command != 'q')
        printf("Поздравляем второго игрока с победой!\n");
    return 0;
}
// Печатает поле со всем объектами
void print_field(int pos_1, int pos_2, int pos_ball_x, int pos_ball_y,
                 int score_1, int score_2) {
    int count, flag_1, flag_ball;
    for (count = 1; count <= LENGHT; count++) printf("-");
    printf("\n");
    for (count = 1; count <= HEIGHT - 2; count++) {
        printf("|");
        if ((count >= pos_1) && (count < pos_1 + PLATFORM)) {
            printf("#");
            flag_1 = 1;
        } else { flag_1 = 0;
        }
        if (pos_ball_y == count) {
            printf("%*c", pos_ball_x - 1 - flag_1, 'o');
            flag_ball = pos_ball_x - 1 - flag_1;
        } else { flag_ball = 0;
        }
        if ((count >= pos_2) && (count < pos_2 + PLATFORM)) {
            printf("%*c|", LENGHT - 2 - flag_1 - flag_ball, '#');
            printf("\n");
        } else {
            printf("%*c\n", LENGHT - 1 - flag_1 - flag_ball, '|');
        }
    }
    for (count = 1; count <= LENGHT; count++) printf("-");
    printf("\n");
    printf("|%*d%*c%*d%*c\n", LENGHT / 4, score_1, LENGHT / 4,
           '|', LENGHT / 4, score_2, LENGHT / 4 - 1, '|');
    for (count = 1; count <= LENGHT; count++) printf("-");
    printf("\n");
}
// Определяет позицию левой ракетки после ввода команды
int locate_rocket_1(int pos, char ch) {
    int res = pos;
    if (ch == 'z') {
        if (pos < HEIGHT - 4) res += 1;
        else
            return res;
    } else if (ch == 'a') {
        if (pos > 1) res -= 1;
    }
    return res;
}
// Определяет позицию правой ракетки после ввода команды
int locate_rocket_2(int pos, char ch) {
    int res = pos;
    if (ch == 'm') {
        if (pos < HEIGHT - 4) res += 1;
    } else if (ch == 'k') {
        if (pos > 1) res -= 1;
    }
    return res;
}
// Определяет направление движения мяча по оси Х
int vector_x(int own) {
    int flag;
    if (own == 1) flag = 1;
    else if (own == 2) flag = -1;
    return flag;
}
// Определяет того, к кому направляется мяч
int change_owner(int own, int pos_1, int pos_2,
                 int pos_ball_x, int poss_ball_y) {
    int res;
    if ((pos_ball_x == LENGHT - 2) &&
        ((poss_ball_y >= pos_2) && (poss_ball_y < (pos_2 + PLATFORM))))
        res = 2;
    else if ((pos_ball_x == 3) &&
             ((poss_ball_y >= pos_1) && (poss_ball_y < (pos_1 + PLATFORM))))
        res = 1;
    else
        res = own;
    return res;
}
// Определяет, необходимо ли начать новый ход
int start_move(int pos_1, int pos_2, int pos_ball_x, int pos_ball_y) {
    int flag = 0;
    if ((pos_ball_x > LENGHT - 1) &&
        ((pos_ball_y < pos_2) || (pos_ball_y >= (pos_2 + PLATFORM))))
        flag = 1;
    else if ((pos_ball_x < 2) &&
             ((pos_ball_y < pos_1) || (pos_ball_y >= (pos_1 + PLATFORM))))
        flag = 1;
    return flag;
}
// Определение начального положения мяча по оси Х
int start_x(int own) {
    int x;
    if (own == 1) x = 3;
    else if (own == 2) x = LENGHT - 2;
    return x;
}
// Проверяет, приходится ли удар мяча на угол ракетки
int angle(int pos_1, int pos_2, int pos_ball_x, int pos_ball_y) {
    int flag = 0;
    if ((pos_ball_x == LENGHT - 1) &&
        ((pos_ball_y == pos_2) || (pos_ball_y == pos_2 + PLATFORM - 1)))
        flag = 1;
    else if ((pos_ball_x == 2) &&
             ((pos_ball_y == pos_1) || (pos_ball_y == pos_1 + PLATFORM - 1)))
        flag = 1;
    return flag;
}
