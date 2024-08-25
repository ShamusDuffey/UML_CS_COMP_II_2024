#define _CRT_SECURE_NO_WARNINGS
/**********************************************************************
Program: River Ferry Logistics Management
Author: Shamus Duffey
Date: 8/24/2024
Time spent: 2 weeks
Purpose: This program provides tools using a queue data structure to read formatted input
corresponding to the backlog of a river ferry's terminals and outputs the number of crossings necessary to accomodate
all accumulated traffic.
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
char findBank(FILE* fp)
{
    char c = '.';
    //int iterations = 0;
    char result = '.';
    while (c != EOF)
    {
        fscanf(fp, "%c", &c);

        if (c == 'l')
        {
            result = 'l';
        }
        else if (c == 'r')
        {
            result = 'r';
        }
        else if (c == 't')
        {
            fscanf(fp, "\n");
            return result;
        }
    }
    return -1;
}
int main(int argc, char** argv)
{
    //opening the file, assigning the file to fp, and checking for a successful assignment
    FILE* fp = NULL;

    fp = fopen("RiverFerryInput.txt", "r");

    if (!fp)
    {
        exit(1);
    }
    printf("File opened\n");//
    //--------------------------------------------------------------------------------------
    //Initialization of opaque objects
    QUEUE leftBank = queueInit();

    if (!leftBank)
        exit(2);

    QUEUE rightBank = queueInit();

    if (!rightBank)
        exit(2);
    //------------------------------------
    //Initializing variables
    int c, l, m, carLength, sumL = 0, sumR = 0, crossings = 0;
    char bank;
    /*Variable dictionary for this file
    c: the number of test cases to be expected for the input
    l: the length of available space on the river ferry in meters
    m: the number of cars in the test case
    carLength: this variable stores the length in centimeters of the car currently being evaluated
    sumL: a variable used to sum up the content of the queue representing the left bank, traversing the queue and comparing the
  sum of the content upto that point added to carLength to l to ensure the aggregate length of the cars does not exceed l
    sumR: sumL but for the queue representing the right bank
    bank: this variable stores which bank the car being evaluated at any given time is located on*/
    //------------------------------------
    //Apprehending c, the number of test cases:
    fscanf(fp, "%d", &c);
    printf("%d test cases\n", c);//
    //------------------------------------------
    //for loop reading each of the c test cases
    for (int i = 0; i < c; i++)
    {
        fscanf(fp, "%d %d", &l, &m);//reads l, the length of available space on the river ferry in meters, then m, the number of cars in the test case
        for (int j = 0; j < m; j++)
        {
            fscanf(fp, "%d", &carLength);
            bank = findBank(fp);
            if (bank == 'r')
            {
                queueInsert(rightBank, carLength);
            }
            else if (bank == 'l')
            {
                queueInsert(leftBank, carLength);
            }
            else
            {
                printf("The findBank function isn't working. Let's figure out what's wrong with it.\n");
                exit(3);
            }
        }
        l *= 100;//convert l to centimeters
        //sum the queues until the sum is greater than l
        while (getSize(leftBank)>0 || getSize(rightBank)>0)
        {
            if ((sumL + getFront(leftBank) < l) && getSize(leftBank)>0 || getSize(rightBank)>0)
                crossings++;
            while ((sumL + getFront(leftBank) < l) && getSize(leftBank))//This loop loads vehicles onto the ferry until the next one won't fit.
            {
                sumL += getFront(leftBank);
                queueService(leftBank);
            }
            if ((sumR + getFront(rightBank) < l) && getSize(rightBank) > 0 || getSize(leftBank) > 0)
                crossings++;
            while ((sumR + getFront(rightBank) < l) && getSize(rightBank))
            {
                sumR += getFront(rightBank);
                queueService(rightBank);
            }
            sumR = 0;//resetting the sums because the boat is empty now
            sumL = 0;
        }
        if (getSize(leftBank))
            printf("One of the sizes isn't 0\n");//
        printf("%d\n", crossings);
        crossings = 0;
    }
    //Destroying opaque objects and closing the file ----------
    queueDestroy(&leftBank);
    queueDestroy(&rightBank);
    fclose(fp);
    //---------------------------------------------------------
    return 0;
}
