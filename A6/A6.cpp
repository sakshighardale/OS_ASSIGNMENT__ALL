#include<bits/stdc++.h> 
using namespace std;

void calculateFragmentation(int originalBlockSize[], int blockSize[], int m, int allocation[], int processSize[], int n)
{
int internalFrag[n];
int totalInternalFrag = 0, externalFrag = 0;

// Calculate internal fragmentation per process 
for (int i = 0; i < n; i++)
{
if (allocation[i] != -1)
{
int blockIndex = allocation[i]; 
internalFrag[i] = blockSize[blockIndex]; 
totalInternalFrag += internalFrag[i];
}
else
{
internalFrag[i] = -1; // Not allocated
}
}

// Calculate external fragmentation 
for (int j = 0; j < m; j++)
{
if (blockSize[j] == originalBlockSize[j]) // Block never allocated 
externalFrag += blockSize[j];
}

// Display internal fragmentation per process
cout << "\nProcess No.\tProcess Size\tBlock no.\tInternal Frag\n"; 
for (int i = 0; i < n; i++)
{
cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
 
if (allocation[i] != -1)
{
cout << allocation[i] + 1 << "\t\t" << internalFrag[i] << endl;
}
else
{
cout << "Not Allocated\t" << "-" << endl;
}
}

}

// First Fit Algorithm
void firstFit(int originalBlockSize[], int blockSize[], int m, int processSize[], int n)
{
int allocation[n]; 
for(int i = 0; i < n; i++)
allocation[i] = -1;

for (int i = 0; i < n; i++)
{
for (int j = 0; j < m; j++)
{
if (blockSize[j] >= processSize[i])
{
allocation[i] = j;
blockSize[j] -= processSize[i]; break;
}
}
}

cout << "\n--- First Fit Allocation ---";
calculateFragmentation(originalBlockSize, blockSize, m, allocation, processSize, n);
}

// Best Fit Algorithm
void bestFit(int originalBlockSize[], int blockSize[], int m, int processSize[], int n)
{
int allocation[n];
 
for (int i = 0; i < n; i++) allocation[i] = -1;

for (int i = 0; i < n; i++)
{
int bestIdx = -1;
for (int j = 0; j < m; j++)
{
if (blockSize[j] >= processSize[i])
{
if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) bestIdx = j;
}
}

if (bestIdx != -1)
{
allocation[i] = bestIdx; blockSize[bestIdx] -= processSize[i];
}
}

cout << "\n--- Best Fit Allocation ---";
calculateFragmentation(originalBlockSize, blockSize, m, allocation, processSize, n);
}

// Worst Fit Algorithm
void worstFit(int originalBlockSize[], int blockSize[], int m, int processSize[], int n)
{
int allocation[n];
for (int i = 0; i < n; i++) allocation[i] = -1;

for (int i = 0; i < n; i++)
{
int worstIdx = -1;
for (int j = 0; j < m; j++)
{
if (blockSize[j] >= processSize[i])
{
 
if (worstIdx == -1 || blockSize[worstIdx] < blockSize[j]) worstIdx = j;
}
}

if (worstIdx != -1)
{
allocation[i] = worstIdx; blockSize[worstIdx] -= processSize[i];
}
}

cout << "\n--- Worst Fit Allocation ---";
calculateFragmentation(originalBlockSize, blockSize, m, allocation, processSize, n);
}

// Next Fit Algorithm
void nextFit(int originalBlockSize[], int blockSize[], int m, int processSize[], int n)
{
int allocation[n];
int lastAllocated = 0; for (int i = 0; i < n; i++)
allocation[i] = -1;

for (int i = 0; i < n; i++)
{
int j = lastAllocated; int count = 0;
while (count < m)
{
if (blockSize[j] >= processSize[i])
{
allocation[i] = j;
blockSize[j] -= processSize[i]; lastAllocated = j;
break;
}
j = (j + 1) % m; count++;
}
 
}

cout << "\n--- Next Fit Allocation ---";
calculateFragmentation(originalBlockSize, blockSize, m, allocation, processSize, n);
}


int main()
{
int n, m;
cout << "Enter the number of blocks: "; cin >> m;
int blockSize[m], originalBlockSize[m]; cout << "Enter the block sizes: ";
for (int i = 0; i < m; i++)
{
cin >> blockSize[i];
originalBlockSize[i] = blockSize[i]; // Save original block sizes
}

cout << "Enter the number of processes: "; cin >> n;
int processSize[n];
cout << "Enter the process sizes: "; for (int i = 0; i < n; i++)
{
cin >> processSize[i];
}

int choice; do
{
cout << "\nMemory Allocation Techniques: \n"
<< "1. First Fit\n"
<< "2. Best Fit\n"
<< "3. Worst Fit\n"
<< "4. Next Fit\n"
<< "5. Exit\n"
<< "Enter your choice: "; cin >> choice;
 
// Restore original block sizes before each technique 
for (int i = 0; i < m; i++)
blockSize[i] = originalBlockSize[i];

switch (choice)
{
case 1:
firstFit(originalBlockSize, blockSize, m, processSize, n); break;
case 2:
bestFit(originalBlockSize, blockSize, m, processSize, n); break;
case 3:
worstFit(originalBlockSize, blockSize, m, processSize, n); break;
case 4:
nextFit(originalBlockSize, blockSize, m, processSize, n); break;
case 5:
cout << "Exiting...\n"; break;
default:
cout << "Invalid choice! Please select 1, 2, 3, 4, or 5.\n"; break;
}
} while (choice != 5);

return 0;
}

