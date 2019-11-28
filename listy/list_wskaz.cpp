#include <iostream>
using namespace std;

typedef int element;
struct cell
{
    element el;
    cell * next;
};

class Lista
{
    protected:
        cell * header; // głowa listy
    public:
        Lista()    //konstruktor
	{
		header = nullptr;
	}        
	~Lista()  //destruktor
	{
		cell * p;
		
		while(header)
		{
			p = header->next;
			delete header;
			header = p;
		}       	
	}


// wstawia element x na pozycję next komórki o wskaźniku p (lub w przypadku pustej listy tworzy komórkę z elementem x w miejscu głowy listy)
        void Insert(element x, cell * p)
{
	if(header == nullptr)
	{
		cell* newHeader = new cell;
		newHeader->el = x;
		newHeader->next = NULL;
		header = newHeader;
	}
	else
	{ 
		cell* nowy = new cell;
		nowy->el = x;
		nowy->next = p->next;
		p->next = nowy;
	}
}
	
// usuwa komórkę z pozycji next komórki o wskaźniku p
        void Delete(cell * p)
	{
		cell* nnnext = new cell;
		nnnext = p->next->next;
		delete p->next;
		p->next = nnnext;
	}

// zwraca element komórki o wskaźniku p
        element Retrieve(cell * p)
	{
		return p->el;
	}

// zwraca wskaźnik do pierwszej komórki z elementem x
        cell * Locate(element x)
	{
		cell* check = new cell;
		check = header;
		while(check->el != x)
		{
			check = check->next;
		}
		return check;
	}

// zwraca wskaźnik do pierwszej komórki na liście
        cell * First()
	{
		//cell* first = new cell;
		//first = header;
		//return first;
		return header; 
	} 

// zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
        cell * Next(cell * p)
	{
		return p->next;
	}

// zwraca wskaźnik do komórki poprzedzającej komórkę o wskaźniku p
        cell * Previous(cell * p)
	{
		cell* check = new cell;
		cell* lastc = new cell;
		check = header;
		while(check != p)
		{
			lastc = check;
			check = check->next;
		}
		return lastc;
	}

// zwraca wskaźnik do ostatniej komórki na liście
        cell * Last()
	{
		cell* check = new cell;
		check = header;
		while(check->next != nullptr)
		{
			check = check->next;
		}
		return check;
	}


        void print() // wyświetla wszystkie elementy listy
	{
		cell* check = new cell;
		check = header;
		while(check)
		{
			cout << check->el << endl;
			check = check->next;
		}
	}
};

int main()
{
	Lista list;

	list.Insert(2, nullptr);
	cell* first = list.First();
	list.Insert(5, first);
	cell* next = list.Next(first);
	list.Insert(7, next);
	cell* last = list.Last();
	list.Insert(10, last);
	cell* loc = list.Locate(5);
	list.Insert(12, loc);

	int elemencik = list.Retrieve(list.Last());

	cout << "last element " << elemencik << endl;

	list.print();

	cell* prev = list.Previous(list.Last());
	list.Delete(prev);

	cout << endl;

	list.print();
}
