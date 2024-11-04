#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

vector<string> v;
vector<int> result,parent[50];
int size,node[50];
bool visit[50],back[50],label[50],p[50][50],flag;

class RelabelingOfGraph
{
public:
	vector<int> renumberVertices(vector<string> v)
	{
		prepare(v);
		for(int i=0;i<size && flag;i++) if(visit[i]==false) circle(i);
		for(int i=0;i<size && flag;i++) {for(int j=0;j<size;j++) visit[j]=false; dfs(i,i);}
		for(int i=0;i<size && flag;i++) sort(parent[i].begin(),parent[i].end());
		for(int i=0;i<size && flag;i++) if(node[i]==-1) assignement(i);
		for(int i=0;i<size && flag;i++) result.push_back(node[i]);
		return result;
	}

	void prepare(vector<string> v_)
	{
		v=v_; size=v.size(); flag=true;
		for(int i=0;i<50;i++) node[i]=-1;
	}

	void circle(int index)
	{
		visit[index]=true;
		for(int i=0;i<size && flag;i++) if(v[index][i]=='1')
		{
			if(visit[i]==false) circle(i);
			if(visit[i]==true && back[i]==false) flag=false;
		}
		back[index]=true;
	}

	void dfs(const int par,int index)
	{
		if(par!=index && p[index][par]==false) {p[index][par]=true; parent[index].push_back(par);}
		visit[index]=true;
		for(int i=0;i<size && flag;i++) if(v[index][i]=='1' && visit[i]==false) dfs(par,i);
	}

	void assignement(int index)
	{
		int numParent=0,numEmpty=0,I=0;
		for(int i=0;i<parent[index].size();i++) if(node[parent[index][i]]==-1) numParent++;
		for(int i=0;i<size && numEmpty<=numParent;i++) if(label[i]==false) {numEmpty++; I=i;} 

		node[index]=I; label[I]=true;
		for(int i=0;i<parent[index].size();i++) if(node[parent[index][i]]==-1)assignement(parent[index][i]);
	}
};
