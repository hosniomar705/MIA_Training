/*
 * File: task1.2.c
 * Author: omar hosni ahmed
 * Description: this code printing numbers from 1 to n descending
 * Date: 12/8/2023
 */


 /* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions
#include <unistd.h> // Unix Standard functions

/* Main Function */
int main() {
    int n;
    printf("Enter a number= ");
    scanf("%d",&n);
    for(;n>0;n--)
    {
        printf("%d\n",n);
        sleep(1);//this give us one second delay
    }
    printf("Blast off to the moon");

    return 0;
}
