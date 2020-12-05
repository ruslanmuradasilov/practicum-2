#include <string>
#include <fstream>

using namespace std;

int basis_check(const char *in, const char *out)
{
	ifstream Cin(in);
	ofstream Cout(out);
	
	int i, j, t, k, n;//���������� ��� ������� ������ � ������
	int p = 0, l = 0, c = 0, kp, length, rtn = 1;//�������� � ����� ������� ��������
	Cin >> t;
	string *m = new string[t];

	int **table = new int*[t];//��������� ������ ��� �������
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

		if(m[i][0] == '0') table[i][0] = 1;//�������� �� �������������� ������� ������ T0

		if(m[i][length - 1] == '1') table[i][1] = 1;//�������� �� �������������� ������� ������ T1

		p = 0, c = 0; l = 0; 
		while (length > 1)
		{
			length /= 2;//����� ������ �������� ������� � ��������� �� ���������� ���� ���������, �� ���� ����������� ���������� ���� �������� ����������� ������� �� ���
			for (j = 0; j < length; j++)
				if (m[i][j] == m[i][j + length]) p++;
			if (p == length)
			{
				l++;//���-�� ��������� ����������
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
					c = 0;//����������
					break;
				}
			}
		}
		if((l == n) || (c != 0)) table[i][2] = 1;//�������� �� �������������� ������� ������ L

		length = 1 << n;
		for(j = 0; j < length/2; j++)
		{
			if(m[i][j] == '0' && m[i][length-1-j] == '1' || m[i][j] == '1' && m[i][length-1-j] == '0') continue;//��������� ��������������� ������
			else break;
		}
		if(j == length/2) table[i][3] = 1;//�������� �� �������������� ������� ������ S
		
		p = 0;
		while(length > 0)
		{
			length /= 2;//��������� ������ �������� �������
			for(j = 0; j < length; j++)
			{
				if((m[i][j] - '0') > (m[i][j + length] - '0'))//�������� �� �������������� �� �������� �������
					{
						p = 1;
						break;//�����������		
					}
			}
			if(p == 1) break;
			if(length == 1) table[i][4] = 1;//�������� �� �������������� ������� ������ M 
		}
	}

	for(i = (-1); i < t; i++)//��� ����� �-�� ��������� ������� �� �������, ��� i = -1  - ��������� ��� ������� �� �������
	{
		rtn = 1;
		for(j = 0; j < 5; j++)//� ����� ������� ������� ���������� +
		{
			kp = 0;//���������� +
			
			for(l = 0; l < t; l++)//����� ������ � ������� j ��������� �� ������� +
			{
				if(l != i)//�� ��������� ������ � ������� i
					if(table[l][j] == 1) kp++;
			}
			
			if(i != (-1) && kp == t - 1)//������� ��������� ���� ������, ���� ������ ���� �������
				break;

			/* ���� ���� � ��������� �-��� ������� �����, �� ��� ������� �� �����. ��� ���� ��� ������� �� �����, �� ��� ���� �� �����*/
			if((i != (-1) && kp != t - 1 && j == 4) || (i == (-1) && kp == t))
				{
					rtn = 0;//�� �����
					break;
				 }
		}

		if(rtn == 0) break;//�� �����
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