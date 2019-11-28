#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Podaj n: " << endl;
    cin >> n;

    int srednia = 0;
    int i=1;
    int suma=0;
    int dana=0;

    for(i=1;i<=n; i++)
    {
	cin>>dana;
	suma=suma+dana;
    }

    srednia = suma/n;

    cout << "srednia wynosi: " << srednia << endl;
}