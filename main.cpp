#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Book {
public:
    string title, author, isbn, dateAdd;
    bool available;

    void setDetails(string t, string a, string i, bool avail, string date) {
        title = t;
        author = a;
        isbn = i;
        available = avail;
        dateAdd = date;
    }

    void displayRow() {
        cout << left << setw(20) << title
             << setw(20) << author
             << setw(10) << isbn
             << setw(10) << (available ? "Yes" : "No")
             << setw(12) << dateAdd;
    }

    void borrow() {
        if (available) {
            available = false;
            cout << "\n✅ Book borrowed successfully!\n";
        } else {
            cout << "\n❌ This book is already borrowed.\n";
        }
    }

    void returnBook() {
        if (!available) {
            available = true;
            cout << "\n🔁 Book returned successfully!\n";
        } else {
            cout << "\n❗ This book is already available.\n";
        }
    }

    // Virtual so derived can override
    virtual void displayExtra() {
        cout << setw(15) << "-" << endl;
    }
};

class HardcopyBook : public Book {
public:
    string shelfNumber;

    void setShelf(string shelf) {
        shelfNumber = shelf;
    }

    void displayExtra() override {
        cout << setw(15) << shelfNumber << endl;
    }
};

class EBook : public Book {
public:
    string licenseEndDate;

    void setLicense(string license) {
        licenseEndDate = license;
    }

    void displayExtra() override {
        cout << setw(15) << licenseEndDate << endl;
    }
};

// Bubble sort function for Book* array (by ISBN)
void sortBooksByISBN(Book* books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (books[j]->isbn > books[j + 1]->isbn) {
                // Swap
                Book* temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

int main() {
    const int SIZE = 5;
    Book* books[SIZE];

    // Add hardcopy and ebook objects
    books[0] = new HardcopyBook();
    books[0]->setDetails("The Hobbit", "J.R.R. Tolkien", "111", true, "2023-01-01");
    ((HardcopyBook*)books[0])->setShelf("A-01");

    books[1] = new EBook();
    books[1]->setDetails("1984", "George Orwell", "222", true, "2023-01-02");
    ((EBook*)books[1])->setLicense("2025-12-31");

    books[2] = new HardcopyBook();
    books[2]->setDetails("Dune", "Frank Herbert", "333", true, "2023-01-03");
    ((HardcopyBook*)books[2])->setShelf("B-03");

    books[3] = new EBook();
    books[3]->setDetails("Hamlet", "Shakespeare", "444", true, "2023-01-04");
    ((EBook*)books[3])->setLicense("2024-06-01");

    books[4] = new HardcopyBook();
    books[4]->setDetails("Frankenstein", "M. Shelley", "555", true, "2023-01-05");
    ((HardcopyBook*)books[4])->setShelf("C-02");

    int choice;
    string input;

    while (true) {
        cout << "\n📚 Library Menu:\n";
        cout << "1. Borrow Book\n";
        cout << "2. Return Book\n";
        cout << "3. Sort Books by ISBN\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "\n👋 Goodbye!\n";
            break;
        }

        if (choice == 3) {
            sortBooksByISBN(books, SIZE);
            cout << "\n✅ Books sorted by ISBN.\n";
        }

        cout << "\nAvailable Books:\n";
        cout << "===========================================================================================\n";
        cout << left << setw(20) << "Title"
             << setw(20) << "Author"
             << setw(10) << "ISBN"
             << setw(10) << "Available"
             << setw(12) << "Date Added"
             << setw(15) << "Extra Info" << endl;
        cout << "-------------------------------------------------------------------------------------------\n";

        for (int i = 0; i < SIZE; i++) {
            books[i]->displayRow();
            books[i]->displayExtra();
        }

        if (choice == 1 || choice == 2) {
            cout << "\nEnter ISBN: ";
            cin >> input;

            bool found = false;
            for (int i = 0; i < SIZE; i++) {
                if (books[i]->isbn == input) {
                    found = true;
                    if (choice == 1) books[i]->borrow();
                    else if (choice == 2) books[i]->returnBook();
                    break;
                }
            }

            if (!found) {
                cout << "\n❌ Book not found.\n";
            }
        }
    }

    return 0;
}
