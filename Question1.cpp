
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include<string>
#include<iomanip>

using namespace std;

class InvestmentData {
public:
    int year;
    double growthPrice;
    double inflationRate;

  
    InvestmentData(double growthPrice = 0.0, int year = 0, double inflationRate = 0.0) {
        this->growthPrice = growthPrice;
        this->year = year;
        this->inflationRate = inflationRate;
    }
};

class ProfitTaxCalc {
private:
    double taxRate;

public:
  
    ProfitTaxCalc() {
        taxRate = 20.0;  
    }

    // function to calculate tax on capital gain
    double calculateTax(double cGain) {
        return (cGain > 0) ? (cGain * (taxRate / 100)) : 0;
    }
};


class InvestmentHouse {
private:
    InvestmentData* fileData;  // dynamically allocated array of csv data.
    long costPrice;
    int purchaseYear;
    double sellingPrice;
    int dataSize;  // number of entries in the csv data file.

public:
 
    InvestmentHouse(double Cp, int Poy, string path) {
        this->fileData = getTheData(path, dataSize);  // Get the data from the CSV file
        this->costPrice = Cp;
        this->purchaseYear = Poy;
    }

    double sellingPriceCalc(int year) {
        sellingPrice = costPrice;
        int index = checkGrowthYear(this->purchaseYear, fileData, dataSize);

        for (int i = index+1; fileData[i].year <= year && i < dataSize; i++) {
            sellingPrice = sellingPrice *  ( 1 + ((fileData[i].growthPrice - fileData[i].inflationRate) / 100));
        }

        return sellingPrice;
    }
    
    double longTermCapitalGainTax() {
        ProfitTaxCalc p;
        double investmentTax = p.calculateTax(sellingPrice - costPrice);
        return investmentTax;
    }

    ~InvestmentHouse() {
        delete[] fileData;  // free dynamically allocated memory.
    }

private:
    
    InvestmentData* getTheData(const string& path, int& size) {
        ifstream file(path);
        if (!file) {
            cerr << "Unable to open file: " << path << endl;
            size = 0;
            return NULL;
        }

        string line;
        int count = 0;

       
        while (getline(file, line)) {
            count++;
        }

        size = count;
        InvestmentData* data = new InvestmentData[size];

        file.clear();
        file.seekg(0);

      
        int i = 0;
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string temp, yearStr;
        double growthPrice, inflationRate;

        // It only take the year (first 4 characters).
        getline(ss, yearStr, ',');
    //    cout<<yearStr;
        int year = stoi(yearStr.substr(0, 4));  // Extract only the year part
            
        getline(ss, temp, ',');
        growthPrice = stod(temp);

        getline(ss, temp, ',');
        inflationRate = stod(temp);

            data[i] = InvestmentData(growthPrice, year, inflationRate);
            i++;
        }

        file.close();
        return data;
    }

    // this function finds the index of the data for the purchase year
    int checkGrowthYear(int purchaseYear, InvestmentData* data, int size) {
        for (int i = 0; i < size; i++) {
            if (data[i].year == purchaseYear) {
                return i;
            }
        }
        return -1;  // if purchase year not present returning -1
    }
};



int main() {
    
    string filePath = "price-inflation.csv";  
    double costPrice = 5000000;  //data is hardcoaded you can mention any amount
    int purchaseYear = 2010;

    InvestmentHouse investment(costPrice, purchaseYear, filePath);
    double sellingPrice = investment.sellingPriceCalc(2019);  //selling yeartaken  2025 , you can take any year
    double tax = investment.longTermCapitalGainTax();

    cout << "Selling Price: " <<fixed<<setprecision(4)<< sellingPrice << endl;
    cout << "Long-Term Capital Gain Tax: " <<fixed<<setprecision(4)<< tax << endl;

    return 0;
}
