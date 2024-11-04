#include<iostream>
#include<vector>
using namespace std;

class SantaClaus
{
public:
	vector<int> exchange(vector<string> v)
	{
		prepare(v);
		smallestPositiveCircle();
		return result;
	}

private:
	vector<int> result;
	vector<string> v;
	int edge[50][50],dis[50][50],dis2[50][50],tmp;

	void prepare(vector<string> v_)
	{
		v=v_;
		for(int i=0;i<v.size();i++) for(int j=0;j<v.size();j++) {dis[i][j]=edge[i][j]=-v[i][i]+v[j][i]; /**/ dis2[i][j]=-2e9;}
		result.push_back(0); result.push_back(0);
	}

	bool smallestPositiveCircle()
	{
		for(int len=3;len<=v.size()+1;len++)
		{
			for(int mid=0;mid<v.size();mid++) for(int i=0;i<v.size();i++) for(int j=0;j<v.size();j++) dis2[i][j]=max(dis2[i][j],dis[i][mid]+edge[mid][j]);
			for(int i=0;i<v.size();i++) for(int j=0;j<v.size();j++) {dis[i][j]=dis2[i][j]; dis2[i][j]=-2e9;}
			for(int i=0;i<v.size();i++) if(dis[i][i]>result[1]) {result[0]=len-1; result[1]=dis[i][i];}
			if(result[0]>0) return 0;
		}
		return 0;
	}
};
