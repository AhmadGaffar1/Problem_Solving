#include<iostream>
#include<vector>
#include<string>
using namespace std;

class NowhereLand
{
public:
	int placeGuards(vector<string> cities,int k,vector<string> guards,vector<string> agencies)
	{
		prepare(cities,k,guards,agencies);
		for(int i=0;i<numcom;i++) {tmp=i; company();}
		return result;
	}

private:
	int result,numcity,numcom,tmp,frnd[51][51],f[51][51];
	bool combuild[51][51],comsold[51][51],visit[51];

	void prepare(vector<string> cities,int k,vector<string> guards,vector<string> agencies)
	{
		result=0; numcity=cities.size(); numcom=k; tmp=0;
		for(int i=0;i<51;i++) for(int j=0;j<51;j++) {frnd[i][j]=0; combuild[i][j]=comsold[i][j]=visit[i]=false;}
		for(int i=0;i<numcity;i++) for(int j=0;j<numcity;j++) if(cities[i][j]=='1') frnd[i][j]=1;
		for(int i=0;i<numcity;i++) for(int j=0;j<agencies[i].size();j+=2)
		{
			tmp=agencies[i][j]-'0';
			if(j+1<agencies[i].size() && agencies[i][j+1]!=' ') {j++; tmp*=10; tmp+=agencies[i][j]-'0';}
			combuild[tmp][i]=true;
		}
		for(int i=0;i<numcity;i++) for(int j=0;j<guards[i].size();j+=2)
		{
			tmp=guards[i][j]-'0';
			if(j+1<guards[i].size() && guards[i][j+1]!=' ') {j++; tmp*=10; tmp+=guards[i][j]-'0';}
			comsold[tmp][i]=true;
		}
	}

	void company()
	{
		for(int i=0;i<51;i++) for(int j=0;j<51;j++) f[i][j]=frnd[i][j];
		for(int i=0;i<numcity;i++) if(comsold[tmp][i]==true) f[50][i]=f[i][50]=2e9;
		for(;flow(50);result++) for(int i=0;i<51;i++) visit[i]=false; /**/ for(int i=0;i<51;i++) visit[i]=false;
	}

	bool flow(int index)
	{
		visit[index]=true;
		for(int i=0;i<numcity;i++) if(f[index][i]>0 && visit[i]==false) if(combuild[tmp][i]==false || flow(i))
		{
			f[index][i]--;
			f[i][index]++;
			return true;
		}
		return false;
	}
};
