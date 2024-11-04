#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

int result,row,col,r,c,res[50][50],visit[50][50];
vector<string> v;
vector<int> arrive[50][50];
int dx[8]={-1,-1,-1,0,0,1,1,1};
int dy[8]={-1,0,1,-1,1,-1,0,1};

class DesertWind
{
public:
	int daysNeeded(vector<string> v)
	{
		prepare(v);
		for(int i=0;i<4000;i++) dp(i);
		result=(res[r][c]!=2e9 ? res[r][c]:-1);
		return result;
	}

	void prepare(vector<string> v_)
	{
		v=v_; row=v.size(); col=v[0].size(); result=-1;
		for(int i=0;i<row;i++) for(int j=0;j<col;j++)
		{
			res[i][j]=2e9;
			if(v[i][j]=='@') {r=i; c=j;}
			if(v[i][j]=='*') {res[i][j]=0; visit[i][j]=1;}
		}
	}

	void dp(int t)
	{
		for(int i=0;i<row;i++) for(int j=0;j<col;j++) if(visit[i][j]==0)
		{
			if(arrive[i][j].size()==1) res[i][j]=3+arrive[i][j][0];
			if(arrive[i][j].size()>1)  {sort(arrive[i][j].begin(),arrive[i][j].end()); /**/ res[i][j]=min(3+arrive[i][j][0],1+arrive[i][j][1]);}
		}
		for(int i=0;i<row;i++) for(int j=0;j<col;j++) if(res[i][j]==t)
		{
			for(int k=0;k<8;k++) if(valid(i+dy[k],j+dx[k]) && visit[i+dy[k]][j+dx[k]]==0) arrive[i+dy[k]][j+dx[k]].push_back(res[i][j]);
			visit[i][j]=1;
		}
	}

	inline bool valid(int r,int c)
	{
		if(r>=0 && r<row && c>=0 && c<col && v[r][c]!='X') return true;
		return false;
	}
};
