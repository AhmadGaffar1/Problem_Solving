#include<iostream>
#include<vector>
#include<string>
using namespace std;

int result,size;
vector<string> v;

class YetAnotherHamiltonianPath
{
public:
	int leastCost(vector<string> v)
	{
		prepare(v);
		minimum();
		return result;
	}

	void prepare(vector<string> v_)
	{
		v=v_; size=v.size();
	}

	int LCP(string s1,string s2)
	{
		for(int i=0;i<min(s1.size(),s2.size());i++) if(s1[i]!=s2[i]) return i;
		return min(s1.size(),s2.size());
	}

	void minimum()
	{
		result+=v[0].size()*v[0].size() + v[1].size()*v[1].size();
		for(int i=2;i<size;i++) result+=2*v[i].size()*v[i].size();

		for(;v.size()>1;)
		{
			int a=-1,b=-1,len=-1;
			for(int j=0;j<v.size();j++) for(int k=j+1;k<v.size();k++) if((!(j==0 && k==1 && v.size()>2)) && LCP(v[j],v[k])>len) {len=LCP(v[j],v[k]); a=j; b=k;}
			
			result-=len*len;
			v[a]=v[a].substr(0,len);
			v.erase(v.begin()+b);
		}
	}
};
