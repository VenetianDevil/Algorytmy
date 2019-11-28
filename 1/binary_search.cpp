#include <iostream>

using namespace std;

int tab[] = {1, 2, 5, 8, 9, 11, 15, 20};

//wyszukiwanie binarne; rekurencja
int szukanie(int szukana, int l, int p)
{
    int sr = (l+p)/2;

    if( tab[sr] == szukana)
    {
        return sr;
    }
    else if(l>p) // brak
        return -100;
    else if(tab[sr] > szukana)
    {
        return szukanie(szukana, l, sr-1);
    }
    else
    {
        return szukanie(szukana, sr+1, p);
    }
}

int main()
{
    int szukana = 3;
    //int tab[] = {1, 2, 5, 8, 9, 11, 15, 20};
    int l = 0;
    int p = 7;
    
    int pozycja = szukanie(szukana, l, p);

    cout << pozycja << endl;

}
