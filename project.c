#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct student
{
    char id[20];
    char name[50];
    char department[30];
    char semester[10];
    double cgpa;
    char grade[5];
}STD;

void saveFile(STD student[],int count);
void loadFile(STD student[],int *count);
int checkDuplicateID(STD student[],int count,char id[]);
void displayHeader();
void showmenu();
void pauseScreen();
void addstudent(STD student[],int *count);
void displaystudent(STD student[],int count);
void searchstudent(STD student[],int count);
void updatestudent(STD student[],int count);
void deletestudent(STD student[],int *count);
void calculateGrade(STD student[],int count);

int main()
{
    STD student[100];
    int count = 0,choice;

    loadFile(student,&count);

    while(1)
    {
        displayHeader();
        showmenu();
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                addstudent(student,&count);
                break;
            case 2:
                displaystudent(student,count);
                break;
            case 3:
                searchstudent(student,count);
                break;
           case 4:
               updatestudent(student,count);
                break;
            case 5:
                deletestudent(student,&count);
                break;
            case 6:
                calculateGrade(student,count);
                break;
           case 7:
           {
            char choice;

            printf("\nAre you sure you want to exit? (Y/N): ");
            scanf(" %c",&choice);

            if(choice == 'Y' || choice == 'y')
            {
                saveFile(student,count);
                printf("Data saved successfully. Thank you\n");
                exit(0);
            }
            else if(choice == 'N' || choice == 'n')
            {
                printf("Exit cancelled.\n");
            }

            break;
           }
            default:
                printf("Invalid choice! Please select 1-7.\n");
        }
        pauseScreen();
    }
    return 0;
}

void displayHeader()
{
    printf("\n==============================================\n");
    printf("              Student Box\n");
    printf("International Islamic University Chittagong\n");
    printf("=================================================\n");
}

void showmenu()
{
    printf("\n====================================\n");
    printf("       Main Menu\n");
    printf("======================================\n");
    printf("1. Add Student Information\n");
    printf("2. Display Student Information\n");
    printf("3. Search Student Information\n");
    printf("4. Update Student Information\n");
    printf("5. Delete Student Information\n");
    printf("6. Calculate Student Grade\n");
    printf("7. Save & Exit\n");
    printf("======================================\n");
}

void addstudent(STD student[],int *count)
{
    if(*count >= 100)
    {
        printf("Student limit reached! Cannot add more.\n");
        return;
    }

    printf("\n--- Add Student Information ---\n");

    int duplicate;

    do
    {
        printf("Enter ID: ");
        scanf("%s",student[*count].id);

        duplicate = checkDuplicateID(student,*count,student[*count].id);

        if(duplicate == 1)
        {
            printf("ID already exits! Please enter another ID.\n");
        }
    }while(duplicate == 1);

    printf("Enter Name: ");
    scanf(" %[^\n]",student[*count].name);

    printf("Enter Department: ");
    scanf(" %[^\n]",student[*count].department);

    int sem;

    do
    {
        printf("Enter Semester (1-12): ");
        scanf("%s",student[*count].semester);

        sem = atoi(student[*count].semester);

        if(sem < 1 || sem > 12)
        {
            printf("Invalid Semester! Please enter a value between 1 and 12.\n");
        }
    } while (sem < 1 || sem > 12);

    do
    {
        printf("Enter CGPA (0.0  - 4.0): ");
        scanf("%lf",&student[*count].cgpa);

        if(student[*count].cgpa < 0 || student[*count].cgpa > 4)
        {
            printf("Invalid CGPA! Please enter a value between 0.0 and 4.0.\n");
        }
    } while (student[*count].cgpa < 0 || student[*count].cgpa > 4);

    strcpy(student[*count].grade,"N/A");

    (*count)++;

    printf("Student information added successfully!\n");
}

void displaystudent(STD student[],int count)
{
    if(count == 0)
    {
        printf("No student information available.\n");
        return;
    }

    printf("\n%-12s %-30s %-15s %-10s %-5s\n","ID","Name","Department","Semester","CGPA");
    printf("------------------------------------------------------------------------------\n");

    for(int i = 0; i < count; i++)
    {
        printf("%-12s %-30s %-15s %-10s %-5.2lf\n",student[i].id,student[i].name,student[i].department,student[i].semester,student[i].cgpa);
    }
}

void searchstudent(STD student[],int count)
{
    if(count == 0)
    {
        printf("No student information available.\n");
        return;
    }

    char searchid[20];
    printf("Enter Student ID to search: ");
    scanf("%s",searchid);

    int found = 0;

    for(int i = 0; i < count; i++)
    {
        if(strcmp(student[i].id,searchid) == 0)
        {
            printf("\n--- Student Information Found ---\n");
            printf("ID:         %s\n",student[i].id);
            printf("Name:       %s\n",student[i].name);
            printf("Department: %s\n",student[i].department);
            printf("Semester:   %s\n",student[i].semester);
            printf("CGPA:       %.2lf\n",student[i].cgpa);
            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("Student with ID %s not found.\n",searchid);
    }
}

void updatestudent(STD student[],int count)
{
    if(count == 0)
    {
        printf("No student information available.\n");
        return;
    }

    char updateid[20];
    printf("Enter Student ID to update: ");
    scanf("%s",updateid);

    int found = 0;

    for(int i = 0; i < count; i++)
    {
        if(strcmp(student[i].id,updateid) == 0)
        {
            printf("\n--- Update Student Information ---\n");

            printf("New Name: ");
            scanf(" %[^\n]",student[i].name);

            printf("New Department: ");
            scanf(" %[^\n]",student[i].department);

            int sem;
            do
            {
                printf("New Semester (1-12): ");
                scanf("%s",student[i].semester);

                sem = atoi(student[i].semester);

                if(sem < 1 || sem > 12)
                {
                    printf("Invalid Semester! Please enter a value between 1 and 12.\n");
                }

            }while(sem < 1 || sem > 12);

            do
            {
                printf("New CGPA (0.0 - 4): ");
                scanf("%lf",&student[i].cgpa);

                if(student[i].cgpa < 0 || student[i].cgpa > 4)
                {
                    printf("Invalid CGPA! Please enter a value between 0.0 and 4.\n");
                }
            }while(student[i].cgpa < 0 || student[i].cgpa > 4);

            found = 1;
            printf("Student information updated succcessfully!\n");
            break;
        }
    }

    if(found == 0)
    {
        printf("Student with ID %s not found.\n",updateid);
    }
}

void deletestudent(STD student[],int *count)
{
    if(*count == 0)
    {
        printf("No student information available.\n");
        return;
    }

    char deleteid[20];
    printf("Enter Student ID to delete: ");
    scanf("%s",deleteid);

    int found = 0;

    for(int i = 0; i < *count; i++)
    {
        if(strcmp(student[i].id,deleteid) == 0)
        {
            found = 1;

            printf("\n--- Student Information Found ---\n");
            printf("ID:         %s\n",student[i].id);
            printf("Name:       %s\n",student[i].name);
            printf("Department: %s\n",student[i].department);
            printf("Semester:   %s\n",student[i].semester);
            printf("CGPA:       %.2lf\n",student[i].cgpa);

            int choice;

            printf("Are you sure you want to delete this student information?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            printf("Enter your choice: ");
            scanf("%d",&choice);

            if(choice == 1)
            {
                for(int j = i; j < *count - 1; j++)
                {
                    student[j] = student[j + 1];
                }

                (*count)--;

                printf("Student information deleted successfully!\n");
            }
            else if(choice == 2)
            {
                printf("Deletion canceled.\n");
            }
            else
            {
                printf("Invalid choice! Deletion canceled.\n");
            }

            break;
        }
    }

    if(found == 0)
    {
        printf("Student with ID %s not found.\n",deleteid);
    }
}

void calculateGrade(STD student[],int count)
{
    if(count == 0)
    {
        printf("No student information available.\n");
        return;
    }

    char searchid[20];
    printf("\nEnter Student ID to see result: ");
    scanf("%s",searchid);

    int found = 0;

    for(int i = 0; i < count; i++)
    {
        if(strcmp(student[i].id,searchid) == 0)
        {
            found = 1;

            if(student[i].cgpa >= 3.75)
            {
                strcpy(student[i].grade,"A+");
            }
            else if(student[i].cgpa >= 3.50)
            {
                strcpy(student[i].grade,"A");
            }
            else if(student[i].cgpa >= 3.25)
            {
                strcpy(student[i].grade,"B+");
            }
            else if(student[i].cgpa >= 3.00)
            {
                strcpy(student[i].grade,"B");
            }
            else if(student[i].cgpa >= 2.75)
            {
                strcpy(student[i].grade,"C+");
            }
            else if(student[i].cgpa >= 2.50)
            {
                strcpy(student[i].grade,"C");
            }
            else if(student[i].cgpa >= 2.00)
            {
                strcpy(student[i].grade,"D");
            }
            else
            {
                strcpy(student[i].grade,"F");
            }

            printf("\n============================================\n");
            printf("              Academic Result\n");
            printf("============================================\n");

            printf("ID: %s\n",student[i].id);
            printf("Name: %s\n",student[i].name);
            printf("Department: %s\n",student[i].department);
            printf("Semester: %s\n",student[i].semester);

            printf("--------------------------------------------\n");

            printf("CGPA: %.2lf\n",student[i].cgpa);
            printf("Grade: %s\n",student[i].grade);

            printf("--------------------------------------------\n");

            if(strcmp(student[i].grade,"F") == 0)
            {
                printf("Status: Failed\n");
            }
            else
            {
                printf("Status: Passed\n");
            }

             printf("============================================\n");

             break;
        }
    }

    if(found == 0)
    {
        printf("\nStudent with ID %s not found!\n",searchid);
    }
}

void pauseScreen()
{
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

int checkDuplicateID(STD student[],int count,char id[])
{
    for(int i = 0; i < count; i++)
    {
        if(strcmp(student[i].id,id) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void saveFile(STD student[],int count)
{
    FILE *fp;

    fp = fopen("student.txt","w");

    if(fp == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        fprintf(fp,"%s\n",student[i].id);
        fprintf(fp,"%s\n",student[i].name);
        fprintf(fp,"%s\n",student[i].department);
        fprintf(fp,"%s\n",student[i].semester);
        fprintf(fp,"%.2lf\n",student[i].cgpa);
        fprintf(fp,"%s\n",student[i].grade);
    }

    fclose(fp);
}

void loadFile(STD student[],int *count)
{
    FILE *fp;

    fp = fopen("student.txt","r");

    if(fp == NULL)
    {
        return;
    }

    while(fscanf(fp,"%s\n",student[*count].id) == 1)
    {
        if(*count >= 100)
        {
            break;
        }

        fgets(student[*count].name,50,fp);
        student[*count].name[strcspn(student[*count].name,"\n")] = 0;

        fgets(student[*count].department,30,fp);
        student[*count].department[strcspn(student[*count].department,"\n")] = 0;

        fscanf(fp,"%s\n",student[*count].semester);

        fscanf(fp,"%lf\n",&student[*count].cgpa);

        fgets(student[*count].grade,20,fp);
        student[*count].grade[strcspn(student[*count].grade,"\n")] = 0;

        (*count)++;
    }

    fclose(fp);
}
