#include <iostream>
using namespace std;

typedef int element;
struct cell
{
	element el;
	cell *next;
	cell *prev;
};

class Lista
{
      protected:
	cell *header; // głowa listy
	cell *tail;   //ogon listy
      public:
	int size = 0;
	Lista() //konstruktor
	{
		header = nullptr;
		tail = nullptr;
	}
	~Lista() //destruktor
	{
		cell *p;

		while (header)
		{
			p = header->next;
			delete header;
			header = p;
		}
	}

	// wstawia element x na pozycję next komórki o wskaźniku p (lub w przypadku pustej listy tworzy komórkę z elementem x w miejscu głowy listy)
	void Insert(element x, cell *p)
	{
		if (header == nullptr)
		{
			cell *newHeader = new cell;
			cell *newTail = newHeader;
			newHeader->el = x;
			newHeader->next = nullptr;
			newHeader->prev = nullptr;
			header = newHeader;
			tail = newTail;
		}
		else if (p == header && tail == header)
		{
			tail = new cell;
			tail->el = x;
			tail->prev = header;
			tail->next = nullptr;
			header->next = tail;
		}
		else if (p == tail)
		{
			cell *newTail = new cell;
			newTail->el = x;
			newTail->prev = tail;
			newTail->next = nullptr;
			tail->next = newTail;
			tail = newTail;
		}
		else
		{
			cell *nowy = new cell;
			nowy->el = x;
			nowy->next = p->next;
			nowy->prev = p;
			p->next->prev = nowy;
			p->next = nowy;
		}
	}

	// usuwa komórkę z pozycji next komórki o wskaźniku p
	void DeleteNext(cell *p)
	{
		if(p->next)
		{
			cell *tmp = p->next;
			p->next = p->next->next;
			if(p->next)
			{
				p->next->prev = p;
			}
			else
			{
				tail = p;
			}
			delete tmp;
		}
	}

	void Delete(cell *p)
	{
		if(p->prev)
			p->prev->next = p->next;
		else
		{
			header = p->next;
		}
		if(p->next){
			p->next->prev = p->prev;
		}
		delete p;
	}

	// zwraca element komórki o wskaźniku p
	element Retrieve(cell *p)
	{
		return p->el;
	}

	// zwraca wskaźnik do pierwszej komórki z elementem x
	cell *Locate(element x)
	{
		cell *check = new cell;
		check = header;
		while (check->el != x)
		{
			check = check->next;
		}
		return check;
	}

	// zwraca wskaźnik do pierwszej komórki na liście
	cell *First()
	{
		return header;
	}

	// zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
	cell *Next(cell *p)
	{
		return p->next;
	}

	// zwraca wskaźnik do komórki poprzedzającej komórkę o wskaźniku p
	cell *Previous(cell *p)
	{
		return p->prev;
	}

	// zwraca wskaźnik do ostatniej komórki na liście
	cell *Last()
	{
		return tail;
	}

	void print() // wyświetla wszystkie elementy listy
	{
		cell *check;
		check = header;
		while (check)
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

	// 2,5,12,7,10

	int elemencik = list.Retrieve(list.Last());

	cout << "last element " << elemencik << endl;

	list.print();

	cell* prev = list.Previous(list.Last());
	list.DeleteNext(prev);

	cout << endl;

	list.print();
}