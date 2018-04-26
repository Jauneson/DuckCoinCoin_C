#include "blockchain.h"


int main(int argc, char const *argv[]) {
	printf("Création Blockchain :\n");
	Blockchain blockchain = create_blockchain() ;
	printf("Done.\n");
	printf("Valeur de vérif : %d\n", verification_1(blockchain));
	return 0 ;
}