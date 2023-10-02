//
//  main.cpp
//  Project 2
//
//  Created by Kai Perez on 10/10/22.
//

#include <iostream>
using namespace std;


int main()
{
    string Name;                    //establishing variables
    double taxableIncome;
    string Occupation;
    int children;
    double taxPayment;
    
    cout.setf(ios::fixed);          //setting up to two decimal places
    cout.precision(2);
    
    cout << "Name: ";               //Obtaining input Data and stopping loopholes
    getline(cin, Name);
    if (Name == ""){
        cout << "---" << endl;
        cout << "You must enter a name" << endl;
        return 1;}
    
    cout << "Taxable Income: ";    
    cin >> taxableIncome;
    if (taxableIncome < 0){
        cout << "---" << endl;
        cout << "The taxable income must not be negative" << endl;
        return 1;}
    cin.ignore(10000, '\n');         //using getline after cin an int
    
    
    cout << "Occupation: ";
    getline(cin, Occupation);
    if (Occupation == ""){
        cout << "---" << endl;
        cout << "You must enter an occupation" << endl;
        return 1;}
    
    cout << "Number of children: ";
    cin >> children;
    if (children < 0){
        cout << "---" << endl;
        cout << "The number of children must not be negative" << endl;
        return 1;}
    
    cout << "---" << endl;
    
    
    
    
    
    if(taxableIncome < 55000){            //calculations regarding tax payment and bracket
        taxPayment = taxableIncome * (0.04);}
    else if (taxableIncome < 125000 && Occupation == "teacher"){
        taxPayment = (55000 * 0.04) + (taxableIncome-55000)*0.05;}
    else if (taxableIncome < 125000 && Occupation == "nurse"){
        taxPayment = (55000 * 0.04) + (taxableIncome-55000)*0.05;}
    else if (taxableIncome < 125000){
        taxPayment = (55000 * 0.04) + (taxableIncome-55000)*0.07;}
    else if (taxableIncome > 125000 && Occupation == "teacher"){
        taxPayment = (55000 * 0.04) + (70000 * 0.05) + (taxableIncome-125000) * (0.093);}
    else if (taxableIncome > 125000 && Occupation == "nurse"){
        taxPayment = (55000 * 0.04) + (70000 * 0.05) + (taxableIncome-125000) * (0.093);}
    else{
        taxPayment = (55000 * 0.04) + (70000 * 0.07) + (taxableIncome-125000) * (0.093);}
    
    
    
    
    
    if (children > 0 && taxableIncome < 125000)    //necessary subtractions for children
        taxPayment = taxPayment - (200 * children);
    
    
    if (taxPayment < 0){               //Output 0 when taxable income reaches negatives
        taxPayment = 0;
        cout << Name << " would pay $" << taxPayment << endl;}
    else {
        cout << Name << " would pay $" << taxPayment << endl;}
    }

