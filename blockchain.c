#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

#include "blockchain.h"

#define NB_MAX_TRANSACTIONS 10 


struct s_blockchain {
	int difficulty  ;
	int nbBlocks ;
	Block sentinel ;
};

/*----------------------------------------------------------------*/

Blockchain create_blockchain() {
	Blockchain blockchain = malloc(sizeof(struct s_blockchain)) ;
	blockchain->sentinel = malloc(sizeof(struct s_block)) ;
	blockchain->sentinel->next = blockchain->sentinel ;
	blockchain->sentinel->prev = blockchain->sentinel ;
	blockchain->nbBlocks = 0 ;
	return blockchain ;
}

/*----------------------------------------------------------------*/

void init_genesis(Blockchain blockchain) {
	Block b = malloc(sizeof(struct s_block)) ;
	b->next = blockchain->sentinel ;
	b->prev = blockchain->sentinel ;
	blockchain->sentinel->next = b ;
	blockchain->sentinel->prev = b ;
	(blockchain->nbBlocks)++ ;
}

/*----------------------------------------------------------------*/

void push_block(Blockchain blockchain,Block block) {
	block->next = blockchain->sentinel ;
	block->prev = blockchain->sentinel->prev ;
	blockchain->sentinel->prev->next = block ;
	blockchain->sentinel->prev = block ;
	(blockchain->nbBlocks)++ ;
}

/*----------------------------------------------------------------*/

void remove_block_from_blockchain(Blockchain blockchain,int indexBlock) {
	assert((indexBlock >= 0) && (blockchain->nbBlocks > indexBlock)) ;
	Block block = blockchain->sentinel->next ;
	while (indexBlock-- != 0){
		block = block->next ;
	}											//on trouve block à suppr
	block->next->prev = block->prev ;				
	block->prev->next = block->next ;			//on décale
	free(block) ;								//on le free
	--(blockchain->nbBlocks) ;
}

/*----------------------------------------------------------------*/

bool empty(Blockchain blockchain) {
	return (blockchain->nbBlocks == 0) ;
}

/*----------------------------------------------------------------*/

Block get_block(Blockchain blockchain, int indexBlock) {
	assert(0<=indexBlock && indexBlock<Blockchain->nbBlocks) ;
	Block itr = blockchain->sentinel->next ;
	for(; indexBlock>0; indexBlock--, itr=itr->next) ;
	return itr ;
}

/*----------------------------------------------------------------*/

void rebuild_Blockchain(Blockchain blockchain, int indexBlock) {
	Block b ;
	for(; indexBlock<blockchain->nbBlocks; indexBlock++){
		b=get_block(blockchain,indexBlock) ; 				// Récupère le block courant
		// HashBlock : fonction existante qui calcule le hash
		// set_hash_block(Block 1, Hash 2) : modifie le hash du block 1, par le hash 2
		calcul_hash_block(b) ; 			// Fonction de block qui permet d'enregistrer un nouveau hash 	
	}
}

/*----------------------------------------------------------------*/
	

void delete_Blockchain (Blockchain blockchain){
	while (blockchain->nbBlocks != 0){
		remove_block_from_blockchain(blockchain,0);				//remove le premier element de la blockchain
	}
	free(blockchain);							//free la blockchain
}


/*-----------------------------------------------------------------*/


//---------TESTS----------

int main(void) {
	srand(time(NULL)) ;
	printf("Création TransactionDeque :\n");
    TransactionDeque t = init_transaction_deque() ;
    for (int i=0; i<5;i++) {
    	printf("Ajout de Transaction :\n");
        add_transaction_to_transactionDeque(t) ;
    }
    printf("Création blockchain : \n");
    Blockchain bc = create_blockchain() ;
    printf("Initialisation du genesis : \n");
    init_genesis(bc) ;
    for (int i = 1; i<3 ; i++) {
    	printf("Ajout de block :\n");
    	push_block(bc,create_block(t,i,get_block(bc,bc->nbBlocks)->hashCour)) ; // ajout d'un block à la bc
    }
    printf("Suppression blockchain :\n");
    delete_Blockchain(bc) ;
    printf("Done.\n");
	return 0 ;
}
