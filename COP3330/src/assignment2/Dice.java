package assignment2;

public class Dice {
  private Die die1;
  private Die die2;

  public Dice() {
    die1 = new Die();
    die2 = new Die();
  }

  public int getFaceValue() {
    return die1.getFaceValue() + die2.getFaceValue();
  }

  public void roll() {
    die1.roll();
    die2.roll();
  }

}