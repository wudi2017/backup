#include <iostream>
#include <string>
#include <string.h>
#include "math.h"
using namespace std;

string manacher(string s)
{
	string t;
	t.append("#");
	for (int i = 0; i < s.size(); ++i)
	{
		t.append(&s[i], 1);
		t.append("#");
	}

	
	int* p=new int[t.size()];
	memset(p,0,t.size()*sizeof(int));
	p[0]=1;
	p[1]=1;
	int mi=1;
	int mx=2;

	int maxi=0;
	int maxR=0;
	
	for (int i = 1; i < t.size(); ++i)
	{
		
		p[i] = (i<mx)?min(p[2*mi-i],mx-i):1;
		//cout<<"i-p[i]"<<i<<p[i]<<endl;
		
		while(i+p[i] <t.size() && t[i+p[i]] == t[i-p[i]]) 
		{

			++p[i];
			//cout<<p[i]<<endl;
		}

		if(mx<i+p[i]){
			mx=i+p[i];
			mi=i;
		}

		if(p[i]>maxR)
		{
			maxi=i;
			maxR=p[i];
		}
	}

	// cout<<t<<endl;
	// for (int i = 0; i < t.size(); ++i)
	// {
	// 	cout<<p[i];
	// }
	// cout<<endl;


	// cout<<"maxi:"<<maxi<<endl;
	// cout<<"maxR:"<<maxR<<endl;

	return s.substr((maxi-(maxR-1))/2,maxR-1);
}

int main()
{
	string s="3dddbasabddds";
	cout<<s<<endl;
	string result = manacher(s);
	cout<<result<<endl;
	return 0;
}