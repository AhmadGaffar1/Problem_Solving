#include<iostream>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

class MagicianTour
{
public:
	int bestDifference(vector<string> roads,vector<int> populations)
	{
		prepare(roads,populations);
		determineGroups();

		if(on.size()==1) result=on[0];
		else minimize();

		return result;
	}

private:
	int result,size,diff,sum;
	vector<vector<int>> v;
	vector<int> num,on;
	bool visit[50];
	short dp[51][501];

	void prepare(vector<string> roads,vector<int> populations)
	{
		size=populations.size(); num=populations; diff=sum=0;
		for(int i=0;i<size;i++) {vector<int> x; v.push_back(x); visit[i]=false;}
		for(int i=0;i<size;i++) for(int j=0;j<size;j++) if(roads[i][j]=='1') v[i].push_back(j);
		for(int i=0;i<=50;i++)  for(int j=0;j<=500;j++) dp[i][j]=0;
	}

	void determineGroups()
	{
		for(int i=0;i<size;i++) if(visit[i]==false) {diff=0; go(i,0); diff=abs(diff); on.push_back(diff); sum+=diff;}
	}

	void go(int index,int flag)
	{
		visit[index]=true;
		if(flag%2==0) diff+=num[index];
		else          diff-=num[index];
		for(int i=0;i<v[index].size();i++) if(visit[v[index][i]]==false) go(v[index][i],flag+1);
	}

	void minimize()
	{
		for(int i=1;i<=on.size();i++) for(int j=1;j<=sum/2;j++) {if(j-on[i-1]>=0) dp[i][j]=on[i-1]+dp[i-1][j-on[i-1]]; dp[i][j]=max(dp[i][j],dp[i-1][j]);}
		result=abs(sum-dp[on.size()][sum/2]-dp[on.size()][sum/2]);
	}
};
