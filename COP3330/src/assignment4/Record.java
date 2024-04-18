package assignment4;

public class Record {

    private int number;
    private String value;

    /* a no argument constructor as you like */
    public Record() {
        this(0, "default 0th value");
    }

    /* a constructor which will take number and value as parameters */
    public Record(int number, String value) {
        this.number = number;
        this.value = value;
    }

    public int getNumber() {
        return this.number;
    }

    public String getValue() {
        return this.value;
    }

    public String toString() {
        return this.number + ":" + this.value;
    }
}
