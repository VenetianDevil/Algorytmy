#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct line
{
    int u; // town 1
    int v; // town 2
    int c; // cost
    int t; // company
};

struct company
{
    int* cost; // cost from this company to other
};

class Travel
{
    private:
        int from;
        int* costs;

    int get_min(int vis[])
    {
        int min = 0, out = 0;
        for(int i=0; i<nr_towns; i++)
        {
            if(vis[i]!=1)
            {  
                // cout << "checking: " << i+1 << "with actual cost " << costs[i] << endl;
                if(min==0 || min>costs[i])
                {
                    min = costs[i];
                    out = i+1;
                }
            }
        }
        return out;
    }

    int possible_cost(int u, int old_firm, int i)
    {
        // cout << "finding possible cost to " << lines[i].u << " " << lines[i].v << endl;
        if(old_firm==0)
            return costs[u-1] + lines[i].c;
        else
            {
                // cout << "cost of changing firms: " << firms[old_firm-1].cost[lines[i].t-1] << endl;
            return costs[u-1] + lines[i].c + firms[old_firm-1].cost[lines[i].t-1];
            }
    }

    void find_costs()
    {
        // cout << "finding ways " << endl;
        int visited[nr_towns] = {0};
        int checking = from;
        int ch = 0;
        int firm[nr_towns] = {0};
        while(ch<nr_towns)
        {
            if(ch>0)
                checking = get_min(visited);
            
            // cout << "checking: " << checking << endl;
            int next_cost = 0;
            int i=0;
            while(i<nr_lines)
            {
                // cout << "\tcheck line " << i << endl;
                if((lines[i].u == checking && visited[lines[i].v-1]==0)|| (lines[i].v == checking && visited[lines[i].u-1]==0))
                {
                    // cout << "last firm: " << firm[checking-1] << endl;
                    next_cost = possible_cost(checking, firm[checking-1], i);
                    // cout << "\tnext possible cost " << next_cost << endl;
                    
                    if(lines[i].u == checking)
                    {
                        if(next_cost < costs[lines[i].v -1])
                        {
                            firm[lines[i].v - 1] = lines[i].t;
                            costs[lines[i].v -1] = next_cost;
                        }
                    }
                    else
                    {
                        if(next_cost < costs[lines[i].u -1])
                        {
                            firm[lines[i].u - 1] = lines[i].t;
                            costs[lines[i].u -1] = next_cost;
                        }
                    }
                    
                    // cout << "\tchosen cost: " << costs[lines[i].v -1] << endl;
                                       
                }
                i++;
            }            
            visited[checking-1] = 1;
            ch++;
        }

        for(int i=0; i<nr_towns; i++)
        {
            if(costs[i] == 100)
                costs[i] = -1;
        }
    }

    public:
        company* firms;
        line* lines;
        int nr_towns;
        int nr_lines;
        Travel(int n, int k, int m, int s)
        {
            nr_towns = n;
            costs = new int[nr_towns];
            firms = new company[k];
            nr_lines = m;
            lines = new line[m];
            from = s;
        }

        void get_costs()
        {

            for(int i=0; i<nr_towns; i++)
            {
                if(i+1 == from)
                    costs[i] = 0;
                else
                    costs[i] = 100;
            }
            find_costs();

            for(int i=0; i<nr_towns; i++)
            {
                cout << costs[i] << " ";
            }
        }
};

Travel* read_file()
{
    //pobranie z pliku danych
    ifstream infile("dane");
    int n, m, k, s;
    string line, str_a, str_b;

    getline(infile, line);
    stringstream stream(line);
    stream >> n >> m >> k >> s;
    // cout << n << " " << m << " " << k << " " << s << endl;

    Travel* t = new Travel(n, k, m, s);

    for(int i=0; i<k; i++)
    {
        getline(infile, line);
        stringstream stream(line);
        t->firms[i].cost = new int[k];
        for(int j=0; j<k; j++)
        {
            stream >> t->firms[i].cost[j];
            // cout << t->firms[i].cost[j] << " ";
        }
        // cout << endl;
    }

    for(int l=0; l<m; l++)
    {
        getline(infile, line);
        stringstream stream(line);
        stream >> t->lines[l].u;
        stream >> t->lines[l].v;
        stream >> t->lines[l].c;
        stream >> t->lines[l].t;
    }
    return t;
}

int main()
{
    Travel* t = read_file();
    t->get_costs();
    cout << endl;
}