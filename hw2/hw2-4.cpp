#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>

struct cmp
{
    bool operator()(pii a,pii b)
    {
        if(a.second != b.second)
            return a.second > b.second;
        else
            return a.first > b.first;
    }
};

int main()
{
    int n,i,j,next,time=0,Wait=0,Turn=0,t; // t = time unit
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
    queue<int> q;
    priority_queue<pii,vector<pii>,cmp> pq;
    ofstream file;
    file.open("hw2-4.txt");
    cin >> n;
    for(i=0;i<n;i++)
        cin >> arrival[i];
    for(i=0;i<n;i++)
    {
        cin >> burst[i];
        remain[i] = burst[i];
    }
    cin >> t;
    q.push(0);
    in_queue[0] = true;
    while(!q.empty() || !pq.empty())
    {
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            int period = min(t,remain[cur]);
            time += period;
            remain[cur] -= period;
            for(j=0;j<n;j++)
            {
                if(arrival[j] > time)
                    break;
                else if(arrival[j]<=time && !in_queue[j] && remain[j]!=0)
                {
                    q.push(j);
                    in_queue[j] = true;
                }
            }
            if(remain[cur] == 0)
            {
                end_time[cur] = time;
            }
            else
            {
                pq.push({cur,remain[cur]});
            }
            //cout << "RR " << "cur: " << cur << " time: " << time << endl;
        }
        while(!pq.empty())
        {
            int cur = pq.top().first;
            next = INT_MAX;
            int next_i;
            for(i=0;i<n;i++)
            {
                if(arrival[i] > time)
                {
                    next = arrival[i];
                    next_i = i;
                    break;
                }
            }
            int period = min(time+remain[cur],next) - time;
            time += period;
            remain[cur] -= period;
            if(remain[cur] == 0)
            {
                pq.pop();
                end_time[cur] = time;
            }
            else
            {
                pq.pop();
                pq.push({cur,remain[cur]});
            }
            //cout << "SRTF " << "cur: " << cur << " time: " << time << endl;
            if(next == time)
            {
                q.push(next_i);
                break;
            }
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