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
int max_coalition(int mandates[], bool can_collaborate[][N], int max_parties[N]);
int coalitions_calc(int mandates[], bool can_collaborate[][N], int temp[N], int prev, int index, int max_parties[N], int *max);
int is_coalition(int mandates[], int temp[], int start);
void print_arr(int arr[], int start, int n);
int check_sum_for_temp(int mandates[], bool can_collaborate[][N], int temp[], int start, int end);
int fill_max_parties_arr(int temp[N], int max_parties[N], int start, int end);



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    int mandates[N]={0};
    bool can_collaborate[N][N] = {{0}};
    if (!scan_input(mandates, can_collaborate))
    {
        printf("Wrong input");
        return 0;
    }
    int max_parties[N] = {0};
    int party_num = max_coalition(mandates, can_collaborate, max_parties);
    printf("Parties in maximal coalition:\n");
    for (int i = 0; i < party_num; i++)
    {
        printf("%d ", max_parties[i]);
    }
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

int max_coalition(int mandates[], bool can_collaborate[][N], int max_parties[N])
{
    int temp[N] = {0};
    int max = 0;
    return coalitions_calc(mandates, can_collaborate, temp, 0, 0, max_parties, &max);
}

/*
  Function to check all of the different combinations of parties to form a coalition.
  temp is a temporary array to sote the current sub combination of parties.
  index is the length of the temp array.
  prev is the party we are currently checking combinations for.
*/
int coalitions_calc(int mandates[], bool can_collaborate[][N], int temp[N], int prev, int index, int max_parties[N], int *max)
{
    int num_parties = 0;
    int parties_holder = 0;
    int check = 0;
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
        // Checking if the current temporary array has enough cooperating parties to form a coalition and getting the number of mandates.
        check = check_sum_for_temp(mandates, can_collaborate, temp, 0, index + 1);
        if (check > *max)
        {
            // The current coalition is larger than previous ones, assigning new max and filling the max parties array.
            *max = check;
            parties_holder = fill_max_parties_arr(temp, max_parties, 0, index + 1);
            if (parties_holder > num_parties)
            {
                num_parties = parties_holder;
            }
        }
        // calling another calculation with the i party in the array and a shorter sub arr
        parties_holder = coalitions_calc(mandates, can_collaborate, temp, i + 1, index + 1, max_parties, max);
        if (parties_holder > num_parties)
            {
                num_parties = parties_holder;
            }
        // Emptying the cell containing the party in order to exclude it from further calculations.
        temp[index] = EMPTY;
    }
    return num_parties;
}

/*
  Function to check if the current temp array contains enough mandates to form a coalition.
*/
int is_coalition(int mandates[], int temp[], int start)
{
    int sum = 0;
    for (int i = start; i < N; i++)
    {
        if (temp[i] >= 0)
        {
            sum += mandates[i];
        }
    }
    if (sum > MANDATES_THRESHOLD)
    {
        return sum;
    }
    return 0;
}

/*
  Function to check which of the parties in the current temp array will cooperate and then
  check if these parties have enough mandates to form a coalition.
  The function will return the number of coalitions the parties have together.
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
                if (mandates[temp[i]] == 0)
                {
                    temp[i] = EMPTY;
                }
                else
                {
                        sum += mandates[temp[i]];
                }
            }
        }
    }
    if (sum > MANDATES_THRESHOLD)
    {
        return sum;
    }
    return 0;
}

/*
  Function to fill the max parties arr with the parties participating in the largest possible coalition.
  The function will return the number of participating parties in the largest coalition.
*/
int fill_max_parties_arr(int temp[N], int max_parties[N], int start, int end)
{
    int j = 0;
    for (int i = start; i < end; i++)
    {
        if (temp[i] >= 0)
        {
            max_parties[j] = temp[i];
            j++;
        }
    }
    return j;
}

void print_arr(int arr[], int start, int n)
{
    if (n == 0)
        return;

    printf("[");
    for (int i = start; i < n - 1; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[n - 1]);
}

