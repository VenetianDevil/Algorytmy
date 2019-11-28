#include <iostream>
#include <cmath>

using namespace std;

//silnia; rekurencja ogonowa
int silnia(int n, int res)
{
	if(n==1||n==0)
	{	
		return res;
	}
	else
	{res = n * res;
	//cout << res << endl;
	n--;
	return silnia(n, res);}
}

int main()
{
	int n =0;
	cout << "Wartosc do silni: " << endl;
	cin >> n;

	//rekurencyjnie
	cout << "rekurencyjnie: " << silnia(n, 1) << endl;

	//iteracyjnie
	int silnia =1;
	for(int i=1; i<=n; i++)
	{
		silnia = silnia * i;
	}

	cout << "iteracyjnie: " << silnia << endl;
}
