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
	Block b = create_block(transaction_genesis(),0,0) ;
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
	while (indexBlock--)
		block = block->next ;	//on trouve block à suppr
	block->next->prev = block->prev ;				
	block->prev->next = block->next ;
	remove_block(block) ;								//on le free
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
	Block itr = blockchain->sentinel->next ;
	while (indexBlock--) 
		itr = itr->next ;
	Block cur = itr->next ; // pointeur sur le blcok dont on va recalculer le hash
	itr->next->prev = itr->prev ; // suppression du block itr
	itr->prev->next = itr->next ;
	remove_block(itr) ;
	blockchain->nbBlocks-- ;

	strcat(cur->hashPrev,get_hash(cur->prev)) ; // on récupère le hash du previous
	while (cur->next != blockchain->sentinel) {
		minage(cur,blockchain->difficulty) ;
		cur = cur->next ;
	}


	/* ANCIENNE VERSION 
	Block b ;
	for(; indexBlock<blockchain->nbBlocks; indexBlock++){
		b=get_block(blockchain,indexBlock) ; 				// Récupère le block courant
		// HashBlock : fonction existante qui calcule le hash
		// set_hash_block(Block 1, Hash 2) : modifie le hash du block 1, par le hash 2
		calcul_hash_block(b) ; 			// Fonction de block qui permet d'enregistrer un nouveau hash 	
	} */
}

/*----------------------------------------------------------------*/
	

void delete_Blockchain (Blockchain blockchain){
	while (blockchain->nbBlocks){
		remove_block_from_blockchain(blockchain,0) ; //remove le premier element de la blockchain
	}
	free(blockchain->sentinel) ;
	free(blockchain) ;							//free la blockchain
}


/*-----------------------------------------------------------------*/


//---------TESTS----------

void display_info_block(Block block) {
	printf("Block info\n index: %d\n Transactions:\n",block->index) ;
	printf("timeStamp: %s\n hash precedent: %s\n",block->timeStamp,block->hashPrev);
	printf("nombre de transactions: %d\n hash transactions: %s\n",block->nbTransaction,block->hashTreeRoot);
	printf("nonce: %d\n hash du block: %s\n",block->nonce,block->hashCour) ;
}


int main(void) {

	srand(time(NULL)) ;
	
	printf("Création TransactionDeque :\n");
    TransactionDeque t = init_transaction_deque() ;
    TransactionDeque t1 = init_transaction_deque() ;

    for (int i=0; i<5;i++) {
    	printf("Ajout de Transaction :\n");
        add_transaction_to_transactionDeque(t) ;
        add_transaction_to_transactionDeque(t1) ;
    }
    
    printf("Création blockchain : \n");
    Blockchain bc = create_blockchain() ;
   
    printf("Initialisation du genesis : \n");
    init_genesis(bc) ;

    printf("Ajout de block :\n");
   	push_block(bc,create_block(t,1,get_block(bc,bc->nbBlocks)->hashCour)) ; // ajout d'un block à la bc
   	push_block(bc,create_block(t1,2,get_block(bc,bc->nbBlocks)->hashCour)) ; // ajout d'un block à la bc
    
   	printf("Affichage des infos des block de la bc :\n") ;
   	for (int i = 0; i < bc->nbBlocks ; i++)
   		display_info_block(get_block(bc,i)) ;


    printf("Suppression blockchain :\n");
    delete_Blockchain(bc) ;
    printf("Done.\n");
	return 0 ;
}
