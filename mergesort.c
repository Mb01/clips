/* a linked list implementation */
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* returns pointer to head of sorted list */
node* list_merge_sort(node* list){

    /* one element by itself is sorted */
    if(!list->next){
        return list;
    }
    node *middle = list, *end = list;
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
        right = list->next;
        list->next = NULL;
    }
    /* make this more readable */
    node *left = list;


    /* call recursively on halves */
    left = list_merge_sort(left);
    right = list_merge_sort(right);

    /* put back together in order */
    /* the first element of the list will change we need to track what that is and return it */
    node *head = NULL, *pos = NULL;
    if(left->data < right->data){
        pos = left;
        head = left;
        left = left->next;
    }else{
        pos = right;
        head = right;
        right = right->next;
    }

    while(left || right){
        /* check if we can use from left */
        if(!right || (left && left->data <= right->data)){
            /* this is the only order that works */
            pos->next = left;
            pos = left;
            left = left->next;
            pos->next = NULL;
        }
        /* else use right as next */
        else{
            pos->next = right;
            pos = right;
                /* funny story this was left = right->next; took me an hour to find */
            right = right->next;
            pos->next = NULL;
        }
    }
    return head;
}

int main(int argc, char** argv){
    node* list = filetolist(argv[1]);
    list_print(list);
    list = list_merge_sort(list);
    list_print(list);
}
