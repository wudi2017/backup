// testalgorithm.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
using namespace std;



void stationDis(vector<int> inList, stack<int> s, vector<int> curRes, set<vector<int> >& allres)
{
	if(inList.size()==0 && s.size() ==0)
	{
		allres.insert(curRes);
		return;
	}

	if(inList.size()!=0)
	{
		int cur=inList[0];
		inList.erase(inList.begin());

		// curent-in-out
		{
			curRes.push_back(cur);
			stationDis(inList, s, curRes, allres);
			curRes.pop_back();
		}
		// current-in
		{
			s.push(cur);
			stationDis(inList, s, curRes, allres);
			s.pop();
		}
		// out 1, and in
		{
			if (s.size()!=0)
			{
				int outi = s.top();
				s.pop();
				curRes.push_back(outi);
				s.push(cur);
				stationDis(inList, s, curRes, allres);
				curRes.pop_back();
				s.push(outi);
			}
			
		}
	}
	else
	{
		while (s.size()!=0)
		{
			int outi = s.top();
			s.pop();
			curRes.push_back(outi);
		}
		stationDis(inList, s, curRes, allres);
	}
}

int main()
{
	vector<int> inList;
	inList.push_back(1);
	inList.push_back(2);
	inList.push_back(3);
	inList.push_back(4);
	inList.push_back(5);
	inList.push_back(6);
	inList.push_back(7);
	stack<int> s;

	set<vector<int> > allres;
	vector<int> curRes;
	stationDis(inList, s, curRes, allres);


	for (set<vector<int> >::iterator it=allres.begin(); it!=allres.end(); ++it)
	{
		vector<int> res = *it;
		for (int j = 0; j < res.size(); ++j)
		{
			cout<<res[j];
		}
		cout<<endl;
	}

 	return 0;
}

