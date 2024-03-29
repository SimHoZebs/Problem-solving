package assignment3;

/**
 * Node
 */
public class Node {

	private int value;
	private Node next;

	public Node(int item) {
		this.value = item;
		this.next = null;
	}

	public void setNext(Node next) {
		this.next = next;
	}

	public Node getNext() {
		return this.next;
	}

	public int getValue() {
		return this.value;
	}
}
