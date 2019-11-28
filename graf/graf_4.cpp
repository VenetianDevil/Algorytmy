//Karolina Gora 2019
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
    bool articulation_point = false;
    int num_of_b_e = 0;
    int back_edges_from[10];
    int DFS_nr = 0;
    int LOW = 0;
};

class Graph
{
    protected:
        edge* all = NULL; //list  of edges
        int edges_num = 0; // how many edges gonna be

    private:
        int counter = 0; //how many edges have been added
        int duality = 0; // yes 1, no -1
        int checked = 0; // for rekurency
        int* sort = NULL; //topologicaly
        int sorted = 0;
        int* parents = NULL; //parent of i-node
        int const_parts = 1;
        edge* bridges = NULL;
        int b=0; //couting bridges
        
        void rek_for_DFS(int groups[], int node_nr)
        {
            // cout << "checking node " << node_nr << endl;
            node n = list[node_nr];
            if(checked <= max_node)
            {
                for(int j=0; j<n.count; j++)
                {
                    if(groups[n.adj[j]] != 0 && n.adj[j]!=parents[node_nr]) // if it's not going back to its parent
                    {
                        list[n.adj[j]].back_edges_from[list[n.adj[j]].num_of_b_e++] = node_nr; // krawedz wsteczna
                    }

                    if(duality == 0 && groups[n.adj[j]]==groups[node_nr]) // for duality
                    {
                        duality = -1;
                    }
                    else if(groups[n.adj[j]]==0) // checking child
                    {
                        if(groups[node_nr]==1)
                            groups[n.adj[j]]=2;
                        else
                            groups[n.adj[j]]=1;

                        parents[n.adj[j]]=node_nr;

                        rek_for_DFS(groups, n.adj[j]);
                    }
                }
                sort[checked++] = node_nr; // for topologic sort
            } 
        }

        void DFS(int start)
        {
            if(list == NULL)
                create_nods();

            sort = new int[max_node+1];
            int groups[max_node+1] = {};

            parents = new int[max_node+1];
            
            if(start<= max_node && start >= 0)
            {
                groups[start] = 1;
                parents[start] = -1; //no parent
                rek_for_DFS(groups, start);
            }

            while(checked<=max_node) // if there is some node left that wasn't adjust to any of checked
            {
                const_parts++;
                for(int i=0; i<=max_node; i++)
                {
                    if(groups[i]==0)
                    {
                        groups[i]=1;
                        parents[i]=-1; //no parent
                        rek_for_DFS(groups, i);
                    }
                }
            }

            if(duality==0)
                duality=1;
        }

        int deleted_node;
        int done;
        void find_art_points(int check[], int start)
        {
            done++;
            check[start] = 1;
            node n = list[start];
            for(int i=0; i<n.count; i++)
            {
                if(check[n.adj[i]]==0)
                {
                    if(n.adj[i] != deleted_node)
                        find_art_points(check, n.adj[i]);
                }
            }
        }

        void find_bridges(int start)
        {
            // cout << "find brodges " << start << endl;
            list[start].DFS_nr = ++checked;
            list[start].LOW = checked;
            node n = list[start];
            if(checked <= max_node+1)
            {
                for(int j=0; j<n.count; j++)
                {
                    if(list[n.adj[j]].DFS_nr==0 && parents[n.adj[j]]==start)
                        find_bridges(n.adj[j]);
                    
                    if(j+1==n.count)//all adj visited
                    {
                    // cout << "\tstart" << start << endl;
                        // cout << start << " DFS = " << n.DFS_nr << " low = " << list[start].LOW << endl;

                        for(int a=0; a<n.count; a++)
                        {
                            // cout << list[start].LOW << " " << list[n.adj[a]].DFS_nr << endl;
                            if(start == parents[n.adj[a]]) // it's a child and dont go back // for graph without direction
                                list[start].LOW = min(list[start].LOW, list[n.adj[a]].LOW);
                            else if(parents[start]!=n.adj[a])
                                list[start].LOW = min(list[start].LOW, list[n.adj[a]].DFS_nr);
                        }
                        
                        // cout << start << " DFS = " << n.DFS_nr << " low = " << list[start].LOW << endl;

                        if(list[start].LOW == list[start].DFS_nr && parents[start]!=-1)
                        {
                            // cout << "bridge found" << endl;
                            edge e {parents[start], start};
                            bridges[b++] = e; 
                        }
                    }
                }
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

        void get_topological_sort(int start)
        {
            if(sort==NULL)
                DFS(start);

            cout << "Topological sort:";
            for(int k=max_node; k>=0; k--)
            {
                cout << " " << sort[k];
            }
            cout << endl;
        }

        bool dichotomy()
        {
            if(duality==0)
                DFS(0);
            
            // cout << "duality = " << duality << endl;

            if(duality==0)
                duality=1;
            
            if(duality==-1)
                return false;
            else
                return true;
        }

        void art_points(int start)
        {
            // cout << "const parts " << const_parts << endl;
            for(int i=0; i<max_node; i++)
            {
                // cout << "check node " << i << endl;
                if(parents[i] != -1)
                {
                    deleted_node = i;
                    int j=0, k=0; 
                    done = 0;
                    int check[max_node+1] = {};
                    while(done<max_node)
                    {
                        if(check[k]==0 && i!=k)
                        {
                            // cout << "next check for " << k << endl;
                            find_art_points(check, k);
                            j++;
                        }
                        k++;
                    }

                    // cout << "new const parts " << j << endl;
                    if(j>const_parts)
                        list[i].articulation_point=true;
                }
                else
                {
                    int root=0, p=0;
                    while(p<=max_node && root<2)
                    {
                        if(parents[p] == start)
                            root++;
                        p++;
                    }
        
                    if(root>1)
                        list[start].articulation_point = true;
                }
            }

            cout << "Articulation points: " << endl;
            for(int a = 0; a<= max_node; a++)
            {
                if(list[a].articulation_point == true)
                    cout << a << endl;
            }
        }

        void get_bridges(int start)
        {
            if(parents == NULL)
                DFS(start);

            bridges = new edge[edges_num];
            checked = 0;
            find_bridges(start);

            cout << "Bridges: " << endl;
            int i =0 ;
            while(i<b)
            {
                cout << bridges[i].a << "\t" << bridges[i].b << endl;
                i++;
            }
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

            cout << "List: " << endl;
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
    cout << endl;

    l->get_topological_sort(0);
    cout << endl;

    bool duality = l->dichotomy();
    if(duality == true)
        cout << "Bipartite graph: YES" << endl;
    else cout<< "Bipartite graph: NO" << endl;
    cout << endl;

    l->get_bridges(0);
    cout << endl;

    l->art_points(0);
}
