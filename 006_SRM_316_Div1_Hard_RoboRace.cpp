#include<iostream>
#include<vector>
#include<string>
using namespace std;

class RoboRace
{
public:
	int startTime(vector<string> board,vector<string> comands)
	{
		prepare(board,comands);
		calc(x1,y1,0);
		calc(x2,y2,0);
		for(int i=0;i<com.size();i++) if(res[x1][y1][i]<res[x2][y2][i]) {result=i; break;}
		return result;
	}

private:
	int result,row,col,***res,x1,y1,x2,y2,x3,y3;
	vector<string> v;
	string com;

	void prepare(vector<string> board,vector<string> comands)
	{
		result=-1; v=board; row=v.size(); col=v[0].size(); com=""; for(int i=0;i<comands.size();i++) com+=comands[i];
		for(int i=0;i<row;i++) for(int j=0;j<col;j++) {if(v[i][j]=='Y') x1=i,y1=j; if(v[i][j]=='F') x2=i,y2=j; if(v[i][j]=='X') x3=i,y3=j;}
		res=new int **[50];
		for(int i=0;i<50;i++) res[i]=new int *[50];
		for(int i=0;i<50;i++) for(int j=0;j<50;j++) res[i][j]=new int [2501];
		for(int i=0;i<50;i++) for(int j=0;j<50;j++) for(int k=0;k<2501;k++) res[i][j][k]=2e9;
		for(int i=0;i<2501;i++) res[x3][y3][i]=0;
	}

	int calc(int x,int y,int t)
	{
		if(res[x][y][t]!=2e9) return res[x][y][t]+1;
		
		if(t<com.size()) res[x][y][t]=calc(x,y,t+1);
		if(t<com.size() && com[t]=='N' && x>0     && v[x-1][y]!='#') res[x][y][t]=min(res[x][y][t],calc(x-1,y,t+1));
		if(t<com.size() && com[t]=='S' && x<row-1 && v[x+1][y]!='#') res[x][y][t]=min(res[x][y][t],calc(x+1,y,t+1));
		if(t<com.size() && com[t]=='W' && y>0     && v[x][y-1]!='#') res[x][y][t]=min(res[x][y][t],calc(x,y-1,t+1));
		if(t<com.size() && com[t]=='E' && y<col-1 && v[x][y+1]!='#') res[x][y][t]=min(res[x][y][t],calc(x,y+1,t+1));
		return res[x][y][t]+1;
	}
};
