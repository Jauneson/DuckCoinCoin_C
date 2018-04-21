package Block;
import java.util.LinkedList;

public class BlockChain {
	private int difficulty ;
	private LinkedList<Block> blocks ;
	
	public BlockChain() {
		this.blocks=new LinkedList<Block>();
		this.difficulty=0;
	}
	
	// Check if an index is between 0 and blockchain's size
	private void verif_index(int index){
		if ( (index<0) || (index>this.blocks.size()) ){
			throw new IllegalArgumentException("No block corresponding to this index");
		}
	}
	
	public void init_genesis(){
		Block b=new Block(0, null, null);
		blocks.addLast(b);
	}
	
	public Boolean empty(){
		return blocks.isEmpty();
	}
	
	public void push_block(Block b){
		blocks.addLast(b);
	}
	
	public void remove_block_at(int index){
		verif_index(index);
		blocks.remove(index);
	}
	
	public Block get_Block(int index){
		verif_index(index);
		return blocks.get(index);
	}
	
	public void rebuild_blockchain(int indexBlock){
		Block b;
		for(;indexBlock<this.blocks.size();indexBlock++){
			b=this.get_Block(indexBlock);
			b.calcul_hash_block();
		}
	}
	
	public void all_blocks_string(){
		for (Block l:this.blocks){
			System.out.println(l.toString());
		}
	}
}
