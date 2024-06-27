#include "GameLife.h"

int main() {
  char A[HEIGHT][WIDTH];
  char B[HEIGHT][WIDTH];
  int counter = 0;
  int pause = 100000;

  Input(A, HEIGHT, WIDTH);

  FILE *tty;
  // перенаправление потока ввода обратно в консоль
  tty = freopen("/dev/tty", "r+", stdin);
  // инициализирует библиотеку curses и ее структуры данных
  initscr();
  // отключить отображение вводимых символов
  noecho();
  // выкл. задержку(getch) не блокирует выполнение программы
  nodelay(stdscr, TRUE);
  // контроль ввода отключаем, чтобы enter не ждал
  cbreak();
  // скрываем курсор
  curs_set(FALSE);

  while (1) {
    clear();
    printw("Generation number: %d\n", counter);
    Output(A, HEIGHT, WIDTH);
    refresh();
    pause = SpeedChange(wgetch(stdscr), pause);
    usleep(pause);
    NewGen(A, B, HEIGHT, WIDTH);
    if (isTheSame(A, B, HEIGHT, WIDTH))
      break;
    else {
      Swap(A, B, HEIGHT, WIDTH);
      counter++;
    }
  }
  printw("\nGame Over!");
  refresh();
  usleep(4000000);
  fclose(tty);  // закрыть файл
  endwin();     // выключаем работу ncurses
  return 0;
}

void Input(char matrix[][WIDTH], int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      // читаем напрямую в матрицу, а потом проверяем что именно записалось,
      // надо либо ' ', либо 'o'
      if (scanf("%c", &matrix[i][j]) == 1) {
        if (matrix[i][j] != 'o' && matrix[i][j] != ' ' && matrix[i][j] != '\n')
          matrix[i][j] = ' ';
        if (matrix[i][j] == '\n') {
          scanf("%c", &matrix[i][j]);
        }
      } else {
        matrix[i][j] = ' ';
      }
    }
  }
}

void Output(char matrix[][WIDTH], int n, int m) {
  printw("\n");
  for (int i = 0; i < WIDTH; i++) printw("=");
  printw("\n");
  // игровое поле
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m - 1; j++) printw("%c", matrix[i][j]);
    if (i == n - 1)
      printw("%c", matrix[i][m - 1]);
    else
      printw("%c\n", matrix[i][m - 1]);
  }
  printw("\n");
  for (int i = 0; i < WIDTH; i++) printw("=");
  printw("\n");
}

int SpeedChange(char button, int pause) {
  if (button == '+')
    pause -= 20000;
  else if (button == '-')
    pause += 20000;

  if (pause > 1000000) pause = 1000000;
  if (pause < 20000) pause = 20000;
  return pause;
}

void NewGen(char A[][WIDTH], char B[][WIDTH], int n, int m) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      int temp = CountNeighbours(A, i, j);
      // обработка правилами игры
      if (temp == 2 && A[i][j] == 'o')
        B[i][j] = 'o';
      else if (temp == 3)
        B[i][j] = 'o';
      else
        B[i][j] = ' ';
    }
}

int CountNeighbours(char matrix[][WIDTH], int y, int x) {
  int res = 0;
  int coor_x, coor_y;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      coor_x = x + i;
      coor_y = y + j;
      // обработка граничных условий
      if (coor_x == -1) coor_x = WIDTH - 1;
      if (coor_y == -1) coor_y = HEIGHT - 1;
      if (coor_x == WIDTH) coor_x = 0;
      if (coor_y == HEIGHT) coor_y = 0;

      if (matrix[coor_y][coor_x] == 'o') res += 1;
    }
  }
  return res;
}

int isTheSame(char A[][WIDTH], char B[][WIDTH], int n, int m) {
  int flag = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      if (A[i][j] != B[i][j]) {  // хоть 1 отличие сразу выходим
        flag = 0;
        break;
      }
    if (!flag) break;
  }
  return flag;
}

void Swap(char A[][WIDTH], char B[][WIDTH], int n, int m) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      char temp = A[i][j];
      A[i][j] = B[i][j];
      B[i][j] = temp;
    }
}