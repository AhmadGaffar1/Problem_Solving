#include<iostream>
#include<vector>
#include<string>
using namespace std;

class UndergroundVault
{
public:
	vector<int> sealOrder(vector<string> v)
	{
		prepare(v);
		best();
		return result;
	}

private:
	vector<int> result;
	vector<vector<int>> v;
	int size,count,close[50],visit[50],tmp;

	void prepare(vector<string> v_)
	{
		size=v_.size(); count=size; tmp=0;
		for(int i=0;i<50;i++) {vector<int> x; v.push_back(x); close[i]=visit[i]=0;}
		for(int i=0;i<v_.size();i++) in(v_[i],i);
	}

	void in(string s,int index)
	{
		string tmp=""; int num=0; s+=',';
		for(int i=0;i<s.size();i++)
		{
			if(s[i]!=',') {tmp+=s[i]; continue;}
			if(tmp.size()==1)      num=(tmp[0]-'0');
			else if(tmp.size()==2) num=(tmp[0]-'0')*10+(tmp[1]-'0');
			v[index].push_back(num);
			tmp=""; num=0;
		}
	}

	void best()
	{
		for(;count>1;) for(int i=1;i<size;i++) if(close[i]==false)
		{
			for(int j=0;j<50;j++) visit[j]=0; tmp=0;
			ok(0,i);
			if(tmp==(count-1)) {result.push_back(i); close[i]=true; count--; break;}
		}
		result.push_back(0);
	}

	void ok(int index,int no)
	{
		visit[index]=1;	tmp++;
		for(int i=0;i<v[index].size();i++) if(close[v[index][i]]==0 && visit[v[index][i]]==false && v[index][i]!=no) ok(v[index][i],no);
	}
};
