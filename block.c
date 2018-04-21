#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<stdbool.h>

#include "block.h"

void calcul_hash_block(Block block) {
	return ;
}

Block create_block(TransactionDeque transactions,int idBlock, char hashPrev[SHA256_BLOCK_SIZE*2 + 1]){
		
	/* Décision du tribunal en attente : on est censé avor la liste de transactions 
	On prend la liste en paramètre, et on calcule l'arbre ici, ou on donne l'arbre et on 
	se débrouille pour récupérer la liste des transaction ? Ou la liste sera faite en arbre et 
	pas en queue ? ... Opinion personnel : On donne la queue (listeTransactions), et pas un 
	transactionTree, le sujet me semble plus tendre vers cette solution. 
	Dans ce cas ==> Transformation de notre TAD transactionTree en transactionList et ajout de 
	la méthode qui en fait un Arbre ? Puis modification des lignes de codes qui le nécessitent.
	*/

	// Initialiser les valeurs du block
	Block block = malloc(sizeof(struct s_block)) ;
	block->index = idBlock ;
	block->timeStamp = getTimeStamp() ;	
	sprintf(block->hashPrev,"%s",hashPrev) ; //<-- block->hashPrev = hash ;
	block->transactions = transactions ;
	//block->nbTransaction = get_nb_total_transactions(transactions) ;
	hash_Merkle_tree(transactions,block->hashTreeRoot) ;
	block->nonce = 0 ;
	calcul_hash_block(block) ;
	//allué dans la strcucture block->hashCour = malloc ( (SHA256_BLOCK_SIZE*2+1)*sizeof(char) ) ; // SHA256_BLOCK_SIZE est déclaré dans sha256.h

	/*
	// Fonction minage début
	// Calculer le hashCour
	// Le contenu du block mis dans une chaine de caractère pour utiliser la fonction de hashage
	//BYTE * tempLine =  Transformer le contenu du block en BYTE  Je vois pas comment faire	 ; // BYTE Défini dans sha256.h

	// Void qui prend le premier char * en parametre et renvoit le hash dans le second char * en parametre 
	sha256ofString(tempLine,block->hashCour); 

	// Modifier les valeurs de la nonce et du hashCour jusqu'a respect des critères de sécurité (4*0 au début du hash)
	while !( ((block->hashCour[0])==0) && ((block->hashCour[1])==0) && 
			((block->hashCour[2])==0) && ((block->hashCour[4])==0) ) {
		tempLine = // Fonction qui transforme le block en BYTE  ;
		sha256ofString(tempLine,block->hashCour) ; 
		++(block->nonce) ;
	}

	// Fonction minage Fin ;
	*/

	return block ;
	
}



/*

On peut créer une fonction "Minage" et qu'on peut appliquer dans le create et dans set_HashPrev qui fait :
void minage(Block block){ 
	BYTE * tempLine ;
	block->nonce = 0 ;
	tempLine =  ; // Fonction qui transforme le block en BYTE 
	sha256ofString(tempLine,block->hashCour) ; 
	while !( ((block->hashCour[0])==0) && ((block->hashCour[1])==0) && 
			((block->hashCour[2])==0) && ((block->hashCour[4])==0) ) {

		tempLine =  ; // Fonction qui transforme le block en BYTE 
		sha256ofString(tempLine,block->hashCour) ; 
		++(block->nonce) ;
	}
}

// Celui ci sert a changer le hashPrev du précédent block (s'il disparait de la chaine par exemple)
// Ensuite il recalcule le hashCour via le void minage
void set_hashPrev(Block block, char * newHashPrev){
	assert(!empty(block)) ;	
	block->hashPrev = newHashPrev ;
	minage(block) ;
}
*/
bool block_empty(Block block){
	return (block->index == 0);
}

char *get_hash(Block block){
	assert(!block_empty(block));
	return block->hashCour;
}

char *get_timeStamp(Block block){
	assert(!block_empty(block));
	return block->timeStamp;
}

TransactionDeque get_transaction(Block block){
	assert(!block_empty(block));
	return block->transactions;
}

/*     problème d'uniformité du type transactionTree?		*/ 

void remove_block(Block block) {
	free(block);
	block = NULL ;
}

/*void display_info_block(Block block) {
	printf("Block info\n index: %d\n Transactions:\n",block->index) ;
	display_info(block->transactions) ;
	printf("timeStamp: %s\n hash precedent: %s\n",block->timeStamp,block->hashPrev);
	printf("nombre de transactions: %d\n hash transactions: %s\n",block->nbTransaction,block->hashTreeRoot);
	printf("nonce: %d\n hash du block: %s\n",block->nonce,block->hashCour) ;
}


int main(void) {
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