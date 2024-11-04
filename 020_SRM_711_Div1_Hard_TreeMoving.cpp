////////////////////////////////////////////////////// library
#include<iostream>
#include<vector>
using namespace std;
////////////////////////////////////////////////////// variable
long long result,numTree,numNode,ret;
vector<short> tree[300][300];
pair<short,short> edge[300][300];
short depth[300][300],lca[300][300][300],least;
long long path[2][300][300],dis[300],x,y;
bool b[300][300],visit[300],flag;
////////////////////////////////////////////////////// function
class TreeMoving
{
public:
	int count(int n,vector<int> root,vector<int> a,vector<int> b,vector<int> c)
	{
		prepare(n,root,a,b,c);
		for(int i=0;i<numTree;i++) depths(i,0,-1,0);
		for(int i=1;i<numTree;i++) for(int j=0;j<numNode-1;j++) LCA(i,edge[i-1][j]);
		for(int i=0;i<numNode-1;i++) count(i);
		return result;
	}

private:
	void prepare(int n,vector<int> root,vector<int> a,vector<int> b,vector<int> c)
	{
		result=0; numTree=root.size(); numNode=n; ret=0; flag=false; least=1000;
		for(int i=0;i<300;i++) for(int j=0;j<300;j++) ::b[i][j]=true;
		long long x[300],u[300],v[300];
		for(int i=0;i<numTree;i++)
		{
			x[0]=c[i];
			for(int k=1;k<=(numNode-2);k++) x[k]=((long long)a[i]*x[k-1]+b[i])%1000000007;
			for(int j=0;j<=(numNode-2);j++)
			{
				u[j]=((long long)root[i]+j+1)%numNode;
				v[j]=((long long)root[i]+(x[j]%(j+1)))%numNode;
				pair<short,short> tmp(min(u[j],v[j]),max(u[j],v[j]));

				tree[i][u[j]].push_back(v[j]);
				tree[i][v[j]].push_back(u[j]);
				edge[i][j]=tmp;
			}
		}
	}

	void depths(short t,short now,short from,short step)
	{
		depth[t][now]=step;
		for(int i=0;i<tree[t][now].size();i++) if(tree[t][now][i]!=from) depths(t,tree[t][now][i],now,step+1);
	}

	void LCA(short t,pair<short,short> e)
	{
		flag=false; least=1000; 
		findPath(t,e.first,-1,e.first,e.second);
	}

	void findPath(short t,short now,short from,short start,short target)
	{
		if(now==target) flag=true;
		for(int i=0;flag==false && i<tree[t][now].size();i++) if(tree[t][now][i]!=from) findPath(t,tree[t][now][i],now,start,target);
		if(flag==true && depth[t][now]<least) {least=depth[t][now]; /**/ lca[t][start][target]=lca[t][target][start]=now;}
	}

	void count(short e)
	{
		for(int i=0;i<300;i++) for(int j=0;j<300;j++) path[0][i][j]=path[1][i][j]=0; /**/ x=-1; y=0;
		b[edge[0][e].first][edge[0][e].second]=b[edge[0][e].second][edge[0][e].first]=false;
		for(int i=0;i<numNode-1;i++) {baseCase(edge[0][e],edge[numTree-1][i]);}
		b[edge[0][e].first][edge[0][e].second]=b[edge[0][e].second][edge[0][e].first]=true;
		for(int j=numTree-2;j>=0;j--) {x=(x+1)%2; y=(y+1)%2; /**/ distance(j+1,0,-1,0); calc(j);}
		result=(result+path[x][edge[0][e].first][edge[0][e].second])%1000000007;
	}

	bool baseCase(pair<short,short> out,pair<short,short> in)
	{
		if(in.first==out.first && in.second==out.second) {path[1][in.first][in.second]=path[1][in.second][in.first]=1; return 0;}
		tree[0][in.first].push_back(in.second);
		tree[0][in.second].push_back(in.first);
		for(int i=0;i<300;i++) visit[i]=false; ret=0; dfs(0); if(ret==numNode) path[1][in.first][in.second]=path[1][in.second][in.first]=1;
		tree[0][in.first].pop_back();
		tree[0][in.second].pop_back();
		return 0;
	}

	void dfs(short index)
	{
		visit[index]=true; ret++;
		for(int i=0;i<tree[0][index].size();i++) if(b[index][tree[0][index][i]]==true && visit[tree[0][index][i]]==false) dfs(tree[0][index][i]);
	}

	void distance(short t,short now,short from,long long val)
	{
		dis[now]=val;
		for(int i=0;i<tree[t][now].size();i++) if(tree[t][now][i]!=from) distance(t,tree[t][now][i],now,dis[now]+path[y][now][tree[t][now][i]]);
	}

	void calc(short t)
	{
		for(int i=0;i<numNode-1;i++) path[x][edge[t][i].first][edge[t][i].second]=path[x][edge[t][i].second][edge[t][i].first] = 
			(dis[edge[t][i].first]+dis[edge[t][i].second]-2*dis[lca[t+1][edge[t][i].first][edge[t][i].second]])%1000000007;
	}
};
