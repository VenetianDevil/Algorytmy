 #include <iostream>
using namespace std;

const int N=1000;

//implementacja lisy z usuwaniem duplikatów
class Lista
{	
	public:
	int tablica[N];
	int last = 0;

	Lista()
	{}
	
 //zwraca index 1 elementu
	int First()
	{
		return 0;
	}

//zwraca index za ostatnim elemenetem
	int End()
	{
		int i=0;
		while(tablica[i]!=0 && i<N) // trzeba zalozyc, ze 0 nie moze byc wartoscia
		{
			i++;
		}
		if(i==N)
		return -1;
		else
		{
			last = i-1;
			return i;
		}
	}

//zwraca index nastepnego el. po p (p+1); jesli nastepny el nie istnieje zwroz -1
	int Next(int p) const
	{
		for(int i=0; i<N; i++)
		{
			if(tablica[i]==p)
			{
				if(i<N-1)
				{
					return i+1;
				}
			}
		}
		return -1;
	}

//wraca index poprzedniego el; jak nie istnieje zwraca -1
	int Previous(int p) const
	{
		for(int i=0; i<N; i++)
		{
			if(tablica[i]==p)
			{
				if(i>0)
				{
					return i-1;
				}
			}
		}
		return -1;
	}

//wstawia x do komorki p
	bool Insert(int x, int p)
	{
		if(End()==-1) //sprawdza czy tablica jest pelna
		return false; //jak Tak to zwracam false bo nie moge juz nic dodac

		if(p<0 || p>N-1) //czy p miesci sie w zakresie tablicy
		return false; //jesli taki index nie istnieje zwracam false

		int temp;
		for(int j=p; j<N; j++)
		{
			temp = tablica[j];
			tablica[j]=x;
			x = temp;
		}

		last++; //zwiekszam last
		return true;
	}

// Usuwa p-ty element listy.
    bool Delete(int p)   
	{
		if(p<0 || p>N-1)
		return false;
	
		for(int j=p; j<N; j++)
		{
			tablica[j]=tablica[j+1];
		}
		last--;
		return true;	
	}


//Zwraca pozycje elementu w liscie jesli x wystepuje
	int Locate(int x)
	{
		for(int i=0; i<=last; i++)
		{
			if(tablica[i]==x)
			{
				return i;
			}
		}
		return End();
	}

// Zwraca wartosc z n-tego elementu listy.
   	int Retrive(int p) const
	{
		if(p<0 || p>N-1)
		return false;

		return tablica[p];
	}


	void DeleteDuplicates()
	{
		int checking=0;
		for(int i=0; i<=last; i++)
		{
			checking = tablica[i];
			for(int j=i+1; j<=last; j++)
			{
				if(checking==tablica[j])
				{
					for(int k=j; k<=last; k++)
					{
						tablica[k]=tablica[k+1];
					}
				}
			}
		}
	}
	
};

int main()
{
	Lista list;

	int first = list.First();
	int end = list.End();
	list.Insert(122, 0);
	list.Insert(143, 1);
	list.Insert(175, 2);
	int next = list.Next(143);
	int prev = list.Previous(122);

	cout << "First-0 " << first <<"\tEnd-0 " << end << "\tNext-2 " << next << "\tPrev-(-1) " << prev << endl;

	end = list.End();
	prev = list.Previous(143);

	cout << "End-3 " << end << "\tPrev-0 " << prev << endl;

	list.Insert(155, 1);
	prev = list.Previous(143);
	int loc = list.Locate(175);
	int ret = list.Retrive(1);
	list.Insert(143, 4);
	end = list.End();

	cout << "End-5 " << end << "\tPrev-1 " << prev << "\tloc-3 " << loc << "\tRet-155 " << ret << endl;

	list.Delete(0);
	ret = list.Retrive(0);

	cout << "ret=155 " << ret << endl;

	list.DeleteDuplicates();
	end = list.End();

	cout << "End-3 " << end << endl;

}