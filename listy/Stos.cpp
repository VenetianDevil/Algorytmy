#include <iostream>
using namespace std;

typedef int element;
struct cell
{
    element el;
    cell * next;
};

class Stack
{
    protected:
        cell * header; // głowa listy
    public:
        Stack()    //konstruktor
	{
		header = nullptr;
	}        
	~Stack()  //destruktor
	{
		cell * p;
		
		while(header)
		{
			p = header->next;
			delete header;
			header = p;
		}       	
	}

        void Push(element x)
	{
		if(header == nullptr)
		{
			cell* newHeader = new cell;
			newHeader->el = x;
			newHeader->next = NULL;
			header = newHeader;
		}
		else //zawsze wstawia na poczatek
		{ 
			cell* nowy = new cell;
			nowy->el = x;
			nowy->next = header;
			header = nowy;
		}
	}	
	
        element Pop()
	{
		cell* toDelete = header;
		header = toDelete->next;
		int x = toDelete->el; 
		delete toDelete;
		return x; 
	}

        element Top()
	{
		return header->el;
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
		if(header==NULL)
		{
			return true;
		}
		return false;
	}
};

int main()
{
	Stack list;

	list.Push(2);
	list.Push(5);
	list.Push(7);
	int a = list.Top();
	cout << a << endl;
	a = list.Pop();
	cout << a << endl;
	list.Push(10);
	list.Push(12);
	

	while(!list.Empty())
	{
		cout << list.Top() << endl;
		list.Pop();
	}
}
