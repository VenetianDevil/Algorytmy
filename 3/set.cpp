#include <iostream>
#include <vector>
using namespace std;

class Set
{
	public:
	vector<int> table;

	Set(vector<int> t)
	{
		table = t;
	}

	Set Suma (Set two)
	{
		vector<int> vec;
		vec.insert(vec.end(), table.begin(), table.end());
		int a;
		bool twice;
		for(int j=0; j<(int)two.table.size(); j++)
		{
			twice = false;
			a = two.table.at(j);
			for(int i=0; i<(int)vec.size(); i++)
			{
				if(a == vec.at(i))
				twice = true;
			}
			if(twice == false)
			vec.push_back(a);
		}
		Set sum(vec);
		return sum;
	}	

	Set Iloczyn (Set two)
	{
		vector<int> iloczyn;
		int a;
		for(int i=0; i<(int)table.size(); i++)
		{
			a = table.at(i);
			for(int j=0; j<(int)two.table.size(); j++)
			{
				if(a == two.table.at(j))
				iloczyn.push_back(a);
			}
		}
		Set both(iloczyn);
		return both;
	}	

	Set Roznica (Set two)
	{
		vector<int> roznica;
		int a;
		bool repeat;
		for(int i=0; i<(int)table.size(); i++)
		{
			repeat = false;
			a = table.at(i);
			for(int j=0; j<(int)two.table.size(); j++)
			{
				if(a == two.table.at(j))
				repeat = true;
			}
			
			if(repeat==false)
			roznica.push_back(a);
		}
		Set sub(roznica);
		return sub;
	}	

	Set Roznica_Sym (Set two)
	{
		vector<int> roznica;
		vector<int> repeated_two;
		int a;
		bool repeat;
		for(int i=0; i<(int)table.size(); i++)
		{
			repeat = false;
			a = table.at(i);
			for(int j=0; j<(int)two.table.size(); j++)
			{
				if(a == two.table.at(j))
				{
					repeat = true;
					repeated_two.push_back(j);
				}
			}
			
			if(repeat==false)
			roznica.push_back(a);
		}

		bool is;
		int b;		
		for(int i=0; i<(int)two.table.size(); i++)
		{
			is = false;
			b = two.table.at(i);
			for(int j=0; j<(int)repeated_two.size(); j++)
			{
				if(i == repeated_two.at(j))
				is = true;	
			}
			if(is == false)
			roznica.push_back(b);
		}

		Set sub(roznica);
		return sub;
	}

	void Wstaw (int one)
	{
		table.push_back(one);
				
	}

	void Usun (int one)
	{
		int index;
		for(int i=0; i<(int)table.size(); i++)
		{
			if(one == table.at(i))
			index = i;
		}
		table.erase(table.begin()+ index);
	}

	void print()
	{
		for( int el: table)
		{
			cout<< el << endl;
		}
	}
};

int main()
{
	vector <int> a{2, 4, 7};
	vector <int> b{1, 8, 4};
	Set A (a);
	Set B (b);

	Set sum = A.Suma(B);
	Set il = A.Iloczyn(B);
	Set roz = A.Roznica(B);
	Set roz_sym = A.Roznica_Sym(B);
	A.Wstaw(5);
	B.Usun(4);

	sum.print();
	cout << endl;
	il.print();
	cout << endl;
	roz.print();
	cout << endl;
	roz_sym.print();
	cout << endl;
	A.print();
	cout << endl;
	B.print();
	cout << endl;

}
