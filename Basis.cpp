#include <string>
#include <fstream>

using namespace std;

int basis_check(const char *in, const char *out)
{
	ifstream Cin(in);
	ofstream Cout(out);
	
	int i, j, t, k, n;//переменные для входных данных и циклов
	int p = 0, l = 0, c = 0, kp, length, rtn = 1;//счетчики и длина вектора значений
	Cin >> t;
	string *m = new string[t];

	int **table = new int*[t];//двумерный массив для таблицы
	for(i = 0; i < t; i++)
		table[i] = new int [5];
	for(i = 0; i < t; i++)
		for(j = 0; j < 5; j++)
			table[i][j] = 0;

	for(i = 0; i < t; i++)
	{
		Cin >> k >> n;
		Cin >> m[i];
		length = 1 << n;

		if(m[i][0] == '0') table[i][0] = 1;//проверка на принадлежность функции классу T0

		if(m[i][length - 1] == '1') table[i][1] = 1;//проверка на принадлежность функции классу T1

		p = 0, c = 0; l = 0; 
		while (length > 1)
		{
			length /= 2;//делим вектор значений пополам и проверяем на совпадение либо отрицание, то есть фиктивность переменной либо линейную зависимость функции от нее
			for (j = 0; j < length; j++)
				if (m[i][j] == m[i][j + length]) p++;
			if (p == length)
			{
				l++;//кол-во фиктивных переменных
				p = 0;
			} 
			else 
			{
				p = 0;
				for (j = 0; j < length; j++)
					if(m[i][j] != (m[i][j + length])) p++;
        		if(p == length)
				{
					c++;
					p = 0;
				} 
				else
				{
					c = 0;//нелинейная
					break;
				}
			}
		}
		if((l == n) || (c != 0)) table[i][2] = 1;//проверка на принадлежность функции классу L

		length = 1 << n;
		for(j = 0; j < length/2; j++)
		{
			if(m[i][j] == '0' && m[i][length-1-j] == '1' || m[i][j] == '1' && m[i][length-1-j] == '0') continue;//проверяем противоположные наборы
			else break;
		}
		if(j == length/2) table[i][3] = 1;//проверка на принадлежность функции классу S
		
		p = 0;
		while(length > 0)
		{
			length /= 2;//разбиваем вектор значений пополам
			for(j = 0; j < length; j++)
			{
				if((m[i][j] - '0') > (m[i][j + length] - '0'))//проверка на немонотонность по соседним наборам
					{
						p = 1;
						break;//немонотонна		
					}
			}
			if(p == 1) break;
			if(length == 1) table[i][4] = 1;//проверка на принадлежность функции классу M 
		}
	}

	for(i = (-1); i < t; i++)//без какой ф-ии проверяем систему на полноту, при i = -1  - проверяем всю таблицу на полноту
	{
		rtn = 1;
		for(j = 0; j < 5; j++)//в каком столбце считаем количество +
		{
			kp = 0;//количество +
			
			for(l = 0; l < t; l++)//какую ячейку в столбце j проверяем на наличие +
			{
				if(l != i)//не проверяем строку с номером i
					if(table[l][j] == 1) kp++;
			}
			
			if(i != (-1) && kp == t - 1)//система перестает быть полной, если убрать одну функцию
				break;

			/* Если даже с выкинутой ф-ией система полна, то эта система не базис. Или если вся система не полна, то она тоже не базис*/
			if((i != (-1) && kp != t - 1 && j == 4) || (i == (-1) && kp == t))
				{
					rtn = 0;//не базис
					break;
				 }
		}

		if(rtn == 0) break;//не базис
	}

	Cout << rtn;
	delete[] m;
	delete[] table;
	return 0;
}

int main(int argc, char* argv[])
{
	if(argc > 1)
		return basis_check(argv[1], argv[2]);
	else return -1;
}