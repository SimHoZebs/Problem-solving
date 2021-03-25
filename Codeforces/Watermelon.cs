using System;

public class Watermelon{

    public static void Core(){
        var weight = Convert.ToDouble(Console.ReadLine());

        if (weight == 2 || weight % 2 != 0){
            Console.WriteLine("NO");
        }
        else if ((weight - 2) % 2 == 0){
            Console.WriteLine("YES");
        }
    }

}