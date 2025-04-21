#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include <string>
using namespace std;

class MemoryManager{
private:
    vector<int> Blocks;
    vector<int> Rem_Space;
    vector<vector<pair<string, int>>> Alloc;
    int lastIndex = 0;
    int Proc_Cnt = 1;
    string Last_Strat = "";

public:
    MemoryManager(vector<int> blocks)
        : Blocks(blocks), Rem_Space(blocks), Alloc(blocks.size()) {}

    void reset(){
        Rem_Space = Blocks;
        Alloc = vector<vector<pair<string, int>>>(Blocks.size());
        lastIndex = 0;
        Proc_Cnt = 1;
        cout << "Memory allocation reset.\n";
    }
    void DisplayMemory(){
        cout << "\nCurrent Memory Status:\n";
        for (size_t i = 0; i < Blocks.size(); ++i){
            cout << "Block " << i + 1 << " (" << Blocks[i] << " KB):\n";
            if (Alloc[i].empty()){
                cout << "  [Empty]\n";
            }
            else{
                for (const auto &alloc : Alloc[i]){
                    cout << "  " << alloc.first << " - " << alloc.second << " KB\n";
                }
            }
            cout << "  Remaining space: " << Rem_Space[i] << " KB\n";
            if (!Alloc[i].empty()){
                cout << "Internal Fragmentation: " << Rem_Space[i] << " KB\n";
            }
        }
    }
    bool allocate(int processSize, const string &strategy){
        string processName = "P" + to_string(Proc_Cnt++);
        int index = -1;
        if (strategy == "FirstFit"){
            for (size_t i = 0; i < Blocks.size(); ++i){
                if (Rem_Space[i] >= processSize){
                    index = i;
                    break;
                }
            }
        }
        else if (strategy == "BestFit"){
            int minWaste = numeric_limits<int>::max();
            for (size_t i = 0; i < Blocks.size(); ++i){
                if (Rem_Space[i] >= processSize){
                    int waste = Rem_Space[i] - processSize;
                    if (waste < minWaste){
                        minWaste = waste;
                        index = i;
                    }
                }
            }
        }
        else if (strategy == "WorstFit"){
            int maxWaste = -1;
            for (size_t i = 0; i < Blocks.size(); ++i){
                if (Rem_Space[i] >= processSize){
                    int waste = Rem_Space[i] - processSize;
                    if (waste > maxWaste){
                        maxWaste = waste;
                        index = i;
                    }
                }
            }
        }
        else if (strategy == "NextFit"){
            int startIndex = lastIndex;
            do{
                if (Rem_Space[lastIndex] >= processSize){
                    index = lastIndex;
                    break;
                }
                lastIndex = (lastIndex + 1) % Blocks.size();
            } while (lastIndex != startIndex);
        }
        if (index != -1){
            Rem_Space[index] -= processSize;
            Alloc[index].push_back({processName, processSize});
            cout << processName << " (" << processSize << " KB) allocated to Block " << index + 1 << "\n";
            if (strategy == "NextFit")
                lastIndex = (index + 1) % Blocks.size();
            return true;
        }
        else{
            cout << "Could not allocate " << processName << " (" << processSize << " KB) - No suitable block found (" << strategy << ").\n";
            return false;
        }
    }

    void batchAllocate(int count, const string &strategy){
        Last_Strat = strategy;
        for (int i = 0; i < count; ++i){
            int size;
            cout << "Enter size for process " << (i + 1) << " (KB): ";
            cin >> size;
            allocate(size, strategy);
        }
    }
};
int main(){
    int n;
    cout << "Enter number of memory blocks: ";
    cin >> n;
    vector<int> blocks(n);
    cout << "Enter sizes of memory blocks (in KB):\n";
    for (int i = 0; i < n; ++i){
        cout << "Block " << i + 1 << ": ";
        cin >> blocks[i];
    }
    MemoryManager manager(blocks);
    int choice;
    do{
        cout << "\nMemory Allocation Menu:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Next Fit\n";
        cout << "5. Reset Allocation\n";
        cout << "6. Show Memory Status\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        try{
            if (choice >= 1 && choice <= 4){
                int processCount;
                cout << "Enter number of processes to allocate: ";
                cin >> processCount;
                string strategy;
                if (choice == 1)
                    strategy = "FirstFit";
                else if (choice == 2)
                    strategy = "BestFit";
                else if (choice == 3)
                    strategy = "WorstFit";
                else
                    strategy = "NextFit";
                manager.batchAllocate(processCount, strategy);
            }
            else if (choice == 5){
                manager.reset();
            }
            else if (choice == 6){
                manager.DisplayMemory();
            }
            else if (choice == 0){
                cout << "Exiting...\n";
            }
            else{
                cout << "Invalid choice. Try again.\n";
            }
        }
        catch (const exception &e){
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 0);
    return 0;
}
