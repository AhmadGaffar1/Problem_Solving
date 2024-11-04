#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class SoftwareCompanies
{
public:
	vector<string> produceData(vector<string> name,vector<string> process,vector<int> cost,vector<int> amount,string comp1,string comp2)
	{
		prepare(name,process,cost,amount,comp1,comp2);
		combinations();
		return result;
	}

private:
	vector<string> name,result,tmp;
	vector<int> cost,amount,on;
	int size,source,sink,edge[24][24],e[24][24],mini,flow,cash,FLOW,CASH;
	bool b[24],visit[24],flag;

	void prepare(vector<string> name_,vector<string> process,vector<int> cost_,vector<int> amount_,string comp1,string comp2)
	{
		name=name_; size=name.size(); cost=cost_; amount=amount_; mini=2e9; FLOW=flow=0; CASH=cash=2e9; flag=true;
		for(int i=0;i<24;i++)     for(int j=0;j<24;j++) edge[i][j]=0;
		for(int i=0;i<size;i++)   edge[i][i+size]=amount[i];
		for(int i=0;i<size;i++) 
		{
			string s=process[i],tmp=""; s+=' ';
			for(int j=0;j<s.size();j++)
			{
				if(s[j]!=' ') {tmp+=s[j]; continue;}
				for(int k=0;k<size;k++) if(tmp==name[k]) edge[i+size][k]=2e9;
				tmp="";
			}
		}
		for(int i=0;i<size;i++) 
		{
			if(name[i]==comp1) source=i; 
			else if(name[i]==comp2) sink=i;
		}
	}

	void combinations()
	{
		for(int i=0;i<pow(2,size);i++) if((i&(1<<source)) && (i&(1<<sink)))
		{
			flow=cash=0;
			for(int j=0;j<24;j++)   b[j]=false;
			for(int j=0;j<24;j++) for(int k=0;k<24;k++) e[j][k]=edge[j][k];
			for(int j=0;j<size;j++) if(i&(1<<j)) {b[j]=b[j+size]=true; cash+=cost[j];}

			flag=true;
			for(;flag==true;) maxFlow();

			if(flow>0 && (flow>FLOW || (flow==FLOW && cash<CASH)))
			{
				FLOW=flow; CASH=cash;
				result.clear();
				for(int j=0;j<size;j++) if(i&(1<<j)) result.push_back(name[j]);
				sort(result.begin(),result.end());
			}
			
			else if(flow>0 && (flow==FLOW && cash==CASH))
			{
				flag=false; tmp.clear();
				for(int j=0;j<size;j++) if(i&(1<<j)) tmp.push_back(name[j]); /**/ sort(tmp.begin(),tmp.end());
				for(int i=0;i<min(result.size(),tmp.size());i++) if(tmp[i]<result[i]) {result=tmp; flag=true; break;}
				if(flag==false && tmp.size()<result.size()) result=tmp;
			}
		}
	}

	void maxFlow()
	{
		for(int i=0;i<24;i++) visit[i]=false; /**/ on.clear(); mini=2e9; flag=false; go(source);
		for(int i=0;flag==true && i<on.size()-1;i++) if(e[on[i]][on[i+1]]<mini) mini=e[on[i]][on[i+1]];
		for(int i=0;flag==true && i<on.size()-1;i++) {e[on[i]][on[i+1]]-=mini; /**/ e[on[i+1]][on[i]]+=mini;}
		if(flag==true) flow+=mini;
	}

	void go(int index)
	{
		if(index==(sink+size)) flag=true;
		on.push_back(index); /**/ visit[index]=true;
		for(int i=0;flag==false && i<(2*size);i++) if(e[index][i]>0 && b[i]==true && visit[i]==false) go(i);
		if(flag==false) on.pop_back();
	}
};
