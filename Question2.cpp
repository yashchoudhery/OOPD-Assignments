
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include<string>
#include<iomanip>
#include"Question1.cpp"

using namespace std;

class InvestmentData1 {
public:
    int year;
    double growthPrice;
    double inflationRate;

  
    InvestmentData1(double growthPrice = 0.0, int year = 0, double inflationRate = 0.0) {
        this->growthPrice = growthPrice;
        this->year = year;
        this->inflationRate = inflationRate;
    }
};

class ProfitTaxCalc1 {
private:
    double taxRate;

public:
  
    ProfitTaxCalc1() {
        taxRate = 20.0;  
    }

    // function to calculate tax on capital gain
    double calculateTax1(double cGain , int sellingyear) {
        return sellingyear < 2024 ? ((cGain > 0) ? (cGain * (taxRate / 100)) : 0) : ((cGain > 0) ? (cGain * 0.125) : 0);
    }
};


class InvestmentHouse1 {
private:
    InvestmentData* fileData;  // dynamically allocated array of csv data.
    long costPrice;
    int purchaseYear;
    double sellingPrice;
    int sellingyear;
    int dataSize;  // number of entries in the csv data file.

public:
 
    InvestmentHouse1(double Cp, int Poy, string path , int sy) {
        this->fileData = getTheData(path, dataSize);  // Get the data from the CSV file
        this->costPrice = Cp;
        this->purchaseYear = Poy;
        this->sellingyear=sy;
    }

    double sellingPriceCalc(int year) {
        sellingPrice = costPrice;
        int index = checkGrowthYear(this->purchaseYear, fileData, dataSize);
        
        for (int i = index+1; fileData[i].year <= year && i < dataSize; i++) {
            sellingPrice =fileData[i].year < 2024 ? (sellingPrice *  ( 1 + ((fileData[i].growthPrice - fileData[i].inflationRate) / 100))) : (sellingPrice *  ( 1 + ((fileData[i].growthPrice ) / 100))) ;
        }

        return sellingPrice;
    }
    
    double longTermCapitalGainTax() {
        ProfitTaxCalc1 p;
        double investmentTax = p.calculateTax1(sellingPrice - costPrice, sellingyear);
        return investmentTax;
    }

    ~InvestmentHouse1() {
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
    long costPrice=5000000;
    int purchaseYear=2010;
    int sellingyear;
    // cout<<"Enter the Property Purchase Price :"<<endl;
    // cin>>costPrice;

    // cout<<endl<<"Enter the Property Purchase Year :"<<endl;
    // cin>>purchaseYear;
    // cout<<endl;

    cout<<endl<<"Enter the Property Selling Year :"<<endl;
    cin>>sellingyear;
    cout<<endl;

    cout<<"Below is the selling price and Long-Term Capital Gain Tax calculation before change in tax rate"<<endl;
    InvestmentHouse investment(costPrice, purchaseYear, filePath);
    double sellingPrice = investment.sellingPriceCalc(sellingyear); 
    double tax = investment.longTermCapitalGainTax();
    cout << "Selling Price: " <<fixed<<setprecision(4)<< sellingPrice << endl;
    cout << "Long-Term Capital Gain Tax: " <<fixed<<setprecision(4)<< tax << endl;

    cout<<"Below is the selling price and Long-Term Capital Gain Tax calculation after change in tax rate"<<endl;
    InvestmentHouse1 investment1(costPrice, purchaseYear, filePath,sellingyear);
    double sellingPrice1 = investment1.sellingPriceCalc(sellingyear); 
    double tax1 = investment1.longTermCapitalGainTax();
    cout << "Selling Price: " <<fixed<<setprecision(4)<< sellingPrice << endl;
    cout << "Long-Term Capital Gain Tax: " <<fixed<<setprecision(4)<< tax << endl;

    cout<<"The Difference Between the calculation of selling price and Long-Term Capital Gain Tax, before and after change in tax rate is :"<<endl;
    cout<<"Difference in selling price is : "<<sellingPrice<<" & "<<sellingPrice1<<" = "<<((sellingPrice-sellingPrice1) < 0 ? (sellingPrice-sellingPrice1)*(-1) : (sellingPrice-sellingPrice1))<<endl;
    cout<<"Difference in ong-Term Capital Gain Tax calculation is : "<<tax<<" & "<<tax1<<" = "<<((tax-tax1)< 0 ? (tax-tax1*(-1)) : (tax-tax1))<<endl;


    return 0;
}
