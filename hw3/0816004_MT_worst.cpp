#include<bits/stdc++.h>
using namespace std;
#define PART 4
#define pii pair<int,int>

vector<int> List;
vector<pii> part;

struct Data
{
	int s=0,e=0,mid=0;
};
void partition_index(int size)
{
	int i,j;
	int unit = size / PART;
	int left = size % PART;
	for(i=0;i<PART;i++)
	{
		part[i].first = i * unit;
		part[i].second = (i+1) * unit -1;
	}
	part[PART-1].second += left;
}
void merge_index(int s,int e)
{
	part[s].second = part[e].second;
	part.erase(part.begin()+e);
}
void* sort(void* data)
{
	struct Data* strc =(struct Data*) data;
	int s = strc->s;
	int e = strc->e;
	int i,j;
	for(i=s;i<=e;i++)
		for(j=i+1;j<=e;j++)
		{
			if(List[j] < List[i])
			{
				int temp = List[i];
				List[i] = List[j];
				List[j] = temp;
			}
		}
	pthread_exit(NULL);
}
void* merge(void* data)
{
	struct Data* strc =(struct Data*) data;
	int s = strc->s;
	int e = strc->e;
	int mid = strc->mid;
	int i,j,List_i;
	vector<int> l,r;
	l.assign(List.begin()+s,List.begin()+mid+1);
	r.assign(List.begin()+mid+1,List.begin()+e+1);
	List_i = s;
	for(i=0,j=0;i<l.size() && j<r.size();)
	{
		if(l[i] < r[j])
			List[List_i++] = l[i++];
		else
			List[List_i++] = r[j++];
	}
	while(i<l.size())
		List[List_i++] = l[i++];
	while(j<r.size())
		List[List_i++] = r[j++];
	pthread_exit(NULL);
}

int main() 
{
	pthread_t t[PART] = {0};
	struct Data data[PART];
	int input,i=0,j;
	part.resize(PART);
	while(cin >> input)
		List.push_back(input);
	partition_index(List.size());

	for(i=0;i<PART;i++)
	{
		data[i].s = part[i].first;
		data[i].e = part[i].second;
		pthread_create(&t[i],NULL,sort,(void *)& data[i]);
	}
	for(i=0;i<PART;i++)
		pthread_join(t[i],NULL);
	while(part.size()!=1)
	{
		for(i=0;i<part.size()-1;i+=2)
		{
			data[i].s = part[i].first;
			data[i].e = part[i+1].second;
			data[i].mid = part[i].second;
			pthread_create(&t[i],NULL,merge,(void *)& data[i]);
		}
		for(i=0;i<part.size()-1;i+=2)
			pthread_join(t[i],NULL);
		for(i=0;i<part.size()-1;i++)
			merge_index(i,i+1);
	}
	for(i=0;i<List.size();i++)
		cout << List[i] << " ";
	
    return 0;
}