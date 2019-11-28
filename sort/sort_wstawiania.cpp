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
		if(tab[0]>a)
		{				
			from = 0;
		}
		else
		{
			for(int j=1; j<i+1; j++)
			{
				if(a>tab[j-1] && a<tab[j])
				from = j;				
			}
		}		
		
		for(int j=from; j<=i; j++)
		{
			int temp = tab[j];
			tab[j] = a;
			a = temp;
		}
		
	}

	for(int i=0; i<leng; i++)
	{
		cout << tab[i] << endl;
	}


}
