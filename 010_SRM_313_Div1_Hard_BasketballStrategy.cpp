#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

struct node {node(){} int a,b; double pro;};

class BasketballStrategy
{
public:
	double scoreProbability(vector<string> team,vector<string> rival,double cp,double cs)
	{
		prepare(team,rival,cp,cs);
		probabilities();
		maximize();
		return result;
	}

private:
	double result,cp,cs,ls,dr,pro[51][51],mx[51];
	vector<pair<int,int>> team,rival;
	int num;
	vector<node> v;
	vector<int> road[51];
	bool visit[51];

	void prepare(vector<string> team_,vector<string> rival_,double cp_,double cs_)
	{
		result=1; cp=cp_; cs=cs_; num=team_.size();
		for(int i=0;i<=50;i++) {for(int j=0;j<=50;j++) pro[i][j]=1; visit[i]=false; mx[i]=0;}
		for(int i=0;i<num;i++) {positions(team,team_[i]); positions(rival,rival_[i]);}
		pair<int,int> goal; goal.first=50; goal.second=0; team.push_back(goal);
	}

	void positions(vector<pair<int,int>> &v,string s)
	{
		int x=0,y=0,i=0; pair<int,int> p;
		if(s[1]==' ') {x=s[0]-'0'; i=2;}
		else          {x=((s[0]-'0')*10)+(s[1]-'0'); i=3;}

		if(s.size()==i+1) {y=s[i]-'0';}
		else              {y=((s[i]-'0')*10)+(s[i+1]-'0');}
		p.first=x; p.second=y; v.push_back(p);
	}

	void probabilities()
	{
		for(int i=0;i<num;i++) for(int j=i+1;j<num;j++) for(int k=0;k<num;k++) //probability of bass
		{
			ls=sqrt(((double)team[i].first-team[j].first)*(team[i].first-team[j].first)+(team[i].second-team[j].second)*(team[i].second-team[j].second));
			drCalc(i,j,k);
			pro[i][j]=min(pro[i][j], cp * (1 - (ls / 150)*(ls / 150)) * dr); /**/ pro[j][i]=pro[i][j];
		}
		for(int i=0;i<num;i++) for(int j=num;j<=num;j++) for(int k=0;k<num;k++) //probability of shot
		{
			ls=sqrt(((double)team[i].first-team[j].first)*(team[i].first-team[j].first)+(team[i].second-team[j].second)*(team[i].second-team[j].second));
			drCalc(i,j,k);
			pro[i][j]=min(pro[i][j],pow((cs * dr),log(ls))); /**/ pro[j][i]=pro[i][j];
		}
	}

	void drCalc(int i,int j,int k)
	{
		dr=1;
		if(team[i].first==team[j].first && rival[k].second >= min(team[i].second,team[j].second) && rival[k].second <= max(team[i].second,team[j].second))  {dr=abs(team[i].first-rival[k].first); /**/ dr=dr/(dr+1);}
		else if(team[i].second==team[j].second && rival[k].first >= min(team[i].first,team[j].first) && rival[k].first <= max(team[i].first,team[j].first)) {dr=abs(team[i].second-rival[k].second); /**/  dr=dr/(dr+1);}
		else
		{
			double m=((double)team[i].second-team[j].second)/(team[i].first-team[j].first);
			double a=m,b=-1,c=((-m)*team[i].first+team[i].second);
			double m2=(-1)/m;
			double a2=m2,b2=-1,c2=((-m2)*rival[k].first+rival[k].second);
			double y=(a*c2-a2*c)/((-a)*b2+a2*b),x=((-b2)*y-c2)/(a2);
			if(x>=min(team[i].first,team[j].first) && x<=max(team[i].first,team[j].first)) {dr=abs(a*rival[k].first+b*rival[k].second+c)/sqrt((a*a)+(b*b)); /**/ dr=dr/(dr+1);}
		}
	}

	void maximize()
	{
		for(int i=0;i<=num;i++)     for(int j=i+1;j<=num;j++)     {node x; x.a=i; x.b=j; x.pro=pro[i][j]; v.push_back(x);}
		for(int i=0;i<v.size();i++) for(int j=i+1;j<v.size();j++) if(v[j].pro>v[i].pro) {node x=v[i]; v[i]=v[j]; v[j]=x;}

		visit[0]=true; mx[0]=1;
		for(;visit[num]==false;) addMax();
		result=mx[num];
	}

	void addMax()
	{
		node tmp; tmp.a=tmp.b=tmp.pro=-1;
		for(int i=0;i<v.size();i++)
			if(visit[v[i].a]==true && visit[v[i].b]==false)      {if((mx[v[i].a]*v[i].pro)>tmp.pro) {tmp.a=v[i].a; tmp.b=v[i].b; tmp.pro=(mx[v[i].a]*v[i].pro);}}
			else if(visit[v[i].a]==false && visit[v[i].b]==true) {if((mx[v[i].b]*v[i].pro)>tmp.pro) {tmp.a=v[i].a; tmp.b=v[i].b; tmp.pro=(mx[v[i].b]*v[i].pro);}}

		if(visit[tmp.a]==false)      {mx[tmp.a]=tmp.pro; visit[tmp.a]=true;}
		else if(visit[tmp.b]==false) {mx[tmp.b]=tmp.pro; visit[tmp.b]=true;}
	}
};
