#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;


struct edge
{
    int a;
    int b;
};

struct node
{
    int count = 0;
    int adj[10];
};

class Graph
{
    protected:
        int edges_num = 0; // how many edges gonna be
        int counter = 0; //how many edges have been added
        edge* all = NULL; //list  of edges

    private:
        int duality = 0;
        int* sort = NULL;
        int checked = 0; // for rekurency
        int sorted = 0;

        void rek_sort_top(int groups[], int node_nr)
        {
            node n = list[node_nr];
            if(checked <= max_node)
            {
                for(int j=0; j<n.count; j++)
                {
                    if(duality==0 && groups[n.adj[j]]==groups[node_nr])
                    {
                        duality = -1;
                        // cout << "duality false przy " << node_nr << " " << n.adj[j] << endl;
                    }
                    else if(groups[n.adj[j]]==0)
                    {
                        if(groups[node_nr]==1)
                            groups[n.adj[j]]=2;
                        else
                            groups[n.adj[j]]=1;

                        rek_sort_top(groups, n.adj[j]);
                    }
                }
                sort[checked++] = node_nr;
                // cout << "dodalen do listy " << node_nr << endl;
            } 
        }

    public:
        node* list = NULL; //list of nodes and their neighbours
        int max_node = 0; //to create the smallest posible array for matrix and list
        
        Graph() = default;
        
        explicit Graph(int edge_num)
        {
            edges_num = edge_num;
            all = new edge [edge_num];
            // cout << "Graf stworzony" << endl;
        }

        void add_edge(edge next)
        {
            all[counter++]=next;
            if(max_node<next.a)
                max_node = next.a;
            if(max_node<next.b)
                max_node = next.b;
            // cout << "\tdodalem node " << next.a << " do " << next.b << endl;
        } 

        void create_nods()
        {
            if(list==NULL)
            {
                int size = max_node +1;
                list = new node[size];
                for(int i=0; i< size; i++)
                {
                    node n;
                    list[i] = n;
                    // cout << n.count << endl;
                }

                edge temp;
                for(int i=0; i<edges_num; i++)
                {
                    temp = all[i];
                    int c = list[temp.a].count;
                    // cout << "counter noda: " << c << endl;
                    list[temp.a].adj[c] = temp.b;
                    // cout << "\t\tDodalem do listy " << temp.a << "->" << list[temp.a].adj[list[temp.a].count] << endl;
                    list[temp.a].count+=1;
                    // cout << list[temp.a].count << endl;
                }
            }
        }

        void sort_topologic(int start)
        {
            if(list == NULL)
                create_nods();

            sort = new int[max_node+1];
            int groups[max_node+1] = {};
            
            if(start<= max_node && start >= 0)
            {
                groups[start] = 1;
                rek_sort_top(groups, start);
            }

            while(checked<=max_node) // if there is some node left that wasn't adjust to any of checked
            {
                for(int i=0; i<=max_node; i++)
                {
                    if(groups[i]==0)
                    {
                        groups[i]=1;
                        rek_sort_top(groups, i);
                    }
                }
            }

            if(duality==0)
                duality=1;

            // for(int k=0; k<=max_node; k++)
            // {
            //     cout << groups[k] << endl;
            // }

        }

        void get_topoligic_sort(int start)
        {
            if(sort==NULL)
                sort_topologic(start);

            cout << "sort topologiczny:";
            for(int k=max_node; k>=0; k--)
            {
                cout << " " << sort[k];
            }
            cout << endl;
        }

        bool dichotomy()
        {
            if(duality==0)
                sort_topologic(0);
            
            // cout << "duality = " << duality << endl;

            if(duality==0)
                duality=1;
            
            if(duality==-1)
                return false;
            else
                return true;
        }
};

class List: public Graph
{
    protected:
        int size = 0;
    
    public:
        explicit List(int edges)
        {
            edges_num = edges;
            all = new edge [edges];
        }

        const void get_list()
        {
            size = max_node+1;
            create_nods();
            // cout << "Zakonczlem create_nods" << endl;

            cout << "Lista: " << endl;
            // cout << size << endl;
            for(int i = 0; i<size; i++)
            {
                cout << i << ":";
                int c = list[i].count;
                // cout << c << endl;
                for(int j=0; j<c; j++)
                {
                    cout << " " << list[i].adj[j];
                }
                cout << endl;
            }
        }
};

class Matrix: public Graph
{
    private:
        int size;
        int **matrix = NULL;

    public:

        explicit Matrix(int edges)
        {
            edges_num = edges;
            all = new edge [edges];
        }

        void create_Matrix()
        {
            size = max_node+1;
            matrix = new int *[size];
            for(int i=0; i<size; i++)
            {
                matrix[i] = new int[size];
                for(int j=0; j<size; j++)
                {
                    matrix[i][j] = 0;
                }
            }

            create_nods();
            // cout << "nodes created" << endl;

            node temp;
            int place = 0;
            // cout << "\t size " << size << endl;
            for(int i=0; i<size; i++)
            {
                temp = list[i];
                // cout << "count now: " << temp.count << endl;
                for(int j=0; j<temp.count; j++)
                {
                    // cout << "want to put 1 on position " << temp.adj[j] << endl;
                    place = temp.adj[j];
                    // cout << "value of this place now is: " << matrix[i][place] << endl;
                    matrix[i][place]=1;
                    // cout << "done" << endl;
                }
            }
        }

        void get_Matrix()
        {
            if(matrix==NULL)
                create_Matrix();

            cout << "Matrix:" << endl;
            
            cout << "  ";
            for(int i=0; i<size; i++)
            {
                cout << " " << i;
            }
            cout << endl;
            
            for(int i=0; i<size; i++)
            {
                cout << i << ":";
                for(int j=0; j<size; j++)
                {
                    cout << " " << matrix[i][j];
                }
                cout << endl;
            }
        }
};

#include<typeinfo>

template<typename T>
T* read_file(T* l)
{
    //pobranie z pliku danych
    ifstream infile("dane");
    int a, b, edges;
    string line, str_a, str_b;

    infile >> edges;
    T* graph = new T(edges);
    // cout << typeid(T).name() << endl;

    for(int i=0; i<=edges; i++)
    {
        getline(infile, line);
        // cout << line.length() << endl;
        if(line.length()>1)
        {
            if(i==edges)
                line.erase(line.length()-1, 1);
            else
                line.erase(line.length()-2,1);
            line.erase(0, 1);

            stringstream stream(line);
            getline(stream, str_a, ',');
            getline(stream, str_b, ',');

            a = atoi(str_a.c_str());
            b = atoi(str_b.c_str());

            // cout << a << "and " << b << endl;

            edge next{a, b};
            graph->add_edge(next);
        }
    }
    return graph;
}

int main()
{
    List* l;
    l = read_file(l);
    l->get_list();

    cout<< endl;

    Matrix* m;
    m = read_file(m);
    m->get_Matrix();

    // cout << endl;

    l->get_topoligic_sort(0);

    bool duality = m->dichotomy();
    if(duality == true)
        cout << "jest dwudzielny" << endl;
    else cout<< "NIE jest dwudzielny" << endl;
}