#include<iostream>
#include<queue>
#include<string>
using namespace std;

struct node{node(){x=0; s="";} long long x; string s;};

class OddDigitable
{
public:
	string findMultiple(int n,int m)
	{
		prepare(n,m);
		find();
		return result;
	}

private:
	string result;
	long long n,m;
	queue<node> on;
	bool b[100000];

	void prepare(int n0,int m0)
	{
		n=n0; m=m0; result="-1";
		for(int i=0;i<100000;i++) b[i]=false;
		for(int i=1;i<=9;i+=2) {node x; x.x=i%n; x.s=(i+'0'); on.push(x); b[i%n]=true;}
	}
	
	void find()
	{
		for(;on.size();)
		{
			node tmp=on.front(); /**/ on.pop();
			if(tmp.x==m) {result=tmp.s; break;}
			for(int i=1;i<=9;i+=2) if(b[(tmp.x*10+i)%n]==false)
			{
				node x;
				x.x=(tmp.x*10+i)%n;
				x.s=tmp.s+(char)(i+'0');
				on.push(x);
				b[x.x]=true;
			}
		}
	}
};
