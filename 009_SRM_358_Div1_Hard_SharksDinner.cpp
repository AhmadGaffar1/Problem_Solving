#include<iostream>
#include<vector>
using namespace std;

class SharksDinner
{
public:
	int minSurvivors(vector<int> size,vector<int> speed,vector<int> intelligence)
	{
		prepare(size,speed,intelligence);
		relations();
		//for(int i=0;i<num;i++) {cout<<"shark["<<i<<"] :: "; for(int j=0;j<shark[i].size();j++) cout<<shark[i][j]<<"\t"; cout<<endl;}
		maximumEat();
		//for(int i=0;i<num;i++) cout<<"kill["<<i<<"] :: "<<kill[i]<<endl;
		return result;
	}

private:
	int result,num,kill[50],tmp;
	vector<int> size,speed,intelligence,shark[50];
	bool visit[50];

	void prepare(vector<int> size_,vector<int> speed_,vector<int> intelligence_)
	{
		size=size_; speed=speed_; intelligence=intelligence_; result=0; num=size.size(); tmp=0;
		for(int i=0;i<50;i++) {kill[i]=-1; visit[i]=false;}
	}

	void relations()
	{
		for(int i=0;i<num;i++) for(int j=0;j<num;j++) 
		{
			if(size[i]==size[j] && speed[i]==speed[j] && intelligence[i]==intelligence[j] && i>j) continue;
			if(i!=j && size[i]>=size[j] && speed[i]>=speed[j] && intelligence[i]>=intelligence[j]) shark[i].push_back(j);
		}
	}

	void maximumEat()
	{
		for(int i=0;i<num;i++)
		{
			for(int j=0;j<num;j++) visit[j]=false; /**/ eat(i);
			for(int j=0;j<num;j++) visit[j]=false; /**/ eat(i);
		}
		for(int i=0;i<num;i++) if(kill[i]==-1) result++;
	}

	int eat(int index)
	{
		for(int i=0;i<shark[index].size();i++) if(visit[shark[index][i]]==false && kill[shark[index][i]]!=index)
		{
			visit[shark[index][i]]=true;
			if(kill[shark[index][i]]==-1 || eat(kill[shark[index][i]]))
			{
				kill[shark[index][i]]=index;
				return 1;
			}
		}
		return 0;
	}
};
