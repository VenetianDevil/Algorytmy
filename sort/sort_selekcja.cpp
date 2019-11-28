#include <iostream>

using namespace std;

int main()
{
	int tab[]= {10, 3, 2, 6, 1, 4, 7, 8, 5, 9};
	int leng = sizeof(tab)/sizeof(int);
	int a =0;
	int from;
	for(int i=0; i<leng; i++)
	{
		a = tab[i];
		for(int j=i+1; j<leng; j++)
		{
			if(a>tab[j])
			{
				a = tab[j];
				from = j;
			}
		}

		int temp = tab[i];
		tab[i] = a;

		for(int k=i+1; k<=from; k++)
		{
			a = tab[k];
			tab[k]= temp;
			temp = a;
		}
	}

	for(int i=0; i<leng; i++)
	{
		cout << tab[i] << endl;
	}
}
