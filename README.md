To compile and build the program:

g++ -c Question1.cpp
g++ -c Question2.cpp


To run the executable:
./Question1
./Question2

To debug the program
g++ -g -o debugltcg Question1.o
g++ -g -o debugltcg2 Question2.o


To Optimize the program:
g++ -O3 -o optimizedltcg Question1.o
g++ -O3 -o optimizedltcg2 Question2.o





Input Format
Question 1: The values (such as the initial property cost and purchase year and selling year) are hardcoded directly in the program. No user input is required.

Question 2: The program takes an integer input from the user representing the selling year , and calculates the estimated selling price and Long-Term Capital Gains (LTCG) tax based on this input and also calculated the difference between them.



I used below formula to calculate the selling price as mentioned in the problem

sellingPrice = sellingPrice *  ( 1 + ((fileData[i].growthPrice - fileData[i].inflationRate) / 100))) 
sellingPrice = sellingPrice *  ( 1 + ((fileData[i].growthPrice ) / 100))

& I used below formula to calculate the longTermCapitalGainTax as mentioned in the problem

longTermCapitalGainTax = capitalGain * (taxRate / 100)
longTermCapitalGainTax = capitalGain * 0.125
