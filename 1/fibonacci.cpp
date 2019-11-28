#include <iostream>
#include <cstdlib>

using namespace std;

//obliczanie n-tego wyrazu ciągu Fibonacciego
int fibonacci(int n)
{
	if(n<2)
	return 1;
	
	return fibonacci(n-1)+fibonacci(n-2);
}

int main()
{
	int n;
	cout << "podaj ktory wyraz mam obliczyc: " << endl;
	cin >> n;

	int pi = 1;
	int dr = 1;
	int temp = 0;

	for( int i=2; i<=n; i++)
	{
		temp = pi + dr;
		pi = dr;
		dr = temp;
	}

	cout << "iteracyjnie: " << dr << endl;

	cout << "rekurencyjnie: " << fibonacci(n) << endl;
	
}
