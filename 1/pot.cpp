#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	int a = 0;
	int p = 0;
	int wynik = 1;
	cout << "podaj liczbe i potege" << endl;
	cin >> a >> p;

	for(int i=0; i<p; i++)
	{
		wynik = wynik * a;
	}

	cout << "Wynik = " << wynik << endl;
}
