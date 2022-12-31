#include "Battleship.h"

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	srand(time(NULL));

	bool game{ 1 };
	while (game == 1) {
		int field[N][N]{};  //матрица поля для кораблей
		int field2[N][N]{};
		int fog[N][N]{};     //матрица тумана войны
		int fog2[N][N]{};

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				field[i][j] = 10;
				field2[i][j] = 10;
			}
		}
		int ships[N] = { 4,3,3,2,2,2,1,1,1,1 };      //количество целых палуб у кораблей игрока 
		int ships2[N] = { 4,3,3,2,2,2,1,1,1,1 };		 //количество целых палуб у кораблей компьютера
		int count_ships = N, count_ships2 = N;
		int count_shots{}, count_shots2{}, turns{};
		const int shipsConst[N] = { 4,3,3,2,2,2,1,1,1,1 };
		
		int x{}, y{};      //переменные для ввода координат
		string symbol;
		bool DIR{ 0 };
		bool turn = 1; //1 - ход игрока(если есть)

		//переменные для ИИ
		bool mode{}, mode2{};
		int firstShotX{}, firstShotY{}, firstShotX2{}, firstShotY2{};
		int xBot{}, yBot{};
		int dir{}, dir2{};

		int player = 1;   // 1 - игрок vs компьютер, 2 - компьютер vs компьютер
		int autoGeneration = 1;  // 1 - автоматическая расстановка кораблей, 2 - ручная
		int difficulty = 1; //0 - случайные выстрелы, 1 - ИИ;

		int menu{ 1 }, exit{ 1 };
		bool result{ 0 };
	
		while (menu != 0) {
			if (menu == 1) {
				cout << " ____МОРСКОЙ БОЙ____\n\n";
				cout << " Выберите режим игры\n\n 1 - игрок против компьютера\n 2 - компьютер против компьютера\n 0 - выйти\n\n";
				while (!(cin >> player) || (player < 0 || player > 2)) {
					cin.clear();
					cin.ignore();
				}
				menu++;
				if (player == 0) {
					menu = 0;
					exit = 0;
					game = 0;
					continue;
				}
			}
			if (player == 1) {
				system("cls");
				if (menu == 2) {
					cout << " ____МОРСКОЙ БОЙ____\n\n";
					cout << " Выберите способ расстановки кораблей\n\n 1 - автоматическая\n 2 - ручная расстановка\n 3 - назад\n 0 - выйти\n\n";
					while (!(cin >> autoGeneration) || (autoGeneration < 0 || autoGeneration > 3)) {
						cin.clear();
						cin.ignore();
					};
					menu++;
					if (autoGeneration == 0) {
						menu = 0;
						exit = 0;
						game = 0;
						system("cls");
						continue;
					}
					else if (autoGeneration == 3) {

						menu = 1;
						autoGeneration = 1;
						system("cls");
						continue;
					}
				}
				if (menu == 3) {
					system("cls");

					cout << " ____МОРСКОЙ БОЙ____\n\n";
					cout << " Выберите сложность игры\n\n 1 - игра с ИИ\n 2 - случайные выстрелы\n 3 - назад\n 0 - выйти\n\n";
					while (!(cin >> difficulty) || (difficulty < 0 || difficulty > 3)) {
						cin.clear();
						cin.ignore();
					}
					if (difficulty == 0) {
						menu = 0;
						exit = 0;
						game = 0;
					}
					else if (difficulty == 3) {
						menu = 2;
						difficulty = 1;
						system("cls");
					}
					else menu = 0;
				}
			}
			else if (player == 2) {
				turn = 0;
				menu = 0;
			}
		}
		system("cls");

		//для расчета времени игры
		int h{}, m{}, s{}, t1{}, t2{};

		if (exit == 1) {
			if (autoGeneration == 1) {  //генерация кораблей для игрока

				for (int i = 0; i < N; i++)
				{
					ship_generator(i, ships[i], field);
				}
			}
			else if (autoGeneration == 2) { //ручная расстановка кораблей

				for (int i = 0; i < N; i++)
				{
					bool set = 0;

					while (set == 0) {
						cout << "     Расставьте свои корабли\n";
						show_field(field, fog, 0);
						cout << endl;
						cout << "    w, a, s, d - перемещение корабля\n";
						cout << "    r - поворот корабля\n";
						cout << "    Enter - поставить корабль\n";
						cout << "    0 - выйти в меню\n";
						show_ship(x, y, dir2, shipsConst[i]);

						int temp_x = x;
						int temp_y = y;
						int temp_dir = dir2;

						int ch = _getch();

						switch (ch)		//изменить координаты или направление
						{
						case 100:		// d вправо
							y++;
							break;
						case 226:		// в вправо
							y++;
							break;
						case 115:		// s вниз
							x++;
							break;
						case 251:		// ы вниз
							x++;
							break;
						case 97:		// a влево
							y--;
							break;
						case 244:		// ф влево
							y--;
							break;
						case 119:		// w вверх
							x--;
							break;
						case 246:		// ц вверх
							x--;
							break;
						case 114:       // r поворот
							dir2 = !dir2;
							break;
						case 234:       // к поворот
							dir2 = !dir2;
							break;
						case 48:		// выйти в меню
							set = 1;
							i = N;
							exit = 0;
							system("cls");
							break;;

						case 13:		// enter установка корабля
							if (set_ship(field, x, y, dir2, shipsConst[i], i) == true) {
								set = 1;
							}
							break;
						}

						if (!(ship_in_field(x, y, dir2, shipsConst[i]))) {
							x = temp_x;
							y = temp_y;
							dir2 = temp_dir;
						}

						system("cls");
					}

				}
			}
			if (exit == 1) {
				for (int i = 0; i < N; i++) //генерация кораблей для компьютера
				{
					ship_generator(i, ships2[i], field2);
				}
				cout << endl;
				t1 = time(NULL);

			}
		}

		while (exit == 1) {   //главный цикл

			int resultShot{};
			int index{};

			do {
				if (player == 1) {

					if (turns < 2) {
						cout << "     Игра началась!\n\n";
					}
					cout << "     Игрок   Кораблей " << count_ships << endl;
					show_field(field, fog, 0);
					cout << endl;

					cout << "     Бот1    Кораблей " << count_ships2 << endl;

					show_field(field2, fog2, 1);
					cout << " 0 - выйти\n";
					cout << endl;
				}
				else {
					cout << "     Бот1    Кораблей " << count_ships2 << endl;
					show_field(field2, fog2, 1);
					cout << endl;

					cout << "     Бот2    Кораблей " << count_ships << endl;
					show_field(field, fog, 1);
					cout << endl;
				}
				if (turn == 1) {
					if (player == 1) {
						cout << "     Ваш ход \n";
						cout << "     Введите координаты : ";
						if (turns < 8)
							cout << "\b\b\b. Например А 1: ";
						if (enter_coord(exit, x, symbol, y)) {
							break;
						}

						while (field2[y][x] == -3 || field2[y][x] == -2 || field2[y][x] == -1) {

							cout << "     Введите другие координаты : ";
							if (enter_coord(exit, x, symbol, y)) {
								break;
							}
						}
						if (exit == 0)
							break;

						resultShot = shot(field2, fog2, y, x, ships2, index, count_ships2, count_shots);

						if (resultShot == 2) { //автозаполнение ячеек вокруг потопленого корабля
							for (int i = 0; i < shipsConst[index]; i++) {
								autoFill(field2, y, x, fog2);
							}
						}
					}
					else if (player == 2) {
						cout << "     Бот2: ";
						Sleep(500);

						artificial_intelligence(mode2, x, y, field2, resultShot,
							fog2, ships2, index, shipsConst, firstShotX2, firstShotY2, dir2, count_ships2, count_shots, player);
					}
				}

				else if (turn == 0) {

					cout << "     Бот1: ";
					Sleep(500);

				//случайный выстрел компьютера
					if (difficulty == 2) {

						do {
							xBot = rand() % N;
							yBot = rand() % N;
						} while (!(field[yBot][xBot] >= 0 && field[yBot][xBot] <= N));

						cout << xBot + 1 << ' ' << yBot + 1 << endl;;
						Sleep(1000);

						resultShot = shot(field, fog, yBot, xBot, ships, index, count_ships, count_shots2);
					}
					
					else if (difficulty == 1) {

						artificial_intelligence(mode, xBot, yBot, field, resultShot,
							fog, ships, index, shipsConst, firstShotX, firstShotY, dir, count_ships, count_shots2, player);
					}
				}

				if (resultShot == 1) {
					cout << "\tПодбил!";
				}
				else if (resultShot == 2) {
					cout << "\tПотоплен!";
				}
				else {
					cout << "\tПромах";
				}

				if (player == 1) 
					Sleep(1500);
				else 
					Sleep(500);

				if (count_ships2 == 0 || count_ships == 0) {
					result = 1;
					t2 = time(NULL);
					total_time(h, m, s, t2 - t1);
					break;
				}
					
				system("cls");

			} while (resultShot != 0);

			turns++;
			turn = !turn;
			system("cls");

			if (player == 1 && (count_ships == 0 || count_ships2 == 0)) {
				if (count_ships == 0) {
					cout << "     Вы проиграли!\n\n";
					break;
				}
				else if (count_ships2 == 0) {
					cout << "     Вы победили!\n\n";
					break;
				}
			}
			else if(player == 2 && (count_ships == 0 || count_ships2 == 0)){
				if (count_ships == 0) {
					cout << "     Бот1 победил!\n\n";
					break;
				}
				else if (count_ships2 == 0) {
					cout << "     Бот2 победил!\n\n";
					break;
				}
			}

		}

		if (result == 1) {

			if (player == 1) {
				cout << "     Игрок\tКораблей " << count_ships << "\tВыстрелов " << count_shots << "\tВремя игры "<< h << ':' << m << ':' << s << endl;
				show_field(field, fog, 0);
				cout << endl;
				cout << "     Бот1\tКораблей " << count_ships2 << "\tВыстрелов " << count_shots2 << endl;
				show_field(field2, fog2, 0);
				cout << endl;
			}
			else {
				cout << "     Бот1\tКораблей " << count_ships2 << "\tВыстрелов " << count_shots2 << "\tВремя игры " << h << ':' << m << ':' << s << endl;
				show_field(field2, fog2, 0);
				cout << endl;
				cout << "     Бот2\tКораблей " << count_ships << "\tВыстрелов " << count_shots << endl;
				show_field(field, fog, 0);
				cout << endl;
			}
		}
		if (game == 1) {
		cout << "   0 - выйти\n   1 - меню\n";
		while (!(cin >> game)) {
			cin.clear();
			cin.ignore();
		}
	}
		system("cls");
	}
}
