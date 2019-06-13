/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define N 5
#define MANDATES_THRESHOLD 60
#define EMPTY -1

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
  Function to check all of the different combinations of parties to form a coalition.
  temp is a temporary array to sote the current sub combination of parties.
  index is the length of the temp array.
  prev is the party we are currently checking combinations for.
*/
int coalitions_calc(int mandates[], bool can_collaborate[][N], int temp[N], int prev, int index)
{
    int sum = 0;
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
        // Checking if the current temporary array has enough cooperating parties to form a coalition.
        sum += check_sum_for_temp(mandates, can_collaborate, temp, 0, index + 1);
        // calling another calculation with the i party in the array and a shorter sub arr
        sum += coalitions_calc(mandates, can_collaborate,temp, i + 1, index + 1);
        // Emptying the cell containing the party in order to exclude it from further calculations.
        temp[index] = EMPTY;

    }
    return sum;
}

/*
  Function to check if the current temp array contains enough mandates to form a coalition.
*/
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
    if (sum > MANDATES_THRESHOLD)
    {
        return 1;
    }
    return 0;
}

/*
  Function to check which of the parties in the current temp array will cooperate and then
  check if these parties have enough mandates to form a coalition.
*/
int check_sum_for_temp(int mandates[], bool can_collaborate[][N], int temp[], int start, int end)
{
    int sum = 0;
    bool agree = true;
    // Going over each party and checking if it will collaborate with the other parties in the temp array.
    for (int i = start; i < end; i++)
    {
        for (int j = start; j < end; j++)
        {
            if (!can_collaborate[temp[i]][temp[j]])
            {
                // The currently iterated party will not collaborate with one of the parties in the temp array so it will be excluded.
                agree = false;
            }
        }
        if (agree)
        {
            if (temp[i] != EMPTY)
            {
                    sum += mandates[temp[i]];
            }
        }
    }
    if (sum > MANDATES_THRESHOLD)
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
