#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

typedef string element;
struct cell
{
	element el;
	cell *next;
};

class Stack
{
protected:
	cell *header; // głowa listy
public:
	Stack() //konstruktor
	{
		header = nullptr;
	}
	~Stack() //destruktor
	{
		cell *p;

		while (header)
		{
			p = header->next;
			delete header;
			header = p;
		}
	}

	void Push(element x)
	{
		if (header == nullptr)
		{
			cell *newHeader = new cell;
			newHeader->el = x;
			newHeader->next = NULL;
			header = newHeader;
		}
		else //zawsze wstawia na poczatek
		{
			cell *nowy = new cell;
			nowy->el = x;
			nowy->next = header;
			header = nowy;
		}
	}

	element Pop()
	{
		cell *toDelete = header;
		header = toDelete->next;
		string x = toDelete->el;
		delete toDelete;
		return x;
	}

	element Top()
	{
		return header->el;
	}

	void Makenull()
	{
		cell *p;
		while (header)
		{
			p = header->next;
			delete header;
			header = p;
		}
	}

	bool Empty()
	{
		if (header == NULL)
		{
			return true;
		}
		return false;
	}
};

int priorytet(string a)
{
	if (a == "(")
		return 0;
	if (a == "+" || a == "-" || a == ")")
		return 1;
	if (a == "^")
		return 3;
	else
		return 2; // * / %
}

int main()
{
	istringstream iss;
	vector<string> result;
	string wyrazenie;

	// ONP -> inifiksowa
	cout << "Podaj wyrazenie w ONP, kazdy znak i liczbe oddziel spacja: " << endl;
	string ONP; // = "2 7 + 3 / 14 3 - 4 * + 2 /";
	getline(cin, ONP);
	// cout << ONP << endl;

	iss.str(ONP);

	while (iss >> wyrazenie)
	{
		result.push_back(wyrazenie);
	}

	// for(size_t i=0; i<result.size(); i++)
	// {
	// 	cout << result.at(i) << endl;
	// }

	Stack list;
	string next, a, b;

	for (size_t j = 0; j < result.size(); j++)
	{
		next = result.at(j);
		if (next != "+" && next != "-" && next != "*" && next != "/" && next != "^" && next != "%")
		{
			list.Push(next);
		}
		else
		{
			a = list.Pop();
			b = list.Pop();
			if (next == "+" || next == "-" || (j < result.size() - 1 && result.at(j + 1) == "^"))
				next = "(" + b + next + a + ")";
			else
				next = b + next + a;
			list.Push(next);
		}
	}

	cout << "Postac inifiksowa: " << list.Pop() << endl
		 << endl;

	// inifiksowa -> ONP
	result.clear();
	cout << "Podaj wyrazenie inifiksowe, kazdy znak, liczbe i nawias odziel spacja :" << endl;
	string inifix; // = "( ( 2 + 7 ) / 3 + ( 14 - 3 ) * 4 ) / 2";
	getline(cin, inifix);
	// cout << inifix << endl;

	istringstream isn;
	string wynik;
	int value; // do priorytetu znakow

	isn.str(inifix);

	while (isn >> wyrazenie)
	{
		result.push_back(wyrazenie);
	}

	for (size_t j = 0; j < result.size(); j++)
	{
		next = result.at(j);
		// cout << next << endl;
		if (next != "+" && next != "-" && next != "*" && next != "/" && next != "^" && next != "%" && next != "(" && next != ")")
		{
			wynik = wynik + " " + next;
		}
		else if (next == ")")
		{
			while (list.Top() != "(")
			{
				// cout << "\t\t" << list.Pop() << endl;
				wynik += " " + list.Pop();
			}
			list.Pop();
		}
		else
		{
			value = priorytet(next);
			if (list.Empty() || next == "(" || value > priorytet(list.Top()))
			{
				list.Push(next);
				// cout << "wepchany na stos" << endl;
			}
			else
			{
				while (value <= priorytet(list.Top()))
				{
					wynik += " " + list.Pop();
				}
				list.Push(next);
			}
		}
	}

	while (!list.Empty()) //wyjęcie reszty znakow ze stosu
	{
		wynik += " " + list.Pop();
	}

	cout << "Postac ONP: " << wynik << endl;
}