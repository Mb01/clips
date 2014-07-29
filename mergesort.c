/* a linked list implementation */
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

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
        
        if(!head){
            pos = head = use;
        }
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
