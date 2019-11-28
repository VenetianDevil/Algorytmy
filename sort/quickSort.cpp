#include <iostream>
using namespace std;

//Quick Sort
void sort(int left, int right, int tab[])
{
	int Pivot = tab[left];
	cout << Pivot<< endl;

	int i = left; //pivot place
	for(int j=i+1; j<=right; j++ )
	{
		cout << tab[j] << endl;
		if(tab[j]<Pivot)
		{
			i++;
			cout << "i = " << i << endl;
			cout << "zamieniam " << tab[j] << " i " << tab[i] << endl <<endl;
			swap(tab[j], tab[i]);
		}
		else
		{
			cout << "Nic nie robie. jestem przy j = " << j <<" i = " << i << endl << endl;
		}
	}
	swap(tab[left], tab[i]);

	if(i-1-left>0)
	sort(left, i-1, tab);

	if(right-i-1>0)
	sort(i+1, right, tab);
}

int main()
{
	int tab[9] = {40, 10, 20, 80, 60, 70, 30, 50, 90};
	int left = 0;
	int right = 8; //sizeof(tab)/sizeof(int);

	int P = tab[0];
	
	sort(left, right, tab);

	for(int k=0; k<9; k++)
	{
		cout << tab[k] << '\t';
	}
	cout << endl;
}