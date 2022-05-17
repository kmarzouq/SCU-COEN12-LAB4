/* Khondakar Marzouq Mujtaba
 *
 * A program that contains functions that allow it to create linked lists which can contain multiple data types and then is able to manipulate them using hash functions
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#include "list.h"
//creating set data type that can take multiple data types. Big O(1)
struct set{
	int count;
	int length;
	void **data;
	int(*compare)();
	unsigned (*hash)();
};
//creates a set of lists the size of maxElts. Big O(n)
SET *createSet(int maxElts, int(*compare)(), unsigned(*hash)()){
	SET* sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count =0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(struct list*)*sp->length);
	assert(sp->data!=NULL);
	int i;
	for(i=0;i<sp->length;i++){
		sp->data[i]=createList(compare);
	}
	sp->compare = compare;
	sp->hash = hash;
	return (sp);
	}

//destroys a set and deallocates the memory we reserved. Big O(n)
void destroySet(SET *sp){
	assert (sp!=NULL);
	int i;
	for(i=0;i<sp->length;i++){
		destroyList(sp->data[i]);
	}
	free (sp->data);
	free (sp);
	}
//returns the number of elements in the set. Big O(1)
int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count;
	}
//searches for a list to place an element in using the hash function and then adds it. If the element is found, it stops the function. BigO(1)
void addElement(SET *sp, void *elt){
	assert(sp!=NULL);
	int ind = (sp->hash)(elt)%sp->length;
	if(findItem(sp->data[ind],elt)==NULL){
		addLast(sp->data[ind],elt);
		sp->count++;
		}
		
}
//removes an element from the set. Big O(1)
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL);
	int ind = (sp->hash)(elt)%sp->length;
	removeItem(sp->data[ind],elt);
	sp->count--;
	}
// finds an element and returns it if it is found. Otherwise it returns NULL. Big O(1)
void *findElement(SET *sp, void *elt){
		assert(sp!=NULL);
		int ind = (sp->hash)(elt)%sp->length;
		void* x = findItem(sp->data[ind],elt);
		if(x!=NULL){
			return x;
			}
		else{
			return NULL;
			}
	}

// returns and array of the elements in a set. Big O(n)
void *getElements(SET *sp){
	assert(sp!=NULL);
	void** arrstr;
	arrstr=malloc(sizeof(void*)*sp->count);
	int i,j;
	j=0;
	for(i=0; i< sp->length; i++){
		void** pl = getItems(sp->data[i]);
		memcpy(arrstr+j,pl,sizeof(void*)*numItems(sp->data[i]));
		j+=numItems(sp->data[i]);
		free(pl);
			}
	return arrstr;
}	
