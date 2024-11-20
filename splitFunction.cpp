// splitFunction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Function to split a string based on a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens; // Vector to hold the split elements
    stringstream ss(str); // Use a stringstream to parse the string
    string token;
    // Split the string using the delimiter
    while (getline(ss, token, delimiter)) {
        if (!token.empty()) { // Avoid adding empty tokens
            tokens.push_back(token);
        }
    }
    return tokens; // Return the vector of tokens
}
int main() {
    string data = "4 year old female hyena, born in spring, tan color, 70 pounds, from Friguia Park, Tunisia";
    // Split the data using comma as the delimiter
    vector<string> result = split(data, ',');
    // Print the results
    for (const auto& element : result) {
        cout << element << endl;
    }
    return 0;
}