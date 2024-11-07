#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A structure to store items' weight, value, and value-to-weight ratio
struct Item {
    int value, weight;
    
    // Constructor
    Item(int value, int weight) {
        this->value = value;
        this->weight = weight;
    }
};

// Comparator function to sort items by value-to-weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Function to calculate maximum value in the knapsack
double fractionalKnapsack(int capacity, vector<Item>& items) {
    // Sort items by value-to-weight ratio
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;  // Total value accumulated in the knapsack
    int n = items.size();

    // Loop through each item
    for (int i = 0; i < n; i++) {
        // If the item can fit in the knapsack, take it fully
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            // Take the fraction of the remaining item that fits
            totalValue += items[i].value * ((double)capacity / items[i].weight);
            break; // The knapsack is now full
        }
    }

    return totalValue;
}

int main() {
    int n;
    int capacity;

    // User input for number of items
    cout << "Enter the number of items: ";
    cin >> n;

    // Vector to store all items
    vector<Item> items;

    // User input for items' values and weights
    for (int i = 0; i < n; i++) {
        int value, weight;
        cout << "Enter value and weight for item " << i + 1 << ": ";
        cin >> value >> weight;
        items.push_back(Item(value, weight));
    }

    // User input for knapsack capacity
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    // Calculate and print the maximum value for the fractional knapsack
    double maxValue = fractionalKnapsack(capacity, items);
    cout << "Maximum value we can obtain = " << maxValue << endl;

    return 0;
}
