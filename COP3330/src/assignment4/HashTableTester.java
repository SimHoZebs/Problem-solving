package assignment4;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

/**
 * HashTableTester
 */
public class HashTableTester {

    public static void main(String[] args) {
        System.out.println("Hello, World!");
        List<String> lines = null;
        try {
            lines = Files.readAllLines(Paths.get(args[0]));
        } catch (Exception e) {
            e.printStackTrace();
        }

        int hashSize = Integer.parseInt(lines.get(0));
        MyHashTable hashTable = new MyHashTable(hashSize);

        for (String line : lines) {

            String[] parts = line.split(" ");
            if (parts[0].equals("add")) {
                String[] recordParts = parts[1].split(":");
                Record record = new Record(Integer.parseInt(recordParts[0]), recordParts[1]);
                hashTable.add(record);
            } else if (parts[0].equals("remove")) {
                try {
                    hashTable.remove(Integer.parseInt(parts[1]));
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                }
            }
        }

        System.out.println(hashTable.toString());
    }

}
