//Karolina Gora 08.06.2019
//Algorytm Kruskala, najmniejsze drzewo rozpinajace
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct edge
{
    int a;
    int b;
    int weight;
};

struct cell
{
    edge element;
    cell* next = NULL;
};

class Kolejka
{
    private:
        cell* start;
    public:
        Kolejka()
        {
            start = nullptr;
        }

        void add(edge e)
        {
            // cout << " adding " << endl;
            cell* next = new cell;
            next->element = e;
            // cout << "element added to cell* next\t";
            if(start == nullptr)
            {
                start = next;
                start->next = nullptr;
                // cout << "first " << endl;
            }
            else
            {
                if(start->element.weight>=e.weight)
                {
                    next->next = start;
                    start = next;
                    // cout << "put as first " << endl;

                }
                else
                {
                    cell* check = start;
                    cell* last = new cell;
                    while(check->element.weight<e.weight && check->next!=nullptr)
                    {
                        // cout << "compare " << check->element.weight << "<" << e.weight << endl;
                        last = check;
                        check = check->next;
                    }
                        // cout << "compared as last " << check->element.weight << "<" << e.weight << endl;

                    if(check->next == nullptr && check->element.weight<e.weight)
                    {
                        check->next = next;
                        next->next = nullptr;
                        // cout << "put as last" << endl;
                    }
                    else
                    {
                        next->next = check;
                        last->next = next;
                        // cout << "put after " << last->element.a << " " << last->element.b << endl;
                    }
                }
            }
        }

        edge pop()
        {
            cell * todelete = start;
            edge pop = start->element;
            start = start->next;
            delete todelete;
            return pop;
        }
};

class Graph
{
    private:
        int nr_edges;
        int nr_nodes;
        edge* min_tree;

        bool check()
        {
            int i=0;
            while(i<nr_nodes-1)
            {
                if(nodes[i]!=nodes[i+1])
                    return false;
                i++;
            }
            return true;
        }

        void change(edge next, int a, int b)
        {
            if (a==0)
                nodes[next.a] = b;
            else if(b==0)
                nodes[next.b] = a;
            else
            {
                for(int i=0; i<nr_nodes; i++)
                {
                    if(nodes[i]==a)
                        nodes[i]=b;
                }
            }
        }

        void find_min()
        {
            int i=1;
            int found = 0;
            do{
                edge next = edges.pop();
                // cout << "pobralem krawedz" << endl;
                if(nodes[next.a]==0 && nodes[next.b]==0)
                {
                    nodes[next.a] = nodes[next.b] = i;
                    i++;
                    min_tree[found++] = next;
                    // cout << "dodalem nowa krawedz, osobny zbior" << endl;
                }
                else if(nodes[next.a]!=nodes[next.b])
                {
                    min_tree[found++] = next;
                    // cout << "dodalem nowa krawedz, zlaczylem zbiory " << endl;
                    change(next, nodes[next.a], nodes[next.b]);
                } 
            }while(check()==false);
        }

    public:
        int* nodes;
        Kolejka edges;
        Graph() = default;
        Graph(int k, int n)
        {
            nr_edges = k;
            nr_nodes = n;
            min_tree = new edge[n-1];
            nodes = new int[n];
            for(int i=0; i<n; i++)
                nodes[i]=0;
        }

        void get_min()
        {
            find_min();

            for(int j=0; j<nr_nodes-1; j++)
            {
                cout << min_tree[j].a << " " << min_tree[j].b << " " << min_tree[j].weight << endl;
            }
        }
};

Graph* read_file()
{
    //pobranie z pliku danych
    ifstream infile("dane");
    int n, k;
    string line;
    getline(infile, line);
    stringstream stream(line);
    stream >> k >> n;
    // cout << k << " " << n << endl;

    Graph* t = new Graph(k, n);

    for(int i=0; i<k; i++)
    {
        edge p;
        getline(infile, line);
        stringstream stream(line);
        stream >> p.a >> p.b >> p.weight;
        // cout << p.a << " " << p.b << " " << p.weight;
        t->edges.add(p);
    }

    return t;
}

int main()
{
    Graph* g = read_file();

    g->get_min();
}

/* Algorytm sortuje rosnąco wagami wstawione krawedzie
Przechodząc po kolejce (od najmniejszych wag) sprawdza:
- czy dana krawedz laczy dwa wierzcholki nienalezaca do drzewa, wtedy dodaje ja, i nadaje taki sam numer obu wierzcholkom i zwieksza i++ aby w kolejnym takim przypadku nadac innny numer.
- jesli laczy wierzcholek nalezacy do drzewa z nienalezacym, dodaje krawedz, i wierzcholkowi nowemu nadaje numer taki jak wierzcholej juz nalezacy wczesniej
- jesli krawedz laczy wierzcholki o roznych numerach a i b, dodaje ja i zamienia wszytskie wierzcholki z nr a na b
- jezeli krawedz laczy wierzcholki o tym samym numerze, nie dodaje jej do drzewa i przechodzi do ponownego pobrania 
warunkiem konczacym petle jest gdy funckja check() zwroci true, czyli wszytskie wierzcholki maja ten sam numer (spojnosc drzewa rozpinajacego) */

/* Zlozonosc: w najgorszym przypadku (sprawdzenie kazdej krawedzi) O(k*n), a w najbardziej optymistycznym (n-1 pierwszych krawedzi tworzy drzewo rozpinajace) O(n^2) */