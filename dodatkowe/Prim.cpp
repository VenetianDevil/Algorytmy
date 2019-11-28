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

        edge pop(int s)
        {
            cell* found = start;
            cell* last = nullptr;
            while(found->element.a!=s && found->element.b!=s)
            {
                last = found;
                found = found->next;
            }

            edge f = found->element;

            if(last == nullptr)
                start = found->next;
            else
                last->next = found->next;

            delete found;
            return f;
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
            while(i<nr_nodes)
            {
                if(nodes[i]==0)
                    return false;
                i++;
            }
            return true;
        }

        void find_min(int s)
        {
            int i=1;
            int found = 0;
            edge next;
            Kolejka to_use;
            do{
                next = edges.pop(s);
                while(next!=)
                {
                    to_use.add(next);
                }

                // cout << "pobralem krawedz" << endl;
                if(nodes[next.a]==0 || nodes[next.b]==0)
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

        void get_min(int start)
        {
            find_min(start);

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

    g->get_min(0);
}
