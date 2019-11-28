#include <iostream>

using namespace std;

int main()
{
	int tab[]= {10, 3, 2, 6, 1, 4, 7, 8, 5, 9};
	int leng = sizeof(tab)/sizeof(int);
	int a =0;
	int m=100;	

	while(m!=0)
	{
		m=0;
		for(int i=0; i<leng-1; i++)
		{
			if(tab[i]>tab[i+1])
			{
				a = tab[i+1];
				tab[i+1] = tab[i];
				tab[i]=a;
				m++;
			}
		}		
	}


	for(int i=0; i<leng; i++)
	{
		cout << tab[i] << endl;
	}
}
