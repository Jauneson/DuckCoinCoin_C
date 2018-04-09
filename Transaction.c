/*
j’ai créé la structure pour faire une liste avec sentinelle comme c’est demandé, Je ne rien changé, j’ai seulement ajouté la structure et quelque fonction. Pour la version 1 j’ai fait une seule fonction qui renvoi une chaîne de caractères et pour la version 2 j’ai fait de fonctions qui réalisent des opérations sur les listes.
Par contre je n’ai rien changé dans le .h parce que je ne suis pas en vie ;)
*/
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sha256_utils.h"
#include "Transaction.h"


/********FONCTION DE CREATION DE DATE*************/

char * getTimeStamp(){
    time_t ltime;
    time(&ltime);
    return ctime(&ltime);
}

/*************************************************/

typedef struct s_transaction {
    struct s_transaction next ;
    struct s_transaction prev ;
    int index ;
    char *srcDest ;
    char hash[SHA256_BLOCK_SIZE*2 + 1] ; // calcul et stockage du hash directement à l'ajout d'une transaction dans la deque
} *Transaction ;

struct s_transactionDeque {
    struct s_transaction *sentinel ;
    int size ;
} ;

/****************************************************/

char *create_transaction() {
    char transaction[30] = "Source-Destination : " ;
    srand(time(NULL)) ;
    sprintf(transaction,"%s%d"-,transaction,rand()%MAX_VALUE) ;
    return transaction ;
}

TransactionDeque init_transaction_deque() {
    TransactionDeque t = malloc(sizeof(struct s_transactionDeque)) ;
    t->sentinel = malloc(sizeof(struct s_transaction)) ;
    t->sentinel->next = t->sentinel ;
    t->sentinel->prev = t->sentinel ;
    t->size = 0 ;
    return t ;
}

/****************************************************/



void set_hash_transaction(Transaction  transaction) {
    char *str = strcat("",transaction->srcDest) ;
    sha256ofString(str, transaction->hash) ;
}


void add_transaction_to_transactionDeque(TransactionDeque t){
    Transaction new = malloc(sizeof(struct s_transaction)) ;
    new->index = t->size ;
    new->srcDest = create_transaction ;
    set_hash_transaction(new);
    new->next = t->sentinel ;
    new->prev = t->sentinel->prev ;
    t->sentinel->prev->next = new ;
    t->sentinel->prev = new ;
    t->size++ ;
}


void remove_transaction(TransactionDeque t, int index) { 
    Transaction *itr = t->sentinel->next ;
    while (--index) {
        itr = itr->next ;
    }
    itr->prev->next = itr->next ;
    itr->next->prev = itr->prev ;
    free(itr) ;
}


void delete_transaction_deque(TransactionDeque t){
    while (t->size)
        remove_transaction(t,0) ;
    free(t) ;
}


int get_index(Transaction transaction) {
    return transaction->index ;
}


