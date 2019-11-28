#include <iostream>
using namespace std;

typedef int element;
struct cell
{
    element el;
    cell * next;
};

class Queue
{
    protected:
        cell * header; // głowa listy
	cell * tail;
    public:
	int size = 0;
        Queue()    //konstruktor
	{
		header = nullptr;
		tail = nullptr;
	}        
	~Queue()  //destruktor
	{
		cell * p;
		
		while(header)
		{
			p = header->next;
			delete header;
			header = p;
		}       	
	}


        void Put(element x)
{
	if(header == nullptr)
	{
		cell* newHeader = new cell;
		newHeader->el = x;
		newHeader->next = NULL;
		header = newHeader;
		tail = header;
	}
	else //zawsze wstawia na koniec
	{ 
		cell* nowyTail = new cell;
		nowyTail->el = x;
		nowyTail->next = NULL;
		tail->next = nowyTail;
		tail = nowyTail;
	}
}
	
        element get()
	{
		cell* toDelete = header;
		int x = toDelete->el;
		header = toDelete->next;
		delete toDelete;
		return x;
	}

        element Front()
	{
		if(header!=nullptr)
		return header->el;
		return -100;
	}

	void Makenull()
	{
		cell * p;
		
		while(header)
		{
			p = header->next;
			delete header;
			header = p;
		}  
	}

	bool Empty()
	{
		if(header==nullptr)
		return true;
		return false;
	}

};

int main()
{
	Queue kolejka;

	kolejka.Put(1);
	kolejka.Put(2);
	kolejka.Put(3);
	kolejka.Put(4);

	cout << kolejka.Front() << endl;
	cout << kolejka.get()<< endl;
	cout << kolejka.get()<< endl;
	cout << kolejka.Front()<< endl;

	kolejka.Makenull();
	if(!kolejka.Empty())
	{
		cout << kolejka.Front()<< endl;
	}
}
