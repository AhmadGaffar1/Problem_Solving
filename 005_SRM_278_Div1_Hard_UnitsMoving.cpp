#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<cmath>
using namespace std;

class UnitsMoving
{
public:
	double bestTime(vector<string> start,vector<string> finish)
	{
		prepare(start,finish);
		BinarySearch();
		return result;
	}


private:
	double result,time[50][50];
	int size,s[50][3],f[50][2],end[50];
	bool visit[50];

	void prepare(vector<string> start,vector<string> finish)
	{
		result=0; size=start.size();
		for(int i=0;i<size;i++) {stringstream ss(start[i]);  ss>>s[i][0]>>s[i][1]>>s[i][2];}
		for(int i=0;i<size;i++) {stringstream ss(finish[i]); ss>>f[i][0]>>f[i][1];}
		for(int i=0;i<size;i++) for(int j=0;j<size;j++) {time[i][j]=sqrt((double)pow(s[i][0]-f[j][0],2)+pow(s[i][1]-f[j][1],2))/s[i][2];}
		for(int i=0;i<size;i++) {visit[i]=false; end[i]=-1;}
	}

	void BinarySearch()
	{
		double a=0,z=2000; result=(a+z)/2.0;
		for(int i=0;i<100;i++) 
		{
			if(ok()) {z=result; result=(a+z)/2.0;}
			else     {a=result; result=(a+z)/2.0;}
		}
	}

	bool ok()
	{
		for(int i=0;i<size;i++) end[i]=-1;
		for(int i=0;i<size;i++) {for(int j=0;j<size;j++) visit[j]=false; if(!matching(i)) return false;}
		return true;
	}

	bool matching(int index)
	{
		for(int i=0;i<size;i++) if(time[index][i]<=result && visit[i]==false)
		{
			visit[i]=true;
			if(end[i]==-1 || matching(end[i])) {end[i]=index; return true;}
		}
		return false;
	}
};
