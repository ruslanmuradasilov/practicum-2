#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int monotone_check(const char *sf, const char *sff)
{
	int i, k, n, length, t = 0, rtn;
	char *m;
	FILE *in;
	in = fopen(sf, "r");
	fscanf(in, "%d", &k);
	fscanf(in, "%d", &n);
	length = pow((long double)k, n);//длина вектора значений 
	m = (char*)malloc(length*sizeof(char));
	fscanf(in, "%c", &m[0]);//считываем пробел
	for(i = 0; i < length; i++)
		fscanf(in, "%c", &m[i]);
	fclose(in);

	while(length > 0)
	{
		length /= k;//разбиваем длину на k частей
		for(i = 0; i < length; i++)
		{
			if((m[i] - '0') > (m[i + length] - '0'))//проверка на немонотонность 
			{
				t = 1;//немонотонна
				break;
			}
		}
		if(t == 1) rtn = 0;
		if(length == 1) rtn = 1;//монотонна
	}

	FILE *out;
	out = fopen(sff, "w");
	fprintf(out, "%d", rtn);
	free(m);
	fclose(out);
	return 0;
}

int main(int argc, char* argv[])
{
	/*if(argc > 1)*/
		return monotone_check("in.txt", "out.txt");
	/*else return -1;*/
}