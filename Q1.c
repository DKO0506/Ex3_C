#include<stdio.h>
#define SIZE 50

void printArr(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d", *(arr +i));
		if(i != n - 1)
			printf(",");
	}

}

void shift_element(int *arr, int i) 
{
	for (int  indx = i - 1; indx >= 0; indx--)
	{
		*(arr + indx + 1) = *(arr + indx);
	}
}//shift_element method to shift the element in the array from a given i one position to the right using pointers` syntax.

void insertion_sort(int *arr, int len)
{
	for (int i = 1; i < len; i++)
	{
		for (int j = 0; j < i; j++)
		{
		if(*(arr + i) < *(arr + j))
			{
				int temp = *(arr + i);
				shift_element(arr+j, i-j);
				*(arr + j) = temp;
			}
		}

	}
}

