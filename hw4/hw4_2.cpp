#include <bits/stdc++.h>
using namespace std;

pthread_mutex_t Mutex = PTHREAD_MUTEX_INITIALIZER;
int  cnt = 0;
struct Data
{
    int thread,part = 0;
};
void *solve(void *data)
{
    struct Data *strc = (struct Data*) data;
    int thread = strc->thread;
    int part = strc->part;
    int i;
    double x,y,dist;
    srand(time(NULL));
    pthread_mutex_lock(&Mutex);
    for(i=0;i<part;i++)
    {
        x = double(rand() % (part + 1)) / part;
        y = double(rand() % (part + 1)) / part;
        dist = x * x + y * y;
        if(dist <= 1)
            cnt++;
    }
    pthread_mutex_unlock(&Mutex);
    return 0;
}

int main()
{
    int thread,point,i;
    cin >> thread >> point;
    struct Data data[thread];
    pthread_t t[thread] = {0};
    for(i=0;i<thread;i++)
    {
        data[i].part = point / thread;
        data[i].thread = thread;
    }
    data[thread-1].part += point % thread;
    for(i=0;i<thread;i++)
        pthread_create(&t[i],NULL,solve,(void *)& data[i]);
    for(i=0;i<thread;i++)
        pthread_join(t[i],NULL);
    cout << double(cnt * 4) / point << endl;
    return 0;
}