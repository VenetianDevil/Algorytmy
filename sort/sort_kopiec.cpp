#include <iostream>

using namespace std;

int main()
{
	int tab[7] = {7, 5, 9, 6, 7, 8, 10};
	int kopiec[8];
	int k = 0; //do skakania po kopcu
	int swaps;
	kopiec[0] = 0;		
	for(int i=1; i<=7; i++)
	{
		kopiec[i] = tab[i-1];
		cout << "dodalem " << tab[i-1] << endl;
		k=i;
		swaps = 1;
		while(swaps==1)
		{
			swaps = 0;
			if(k%2 == 0)
			{
				if(kopiec[k]>kopiec[k/2])
				{
					swap(kopiec[k], kopiec[k/2]);
					k = k/2;
					swaps = 1;
					cout << "swap " << k << " " << k/2 << endl; 
				}
				else
					cout << "nic" << endl; 
			}	
			else
			{
				if(kopiec[k]>kopiec[(k-1)/2] && k!=1)
				{
					swap(kopiec[k], kopiec[(k-1)/2]);
					k = (k-1)/2;
					swaps = 1;
					cout << "swap " << k << " " << (k-1)/2 << endl;
				}
				cout << "nic" << endl;
			}	
		}
		cout << endl;
	}


	for(int i=1; i<8; i++)
	{
		cout << kopiec[i] << "\t";
	}
	cout << endl;
}
