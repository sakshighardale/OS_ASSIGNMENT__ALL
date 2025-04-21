#include<iostream>
using namespace std;

void fifo(int string[20],int n, int size)
{
    int frames[n];
    for(int i=0;i<n;i++)
    {
        frames[i]=-1;
    }
    int index=-1;
    int page_hits=0;
    for(int i=0;i<size;i++)
    {
        int symbol=string[i];
        int flag=0;
        for(int j=0;j<n;j++)
        {
            if(symbol==frames[j])
            {   
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            page_hits+=1;
            cout<<"\nSymbol"<<symbol<<" Frame : ";
            for(int j=0;j<n; j++)
            {
                cout<<frames[j]<<" ";
            }
        }
        else{
            index=(index+1)%n;
            frames[index]=symbol;
            cout<<"\nSymbol "<<symbol<<" Frame : ";
            for(int j=0;j<n;j++)
            {
                cout<<frames[j]<<" ";
            }
        }
    }

    cout<<"\n Page hits :"<<page_hits<<"\nPage miss :"<<size-page_hits<<"\n Page hit ratio :"<<(float)page_hits/size<<"\n Page miss ratio :"<<(float)(size-page_hits)/size<<endl;
}

void lru(int string[20],int n, int size)
{
    int frames[n];
    for(int i=0;i<n;i++) frames[i]=-1;
    int index=-1;
    int pageHits=0;
    for(int i=0;i<size;i++)
    {
        int symbol=string[i];
        int flag=0;
        int full=0;
        for(int j=0;j<n;j++)
        {
            if(symbol==frames[j])
            {
                flag=1;
                break;
            }
        }

        if(flag==1)
        {
            pageHits++;
            cout<<"\nSymbol "<<symbol<<" Frames :";
            for(int j=0;j<n;j++)
            {
                cout<<frames[j]<<" ";
            }
        }
        else{
            if(full==0)
            {
                index=(index+1)%n;
                frames[index]=symbol;
                cout<<"\nSymbol "<<symbol<<" Frames :";
                for(int j=0;j<n;j++)
                {
                    cout<<frames[j]<<" ";
                }
                full++;
            }
            else
            {
                int pos=999;
                int index=-1;
                for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                {
                    if(frames[j]==string[k])
                    {
                        if(pos>k)
                        {
                            pos=k;
                            index=j;
                            break;
                        }
                    }
                }
                frames[index]=symbol;
            }
        }
    }
     cout<<"\n Page hits :"<<pageHits<<"\nPage miss :"<<size-pageHits<<"\n Page hit ratio :"<<(float)pageHits/size<<"\n Page miss ratio :"<<(float)(size-pageHits)/size<<endl;
}

void optimal(int string[20],int n, int size)
{
    int frames[n];
    for(int i=0;i<n;i++) frames[i]=-1;

    int pageHits=0;
    for(int i=0;i<size;i++)
    {
        int symbol=string[i];
        int flag=0;
        for(int j=0;j<n;j++)
        {
            if(symbol==frames[j])
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            pageHits++;
            cout<<"\nSymbol "<<symbol<<" Frames :";
            for(int j=0;j<n;j++)
            {
                cout<<frames[j]<<" ";
            }
        }
        else{
            int index=-1;
            int farthest=i+1;
            for(int j=0;j<n;j++)
            {
                int k;
                for(k=i+1;k<size;k++)
                {
                    if(frames[j]==string[k])
                    break;
                }
                if(k==size)
                {
                    index=j;
                    break;
                }
                if(k>farthest)
                {
                    farthest=k;
                    index=j;
                }
                if(frames[j]==-1)
                {
                    index=j;
                    break;
                }
            }
            frames[index] = symbol;
            cout << "\nSymbol: " << symbol << "  Frame: ";
            for (int j = 0; j < n; j++)
            {
                    cout << frames[j] << " ";
            }
        }
    }
    cout<<"\n Page hits :"<<pageHits<<"\nPage miss :"<<size-pageHits<<"\n Page hit ratio :"<<(float)pageHits/size<<"\n Page miss ratio :"<<(float)(size-pageHits)/size<<endl;
}
int main()
{
    int n, numFrames;
    cout<<"Enter number of pages :";
    cin>>n;
    int pages[n];
    cout<<"Enter page references :";
    for(int i=0;i<n;i++)
    {
        cin>>pages[i];
    }
    cout<<"Enter frame capacity :";
    cin>>numFrames;

    fifo(pages,numFrames,n);
    lru(pages,numFrames,n);
    optimal(pages,numFrames,n);
    return 0;
}