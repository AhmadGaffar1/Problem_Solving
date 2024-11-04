#include<iostream>
#include<vector>
#include<string>
using namespace std;

int result,size,node[202][202],n[202][202],a=0,z=50,mid=(a+z)/2;
int b,g,bk,gk,source,sink;
bool visit[202];

class DancingParty
{
public:
	int maxDances(vector<string> like,int k)
	{
		prepare(like);
		maxFlowNetwork(like,k);
		for(;a!=z;) rounds();
		result=mid;
		return result;
	}

	void prepare(vector<string> like)
	{
		size=like.size();
		b=0; g=size; bk=2*size; gk=3*size; source=200; sink=201;
	}

	void maxFlowNetwork(vector<string> like,int k)
	{
		for(int i=0;i<size;i++) for(int j=0;j<size;j++)
		{
			if(like[i][j]=='Y') node[i+b][j+g]=1;
			else                node[i+bk][j+gk]=1;
		}
		for(int i=0;i<size;i++)
		{
			node[i+b][i+bk]=k;
			node[i+gk][i+g]=k;
		}
	}

	void rounds()
	{
		for(int i=0;i<202;i++) for(int j=0;j<202;j++) n[i][j]=node[i][j];
		for(int i=0;i<size;i++) {n[source][i+b]=mid; n[i+g][sink]=mid;}

		result=0;
		for(int i=0;i<202;i++) visit[i]=false;
		for(int i=1;maxFlow(source);i++) 
		{
			for(int i=0;i<202;i++) visit[i]=false;
			result++;
		}
		if(result==(mid*size)) {a=mid;   mid=(a+1+z)/2;}
		else                   {z=mid-1; mid=(a+z)/2;}
	}

	bool maxFlow(int index)
	{
		visit[index]=true;
		if(index==sink) return true;
		for(int i=0;i<202;i++) if(n[index][i]>0 && visit[i]==false && maxFlow(i)==true) {n[index][i]--; n[i][index]++; return true;}
		return false;
	}
};
