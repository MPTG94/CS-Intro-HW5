/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

void print_arr(int arr[], int n);
void print_scan_int_request(char ch);
void print_scan_arr_request();
int get_int_from_user(int *var, char ch);
int fill_array_with_values(int *arr, int n);
void sort_arr(int *arr, int n, int k);

/*-------------------------------------------------------------------------
  This program takes as input an array ordered distance number, the size of
  an array and the numbers to fill the array with.
  The program will sort and print the sorted array.
 -------------------------------------------------------------------------*/
int main()
{
    int k = 0;
    int n = 0;
    print_scan_int_request('k');
    if (!get_int_from_user(&k, 'k'))
    {
        return 0;
    }
    print_scan_int_request('n');
    if (!get_int_from_user(&n, 'n'))
    {
        return 0;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        return 0;
    }

    if (n != 0)
    {
        print_scan_arr_request();
        if (!fill_array_with_values(arr, n))
        {
            return 0;
        }
        sort_arr(arr, n, k);
        print_arr(arr, n);
        free(arr);
    }

    return 0;
}

void sort_arr(int *arr, int n, int k)
{
    if (k == 0)
    {
        return;
    }
    else if (k < n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j - i <= k && j < n; j++)
            {
                if (arr[i] > arr[j])
                {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
    else if (k >= n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j <= n - 1; j++)
            {
                if (arr[i] > arr[j])
                {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
}

int fill_array_with_values(int *arr, int n)
{
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &num) != 1)
        {
            return 0;
        }
        arr[i] = num;
    }

    return 1;
}

int get_int_from_user(int *var, char ch)
{
    int k = 0;
    if (scanf("%d", &k) != 1)
    {
        return 0;
    }
    while (k < 0)
    {
        print_scan_int_request(ch);
        if (scanf("%d", &k) != 1)
        {
            return 0;
        }
    }
    *var = k;
    return 1;
}

void print_arr(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
}

void print_scan_int_request(char ch)
{
    printf("Please enter a non negative integer (%c):", ch);
}

void print_scan_arr_request()
{
    printf("Please enter n integer values with the special characteristic:\n");
}
