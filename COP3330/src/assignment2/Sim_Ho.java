package assignment2;

public class Sim_Ho {
  public static void main(String[] args) {
    Dice dice = new Dice();

    // store roll count
    final int COUNT_SIZE = 11;
    int[] count = new int[COUNT_SIZE];

    // index 0 is 0, index 1 is 25, index 2 is 50, etc.

    for (int i = 0; i < 1000; i++) {
      dice.roll();
      count[dice.getFaceValue() - 2]++;
    }

    for (int i = 0; i < COUNT_SIZE; i++) {
      System.out.println("Number of " + (i + 2) + "s are " + count[i]);
    }

    System.out.println("Graph");

    final int HISTOGRAM_MAX = 7;
    final int HISTOGRAM_STEP = 25;
    for (int i = HISTOGRAM_MAX - 1; i >= 0; i--) {
      StringBuilder line = new StringBuilder();

      int y = i * HISTOGRAM_STEP;

      if (y % 100 < y) {
      } else if (y % 10 < y) {
        line.append(" ");
      } else {
        line.append("  ");
      }

      line.append((i * HISTOGRAM_STEP) + "|");

      for (int j = 0; j < COUNT_SIZE; j++) {
        if (count[j] >= i * HISTOGRAM_STEP) {
          line.append("*  ");
        } else {
          line.append("   ");
        }
      }

      System.out.println(line);
    }

    StringBuilder xAxisBorder = new StringBuilder();
    xAxisBorder.append("    ");
    for (int i = 0; i < COUNT_SIZE; i++) {
      xAxisBorder.append("---");
    }
    // remove last
    xAxisBorder.deleteCharAt(COUNT_SIZE * 3);

    System.out.println(xAxisBorder);

    StringBuilder xAxis = new StringBuilder();
    xAxis.append("    ");
    for (int i = 0; i < COUNT_SIZE; i++) {
      xAxis.append((i + 2));
      if ((i + 2) < 9) {
        xAxis.append(" ");
      }
      xAxis.append(" ");
    }

    System.out.println(xAxis);

  }
}