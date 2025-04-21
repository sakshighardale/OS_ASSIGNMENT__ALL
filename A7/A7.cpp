#include<iostream>
using namespace std;

void fifo(int string[20], int n, int size)
{
    int frames[n];
    for (int i = 0; i < n; i++)
        frames[i] = -1;
    int index = -1;
    int page_hits = 0;
    for (int i = 0; i < size; i++)
    {
        int symbol = string[i];
        int flag = 0;
        for (int j = 0; j < n; j++)
        {
            if (symbol == frames[j])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            cout << "\nSymbol: " << symbol << "  Frame: ";
            for (int j = 0; j < n; j++)
                cout << frames[j] << " ";
            page_hits += 1;
        }
        else
        {
            index = (index + 1) % n;
            frames[index] = symbol;
            cout << "\nSymbol: " << symbol << "  Frame: ";
            for (int j = 0; j < n; j++)
            {
                if (frames[j] == -1)
                    cout << " ";
                else
                    cout << frames[j] << " ";
            }
        }
    }
    cout << "\nPage hits: " << page_hits;
    cout << "\nPage misses: " << size - page_hits;
    cout << "\nRatio of Page Hit: " << (float)page_hits / size;
    cout << "\nRatio of Page miss: " << (float)(size - page_hits) / size << endl;
}

void lru(int string[20], int n, int size)
{
    int frames[n];
    for (int i = 0; i < n; i++)
        frames[i] = -1;
    int index = -1;
    int page_hits = 0;
    for (int i = 0; i < size; i++)
    {
        int symbol = string[i];
        int flag = 0;
        int full = 0;
        for (int j = 0; j < n; j++)
        {
            if (symbol == frames[j])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            cout << "\nSymbol: " << symbol << "  Frame: ";
            for (int j = 0; j < n; j++)
                cout << frames[j] << " ";
            page_hits += 1;
        }
        else
        {
            if (full == 0)
            {
                index = (index + 1) % n;
                frames[index] = symbol;
                cout << "\nSymbol: " << symbol << "  Frame: ";
                for (int j = 0; j < n; j++)
                {
                    if (frames[j] == -1)
                        cout << " ";
                    else
                        cout << frames[j] << " ";
                }
            }
            else
            {
                int pos = 999;
                int index = -1;
                for (int j = 0; j < n; j++)
                {
                    for (int k = 0; k < size; k++)
                    {
                        if (frames[j] == string[k])
                        {
                            if (pos > k)
                            {
                                pos = k;
                                index = j;
                                break;
                            }
                        }
                    }
                }
                frames[index] = symbol;
            }
        }
    }
    cout << "\nPage hits: " << page_hits;
    cout << "\nPage misses: " << size - page_hits;
    cout << "\nRatio of Page Hit: " << (float)page_hits / size;
    cout << "\nRatio of Page miss: " << (float)(size - page_hits) / size << endl;
}

void optimal(int string[20], int n, int size)
{
    int frames[n];
    for (int i = 0; i < n; i++)
        frames[i] = -1;
    int page_hits = 0;
    for (int i = 0; i < size; i++)
    {
        int symbol = string[i];
        int flag = 0;
        for (int j = 0; j < n; j++)
        {
            if (frames[j] == symbol)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            cout << "\nSymbol: " << symbol << "  Frame: ";
            for (int j = 0; j < n; j++)
                cout << frames[j] << " ";
            page_hits++;
        }
        else
        {
            int index = -1;
            int farthest = i + 1;
            for (int j = 0; j < n; j++)
            {
                int k;
                for (k = i + 1; k < size; k++)
                {
                    if (frames[j] == string[k])
                        break;
                }
                if (k == size)
                {
                    index = j;
                    break;
                }
                if (k > farthest)
                {
                    farthest = k;
                    index = j;
                }
                if (frames[j] == -1)
                {
                    index = j;
                    break;
                }
            }
            frames[index] = symbol;
            cout << "\nSymbol: " << symbol << "  Frame: ";
            for (int j = 0; j < n; j++)
            {
                if (frames[j] == -1)
                    cout << " ";
                else
                    cout << frames[j] << " ";
            }
        }
    }
    cout << "\nPage hits: " << page_hits;
    cout << "\nPage misses: " << size - page_hits;
    cout << "\nRatio of Page Hit: " << (float)page_hits / size;
    cout << "\nRatio of Page miss: " << (float)(size - page_hits) / size << endl;
}

int main()
{
    int n, no_frames;
    cout << "Enter number of pages: ";
    cin >> n;
    int pages[n];
    cout << "Enter the page reference sequence: ";
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }
    cout << "Enter the number of frames: ";
    cin >> no_frames;
    int choice;
    cout << "Enter Choice:\n1. FIFO\t 2. LRU\t 3. Optimal: ";
    cin >> choice;
    if (choice == 1)
        fifo(pages, no_frames, n);
    else if (choice == 2)
        lru(pages, no_frames, n);
    else if (choice == 3)
        optimal(pages, no_frames, n);
    else
        cout << "Enter valid choice!!" << endl;
    return 0;
}
