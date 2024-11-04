#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

struct data{data(){b=r=0;} int b,r;};

class HouseProtection
{
public:
	double safetyFactor(vector<int> bx,vector<int> by,vector<int> rx,vector<int> ry,int r)
	{
		prepare(bx,by,rx,ry,r);
		findRadius();
		return result;
	}

private:
	double result,maxRadius,r,edge[50][50];
	int sizeB,sizeR,numCircle,tmp,dam[50];
	bool visit[50];
	vector<int> bx,by,rx,ry;
	vector<double> v;

	void prepare(vector<int> _bx,vector<int> _by,vector<int> _rx,vector<int> _ry,int _r)
	{
		result=0; bx=_bx; by=_by; rx=_rx; ry=_ry; sizeB=bx.size(); sizeR=rx.size(); maxRadius=r=_r; numCircle=tmp=0;
		for(int i=0;i<sizeB;i++) for(int j=0;j<sizeR;j++) edge[i][j]=(sqrt((bx[i]-rx[j])*(bx[i]-rx[j]) + (by[i]-ry[j])*(by[i]-ry[j]))/2.0);
		for(int i=0;i<sizeB;i++) for(int j=0;j<sizeR;j++) if(edge[i][j]<maxRadius) v.push_back(edge[i][j]);
		v.push_back(maxRadius); sort(v.begin(),v.end());
		
	}

	void findRadius()
	{
		for(int i=0;i<v.size();i++)
		{
			r=v[i]; tmp=0;
			for(int j=0;j<50;j++) dam[j]=-1;
			for(int j=0;j<sizeB;j++)
			{
				for(int k=0;k<50;k++) visit[k]=false;
				tmp+=minimumDamage(j);
			}
			numCircle=sizeB+sizeR-tmp;
			result=max(result,numCircle*3.14159265359*r*r);
		}
	}

	int minimumDamage(int index)
	{
		for(int i=0;i<sizeR;i++) if(edge[index][i]<r && visit[i]==false)
		{
			visit[i]=true;
			if(dam[i]==-1 || minimumDamage(dam[i]))
			{
				dam[i]=index;
				return 1;
			}
		}
		return 0;
	}
};
