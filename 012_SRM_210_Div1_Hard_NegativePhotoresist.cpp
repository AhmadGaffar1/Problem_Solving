#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<cmath>
using namespace std;

struct point{double x,y;};

class NegativePhotoresist
{
public:
	double minimumTilt(vector<string> v,int limit)
	{
		prepare(v,limit);
		miniAngle();
		return result;
	}

private:
	double result,dis[50][50],sum;
	int size,limit,arr[55];
	vector<vector<int>> v;
	point p[50],p2[50];

	void prepare(vector<string> v_,int limit_)
	{
		result=1.55; limit=limit_; size=v_.size(); sum=0;
		for(int i=0;i<50;i++) {vector<int> x; v.push_back(x);}
		for(int i=0;i<v_.size();i++) in(i,v_[i]);
	}

	void in(int index,string s)
	{
		int count=1;
		for(int i=0;i<s.size();i++) if(s[i]==',' || s[i]==' ') {s[i]=' '; count++;}
		stringstream ss; ss<<s;
		for(int i=0;i<count;i++) {ss>>arr[i];}
		p[index].x=arr[0]; p[index].y=arr[1];
		for(int i=2;i<count;i++) v[index].push_back(arr[i]);
	}

	void miniAngle()
	{
		double a=0.01,z=1.55; result=(a+z)/2.0;
		for(int i=0;i<50;i++)
		{
			if(ok()) {z=result; result=(a+z)/2.0;}
			else     {a=result; result=(a+z)/2.0;}
		}
	}

	bool ok()
	{
		newPositions();
		newDistances();
		sum=0;
		for(int k=0;k<size;k++) for(int i=0;i<size;i++) for(int j=0;j<size;j++) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		for(int i=0;i<size;i++) for(int j=i+1;j<size;j++) if(dis[i][j]<1e100) sum+=dis[i][j];
		
		if(sum<limit) return true;
		return false;
	}

	void newPositions()
	{
		for(int i=0;i<size;i++)
		{
			p2[i].x=p[i].x;
			p2[i].y=p[i].y*cos(result);
		}
	}

	void newDistances()
	{
		for(int i=0;i<size;i++) for(int j=0;j<size;j++) dis[i][j]=1e100;
		for(int i=0;i<size;i++) for(int j=0;j<v[i].size();j++) 
			dis[i][v[i][j]]=sqrt(double(p2[i].x-p2[v[i][j]].x)*(p2[i].x-p2[v[i][j]].x)+(p2[i].y-p2[v[i][j]].y)*(p2[i].y-p2[v[i][j]].y));
	}
};
