#include <iostream>
using namespace std;

#include <vector>

void printArr(vector<int> arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}


void swap(vector<int> & arr, int a, int b)
{
	// cout<<"swap:"<<a<<" "<<b<<endl;
	int x = arr[a];
	arr[a] = arr[b];
	arr[b] = x;


	// for (int i = 0; i < arr.size(); ++i)
	// {
	// 	cout<<arr[i]<<" ";
	// }
	// cout<<endl;
}

//--------------------------------------------------
// select sort
void sort_select(vector<int> & arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		int minval = arr[i];
		int newMinIndex = i;
		for (int j=i+1; j < arr.size(); ++j)
		{
			if(arr[j] < minval)
			{
				newMinIndex=j;
			}
		}
		swap(arr, i, newMinIndex);
	}
}

//--------------------------------------------------
// fast sort
int sort_fast_sep2(vector<int> & arr,int i, int j)
{
	//cout<<"sort_fast_sep2---"<<endl;
	int firstIndex = i;
	int mval = arr[firstIndex];
	//cout<<"mval:"<<mval<<endl;
	while(i<j)
	{
		while(arr[i]<=mval && i<j)
			i++;
		while(arr[j]>=mval && i<j)
			j--;
		if(i<j && arr[i]>arr[j])
		{
			//cout<<"find:ij="<<i<<j<<endl;
			swap(arr,i,j);
		}
		
	}
	int midIndex = i-1;
	if(arr[i]<=mval)
		midIndex = i;
	else
		midIndex = i-1;

	//cout<<"midIndex="<<midIndex<<endl;
	swap(arr,firstIndex,midIndex);

	return midIndex;
}
int sort_fast_sep(vector<int> & arr,int i, int j)
{
	int mval = arr[i];
	while(i<j)
	{
		while(arr[j]>=mval && i<j)
			j--;
		swap(arr,i,j);

		while(arr[i]<=mval && i<j)
			i++;
		swap(arr,i,j);
	}
	return i;
}
void sort_fast_imp(vector<int> & arr,int i, int j)
{
	if(i<0 || i>=j)
		return;
	int iM = sort_fast_sep(arr, i, j);

	cout<<i<<iM<<j<<endl;
	printArr(arr);

	sort_fast_imp(arr, i, iM-1);
	sort_fast_imp(arr, iM+1, j);
}
void sort_fast(vector<int> & arr)
{
	sort_fast_imp(arr, 0, arr.size()-1);
}


//--------------------------------------------------
// main


int main()
{
	vector<int> arr;

	// int x;
	// while(cin>>x)
	// {
	// 	arr.push_back(x);
	// }

	arr.push_back(7);
	arr.push_back(1);
	arr.push_back(9);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(6);
	arr.push_back(4);
	arr.push_back(2);

	cout<<"origin:"<<endl;
	printArr(arr);

	cout<<"call sort:"<<endl;
	sort_fast(arr);

	cout<<"result:"<<endl;
	printArr(arr);

	return 0;
}