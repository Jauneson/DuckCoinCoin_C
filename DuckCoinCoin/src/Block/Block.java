package Block;
import java.sql.Timestamp;
import java.util.LinkedList;

import Transaction.*;


public class Block {

	private int index;
	private Timestamp timestamp;
	private String hashPrev;
	private int nbTransactions; 
	private LinkedList<Transaction> transactions;
	private String hashTreeRoot;
	private String hashBlock;
	private int nonce;

	public Block(int index,LinkedList<Transaction> transactions, String hashPrev) {
		super();
		this.index = index;
		this.timestamp = new Timestamp(System.currentTimeMillis());
		this.hashPrev = hashPrev;
		this.nbTransactions = transactions.size();
		this.transactions = transactions;
		this.hashTreeRoot = "Calcul du Hash de 'transactions' ";
		this.hashBlock = "Calcul du Hash du Block";
		this.nonce = 0;
	}

	/**
	 * @return the timestamp
	 */
	public Timestamp getTimestamp() {
		return timestamp;
	}

	/**
	 * @return the transactions
	 */
	public LinkedList<Transaction> getTransactions() {
		return transactions;
	}

	/**
	 * @return the hashBlock
	 */
	public String getHashBlock() {
		return hashBlock;
	}	
	
	//public void minage(){}
	
	public void calcul_hash_block(){
		hashBlock=" Resultat de la fonction de calcul";
	}
	
	public String toString(){
		return index+" "+nbTransactions+" "+timestamp;
	}
}
