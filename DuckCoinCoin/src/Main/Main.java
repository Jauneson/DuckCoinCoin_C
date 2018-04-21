package Main;
import Block.*;
import Transaction.*;
import java.util.*;

public class Main {

	public static void main(String[] args) {
		LinkedList<Transaction> L = new LinkedList<Transaction>();
		Block b = new Block(0, L, null);
		// Temporisation juste présente pour vérifier que les timestamp différents fonctionnent.
		try { 
			Thread.sleep(100);
		}
		catch (InterruptedException exception) {
			exception.printStackTrace();
		}
		Block b1 = new Block(0, L, null);
		BlockChain B = new BlockChain();
		B.push_block(b);
		B.push_block(b1);
		B.push_block(b);
		B.all_blocks_string();
	}

}
