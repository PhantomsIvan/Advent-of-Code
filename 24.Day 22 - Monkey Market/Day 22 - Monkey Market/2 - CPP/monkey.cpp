#include <iostream> //for printing "cout << total << endl;" "cout << maxValue << endl;"" count = "Console Out Put"       
#include <fstream>  //for reading and writing input.txt
#include <vector>  //Array List
#include <unordered_map>   //seqToTOtal for our unordered map
#include <unordered_set>   //HashSet for our sequence differences "seen" 
#include <algorithm>       // we use the "max" function in question 2
#include <functional> //interactions without custom VectorHash CPP doesn't automatically process Hash 

// Since we are using a Hash Set and Has Map
//This VectorHash Struct provides a way to hash the keys
//For more information watch 9:23 https://youtu.be/KiB0vRi2wlc?si=YxRPVpnlrjIS93vK&t=564 
//interesting note about const maps and necessity of "".at" syntax
struct VectorHash {
   std::size_t operator()(const std::vector<int>& v) const {
       std::size_t hash = 0;
       for (int val : v) {
           hash = hash * 31 + val; 
       }
       return hash;
   }
};


//luckily Bitwise XOR ^ is similar in CPP
//It's just part of a way to generate random numbers also "(num * 64)) % 16777216" has an invisible bracket around it

long step(long num) {
   num = (num ^ (num * 64)) % 16777216;
   num = (num ^ (num / 32)) % 16777216;
   num = (num ^ (num * 2048)) % 16777216;
   return num;
}

void partOne() {
   long total = 0;
   std::ifstream inputFile("input.txt");
   std::string line;

   while (std::getline(inputFile, line)) {
       long num = std::stol(line);
       for (int i = 0; i < 2000; i++) {
           num = step(num);
       }
       total += num;
   }

   inputFile.close();
   std::cout << total << std::endl;
}

void partTwo() {
   //VectorHash is the struct above to give rules for how Hash Is Treated
   std::unordered_map<std::vector<int>, long, VectorHash> seqToTotal;
   std::ifstream inputFile("input.txt");
   std::string line;

   while (std::getline(inputFile, line)) {
       long num = std::stol(line);
       std::vector<int> buyer;
       buyer.push_back(static_cast<int>(num % 10));

       for (int i = 0; i < 2000; i++) {
           num = step(num);
           buyer.push_back(static_cast<int>(num % 10));
       }

       std::unordered_set<std::vector<int>, VectorHash> seen;

       for (std::size_t i = 0; i < buyer.size() - 4; i++) {
            // Get 5 consecutive numbers
            int a = buyer[i];          // Note: C++ uses [] instead of .get()
            int b = buyer[i + 1];
            int c = buyer[i + 2];
            int d = buyer[i + 3];
            int e = buyer[i + 4];
            
            // Calculate differences
            std::vector<int> seq;
            seq.push_back(b - a);
            seq.push_back(c - b);
            seq.push_back(d - c);
            seq.push_back(e - d);

            if (seen.find(seq) != seen.end()) {
                continue;
            }
            seen.insert(seq);
            seqToTotal[seq] += e;
        }
   }

   inputFile.close();

//Here we use an iterator to look at the keys and the value assigned to it to see which key has the largest value
//Iterator -- has the most control with access to both key and value
//Loop -- could use a big loop but you hav less control less compatible with older code 
//Key -- The key of this unordered map is the list of ints we call "sequence"
//unordered vs normal map -- performance is the main thing if you have a lot of data unordered is better and should be priorirtised but map can be faster 
//Vector over Map -- Vector is still an option and can be faster but Hash Map is quicker and easier to implement and Vector situtationally better
//Parts of this iteration -- 
// <std::vector<int>, long, VectorHash>
//1 "std::vector<int>" -- they key is a vector of ints, we turn that sequence to a binary key which we use to characterise the dictionary in terms of the value "e" the final banana amount
//2 "long" -- the value the key is pointing to is a long "e" the banana amount maybe this could be an int?
//3 "VectorHash" -- we want to use our VectorHash to process the keys and handle them
//4 ::iterator it = seqToTotal.begin() -- we want iterator we these aboe parameters, begin() tells us to begin at the first element
//note -- begin() alterntive rbegin(), cbeing(), crbeing() --> cbegin crbegin are read only
   long maxValue = 0;
   for (std::unordered_map<std::vector<int>, long, VectorHash>::iterator it = seqToTotal.begin(); 
        it != seqToTotal.end(); ++it) {
       maxValue = std::max(maxValue, it->second);
   }

   std::cout << maxValue << std::endl;
}

int main() {
   partOne();
   partTwo();
   return 0;
}

//g++ -std=c++11 -o monkey monkey.cpp
//./monkey
