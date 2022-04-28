#include <bits/stdc++.h>
using namespace std;

#define n 3

int len,done=0;
pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t out = PTHREAD_MUTEX_INITIALIZER;
string input;
long long int cnt[3];
struct Data
{
    int s=0,e=0,index=0;
};
void *count(void* data)
{
    struct Data *strc = (struct Data*) data;
    int s = strc->s;
    int e = strc->e;
    int index = strc->index;
    int i;
    pthread_mutex_lock(&Mutex);
    for(i=s;i<=e;i++)
    {
        //cout << "i : " << i << " ,input : " << (int)input[i] - 48 << endl;
        cnt[input[i]-48]++;
    }
    pthread_mutex_unlock(&Mutex);
    while(1)
        if((cnt[0]+cnt[1]+cnt[2]) == len) break;
    while(1)
    {
        if(index == done)
        {
            pthread_mutex_lock(&out);
            done++;
            break;
        }
    }
    cout << index << ": " << cnt[index] << endl;
    pthread_mutex_unlock(&out);
    return 0;
}

int main()
{
    int i,part,s=0;
    cin >> len;
    part = len/n;
    cin.get();
    getline(cin,input);
    //cout << input.size() << endl;
    pthread_t t[n] = {0};
    struct Data data[n];
    for(i=0;i<n;i++)
    {
        data[i].index = i;
        data[i].s = s;
        data[i].e = s + part-1;
        s = data[i].e + 1;
        //cout << "s : " << data[i].s << " ,e : " << data[i].e << endl;
    }
    data[n-1].e = len - 1;
    for(i=0;i<n;i++)
        pthread_create(&t[i],NULL,count,(void *)& data[i]);
    for(i=0;i<n;i++)
        pthread_join(t[i],NULL);
    return 0;
}