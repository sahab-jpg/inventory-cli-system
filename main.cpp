#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

void displayMenu() {
    cout << "\n==============================\n";
    cout << "   LOCAL INVENTORY & BILLING  \n";
    cout << "==============================\n";
    cout << "1. Add New Product\n";
    cout << "2. View All Products\n";
    cout << "3. Search Product\n";
    cout << "4. Generate Bill\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<Product> inventory;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                Product p;
                p.id = inventory.size() + 1;
                cout << "Enter product name: ";
                cin >> p.name;
                cout << "Enter price: ";
                cin >> p.price;
                cout << "Enter stock quantity: ";
                cin >> p.quantity;
                
                inventory.push_back(p);
                cout << "[SUCCESS] Product added with ID: " << p.id << "\n";
                break;
            }
            case 2: {
                if (inventory.empty()) {
                    cout << "Inventory is empty!\n";
                    break;
                }
                cout << "\n--- CURRENT INVENTORY ---\n";
                cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Price" << setw(10) << "Stock" << endl;
                cout << "------------------------------------\n";
                for (const auto& p : inventory) {
                    cout << left << setw(5) << p.id 
                         << setw(15) << p.name 
                         << "$" << setw(9) << p.price 
                         << setw(10) << p.quantity << endl;
                }
                break;
            }
            case 3: {
                string searchName;
                cout << "Enter product name to search: ";
                cin >> searchName;
                bool found = false;
                for (const auto& p : inventory) {
                    if (p.name == searchName) {
                        cout << "Found -> ID: " << p.id << " | Price: $" << p.price << " | Stock: " << p.quantity << "\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Product not found.\n";
                break;
            }
            case 4: {
                int id, qty;
                double total = 0.0;
                cout << "--- BILLING COUNTER ---\n";
                char more;
                do {
                    cout << "Enter Product ID to buy: ";
                    cin >> id;
                    if (id > 0 && id <= inventory.size()) {
                        cout << "Enter quantity: ";
                        cin >> qty;
                        if (qty <= inventory[id - 1].quantity) {
                            double cost = inventory[id - 1].price * qty;
                            total += cost;
                            inventory[id - 1].quantity -= qty; // Reduce stock
                            cout << "Added " << qty << "x " << inventory[id - 1].name << " ($" << cost << ")\n";
                        } else {
                            cout << "[ERROR] Not enough stock available!\n";
                        }
                    } else {
                        cout << "[ERROR] Invalid Product ID.\n";
                    }
                    cout << "Add another item? (y/n): ";
                    cin >> more;
                } while (more == 'y' || more == 'Y');
                
                cout << "==============================\n";
                cout << "TOTAL BILL: $" << total << "\n";
                cout << "==============================\n";
                break;
            }
            case 5:
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
