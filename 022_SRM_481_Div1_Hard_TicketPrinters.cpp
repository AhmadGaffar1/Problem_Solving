#include<iostream>
#include<vector>
using namespace std;

int result,current,size,disP[16][16],disT[16][16];
int t[16],p[16],a=0,z=1e9;
bool visit[16];

class TicketPrinters
{
public:
	int minTime(int current,vector<int> dis,vector<int> start,vector<int> wanted)
	{
		prepare(current,dis,start,wanted);
		binarySearch();
		return result;
	}

	void prepare(int current_,vector<int> dis,vector<int> start,vector<int> wanted)
	{
		current=current_; size=start.size(); result=(a+z)/2;
		for(int i=0;i<size;i++) disPrinter(i,i,0,dis);
		for(int i=0;i<size;i++) for(int j=0;j<size;j++) disT[i][j]=abs(start[i]-wanted[j])+1;
		for(int i=0;i<16;i++) t[i]=p[i]=-1;
	}

	void disPrinter(const int s,int index,int val,vector<int> &dis)
	{
		disP[s][index]=disP[index][s]=val;
		if(index+1<size) disPrinter(s,index+1,val+dis[index],dis);
	}

	void binarySearch()
	{
		for(;a!=z;)
		{
			for(int i=0;i<16;i++) t[i]=p[i]=-1;
			if(calc((1<<size)-1,current,0,t,p)) {z=result;   result=(a+z)/2;}
			else                                {a=result+1; result=(a+z)/2;}
		}
	}

	bool calc(int group,int index,int step,int t_[16],int p_[16])
	{
		for(int i=0;i<16;i++) {t[i]=t_[i]; p[i]=p_[i]; visit[i]=false;} p[index]=step;
		if(!matching(index))      return false;
		if((group^(1<<index))==0) return true;

		int t2[16],p2[16];
		for(int i=0;i<16;i++) {t2[i]=t[i]; p2[i]=p[i];}
		bool left=false,right=false;
		                for(int i=index-1;i>=0   && step+disP[index][i]<result;i--) if((1<<i)&group) {left =calc(group^(1<<index),i,step+disP[index][i],t2,p2); break;}
		if(left==false) for(int i=index+1;i<size && step+disP[index][i]<result;i++) if((1<<i)&group) {right=calc(group^(1<<index),i,step+disP[index][i],t2,p2); break;}

		if(left==true || right==true) return true;
		return false;
	}

	bool matching(int index)
	{
		for(int i=0;i<size;i++) if(p[index]+disT[index][i]<=result && visit[i]==false)
		{
			visit[i]=true;
			if(t[i]==-1 || matching(t[i])) {t[i]=index; return true;}
		}
		return false;
	}
};
