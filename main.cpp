#include <iostream>   // lets us use cout and cin for input/output
#include <string>     // lets us use the string type
#include <iomanip>    // lets us line up columns with setw and left
#include <sstream>    // helps convert text into dates
#include <ctime>      // lets us work with dates and times
using namespace std;

// A basic Book class that holds book info
class Book {
public:
    string title;     // book title
    string author;    // book author
    string isbn;      // book ISBN number (must be unique)
    string dateAdd;   // date the book was added
    bool available;   // is the book available to borrow?
    string type;      // either "hardcopy" or "ebook"

    // Fill in all the book details at once
    void setDetails(
        string t, string a, string i,
        bool avail, string date,
        string bookType
    ) {
        title     = t;
        author    = a;
        isbn      = i;
        available = avail;
        dateAdd   = date;
        type      = bookType;
    }

    // Print one line about this book
    void displayRow() {
        cout << left
             << setw(20) << title
             << setw(20) << author
             << setw(10) << isbn
             << setw(10) << (available ? "Yes" : "No")
             << setw(12) << dateAdd;
    }

    // Borrow this book if it's available
    void borrow() {
        if (available) {
            available = false;
            cout << "\nYou have borrowed the book.\n";
        } else {
            cout << "\nSorry, that book is already borrowed.\n";
        }
    }

    // Return this book if it was borrowed
    void returnBook() {
        if (!available) {
            available = true;
            cout << "\nYou have returned the book.\n";
        } else {
            cout << "\nThat book was not borrowed.\n";
        }
    }
};

// A hardcopy book adds a shelf number
class HardcopyBook : public Book {
public:
    string shelfNumber;
    void   setShelf(string shelf) { shelfNumber = shelf; }
    string getShelf()             { return shelfNumber; }
};

// An ebook adds a license end date
class EBook : public Book {
public:
    string licenseEndDate;
    void   setLicense(string license) { licenseEndDate = license; }
    string getLicense()               { return licenseEndDate; }
};

// Check if a string contains only digits
bool isNumeric(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Try to read a YYYY-MM-DD date into a tm struct
bool parseDate(const string& dateStr, tm& dateTm) {
    istringstream ss(dateStr);
    ss >> get_time(&dateTm, "%Y-%m-%d");
    return !ss.fail();  // false if parsing failed
}

// Simple bubble sort of books by their ISBN
void sortBooks(Book* books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (books[j]->isbn > books[j + 1]->isbn) {
                Book* temp   = books[j];
                books[j]     = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

// Show a list of all books in a table
void displayAllBooks(Book* books[], int SIZE) {
    cout << "\nBook List:\n";
    cout << "==========================================================================================\n";
    cout << left
         << setw(20) << "Title"
         << setw(20) << "Author"
         << setw(10) << "ISBN"
         << setw(10) << "Available"
         << setw(12) << "Date Added"
         << setw(15) << "Extra Info" << endl;
    cout << "------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < SIZE; i++) {
        books[i]->displayRow();
        if (books[i]->type == "hardcopy") {
            cout << setw(15)
                 << static_cast<HardcopyBook*>(books[i])->getShelf()
                 << endl;
        } else {
            cout << setw(15)
                 << static_cast<EBook*>(books[i])->getLicense()
                 << endl;
        }
    }
}

int main() {
    const int MAX = 100;
    Book* books[MAX];
    int   SIZE = 5;

    // Start with 5 books already in the library
    books[0] = new HardcopyBook();
    books[0]->setDetails(
        "The Hobbit", "J.R.R. Tolkien", "111",
        true, "2023-01-01", "hardcopy"
    );
    static_cast<HardcopyBook*>(books[0])->setShelf("A-01");

    books[1] = new EBook();
    books[1]->setDetails(
        "1984", "George Orwell", "222",
        true, "2023-01-02", "ebook"
    );
    static_cast<EBook*>(books[1])->setLicense("2025-12-31");

    books[2] = new HardcopyBook();
    books[2]->setDetails(
        "Dune", "Frank Herbert", "333",
        true, "2023-01-03", "hardcopy"
    );
    static_cast<HardcopyBook*>(books[2])->setShelf("C-03");

    books[3] = new EBook();
    books[3]->setDetails(
        "Hamlet", "W. Shakespeare", "444",
        true, "2023-01-04", "ebook"
    );
    static_cast<EBook*>(books[3])->setLicense("2024-06-01");

    books[4] = new HardcopyBook();
    books[4]->setDetails(
        "Frankenstein", "M. Shelley", "555",
        true, "2023-01-05", "hardcopy"
    );
    static_cast<HardcopyBook*>(books[4])->setShelf("B-02");

    int    choice;
    string input;

    // Keep showing the menu until the user exits
    while (true) {
        cout << "\n========== LIBRARY MENU ==========\n";
        cout << "1- List all Books\n";
        cout << "2- Borrow a Book\n";
        cout << "3- Return a Book\n";
        cout << "4- Add a new Book\n";
        cout << "5- Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 5) {
            cout << "\nGoodbye!\n";
            break;
        }

        if (choice == 1) {
            // Option 1: list every book
            displayAllBooks(books, SIZE);
        }
        else if (choice == 2 || choice == 3) {
            // Option 2 or 3: show books, then borrow/return
            displayAllBooks(books, SIZE);
            cout << "\nEnter ISBN: ";
            cin >> input;
            bool found = false;
            for (int i = 0; i < SIZE; i++) {
                if (books[i]->isbn == input) {
                    if (choice == 2)
                        books[i]->borrow();
                    else
                        books[i]->returnBook();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\nThat ISBN wasn't found in the list.\n";
            }
        }
        else if (choice == 4) {
            // Option 4: add a brand-new book
            cin.ignore(); // clear leftover newline
            string title, author, isbn, date, type;
            bool   avail;

            cout << "\nAdd New Book\n";
            cout << "Title: "; getline(cin, title);
            cout << "Author: "; getline(cin, author);
            cout << "ISBN: "; getline(cin, isbn);

            // Must be only digits
            if (!isNumeric(isbn)) {
                cout << "\nISBN must be numbers only.\n";
                continue;
            }
            // Must not already exist
            bool duplicate = false;
            for (int i = 0; i < SIZE; i++) {
                if (books[i]->isbn == isbn) {
                    duplicate = true;
                    break;
                }
            }
            if (duplicate) {
                cout << "\nThat ISBN is already in use.\n";
                continue;
            }

            cout << "Date Added (YYYY-MM-DD): "; cin >> date;
            tm addTm = {};
            if (!parseDate(date, addTm)) {
                cout << "\nPlease use the date format YYYY-MM-DD.\n";
                continue;
            }

            cout << "Available? (1 = Yes, 0 = No): "; cin >> avail;
            cout << "Type (hardcopy or ebook): "; cin >> type;

            if (type == "hardcopy") {
                string shelf;
                cout << "Shelf Number: "; cin >> shelf;
                HardcopyBook* newBook = new HardcopyBook();
                newBook->setDetails(title, author, isbn, avail, date, type);
                newBook->setShelf(shelf);
                books[SIZE++] = newBook;
                sortBooks(books, SIZE);
            }
            else if (type == "ebook") {
                string license;
                cout << "License End Date (YYYY-MM-DD): "; cin >> license;
                tm licTm = {};
                if (!parseDate(license, licTm)) {
                    cout << "\nPlease use the date format YYYY-MM-DD.\n";
                    continue;
                }
                EBook* newBook = new EBook();
                newBook->setDetails(title, author, isbn, avail, date, type);
                newBook->setLicense(license);
                books[SIZE++] = newBook;
                sortBooks(books, SIZE);
            }
            else {
                cout << "\nType must be 'hardcopy' or 'ebook'.\n";
            }
        }
        else {
            cout << "\nPlease choose a valid option.\n";
        }
    }

    return 0;
}
