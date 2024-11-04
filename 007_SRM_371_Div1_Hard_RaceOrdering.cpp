#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

struct block{block(){node=0; patern=0;} long long node,patern;};

class RaceOrdering
{
public:
	int countOrders(int n,vector<int> v1,vector<int> v2)
	{
		prepare(n,v1,v2);
		relations();
		if(flag==false) return 0;
		integrations();
		return result.patern;
	}

private:
	long long n,bi,bn,way[33][33],*perm[30];
	vector<int> vp[30],vc[30],parent[30],blk[30];
	block res[30],result;
	bool visit[30],end[30],flag,ok[30][30];

	void prepare(int n,vector<int> v1,vector<int> v2)
	{
		this->n=n; bi=bn=0; flag=true;
		for(int i=0;i<33;i++) way[0][i]=0;
		for(int j=1;j<33;j++) way[1][j]=j;
		for(int i=2;i<33;i++) for(int j=1;j<33;j++) {way[i][j]=0; for(int k=j;k>=1;k--) way[i][j]+=way[i-1][k];}//count way of insert (i) node in (j) place;

		for(int i=0;i<v2.size();i++) {vp[v2[i]].push_back(v1[i]); vc[v1[i]].push_back(v2[i]);}
		for(int i=0;i<30;i++) {perm[i]=new long long [(1<<16)]; for(int j=0;j<(1<<16);j++) perm[i][j]=-1; perm[i][0]=1; end[i]=false;}
		for(int i=0;i<30;i++) for(int j=0;j<30;j++) ok[i][j]=true;
	}

	void relations()
	{
		for(int i=0;i<n && flag;i++)
		{
			for(int j=0;j<n;j++) end[j]=false;
			parents(i);
			for(int j=0;j<n;j++) if(end[j]==true && j!=i) {parent[i].push_back(j); ok[i][j]=false;}
		}

		for(int i=0;i<n;i++) end[i]=false;
		for(int i=0;i<n && flag;i++) if(end[i]==false)
		{
			for(int j=0;j<n;j++) visit[j]=false;
			family(i);
			for(int j=0;j<n;j++) if(visit[j]==true) blk[i].push_back(j);
		}
	}

	void parents(int index)
	{
		if(visit[index]==true) flag=false;
		visit[index]=true; end[index]=true;
		for(int i=0;i<vp[index].size() && flag;i++) parents(vp[index][i]);
		visit[index]=false;
	}

	void family(int index)
	{
		end[index]=true; visit[index]=true;
		for(int i=0;i<vp[index].size();i++) if(visit[vp[index][i]]==false) family(vp[index][i]);
		for(int i=0;i<vc[index].size();i++) if(visit[vc[index][i]]==false) family(vc[index][i]);
	}

	void integrations()
	{
		for(int i=0;i<n;i++) if(blk[i].size()>0) 
		{
			bi=i; 
			bn=blk[i].size(); 
			res[i].node=bn; 
			res[i].patern=calc(pow(2,blk[i].size())-1);
		}

		for(int i=0;i<n;i++) if(blk[i].size()>0) 
		{
			if(result.node==0) {result=res[i]; continue;}
			result.patern=way[result.node][res[i].node+1]*result.patern*res[i].patern; result.patern%=1000003;
			result.node+=res[i].node;
		}
	}

	long long calc(int mask)
	{
		if(perm[bi][mask]!=-1) return perm[bi][mask];
		perm[bi][mask]=0;
		for(int i=0;i<bn;i++) if(mask&(1<<i))
		{
			flag=true;
			for(int j=0;j<bn;j++) if((mask&(1<<j)) && ok[blk[bi][i]][blk[bi][j]]==false) {flag=false; break;}
			if(flag==true) {perm[bi][mask]+=calc(mask^(1<<i)); perm[bi][mask]%=1000003;}
		}
		return perm[bi][mask];
	}
};
