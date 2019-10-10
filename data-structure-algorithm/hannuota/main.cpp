#include <iostream>
using namespace std;


void moveHNT(int n, int s, int d, int m)
{
	if(0==n) return;
	moveHNT(n-1, s, m, d);
	cout<<"move 1 form "<<s<<" to "<<d<<endl;
	moveHNT(n-1, m, d, s);
}

int main()
{
	moveHNT(3, 1, 3, 2);
	return 0;
}