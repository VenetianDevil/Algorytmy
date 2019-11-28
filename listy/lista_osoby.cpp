#include <iostream>
#include <string>
using namespace std;

class Osoba {
    public:
    string imie;
    string nazwisko;

    Osoba() = default;
    Osoba(string imie, string nazwisko) : imie(imie), nazwisko(nazwisko) {}
};

template <class T>
struct cell
{
	T el;
	cell<T> *next;
	cell<T> *prev;
};

template <class T>
class Lista
{
      protected:
	cell<T> *header; // głowa listy
	cell<T> *tail;   //ogon listy
      public:
	int size = 0;
	Lista() //konstruktor
	{
		header = nullptr;
		tail = nullptr;
	}
	~Lista() //destruktor
	{
		cell<T> *p;

		while (header)
		{
			p = header->next;
			delete header;
			header = p;
		}
	}

	// wstawia element x na pozycję next komórki o wskaźniku p (lub w przypadku pustej listy tworzy komórkę z Tem x w miejscu głowy listy)
	void Insert(T x, cell<T> *p)
	{
		if (header == nullptr)
		{
			cell<T> *newHeader = new cell<T>;
			cell<T> *newTail = newHeader;
			newHeader->el = x;
			newHeader->next = nullptr;
			newHeader->prev = nullptr;
			header = newHeader;
			tail = newTail;
		}
		else if (p == header && tail == header)
		{
			tail = new cell<T>;
			tail->el = x;
			tail->prev = header;
			tail->next = nullptr;
			header->next = tail;
		}
		else if (p == tail)
		{
			cell<T> *newTail = new cell<T>;
			newTail->el = x;
			newTail->prev = tail;
			newTail->next = nullptr;
			tail->next = newTail;
			tail = newTail;
		}
		else
		{
			cell<T> *nowy = new cell<T>;
			nowy->el = x;
			nowy->next = p->next;
			nowy->prev = p;
			p->next->prev = nowy;
			p->next = nowy;
		}
	}

	// usuwa komórkę z pozycji next komórki o wskaźniku p
	void DeleteNext(cell<T> *p)
	{
		if (p->next)
		{
			cell<T> *tmp = p->next;
			p->next = p->next->next;
			if (p->next)
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

	void Delete(cell<T> *p)
	{
		if (p->prev)
			p->prev->next = p->next;
		else
		{
			header = p->next;
		}
		if (p->next)
		{
			p->next->prev = p->prev;
		}
		delete p;
	}

	// zwraca element komórki o wskaźniku p
	T Retrieve(cell<T> *p)
	{
		return p->el;
	}

	// zwraca wskaźnik do pierwszej komórki z elementem x
	cell<T> *Locate(T x)
	{
		cell<T> *check = new cell<T>;
		check = header;
		while (check->el.imie != x.imie && check->el.nazwisko != x.nazwisko)
		{
			check = check->next;
		}
		return check;
	}

	// zwraca wskaźnik do pierwszej komórki na liście
	cell<T> *First()
	{
		return header;
	}

	// zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
	cell<T> *Next(cell<T> *p)
	{
		return p->next;
	}

	// zwraca wskaźnik do komórki poprzedzającej komórkę o wskaźniku p
	cell<T> *Previous(cell<T> *p)
	{
		return p->prev;
	}

	// zwraca wskaźnik do ostatniej komórki na liście
	cell<T> *Last()
	{
		return tail;
	}

	void print() // wyświetla wszystkie elementy listy
	{
		cell<T> *check;
		check = header;
		while (check)
		{
			cout << check->el.imie << "\t" << check->el.nazwisko << endl;
			check = check->next;
		}
	}
};

int main()
{
	Lista<Osoba> list;

    Osoba osoba("Anna", "Arbuz");

	list.Insert(osoba, nullptr);

    Osoba osoba2("Beata", "Bar");
	cell<Osoba> *first = list.First();
	list.Insert(osoba2, first);

    Osoba osoba3("Cezary", "Czar");
	cell<Osoba> *next = list.Next(first);
	list.Insert(osoba3, next);
	
    Osoba osoba4("Dawid", "Dno");    
    cell<Osoba> *last = list.Last();
	list.Insert(osoba4, last);
	cell<Osoba> *loc = list.Locate(osoba3);
    Osoba osoba5("Edward", "Energia");
	list.Insert(osoba5, loc);

	// A, B, C, E, D

	Osoba elemencik = list.Retrieve(list.Last());

	cout << "last element " << elemencik.imie << endl;

	list.print();

	cell<Osoba> *prev = list.Previous(list.Last());
	list.DeleteNext(prev);

	cout << endl;

	list.print();
}