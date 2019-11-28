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

    void find_cost(int to)
    {
        // cout << "finding way to: " << to << endl;
        int visited[nr_towns] = {0};
        int checking = from, next = 0;
        int ch = 0, cost = 0;
        int firm = 0;
        while(ch<nr_towns && checking != to)
        {
            // cout << checking << endl;
            int next_cost = 0;
            int next_firm = 0;
            for(int i=0; i<nr_lines; i++)
            {
                if((lines[i].u == checking && visited[lines[i].v-1]==0) || (lines[i].v == checking && visited[lines[i].u-1]==0))
                {
                    if(next_cost==0 || next_cost > lines[i].c)
                        next_cost = lines[i].c;
                    
                    // cout << "\t" << lines[i].c << endl;
                
                    if(next_cost == lines[i].c)
                    {
                        if(lines[i].u == checking)
                            next = lines[i].v;
                        else
                            next = lines[i].u;
                    
                        next_firm = lines[i].t;                        
                    }
                }
            }
            // cout << "\t\t" << next << endl;
            cost += next_cost;
            if(firm != 0 && firm!=next_firm)
            {
                cost += firms[firm-1].cost[next_firm-1];
                // cout << "paymant for changing firms added" << endl;
            }
            
            firm = next_firm;
            visited[checking-1] = 1;
            
            checking = next;
            
            ch++;
        }

        if(checking == to)
            costs[to-1] = cost;
        else
            costs[to-1] = -1;
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
                {
                    find_cost(i+1);
                }
            }

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