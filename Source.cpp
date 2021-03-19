#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;

constexpr auto maxi = 24;
struct place
{
	int x, y;
};
int control() // dieu khien
{
	int press = _getch();
	switch (press)
	{
	case 119:return 2;
	case 115: return 4;
	case 97:return 1;
	case 100: return 3;
	}
	return 0;
}
void move(int coman,place&pos) // di chuyen xe
{
	switch (coman)
	{
	case 1:
	{
		if (pos.x - 1 >= -1) pos.x--;
		break;
	}
	case 2:
		if (pos.y - 1 >= 0) pos.y--; break;
	case 3:
		if (pos.x + 1 <= maxi / 3) pos.x++; break;
	case 4: 
		if (pos.y + 1 < maxi) pos.y++; break;
	}
}
int randomcar() // khoi tao xe ngau nhien
{
	return  rand() % (maxi / 3 ) ;
}
void carrun(int**& a,int hard) // xe chay tren mang
{
		for (int i = 0; i < maxi / 3; i++)
		{
			for (int j = maxi - 1; j >= 1; j--)
			{
				a[i][j] = a[i][j - 1];
			}
			a[i][0] = 0;
		}
		for (int i = 0; i < hard;i++)
		{
			a[randomcar()][0] = 1;
		}
}
int board(int**& a,place pos,int hard) //ham nay display ra man hinh (xe va mang)
{
	carrun(a,hard);
	if (pos.x != -1 && pos.x != maxi / 3)
	{
		if (a[pos.x][pos.y] != 0) return 0;
	}
	if (pos.x == maxi / 3)return 2;
	for (int j = 0; j < maxi; j++)
	{
		for (int i = -1; i <= maxi / 3; i++)
		{
			if (i == pos.x && j == pos.y)
			{
				cout << "| * ";
			}
			else
			{
				if (i != -1 && i != maxi / 3)
				{
					if (a[i][j] == 0)
					{
						cout << "|   ";
					}
					else
					{
						if (a[i][j] == 1)
						{
							cout << "|000";
						}
					}
				}
				else
				{
					cout << "|   ";
				}
			}
		}
			cout <<"|"<< endl;
	}
	return 1;
} // 
void reset(int**& a) // reset mang thanh so 0
{
	for (int i = 0; i < maxi / 3; i++)
	{
		memset(a[i], 0, maxi * sizeof(int));
	}
}
void create(int**& a) // cap phat dong mang 2 chieu
{
	a = new int* [maxi / 3];
	for (int i = 0; i < maxi / 3; i++)
	{
		a[i] = new int[maxi];
	}
}
void release(int**& a)  // giai phong mang
{
	for (int i = 0; i < maxi / 3; i++)
	{
		delete[] a[i];
	}
	delete[]a;
}
int aimove(int** a, place pos) // may choi
{
	if (pos.x + 1 == maxi / 3)
	{
		return 3;
	}
	else
	{
		if (pos.x == -1)
		{
			if (a[pos.x + 1][pos.y] == 0 && a[pos.x + 1][pos.y - 1] == 0) { return 3; }
		}
		else
		{
			if (a[pos.x + 1][pos.y] == 0 && a[pos.x + 1][pos.y - 1] == 0) { return 3; }
			else
			{
				if (a[pos.x][pos.y - 1] != 0)
				{
					if (pos.x - 1 == -1) { return 1; }
					else
					{

						if (a[pos.x - 1][pos.y] == 0)
						{
							return 1;
						}
						else
						{
							return 4;
						}
					}
				}
			}
		}
	}
	
}
int hardmenu() // menu chon do kho
{
	system("cls");
	cout << "1.easy " << endl;
	cout << "2.medium" << endl;
	cout << "3.hard" << endl;
	cout << "4.supa hard" << endl;
	cout << "0.back" << endl;
	return 0;
}
int hardchose(int lenh) // chon do kho
{
	do 
	{
		lenh = _getch();
		lenh -= 48;
	} while (lenh < 0 || lenh >4);
	return lenh;
}
int play(int playmode,int hard) // ham game play
{
	int** a;
	while (1)
	{
		system("cls");
		create(a);
		reset(a);
		place pos;
		pos.x = -1;
		if (playmode == 1) {
			pos.y = maxi / 2;
		}
		else
		{
			pos.y = 2;
		}
		int coal = 1;
		char key;
		while (1)
		{
			system("cls");
			coal = board(a, pos,hard);
			if (playmode == 1)
			{
				if (_kbhit()) { move(control(), pos); }
			}
			else
			{
				move(aimove(a,pos), pos);
			}
			if (coal == 0 || coal == 2) break;
			else
			{
				Sleep(50);
				
			}
		}
		switch (coal)
		{
		case 0: cout << " You lose  " << endl; break;
		case 2: cout << " You win " << endl; break;
		}
		
			cout << "Press r to play again" << endl;
			cout << "Press e to exit" << endl;
			do
			{
				key = _getch();
			} while (key != 'r' && key != 'e');
			if (key == 'e')break;
		
	}
	release(a);
	return 0;
}
int menu() // menu chinh
{
	cout << "1.NEW GAME" << endl;
	cout << "2.AI" << endl;
	cout << "0.EXIT" << endl;
	return 0;
}
int nhaplenh(int lenh) // chon lenh menu chinh
{
	int temp;
	do
	{
		temp = _getch();
		
	} while (temp > 2+48 || temp < 0+48);
	return temp-48;
}
int xuly(int lenh) // xu ly chon lenh
{
	int chose;
	switch (lenh)
	{
	case 1: chose = hardchose(hardmenu()); if (chose!=0) play(1,chose); return 1; break;
	case 2: chose = hardchose(hardmenu()); if (chose != 0) play(2,chose); return 2; break;
	}
	return 0;
}
int main()
{
	int lenh = 1;
	do
	{
		system("cls");
		lenh = xuly(nhaplenh(menu()));
	} 	while (lenh != 0);
	return 0;
}