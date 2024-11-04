#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

int result,row,col;
pair<int,int> A,B,a,b;
vector<string> v;
struct state{int Ax,Ay,Bx,By,time;};
queue<state> on;
bool visit[20][20][20][20];
int dx[9]={-1,-1,-1,0,0,0,1,1,1};
int dy[9]={-1,0,1,-1,0,1,-1,0,1};

class PathFinding
{
public:
	int minTurns(vector<string> v)
	{
		prepare(v);
		for(;on.size() && result==-1;) {state s=on.front(); on.pop(); bfs(s.Ax,s.Ay,s.Bx,s.By,s.time);}
		return result;
	}

	void prepare(vector<string> v_)
	{
		result=-1; v=v_; row=v.size(); col=v[0].size();
		for(int i=0;i<row;i++) for(int j=0;j<col;j++)
		{
			if(v[i][j]=='A') {A.first=i; A.second=j;}
			if(v[i][j]=='B') {B.first=i; B.second=j;}
		}
		visit[A.first][A.second][B.first][B.second]=true;
		state s; s.Ax=A.first; s.Ay=A.second; s.Bx=B.first; s.By=B.second; s.time=0; on.push(s);
	}

	void bfs(int Ax,int Ay,int Bx,int By,int time)
	{
		for(int i=0;i<9;i++)
		{
			a.first=Ax+dx[i]; a.second=Ay+dy[i];
			for(int j=0;j<9 && valid(a);j++)
			{
				b.first=Bx+dx[j]; b.second=By+dy[j];
				if(valid(b) && a!=b && noCross(Ax,Ay,Bx,By,a,b) && visit[a.first][a.second][b.first][b.second]==false)
				{
					visit[a.first][a.second][b.first][b.second]=true;
					state s; s.Ax=a.first; s.Ay=a.second; s.Bx=b.first; s.By=b.second; s.time=time+1; on.push(s);
					if(a.first==B.first && a.second==B.second && b.first==A.first && b.second==A.second) {result=time+1; i=j=10;}
				}
			}
		}
	}

	inline bool valid(pair<int,int> &a)
	{
		if(a.first>=0 && a.first<row && a.second>=0 && a.second<col && v[a.first][a.second]!='X') return true;
		return false;
	}

	inline bool noCross(int &Ax,int &Ay,int &Bx,int &By,pair<int,int> &a,pair<int,int> &b)
	{
		if(a.first==Bx && a.second==By && b.first==Ax && b.second==Ay) return false;
		return true;
	}
};
