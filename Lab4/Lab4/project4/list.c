
/*Khondakar Mujtaba
 *
 *This program creates and a doubly linked circular list and manipulates it by adding, removing, or returning values.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

//creates list structure Big O(1)
struct list{
	int count;
	struct node *head;
	int(*compare)();
};
// creates node structure Big O(1)
struct node{
	void *data;
	struct node *next;
	struct node *prev;
};
//creates and allocates memory for a list with a count, a head, and a compare function. Big O(1)
LIST *createList(int(*compare)()){
	struct list *lp;
	lp = malloc(sizeof(struct list));
	assert(lp!=NULL);
	lp->compare = compare;
	lp->count=0;
	lp->head = malloc(sizeof(struct node));
	assert(lp->head!=NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}
//returns number of items in list. Big O(1)
int numItems(LIST *lp){
	assert(lp!=NULL);
	return lp->count;
	}

//Adds an item to the beginning of the list. Big O(1)
void addFirst(LIST *lp, void *item){
	assert(lp!=NULL && item!=NULL);
	struct node *dum = lp->head->next;
	struct node *i;
	i=malloc(sizeof(struct node));
	i->next=dum;
	i->prev=dum->prev;
	dum->prev->next=i;
	dum->prev=i;
	i->data=item;
	lp->count++;
}
//Adds an item to the end of the list. Big O(1)
void addLast(LIST *lp, void *item){
	assert(lp!=NULL && item!=NULL);
	struct node *dum = lp->head->prev;
	struct node *i;
	i=malloc(sizeof(struct node));
	i->prev = dum;
	i->next = dum->next;
	dum->next->prev=i;
	dum->next = i;
	i->data = item;
	lp->count++;
}
//Gets the first item in a list. Big O(1)
void *getFirst(LIST *lp){
	assert(lp!=NULL);
	return lp->head->next->data;
	}
// Gets the last item in a list. Big O(1)
void *getLast(LIST *lp){
	assert(lp!=NULL);
	return lp->head->prev->data;
	}

//Removes the first item in a list. Big O(1)
void *removeFirst(LIST *lp){
	assert(lp!=NULL);
	struct node *dum = lp->head->next;
	dum->prev->next = dum->next;
	dum->next->prev = dum->prev;
	void *ret;
	ret = dum->data;
	free(dum);
	lp->count--;
	return ret;
	}
//Removes the last item in a list. Big O(1)
void *removeLast(LIST *lp){
	assert(lp!=NULL);
	struct node *dum = lp->head->prev;
	dum->next->prev = dum->prev;
	dum->prev->next = dum->next;
	void *ret;
	ret = dum->data;
	free(dum);
	lp->count--;
	return ret;
}
//Removes an item from anywhre in the list. Big O(n)
void removeItem(LIST *lp, void *item){
	assert(lp!=NULL && item!=NULL);
	struct node *dum = lp->head->next;
	int i;
	void *ret;
	for(i=0; i< lp->count; i++){
		if((*lp->compare)(dum->data,item)==0){
			dum->next->prev = dum->prev;
			dum->prev->next = dum->next;
			ret = dum->data;
			free(dum);
			lp->count--;
		}
		dum=dum->next;
	}	
}
//Finds out whther or not an item is in a list. Big O(n)
void *findItem(LIST *lp, void *item){
	assert(lp!=NULL && item!=NULL);
	int i;
	struct node *dum = lp->head;
	for(i=0; i< lp->count ; i++){
		if((*lp->compare)(dum->next->data,item)==0){
			return dum->next->data;
			}
		dum=dum->next;
		}
	return NULL;
	}
//Gets all the items in a list into an array and returns its pointer. Big O(n)
void *getItems(LIST *lp){
	assert(lp!=NULL);
	void** arrstr;
	arrstr=malloc(sizeof(void*)*lp->count);
	struct node *dum = lp->head->next;
	int i;
	for(i=0; i<lp->count; i++){
		arrstr[i]=dum->data;
		dum=dum->next;
		}
	return arrstr;
	}
//Destroys the list and deallocates its memory. Big O(n)
void destroyList(LIST *lp){
	assert(lp!=NULL);
	int i;
	struct node *dum = lp->head;
	for(i=0;i<lp->count;i++){
		struct node *nxt;
		nxt=dum->next;
		free(dum);
		lp->count--;
		dum=nxt;
	}
	free(lp);
}

