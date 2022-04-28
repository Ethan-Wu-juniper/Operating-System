#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,i,time=0,Wait=0,Turn=0;
    int arrival[11];
    int burst[11];
    int wait[11];
    int turn[11];
    memset(arrival,0,sizeof(arrival));
    memset(burst,0,sizeof(burst));
    memset(wait,0,sizeof(wait));
    memset(turn,0,sizeof(turn));
    ofstream file;
    file.open("hw2-1.txt");
    cin >> n;
    for(i=0;i<n;i++)
        cin >> arrival[i];
    for(i=0;i<n;i++)
        cin >> burst[i];
    for(i=0;i<n;i++)
    {
        time += burst[i];
        turn[i] = time - arrival[i];
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