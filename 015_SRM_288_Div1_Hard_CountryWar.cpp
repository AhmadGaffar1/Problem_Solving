#include<iostream>
#include<vector>
#include<string>
using namespace std;

class CountryWar
{
public:
	double defeatAll(vector<string> v)
	{
		prepare(v);	
		for(int i=1;i<21;i++) fun(20,20,i);
		result=go(((1<<size)-1)^(1<<y),unit[y],e);
		return result;
	}

private:
	double result,**dp,prob[21][21][21];
	vector<vector<int>> v;
	int size,y,n,e,unit[15];
	char type[15];
	bool frnd[15][15];

	void prepare(vector<string> v_)
	{
		result=1; size=v_.size(); y=n=e=0;
		for(int i=0;i<size;i++) {vector<int> x; v.push_back(x);}
		for(int i=0;i<size;i++) for(int j=0;j<size;j++) frnd[i][j]=0;
		for(int i=0;i<v_.size();i++) in(v_[i],i);
		
		dp=new double *[(1<<15)];
		for(int i=0;i<(1<<15);i++) dp[i]=new double[21];
		for(int i=0;i<(1<<15);i++) for(int j=0;j<21;j++) {dp[i][j]=-1; /**/ if(i==0 && j>0) dp[i][j]=1;}

		for(int i=0;i<21;i++) for(int j=0;j<21;j++) for(int k=0;k<21;k++) 
		{
			prob[i][j][k]=-1; 
			if(j==0 && i==k) prob[i][j][k]=1; 
			else if(j==0 || i<k) prob[i][j][k]=0;
		}
	}

	void in(string s,int index)
	{
		if(s[0]=='Y')      {type[index]='Y'; y=index;}
		else if(s[0]=='N') {type[index]='N'; n++;}
		else if(s[0]=='E') {type[index]='E'; e++;}

		if(s.size()>3 && s[3]!=' ') unit[index]=(s[2]-'0')*10+(s[3]-'0');
		else                        unit[index]=(s[2]-'0');

		s+=' ';
		string tmp="";
		int num=0;
		for(int i=4;i<s.size();i++)
		{
			if(s[i]!=' ') {tmp+=s[i]; continue;}
			if(s[i]==' ' && tmp.size()==0) continue;

			num=tmp[0]-'0';
			if(tmp.size()>1) {num*=10; num+=tmp[1]-'0';}
			v[index].push_back(num);
			frnd[index][num]=1;
			tmp=""; num=0;
		}
	}

	double fun(int a,int b,int carry)
	{
		if(prob[a][b][carry]!=-1) return prob[a][b][carry];
		prob[a][b][carry]=val(a,b,0)*fun(a,b-1,carry)+val(a,b,1)*fun(a-1,b,carry);
		return prob[a][b][carry];
	}

	inline double val(double a,double b,double flag)
	{
		double tmp=flag-(a*a/(a*a+b*b+a*b));
		if(tmp<0) tmp=tmp*(-1);
		return tmp;
	}

	double go(int group,int units,int enemy)
	{
		if(enemy==0)             return 1;
		if(dp[group][units]!=-1) return dp[group][units];

		dp[group][units]=0;
		for(int i=0;i<size;i++) if(((1<<i)&group) && ok(group,i))
		{
			double tmp=0;
			int f=0; if(type[i]=='E') f=1;

			for(int carry=units;carry>0;carry--) tmp+=prob[units][unit[i]][carry]*go(group^(1<<i),carry,enemy-f);
			if(tmp>dp[group][units]) dp[group][units]=tmp;
		}
		return dp[group][units];
	}

	bool ok(int group,int x)
	{
		for(int i=0;i<size;i++) if(((1<<i)&group)==0 && frnd[i][x]==true) return 1;
		return 0;
	}
};
