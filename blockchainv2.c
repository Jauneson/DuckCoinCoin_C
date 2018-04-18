#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

#include "blockChain.h"

#define NB_MAX_TRANSACTIONS 10 


struct s_blockchain {
	int difficulty  ;
	int nbBlocks ;
	Block sentinel ;
};

/*----------------------------------------------------------------*/

Blockchain create_blockchain() {
	Blockchain blockchain = malloc(sizeof(struct s_blockchain)) ;
	blockchain->sentinel = create_block(NULL,-1,NULL) ;
	blockchain->sentinel->next = blockchain->sentinel ;
	blockchain->sentinel->prev = blockchain->sentinel ;
	blockchain->nbBlocks = 0 ;
	return blockchain ;
}

/*----------------------------------------------------------------*/

void init_genesis(Blockchain blockchain) {
	Block b = create_block(NULL,0,NULL) ; // A revoir quand hash et block dispo
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
		set_hash_block(b,HashBlock(b)) ; 			// Fonction de block qui permet d'enregistrer un nouveau hash 	
	}
}

/*----------------------------------------------------------------*/
	

void delete_Blockchain (Blockchain blockchain){
	while (blockchain->nbBlocks != 0){
		remove_block(blockchain,0);				//remove le premier element de la blockchain
	}
	free(blockchain);							//free la blockchain
}


/*-----------------------------------------------------------------*/


//---------TESTS----------

/*int main(void) {
	srand(time(NULL)) ;
    TransactionDeque t = init_transaction_deque() ;
    for (int i=0; i<5;i++) 
        add_transaction_to_transactionDeque(t) ;
    Block b = create_block(t,0,"") ;
    display_info_block(b) ;
    remove_block(b) ;
    delete_transaction_deque(t) ;
	return 0 ;
}
*/