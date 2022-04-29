/*
 * main.c
 *
 * Created: 3/27/2022 5:55:17 PM
 *  Author: NourhanAlrefaei
 */

#include "SimpleDb.h"

uint8_t number_of_procss;
uint8_t return_isFull;
uint8_t return_size;
uint8_t return_func_status;
static uint8_t id;
static uint8_t year;
uint8_t subjebt[COURSE_ID_MAX_SIZE];
uint8_t grades[COURSE_GRADE_MAX_SIZE];
uint8_t l_counter=ZERO_INIT;
uint8_t char_check_end_program='y';
uint8_t isExist=0;
uint8_t count=0;
uint8_t list[10];
uint8_t Delete_Success=ZERO_INIT;

int main()
{
    printf("Hello to Simple Database for Students \n");
    while(char_check_end_program=='y'){
        printf("If you want to check your database(Full or Not full or Empty)-->press 1\n"
             "If you want to get your database size --> press 2\n"
             "If you want to add data -->press 3\n"
             "If you want to delete data --> press 4\n"
             "If you want to read data --> press 5\n"
             "If you want to display student information -->press 6\n"
             "If you want to search for data -->press 7\n"
             "If you want to exit -->press 8\n\n");

     printf("Enter the number of your process: ");

     scanf("%d",&number_of_procss);
     switch(number_of_procss){
        case 1:
            return_isFull=SDB_isFull();
            if(return_isFull==0){
                printf("Your Database is Empty\n");
            }else if(return_isFull==1){
                printf("Your Database is Full\n");
            }else{
                printf("Your Database is not Full\n");
            }
            break;
        case 2:
            return_size=SDB_GetUsedSize();
            printf("The size of your database = %d students\n",return_size);
            break;
        case 3:
                printf("Please Enter the student ID:");
                scanf("%d",&id);
                printf("Please Enter the student year:");
                scanf("%d",&year);
                printf("Please Enter student courses id and courses grade:\n");
                for(l_counter=0;(l_counter<COURSE_ID_MAX_SIZE);l_counter++){
                printf("Course %d_ID:",l_counter+1);
                scanf("%d",&subjebt[l_counter]);
                printf("Course %d_grade:",l_counter+1);
                scanf("%d",&grades[l_counter]);
                }
                if(SDB_GetUsedSize()==0)
                {
                    SDB_AddHead(id,year,subjebt,grades);
                }
                else
                {
                    SDB_AddEntry(id,year,subjebt,grades);
                }
           break;

        case 4:
            printf("Please Enter the id of Student you want to delete:");
            scanf("%d",&id);
            Delete_Success=SDB_DeleteEntry(id);
            if(Delete_Success==1)
            {
                printf("The student has been deleted\n");
            }
            else
            {

            }
            break;
        case 5:
            printf("Please Enter the id of Student you want to read his data:");
            scanf("%d",&id);
            isExist=SDB_ReadEntry(id,&year,subjebt,grades);
            if(isExist==1){
                printf("The Student Year=%d\n",year);
                printf("The Student Subjects and his grade\n");
                for(l_counter=ZERO_INIT;(l_counter<COURSE_ID_MAX_SIZE);l_counter++){
                    printf("Course %d_ID:",l_counter+1);
                    printf("%d\n",subjebt[l_counter]);
                    printf("Course %d_grade:",l_counter+1);
                    printf("%d\n",grades[l_counter]);
                }
            }
            else{
                    printf("This Data is not exist\n");
                }

            break;
        case 6:
                SDB_GetIDList(&count,list);
                printf("The Number of students=%d\n",count);
                for(l_counter=ZERO_INIT;l_counter<count;l_counter++)
                {
                    printf("Student %d's id  %d\n",l_counter+1,list[l_counter]);
                }
            break;

        case 7:
            printf("Please Enter the id of Student you want to search for:");
            scanf("%d",&id);
            isExist=SDB_IsIdExist(id);
            if(isExist==1)
            {
                printf("The student is exist\n");
            }else{
                printf("The student is not exist\n");
            }
            break;

        case 8:
            char_check_end_program='n';
            break;
        default:
            exit(0);
    }
    printf("Do you want to continue [y,n]?");
    fflush(stdin);
    scanf("%c",&char_check_end_program);
    }
    return 0;
}
