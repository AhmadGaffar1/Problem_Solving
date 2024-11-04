#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct rel{int row,col,index,step;};

class WorkersOnPlane
{
public:
	int howMany(vector<string> v_,int k_)
	{
		prepare(v_,k_);
		relations();
		for(int k=0;k<900;k++) visit[k]=false;
		for(;maxFlow(2000);) {for(int j=0;j<2002;j++) visit[j]=false; /**/ result++;}
		return result;
	}

private:
	int result,k,**edge;
	vector<int> v[2002];
	vector<string> land;
	vector<rel> on;
	bool visit[2002],flag;

	void prepare(vector<string> v_,int k_)
	{
		result=0; land=v_;  k=k_; flag=false;
		edge=new int *[2002];
		for(int i=0;i<2002;i++) {edge[i]=new int [2002]; for(int j=0;j<2002;j++) edge[i][j]=0; visit[i]=false;}
	}

	void relations()
	{
		for(int i=0;i<land.size();i++) for(int j=0;j<land[0].size();j++) if(land[i][j]=='W')
		{
			for(int k=0;k<900;k++) visit[k]=false;
			rel x; x.row=i; x.col=j; x.index=i*land[0].size()+j; x.step=0; on.push_back(x); visit[i*land[0].size()+j]=true;
			for(;on.size();on.erase(on.begin()+0)) relations(on[0].row,on[0].col,on[0].index,on[0].step);
			v[i*land[0].size()+j].push_back(i*land[0].size()+j+900); /**/ edge[i*land[0].size()+j][i*land[0].size()+j+900]=1;
		}
		else if(land[i][j]=='S') {v[2000].push_back(i*land[0].size()+j); edge[2000][i*land[0].size()+j]=1;}
		else if(land[i][j]=='G') {v[i*land[0].size()+j].push_back(2001); edge[i*land[0].size()+j][2001]=1;}
	}

	bool relations(int row,int col,int index,int step)
	{
		if(land[row][col]=='G') {v[index+900].push_back(row*land[0].size()+col); edge[index+900][row*land[0].size()+col]=1; return 0;}
		if(land[row][col]=='S') {v[row*land[0].size()+col].push_back(index);     edge[row*land[0].size()+col][index]=1;     return 0;}
		if((land[row][col]=='.' || land[row][col]=='W') && step<k)
		{
			if(row>0 && land[row-1][col]!='X' && land[row-1][col]!='W' && visit[(row-1)*land[0].size()+col]==false) {rel x; x.row=row-1; x.col=col; x.index=index; x.step=step+1; on.push_back(x); visit[(row-1)*land[0].size()+col]=true;}//up
			if(row<(land.size()-1) && land[row+1][col]!='X' && land[row+1][col]!='W' && visit[(row+1)*land[0].size()+col]==false) {rel x; x.row=row+1; x.col=col; x.index=index; x.step=step+1; on.push_back(x); visit[(row+1)*land[0].size()+col]=true;}//down
			if(col>0 && land[row][col-1]!='X' && land[row][col-1]!='W' && visit[row*land[0].size()+(col-1)]==false) {rel x; x.row=row; x.col=col-1; x.index=index; x.step=step+1; on.push_back(x); visit[row*land[0].size()+(col-1)]=true;}//left
			if(col<(land[0].size()-1) && land[row][col+1]!='X' && land[row][col+1]!='W' && visit[row*land[0].size()+(col+1)]==false) {rel x; x.row=row; x.col=col+1; x.index=index; x.step=step+1; on.push_back(x); visit[row*land[0].size()+(col+1)]=true;}//right
		}
		return 0;
	}

	bool maxFlow(int now)
	{
		visit[now]=true;
		if(now==2001) {return 1;}
		for(int i=0;i<2002;i++) if(visit[i]==false && edge[now][i]>0 && maxFlow(i)) {edge[now][i]--; edge[i][now]++; return 1;}
		return 0;
	}
};
