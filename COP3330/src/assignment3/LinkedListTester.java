/*
 * Ho Sim
 * COP 3330
 * Dr. Bacanli
 * Assignment 3
 */
package assignment3;

import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

/**
 * LinkedListTester
 */
public class LinkedListTester {
	public static void main(String[] args) {
		// find the file and get a reader from it.
		Scanner reader = getReader();
		if (reader == null) {
			return;
		}

		// finally start adding the numbers into a linked list
		LinkedList list = createLinkedList(reader);
		reader.close();
		// System.out.println("initial list:\n" + list);

		// traverse the linked list, starting from the first node
		Node currentNode = list.getHead();
		Node prevNode = null;
		// replacement value
		int count = -100;
		while (currentNode != null) {
			Node nextNode = currentNode.getNext();
			// if this is the last node, stop the loop
			if (nextNode == null) {
				break;
			}

			// shrink condition
			if (shouldShrink(currentNode, nextNode)) {
				// System.out.println("Shrinking");
				// keep track of current head and tail for later
				Node head = list.getHead();
				Node tail = list.getTail();

				// shrink
				list.remove(currentNode);
				list.remove(nextNode);

				Node replacementNode = new Node(count);
				count++;

				// if head changed, head node was deleted.
				// replacement node should be the head
				if (head != list.getHead()) {
					replacementNode.setNext(list.getHead());
					list.setHead(replacementNode);
				}
				// if tail changed, tail node was deleted.
				// replacement node just needs to be inserted
				else if (tail != list.getTail()) {
					list.insert(replacementNode);
				}
				// othewise, insert replacementNode in front of
				// prevNode
				else {
					replacementNode.setNext(prevNode.getNext());
					prevNode.setNext(replacementNode);
				}
				currentNode = replacementNode;
			} else {

				// traverse
				prevNode = currentNode;
				currentNode = currentNode.getNext();
			}

		}

		// add the last cound as a node
		Node lastNode = new Node(count);
		list.insert(lastNode);

		writeListToFile(list);
	}

	// get a readable Scanner from a file. Error out if the file is not found or
	// unreadable
	private static Scanner getReader() {
		// checking if the file exists
		File data = null;
		try {
			data = new File("./data.txt");
		} catch (Exception e) {
			System.out.println("File not found");
			return null;
		}

		// checking if the file is readable by Scanner
		Scanner reader = null;
		if (data.exists() && data.canRead()) {
			try {
				reader = new Scanner(data);
			} catch (Exception e) {
				System.out.println("Error reading file");
				reader.close();
				return null;
			}
		} else {
			System.out.println("File unreadable");
			return null;
		}
		return reader;
	}

	// write the linked list to processed.txt. Error out if the file is not created
	// or writing fails for some reason.
	private static void writeListToFile(LinkedList list) {
		// create a new file to write to
		File output = new File("./processed.txt");
		try {
			output.createNewFile();
		} catch (Exception e) {
			System.out.println("Error creating output file");
			return;
		}

		// if the file was created, write the list to it
		try {
			FileWriter writer = new FileWriter(output);
			writer.write(list.toString());
			writer.close();
		} catch (Exception e) {
			System.out.println("Error writing to file");
			return;
		}
	}

	// create a linked list from the reader
	private static LinkedList createLinkedList(Scanner reader) {
		LinkedList list = new LinkedList();
		while (reader.hasNextInt()) {
			int item = reader.nextInt();
			if (item > -1) {
				Node node = new Node(item);
				list.insert(node);
			}
		}

		return list;

	}

	private static boolean shouldShrink(Node currentNode, Node nextNode) {
		// System.out.println(currentNode.getValue() + " * 2 + 7 = " +
		// (currentNode.getValue() * 2 + 7));
		// System.out.println("nextNode value is " + nextNode.getValue());
		return currentNode.getValue() * 2 + 7 == nextNode.getValue();
	}

}
