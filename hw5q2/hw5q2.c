/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define N 5

bool scan_1d_arr(int arr[], int n);
bool scan_2d_bool_arr(bool arr[][N], int nrows);
bool scan_input(int mandates[], bool can_collaborate[][N]);
int count_coalitions(int mandates[], bool can_collaborate[][N]);
int coalitions_calc(int mandates[], bool can_collaborate[][N], int temp[N], int prev, int index);
int is_coalition(int mandates[], int temp[], int start);
void print_arr(int arr[], int start,int n);
int check_sum_for_temp(int mandates[], bool can_collaborate[][N], int temp[], int start, int end);

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int mandates[N]= {0};
    bool can_collaborate[N][N] = {{0}};
    if (!scan_input(mandates, can_collaborate))
    {
        printf("Wrong input");
        return 0;
    }
    int coalition_num = count_coalitions(mandates, can_collaborate);
    printf("Number of coalitions: %d\n", coalition_num);
    return 0;
}

bool scan_1d_arr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", arr+i)!=1 || arr[i] < 0)
        {
            return false;
        }
    }
    return true;
}

bool scan_2d_bool_arr(bool arr[][N], int nrows)
{
    int x = 0;
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (scanf("%d", &x) != 1)
            {
                return false;
            }
            arr[i][j] = x; // convert to bool
        }
    }
    return true;
}

bool scan_input(int mandates[], bool can_collaborate[][N])
{
    printf("Enter mandates:\n");
    if (!scan_1d_arr(mandates, N))
    {
        return false;
    }
    printf("Enter possible collaborations:\n");
    return scan_2d_bool_arr(can_collaborate, N);
}


int count_coalitions(int mandates[], bool can_collaborate[][N])
{
    int temp[N] = {0};
    return coalitions_calc(mandates, can_collaborate, temp, 0, 0);
}

/*
  temp is a temporary array
  index is the length of the temp array.
  prev is the party we are currently looking at.
*/
int coalitions_calc(int mandates[], bool can_collaborate[][N], int temp[N], int prev, int index)
{
    int sum = 0;
    //int my_sum = 0;
    //bool agree = true;
    if (index == N)
    {
        if (is_coalition(mandates, temp, index - 1))
        {
            return 1;
        }
        return 0;

    }
    for (int i = prev; i < N; i++)
    {
        // adding the i party to the temp array
        temp[index] = i;
        //printf("temp arr is:\n");
        //print_arr(temp, 0, index+1);
        sum +=check_sum_for_temp(mandates, can_collaborate, temp, 0, index+1);
        //
        // going over the array from i until the length of the array
        /*for (int j = i; j < index+1; j++)
        {
            printf("i is: %d j is: %d\n",i ,j);
            // checking if party i will cooperate with j
            //printf("checking if %d will cooperate with %d\n", i, j);
            if (!can_collaborate[i][j])
            {
                agree = false;
            }
        }
        // party i will cooperate will all other parties in the array.
        if (agree)
        {
            //printf("party %d will cooperate with all other parties, so it will be included\n", i);
            my_sum+= mandates[i];
        }
        agree = true;*/
        //
        // calling another calculation with the i party in the array and a shorter sub arr
        sum += coalitions_calc(mandates, can_collaborate,temp, i+1, index+1);
        //sum+=is_coalition(mandates, temp, index);
        temp[index] = -1;

    }
    /*if (my_sum > 60)
    {
        sum++;
    }*/

    return sum;
}

int is_coalition(int mandates[], int temp[], int start)
{
    int sum = 0;
    for (int i = start; i < N; i++)
    {
        if (temp[i] != 1)
        {
            sum += mandates[i];
        }
    }
    if (sum > 60)
    {
        return 1;
    }
    return 0;
}

int check_sum_for_temp(int mandates[], bool can_collaborate[][N], int temp[], int start, int end)
{
    int sum = 0;
    bool agree = true;
    print_arr(temp, start, end);
    for (int i = start; i < end; i++)
    {
        for (int j = start; j < end; j++)
        {
            if (!can_collaborate[temp[i]][temp[j]])
            {
                agree = false;
            }
        }
        if (agree)
        {
            if (temp[i] != -1)
            {
                    sum+=mandates[temp[i]];
            }
        }
    }
    if (sum > 60)
    {
        printf("the sum for the array is enough to form a coalition\n");
        print_arr(temp, start, end);
        printf("the sum is: %d\n", sum);
        return 1;
    }
    return 0;
}

void print_arr(int arr[], int start,int n)
{
    if (n == 0) return;

    printf("[");
    for (int i = start; i < n - 1; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[n-1]);

}
