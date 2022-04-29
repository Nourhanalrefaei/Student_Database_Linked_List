/*
 * SimpleDb.c
 *
 * Created: 3/27/2022 5:55:17 PM
 *  Author: NourhanAlrefaei
 */

#include "SimpleDb.h"

/************************Global Variables***************************/
typedef enum
{
    DATABASE_IS_EMPTY = 0,
    DATA_BASE_IS_FULL,
    DATABASE_IS_NOT_FULL,
    DATABASE_INVALID_STATE,
};

uint8_t Counter_of_elements=0;

node_t *global_ptr_start_node = NULL;
node_t *global_ptr_next_node  = NULL;

uint32_t global_counter_of_nodes = 0;
uint8_t  global_uint8_head_created = HEAD_NODE_NOT_CREATED;
uint32_t global_uint32_database_status = DATABASE_IS_EMPTY;
uint8_t Exist=1;
uint8_t NotExist=0;

/*
 * Prototype    : uint8_t SDB_isFull(void);
 * Description : Check if the database isFull
 * Arguments  : void
 * return         : global data status (Empty or Not full or Full)
 */
uint8_t SDB_isFull(void){
    return global_uint32_database_status;
}
/*
 * Prototype    : uint8_t SDB_GetUsedSize(void);
 * Description : Get number of entries in the database
 * Arguments  : void
 * return         : global counter of nodes
 */
uint8_t SDB_GetUsedSize(void){
    return global_counter_of_nodes;
}

/*
 * Prototype    : uint8_t SDB_AddHead(uint8_t id,uint8_t year,uint8_t *subjects, uint8_t *grades);
 * Description : Add the head of database
 * Arguments  : id , year, *subjects , *grades
 * return         :   return status of the function
 */
uint8_t SDB_AddHead(uint8_t id,uint8_t year,uint8_t *subjects, uint8_t *grades)
{
    uint8_t uint8_retval = LINKED_LIST_SUCCESS;
        if(global_uint8_head_created == HEAD_NODE_NOT_CREATED)
        {
            if((subjects != NULL) && (grades != NULL))
            {
                global_ptr_start_node = (node_t*) malloc(sizeof(node_t));
                if(global_ptr_start_node != NULL)
                {
                    global_ptr_start_node->Student_info.student_ID = id;
                    global_ptr_start_node->Student_info.student_year = year;
                    uint8_t local_iterator;
                    for(local_iterator = 0; local_iterator < COURSE_ID_MAX_SIZE; local_iterator++)
                    {
                        global_ptr_start_node->Student_info.course_ID[local_iterator]= subjects[local_iterator];
                        global_ptr_start_node->Student_info.course_grade[local_iterator]= grades[local_iterator];
                    }
                    global_ptr_start_node->next_node = NULL;

                    global_counter_of_nodes++;
                    global_uint8_head_created = HEAD_NODE_CREATED;
                    global_uint32_database_status = DATABASE_IS_NOT_FULL;
                    printf("Head Implementation is completed\n");
                }
                else
                {
                    uint8_retval = LINKED_LIST_FAILURE;
                    printf("Head Node can't be allocated!\r\n");
                }
            }
            else
            {
                uint8_retval = LINKED_LIST_FAILURE;
                printf("Invalid Pointer!\r\n");
            }
        }
        else
        {
            printf("Head Already Created Before!\r\n");
            uint8_retval =LINKED_LIST_FAILURE;
        }
        return uint8_retval;
    }

/*
 * Prototype    : uint8_t SDB_AddEntry(uint8_t id,uint8_t year,uint8_t *subjects, uint8_t *grades);
 * Description : Add new Entry to database
 * Arguments  : id , year, *subjects , *grades
 * return         : return status of the function
 */

uint8_t SDB_AddEntry(uint8_t id,uint8_t year,uint8_t *subjects, uint8_t *grades)
{
    node_t *ptr_to_last_node=NULL;
	uint8_t uint8_retval = LINKED_LIST_SUCCESS;
    if(global_uint8_head_created == HEAD_NODE_CREATED)
	{
		if((subjects != NULL) && (grades != NULL) && (SDB_GetUsedSize() < DATABASE_MAX_SIZE))
		{
			global_ptr_next_node = (node_t*) malloc(sizeof(node_t));
			if(global_ptr_next_node != NULL)
			{
				global_ptr_next_node->Student_info.student_ID = id;
				global_ptr_next_node->Student_info.student_year = year;
				uint8_t local_iterator;
				for(local_iterator = 0; local_iterator < COURSE_ID_MAX_SIZE; local_iterator++)
				{
					global_ptr_next_node->Student_info.course_ID[local_iterator]= subjects[local_iterator];
					global_ptr_next_node->Student_info.course_grade[local_iterator]	= grades[local_iterator];
				}
				if(SDB_GetUsedSize()==1)
                {
                    global_ptr_start_node->next_node=global_ptr_next_node;
                }
                else
                {
                    ptr_to_last_node=global_ptr_start_node->next_node;
                    while(ptr_to_last_node != NULL)
                    {
                        ptr_to_last_node=ptr_to_last_node->next_node;
                    }
                    ptr_to_last_node=global_ptr_next_node;
                    ptr_to_last_node->next_node=NULL;
                }
                    global_ptr_next_node->next_node = NULL;

                    global_counter_of_nodes++;
			}
			else
			{
				uint8_retval = LINKED_LIST_FAILURE;
				printf("Node can't be allocated!\r\n");
				if(SDB_GetUsedSize() == DATABASE_MAX_SIZE)
				{
					global_uint32_database_status = DATA_BASE_IS_FULL;
				}
			}
		}
		else
		{
			uint8_retval =LINKED_LIST_FAILURE;
			printf("Node Creation Requirements Not Met!\r\n");
		}
	}
	else
	{
		uint8_retval =LINKED_LIST_FAILURE;
		printf("Head Node Not Created Before!\r\n");
	}
	return uint8_retval;
}

/*
 * Prototype    : return_status_t SDB_DeleteEntry(uint8_t id);
 * Description : Delete the entry with the given ID
 * Arguments  : id
 * return         : return status of the function
 */
return_status_t SDB_DeleteEntry(uint8_t id){
        node_t *ptr_node=NULL;
        node_t *temp_node=NULL;
        if(global_counter_of_nodes==0){
            printf("There is no data to delete!!!\n");
            return R_NOK;
        }else{
            ptr_node=global_ptr_start_node;
            temp_node=global_ptr_start_node;
            if(global_ptr_start_node->Student_info.student_ID==id)
                {
                ptr_node=ptr_node->next_node;
                global_ptr_start_node=ptr_node;
                free(temp_node);
                free(ptr_node);
                global_counter_of_nodes--;
                if(global_counter_of_nodes==0)
                {
                    global_uint32_database_status=DATABASE_IS_EMPTY;
                    global_uint8_head_created=HEAD_NODE_NOT_CREATED;
                }
                return R_OK;
            }
            while(ptr_node->Student_info.student_ID!=id)
            {
                temp_node=ptr_node;
                ptr_node=ptr_node->next_node;
                if(ptr_node==NULL)
                {
                    printf("This id is not found\n");
                    return R_NOK;
                }
            }
            temp_node->next_node=ptr_node->next_node;
            global_counter_of_nodes--;
            free(ptr_node);
        }
        return R_OK;
}

/*
 * Prototype    : uint8_t SDB_ReadEntry(uint8_t id,uint8_t *year,uint8_t *subjects, uint8_t *grades);
 * Description : Read an entry matching the providing id
 * Arguments  : id ,*year, *subjects, *grades
 * return         : return status (the id is exist or not)
 */
uint8_t SDB_ReadEntry(uint8_t id,uint8_t *year,uint8_t *subjects, uint8_t *grades){
    node_t *ptr_node=NULL;
    uint32_t l_counter=ZERO_INIT;
        if(global_ptr_start_node==NULL){
        printf("There is no students to search for!!!\n");
        return NotExist;
    }else{
        ptr_node=global_ptr_start_node;
        if((year==NULL)||(subjects==NULL)||(grades==NULL))
            {
                printf("Pointers are Invalid!!!\n");
                return NotExist;
            }
            else
                {

                }
        while(ptr_node !=NULL){
            if(ptr_node->Student_info.student_ID==id){
                *year =ptr_node->Student_info.student_year;
                for(l_counter;(l_counter<COURSE_ID_MAX_SIZE)&&(l_counter<COURSE_GRADE_MAX_SIZE);l_counter++){
                    *(subjects+l_counter)=ptr_node->Student_info.course_ID[l_counter];
                    *(grades+l_counter)=ptr_node->Student_info.course_grade[l_counter];
                }
                return Exist;
            }
            ptr_node=ptr_node->next_node;
    }
    return NotExist;
}
return NotExist;
}

/*
 * Prototype    : void SDB_GetIDList(uint8_t *Counter,uint8_t *List);
 * Description : Get the list of IDS of students
 * Arguments  : *Counter, *List
 * return         : void
 */
void SDB_GetIDList(uint8_t *Counter,uint8_t *List){
    node_t *ptr_node=NULL;
    ptr_node=global_ptr_start_node;
    uint8_t l_counter=ZERO_INIT;
    if(global_ptr_start_node==NULL){
            printf("There is no students in the database!!!\n");
    }else{
        if((Counter==NULL)||(List==NULL)){
            printf("There are Invalid Pointers\n");
        }
        else {
            while(ptr_node !=NULL){
            *Counter=global_counter_of_nodes;
            List[l_counter]=ptr_node->Student_info.student_ID;
            l_counter++;
            ptr_node=ptr_node->next_node;
        }
    }
        }
}

/*
 * Prototype    : uint8_t SDB_IsIdExist(uint8_t id);
 * Description : Checks if the provided id student is exist
 * Arguments  : id
 * return         : return status (id exist or not)
 */
uint8_t SDB_IsIdExist(uint8_t id){
    node_t *ptr_node=NULL;
        if(global_ptr_start_node==NULL){
        printf("There is no students to search for!!!");
        return NotExist;
    }else{
        ptr_node=global_ptr_start_node;
        while(ptr_node !=NULL){
            if(ptr_node->Student_info.student_ID==id){
                return Exist;
            }
            ptr_node=ptr_node->next_node;
    }
}
    return NotExist;
}
