import java.io.*;
import java.util.*;

//import java.io.*;
//Helps read the input file
//This test case is so large we  need another file to input it
//Note that vs code has a 26 character limit on input
//Handles I/O errors, these are input output errors (IO) we're processing an Input file of strings and outputing two lists

//import java.util.*;
//We're going to use Data Structures: lists, Array List, Hash Maps
//and the Collections tool for sorting

public class Solution {

    public static void main(String[] args) throws IOException {
        //Step 1 process the data given, take them as a string and populate 2 lists
        InputData data = readInput("./input.txt");
        double distance = calculateTotalDistance(data.list1, data.list2);
        long score = calculateSimilarityScore(data.list1, data.list2);
        
        System.out.println(distance);
        System.out.println(score);
    }
 
    //We're going to define a type of Object 
    //We define it to constain 2 lists
    //Data structures can cotain Objects and it's pretty convenient
    //We define it using a constructor
    //We could probably make this a sepparate file or make the whole thing instanced
    private static class InputData {
       List<Integer> list1;
       List<Integer> list2;
       
       InputData(List<Integer> list1, List<Integer> list2) {
           this.list1 = list1;
           this.list2 = list2;
       }
    }
   
    //This reads the input file and populates our lists
    private static InputData readInput(String inputFileDir) throws IOException {
        List<Integer> list1 = new ArrayList<>();
        List<Integer> list2 = new ArrayList<>();
       
        BufferedReader reader = new BufferedReader(new FileReader(inputFileDir));
        String line;
        while ((line = reader.readLine()) != null) {
            String[] data = line.trim().split("   "); /* In prog2 we use split(" ") */
            list1.add(Integer.parseInt(data[0]));
            list2.add(Integer.parseInt(data[1]));
        }
        reader.close();
       
        return new InputData(list1, list2);
    }

    //Here we process the newly created lists into an array list
    //then we use the "Collections" tool to easily sort them "from smallest to largest" 
    //Don't be afraid by Collections it's just overall an easy to use tool that works with lists and maps etc
    //by default this tool sorts in ascending but it has ways to reverse
    private static double calculateTotalDistance(List<Integer> list1, List<Integer> list2) {
        List<Integer> sortedList1 = new ArrayList<>(list1);
        List<Integer> sortedList2 = new ArrayList<>(list2);
       
        Collections.sort(sortedList1);
        Collections.sort(sortedList2);
       
        double totalDistance = 0;
        for (int i = 0; i < sortedList1.size(); i++) {
            totalDistance += Math.abs(sortedList1.get(i) - sortedList2.get(i));
        }
       
        return totalDistance;
    }
   
    //Here we use a HashMap to store our findings
    //Rather than storing everything in a list we use a key value pair to count occurrences
    //First we track the occurrences of duplicates in the second list
    //We then use a function of hash maps to check each number in the first list    
    //so in the example the 3 from list 1 occurs 3 times in the second list so the score etablished was 3*3 = 9 3
    // for the number istelf and 3 for the occurrences
    private static long calculateSimilarityScore(List<Integer> list1, List<Integer> list2) {
        Map<Integer, Integer> numberOccurrenceMap = new HashMap<>();
        long similarityScore = 0;
       

        //If HashMap has a put method
        //First is the target number or result, the second value is the ocurrencece
        //Get or Default
        //"Default" -- If the number doesn't exist then the default is zero and we increment that by 1
        //"Get" -- if the number existesd we get the previous number and increment that
        //NOTE this is possibly doable with a Vector/ArrayList or List/LinkedlIst but this is faster and easier
        //NOTE "Encapsulation" in OOP -- 1 Data Hiding Private and Protected hides access to data, 2 Access Control can control how the data is access through available methods, 
        //3 Data Validation you can set rules like not being ablt to withdraw more money than you own or have deposited
        for (int number : list2) {
            numberOccurrenceMap.put(number, numberOccurrenceMap.getOrDefault(number, 0) + 1);
        }
       
        for (int number : list1) {
            if (numberOccurrenceMap.containsKey(number)) {
                similarityScore += (long) number * numberOccurrenceMap.get(number);
            }
        }
       
        return similarityScore;
    }
}

/*
 Solution Explain

 Advent of Code 1 has 
    "2 QUESTIONS"

    Q1 Distance
    Its given us two lists
    It's asking us basically to take the smallest of the first list and find the distance to the smallest of the second (NOTE absolute value)

    Then the second smallest of the first compared to the second smallest of the third. Then add to the total distance.

    Q2 Similarity Score
    It gives us a formula for "Similarity score" say the number is 3 on first list, if 3 occurs 5 times in the second list then the score is 3*5 = 15 
    add that to the overall similarity score

    in the example 3 occured 3 times in the second so that's 3*3=9 

    We could use an arraylist but HashMap has both speed on its side and fnctionality it's easier to use
  
 */
