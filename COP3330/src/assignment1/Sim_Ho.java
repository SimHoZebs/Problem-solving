/*
 * Ho Sim
 * COP 3330
 * Dr. Bacanli
 * Assignment 1
 */
package assignment1;

import java.util.Random;
import java.util.Scanner;

public class Sim_Ho {
  private static final String[] MONTHS = { "Janurary", "Feburary", "March", "April", "May", "June", "July", "August",
      "September", "October", "November", "December" };

  public static void main(String[] args) {

    // random number generator
    Random rand = new Random();
    // receiptNumber: from 1000 to 1999
    int receiptNumber = rand.nextInt(1000) + 1000;
    // year: from 1900 to 2099
    int year = rand.nextInt(200) + 1900;
    // month: from 0 to 11
    int month = rand.nextInt(12);
    // day: from 1 to 28
    int day = rand.nextInt(28) + 1;

    // decorative outputs
    System.out.println("******************************");
    System.out.println("****** S store ***************");
    System.out.println("******************************");
    System.out.println("receipt number      " + receiptNumber);
    System.out.println(MONTHS[month] + " " + day + " " + year);

    Scanner scan = new Scanner(System.in);
    boolean isDone = false;
    int itemCount = 0;
    float totalCost = 0f;

    while (!isDone) {
      System.out.print("Write item name ");
      String itemName = scan.next();

      if (itemName.equals("DONE")) {
        // stop loop when item name is "DONE"
        scan.close();
        isDone = true;
      } else {
        // if not done, increase item count
        itemCount++;

        // capitalize first character
        itemName = itemName.substring(0, 1).toUpperCase() + itemName.substring(1);

        // scan price and store as float
        System.out.print("Write price ");
        float price = Float.parseFloat(scan.next());

        // convert itemName to lowercase and check if it equals to "food"
        if (!itemName.toLowerCase().equals("food")) {
          // if it is, add 30% tax
          price *= 1.3;
        }

        // confirmation output
        System.out.println("item number " + itemCount + " " + itemName + " " + price);

        totalCost += price;
      }
    }

    // final print
    System.out.println(itemCount + " items" + "      " + "total " + totalCost);

    // bottom decorative outputs
    for (int i = 0; i < 3; i++) {
      System.out.println("******************************");
    }

  }
}