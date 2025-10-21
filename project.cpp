#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

class Car {
private:
    string carId;
    string model;
    string brand;
    double pricePerDay;
    bool isAvailable;

public:
    Car(string id, string m, string b, double price) {
        carId = id;
        model = m;
        brand = b;
        pricePerDay = price;
        isAvailable = true;
    }

    string getCarId() { return carId; }
    string getModel() { return model; }
    string getBrand() { return brand; }
    double getPricePerDay() { return pricePerDay; }
    bool getAvailability() { return isAvailable; }

    void setAvailability(bool status) { isAvailable = status; }

    void displayCarInfo() {
        cout << left << setw(10) << carId 
             << setw(15) << brand 
             << setw(15) << model 
             << setw(12) << pricePerDay 
             << (isAvailable ? "Available" : "Rented") << endl;
    }
};

class Customer {
private:
    string customerId;
    string name;
    string phone;
    string email;

public:
    Customer(string id, string n, string p, string e) {
        customerId = id;
        name = n;
        phone = p;
        email = e;
    }

    string getCustomerId() { return customerId; }
    string getName() { return name; }
    string getPhone() { return phone; }
    string getEmail() { return email; }

    void displayCustomerInfo() {
        cout << "\nCustomer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
    }
};

class Rental {
private:
    string rentalId;
    string carId;
    string customerId;
    int days;
    double totalCost;
    string rentalDate;

public:
    Rental(string rId, string cId, string custId, int d, double cost) {
        rentalId = rId;
        carId = cId;
        customerId = custId;
        days = d;
        totalCost = cost;
        
        time_t now = time(0);
        rentalDate = ctime(&now);
    }

    string getRentalId() { return rentalId; }
    string getCarId() { return carId; }
    string getCustomerId() { return customerId; }

    void displayRentalInfo() {
        cout << "\n========== RENTAL RECEIPT ==========" << endl;
        cout << "Rental ID: " << rentalId << endl;
        cout << "Car ID: " << carId << endl;
        cout << "Customer ID: " << customerId << endl;
        cout << "Rental Days: " << days << endl;
        cout << "Total Cost: Rs. " << fixed << setprecision(2) << totalCost << endl;
        cout << "Rental Date: " << rentalDate;
        cout << "====================================" << endl;
    }
};

class CarRentalSystem {
private:
    vector<Car> cars;
    vector<Customer> customers;
    vector<Rental> rentals;
    int carCounter;
    int customerCounter;
    int rentalCounter;

public:
    CarRentalSystem() {
        carCounter = 1;
        customerCounter = 1;
        rentalCounter = 1;
        
        // Pre-loaded cars
        cars.push_back(Car("C001", "Swift", "Maruti Suzuki", 1500));
        cars.push_back(Car("C002", "City", "Honda", 2500));
        cars.push_back(Car("C003", "Fortuner", "Toyota", 5000));
        cars.push_back(Car("C004", "XUV700", "Mahindra", 3500));
        cars.push_back(Car("C005", "Thar", "Mahindra", 4000));
        carCounter = 6;
    }

    void addCar() {
        string model, brand;
        double price;

        cout << "\n=== Add New Car ===" << endl;
        cout << "Enter Brand: ";
        cin.ignore();
        getline(cin, brand);
        cout << "Enter Model: ";
        getline(cin, model);
        cout << "Enter Price per Day (Rs.): ";
        cin >> price;

        string carId = "C" + string(3 - to_string(carCounter).length(), '0') + to_string(carCounter++);
        cars.push_back(Car(carId, model, brand, price));
        
        cout << "\nCar added successfully with ID: " << carId << endl;
    }

    void displayAllCars() {
        cout << "\n========== AVAILABLE CARS ==========" << endl;
        cout << left << setw(10) << "Car ID" 
             << setw(15) << "Brand" 
             << setw(15) << "Model" 
             << setw(12) << "Price/Day" 
             << "Status" << endl;
        cout << string(65, '-') << endl;

        for (auto& car : cars) {
            car.displayCarInfo();
        }
        cout << "====================================\n" << endl;
    }

    void registerCustomer() {
        string name, phone, email;

        cout << "\n=== Customer Registration ===" << endl;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter Email: ";
        getline(cin, email);

        string custId = "CUST" + string(3 - to_string(customerCounter).length(), '0') + to_string(customerCounter++);
        customers.push_back(Customer(custId, name, phone, email));
        
        cout << "\nCustomer registered successfully!" << endl;
        cout << "Your Customer ID: " << custId << endl;
    }

    void rentCar() {
        string carId, custId;
        int days;

        displayAllCars();

        cout << "Enter Car ID to rent: ";
        cin >> carId;
        cout << "Enter Customer ID: ";
        cin >> custId;
        cout << "Enter number of days: ";
        cin >> days;

        Car* selectedCar = nullptr;
        Customer* selectedCustomer = nullptr;

        for (auto& car : cars) {
            if (car.getCarId() == carId) {
                selectedCar = &car;
                break;
            }
        }

        for (auto& cust : customers) {
            if (cust.getCustomerId() == custId) {
                selectedCustomer = &cust;
                break;
            }
        }

        if (selectedCar == nullptr) {
            cout << "\nError: Car not found!" << endl;
            return;
        }

        if (selectedCustomer == nullptr) {
            cout << "\nError: Customer not found! Please register first." << endl;
            return;
        }

        if (!selectedCar->getAvailability()) {
            cout << "\nSorry! This car is already rented." << endl;
            return;
        }

        double totalCost = selectedCar->getPricePerDay() * days;
        string rentalId = "R" + string(3 - to_string(rentalCounter).length(), '0') + to_string(rentalCounter++);

        rentals.push_back(Rental(rentalId, carId, custId, days, totalCost));
        selectedCar->setAvailability(false);

        cout << "\n*** Car Rented Successfully! ***" << endl;
        selectedCustomer->displayCustomerInfo();
        cout << "\nCar: " << selectedCar->getBrand() << " " << selectedCar->getModel() << endl;
        cout << "Days: " << days << endl;
        cout << "Total Cost: Rs. " << fixed << setprecision(2) << totalCost << endl;
    }

    void returnCar() {
        string carId;

        cout << "\nEnter Car ID to return: ";
        cin >> carId;

        Car* selectedCar = nullptr;
        Rental* selectedRental = nullptr;

        for (auto& car : cars) {
            if (car.getCarId() == carId && !car.getAvailability()) {
                selectedCar = &car;
                break;
            }
        }

        if (selectedCar == nullptr) {
            cout << "\nError: Car not found or not currently rented!" << endl;
            return;
        }

        for (auto& rental : rentals) {
            if (rental.getCarId() == carId) {
                selectedRental = &rental;
                break;
            }
        }

        selectedCar->setAvailability(true);
        
        cout << "\n*** Car Returned Successfully! ***" << endl;
        if (selectedRental != nullptr) {
            selectedRental->displayRentalInfo();
        }
        cout << "\nThank you for using our service!" << endl;
    }

    void displayRentals() {
        if (rentals.empty()) {
            cout << "\nNo rental records available." << endl;
            return;
        }

        cout << "\n========== RENTAL HISTORY ==========" << endl;
        for (auto& rental : rentals) {
            rental.displayRentalInfo();
        }
    }
};

int main() {
    CarRentalSystem system;
    int choice;

    cout << "\n****************************************" << endl;
    cout << "*   WELCOME TO CAR RENTAL SYSTEM   *" << endl;
    cout << "****************************************" << endl;

    while (true) {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Display All Cars" << endl;
        cout << "2. Add New Car" << endl;
        cout << "3. Register Customer" << endl;
        cout << "4. Rent a Car" << endl;
        cout << "5. Return a Car" << endl;
        cout << "6. View Rental History" << endl;
        cout << "7. Exit" << endl;
        cout << "===============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.displayAllCars();
                break;
            case 2:
                system.addCar();
                break;
            case 3:
                system.registerCustomer();
                break;
            case 4:
                system.rentCar();
                break;
            case 5:
                system.returnCar();
                break;
            case 6:
                system.displayRentals();
                break;
            case 7:
                cout << "\nThank you for using Car Rental System!" << endl;
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
    }

    return 0;
}