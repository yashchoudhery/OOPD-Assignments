#include<iostream>


using namespace std;


class InvestmentData{

    int year;
    double costPrice;
    double inflationrate;

    InvestmentData(double costPrice,int year,double inflationraate){
        this->costPrice=costPrice;
        this->year=year;
        this->inflationrate;


    }


}

class InvestmentHouse
{
    double costPrice;
    int purchanseYear;
public:
    InvestmentHouse(double Cp,int Poy){
        this->costPrice=Cp;
        this->purchanseYear=Poy;

    }    



    double sellingPriceCalc(){


    }


};


class ProfitTaxCalc{
    private:
    double taxRate;

public:
    ProfitTaxCalc() {
        taxRate = 20.0;
    }

    
    double calculateTax(double cGain) {
        return (cGain > 0) ? (cGain * (taxRate / 100)) : 0;
    }
};




