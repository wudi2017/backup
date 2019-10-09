#include <iostream>
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

/*
V (bag volume) 
N (things count)
v[] (volume table)
w[] (value table)
T (group count)
t[] (group table)
*/

// base 0-1
// https://blog.csdn.net/qq_38410730/article/details/81667885
/*
V=8 N=4
v w
2 3
3 4 <-
4 5 
5 6 <-
--->>> result: W=10 (4,2)
*/
int main_01()
{
	// input parameter
	int V=8;
	int N=4;
	vector<int> v;
	v.push_back(0);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	vector<int> w;
	w.push_back(0);
	w.push_back(3);
	w.push_back(4);
	w.push_back(5);
	w.push_back(6);

	// init dynimic planning table
	int ** dp = new int*[N+1]; // dynimic planning table
	for (int iLine = 0; iLine < N+1; ++iLine)
	{
		dp[iLine]=new int[V+1];
		memset(dp[iLine], 0, sizeof(int)*(V+1));
	}

	// cal dynimic planning table
	for (int iLine = 1; iLine <= N; ++iLine)
	{
		for (int iCol = 1; iCol <= V; ++iCol)
		{
			//set dtable[i][j] = ?
			if(iCol<v[iLine])
			{
				dp[iLine][iCol] = dp[iLine-1][iCol];
			}
			else
			{
				// use thins index i
				int ui_totalVal=w[iLine]+dp[iLine-1][iCol-v[iLine]];
				// NOT use thins index i
				int not_ui_totalVal = dp[iLine-1][iCol];

				int maxVal = max(ui_totalVal,not_ui_totalVal);

				dp[iLine][iCol] = maxVal;
			}
		}
	}

	// print dynimic planning table
	cout<<"dynimic planning>>>"<<endl;
	for (int iLine = 0; iLine <= N; ++iLine)
	{
		for (int iCol = 0; iCol <= V; ++iCol)
		{
			cout<<dp[iLine][iCol]<<" ";
		}
		cout<<endl;
	}

	// find select result use dynimic planning table
	int iLine=N;
	int iCol=V;
	int curVal=dp[iLine][iCol];
	while(curVal>0)
	{
		if(curVal==dp[iLine-1][iCol])
		{
			// not use i
			iLine=iLine-1;
		}
		else
		{
			// use i
			cout<<iLine<<" ";
			iCol=iCol-v[iLine];
			iLine=iLine-1;
		}
		curVal=dp[iLine][iCol];
	}
	cout<<endl;

	return 0;
}

// base group
// https://blog.csdn.net/xiaoxun2802/article/details/80036475
// https://www.cnblogs.com/aininot260/p/9308736.html
/*
V=10 N=6 T=3
t v w
1 2 1
1 3 2 <-
2 4 2
2 5 3 <-
3 2 4 <-
3 1 3
--->>> result: W=9(2,4,5)
*/
int main_group()
{
	// input parameter
	int V=10;
	int N=6;
	int T=3;
	vector<int> t;
	t.push_back(0);
	t.push_back(1);
	t.push_back(1);
	t.push_back(2);
	t.push_back(2);
	t.push_back(3);
	t.push_back(3);
	vector<int> v;
	v.push_back(0);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(2);
	v.push_back(1);
	vector<int> w;
	w.push_back(0);
	w.push_back(1);
	w.push_back(2);
	w.push_back(2);
	w.push_back(3);
	w.push_back(4);
	w.push_back(3);

	// groupthings
	vector< vector<int> > a;
	vector<int> v0;
	a.push_back(v0);
	for (int i = 1; i <= T; ++i)
	{
		vector<int> vs;
		for (int j = 0; j <= N; ++j)
		{
			if(t[j]==i)
			{
				vs.push_back(j);
			}
		}
		a.push_back(vs);
	}
	// print groupthings
	// cout<<"groupthings>>>"<<endl;
	// for (int iLine = 1; iLine <= T; ++iLine)
	// {
	// 	vector<int> vs = a[iLine];
	// 	for (int k = 0; k < vs.size(); ++k)
	// 	{
	// 		cout<<vs[k]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	// init dynimic planning table
	int ** dp = new int*[T+1]; // dynimic planning table
	for (int iLine = 0; iLine < T+1; ++iLine)
	{
		dp[iLine]=new int[V+1];
		memset(dp[iLine], 0, sizeof(int)*(V+1));
	}

	// cal dynimic planning table
	for (int iLine = 1; iLine <= T; ++iLine)
	{
		for (int iCol = 1; iCol <= V; ++iCol)
		{
			//cout<<"iLine:"<<iLine<<" iCol:"<<iCol<<endl;
			for (int k = 0; k < a[iLine].size(); ++k)
			{
				int indexK = a[iLine][k];
				//cout<<"indexK:"<<indexK<<endl;
				if(iCol-v[indexK] >=0)
				{
					dp[iLine][iCol] = max(dp[iLine][iCol], w[indexK]+dp[iLine-1][iCol-v[indexK]]);
					//cout<<"set:dp[iLine][iCol]="<<dp[iLine][iCol]<<endl;
				}
				else
				{
					dp[iLine][iCol] = max(dp[iLine][iCol], dp[iLine-1][iCol]);
				}
			}
		}
	}


	// print dynimic planning table
	cout<<"dynimic planning>>>"<<endl;
	for (int iLine = 0; iLine <= T; ++iLine)
	{
		for (int iCol = 0; iCol <= V; ++iCol)
		{
			cout<<dp[iLine][iCol]<<" ";
		}
		cout<<endl;
	}
}




//  base depend
// tree
vector<int> endPoint(100,0),head(100,0),next(100,0);
vector<int> root;
int tmpCount=1;
void addEdgeToTree(int a, int b)
{
	cout<<"addEdgeToTree:"<<a<<"-"<<b<<endl;
	endPoint[tmpCount]=b;
	next[tmpCount]=head[a];
	head[a]=tmpCount;
	tmpCount++;
}
void printTree()
{
	cout<<"head:";
	for (int i = 1; i <= 5; ++i)
	{
		cout<<head[i]<<" ";
	}
	cout<<endl;
	cout<<"next:";
	for (int i = 1; i <= 5; ++i)
	{
		cout<<next[i]<<" ";
	}
	cout<<endl;
	cout<<"endPoint:";
	for (int i = 1; i <= 5; ++i)
	{
		cout<<endPoint[i]<<" ";
	}
	cout<<endl;
	for (int iRoot = 0; iRoot < root.size(); ++iRoot)
	{
		int rootVal = root[iRoot];
		cout<<"rootVal:"<<rootVal<<endl;
		for (int a = head[rootVal]; a>0; a=next[a])
		{
			int b=endPoint[a];
			cout<<rootVal<<"-"<<b<<endl;
		}
	}
}

//main
int main_dep()
{
	// input parameter
	int V=10;
	int N=5;
	vector<int> v;
	v.push_back(0);
	v.push_back(8);
	v.push_back(4);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	vector<int> w;
	w.push_back(0);
	w.push_back(2);
	w.push_back(5);
	w.push_back(5);
	w.push_back(3);
	w.push_back(2);
	vector<int> parentTable;
	parentTable.push_back(0);
	parentTable.push_back(0);
	parentTable.push_back(1);
	parentTable.push_back(5);
	parentTable.push_back(5);
	parentTable.push_back(0);


	
	for (int i = 1; i <= N; ++i)
	{
		if(parentTable[i]==0) // root
		{
			root.push_back(i);
		}
		else // add to tree
		{
			addEdgeToTree(parentTable[i],i);
		}
	}
	printTree();

	// init dynimic planning table
	int ** dp = new int*[N+1]; // dynimic planning table
	for (int iLine = 0; iLine < N+1; ++iLine)
	{
		dp[iLine]=new int[V+1];
		memset(dp[iLine], 0, sizeof(int)*(V+1));
	}

	// cal dynimic planning table
	for (int iLine = 1; iLine <= N; ++iLine)
	{
		for (int iCol = 1; iCol <= V; ++iCol)
		{
			//set dtable[i][j] = ?
			if(iCol<v[iLine])
			{
				dp[iLine][iCol] = dp[iLine-1][iCol];
			}
			else
			{
				// use thins index i
				int ui_totalVal=w[iLine]+dp[iLine-1][iCol-v[iLine]];

				// NOT use thins index i
				int not_ui_totalVal = dp[iLine-1][iCol];

				int maxVal = max(ui_totalVal,not_ui_totalVal);

				dp[iLine][iCol] = maxVal;
			}
		}
	}

	// print dynimic planning table
	for (int iLine = 0; iLine <= N; ++iLine)
	{
		for (int iCol = 0; iCol <= V; ++iCol)
		{
			cout<<dp[iLine][iCol]<<" ";
		}
		cout<<endl;
	}

	// find select result use dynimic planning table
	cout<<"R:";
	int iLine=N;
	int iCol=V;
	int curVal=dp[iLine][iCol];
	while(curVal>0)
	{
		if(curVal==dp[iLine-1][iCol])
		{
			// not use i
			iLine=iLine-1;
		}
		else
		{
			// use i
			cout<<iLine<<" ";
			iCol=iCol-v[iLine];
			iLine=iLine-1;
		}
		curVal=dp[iLine][iCol];
	}
	cout<<endl;

	return 0;
}

