#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include <sha256.h>
#include <sha256_utils.h>


typedef struct s_block *{
	int index ;
	char *timeStamp ;
	char *hashPrev ;
	int nbTransactions ;
	TransactionTree transactions ; // Supposé TransactionTree pour l'instant
	char *hashTreeRoot ;
	char *hashCour ;
	int nonce ;
	struct s_block *prev ;
	struct s_block *next ;
}Block ;

Block create_block(TransactionTree transactionTree,int idBlock, char *hash){
		
	/* Décision du tribunal en attente : on est censé avor la liste de transactions 
	On prend la liste en paramètre, et on calcule l'arbre ici, ou on donne l'arbre et on 
	se débrouille pour récupérer la liste des transaction ? Ou la liste sera faite en arbre et 
	pas en queue ? ... Opinion personnel : On donne la queue (listeTransactions), et pas un 
	transactionTree, le sujet me semble plus tendre vers cette solution. 
	Dans ce cas ==> Transformation de notre TAD transactionTree en transactionList et ajout de 
	la méthode qui en fait un Arbre ? Puis modification des lignes de codes qui le nécessitent.
	*/

	// Initialiser les valeurs du block
	Block block ;
	block->index = idBlock ;
	block->timeStamp = getTimeStamp() ;	
	block->hashPrev = hash ;
	block->transactions = transactionList ;
	block->nbTransaction = get_nb_total_transaction(liste) ;
	block->hashTreeRoot = hash_Merkle_tree(transactions) ;
	block->prev = NULL ;
	block->next = NULL ;
	block->nonce = 0 ;
	block->hashCour = malloc ( (SHA256_BLOCK_SIZE*2+1)*sizeof(char) ) ; // SHA256_BLOCK_SIZE est déclaré dans sha256.h


	// Fonction minage début
	// Calculer le hashCour
	// Le contenu du block mis dans une chaine de caractère pour utiliser la fonction de hashage
	BYTE * tempLine = /* Transformer le contenu du block en BYTE  Je vois pas comment faire	*/ ; // BYTE Défini dans sha256.h

	// Void qui prend le premier char * en parametre et renvoit le hash dans le second char * en parametre 
	sha256ofString(tempLine,block->hashCour); 

	// Modifier les valeurs de la nonce et du hashCour jusqu'a respect des critères de sécurité (4*0 au début du hash)
	while !( ((block->hashCour[0])==0) && ((block->hashCour[1])==0) && 
			((block->hashCour[2])==0) && ((block->hashCour[4])==0) ) {
		tempLine = /* Fonction qui transforme le block en BYTE */ ;
		sha256ofString(tempLine,block->hashCour) ; 
		++(block->nonce) ;
	}

	// Fonction minage Fin ;


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
	return (block->size == 0);
}

char *get_hash(Block block){
	assert(!block_empty(block));
	return block->hashCour;
}

time_t get_timeStamp(Block block){
	assert(!block_empty(block));
	return block->timeStamp;
}

transactionTree get_transaction(Block block){
	assert(!block_empty(block));
	return block->transactions;
}

/*     problème d'uniformité du type transactionTree?		*/ 
