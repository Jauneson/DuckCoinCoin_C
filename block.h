#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <stdbool.h>
#include "transactionTree.h"

/**
 * @brief description of a block
 */
typedef struct s_block *Block ;
/**
 * @brief initialize a block 
 * 
 * @param transactionTree that must be stored in this block
 * @param idBlock the number to identify the position of the block 
 * @param hash of the previous block in the blockchain
 * @return block (type s_block *)
 */
Block create_block(TransactionTree transactionTree,int idBlock, char *hash) ;
/**
 * @return the current hash of a block
 * 
 * @param block [description]
 * @return hash (type char *)
 */
bool block_empty(Block block);

char *get_hash(Block block) ;
/**
 * @return timestamp of a block
 * 
 * @param block [description]
 * @return timestamp (type time_t)
 */
time_t get_timeStamp(Block block) ;
/**
 * @return transactionTree of a block
 * 
 * @param block [description]
 * @return transaction Tree (type transationTree)
 */
transactionTree get_transaction(Block block) ;
#endif
