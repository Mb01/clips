#include "stdio.h"
#include "stdlib.h"
#include <gmp.h>

/* a queue implemented as a linked list, why not */
/* useful for making the list with add (push) and then using it as a linked list */
typedef struct Queue Queue;
typedef struct Node Node;

struct Queue{
    Node* head;
    Node* tail;
    int size;
};

struct Node{
    mpz_t data;
    Node* next;
};

/* makes an empty queue */
Queue* init_queue(){
    /* allocate for empty q */
    Queue* q = malloc(sizeof(Queue));
    /* set size to zero */
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/* append to the end (right) of a queue */
void q_add( Queue * queue, mpz_t data ){
    /* check if it's empty */
    if(queue->tail == NULL){
        /* create the first element */
        queue->head = queue->tail = malloc(sizeof(Node));
    }else{
        /* create the new element */
       queue->tail->next = malloc(sizeof(Node));
       /* set the new tail */
       queue->tail = queue->tail->next;
    }
    /* set the last elements next pointer to null */
    queue->tail->next = NULL;
    /* must initialize mpz_t */
    mpz_init( queue->tail->data );
    /* set the data of the new element */
    mpz_set(queue->tail->data, data);
    /* iterate size */
    queue->size++;
}

/* i.e. pop left */
Node* q_get( Queue * q ){
    if(q->head == NULL){
        return NULL;
    }
    /* reset head */
    Node* old = q->head;
    q->head = q->head->next;
    /* reduce size */
    q->size--;
    return old;
}

/* attach to queues together save as q1 */
void extend(Queue* q1, Queue* q2){
    q1->tail->next = q2->head;
    q1->tail = q2->tail;
    /* but we might want to save the reference */
    /* free(q2) */
    return;
}

/* copy q1 into q2 */
void copy(Queue* q1, Queue* q2){
    /* don't kill q1 with q_get */
    Node* next = q1->head;
    /* now we have a linked list */
    while(next != NULL){
        q_add(q2, next->data);
        next = next->next;
    }
}

/*TODO free queue nodes. How about a function ^^^somewhere above^^^?*/

void printq( Queue* q ){
    Node* next = q->head;
    while(next != NULL){
        gmp_printf("%Zd", next->data);
        next = next->next;
        if(next != NULL){
            printf(",");
        }
    }
    printf("\n");
}

/* find prime factors for a number, store in a queue */
Queue* prime_factor( mpz_t arg ){
    /* holds a root of arg or reduced arg such that we know when to stop looking */
    mpz_t arg_sqr;
    mpz_init(arg_sqr);
    /* holds all temp mpz_t values */
    if( !mpz_cmp_ui( arg, 0) || !mpz_cmp_ui( arg, 1) ){
        return NULL;
    }
    /* q is a container for the result */ 
    Queue* q = init_queue();
    /* get the square root of the number to find,
       two factors can't both be above this */
    mpz_sqrt(arg_sqr, arg);
    /* in case a number is a perfect square, add one */
    mpz_add_ui(arg_sqr, arg_sqr, 1);
    /* current number for testing division */
    mpz_t x;
    mpz_init_set_ui(x,2);

    while( /* x <= arg_sqr */ (mpz_cmp(x, arg_sqr) < 1)){
        /* continue adding factor x while arg is divisible by x */
        /* while(arg % x == 0){ */
        while(mpz_divisible_p(arg, x)){
            /* add the number arg is divisible by to the queue */
            q_add(q, x);
            
            /* arg = arg / x; */
            mpz_divexact(arg, arg, x);
            
            /* set the new root which x must be less than */
            /* sticking with sqaure root for now */
            mpz_sqrt( arg_sqr, arg);
            /* add one in case perfect square  */
            mpz_add_ui(arg_sqr, arg_sqr, 1);
            
        }
        /* x++, we're missing a chance to skip even numbers */
        mpz_add_ui(x, x, 1);
    }
    /* if there is anything remaining of the arg, add it to the result */
    /* I think this is only the case when the original argument is prime */
    if(mpz_cmp_ui( arg, 1) == 1){
        q_add(q, arg);
    }
    printq( q );
    free(q);
}


int main(int argv, char **argc){
    int x;
    for(x = 1; x < argv; x++){
        mpz_t arg;
        /* set arg, from the xth argument, using base from notation convention (e.g. 123 is decimal 0xff is hex) */
        mpz_init_set_str(arg, argc[x], 0);
        prime_factor( arg );
    }
}


