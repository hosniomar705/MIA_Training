/*
 * File: task1.4.c
 * Author: omar hosni ahmed
 * Description: fusion two sensors readings to come up with more accurate readings
 * Date: 13/8/2023
 */

/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions

/* Main Function */
int main()
{
    //sensors accuracy
    float acc_mpu6050 = .78;
    float acc_bno55 = .92;
    //calculate a weight to each sensor based on its accuracy
    float wieght_mpu6050= acc_mpu6050/(acc_mpu6050+acc_bno55);
    float wieght_bno55= acc_bno55/(acc_mpu6050+acc_bno55);

    float mpu6050[10] = {0.0, 11.68, 18.95, 23.56, 25.72, 25.38, 22.65, 18.01, 10.14, -0.26};
    float bno55[10] = {0.0,9.49, 16.36, 21.2, 23.16, 22.8, 19.5, 14.85, 6.79, -2.69};
    //initialize array to put output in
    float fair[10];
    float good[10];
    //first method without taking accuracy of each sensor in consideration
    printf("fair:");
    for(int i=0;i<10;i++)
    {
        fair[i] = (mpu6050[i] + bno55[i])/2;
        printf("%f ",fair[i]);

    }
    //second method with taking accuracy of each sensor in consideration
    printf("\ngood:");
    for(int i=0;i<10;i++)
    {
        good[i] = wieght_mpu6050*mpu6050[i] + wieght_bno55*bno55[i];
        printf("%f ",good[i]);

    }

    return 0;
}
