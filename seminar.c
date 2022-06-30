#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char name[20];
    int id;
    char dept[20];
    int salary;
    struct node *next;
} NODE;
//function to add employee at the end

NODE *ins_last(NODE *first)
{
    NODE *newnode, *temp;
    newnode = (NODE *)malloc(sizeof(NODE));
    printf("\nEnter the name of employee:");
    scanf("%s", newnode->name);
    printf("\nEnter the ID of employee:");
    scanf("%d", &newnode->id);
    printf("\nEnter the department of employee:");
    scanf("%s", newnode->dept);
    printf("\nEnter the salary of employee:");
    scanf("%d", &newnode->salary);
    newnode->next = NULL;
    if (first == NULL)
        first = newnode;
    else
    {
        temp = first;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }
    return (first);
}

//Delete the employee right to the employee with specified id

NODE *delete (NODE *first)
{

    NODE *temp,*del;
    int id;
    if (first == NULL)
    {

        printf("\nList is empty");
    }
    else
    {
        printf("\nEnter the id of employee");
        scanf("%d", &id);
        temp = first;
        while (temp != NULL)
        {

            if (temp->id == id)
            {
                if(temp->next==NULL)
                {
                    printf("\nNo employee is present to the right of the employee with %d id\n",id);
                    return (first);
                }
                
                printf("\nEmployee right to the employee with specified id %d having name %s and id %d is deleted successfully\n", temp->id, temp->next->name, temp->next->id);
                del=temp->next;
                temp->next = temp->next->next;
                free(del);
                
                return (first);
            }
            temp = temp->next;
        }
        printf("\nEmployee with id %d is not present in the list\n", id);
    }
    return (first);
}

//compute total salary of specific department

NODE *compute(NODE *first)
{

    int sum = 0;
    NODE *temp;
    char dept[20];
    if (first == NULL)
    {

        printf("\nLIst is empty");
    }
    else
    {
        printf("\nEnter the name of the department for salary computation:");
        scanf("%s", dept);
        temp = first;
        while (temp != NULL)
        {
            if (strcmp(dept, temp->dept) == 0)
            {
                sum = sum + temp->salary;
            }
            temp = temp->next;
        }
        printf("\nTotal salary of %s department is %d\n", dept, sum);
    }
    return (first);
}
//Display only those employee of specific department with salary greater than 50,000

void display(NODE *first)
{
    char dept[20];
    int flag=0;
    if (first == NULL)
    {
        printf("\nList is empty");
        return;
    }
    printf("\nEnter the name of the department:");
    scanf("%s", dept);
    
    while (first != NULL)
    {
        if (first->salary > 50000 && strcmp(first->dept,dept)==0)

        {
            if(flag==0)
            {
                printf("NAME\t\tID\tDEPT\tSALARY\n");
                flag=1;
            }
            printf("%s\t\t%d\t%s\t%d\n", first->name, first->id, first->dept, first->salary);
        }
        first = first->next;
    }
    if(flag==0)
    {
        printf("\nNo employee of dept %s having salary greater than 50,000",dept);
    }
}

//Display all employee present in the list

void display_all(NODE *first)
{
    if (first == NULL)
    {
        printf("\nList is empty");
        return;
    }
    printf("NAME\t\tID\tDEPT\tSALARY\n");
    while (first != NULL)
    {
        printf("%s\t\t%d\t%s\t%d\n", first->name, first->id, first->dept, first->salary);
        first = first->next;
    }
}

int main()
{
    NODE *first = NULL;
    int choice;
    while (1)
    {
        printf("\n1:Add Employee\n2:Delete\n3:Compute salary\n4:Display employee with salary>Rs.50000\n5:Display all\n6:Exit");
        printf("\nEnte your choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            first = ins_last(first);
            break;
        case 2:
            first = delete (first);
            break;
        case 3:
            first = compute(first);
            break;
        case 4:
            display(first);
            break;
        case 5:
            display_all(first);
            break;
        case 6:
            exit(0);
        }
    }
    return 0;
}