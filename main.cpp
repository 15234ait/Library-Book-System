#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Base class
class Book {
public:
    string title, author, isbn, dateAdd;
    bool available;
    string type; // "hardcopy" or "ebook"

    void setDetails(string t, string a, string i, bool avail, string date, string bookType) {
        title = t;
        author = a;
        isbn = i;
        available = avail;
        dateAdd = date;
        type = bookType;
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
};

// Derived class: HardcopyBook
class HardcopyBook : public Book {
public:
    string shelfNumber;

    void setShelf(string shelf) {
        shelfNumber = shelf;
    }

    string getShelf() {
        return shelfNumber;
    }
};

// Derived class: EBook
class EBook : public Book {
public:
    string licenseEndDate;

    void setLicense(string license) {
        licenseEndDate = license;
    }

    string getLicense() {
        return licenseEndDate;
    }
};

int main() {
    const int SIZE = 5;
    Book* books[SIZE];

    // Create books
    HardcopyBook* b1 = new HardcopyBook();
    b1->setDetails("The Hobbit", "J.R.R. Tolkien", "111", true, "2023-01-01", "hardcopy");
    b1->setShelf("A-01");

    EBook* b2 = new EBook();
    b2->setDetails("1984", "George Orwell", "222", true, "2023-01-02", "ebook");
    b2->setLicense("2025-12-31");

    HardcopyBook* b3 = new HardcopyBook();
    b3->setDetails("Dune", "Frank Herbert", "333", true, "2023-01-03", "hardcopy");
    b3->setShelf("C-03");

    EBook* b4 = new EBook();
    b4->setDetails("Hamlet", "W. Shakespeare", "444", true, "2023-01-04", "ebook");
    b4->setLicense("2024-06-01");

    HardcopyBook* b5 = new HardcopyBook();
    b5->setDetails("Frankenstein", "M. Shelley", "555", true, "2023-01-05", "hardcopy");
    b5->setShelf("B-02");

    // Add to array
    books[0] = b1;
    books[1] = b2;
    books[2] = b3;
    books[3] = b4;
    books[4] = b5;

    int choice;
    string input;

    while (true) {
        cout << "\n📚 Library Menu:\n";
        cout << "1. Borrow Book\n";
        cout << "2. Return Book\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "\n👋 Exiting... Have a great day!\n";
            break;
        }

        // Show book table
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

            if (books[i]->type == "hardcopy") {
                // Safe cast: we know it's a HardcopyBook
                HardcopyBook* h = static_cast<HardcopyBook*>(books[i]);
                cout << setw(15) << h->getShelf() << endl;
            } else if (books[i]->type == "ebook") {
                EBook* e = static_cast<EBook*>(books[i]);
                cout << setw(15) << e->getLicense() << endl;
            } else {
                cout << setw(15) << "-" << endl;
            }
        }

        // Ask for ISBN
        cout << "\nEnter ISBN: ";
        cin >> input;

        bool found = false;
        for (int i = 0; i < SIZE; i++) {
            if (books[i]->isbn == input) {
                found = true;
                if (choice == 1) {
                    books[i]->borrow();
                } else if (choice == 2) {
                    books[i]->returnBook();
                }
                break;
            }
        }

        if (!found) {
            cout << "\n❌ Book with ISBN " << input << " not found.\n";
        }
    }

    return 0;
}
