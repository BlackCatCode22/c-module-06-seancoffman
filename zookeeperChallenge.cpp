// Zookeeper's Challenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Sean Coffman

#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

class Animal {
public:
    Animal(int age, const string& sex, const string& color, int weight, const string& origin)
        : age(age), sex(sex), color(color), weight(weight), origin(origin) {
        arrivalDate = getCurrentDate();
    }

    virtual ~Animal() {}

    virtual void genUniqueID(int id) { uniqueID = id; }
    virtual void setName(const string& name) { animalName = name; }
    virtual void genBirthDay(int age) {
        birthDate = calculateBirthDate(age);
    }

    // Output animal details in the required format
    virtual void outputDetails(ofstream& out) const {
        out << animalName << "; " << birthDate << "; " << color << " color; "
            << sex << "; " << weight << " pounds; from " << origin << "; "
            << "arrived " << arrivalDate << endl;
    }

protected:
    int age;
    string sex;
    string color;
    int weight;
    string origin;
    string birthDate;
    string animalName;
    int uniqueID;
    string arrivalDate;

    // Get the current date as a string
    string getCurrentDate() const {
        time_t now = time(0);
        tm ltm; // Declare tm structure
        localtime_s(&ltm, &now); // Use localtime_s to fill the structure

        return to_string(1900 + ltm.tm_year) + "-" +
            to_string(1 + ltm.tm_mon) + "-" +
            to_string(ltm.tm_mday);
    }

    // Calculate birth date based on age
    string calculateBirthDate(int age) const {
        int birthYear = 2024 - age; // Using 2024 as the current year for calculation
        return to_string(birthYear) + "-03-15"; // Placeholder birth date
    }
};

class Hyena : public Animal {
public:
    Hyena(int age, const string& sex, const string& color, int weight, const string& origin)
        : Animal(age, sex, color, weight, origin) {}
};

class Lion : public Animal {
public:
    Lion(int age, const string& sex, const string& color, int weight, const string& origin)
        : Animal(age, sex, color, weight, origin) {}
};

class Tiger : public Animal {
public:
    Tiger(int age, const string& sex, const string& color, int weight, const string& origin)
        : Animal(age, sex, color, weight, origin) {}
};

class Bear : public Animal {
public:
    Bear(int age, const string& sex, const string& color, int weight, const string& origin)
        : Animal(age, sex, color, weight, origin) {}
};

// Utility function to trim whitespace from strings
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void processArrivingAnimals(const string& fileName, vector<Animal*>& animals) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    int hyenaCount = 1, lionCount = 1, tigerCount = 1, bearCount = 1;

    while (getline(file, line)) {
        stringstream ss(line);
        int age, weight;
        string sex, species, season, color, origin;

        // Read age and the word "year" and "old" together
        if (!(ss >> age)) {
            continue; // Skip this line if parsing fails
        }
        string yearStr;
        ss >> yearStr >> yearStr; // Read "year old"

        // Read sex
        ss >> sex;
        // Validate sex
        if (sex != "male" && sex != "female") {
            continue; // Skip this line
        }

        // Read species
        getline(ss, species, ',');
        species = trim(species);
        // Validate species
        if (species != "hyena" && species != "lion" && species != "tiger" && species != "bear") {
            continue; // Skip this line
        }

        // Read remaining attributes
        getline(ss, season, ',');
        season = trim(season);
        getline(ss, color, ',');
        color = trim(color);
        if (!(ss >> weight)) { // Read weight
            continue; // Skip this line if parsing fails
        }
        ss.ignore(1000, ' '); // Ignore "pounds"
        getline(ss, origin);
        origin = trim(origin);

        Animal* animal = nullptr;

        // Determine the species and assign unique IDs
        if (species == "hyena") {
            animal = new Hyena(age, sex, color, weight, origin);
            animal->setName("Hy" + string(2 - to_string(hyenaCount).length(), '0') + to_string(hyenaCount++));
        }
        else if (species == "lion") {
            animal = new Lion(age, sex, color, weight, origin);
            animal->setName("Li" + string(2 - to_string(lionCount).length(), '0') + to_string(lionCount++));
        }
        else if (species == "tiger") {
            animal = new Tiger(age, sex, color, weight, origin);
            animal->setName("Ti" + string(2 - to_string(tigerCount).length(), '0') + to_string(tigerCount++));
        }
        else if (species == "bear") {
            animal = new Bear(age, sex, color, weight, origin);
            animal->setName("Be" + string(2 - to_string(bearCount).length(), '0') + to_string(bearCount++));
        }

        if (animal) {
            animal->genBirthDay(age); // Call to generate the birth date
            animals.push_back(animal);
        }
    }
}

// Function to output animal details to a file
void outputAnimalsToFile(const string& filename, const vector<Animal*>& animals) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error opening output file: " << filename << endl;
        return;
    }

    for (const Animal* animal : animals) {
        animal->outputDetails(out);
    }

    out.close();
}

int main() {
    vector<Animal*> animals;
    processArrivingAnimals("arrivingAnimals.txt", animals);

    // Output all animals to a file
    outputAnimalsToFile("zooPopulation.txt", animals);

    // Clean up
    for (Animal* animal : animals) {
        delete animal;
    }

    return 0;
}