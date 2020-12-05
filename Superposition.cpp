#include <fstream>
#include <string>

using namespace std;

int superposition(const char *in, const char *out)
{
	ifstream Cin(in);
	ofstream Cout(out);

	int n1, n2, i, j, l, t, k, x1, x2;
	string str1 = "", str2 = "";
	
	Cin >> n1 >> str1;
	string *m1 = new string[n1 + 1];//вектора значений фи и пси А автомата
	for(i = 0; i < n1 + 1; i++)
	{
		Cin >> t >> t;
		Cin >> m1[i];
	}

	Cin >> n2 >> str2;
	string *m2 = new string[n2 + 1];//вектора значений фи и пси В автомата
	for(i = 0; i < n2 + 1; i++)
	{
		Cin >> t >> t;
		Cin >> m2[i];
	}

	string *m3 = new string[n1 + n2 + 1];//вектора значений фи и пси С автомата
	for(i = 0; i < n1 + n2 + 1; i++)
		m3[i] = "";

	for(j = 0; j < n1; j++)//функции фи в автомате С из автомата А
	{
		k = 0;//счетчик для четности дублирования
		for(l = 0; l < (1 << n1 + 1); l += 2)//берем по два значения из векторов значений фи автомата А
		{
			for(i = 0; i < (1 << n2 + 1); i++)//дублируем число раз, равное 2^состояния из автомата В + х
			{
				if(k % 2 == 0)
					m3[j] += m1[j][l];
				else
					m3[j] += m1[j][l+1];
				k++;
			}
		}
	}

	k = 0;
	for(l = 0; l < (1 << n1 + 1); l+=2)
	{
		x1 = m1[n1][l] - '0';//берем числа из вектора значений пси автомата А
		x2 = m1[n1][l+1] - '0';

		if(x1 == x2)
		{
			if(x1 == 0) k = -1;
			else k = 1;
			for(i = 0; i < n2 + 1; i++)//заполняем фи и пси автомата С по фи и пси автомата В
				for(j = 0; j < (1 << n2 + 1); j++)
				{
					if(x1 % 2 == j % 2)//так как вектор значений х = 0101...0101, то если х1 == 0 - берем пред значение, если х1 == 1 - след
						m3[i + n1] += m2[i][j];
					else
						m3[i + n1] += m2[i][j + k];
				}
			continue;
		}
		if(x1 == 0 && x2 == 1)
		{
			for(i = 0; i < n2 + 1; i++)
				for(j = 0; j < (1 << n2 + 1); j++)
					m3[i + n1] += m2[i][j];//так как вектор значений х = 0101...0101, то ,берем по 4 значения подряд
			continue;
		}
		
		for(i = 0; i < n2 + 1; i++)
			for(j = 0; j < (1 << n2 + 1); j++)
			{
				if(j % 2 == 0) k = 1;
				else k = -1;
				m3[i + n1] += m2[i][j+k];//так как вектор значений х = 0101...0101, то если j-неч - берем след значение, если j-чет - пред
			}	
	}

	Cout << n1 + n2 << " " << str1 + str2 << endl;
	for(i = 0; i < n1 + n2 + 1; i++)
		Cout << "2 " << n1 + n2 + 1 << " " << m3[i] << endl;

	delete[] m1;
	delete[] m2;
	delete[] m3;

	return 0;
}

int main(int argc, char* argv[])
{
	if(argc > 1)
		return superposition(argv[1], argv[2]);
	else return -1;
}