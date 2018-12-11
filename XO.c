/* простая программа игры в крестики-нолики */
#include <stdio.h>
#include <stdlib.h>

#define SPACE ' '
char matrix[3][3] = { /* поле для крестиков-ноликов */
{SPACE, SPACE, SPACE},
{SPACE, SPACE, SPACE},
{SPACE, SPACE, SPACE}
};
void get_computer_move(void), get_player_move(void);
void disp_matrix(void);
char check(void);
int main()
{
  char done;
  printf("Это простая игра в крестики-нолики.\n");
  printf("В этой версии вы можете играть только с компьютером.\n");
  done = SPACE;
  do {
    disp_matrix(); /* вывод игрового поля */
    get_player_move(); /* ходит игрок */
    done = check(); /* проверка на победу */
    if (done != SPACE) break; /* победитель */
    get_computer_move(); /* ходит компьютер */
    done = check(); /* проверка на победу */
  } while (done == SPACE);
  if (done == 'X') printf("Ты победил!\n");
  else printf("Я выиграл!!!!\n");
  disp_matrix(); /* отображение результирующего положения */
  return 0;
}

/* ход игрока */
void get_player_move(void)
{
  int x, y;
  printf("Укажите строку и колонку вашего X.\n");
  printf("Строка? ");
  scanf("%d", &x);
  printf("Колонка? ");
  scanf("%d", &y);
  x-- ; y--;
  if (x < 0 || y < 0 || x>2 || y>2 || matrix[x][y] != SPACE)
  {
    printf("Неудачная попытка.Попробуй ещё.\n");
    get_player_move();
  }
  else matrix[x][y] = 'X';
}

/* ход компьютера */
void get_computer_move(void)
{
  register int t;
  char *p;
  p = (char *)matrix;
  for (t = 0; *p != SPACE && t < 9; ++t) p++;
  if (t == 9)
  {
    printf("draw\n");
    exit(0); /* game over */
  }
  else *p = 'O';
}

/* отображение игрового поля */
void disp_matrix(void)
{
  int t;
  for (t = 0; t < 3; t++)
  {
    printf(" %c | %c | %c", matrix[t][0], matrix[t][1], matrix[t][2]);
    if (t != 2) printf("\n---|---|---\n");
  }
  printf("\n");
}

/* проверка на победу */
char check(void)
{
  int t;
  char *p;
  for (t = 0; t < 3; t++) { /* проверка строк */
    p = &matrix[t][0];
    if (*p == *(p + 1) && * (p + 1) == *(p + 2)) return *p;
  }
  for (t = 0; t < 3; t++) { /* проверка столбцов */
    p = &matrix[0][t];
    if (*p == *(p + 3) && *(p + 3) == *(p + 6)) return *p;
  }

  /* проверка диагоналей */
  if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2])
    return matrix[0][0];
  if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0])
    return matrix[0][2];
  return SPACE;
}
