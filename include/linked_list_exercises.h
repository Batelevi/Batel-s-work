/*********************************************
* Developer:      Batel                      *
* Reviewer:       -                          *
* Version:        1.0                        *    
* Description: API for singly_linked_list.c  * 
**********************************************/
#ifndef __OL134_LINKED_LIST_EXERCISES_H__
#define __OL134_LINKED_LIST_EXERCISES_H__

typedef struct node node_t;


/*	reverses the order of a given slist	*/
node_t *Flip(node_t *head);

/*	tells whther a given slist has loop	*/
int HasLoop(const node_t *head);

/*	returns a pointer to a first node mutual to both slists, if any	*/
node_t *FindIntersection(node_t *head_1, node_t *head_2);


#endif /* __OL134_LINKED_LIST_EXERCISES_H__*/
