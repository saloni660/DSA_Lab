#include <iostream>
using namespace std;

class HashTable
{
public:
    int arr[10][2];

    HashTable()
    {
        for (int j = 0; j < 10; j++)
        {
            arr[j][0] = -1;
            arr[j][1] = -1;
        }
    }

    int hash(int value)
    {
        return value % 10;
    }

    bool isFull()
    {
        for (int i = 0; i < 10; i++)
        {
            if (arr[i][0] == -1)
            {
                return false;
            }
        }
        return true;
    }

    void insert(int n)
    {
        int loc = hash(n);
        if (isFull())
        {
            cout << "Hash Table is full, cannot insert " << n << endl;
            return;
        }
        else
        {
            if (arr[loc][0] == -1)
            {
                arr[loc][0] = n;
                cout << "Inserted " << n << " at index " << loc << endl;
            }
            else if (arr[loc][0] % 10 != loc)
            {
                for (int i = loc; i < loc + 10; i++)
                {
                    int j = i % 10;
                    if (arr[j][0] == -1)
                    {
                        arr[j][0] = arr[loc][0];
                        arr[j][1] = arr[loc][1];
                        for (int i = 0; i < 10; i++)
                        {
                            if (arr[i][1] == loc)
                            {
                                arr[i][1] = j;
                            }
                        }
                        break;
                    }
                }
                arr[loc][0] = n;
                arr[loc][1] = -1;
                return;
            }
            else if (arr[loc][0] % 10 == loc)
            {
                while (arr[loc][1] != -1)
                {
                    loc = arr[loc][1];
                }
                for (int i = loc; i < loc + 10; i++)
                {
                    int j = i % 10;
                    if (arr[j][0] == -1)
                    {
                        arr[j][0] = n;
                        arr[loc][1] = j;
                        return;
                    }
                }
            }
        }
    }

    void display()
    {
        cout << "Ind Key Chain" << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << i << " " << arr[i][0] << " " << arr[i][1] << endl;
        }
    }
};

int main()
{
    HashTable table;
    int choice, value;

    while (true)
    {
        cout << "Menu:\n";
        cout << "1. Insert value\n";
        cout << "2. Display array\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            table.insert(value);
            break;
        case 2:
            table.display();
            break;
        case 3:
            return 0;
        default:
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}