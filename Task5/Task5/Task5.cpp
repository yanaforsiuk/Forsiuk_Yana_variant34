#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Car {
    string name;
    double engineVolume;
    double fuelConsumption;
    int passengers;
    string brand;
};

void addCar(const string& filename) {
    ofstream fout(filename, ios::app);
    Car car;

    cout << "Enter car name: ";
    cin >> ws;
    getline(cin, car.name);

    cout << "Enter engine volume: ";
    cin >> car.engineVolume;

    cout << "Enter fuel consumption: ";
    cin >> car.fuelConsumption;

    cout << "Enter number of passengers: ";
    cin >> car.passengers;

    cout << "Enter brand: ";
    cin >> ws;
    getline(cin, car.brand);

    fout << car.name << endl;
    fout << car.engineVolume << endl;
    fout << car.fuelConsumption << endl;
    fout << car.passengers << endl;
    fout << car.brand << endl;

    fout.close();

    cout << "Car added successfully.\n";
}

vector<Car> readCars(const string& filename) {
    ifstream fin(filename);
    vector<Car> cars;
    Car car;

    while (getline(fin, car.name)) {
        fin >> car.engineVolume;
        fin >> car.fuelConsumption;
        fin >> car.passengers;
        fin >> ws;
        getline(fin, car.brand);

        cars.push_back(car);
    }

    fin.close();
    return cars;
}

void showCars(const string& filename) {
    vector<Car> cars = readCars(filename);

    if (cars.empty()) {
        cout << "No cars found.\n";
        return;
    }

    for (const auto& car : cars) {
        cout << "\nName: " << car.name << endl;
        cout << "Engine volume: " << car.engineVolume << endl;
        cout << "Fuel consumption: " << car.fuelConsumption << endl;
        cout << "Passengers: " << car.passengers << endl;
        cout << "Brand: " << car.brand << endl;
    }
}

void showMinMaxFuelCars(const string& filename) {
    vector<Car> cars = readCars(filename);

    if (cars.empty()) {
        cout << "No cars found.\n";
        return;
    }

    Car minCar = cars[0];
    Car maxCar = cars[0];

    for (const auto& car : cars) {
        if (car.fuelConsumption < minCar.fuelConsumption)
            minCar = car;

        if (car.fuelConsumption > maxCar.fuelConsumption)
            maxCar = car;
    }

    cout << "\nCar with MIN fuel consumption:\n";
    cout << "Name: " << minCar.name << endl;
    cout << "Brand: " << minCar.brand << endl;
    cout << "Fuel: " << minCar.fuelConsumption << endl;
    cout << "Engine: " << minCar.engineVolume << endl;
    cout << "Passengers: " << minCar.passengers << endl;

    cout << "\nCar with MAX fuel consumption:\n";
    cout << "Name: " << maxCar.name << endl;
    cout << "Brand: " << maxCar.brand << endl;
    cout << "Fuel: " << maxCar.fuelConsumption << endl;
    cout << "Engine: " << maxCar.engineVolume << endl;
    cout << "Passengers: " << maxCar.passengers << endl;
}

int main() {
    string filename = "cars.txt";
    int choice;

    do {
        cout << "\n===== CAR TERMINAL =====\n";
        cout << "1. Add new car\n";
        cout << "2. Show all cars\n";
        cout << "3. Show cars with min/max fuel\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addCar(filename);
            break;
        case 2:
            showCars(filename);
            break;
        case 3:
            showMinMaxFuelCars(filename);
            break;
        case 0:
            cout << "Exit...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}