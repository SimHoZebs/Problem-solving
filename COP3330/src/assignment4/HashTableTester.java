package assignment4;

import java.util.Scanner;

/**
 * HashTableTester
 * You will take the name of the data file as a command line parameter. You will
 * create a myHashTable object and do the actions stated in the file. Then you
 * will print the resulting myHashTable.
 *
 * Example data file
 * 
 * 7
 * add 12:Test
 * add 22:Test1
 * add 26:Test5
 * add 97:Test2
 * add 19:Test3
 * add 22:Test4
 * remove 9
 */
public class HashTableTester {

    public static void main(String[] args) {
        MyHashTable myHashTable = new MyHashTable();
        String fileName = args[0];
        Scanner scanner = new Scanner(fileName);
        int size = scanner.nextInt();
        for (int i = 0; i < size; i++) {
            String action = scanner.next();
            int number = scanner.nextInt();
            String value = scanner.next();
            Record record = new Record(number, value);
            if (action.equals("add")) {
                myHashTable.add(record);
            } else if (action.equals("remove")) {
                myHashTable.remove(number);
            }
        }
        scanner.close();
    }

}
