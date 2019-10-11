#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////
// func common template 
template<typename T1, typename T2> void add(T1 t1, T2 t2)
{
	int x = t1+t2;
	cout<<x<<endl;
}


template void add<int,int>(int t1, int t2); // explicite instantiation

template<> void add<float,int>(float t1, int t2)  // explicite specialization
{

}
/* C++ : function template partial specialization ‘add<T1, std::string>’ is not allowed */
// template<typename T1> void add<T1,string>(T1 t1, string t2)  // partial specialization
// {

// }


/////////////////////////////////////////////////////////////////////
// func common template
template<typename T1, typename T2> class Pair
{
public:
	void func()
	{

	}
};

Pair<string,string> ii; // implicit instantiation
template class Pair<int, double>; // explicite instantiation

template<> class Pair<const char*,int> // explicite specialization
{
public:
	void func()
	{

	}
};

template<typename T1> class Pair<T1,int> // partial specialization
{
public:
	void func()
	{

	}
};



int main()
{
	add<int,int>(1,2); // implicit instantiation


	return 0;
}