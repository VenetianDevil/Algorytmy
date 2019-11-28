#include <iostream>

using namespace std;

int main()
{
	int tab[] = {0, 1, 2, 3, 4, 5};
	int left = 0;
	int right = 5;
	int x = 4;
	
	int i = (left+right)/2;
	while(tab[i]!=x)
	{
		if(left==right+1)
			{cout << "brak" << endl;
			return 0;}
		else if(x< tab[i])
			right = i-1;
		else
			left = i+1;

		i = (left+right)/2;
	}

	cout << i << endl;
}
