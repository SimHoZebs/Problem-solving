/*
 * Ho Sim
 * COP 3330
 * Dr. Bacanli
 * Assignment 2
 */
package assignment2;

public class Die {
  private int faceValue;

  public Die() {
    faceValue = 1;
  }

  public int getFaceValue() {
    return faceValue;
  }

  public void setFaceValue(int value) {
    faceValue = value;
  }

  public void roll() {
    setFaceValue((int) (Math.random() * 6) + 1);
  }

}
