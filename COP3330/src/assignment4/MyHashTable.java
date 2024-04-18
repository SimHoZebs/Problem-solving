package assignment4;

/**
 * MyHashTable
 */
public class MyHashTable {

    private ArrayListAlt[] table;
    private int size;

    public MyHashTable(int size) {
        this.size = size;
        this.table = new ArrayListAlt[size];
        for (int i = 0; i < size; i++) {
            table[i] = new ArrayListAlt();
        }
    }

    public MyHashTable() {
        this(11);
    }

    private int hashFunc(int position) {
        return position % size;
    }

    /**
     * add the Record object to the hash table appropriately. Note that the instance
     * variable array contains ArrayListAlt objects.
     */
    public void add(Record r) {
        int index = hashFunc(r.getNumber());
        table[index].add(r);
    }

    public void remove(int num) {
        int index = hashFunc(num);
        table[index].remove(num);
    }

    /*
     * Retrieves a record from the hash table based on the provided number. If no
     * such element, the method will return null.
     */
    public String get(int num) {
        int index = hashFunc(num);
        return table[index].get(num);
    }
}
