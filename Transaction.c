/*
j’ai créé la structure pour faire une liste avec sentinelle comme c’est demandé, Je ne rien changé, j’ai seulement ajouté la structure et quelque fonction. Pour la version 1 j’ai fait une seule fonction qui renvoi une chaîne de caractères et pour la version 2 j’ai fait de fonctions qui réalisent des opérations sur les listes.
Par contre je n’ai rien changé dans le .h parce que je ne suis pas en vie ;)
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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
    struct s_transaction *next ;
    struct s_transaction *prev ;
    int index ;
    char srcDest[512] ;
    char hash[SHA256_BLOCK_SIZE*2 + 1] ; // calcul et stockage du hash directement à l'ajout d'une transaction dans la deque
}*Transaction;

struct s_transactionDeque {
    struct s_transaction *sentinel ;
    int size ;
};

/****************************************************/


void create_transaction(char trans[512]) {
    sprintf(trans,"Source-Destination : %d",rand()%MAX_VALUE) ;
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
    sha256ofString(transaction->srcDest, transaction->hash) ;
}


void add_transaction_to_transactionDeque(TransactionDeque t){
    Transaction new = malloc(sizeof(struct s_transaction)) ;
    new->index = t->size ;
    create_transaction(new->srcDest) ;
    set_hash_transaction(new);
    new->next = t->sentinel ;
    new->prev = t->sentinel->prev ;
    t->sentinel->prev->next = new ;
    t->sentinel->prev = new ;
    t->size++ ;
}


void remove_transaction(TransactionDeque t, int index) { 
    Transaction itr = t->sentinel->next ;
    while (index--) {
        itr = itr->next ;
    }
    itr->prev->next = itr->next ;
    itr->next->prev = itr->prev ;
    free(itr) ;
    --(t->size) ;
}


void delete_transaction_deque(TransactionDeque t){
   while(t->size!=0){
    remove_transaction(t,0) ;
   }
   free(t->sentinel) ;
   free(t) ;
   t=NULL ;
}


int get_index(Transaction transaction) {
    return transaction->index ;
}


int main(int argc,char *argv[]) {
    srand(time(NULL)) ;
    TransactionDeque t = init_transaction_deque() ;
    for (int i=0; i<5;i++) 
        add_transaction_to_transactionDeque(t) ;
    for(Transaction itr = t->sentinel->next;itr != t->sentinel;itr=itr->next){
        printf(" Transaction: %s\n Index: %d\n Hash: %s\n",itr->srcDest,get_index(itr),itr->hash) ;
    }
    delete_transaction_deque(t) ;
    return 0 ;
}