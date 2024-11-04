#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct node{node(){x=y=s=0; num=1; for(int i=0;i<50;i++) b[i]=false;} long double x,y,s; int num; bool b[50];};

class PlaneDivision
{
public:
	int howManyFiniteParts(vector<int> x1,vector<int> y1,vector<int> x2,vector<int> y2)
	{
		prepare(x1,y1,x2,y2);
		for(int i=0;i<size;i++) determineSlopes(i);
		for(int i=0;i<size;i++) for(int j=i+1;j<size;j++) if(slp[i]!=slp[j]) {if(slp[i]==1e300) determinePoints(j,i); else determinePoints(i,j);}
		count();
		return result;
	}

private:
	int result,size,line;
	vector<int> x1,y1,x2,y2;
	vector<node> point;
	vector<node> slope;
	long double slp[50];

	void prepare(vector<int> x1_,vector<int> y1_,vector<int> x2_,vector<int> y2_)
	{
		result=line=0; x1=x1_; y1=y1_; x2=x2_; y2=y2_; size=x1.size();
	}

	bool determineSlopes(int index)
	{
		node tmp;
		if(x1[index]-x2[index]==0) tmp.s=1e300;
		else tmp.s=((double)y1[index]-y2[index])/(x1[index]-x2[index]);
		slp[index]=tmp.s;

		for(int i=0;i<slope.size();i++) if(slope[i].s==tmp.s) {slope[i].num++; return 0;}
		slope.push_back(tmp); return 0;
	}

	bool determinePoints(int a,int b)
	{
		node tmp;
		double val=(double)y1[a]-slp[a]*x1[a],val2=(double)y1[b]-slp[b]*x1[b];
		tmp.x=(val2-val)/(slp[a]-slp[b]);
		tmp.y=slp[a]*tmp.x+val;
		tmp.num=2;
		tmp.b[a]=tmp.b[b]=true;
		
		for(int i=0;i<point.size();i++) if(abs(point[i].x-tmp.x)<1e-10 && abs(point[i].y-tmp.y)<1e-10)
		{
			if(point[i].b[a]==false) {point[i].b[a]=true; point[i].num++;}
			if(point[i].b[b]==false) {point[i].b[b]=true; point[i].num++;}
			return 0;
		}
		point.push_back(tmp); return 0;
	}

	void count()
	{
		line=slope[0].num;
		if(slope.size()>1)              {result=(slope[1].num-1)*(line-1); line+=slope[1].num;}
		for(int i=2;i<slope.size();i++) {result+=(slope[i].num) *(line-1); line+=slope[i].num;}

		for(int i=0;i<point.size();i++) if(point[i].num>2) result-=intersection(point[i].num);
	}

	int intersection(int num)
	{
		int ret=0;
		for(int i=3;i<=num;i++) ret+=(i-2);
		return ret;
	}
};
