/*
* 
* SortImpls.h
* 
* Sort declarations/definitions
* 
* Sorts: Bubble, Insertion, Merge,
* IterativeMerge, Shell, and Quick
* 
* Helpers: merge, swap, findPivot
* 
* Made by Alan Lai on 11/16-30/2020
* CSS 342, Program 4
*/
#ifndef SORTIMPLS_H
#define SORTIMPLS_H
#include <vector>
#include <iostream>
using namespace std;


// Swap Helper
void swap(vector<int>& list, int index_1, int index_2);

// Quick Sort + find pivot helper
int FindPivot(vector<int>& list, int low, int high);
void QuickSort(vector<int>& list, int low, int high);

// Bubble Sort
void BubbleSort(vector<int>& list, int start, int end);

// Insertion Sort
void InsertionSort(vector<int>& list, int start, int end);

// Merge Sort + merge helper
void MergeSort(vector<int>& list, int first, int last);
void merge(vector<int>& list, int first, int mid, int last);

// Iterative Merge Sort
void IterativeMergeSort(vector<int>& list, int first, int last);

// ShellSort + ShellSorter (helper)
void ShellSort(vector<int>& list, int start, int end);
void ShellSorter(vector<int>& list, int n);

inline void swap(vector<int>& list, int index_1, int index_2)
{
	int temp = list[index_1];
	list[index_1] = list[index_2];
	list[index_2] = temp;
}



inline int FindPivot(vector<int>& list, int low, int high)
{
	int pivot = list[high];
	int small_index = low;
	for (int i = low; i < high; i++) {
		if (list[i] < pivot)
		{
			swap(list, i, small_index++);
		}
	}
	swap(list, small_index, high);	// drop Pivot
	return small_index;
}

inline void QuickSort(vector<int>& list, int low, int high)
{
	if (low < high)
	{
		int pivot = FindPivot(list, low, high);
		QuickSort(list, low, pivot - 1);
		QuickSort(list, pivot + 1, high);
	}
}


inline void BubbleSort(vector<int>& list, int start, int end)
{
	for (int a = start; a < end; a++)
	{
		for (int b = start; b < end - a; b++)
		{
			if (list[b] > list[b + 1])
			{
				swap(list, b, b + 1);
			}
		}
	}
}

inline void InsertionSort(vector<int>& list, int start, int end)
{
	for (int i = 1; i <= end; i++)
	{
		int temp = list[i];
		int index = i;
		while ((index > start) && (list.at(index - 1) > temp))
		{	// While index>0 and last value is greater than our current val(temp)
			list[index] = list[index - 1];	// Swap them.
			index--;
		}
		list[index] = temp;
	}
}

inline void merge(vector<int>& list, int first, int mid, int last)
{
	vector<int> temp_arr;

	if (mid > list.size() - 1)
	{
		mid = (list.size() - 1);
	}
	int first_one = first;
	int last_one = mid;
	int first_two = mid + 1;
	int last_two = last;
	int index = 0;

	while ((first_one <= last_one) && (first_two <= last_two))
	{
		if (list[first_one] <= list[first_two])
		{
			temp_arr.push_back(list[first_one]);
			first_one++;
		}
		else
		{
			temp_arr.push_back(list[first_two]);
			first_two++;
		}
	}
	while (first_one <= last_one)
	{
			temp_arr.push_back(list[first_one]);
			first_one++;
	}
	while (first_two <= last_two)
	{
			temp_arr.push_back(list[first_two]);
			first_two++;
	}

	for (int i = first; i <= last; i++)
	{
			list[i] = temp_arr[index];
			index++;
	}
}



inline void MergeSort(vector<int> &list, int first, int last)
{	
	if (first < last)
	{
		int mid = (first + last) / 2;
		MergeSort(list, first, mid);
		MergeSort(list, mid + 1, last);
		merge(list, first, mid, last);
	}
}

inline void IterativeMergeSort(vector<int>& list, int first, int last)
{
	if (first < last)
	{
		int* tempArr = new int[last + 1];	// Temporary Array
		int length = (last - first) + 1;
		int end = last + 1;
		int arraySize = 1;
		int first1, first2, last1, last2;
		int index1, index2, tempIndex;

		for (tempIndex = 0; tempIndex < first; tempIndex++)
		{
			tempArr[tempIndex] = list[tempIndex];
		}

		while (arraySize < length)
		{
			first1 = first;
			tempIndex = first;
			while ((first1 + arraySize) < end)
			{
				first2 = first1 + arraySize;
				last1 = first2 - 1;
				last2 = ((first2 + arraySize - 1) < end) ? (first2 + arraySize - 1) : (end - 1);

				for (index1 = first1, index2 = first2; index1 <= last1 && index2 <= last2; tempIndex++)
				{
					if (list[index1] <= list[index2])
					{
						tempArr[tempIndex] = list[index1++];
					}
					else
					{
						tempArr[tempIndex] = list[index2++];
					}
				}

				while (index1 <= last1)
				{
					tempArr[tempIndex++] = list[index1++];
				}

				while (index2 <= last2)
				{
					tempArr[tempIndex++] = list[index2++];
				}

				first1 = last2 + 1;
			}

			for (index1 = first1; tempIndex < end; index1++)
			{
				tempArr[tempIndex++] = list[index1];
			}

			for (int i = first; i < end; i++)
			{
				list[i] = tempArr[i];
			}
			arraySize *= 2;
		}
	}
}


inline void ShellSort(vector<int>& list, int start, int end)
{
	if ((start == 0) && (end == list.size() - 1))
	{
		ShellSorter(list, list.size());
		return;
	}
	vector<int> temp_arr;
	for (int i = start; i <= end; i++)
		temp_arr.push_back(list[i]);
	ShellSorter(temp_arr, temp_arr.size());
	int count = start;
	for (int sorted : temp_arr)
	{
		list[count] = sorted;
		count++;
	}
}

inline void ShellSorter(vector<int>& list, int n)
{
	int size = n;
	for (int gap = size / 2; gap > 0; gap = (gap == 2) ? 1 : int(gap / 2.2))
	{
		for (int i = gap; i < size; i++)
		{
			int temp = list[i];
			int j = i;
			for (;(j >= gap) && (temp < list[j - gap]); j -= gap)
			{
				list[j] = list[j - gap];
			}
			list[j] = temp;
		}
	}
}

#endif