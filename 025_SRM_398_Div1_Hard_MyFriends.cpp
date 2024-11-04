#include<iostream>
#include<vector>
#include<string>
using namespace std;

string result;
int size,k,degree[50],mini,maxi;
vector<int> v,head,z;
bool visit[50];

class MyFriends
{
public:
	string calcFriends(vector<int> v,int k)
	{
		prepare(v,k);
		groups();
		merge();
		repair();
		for(;maxi<size;) search();
		return result;
	}

	void prepare(vector<int> v_,int k_)
	{
		v=v_; k=k_; size=v.size(); mini=2e9; maxi=-2e9; result="IMPOSSIBLE";
	}

	void groups()
	{
		for(int i=0;i<size;i++) if(visit[i]==false)
		{
			head.push_back(i);
			degree[i]=0;
			visit[i]=true;
			equations(i,(((i+k)%size)+k)%size,v[i],v[((i+k)%size)]);
		}
	}

	void merge()
	{
		for(int i=0;i<50;i++) visit[i]=false;
		for(int i=1;i<head.size();i++)
		{
			int I=head[i],sum=v[0]+degree[0]+degree[k%size]-v[I],diff=degree[I]-degree[(I+k)%size];
			if(sum%2==0 && diff%2==0) degree[I]=sum/2+diff/2;
			if(sum%2!=0 && diff%2!=0) degree[I]=(sum+1)/2+(diff+1)/2-1;
			equations(I,(((I+k)%size)+k)%size,v[I],v[((I+k)%size)]);
		}
	}

	bool equations(int index,int supSup,int ans1,int ans2)
	{
		//degree[supSup]-degree[index]=(ans1-ans2);
		if(visit[supSup]==true) return 0;
		visit[supSup]=true;
		degree[supSup]=(ans1-ans2)+degree[index];
		equations(supSup,(((supSup+k)%size)+k)%size,v[supSup],v[((supSup+k)%size)]);
		return 0;
	}

	void repair()
	{
		for(int i=0;i<size;i++)
		{
			if(degree[i]<mini) mini=degree[i];
			if(degree[i]>maxi) maxi=degree[i];
		}

		for(int i=0;i<size;i++) degree[i]+=abs(mini);
		maxi+=abs(mini);
	}

	bool search()
	{
		for(int i=0;i<size;i++)
		{
			int sum=0;
			for(int j=0;j<size;j++) if(j!=i && j!=((i+k)%size)) sum+=degree[j];
			
			if(sum>v[i]) {maxi=2e9; return 0;}
			if(sum<v[i]) {for(int j=0;j<size;j++) degree[j]++; /**/ maxi++; return 0;}
		}

		z.clear();
		for(int i=0;i<size;i++) z.push_back(degree[i]);
		if(back()>0) {maxi=2e9; return 0;}

		result="POSSIBLE";
		maxi=2e9;
		return 0;
	}

	int back()
	{
		int tmp=0;
		for(int i=0;i<size;i++) {for(int j=i+1;j<size;j++) if(z[j]>z[i]) {tmp=z[i]; z[i]=z[j]; z[j]=tmp;}}

		if(z[0]==0) return 0;
		for(int j=1;j<size && z[0]>0;j++) 
		{
			if(z[j]==0) return 1;
			z[0]--; z[j]--;
		}
		return back();
	}
};
