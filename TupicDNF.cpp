#include <fstream>
#include <string>

using namespace std;

void tdnf_cout(int **table, int *p, int t, int n, string *m, string *td, const char *out);

int tdnf(const char *in, const char *out)
{
	ifstream Cin(in);
	ofstream Cout(out);
	int n, t, i, j, l, a = 1, k = 0;
	string temp;

	Cin >> n >> t;
	
	string *m = new string[t];//������, ������� ������ ����������
	string *mm = new string[1 << n];//������ ��� ������� ����������
	if (t == 1)//���� ��� = ����
	{
		Cin >> m[0];
		Cout << n << " " << t << endl;
		Cout << m[0];
		return 0;
	}
	if(t == 0)//���� ��� = 0
	{
		Cout << n << " 0";
		return 0;
	}
	
	//������� � ������ mm ������� ����������
	string str = "", str1 = "";
	for(i = 0; i < n; i++)
	{
		str += '0';//00...0
		str1 += '1';//11...1
	}

	l = 0;
	while(1)
	{
		mm[l] = str;
		if(str[n - 1] == '0') 
			str[n - 1] ='1';
		else
		{
			 if(str == str1) break;//������� ���������
		     for(i = n - 1; i >= 0; i--)
			 {
				 if(str[i] == '0') 
				 {
						    str[i] = '1';
							for(j = n - 1; j > i; j--)
								 str[j] = '0';
							 break;
				 }
			 }
		}
		l++;
	}


	int **table = new int*[t];//��������� ������ ��� ������� ��������
	for(i = 0; i < t; i++)
		table[i] = new int [1 << n];
	for(i = 0; i < t; i++)
		for(j = 0; j < 1 << n; j++)
			table[i][j] = 0;

	for(i = 0; i < t; i++)//��������� ����������
			Cin >> m[i];

	for(i = 0; i < t; i++)//��������� ������� ��������
		{
			for(j = 0; j < 1 << n; j++)
			{
				a = 1;
				for(l = 0; l < n; l++)
				{
					if(m[i][l] == '*') continue;
					if(m[i][l] == mm[j][l])
						continue;
					else
					{
						a = 0;
						break;
					}
				}
				table[i][j] = a;
			}
		}

	int *p = new int[t];//������� ����������� ������ �� �����������, ������� �� �������
	for(i = 0; i < t; i++)
		p[i] = 1;

	string *td = new string[t];//������, ������� ������ ����
	for(i = 0; i < t; i++)
		td[i] = "";

	tdnf_cout(table, p, t, n, m, td, out);

	for(i = 0; i < t; i++)//������������ ���� �����������������
		for(j = i; j < t; j++)
		{
			if(td[i].size() < td[j].size())//������� ������� ������
				a = td[i].size();
			else a = td[j].size();
			for(l = 0; l < a; l++)//���������� �����������
				{
					if ( ((td[i][l] == '*') && (td[j][l] != '*')) || ((td[i][l] == '1') && (td[j][l] == '0')) )
					{ 
						temp = td[i];
						td[i] = td[j];
						td[j] = temp;
						break;
					}
					if ( ((td[i][l] == '0') && (td[j][l] != '0')) || ((td[i][l] == '1') && (td[j][l] == '*')) )
						break;
				}
		}

	for(i = 0; i < t; i++)
		if(td[i] != "")
		{
			Cout << n << " " << td[i].size()/n << endl;
			for(j = 0; j < td[i].size(); j++)
			{
				Cout << td[i][j];
				if((j + 1) % n == 0)
					Cout << endl;
			}
		}
	delete[] m;
	delete[] mm;
	delete[] table;
	delete[] p;
	delete[] td;

	return 0;
}

void tdnf_cout(int **table, int *p, int t, int n, string *m, string *td, const char *out)
{
	int i, j, l, s = 0, spp = 0;
	string str = "";
	int *pp = new int[t];//������ ��� ����������� �� ������� ����������
	for(i = 0; i < t; i++)
		pp[i] = -1;
	
	for(i = t-1; i >= 0; i--)//����� ������� � ��������� ���������� �� ������� ��������
	{
		if(p[i] != 0)
		{
			s = 0;
			for(j = 0; j < 1 << n; j++)
			{
				if(table[i][j] == 1)
				{
					s = 0;
					for(l = t-1; l >= 0; l--)
					{
						if((l != i) && (p[l] != 0))
						{
							if(table[l][j] == 1)
								{
									s = 1;
									break;
								}
							else continue;
						}
					}
					if(s == 0) break;//���� ���������� �������
				}
			}
			if(s == 1)//���� ���������� �� �������, �� ����� ������
				{
					pp[spp] = i;
					spp++;//���-�� �� ������� ����������
				}
		}	
	}
	
	if(spp > 0)
	{
		s = 1;
		for(i = 0; i < spp; i++)//������� ��������� ���������� � ��������� ���������� ����-������� �� ����
			{
				p[pp[i]] = 0;
				tdnf_cout(table, p, t, n, m, td, out);
				p[pp[i]] = 1;
			}
	}
	
	if(s == 0)//��� ���������� �������
	{
		for(i = 0; i < t; i++)//�������� ���� � ������
			if(p[i] == 1)
				str += m[i];
		l = 0;
		while((str != td[l]) && (td[l] != ""))
			l++;
		td[l] = str;//��������� �� � ������ ����, ���� ����� �� ����
	}
}

int main(int argc, char* argv[])
{
	//if(argc > 1)
		return tdnf("in.txt", "out.txt");
	/*else return -1;*/
}
