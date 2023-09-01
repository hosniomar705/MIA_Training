/*
 * File: task1.3.c
 * Author: omar hosni ahmed
 * Description: this code printing "GRU"
 * Date: 12/8/2023
 */

/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <stdlib.h> // Standard library functions
#include <string.h> // String library functions

/* Macros */
#define buffer_size 1000

/* Function Declarations */
/**
 * @brief by calling this fun you can add a new task.
 */
void add_task();

/**
 * @brief by calling this fun you can view all current tasks.
 */
void view_tasks();

/**
 * @brief by calling this fun you can remove a existing task.
 */
void remove_task();

/**
 * @brief by calling this fun you can mark any task as a completed or uncompletes task
 */
void mark_tasks();

//Global variables
char **tasks;
int *tasks_status = NULL;
int num_of_tasks = 0;

/* Main Function */
int main()
{
    int option = 1;
    tasks = (char **)malloc(num_of_tasks * sizeof(char *));

    printf("Wellcome to Minions Task Manager.\n");
    printf("1. Add Task.\n");
    printf("2. View Tasks.\n");
    printf("3. Remove Task.\n");
    printf("4. Mark Tasks.\n");
    printf("5. Exit.\n");

    while(option!=5)//take i/p from user
    {

        printf("\nSelect an option: ");
        scanf("%d",&option);
        while(option<1 || option>5)//to ensure that the user entered a valid number
        {
            printf("Select a valid option: ");
            scanf("%d",&option);
        }


        if(option == 1)
        {
            add_task();
        }
        else if(option == 2)
        {
            view_tasks();
        }
        else if(option == 3)
        {
            remove_task();
        }
        else if(option == 4)
        {
            mark_tasks();
        }

    }

    printf("Exiting Minions Task Manager. Have a great day!");

    return 0;
}

/* Function Declarations */
/**
 * @brief by calling this fun you can add a new task.
 */
void add_task()
{
    getchar();
    char buffer[buffer_size];//create buffer to save user input in it
    int length;
    num_of_tasks++;//increase number of tasks
    tasks = (char **)realloc(tasks,num_of_tasks * sizeof(char *));//create new pointer to tasks
    tasks_status = (int *)realloc(tasks_status,num_of_tasks * sizeof(int *));//create new space to add task status
    tasks_status[num_of_tasks-1] = 0;//initialize task status =0 "uncompleted"
    printf("Enter task description: ");
    fgets(buffer,buffer_size,stdin);//store user i/p in the buffer
    length = strlen(buffer);
    buffer[length-1] = '\0';//convert last char in buffer from "/n" to "/0" so we can use strcpy
    tasks[num_of_tasks-1] = (char *)malloc(length * sizeof(char));//create a space in the pointer that we have just created on tasks
    strcpy(tasks[num_of_tasks-1],buffer);//copy user i/p from buffer to tasks
    printf("Task added successfully!\n");

}

/**
 * @brief by calling this fun you can view all current tasks.
 */
void view_tasks()
{
    if(num_of_tasks==0)
    {
        printf("there is no tasks, go have some fun\n");
    }
    for(int i=0; i<num_of_tasks; i++)//print tasks
    {
        printf("Current Tasks:\n");
        printf("Task ID: %d\n",i+1);
        printf("Description: %s\n",tasks[i]);
    }
}

/**
 * @brief by calling this fun you can remove a existing task.
 */
void remove_task()
{
    int option;
    if (num_of_tasks==0)//to return to main menu when there is no tasks to remove
    {
        printf("there is no tasks, take a nap\n");
        return;
    }
    printf("Enter task ID to remove: ");
    scanf("%d",&option);//take user i/p
    while(option<1 || option>num_of_tasks)//to ensure that the user entered a valid number
    {
        printf("Enter a valid task ID to remove: ");
        scanf("%d",&option);
    }
    for(int i=option-1; i<num_of_tasks-1; i++)
    {
        tasks[i] = tasks[i+1];//move tasks that are after the removed task and overwrite the removed task
        tasks_status[i] = tasks_status[i+1];//move tasks_status that are after the removed task and overwrite the removed tasks_status
    }
    num_of_tasks--;//decrease number of task by one to keep track of number of tasks
    tasks = (char **)realloc(tasks,num_of_tasks * sizeof(char *));//resize tasks after we removed the task
    tasks_status = (int *)realloc(tasks_status,num_of_tasks * sizeof(int *));//resize tasks_status after we removed the task
    printf("Task removed successfully!\n");
}

/**
 * @brief by calling this fun you can mark any task as a completed or uncompletes task
 */
void mark_tasks()
{
    int num;
    while(1)
    {
        printf(" ----------------------------\n");//printing all tasks in a table
        for(int i=0; i<num_of_tasks; i++)
        {
            if(tasks_status[i]==0)
            {
                printf("| task%d | uncompleted task |\n ",i+1);
            }
            else
            {
                printf("| task%d |  completed task  |\n ",i+1);
            }
            printf("--------------------------\n");

        }
        printf("Enter task number to revert its status or 0 to exit: ");
        scanf("%d",&num);
        while(num<0 || num>num_of_tasks)//to ensure that the user entered a valid number
        {
            printf("Enter a valid task ID: ");
            scanf("%d",&num);
        }
        if(num==0)//to break while and return to main menu
        {
            break;
        }
        else if(tasks_status[num-1]==0)//revert task status that the user have entered its number
        {
            tasks_status[num-1] = 1;
        }
        else if(tasks_status[num-1]==1)
        {
            tasks_status[num-1] = 0;
        }


    }
}
