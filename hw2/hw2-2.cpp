#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,i,j,next,min,time=0,Wait=0,Turn=0;
    int arrival[11];
    int burst[11];
    int wait[11];
    int turn[11];
    bool done[11];
    memset(arrival,0,sizeof(arrival));
    memset(burst,0,sizeof(burst));
    memset(wait,0,sizeof(wait));
    memset(turn,0,sizeof(turn));
    memset(done,0,sizeof(done));
    ofstream file;
    file.open("hw2-2.txt");
    cin >> n;
    for(i=0;i<n;i++)
        cin >> arrival[i];
    for(i=0;i<n;i++)
        cin >> burst[i];
    for(i=0;i<n;i++)
    {
        min = INT_MAX;
        for(j=0;j<n;j++)
        {
            if(time>=arrival[j] && !done[j] && min > burst[j])
            {
                next = j;
                min = burst[j];
            }
        }
        time += burst[next];
        turn[next] = time - arrival[next];
        wait[next] = turn[next] - burst[next];
        done[next] = true;
    }
    for(i=0;i<n;i++)
    {
        cout << "P" << i << ": " << wait[i] << " " << turn[i] << endl;
        file << wait[i] << " " << turn[i] << endl;
        Wait += wait[i];
        Turn += turn[i];
    }
    cout << "Total waiting time: " << Wait << endl;
    cout << "Total turnaround time: " << Turn << endl;
    file << Wait << endl;
    file << Turn << endl;
    file.close();
    return 0;
}