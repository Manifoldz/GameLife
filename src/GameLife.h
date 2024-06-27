#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

// инициализация первоначальной матрицы
void Input(char matrix[][WIDTH], int n, int m);

// вывод матрицы
void Output(char matrix[][WIDTH], int n, int m);
// контроль скорости
int SpeedChange(char button, int pause);
// расчет нового поколения согласно правилам
void NewGen(char A[][WIDTH], char B[][WIDTH], int n, int m);
// подсчет соседей у клетки
int CountNeighbours(char matrix[][WIDTH], int y, int x);
// проверка одинаковы ли матрицы
int isTheSame(char A[][WIDTH], char B[][WIDTH], int n, int m);
// swap матрицы
void Swap(char A[][WIDTH], char B[][WIDTH], int n, int m);

#endif