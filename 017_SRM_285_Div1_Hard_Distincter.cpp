#include<iostream>
#include<vector>
using namespace std;

class Distincter
{
public:
	int disperse(vector<int> v,int k)
	{
		prepare(v,k);
		for(;k-diff>0;) minimum();
		return result;
	}

private:
	int result,k,diff,left,right,best,index,num[1100],res[1100],resL[1100],resR[1100],res2[1100];
	bool b[1100],bL[1100],bR[1100],b2[1100];

	void prepare(vector<int> v,int k_)
	{
		result=diff=left=right=best=index=0; k=k_;
		for(int i=0;i<1100;i++) num[i]=res[i]=resL[i]=resR[i]=res2[i]=b[i]=bL[i]=bR[i]=b2[i]=0;
		for(int i=0;i<v.size();i++) {if(b[v[i]+50]==0) diff++; /**/ num[v[i]+50]++; b[v[i]+50]=bL[v[i]+50]=bR[v[i]+50]=b2[i]=1;}
	}

	void minimum()
	{
		best=2e9;
		for(int i=51;i<=1050;i++) if(num[i]>1)
		{
			left=right=0;
			for(int j=0;j<1100;j++) {resL[j]=resR[j]=res[j]; bL[j]=bR[j]=b[j];}

			goLeft(i-1,-1);
			goRight(i+1,1);

			if(left<=right && left<best)      for(int j=0;j<1100;j++) {res2[j]=resL[j]; b2[j]=bL[j]; best=left; index=i;}
			else if(right<left && right<best) for(int j=0;j<1100;j++) {res2[j]=resR[j]; b2[j]=bR[j]; best=right; index=i;}
		}

		num[index]--; diff++; result+=best;
		for(int i=0;i<1100;i++) {res[i]=res2[i]; b[i]=b2[i];}
	}

	void goLeft(int index,int value)
	{
		if(bL[index]==0)
		{
			left+=abs(value);
			bL[index]=1;
			resL[index]=value;
		}

		else if(resL[index]>0)
		{
			left-=abs(resL[index]); left+=abs(value);
			goLeft(index-1,resL[index]-1);
			resL[index]=value;
		}

		else goLeft(index-1,value-1);
	}

	void goRight(int index,int value)
	{
		if(bR[index]==0)
		{
			right+=abs(value);
			bR[index]=1;
			resR[index]=value;
		}

		else if(resR[index]<0)
		{
			right-=abs(resR[index]); right+=abs(value);
			goRight(index+1,resR[index]+1);
			resR[index]=value;
		}

		else goRight(index+1,value+1);
	}
};
