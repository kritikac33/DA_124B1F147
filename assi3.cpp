#include <iostream>
#include <algorithm>
using namespace std;

struct Item
{
    string name;
    float weight;
    float value;
    bool divisible;
    float ratio;
};

bool compare(Item a, Item b)
{
    return a.ratio > b.ratio;
}

int main()
{
    int n;
    float capacity;

    cout << "Enter number of items: ";
    cin >> n;

    Item items[20];

    // Input
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter details of item " << i + 1 << ":\n";

        cout << "Name: ";
        cin >> items[i].name;

        cout << "Weight: ";
        cin >> items[i].weight;

        cout << "Value: ";
        cin >> items[i].value;

        int choice;
        cout << "Divisible? (1 = Yes, 0 = No): ";
        cin >> choice;

        items[i].divisible = (choice == 1);

        // Calculate value/weight ratio
        items[i].ratio = items[i].value / items[i].weight;
    }

    cout << "\nEnter boat capacity: ";
    cin >> capacity;

    // Sort items according to value/weight ratio
    sort(items, items + n, compare);

    float totalValue = 0;
    float totalWeight = 0;

    cout << "\n--- Selected Items ---\n";

    // Greedy selection
    for (int i = 0; i < n; i++)
    {
        if (capacity == 0)
            break;

        // If complete item fits
        if (items[i].weight <= capacity)
        {
            capacity = capacity - items[i].weight;
            totalWeight = totalWeight + items[i].weight;
            totalValue = totalValue + items[i].value;

            cout << items[i].name << " -> Full item selected\n";
        }

        // If item does not completely fit
        else
        {
            // Take fraction only if item is divisible
            if (items[i].divisible)
            {
                float fraction = capacity / items[i].weight;

                totalValue = totalValue + (fraction * items[i].value);
                totalWeight = totalWeight + capacity;

                cout << items[i].name << " -> "
                     << fraction * 100
                     << "% selected\n";

                capacity = 0;
            }
            else
            {
                cout << items[i].name
                     << " -> Skipped (indivisible)\n";
            }
        }
    }

    cout << "\n--- Final Result ---\n";
    cout << "Total Weight Carried = " << totalWeight << " kg\n";
    cout << "Maximum Utility = " << totalValue << " units\n";
    return 0;
}
