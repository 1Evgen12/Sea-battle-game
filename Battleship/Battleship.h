#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;
const int N = 10;

void gotoxy(int x, int y);
//функция для ручной установки кораблей
bool set_ship(int field[N][N], int x, int y, int direction, int size_ship, int index);

void show_ship(int x, int y, int dir, int size);

bool ship_in_field(int x, int y, int direction, int size_ship);

// случайная генерация кораблей 
void ship_generator(int ship_id, int size_ship, int field[N][N]);

void show_field(int field[N][N], int fog[N][N], bool useFog);

int shot(int field[N][N], int fog[N][N], int x, int y, int ships[N], int& index, int& count_ships, int& count_shots);

void autoFill(int field[N][N], int& x, int& y, int fog[N][N]);

bool enter_coord(int& exit, int& x, string symbol, int& y);

void artificial_intelligence(bool& mode, int& xBot, int& yBot, int field[N][N], int& resultShot,
	int fog[N][N], int ships[N], int& index, const int shipsConst[N],int& firstShotX, 
	int& firstShotY, int& dir, int& count_ships, int& count_shots, int player);

void total_time(int& hours, int& minuts, int& seconds, int total);
