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
  index is the current index to run over mandates array from.
  prev is the last relevant value from the temp array.
*/
int coalitions_calc(int mandates[], bool can_collaborate[][N], int temp[N], int prev, int index)
{
    int sum = 0;
    bool agree = true;
    prev++;
    if (index == N)
    {
        if (is_coalition(mandates, temp, index - 1))
        {
            return 1;
        }
        return 0;

    }
    for (int i = index; i < N; i++)
    {
        for (int j = index; j < N; j++)
        {
            temp[j] = can_collaborate[i][j];
            //sum+=coalitions_calc(mandates, can_collaborate, temp, prev,index+1);
        }
        print_arr(temp, index, N);
        sum+=is_coalition(mandates, temp, index);
    }
    /*temp[prev] = 1;
    for (int i = index; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            // going over each party and checking if it will cooperate with the current party.
            if (!can_collaborate[i][j])
            {
                printf("party no. %d will not cooperate with party %d\n", i, j);
                agree = false;
            }
        }
        if (agree)
        {
            // all parties agreed to cooperate, so this party will participate
            temp[i] = 1;
            print_arr(temp, index, N);
            // initiating new coalition check with current party included.
        }
        agree = true;
        sum += coalitions_calc(mandates, can_collaborate, temp, prev+1, index+1);
    }*/
    return sum;
}

int is_coalition(int mandates[], int temp[], int start)
{
    int sum = 0;
    for (int i = start; i < N; i++)
    {
        if (temp[i] == 1)
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
