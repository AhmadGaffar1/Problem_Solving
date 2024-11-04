#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

struct node {short r,c,time,dir; double cost;};

class LateForConcert
{
public:
	double bestRoute(vector<string> g,int time,double speed,double red)
	{
		prepare(g,time,speed,red);
		search();
		return result;
	}

private:
	double result,speed,red;
	int time,row,col,r,c;
	int dis[50][50];
	vector<string> g;
	vector<queue<node*>> on;
	node *****cost;

	void prepare(vector<string> g0,int time0,double speed0,double red0)
	{
		result=2e9; g=g0; time=time0; speed=speed0; red=red0*0.7; row=g.size(); col=g[0].size();
		cost=new node ****[102];
		for(int i=0;i<102;i++) cost[i]=new node ***[50];
		for(int i=0;i<102;i++) for(int j=0;j<50;j++) cost[i][j]=new node **[50];
		for(int i=0;i<102;i++) for(int j=0;j<50;j++) for(int k=0;k<50;k++) cost[i][j][k]=new node *[4];
		for(int i=0;i<102;i++) for(int j=0;j<50;j++) for(int k=0;k<50;k++) for(int m=0;m<4;m++) {cost[i][j][k][m]=new node; cost[i][j][k][m]->cost=2e9;}

		node x,y;
		for(int i=0;i<row;i++) for(int j=0;j<col;j++)
		{
			if(g[i][j]=='Y') {x.r=i; x.c=j; x.time=0; x.cost=0; x.dir=' ';} 
			else if(g[i][j]=='C') {r=i; c=j;}
		}
		for(int i=0;i<102;i++) {queue<node*> x; on.push_back(x);}
		g[x.r][x.c]='.'; input(x);
		
		for(int i=0;i<50;i++) for(int j=0;j<50;j++) dis[i][j]=2e9; /**/ dis[r][c]=0;
		y.r=r; y.c=c; y.time=y.dir=y.cost=0; distance(y);
	}

	void distance(node tmp)
	{
		queue<node> v; v.push(tmp);
		for(;v.size();)
		{
			node x=v.front();
			if(x.r>0     && g[x.r-1][x.c]!='X' && dis[x.r-1][x.c]==2e9) {dis[x.r-1][x.c]=dis[x.r][x.c]+1; node y; y.r=x.r-1; y.c=x.c; v.push(y);}
			if(x.r<row-1 && g[x.r+1][x.c]!='X' && dis[x.r+1][x.c]==2e9) {dis[x.r+1][x.c]=dis[x.r][x.c]+1; node y; y.r=x.r+1; y.c=x.c; v.push(y);}
			if(x.c>0     && g[x.r][x.c-1]!='X' && dis[x.r][x.c-1]==2e9) {dis[x.r][x.c-1]=dis[x.r][x.c]+1; node y; y.r=x.r; y.c=x.c-1; v.push(y);}
			if(x.c<col-1 && g[x.r][x.c+1]!='X' && dis[x.r][x.c+1]==2e9) {dis[x.r][x.c+1]=dis[x.r][x.c]+1; node y; y.r=x.r; y.c=x.c+1; v.push(y);}
			v.pop();
		}
	}

	void search()
	{
		for(int i=1;i<time;i++) for(;on[i].size();)
		{
			node *x=on[i].front();
			if(x==cost[x->time][x->r][x->c][x->dir] && x->time+dis[x->r][x->c]<=time) input(*x);
			on[i].pop();
		}

		for(int d=0;d<4;d++) result=min(result,cost[time][r][c][d]->cost);
		if(result==2e9) result=-1;
	}

	inline void input(node x)
	{
		if(g[x.r][x.c]=='.' && x.r>0 && g[x.r-1][x.c]!='X'     && x.dir!=1) in(x.time+1,x.r-1,x.c,0,x.cost);
		if(g[x.r][x.c]=='.' && x.r<row-1 && g[x.r+1][x.c]!='X' && x.dir!=0) in(x.time+1,x.r+1,x.c,1,x.cost);
		if(g[x.r][x.c]=='.' && x.c>0 && g[x.r][x.c-1]!='X'     && x.dir!=3) in(x.time+1,x.r,x.c-1,2,x.cost);
		if(g[x.r][x.c]=='.' && x.c<col-1 && g[x.r][x.c+1]!='X' && x.dir!=2) in(x.time+1,x.r,x.c+1,3,x.cost);

		if(g[x.r][x.c]=='S' && x.r>0 && g[x.r-1][x.c]!='X'     && x.dir!=1) in(x.time+1,x.r-1,x.c,0,x.cost+speed);
		if(g[x.r][x.c]=='S' && x.r<row-1 && g[x.r+1][x.c]!='X' && x.dir!=0) in(x.time+1,x.r+1,x.c,1,x.cost+speed);
		if(g[x.r][x.c]=='S' && x.c>0 && g[x.r][x.c-1]!='X'     && x.dir!=3) in(x.time+1,x.r,x.c-1,2,x.cost+speed);
		if(g[x.r][x.c]=='S' && x.c<col-1 && g[x.r][x.c+1]!='X' && x.dir!=2) in(x.time+1,x.r,x.c+1,3,x.cost+speed);

		if(g[x.r][x.c]=='T' && x.r>0 && g[x.r-1][x.c]!='X'     && x.dir!=1) in(x.time+1,x.r-1,x.c,0,x.cost+red), in(x.time+2,x.r-1,x.c,0,x.cost);
		if(g[x.r][x.c]=='T' && x.r<row-1 && g[x.r+1][x.c]!='X' && x.dir!=0) in(x.time+1,x.r+1,x.c,1,x.cost+red), in(x.time+2,x.r+1,x.c,1,x.cost);
		if(g[x.r][x.c]=='T' && x.c>0 && g[x.r][x.c-1]!='X'     && x.dir!=3) in(x.time+1,x.r,x.c-1,2,x.cost+red), in(x.time+2,x.r,x.c-1,2,x.cost);
		if(g[x.r][x.c]=='T' && x.c<col-1 && g[x.r][x.c+1]!='X' && x.dir!=2) in(x.time+1,x.r,x.c+1,3,x.cost+red), in(x.time+2,x.r,x.c+1,3,x.cost);
	}

	inline void in(short time,short r,short c,short dir,double cos)
	{
		if(cos<cost[time][r][c][dir]->cost)
		{
			cost[time][r][c][dir]->time=time; cost[time][r][c][dir]->r=r; cost[time][r][c][dir]->c=c; cost[time][r][c][dir]->dir=dir; cost[time][r][c][dir]->cost=cos;
			on[time].push(cost[time][r][c][dir]);
		}
	}
};
