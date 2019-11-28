#include <iostream>
//#include <iterator>
//#include <string>
using namespace std;

struct q_key
{
    int prio; // data;
};

//Implementacja kolejki na Kopcu
class MinPriorityQueue
{
private:
    q_key *queue;
    int n = 0; //liczba elementow
    int max_n = 0;

public:
    MinPriorityQueue() = default;
    MinPriorityQueue(int max)
    {
        max_n = max;
        queue = new q_key[max];
        n = 0;
        cout << "queue created" << endl;
    }

    MinPriorityQueue(int keys[], int size)
    {
        max_n = size;
        // cout << "max_n = " << max_n << endl;

        queue = new q_key[max_n];

        // cout << "odczytany rozmiar tablicy " << max_n << endl;
        for (int i = 0; i < max_n; i++)
        {
            // cout << keys[i] << endl;
            insert(keys[i]);
            // cout<< "wrzucam do kolejki el: " << i << " n= " << n << "n_max = " << max_n << endl;
        }
        cout << "queue created" << endl;
    }

    int min() //return min
    {
        return queue[0].prio;
    }

    int deleteMin() //return and delete min
    {
        int min = queue[0].prio;
        n--;
        queue[0].prio = queue[n].prio;
        // cout << "pelozona najdalsza wartosc na szczyt: " << queue[0].prio << endl;
        int k = 0;
        int swaps = 1;

        while (swaps == 1 && ((k + 1) * 2) - 1 < n && (k + 1) * 2 < n)
        {
            swaps = 0;
            if (queue[k].prio > queue[((k + 1) * 2) - 1].prio)
            {
                swap(queue[k], queue[((k + 1) * 2) - 1]);
                // cout << "swap " << k << " " << ((k+1)*2)-1 << endl;
                k = ((k + 1) * 2) - 1;
                swaps = 1;
            }
            else if (queue[k].prio > queue[((k + 1) * 2)].prio)
            {
                swap(queue[k], queue[(k + 1) * 2]);
                // cout << "swap " << k << " " << (k+1)*2 << endl;
                k = (k + 1) * 2;
                swaps = 1;
            }
        }

        return min;
    }

    bool isEmpty() //check if queue is epmpty
    {
        if (n == 0)
            return true;
        else
            return false;
    }

    int size()
    {
        return n;
    }

    void insert(int x)
    {
        if (n == max_n)
        {
            cout << "No more space, size of the key equals max size." << endl;
        }
        else
        {
            int i, j;
            i = n++;
            j = (i - 1) / 2;
            while (i > 0 && queue[j].prio > x)
            {
                queue[i] = queue[j];
                i = j;
                j = (i - 1) / 2;
            }
            queue[i].prio = x;
        }
    }

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            cout << queue[i].prio << "\n";
        }
        cout << endl;
    }
};

int main()
{
    MinPriorityQueue kopiec = MinPriorityQueue(7);

    if (kopiec.isEmpty() == true)
        cout << "Kolejka pusta" << endl;
    else
        cout << "Kolejka nie jest pusta" << endl;

    kopiec.insert(7);
    kopiec.insert(3);
    kopiec.insert(9);

    if (kopiec.isEmpty() == true)
        cout << "Kolejka pusta" << endl;
    else
        cout << "Kolejka nie jest pusta" << endl;

    cout << "min wartosc: " << kopiec.min() << endl;

    kopiec.print();

    int tab[7] = {7, 5, 9, 6, 7, 8, 10};
    int size = (int)sizeof(tab) / sizeof(int);
    MinPriorityQueue kopiec_tab = MinPriorityQueue(tab, size);
    kopiec_tab.print();

    int min = kopiec_tab.deleteMin();
    cout << "min = " << min << endl;

    cout << "size = " << kopiec_tab.size() << endl;

    kopiec_tab.print();
}
