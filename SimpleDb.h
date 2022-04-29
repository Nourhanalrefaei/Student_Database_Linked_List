/*
 * SimpleDb.h
 *
 * Created: 3/27/2022 5:55:17 PM
 *  Author: NourhanAlrefaei
 */


#ifndef _SIMPLEDB_H
#define _SIMPLEDB_H

/****************************Inclues****************************/
#include "std_type.h"

/****************************Macros**************************/
#define DATABASE_MAX_SIZE                           10
#define COURSE_ID_MAX_SIZE                          3
#define COURSE_GRADE_MAX_SIZE                  COURSE_ID_MAX_SIZE

#define LINKED_LIST_SUCCESS			             0
#define LINKED_LIST_FAILURE			                 1
#define HEAD_NODE_CREATED			                 LINKED_LIST_SUCCESS
#define HEAD_NODE_NOT_CREATED		             LINKED_LIST_FAILURE


typedef struct{
uint8_t  student_ID;
uint8_t student_year;
uint8_t course_ID[COURSE_ID_MAX_SIZE];
uint8_t course_grade[COURSE_GRADE_MAX_SIZE];
}Student_info_t;

typedef struct node{
    Student_info_t  Student_info;
    struct node *next_node;
}node_t;

/*
 * Prototype    : uint8_t SDB_isFull(void);
 * Description : Check if the database isFull
 * Arguments  : void
 * return         : global data status (Empty or Not full or Full)
 */
uint8_t SDB_isFull(void);

/*
 * Prototype    : uint8_t SDB_GetUsedSize(void);
 * Description : Get number of entries in the database
 * Arguments  : void
 * return         : global counter of nodes
 */
uint8_t SDB_GetUsedSize(void);

/*
 * Prototype    : uint8_t SDB_AddHead(uint8_t id,uint8_t year,uint8_t *subjects, uint8_t *grades);
 * Description : Add the head of database
 * Arguments  : id , year, *subjects , *grades
 * return         :   return status of the function
 */
uint8_t SDB_AddHead(uint8_t id,uint8_t year,uint8_t *subjects, uint8_t *grades);

/*
 * Prototype    : uint8_t SDB_AddEntry(uint8_t id,uint8_t year,uint8_t *subjects, uint8_t *grades);
 * Description : Add new Entry to database
 * Arguments  : id , year, *subjects , *grades
 * return         : return status of the function
 */

uint8_t SDB_AddEntry(uint8_t id,uint8_t year,uint8_t *subjects, uint8_t *grades);

/*
 * Prototype    : return_status_t SDB_DeleteEntry(uint8_t id);
 * Description : Delete the entry with the given ID
 * Arguments  : id
 * return         : return status of the function
 */
return_status_t SDB_DeleteEntry(uint8_t id);

/*
 * Prototype    : uint8_t SDB_ReadEntry(uint8_t id,uint8_t *year,uint8_t *subjects, uint8_t *grades);
 * Description : Read an entry matching the providing id
 * Arguments  : id ,*year, *subjects, *grades
 * return         : return status (the id is exist or not)
 */

uint8_t SDB_ReadEntry(uint8_t id,uint8_t *year,uint8_t *subjects, uint8_t *grades);


/*
 * Prototype    : void SDB_GetIDList(uint8_t *Counter,uint8_t *List);
 * Description : Get the list of IDS of students
 * Arguments  : *Counter, *List
 * return         : void
 */

void SDB_GetIDList(uint8_t *Counter,uint8_t *List);

/*
 * Prototype    : uint8_t SDB_IsIdExist(uint8_t id);
 * Description : Checks if the provided id student is exist
 * Arguments  : id
 * return         : return status (id exist or not)
 */
uint8_t SDB_IsIdExist(uint8_t id);



#endif // _SIMPLEDB_H

