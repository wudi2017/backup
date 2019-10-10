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
// merge sort
void sort_merge_merge(vector<int> & arr, int i, int m, int j, vector<int> & temparr)
{
	//cout<<i<<m<<j<<endl;
	int iTemp = i;
	int i1 = i;
	int i2 = m+1;
	while(i1<=m && i2<=j)
	{
		if(arr[i1] > arr[i2])
		{
			temparr[iTemp++] = arr[i2++];
		}
		else
		{
			temparr[iTemp++] = arr[i1++];
		}
	}
	for (int k = i1; k <= m; ++k)
	{
		temparr[iTemp++] = arr[k];
	}
	for (int k = i2; k <= j; ++k)
	{
		temparr[iTemp++] = arr[k];
	}

	// copy tmparr -> origin arr
	for (int u = i; u <= j; ++u)
	{
		arr[u]=temparr[u];
	}
}
void sort_merge_impl(vector<int> & arr, int i, int j, vector<int> & temparr)
{
	if(i<j)
	{
		int mid = i + (j-i)/2;
		sort_merge_impl(arr, i, mid, temparr);
		sort_merge_impl(arr, mid+1, j, temparr);
		sort_merge_merge(arr, i, mid, j, temparr);
	}
	
}
void sort_merge(vector<int> & arr)
{
	vector<int> temparr(arr.size());
	sort_merge_impl(arr, 0, arr.size()-1, temparr);
}


//--------------------------------------------------
// heap sort
void adjust_heap(vector<int> & arr, int i, int j)
{
	//cout<<"i:"<<i<<" j:"<<j<<endl;
	while(true)
	{
		if (2*i+2<=j) // has left & right
		{
			int left = arr[2*i+1];
			int right = arr[2*i+2];
			//cout<<"left:"<<left<<"right:"<<right<<endl;
			if(arr[i]<=left && arr[i]<=right)
			{
				break;
			}
			else if(left<right)
			{
				swap(arr, i, 2*i+1);
				i=2*i+1;
			}
			else
			{
				swap(arr, i, 2*i+2);
				i=2*i+2;
			}
		}
		else if(2*i+1<=j) // has left
		{
			int left = arr[2*i+1];
			//cout<<"left:"<<left<<endl;
			if(arr[i]<=left)
			{
				break;
			}
			else
			{
				swap(arr, i, 2*i+1);
				i=2*i+1;
			}
		}
		else
		{
			break;
		}
		
	}
	//printArr(arr);
	
}
void create_heap(vector<int> & arr, int maxi)
{
	for (int i = maxi/2; i >=0; i--)
	{
		adjust_heap(arr, i, maxi);
	}
}

void sort_heap(vector<int> & arr)
{
	create_heap(arr, arr.size()-1);
	for (int i = arr.size()-1; i >= 0; i--)
	{
		swap(arr, 0, i);
		adjust_heap(arr, 0, i-1);
	}
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
	sort_heap(arr);

	cout<<"result:"<<endl;
	printArr(arr);

	return 0;
}