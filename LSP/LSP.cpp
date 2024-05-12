#include <iostream>
#include<vector>
using namespace std;
//1
//Напишите программу для расчёта оплаты за электроэнергию. 
//Создайте базовый класс для всех типов счетчиков электроэнергии, имеющий метод для вычисления стоимости потребленной электроэнергии. 
//Реализуйте несколько подклассов счетчиков, например, обычный, двухтарифный, многотарифный и т.д.
//Переопределите метод для каждого подкласса так, чтобы он корректно вычислял стоимость в соответствии с тарифами. 
//Создайте вектор указателей на объекты базового класса и заполните его объектами каждого из подклассов. 
//Напишите функцию для вывода стоимости потребленной электроэнергии для каждого счетчика.

class ElectricityMeter abstract {
protected:
    const double tariff_before_hundred = 0.9;
    const double tariff_after_hundred = 1.68;  
public:
    virtual double CalculateCost(double consumed_amount) = 0;
};

class OriginalElectricityMeter : public ElectricityMeter {      
public:
    virtual double CalculateCost(double consumed_amount) {
        double cost = 0;
        if (consumed_amount > 100)
        {
            cost += 100 * tariff_before_hundred;          
            consumed_amount -= 100;            
            cost += consumed_amount * tariff_after_hundred;
        }
        else
            cost += consumed_amount * tariff_before_hundred;
        return cost;
    }
};

class DualRateElectricityMeter : public ElectricityMeter {
    const double tariff_day = 1;
    const double tariff_night = 0.5;
    double night_electricity = 0;
    double day_electricity = 0;
public:
    void SetTariffElectricity(double consumed_amount) {        
        cout << "Day electricity - ";
        cin >> day_electricity;
        cout << "\nNight electricity - ";        
        cin >> night_electricity;
        if (night_electricity + day_electricity == consumed_amount)
            cout << "\nCorrect\n";
        else
        {
            cout << "\nIncorrect numbers\n";
            SetTariffElectricity(consumed_amount);
        }
    }
    virtual double CalculateCost(double consumed_amount) {
        double cost = 0;
        SetTariffElectricity(consumed_amount);
        if (consumed_amount > 100) {
            //100 кВт * год × 0.9 грн × 1 × 70 % +100 кВт * год × 0.9 грн × 0.5 × 30 % = 76.50 грн
            cost += 100 * tariff_before_hundred * tariff_day * (day_electricity / (day_electricity + night_electricity)) + 100 * tariff_before_hundred * tariff_night * (night_electricity / (day_electricity + day_electricity));
            consumed_amount -= 100;
            cost += consumed_amount * tariff_after_hundred * tariff_day * (day_electricity / (day_electricity + night_electricity)) + consumed_amount * tariff_after_hundred * tariff_night * (night_electricity / (day_electricity + day_electricity));
        }
        else
            cost += consumed_amount * tariff_before_hundred * tariff_day * (day_electricity / (day_electricity + night_electricity)) + consumed_amount * tariff_before_hundred * tariff_night * (night_electricity / (day_electricity + day_electricity));
        return cost;
    }
};

class MultiTariffElectricityMeter : public ElectricityMeter {
    const double tariff_pic = 1.5;
    const double tariff_semi_pic = 1;
    const double tariff_night = 0.4;
    double pic_electricity = 0;
    double semi_pic_electricity = 0;
    double night_electricity = 0;
public:
    void SetTariffElectricity(double consumed_amount) {
        cout << "Enter pic electricity - ";
        cin >> pic_electricity;
        cout << "\nEnter semi-pic electricity - ";
        cin >> semi_pic_electricity;
        cout << "\nEnter night electricity - ";
        cin >> night_electricity;
        if (pic_electricity + semi_pic_electricity + night_electricity == consumed_amount)
            cout << "Correct\n";
        else
        {
            cout << "Incorrect numbers\n";
            SetTariffElectricity(consumed_amount);
        }
    }
    virtual double CalculateCost(double consumed_amount) {
        double cost = 0;
        SetTariffElectricity(consumed_amount);
        if (consumed_amount > 100) {
            cost += 100 * tariff_before_hundred * tariff_pic * (pic_electricity / (pic_electricity + semi_pic_electricity + night_electricity)) + 100 * tariff_before_hundred * tariff_semi_pic * (semi_pic_electricity / (pic_electricity + semi_pic_electricity + night_electricity)) + 100 * tariff_before_hundred * tariff_night * (night_electricity / (pic_electricity + semi_pic_electricity + night_electricity));
            consumed_amount -= 100;
            cost += consumed_amount * tariff_before_hundred * tariff_pic * (pic_electricity / (pic_electricity + semi_pic_electricity + night_electricity)) + consumed_amount * tariff_before_hundred * tariff_semi_pic * (semi_pic_electricity / (pic_electricity + semi_pic_electricity + night_electricity)) + consumed_amount * tariff_before_hundred * tariff_night * (night_electricity / (pic_electricity + semi_pic_electricity + night_electricity));
        }
        else
            cost += consumed_amount * tariff_before_hundred * tariff_pic * (pic_electricity / (pic_electricity + semi_pic_electricity + night_electricity)) + consumed_amount * tariff_before_hundred * tariff_semi_pic * (semi_pic_electricity / (pic_electricity + semi_pic_electricity + night_electricity)) + consumed_amount * tariff_before_hundred * tariff_night * (night_electricity / (pic_electricity + semi_pic_electricity + night_electricity));
        return cost;
    }
};
//2
//Напишите программу для работы с базой данных сотрудников.
//Создайте базовый класс для всех сотрудников, имеющий методы для получения их данных и вывода информации.
//Реализуйте несколько подклассов сотрудников, например, менеджер, инженер, бухгалтер и т.д.
//Для каждого подкласса переопределите методы базового класса так, чтобы они выводили соответствующую информацию о сотруднике.
//Создайте вектор указателей на объекты базового класса и заполните его объектами каждого из подклассов.
//Напишите функцию для вывода информации о каждом сотруднике.

class Employee abstract{
public:
    virtual void Print() = 0;
};

class Engineer : public Employee {
public:
    virtual void Print() {
        cout << "Engineer\n";
    }
};

class Manager : public Employee {
public:
    virtual void Print() {
        cout << "Manager\n";
    }
};

class Accountant : public Employee {
public:
    virtual void Print() {
        cout << "Accountant\n";
    }
};

int main()
{    
    /*vector<ElectricityMeter*> ar;
    ar.push_back(new OriginalElectricityMeter);
    ar.push_back(new DualRateElectricityMeter);
    ar.push_back(new MultiTariffElectricityMeter);
    for (int i = 0; i < ar.size(); i++)
        cout << ar[i]->CalculateCost(230) << "\n";*/


    vector<Employee*> ar;
    ar.push_back(new Accountant);
    ar.push_back(new Engineer);
    ar.push_back(new Manager);
    for (int i = 0; i < ar.size(); i++)
    {
        ar[i]->Print();
    }
}