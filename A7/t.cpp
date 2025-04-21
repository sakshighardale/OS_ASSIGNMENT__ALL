#include<iostream>
using namespace std;

void fifo(int pages[20],int numFrames, int sizePages)
{
    int frames[numFrames];
    for(int i=0;i<numFrames;i++) frames[i]=-1;

    int index=-1;
    int pageHits=0;
    for(int i=0;i<sizePages;i++)
    {
        int symbol=pages[i];
        int flag=0;
        for(int j=0;j<numFrames;j++)
        {
            if(symbol==frames[j])
            {
                flag=1;
                break;
            }
        }

        if(flag==1)
        {
            cout<<"\nSymbol "<<symbol<<" Frames :";
            for(int j=0;j<numFrames;j++)
            {
                cout<<frames[j]<<" ";
            }
            pageHits+=1;
        }
        else
        {
            index=(index+1)%numFrames;
            frames[index]=symbol;
            cout<<"\nSymbol "<<symbol<<" Frames :";
            for(int j=0;j<numFrames;j++)
            {
                cout<<frames[j]<<" ";
            }
        }
    }
    cout<<"\nPage hits :"<<pageHits<<"\nPage miss :"<<(sizePages-pageHits)<<"\n Page hit ratio :"<<(float)pageHits/sizePages<<"\nPage miss ratio :"<<(float)(sizePages-pageHits)/sizePages<<endl;
}

void lru(int pages[20],int numFrames, int sizePages){
    int frames[numFrames];
    for(int i=0;i<numFrames;i++) frames[i]=-1;

    int index=-1;
    int pageHits=0;
    for(int i=0;i<sizePages;i++)
    {
        int symbol=pages[i];
        int flag=0;
        int full=0;
        for(int j=0;j<numFrames;j++)
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
            for(int j=0;j<numFrames;j++)
            {
                cout<<frames[j]<<" ";
            }
        }
        else{
            if(full==0)
            {
                index=(index+1)%numFrames;
                frames[index]=symbol;
                 cout<<"\nSymbol "<<symbol<<" Frames :";
                for(int j=0;j<numFrames;j++)
                {
                    cout<<frames[j]<<" ";
                }
            }
            else{
                int pos=999;
                int index=-1;
                for(int j=0;j<numFrames;j++)
                {
                    for(int k=0;k<sizePages;k++)
                    {
                        if(frames[j]==pages[k])
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
   cout<<"\nPage hits :"<<pageHits<<"\nPage miss :"<<(sizePages-pageHits)<<"\n Page hit ratio :"<<(float)pageHits/sizePages<<"\nPage miss ratio :"<<(float)(sizePages-pageHits)/sizePages<<endl;
}

void optimal(int pages[20],int numFrames, int sizePages)
{
    int frames[numFrames];
    for(int i=0;i<numFrames;i++)
    {
        frames[i]=-1;
    }
    int pageHits=0;

    for(int i=0;i<sizePages;i++)
    {
        int symbol=pages[i];
        int flag=0;
        for(int j=0;j<numFrames;j++)
        {
            if(symbol==frames[j])
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            cout<<"\nSymbol "<<symbol<<" Frames :";
            for(int j=0;j<numFrames;j++)
            {
                cout<<frames[j]<<" ";
            }
            pageHits++;
        }
        else{
            int index=-1;
            int farthest=i+1;
            for(int j=0;j<numFrames;j++)
            {
                int k;
                for(k=i+1;k<sizePages;k++)
                {
                    if(frames[j]==pages[k])
                    {
                        break;
                    }
                }
                if(k==sizePages)
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
            frames[index]=symbol;
            cout << "\nSymbol: " << symbol << "  Frame: ";
            for (int j = 0; j < numFrames; j++)
            {
                    cout << frames[j] << " ";
            }
        }
    }
cout<<"\nPage hits :"<<pageHits<<"\nPage miss :"<<(sizePages-pageHits)<<"\n Page hit ratio :"<<(float)pageHits/sizePages<<"\nPage miss ratio :"<<(float)(sizePages-pageHits)/sizePages<<endl;
}
int main()
{
    int n, numFrames;
    cout<<"Enter number of pages :";
    cin>>n;
    int pages[n];
    cout<<"Enter page sequences :";
    for(int i=0;i<n;i++) cin>>pages[i];
    cout<<"Enter number of frames :";
    cin>>numFrames;
    fifo(pages,numFrames,n);
    lru(pages,numFrames,n);
    optimal(pages,numFrames,n);
    return 0;
}