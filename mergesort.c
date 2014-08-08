/* an in-place mergesort implementation for linked lists */
/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    For a copy of the GNU General Public License see http://www.gnu.org/licenses/
    Copyright Mark Bowden 2014
*/
#include <stdlib.h>
#include <stdio.h>
#include "list.h" /* typedef struct node node | filetolist(char* filename) | list_print(node* head) */

/* returns pointer to head of sorted list */
/* it might be simpler to have a reference to left and set that to head at the end */
/* e.g. void list_merge(node** head){ left = *head; *head = NULL; ... continue in the same manner but don't return */
node* list_merge_sort(node* left){

    /* one element by itself is sorted */
    if(!left->next){
        return left;
    }
    node *middle = left, *end = left;
    /* find a suitable middle node at which to split */
    while(end){
        end = end->next;
        middle = middle->next;
        if(end){
            end = end->next;
        }
    }
    /* break the list up */
    node *right;
    if(middle->next != end){
        right = middle->next;
        middle->next = NULL;
    }else{
        right = left->next;
        left->next = NULL;
    }

    /* call recursively on halves */
    left = list_merge_sort(left);
    right = list_merge_sort(right);

    /* put back together in order */
    /* the first element of the list will change we need to track what that is and return it */
    node *head = NULL, *pos = NULL;

    while(left || right){
        /* check if we can use from left */
        node* use = NULL;
        if(!right || (left && left->data <= right->data)){
            use = left;
            left = left->next;
        }
        /* else use right as next */
        else{
            use = right;
            right = right->next;
        }
        /* the head is the first node used */
        if(!head){
            pos = head = use;
        }
        /* set the next node in the new list to use and move position to that */
            pos->next = use;
            pos = use;
    }
    return head;
}

int main(int argc, char** argv){
    node* list = filetolist(argv[1]);
    list = list_merge_sort(list);
    list_print(list);
}
