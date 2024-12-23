#include <iostream> //for printing
#include <fstream> //to work with read/write files in java "import java.io.*;"
#include <vector> //to work with lists
#include <string> //to work with Strings
#include <algorithm> //compraable to Collections tools we used in the Java version
#include <unordered_map> //Hashmaps
#include <cstdlib> //math tools for absolute value
#include <sstream> //parsing also can be used like scanner
#include <iomanip> //by default C++ will output numbers differrently like using exponents this basically lets us fix the output

class InputData {

//Lesson 0.1: CPP files must have a tasks.json file accompanying it for some reaosn, was super confusing

//Lesson 0.2: CPP groups all Public functions under "Public: " and all privates as "Private: "

//Leson 1: Lists in C++
//Options: Vector(like an ArrayList), List(think LinkedLIst), Deque(ArrayDeque), array(Java Array, non reziable)
//Vector dynamically sized, better for reading/insertion, C++ Vector has better control of memory but requires more effort/accuracy 
//Runtime Generics: Java uses Type erasure and Casting, eliminating type information and treating everything generically as objects requiring type Casting
//CPP checks types at compile time while Java checks during run time dynamically
//CPP Vector faster but prone to issues and complexity, also not good for instertion/deletion beyond the ends as it gets shuffled

//List like ArrayList is doublelinked better for insertion and deletion not as good for reading and iterating over

//CPP Arrays not resizeable Vector and LIst are resizeable

//CPP faster but requires constant interaction with memory where Java has a garbage collector
public: //all public functions are grouped
    std::vector<int> list1; //"std::" every command has this to keep sepparate to keep commands sepparate to other functions "Avoids conflict"
    std::vector<int> list2;

//Constructor: In java this would be "InputData(List<Integer) list1, List<Integer) list2 )"
    InputData(std::vector<int>& list1, std::vector<int>& list2) 
        : list1(list1), list2(list2) {}
};


//Note that this is using modern CPP it assignms memory when using "push back"
//It deletes when we return
//Modern CPP uses modern pointers which avoids issues like dangling Pointers
//Pointer is like a memory refference but it has less rules and more flexible and prone to error
//"*"  int* arr; is used to declare an array as a pointer to int

/*Thi sis what manual memory management looks like wiht pointers
class InputData {
public:
    int* list1;  // Raw pointer
    int* list2;
    size_t size;

    // Constructor with manual allocation
    InputData(size_t size) {
        this->size = size;
        list1 = new int[size];  // Manually allocate memory
        list2 = new int[size];
    }

    // Destructor to prevent memory leaks
    ~InputData() {
        delete[] list1;  // Manually free memory
        delete[] list2;
    }
};

//Dynamic arrays, handlings Files, 
*/
InputData readInput(const std::string& inputFileDir) {
    std::vector<int> list1;
    std::vector<int> list2;
    
    std::ifstream file(inputFileDir); //opening the file
    std::string line;
    
    while (std::getline(file, line)) { //reads the file by line
        std::stringstream ss(line); //reads the line using stringstream
        int num1, num2; //initiates these two ints
        ss >> num1 >> num2; //splits the string into two, CPP doesn't need to parse and split sepparately
        //ss because that's the name we used two lines above
        list1.push_back(num1); //this is how CPP adds or appeands lists
        list2.push_back(num2);
    }
    
    return InputData(list1, list2);
}

//Note how CPP indicates the type of parameter witht he & symbol
double calculateTotalDistance(const std::vector<int>& list1, const std::vector<int>& list2) {
    std::vector<int> sortedList1 = list1;
    std::vector<int> sortedList2 = list2;
    


    std::sort(sortedList1.begin(), sortedList1.end());
    std::sort(sortedList2.begin(), sortedList2.end());
    
    double totalDistance = 0;
    for (size_t i = 0; i < sortedList1.size(); i++) {
        totalDistance += std::abs(sortedList1[i] - sortedList2[i]);
    }
    
    return totalDistance;
}

//Unorder map is the HashMap in CPP 
//long is +-2.147 Billion or +-9.2 Quintillion Quintillion for 8 bith systems
//long long is only +-9.2 Quintillion Quintillion guaranteed
long long calculateSimilarityScore(const std::vector<int>& list1, const std::vector<int>& list2) {
    std::unordered_map<int, int> numberOccurrenceMap;
    long long similarityScore = 0;
    
    for (int number : list2) {
        numberOccurrenceMap[number]++;
    }

     //CPP has an iterator that can handle missing keys
    //Java needs explicit instructions for missing keys getordefault or merge()
    for (int number : list1) {
        auto it = numberOccurrenceMap.find(number);
        if (it != numberOccurrenceMap.end()) {
            similarityScore += (long long)number * it->second; //So this map a "first" and "second" value the occurrence is "second" we have to speciffy
            //also type casting long long as it is an integer at the moment
        }
    }
    
    return similarityScore;
}

//the main method in CPP is an int method that returns 0 if the code executed without errors
//non 0 indicates an error
//it's possible to use void main()
int main() {
    InputData data = readInput("./input.txt");
    double distance = calculateTotalDistance(data.list1, data.list2);
    long long score = calculateSimilarityScore(data.list1, data.list2);

    //std::cout and Endl work with the ostream class which we use for printing
    //cout used to print
    //endl used to manipulate and change ostream 
    //endl vs \n -- endle flushes the stream which is slower
    
    std::cout << std::fixed;  // Use fixed point notation and avoid unnatural number expression
    std::cout << std::setprecision(0);  // No decimal places
    std::cout << distance << std::endl;
    std::cout << score << std::endl;
    
    return 0;
}

//To launch the file type these two lines in terminal
//g++ Solution.cpp -o solution
//./solution
