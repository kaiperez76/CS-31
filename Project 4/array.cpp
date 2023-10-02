//
//  main.cpp
//  Project 4
//
//  Created by Kai Perez on 10/27/22.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include <cmath>
using namespace std;




int appendToAll(string a[], int n, string value){
    if (n < 0){
        return -1;}
    if (n >= 0){
        for (int k = 0; k < n; k++){        //looping through and appending chars
            a[k] += value;}
    }
return n;
}





int lookup(const string a[], int n, string target){
    if (n < 0){
        return -1;}
    for (int k = 0; k < n; k++){
        if (a[k] ==  target)            //loop through and return if they are equal
            return k;
    }
return -1;
}



int positionOfMax(const string a[], int n){
    string currentMaxStr = "";
    int currentMaxInt = -1;
    if (n <= 0 ){
        return -1;}
    for (int k = 0; k < n; k++){
        for(int i = 0; i < a[k].size(); i++){
            tolower(a[k].at(i));   //make everything lowercase so it compares alphabetically
        }
        if (currentMaxStr < a[k]){      // loop through and if its bigger assign it
            currentMaxStr = a[k];
            currentMaxInt = k;
        }
    }
    return currentMaxInt;
}




int rotateLeft(string a[], int n, int pos){
    if (n < 0 || pos < 0){
        return -1;}
    if (pos > n)
        return -1;
    string tempValue = a[pos];      //assign deleted variable to tempValue
    for (int k = 0; k < (n - pos - 1); k++){
        a[k + pos] = a[k + pos + 1];        //rotate everything left
        }
    a[n - 1] = tempValue;           //assign deleted variable again
    return pos;
}



int countRuns(const string a[], int n){
    int counter = 0;
    if (n < 0){
        return -1;}
    for (int k = 0; k < n - 1; k++){   //loops through and counts if they aren't identical
        if (a[k] != a[k+1])
            counter++;
    }
    if(n > 0){
        counter += 1;}   //to account for last index not in for loop
    return counter;
}


int flip(string a[], int n){
    if (n < 0){
        return -1;}
    for (int k = 0; k < (n/2); k++){
        string tempValue = a[k];        //assigns left side to other value
        a[k] = a[n - k - 1];            //left side is equal to right
        a[n - k - 1] = tempValue;       //right side is equal to the other value
    }
    return n;
}



int differ(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0){
        return -1;}
    
    int counter = 0;
    int smallerValue = 0;           // sets loop to size of smaller array
    if (n1 > n2){
        smallerValue = n2;}
    if (n2 > n1){
        smallerValue = n1;}
    if (n2 == n1){
        smallerValue = n1;}
    
    if (smallerValue == 1){
        if (a1[0] != a2[0])
            return 0;
    }
    
    for (int k = 0; k < smallerValue; k++){  //counts then breaks when the two arrays dont match
        if (a1[k] == a2[k])
            counter = k;
        if (a1[k] != a2[k])
            break;
    }
    return counter + 1;
}


int subsequence(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0){
        return -1;}
    if (n2 == 0){
        return 0;}
    
    int counter = 0;
    for (int k = 0; k < n1; k++){
        if (a1[k] == a2[0]){                //checks matching to begining of substring
            for (int i = 0; i < n2; i++){
                if (a1[k+i] ==  a2[i]){         //as long as they still match, add to counter
                    counter += 1;
                    if (counter == (n2)){      // if it matches the whole substring, return k
                        return (k);
                    }
                }
            }
        }
    }
    return -1;
}





int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0 || n2 < 0){
        return -1;}
    for (int k = 0; k < n1; k++){       //increment through a1
        for (int i = 0; i < n2; i++){       //increment through a2
            if (a1[k] == a2[i]){                // if a1 is equal to a2, return pos a1
                return k;
            }
        }
    }
    return -1;
}




int split(string a[], int n, string splitter){
    if (n < 0){
        return -1;}
    
    
    string tempValue;
    int saver = 0;
    int smallerValue = static_cast<int>(a[0].size());
    for (int k = 0; k < n; k++){                  //makes everything lowercase
        for(int i = 0; i < a[k].size() ;i++){
            a[k].at(i) = tolower(a[k].at(i));}
        }
   
    for (int k = 0; k < n ; k++){    //takes size of smaller string and stores it in smallerValue
             if (a[k].size() > splitter.size()){
                 smallerValue = static_cast<int>(splitter.size());}
             if (a[k].size() < splitter.size()){
                 smallerValue = static_cast<int>(a[k].size());}
             if (a[k].size() == splitter.size()){
                 smallerValue = static_cast<int>(a[k].size());}
         
        for(int i = 0; i < smallerValue; i++){
            if (a[k].at(i) < splitter.at(i)){       //if string is less than splitter
                saver++;                            //add to count
                tempValue = a[k];
                for (int p = (k); p > 0; p--){
                    a[p] = a[p - 1];                //move string increment of 1 right
                }
                a[0] = tempValue;                   //assign deleted value to a[0]
            }
            if (a[k].at(i) > splitter.at(i)){
                break;}
        }
    }
    if (saver >= 0 &&  saver < n){
            return saver;
    }
    return n;
}




int main() {
    
    //initial asserts affect following ones
    string food[5] = {"pasta", "sushi", "barbeque", "curry", "steak" };
    assert(appendToAll(food, -6, "!!") == -1 && food[0] == "pasta");
    //assert(appendToAll(food, 4, "!!") == 4 && food[4] == "steak"
                                           //&& food[3] == "curry!!" );
    assert(appendToAll(food, 5, "!!") == 5 && food[4] == "steak!!"
                                           && food[3] == "curry!!" );
    
    
    string seasons[5] = {"winter", "fall", "spring", "summer", "winter"};
    assert(lookup(seasons, 5, "winter") == 0);
    assert(lookup(seasons, 5, "summer") == 3);
    assert(lookup(seasons, 5, "Summer") == -1);
    assert(lookup(seasons, 2, "summer") == -1);
    assert(lookup(seasons, -7, "summer") == -1);
    
    
    string sports[6] = {"Soccer", "Basketball", "Football", "Rugby", "Tennis", "Track"};
    assert(positionOfMax(sports, 6) == 5);
    assert(positionOfMax(sports, -5) == -1);
    assert(positionOfMax(sports, 4) == 0);
    assert(positionOfMax(sports, 0) == -1);
    
    //initial asserts affect following ones
    string trees[6] = {"poplar", "birch", "pine", "oak", "evergreen", "maple"};
    assert(rotateLeft(trees, -6, 1) == -1 && trees[1] == "birch");
    assert(rotateLeft(trees, 6, -1) == -1 && trees[1] == "birch");
    //assert(rotateLeft(trees, 6, 1) == 1 && trees[1] == "pine" && trees[5] == "birch");
    //assert(rotateLeft(trees, 6, 4) == 4 && trees[1] == "birch" && trees[4] ==  "maple");
    //assert(rotateLeft(trees, 6, 2) == 2 && trees[1] == "birch" && trees[5] ==  "pine");
    assert(rotateLeft(trees, 6, 5) == 5 && trees[1] == "birch" && trees[5] ==  "maple");
    
    
    string fruits[5] = {"apple", "apple", "mango", "mango", "orange"};
    assert(countRuns(fruits, 5) == 3);
    assert(countRuns(fruits, 4) == 2);
    assert(countRuns(fruits, 3) == 2);
    assert(countRuns(fruits, -5) == -1);
    assert(countRuns(fruits, 1) == 1);
    
    //initial asserts affect following ones
    string colors[5] = {"red", "orange", "yellow", "green", "blue"};
    assert(flip(colors, -3) == -1);
    //assert(flip(colors, 5) == 5 && colors[0] == "blue" && colors[2] == "yellow");
    //assert(flip(colors, 4) == 4 && colors[0] == "green" && colors[2] == "orange");
    assert(flip(colors, 0) == 0 && colors[0] == "red" && colors[2] == "yellow");
    
    
    string desserts[4] = {"waffle", "pancakes", "cereal", "brownie"};
    string breakfast[4] = {"waffle", "pancakes", "cereal", "eggs"};
    assert(differ(desserts, 4, breakfast, 4) == 3);
    assert(differ(desserts, 4, breakfast, 1) == 1);
    assert(differ(desserts, 4, breakfast,-3) == -1);
    assert(differ(desserts, -4, breakfast,-3) == -1);
    assert(differ(desserts, 4, breakfast,-3) == -1);
    assert(differ(desserts, 3, breakfast, 3) == 3);
    
    string plant [5] = {"bush", "tree", "flower", "succulent", "fern"};
    string plant2 [3] = {"tree", "flower", "succulent"};
    string plant3 [3] = {"daisy", "orchid", "lily"};
    assert(subsequence(breakfast, 4 , desserts , 4) == -1);
    assert(subsequence(plant, 5, plant2, 3) == 1);
    assert(subsequence(plant, 5, plant2, 0) == 0);
    assert(subsequence(plant, 5, plant3, 3) == -1);
    assert(subsequence(plant, -5, plant2, 3) == -1);
    assert(subsequence(plant, 5, plant2, -3) == -1);
    assert(subsequence(plant, -5, plant2, -3) == -1);
    
    
    string furniture[6] = {"couch", "chair", "table", "TV", "window", "pot"};
    string furniture2[4] = {"desk", "window", "curtain", "table"};
    assert(lookupAny(furniture, 6, furniture2, 4) == 2);
    assert(lookupAny(furniture, 6, furniture2, 1) == -1);
    assert(lookupAny(furniture, -6, furniture2, 4) == -1);
    assert(lookupAny(furniture, 6, furniture2, -4) == -1);
    assert(lookupAny(furniture, -6, furniture2, -4) == -1);
    
    //initial asserts affect following ones
    string dogs[5] = {"Husky", "Bulldog", "Boxer", "Poodle", "Labrador"};
    assert(split(dogs, 5, "liz") == 4 );
    assert(split(dogs, 5, "couch") == 2 && ("bulldog" == dogs[0] ||
                                            "bulldog" == dogs[1]));
    assert(split(dogs, 5, "quartz") == 5);
    assert(split(dogs, -5, "couch") == -1);
    //assert(split(dogs, 5, "abc") == 0 && "boxer" == dogs[2]);

    
    

    

    
    
    cerr << "all tests passed" << endl;
    
    
  
    
    return 0;
}

