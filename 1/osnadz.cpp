#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int osem;
    cout << "podaj w osemkowym: " << endl;
    cin >> osem;

    int r=0;
    int i=0;
    int wynik;
    while(osem>1)
    {
	r=osem%10;
	wynik=wynik+r*pow(8, i);
	osem=(osem-r)/10;
	i++;
    }

    cout << "w sys. dziesietnym to: " << wynik << endl;
}