// testalgorithm.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <algorithm>
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
		
		// curent-in-out
		{
			inList.erase(inList.begin());
			curRes.push_back(cur);
			stationDis(inList, s, curRes, allres);
			curRes.pop_back();
			inList.insert(inList.begin(),cur);
		}
		// current-in
		{
			inList.erase(inList.begin());
			s.push(cur);
			stationDis(inList, s, curRes, allres);
			s.pop();
			inList.insert(inList.begin(),cur);
		}
		// out 1, and in
		{
			if (s.size()!=0)
			{
				int outi = s.top();
				s.pop();
				curRes.push_back(outi);

				stationDis(inList, s, curRes, allres);
				inList.erase(inList.begin());
				s.push(cur);

				inList.insert(inList.begin(),cur);

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
	inList.push_back(6);
	inList.push_back(1);
	inList.push_back(5);
	inList.push_back(3);
	inList.push_back(2);
	inList.push_back(7);
	inList.push_back(4);
	stack<int> s;

	set<vector<int> > allres;
	vector<int> curRes;
	stationDis(inList, s, curRes, allres);

allres.begin();
	//sort(allres.begin(), allres.end());

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

