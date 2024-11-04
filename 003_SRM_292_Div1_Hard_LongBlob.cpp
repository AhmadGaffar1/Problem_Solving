#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

struct node{int r,c,cost;};

class LongBlob
{
public:
	double maxLength(vector<string> v)
	{
		prepare(v);
		for(int i=0;i<row;i++) for(int j=0;j<col;j++) search(i,j);
		return result;
	}

private:
	double result,****dis;
	vector<string> v;
	vector<vector<node>> on;
	int row,col,one;
	bool visit[25][25];

	void prepare(vector<string> v0)
	{
		result=0; v=v0; row=v.size(); col=v[0].size(); one=0;
		dis=new double ***[25];
		for(int i=0;i<25;i++) dis[i]=new double **[25];
		for(int i=0;i<25;i++) for(int j=0;j<25;j++) dis[i][j]=new double *[25];
		for(int i=0;i<25;i++) for(int j=0;j<25;j++) for(int k=0;k<25;k++) dis[i][j][k]=new double [25];
		for(int i=0;i<25;i++) for(int j=0;j<25;j++) for(int k=0;k<25;k++) for(int m=0;m<25;m++) dis[i][j][k][m]=-1;
		for(int i=0;i<row;i++) for(int j=0;j<col;j++) for(int k=0;k<row;k++) for(int m=0;m<col;m++) if(dis[i][j][k][m]==-1) distance(i,j,k,m);
		for(int i=0;i<=4;i++) {vector<node> x; on.push_back(x);}
	}

	void distance(int x0,int y0,int x1,int y1)
	{
		dis[x0][y0][x1][y1]=dis[x1][y1][x0][y0]=sqrt((double)pow(x1-x0,2)+pow(y1-y0,2));
	}

	void search(int r,int c)
	{
		for(int i=0;i<25;i++) for(int j=0;j<25;j++) visit[i][j]=false;
		for(int i=0;i<=4;i++) on[i].clear();
		node x; x.r=r; x.c=c; x.cost=0; if(v[r][c]=='1') x.cost=1;
		visit[r][c]=true; on[x.cost].push_back(x);

		for(int i=0;i<=4;i++)
		{
			for(int j=0;j<on[i].size();j++) go(on[i][j].r,on[i][j].c,on[i][j].cost,'0');
			if(i<4) for(int j=0;j<on[i].size();j++) go(on[i][j].r,on[i][j].c,on[i][j].cost,'1');
		}

		for(int i=0;i<row;i++) for(int j=0;j<col;j++) if(visit[i][j]==true) result=max(result,dis[r][c][i][j]);
	}

	void go(int r,int c,int cost,char flag)
	{
		if(r>0     && v[r-1][c]==flag && visit[r-1][c]==false) {visit[r-1][c]=true; node x; x.r=r-1; x.c=c; x.cost=cost+(flag-'0'); on[x.cost].push_back(x);}
		if(r<row-1 && v[r+1][c]==flag && visit[r+1][c]==false) {visit[r+1][c]=true; node x; x.r=r+1; x.c=c; x.cost=cost+(flag-'0'); on[x.cost].push_back(x);}
		if(c>0     && v[r][c-1]==flag && visit[r][c-1]==false) {visit[r][c-1]=true; node x; x.r=r; x.c=c-1; x.cost=cost+(flag-'0'); on[x.cost].push_back(x);}
		if(c<col-1 && v[r][c+1]==flag && visit[r][c+1]==false) {visit[r][c+1]=true; node x; x.r=r; x.c=c+1; x.cost=cost+(flag-'0'); on[x.cost].push_back(x);}
	}
};
