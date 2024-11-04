#include<iostream>
#include<vector>
#include<string>
using namespace std;

unsigned long long result,size,roadCost;
vector<string> v;
vector<unsigned long long> h,H,houseCost,on;
unsigned long long edge[50][50],conect;
bool flag[50];

class BuildersCountry
{
public:
	long long minCost(vector<int> before,vector<int> after,vector<int> houseCost,vector<string> g,int roadCost)
	{
		prepare(before,after,houseCost,g,roadCost);
		phase1();
		for(conect=0;conect<size;) phase2();
		return result;
	}

	void prepare(vector<int> before,vector<int> after,vector<int> houseCost_,vector<string> g,int roadCost_)
	{
		result=0; size=before.size(); roadCost=roadCost_; v=g;
		for(int i=0;i<size;i++) {unsigned long long x,y,z; h.push_back(x); H.push_back(y); houseCost.push_back(z); h[i]=before[i]; H[i]=after[i]; houseCost[i]=houseCost_[i];}
	}

	void phase1()
	{
		for(int i=0;i<size;i++) for(int j=i+1;j<size;j++) if(v[i][j]=='N') edge[i][j]=edge[j][i]=(h[i]+h[j])*roadCost + (H[i]-h[i])*h[j]*houseCost[i] + (H[j]-h[j])*h[i]*houseCost[j] + (H[i]-h[i])*(H[j]-h[j])*min(houseCost[i],houseCost[j]);
		on.push_back(0); flag[0]=true; conect=1; for(;conect<size;) prim();
	}

	void prim()
	{
		unsigned long long a=-1,b=-1,dis=1.8e19;
		for(int i=0;i<on.size();i++) for(int j=0;j<size;j++) if(flag[j]==false && edge[on[i]][j]<dis) {a=on[i]; b=j; dis=edge[a][b];}
		on.push_back(b); flag[b]=true; conect++; if(v[a][b]=='N') result+=(h[a]+h[b])*roadCost; v[a][b]=v[b][a]='Y';
	}

	void phase2()
	{
		unsigned long long a=0,cost=0,old=0,nw=0;
		for(int i=0;i<size;i++) if(h[i]<H[i] && houseCost[i]>cost) {cost=houseCost[i]; a=i;}
		for(int i=0;i<size;i++) if(v[a][i]=='Y') old+=h[i]; /**/ old+=h[a]; nw=H[a]-h[a];
		result+=nw*old*houseCost[a];
		result+=(nw*(nw-1)/2)*houseCost[a];
		h[a]=H[a]; conect++;
	}
};
