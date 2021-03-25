using System;
using System.Collections.Generic;

public class BeforeAnExam{

    static int days, sumTime, studiedTime;
    static List<int[]> allTimeRangeList = new List<int[]>();
    public static void Core(){ // minTime < studyTime < maxTime per each i-th day

        daysAndSumTime(Console.ReadLine());
        for (int i = 0; i < days; i++){
            MakeAllTimeRangeList(Console.ReadLine());
        }

        var TimeSelectionList = MakeTimeSelectionList();
        var studiedTimeList = MakeStudiedTimeList(TimeSelectionList);

        studiedTime = AddIntsInList(studiedTimeList);
        VerifyStudiedTime(studiedTimeList, TimeSelectionList);

        if (sumTime == studiedTime){
            Console.WriteLine("YES");
            foreach(int time in studiedTimeList){
                Console.Write(time + " ");
            }
        }
        else{
            Console.WriteLine("NO");
        }
    }

    private static void daysAndSumTime(string input){
        
        string[] firstInputs = input.Split();
        days = Convert.ToInt32(firstInputs[0]);
        sumTime = Convert.ToInt32(firstInputs[1]);
    }

    private static void MakeAllTimeRangeList(string input){

        var tempArray = input.Split();
        int[] tempArrayInt = {Convert.ToInt32(tempArray[0]), Convert.ToInt32(tempArray[1])};
        allTimeRangeList.Add(tempArrayInt);
    }

    private static List<string> MakeTimeSelectionList(){
        var tempList = new List<string>();

        foreach (int[] timeRangeArray in allTimeRangeList){
            var maxTime = timeRangeArray[1];
            var minTime = timeRangeArray[0];
            var tempSumTime = sumTime;

            var diffWithMax = Math.Abs(tempSumTime - maxTime);
            var diffWithMin = Math.Abs(tempSumTime -  minTime);

            if (diffWithMin >= diffWithMax){
                tempSumTime -= minTime;
                tempList.Add("Max");
            }
            else{
                tempSumTime -= maxTime;
                tempList.Add("Min");
            }
        }
        return tempList;
    }


    private static List<int> MakeStudiedTimeList(List<string> timeSelectionList){
        var tempList = new List<int>();
        for (int i = 0; i < timeSelectionList.Count; i++){
            var todaysTimeRange = allTimeRangeList[i];

            if (timeSelectionList[i] == "Max"){
                tempList.Add(todaysTimeRange[1]);
            }
            else{
                tempList.Add(todaysTimeRange[0]);
            }
        }

        return tempList;
    }

    private static void VerifyStudiedTime(
        List<int> studiedTimeList,
        List<string> TimeSelectionList){
        
        var i = 0;
        while (sumTime != studiedTime){

            if (i >= studiedTimeList.Count){
                break;
            }

            var todaysMaxTime = allTimeRangeList[i][1];
            var todaysMinTime = allTimeRangeList[i][0];
            var todaysStudiedTime = studiedTimeList[i];
            var todaysTimeSelection = TimeSelectionList[i];

            if (todaysTimeSelection == "Max" && todaysStudiedTime > todaysMinTime ){
                studiedTimeList[i] = todaysStudiedTime - 1;
            }
            else if (todaysTimeSelection == "Min" && todaysStudiedTime < todaysMaxTime){
                studiedTimeList[i] = todaysStudiedTime + 1;
            }
            else{
                i++;
                continue;
            }

            BeforeAnExam.studiedTime = AddIntsInList(studiedTimeList);
        }
    }

    private static int AddIntsInList(List<int> numList){

        var total = 0;
        foreach (int num in numList){
            total += num;
        }

        return total;
    }
}
