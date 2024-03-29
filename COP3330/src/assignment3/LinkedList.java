package assignment3;

/**
 * LinkedList
 */
public class LinkedList {

	private Node head;
	private Node tail;

	public LinkedList() {
		this.head = null;
	}

	public Node insert(Node node) {
		if (isEmpty()) {
			setHead(node);
			setTail(node);
		} else {
			this.tail.setNext(node);
			setTail(node);
		}
		return head;
	}

	// removes a node from the linked list. Note that the search depends on
	// the node's reference, avoiding the deletion of other nodes with the same
	// value
	public void remove(Node node) {
		// can't remove the node if the list is empty
		if (isEmpty()) {
			return;
		}

		Node currentNode = getHead();
		Node prevNode = null;

		while (currentNode != null) {
			// node found
			if (currentNode == node) {
				// if the node is the head, next node becomes the head
				if (prevNode == null) {
					setHead(currentNode.getNext());
				}
				// othewise the previous node's next becomes the current node's next
				else {
					prevNode.setNext(currentNode.getNext());
				}
				break;
			}

			// node not found, move to the next node
			prevNode = currentNode;
			currentNode = currentNode.getNext();
		}
	}

	public void setHead(Node node) {
		this.head = node;
	}

	public Node getHead() {
		return this.head;
	}

	public void setTail(Node node) {
		this.tail = node;
	}

	public Node getTail() {
		return this.tail;
	}

	public boolean isEmpty() {
		return this.head == null;
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		Node currentNode = getHead();
		while (currentNode != null) {
			sb.append(currentNode.getValue());
			currentNode = currentNode.getNext();
			if (currentNode != null) {
				sb.append(" ");
			}
		}
		return sb.toString();
	}
}
