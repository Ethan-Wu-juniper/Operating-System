#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,i,j,time=0,Wait=0,Turn=0,q;
    int arrival[11];
    int burst[11];
    int remain[11];
    int wait[11];
    int turn[11];
    int end_time[11];
    bool in_queue[11];
    memset(arrival,0,sizeof(arrival));
    memset(burst,0,sizeof(burst));
    memset(remain,0,sizeof(remain));
    memset(wait,0,sizeof(wait));
    memset(turn,0,sizeof(turn));
    memset(end_time,0,sizeof(end_time));
    memset(in_queue,0,sizeof(in_queue));
    queue<int> Queue;
    ofstream file;
    file.open("hw2-3.txt");
    cin >> n;
    for(i=0;i<n;i++)
        cin >> arrival[i];
    for(i=0;i<n;i++)
    {
        cin >> burst[i];
        remain[i] = burst[i];
    }
    cin >> q;
    Queue.push(0);
    in_queue[0] = true;
    while(!Queue.empty())
    {
        int cur = Queue.front();
        Queue.pop();
        time += min(q,remain[cur]);
        remain[cur] -= min(q,remain[cur]);
        for(j=0;j<n;j++)
        {
            if(arrival[j] > time)
                break;
            else if(arrival[j]<=time && !in_queue[j] && remain[j]!=0)
            {
                Queue.push(j);
                in_queue[j] = true;
            }
        }
        if(remain[cur] != 0)
        {
            Queue.push(cur);
        }
        else
        {
            in_queue[cur] = false;
            end_time[cur] = time;
        }
    }
    for(i=0;i<n;i++)
    {
        turn[i] = end_time[i] - arrival[i];
        wait[i] = turn[i] - burst[i];
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