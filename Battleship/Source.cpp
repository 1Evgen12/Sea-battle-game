#include "Battleship.h"

void gotoxy(int x, int y) {  //функци€ став€ща€ курсор во введенные координаты
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
//функци€ дл€ ручной установки кораблей
bool set_ship(int field[N][N], int x, int y, int direction, int size_ship, int index) {

	int temp_x = x;
	int temp_y = y;
	bool setting_is_possible = true;

	for (int i = 0; i < size_ship; i++) //проверка возможности расположени€ корабл€
	{
		if (x < 0 || y < 0 || x >= N || y >= N) {    //условие провер€ет что корабль 
			setting_is_possible = false;             //не выходит за пределы пол€
			break;
		}


		if (field[x][y] >= 0 && field[x][y] < N) { 		//проверка что корабль не пересекаетс€ с другими корабл€ми
			setting_is_possible = false;
			break;
		}

		if (x > 0 && y > 0) {
			if (field[x - 1][y - 1] >= 0 && field[x - 1][y - 1] < N) {
				setting_is_possible = false;
				break;
			}
		}

		if (x > 0) {
			if (field[x - 1][y] >= 0 && field[x - 1][y] < N) {
				setting_is_possible = false;
				break;
			}
		}

		if (x > 0 && y < N - 1) {
			if (field[x - 1][y + 1] >= 0 && field[x - 1][y + 1] < N) {
				setting_is_possible = false;
				break;
			}
		}

		if (x < N - 1 && y > 0) {
			if (field[x + 1][y - 1] >= 0 && field[x + 1][y - 1] < N) {
				setting_is_possible = false;
				break;
			}
		}

		if (x < N - 1) {
			if (field[x + 1][y] >= 0 && field[x + 1][y] < N) {
				setting_is_possible = false;
				break;
			}
		}

		if (x < N - 1 && y < N - 1) {
			if (field[x + 1][y + 1] >= 0 && field[x + 1][y + 1] < N) {
				setting_is_possible = false;
				break;
			}
		}

		if (y > 0) {
			if (field[x][y - 1] >= 0 && field[x][y - 1] < N) {
				setting_is_possible = false;
				break;
			}
		}

		if (y < N - 1) {
			if (field[x][y + 1] >= 0 && field[x][y + 1] < N) {
				setting_is_possible = false;
				break;
			}
		}

		switch (direction) {
		case 0: //вниз
			x++;
			break;

		case 1: //вправо
			y++;
			break;

		case 2: //вверх
			x--;
			break;

		case 3: //влево
			y--;
			break;
		}
	}
	if (setting_is_possible == true) {  //если проверка пройдена, то корабль можно ставить

		x = temp_x;
		y = temp_y;

		for (int i = 0; i < size_ship; i++)
		{
			field[x][y] = index;    //присваивание каждому кораблю индексa

			switch (direction) {
			case 0: //вниз
				x++;
				break;

			case 1: //вправо
				y++;
				break;

			case 2: //вверх
				x--;
				break;

			case 3: //влево
				y--;
				break;
			}
		}
	}
	return setting_is_possible;
}

void show_ship(int x, int y, int dir, int size) { //функци€ отображает корабль и место
	y *= 4;
	x *= 2;
	for (int i = 0; i < size; i++)				  //перед установкой корабл€ (ручна€ установка)
	{
		gotoxy(y + 5, x + 4);
		cout << "# ";
		switch (dir) {
		case 0: //вниз
			x += 2;
			break;

		case 1: //вправо
			y += 4;
			break;

		case 2: //вверх
			x -= 2;
			break;

		case 3: //влево
			y -= 4;
			break;
		}
	}
}

bool ship_in_field(int x, int y, int direction, int size_ship) {

	bool in_field = true;

	for (int i = 0; i < size_ship; i++) //проверка возможности расположени€ корабл€
	{
		if (x < 0 || y < 0 || x >= N || y >= N) {    //условие провер€ет что корабль 
			in_field = false;             //не выходит за пределы пол€
			break;
		}

		switch (direction) {
		case 0: //вниз
			x++;
			break;

		case 1: //вправо
			y++;
			break;

		case 2: //вверх
			x--;
			break;

		case 3: //влево
			y--;
			break;
		}
	}
	return in_field;
}

// случайна€ генераци€ кораблей 
void ship_generator(int ship_id, int size_ship, int field[N][N]) {

	int iteration = 0;
	int count_ship = 0;
	int x, y;

	while (count_ship < 1) //генераци€ кораблей
	{
		iteration++;
		if (iteration > 100)
			break;

		x = rand() % N; //генераци€ случайных координат в границах пол€
		y = rand() % N;

		int temp_x = x;
		int temp_y = y;

		int direction = rand() % 4; //генераци€ случайного направлени€

		bool setting_is_possible = true;

		for (int i = 0; i < size_ship; i++) //проверка возможности расположени€ корабл€
		{
			if (x < 0 || y < 0 || x >= N || y >= N) {    //условие провер€ет что корабль 
				setting_is_possible = false;             //не выходит за пределы пол€
				break;
			}

			if (field[x][y] >= 0 && field[x][y] < N) { 		//проверка что корабль не пересекаетс€ с другими корабл€ми
				setting_is_possible = false;
				break;
			}
			if (x > 0 && y > 0) {
				if (field[x - 1][y - 1] >= 0 && field[x - 1][y - 1] < N) {
					setting_is_possible = false;
					break;
				}
			}
			if (x > 0) {
				if (field[x - 1][y] >= 0 && field[x - 1][y] < N) {
					setting_is_possible = false;
					break;
				}
			}
			if (x > 0 && y < N - 1) {
				if (field[x - 1][y + 1] >= 0 && field[x - 1][y + 1] < N) {
					setting_is_possible = false;
					break;
				}
			}
			if (x < N - 1 && y > 0) {
				if (field[x + 1][y - 1] >= 0 && field[x + 1][y - 1] < N) {
					setting_is_possible = false;
					break;
				}
			}
			if (x < N - 1) {
				if (field[x + 1][y] >= 0 && field[x + 1][y] < N) {
					setting_is_possible = false;
					break;
				}
			}
			if (x < N - 1 && y < N - 1) {
				if (field[x + 1][y + 1] >= 0 && field[x + 1][y + 1] < N) {
					setting_is_possible = false;
					break;
				}
			}
			if (y > 0) {
				if (field[x][y - 1] >= 0 && field[x][y - 1] < N) {
					setting_is_possible = false;
					break;
				}
			}
			if (y < N - 1) {
				if (field[x][y + 1] >= 0 && field[x][y + 1] < N) {
					setting_is_possible = false;
					break;
				}
			}

			switch (direction) {
			case 0: //вниз
				x++;
				break;

			case 1: //вправо
				y++;
				break;

			case 2: //вверх
				x--;
				break;

			case 3: //влево
				y--;
				break;
			}
		}

		if (setting_is_possible == true) {  //если проверка пройдена, то корабль можно ставить

			x = temp_x;
			y = temp_y;

			for (int i = 0; i < size_ship; i++)
			{
				field[x][y] = ship_id;    //присваивание каждому кораблю индексa

				switch (direction) {
				case 0: //вниз
					x++;
					break;

				case 1: //вправо
					y++;
					break;

				case 2: //вверх
					x--;
					break;

				case 3: //влево
					y--;
					break;
				}
			}
			count_ship++;
		}
	}
}

void show_field(int field[N][N], int fog[N][N], bool useFog) { // вывод пол€ на экран

	cout << "     ";
	for (int i = 192; i < 203; i++) {
		if (i == 201)
			continue;
		else cout << (char)i << "   ";
	}
	cout << endl;
	cout << "    ";

	//верхн€€ граница пол€
	for (int i = 0; i < N * 4 - 1; i++)
	{
		cout << '_';
	}
	cout << endl << "   " << '|';
	for (int i = 0; i < N * 4 - 2; i++)
	{
		cout << ' ';
	}
	cout << " |";
	cout << endl;

	for (int i = 0; i < N; i++) {
		cout << ' ';
		if (i == N)  cout << ' '; 
		if (i < N - 1) 
			cout << i + 1 <<" | ";
		else cout << i + 1 <<"| ";

		for (int j = 0; j < N; j++) {
			if (fog[i][j] == 1 || useFog == 0) {

				if (field[i][j] >= 0 && field[i][j] < N) {
					cout << "# | ";
				}
				else if (field[i][j] == -2 || field[i][j] == -3) {
					cout << "X | ";
				}
				else if (field[i][j] == -1) {
					cout << ". | ";
				}
				else {
					cout << "  | ";
				}
			}
			else cout << "  | ";
		}
		// горизонтальные линии

		cout << endl;
		if (i < N - 1) {
			cout << "   | ";
			cout << "--";
			for (int i = 0; i < N - 1; i++)
			{
				cout << "|---";
			}

			cout << "\b |";
			cout << endl;
		}
		else cout << "    ";
	}
	//нижн€€ граница пол€
	cout << "\b|";
	for (int i = 0; i < N * 4 - 1; i++)
	{
		cout << '_';

	}
	cout << '|' << endl;;
	cout << "   ";

}

int shot(int field[N][N], int fog[N][N], int x, int y, int ships[N], int& index, int& count_ships, int& count_shots) {

	int result = 0;

	if (field[x][y] >= 0 && field[x][y] < N) {

		ships[field[x][y]]--;

		if (ships[field[x][y]] == 0) {
			result = 2; //потоплен
			count_ships--;
			index = field[x][y];
			field[x][y] = -3;
		}
		else {
			result = 1; //подбит
			field[x][y] = -2;
		}

	}
	else if (field[x][y] == -1) {
		result = 0;    //промах
	}
	else {

		field[x][y] = -1;
	}

	fog[x][y] = 1;
	count_shots++;
	return result;
}

void autoFill(int field[N][N], int& x, int& y, int fog[N][N]) {

	int tempX{}, tempY{};

	if (x > 0 && y > 0) {
		if (field[x - 1][y - 1] == 10) {
			field[x - 1][y - 1] = -1;
			fog[x - 1][y - 1] = 1;
		}
		else if (field[x - 1][y - 1] == -2) {
			field[x - 1][y - 1] = -3;
			tempX = x - 1;
			tempY = y - 1;
		}
	}
	if (x > 0) {
		if (field[x - 1][y] == 10) {
			field[x - 1][y] = -1;
			fog[x - 1][y] = 1;
		}
		else if (field[x - 1][y] == -2) {
			field[x - 1][y] = -3;
			tempX = x - 1;
			tempY = y;
		}
	}
	if (x > 0 && y < N - 1) {
		if (field[x - 1][y + 1] == 10) {
			field[x - 1][y + 1] = -1;
			fog[x - 1][y + 1] = 1;
		}
		else if (field[x - 1][y + 1] == -2) {
			field[x - 1][y + 1] = -3;
			tempX = x - 1;
			tempY = y + 1;
		}
	}
	if (x < N - 1 && y > 0) {
		if (field[x + 1][y - 1] == 10) {
			field[x + 1][y - 1] = -1;
			fog[x + 1][y - 1] = 1;
		}
		else if (field[x + 1][y - 1] == -2) {
			field[x + 1][y - 1] = -3;
			tempX = x + 1;
			tempY = y - 1;
		}
	}
	if (x < N - 1) {
		if (field[x + 1][y] == 10) {
			field[x + 1][y] = -1;
			fog[x + 1][y] = 1;
		}
		else if (field[x + 1][y] == -2) {
			field[x + 1][y] = -3;
			tempX = x + 1;
			tempY = y;
		}
	}
	if (x < N - 1 && y < N - 1) {
		if (field[x + 1][y + 1] == 10) {
			field[x + 1][y + 1] = -1;
			fog[x + 1][y + 1] = 1;
		}
		else if (field[x + 1][y + 1] == -2) {
			field[x + 1][y + 1] = -3;
			tempX = x + 1;
			tempY = y + 1;
		}
	}
	if (y > 0) {
		if (field[x][y - 1] == 10) {
			field[x][y - 1] = -1;
			fog[x][y - 1] = 1;
		}
		else if (field[x][y - 1] == -2) {
			field[x][y - 1] = -3;
			tempX = x;
			tempY = y - 1;
		}
	}
	if (y < N - 1) {
		if (field[x][y + 1] == 10) {
			field[x][y + 1] = -1;
			fog[x][y + 1] = 1;
		}
		else if (field[x][y + 1] == -2) {
			field[x][y + 1] = -3;
			tempX = x;
			tempY = y + 1;
		}
	}
	x = tempX;
	y = tempY;
}

bool enter_coord(int& exit, int& x, string symbol, int& y) {

	while (true) {

	bool mistake = 0;

		                                             //кириллица стр                       кириллица заглав                цифры
	while ((!(cin >> symbol)) || !((symbol[0] >= -32 && symbol[0] <= -22) || (symbol[0] >= -64 && symbol[0] <= -54) || (symbol[0] >= 48 && symbol[0] <= 58)) || 
		(symbol[0] != '1' && symbol[1] == '0')  || (symbol[0] == '1' && (symbol[1] > '0' && symbol[1] <= '9'))) {

			if (!((symbol[0] >= -32 && symbol[0] <= -22) || (symbol[0] >= -64 && symbol[0] <= -54) || (symbol[0] >= 48 && symbol[0] <= 58)) || 
				(symbol[0] != '1' && symbol[1] == '0') || (symbol[0] == '1' && (symbol[1] > '0' && symbol[1] <= '9'))) {
				cout << "     Ќеправильна€ перва€ координата \n";
				mistake = 1;
				break;
			}
			
			cin.clear();
			cin.ignore();
		};

		if (mistake == 1)
			continue;

		if (symbol[0] == '0') {
			exit = 0;
			return 1;
		}

		if      (symbol[0] == 'б' || symbol[0] == 'Ѕ' || symbol[0] == '2') x = 1;
		else if (symbol[0] == 'в' || symbol[0] == '¬' || symbol[0] == '3') x = 2;
		else if (symbol[0] == 'г' || symbol[0] == '√' || symbol[0] == '4') x = 3;
		else if (symbol[0] == 'д' || symbol[0] == 'ƒ' || symbol[0] == '5') x = 4;
		else if (symbol[0] == 'е' || symbol[0] == '≈' || symbol[0] == '6') x = 5;
		else if (symbol[0] == 'ж' || symbol[0] == '∆' || symbol[0] == '7') x = 6;
		else if (symbol[0] == 'з' || symbol[0] == '«' || symbol[0] == '8') x = 7;
		else if (symbol[0] == 'и' || symbol[0] == '»' || symbol[0] == '9' || symbol[0] == 'й' || symbol[0] == '…') x = 8;
		else if (symbol[0] == 'к' || symbol[0] == ' ') x = 9;
		else if (symbol[0] == '1' && symbol[1] == '0') x = 9;
		else if (symbol[0] == 'а' || symbol[0] == 'A' || symbol[0] == '1') x = 0;


		while (!(cin >> y) || y < 0 || y > 10) {
			cin.clear();
			cin.ignore();

			if (y < 0 || y > 10)
				cout << "     Ќеправильна€ втора€ координата\n";
			mistake = 1;
			break;
		};

		if (mistake == 1)
			continue;

		if (y == 0) {
			exit = 0;
			return 1;
		}
		y--;
		return 0;
	}
}

void artificial_intelligence(bool& mode, int& xBot, int& yBot, int field[N][N],
	int& resultShot, int fog[N][N], int  ships[N], int& index, const int shipsConst[N],
	int& firstShotX, int& firstShotY, int& dir, int& count_ships, int& count_shots, int player) {
	if (mode == 0) {

		do {
			xBot = rand() % N;
			yBot = rand() % N;
		} while (!(field[yBot][xBot] >= 0 && field[yBot][xBot] <= N));

		cout << xBot + 1 << ' ' << yBot + 1<<endl;


		resultShot = shot(field, fog, yBot, xBot, ships, index, count_ships, count_shots);

		if (resultShot == 2) { //автозаполнение €чеек вокруг потопленого корабл€

			for (int i = 0; i < shipsConst[index]; i++) {
				autoFill(field, yBot, xBot, fog);
			}
		}
		xBot += yBot;
		yBot = xBot - yBot;
		xBot -= yBot;

		if (resultShot == 1) {
			mode = 1;
			firstShotX = xBot;
			firstShotY = yBot;
		}

	}
	else if (mode == 1) {
		cout << xBot << ' ' << yBot << endl;
		if (dir == 0) {
			if (xBot > 0) {
				xBot--;
				if (field[xBot][yBot] == -1) {
					dir = 1;
					xBot = firstShotX + 1;
				}
			}
			else {
				dir = 1;
				xBot = firstShotX + 1;
			}
		}
		else if (dir == 1) {
			if (xBot < N - 1) {
				xBot++;
				if (field[xBot][yBot] == -1) {
					dir = 2;
					xBot = firstShotX;
					if (yBot > 0)
						yBot = firstShotY - 1;
					else {
						dir = 3;
						yBot = firstShotY + 1;
					}
				}
			}
			else {
				dir = 2;
				if (yBot > 0)
					yBot = firstShotY - 1;
				else {
					dir = 3;
					yBot = firstShotY;
				}
			}
		}
		else if (dir == 2) {
			if (yBot > 0) {
				yBot--;
				if (field[xBot][yBot] == -1) {
					dir = 3;
					yBot = firstShotY + 1;
				}
			}
			else {
				dir = 3;
				yBot = firstShotY + 1;
			}
		}
		else if (dir == 3) {
			if (yBot < N - 1) {
				yBot++;
			}
			else {
				dir = 0;
				mode = 0;
			}
		}

		resultShot = shot(field, fog, xBot, yBot, ships, index, count_ships, count_shots);

		if (resultShot == 0) {
			dir++;
			xBot = firstShotX;
			yBot = firstShotY;
		}
		else if (resultShot == 2) {
			mode = 0;
			dir = 0;

			for (int i = 0; i < shipsConst[index]; i++) {
				autoFill(field, xBot, yBot, fog);
			}
		}
	}
};

void total_time(int& hours, int& minuts, int& seconds, int total) {
	hours = total / 3600;
	total %= 3600;
	minuts = total / 60;
	total %= 60;
	seconds = total;
}
