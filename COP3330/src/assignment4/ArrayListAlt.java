package assignment4;

import java.util.ArrayList;

/**
 * an alternative Arraylist. That arraylist will store Records in sorted manner
 * (ascending) according to the number in the record object. It will have an
 * ArrayList object as instance variable which will hold Records.
 */
public class ArrayListAlt {
    private ArrayList<Record> records;

    public ArrayListAlt() {
        this.records = new ArrayList<Record>();
    }

    /**
     * Adds a Record object to the sorted ArrayListAlt. You need to be adding the
     * new record to appropriate place in the arraylist as the arraylist will store
     * the elements sorted in ascending manner. If a record with the same number
     * exists in the ArrayList, change the value of that record using value of r
     * parameter. Hint: Use find() method to find the position of the element
     */
    void add(Record r) {
        int index = find(r.getNumber());
        if (index != -1) {
            records.set(index, r);
        } else {
            int i = 0;
            while (i < records.size() && records.get(i).getNumber() < r.getNumber()) {
                i++;
            }
            records.add(i, r);
        }
    }

    /**
     * Removes a record from the ArrayListAlt whose number matches with the
     * given num. If no such element exists, it will return false and throw
     * exception with message "No such element". Hint: Use find() method to find the
     * position of the element
     */
    boolean remove(int num) {
        int index = find(num);
        if (index != -1) {
            records.remove(index);
            return true;
        } else {
            throw new IllegalArgumentException("No such element");
        }
    }

    public String toString() {
        return records.toString();
    }

    /**
     * returns the value of a record ( as String) from the ArrayListAlt based on the
     * provided number. It will return null if no such element exists. Hint: Use
     * find() method to find the position of the element
     */
    public String get(int number) {
        int index = find(number);
        if (index != -1) {
            return records.get(index).getValue();
        }
        return null;
    }

    /**
     * finds the position of a record in the ArrayListAlt based on the provided
     * number. Use binary search to search the element. That method will be private.
     * If the record does not exist, this method should return -1.
     */
    private int find(int number) {
        int left = 0;
        int right = records.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (records.get(mid).getNumber() == number) {
                return mid;
            } else if (records.get(mid).getNumber() < number) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
}
