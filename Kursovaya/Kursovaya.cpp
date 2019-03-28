﻿#include "pch.h"
#include <iostream>
#include <conio.h>
#include "Sea_Battle.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77


int ** set_0(int **array) {
	for (int i = 0; i < 10; i++) {
		array[i] = new int[10];
		for (int j = 0; j < 10; j++) { array[i][j] = 0; } //собственно, поля
	}
	return array;
}

void simple_vivod (int **array, const char alphabet[10], int i) {
	for (int j = 0; j < 12; j++) {
		if (i == 0 && j >= 2) { cout << alphabet[j - 2] << " ";  }
		else if (i == 1) { break; }
		else if ((i > 1 && j == 1) || (i == 0 && j < 2)) { cout << "  "; }
		else if ( i > 1 && j == 0) { 
			if (i-1 != 10) {cout << i - 1 << " ";}
			else { cout << i - 1; }	
		}
		else {
			switch (array[i-2][j-2]) {
			case 0:
				cout << ". ";
				break;
			case 1:
			case 2:
			case 3:
			case 4:
				cout << array[i-2][j-2] << " ";
				break;
			case -1:
				cout << "o "; 
				break;
			case (-2):
				cout << "x ";
				break;
			}
		}
	}
}

void vivod(int **array_1, int **array_2, const char alphabet[10]) {
	cout << endl; //отступ от границы сверху
	for (int i = 0; i < 12; i++) {
		cout << "        "; //отступ от границы слева 
		simple_vivod(array_1, alphabet, i);
		cout << "           ";
		simple_vivod(array_2, alphabet, i);
		cout << endl;
	}
	cout << endl << endl << endl; //отступ снизу
}


void rezim(int **array, const char alphabet[10]) {
	cout << endl;
	for (int i = 0; i < 12; i++) {
		cout << "                        "; //отступ от границы слева 
		simple_vivod(array, alphabet, i);
		cout << endl;
	}
	cout << endl << endl << endl;
	cout << "     Это режим расстановки ваших кораблей." << endl;
	cout << "     Введите точку (например, D4), где хотите поставить 'голову' корабля, " << endl;
	cout << "     а затем укажите стрелочкой направление тела корабля." << endl << endl;
}

int ** ras(int **array, const char alphabet[10]) {
	int ships[4] = { 1, 2, 3, 4 };
	int ship_count = 0;
	while (true) {
		int number = 0;
		int number_letter;
		char letter;

		rezim(array, alphabet);

		if (ships[ship_count] == 0) {
			ship_count += 1;
		}
		int ship_length = 0;
		if (ships[ship_count] > 0) {
			switch (ship_count) {
			case 0: 
				ship_length = 4;
				cout << "     Сейчас расположите линкор: ";
				break;
			case 1:
				ship_length = 3;
				cout << "     Сейчас расположите крейсер: ";
				break;
			case 2:
				ship_length = 2;
				cout << "     Сейчас расположите эсминец: ";
				break;
			case 3:
				ship_length = 1;
				cout << "     Сейчас расположите катер: ";
				break;
			}
			ships[ship_count] -= 1;	
		}

		cin >> letter >> number;
		number -= 1;
		number_letter = letter - 'A';
		array[number][number_letter] = ship_length;

		system("cls");
		rezim(array, alphabet);

		if (ship_length != 1) {
			cout << "     Теперь введите направление расположения корабля стрелкой : ";
			cout << endl;
			int KeyStroke;
			KeyStroke = _getch();

			if (KeyStroke == 224)
			{
				KeyStroke = _getch(); // Even though there are 2 getch() it reads one keystroke
				switch (KeyStroke)
				{
				case UP_ARROW:
					for (int i = 1; i < ship_length; i++) {
						array[number - i][number_letter] = ship_length;
					}
					break;
				case DOWN_ARROW:
					for (int i = 1; i < ship_length; i++) {
						array[number + i][number_letter] = ship_length;
					}
					break;
				case LEFT_ARROW:
					for (int i = 1; i < ship_length; i++) {
						array[number][number_letter - i] = ship_length;
					}
					break;
				case RIGHT_ARROW:
					for (int i = 1; i < ship_length; i++) {
						array[number][number_letter + i] = ship_length;
					}
					break;
				default:
					cout << "Some other key." << endl;
				}
			}
			else cout << KeyStroke << endl;

		}
		
		//system("pause");
		system("cls");
		if (ships[ship_count] == 0 && ship_count == 3) {
			cout << endl;
			for (int i = 0; i < 12; i++) {
				cout << "                        "; //отступ от границы слева 
				simple_vivod(array, alphabet, i);
				cout << endl;
			}
			cout << endl << endl << endl;
			cout << endl<< "Расстановка окончена! Приступим к игре." << endl;
			system("pause");
			break;
		}
	}
	return array;
}

int main()
{

	setlocale(LC_ALL, "Russian");
	const char alphabet[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	int ** self_zones = new int*[10];
	int ** enemy_zones = new int*[10];
	self_zones = set_0(self_zones);
	enemy_zones = set_0(enemy_zones);

	ras(self_zones, alphabet);
	
	//vivod(self_zones, enemy_zones, alphabet);
}
