#include <iostream>   // for input/output (cin, cout)
#include <string>     // for std::string type
#include <iomanip>    // for std::setw to format columns
using namespace std;

// Check if a string contains only digits (used for ISBN)
bool isNumeric(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Very basic date-format check: YYYY-MM-DD
bool isValidDate(const string& s) {
    // Must be 10 chars, with '-' at positions 4 and 7
    if (s.size() != 10 || s[4] != '-' || s[7] != '-') return false;
    // All other positions must be digits
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(s[i])) return false;
    }
    return true;
}

// Base Book class: holds common book data and actions
class Book {
public:
    string title;      // title of book
    string author;     // author name
    string isbn;       // unique numeric identifier
    string dateAdded;  // when it was added
    bool available;    // true if not borrowed
    string type;       // "hardcopy" or "ebook"

    // fill in all fields at once
    void setDetails(string t, string a, string i, bool avail,
                    string date, string tp) {
        title = t;
        author = a;
        isbn = i;
        available = avail;
        dateAdded = date;
        type = tp;
    }

    // print one line of the table for this book
    void displayRow() {
        cout << left
             << setw(20) << title
             << setw(20) << author
             << setw(10) << isbn
             << setw(10) << (available ? "Yes" : "No")
             << setw(12) << dateAdded;
    }

    // borrow the book if available
    void borrow() {
        if (available) {
            available = false;
            cout << "\nBook borrowed.\n";
        } else {
            cout << "\nAlready borrowed.\n";
        }
    }

    // return the book if it was borrowed
    void returnBook() {
        if (!available) {
            available = true;
            cout << "\nBook returned.\n";
        } else {
            cout << "\nWas not borrowed.\n";
        }
    }
};

// Hardcopy book adds a shelf number
class HardcopyBook : public Book {
public:
    string shelf;
    void setShelf(string s) { shelf = s; }
};

// EBook adds a license end date
class EBook : public Book {
public:
    string licenseDate;
    void setLicense(string d) { licenseDate = d; }
};

// simple bubble sort by ISBN (ascending)
void sortBooks(Book* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j]->isbn > arr[j + 1]->isbn) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// display all books in a neat table
void showAll(Book* arr[], int n) {
    cout << "\nBook List:\n"
         << "==============================================================\n"
         << left << setw(20) << "Title"
         << setw(20) << "Author"
         << setw(10) << "ISBN"
         << setw(10) << "Avail."
         << setw(12) << "Date Added"
         << setw(12) << "Extra Info" << "\n"
         << "--------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        arr[i]->displayRow();
        // show shelf or license depending on type
        if (arr[i]->type == "hardcopy") {
            cout << setw(12) << static_cast<HardcopyBook*>(arr[i])->shelf;
        } else {
            cout << setw(12) << static_cast<EBook*>(arr[i])->licenseDate;
        }
        cout << "\n";
    }
}

int main() {
    const int MAX = 100;
    Book* books[MAX];
    int   size = 5;  // current number of books

    // preload 5 sample books
    books[0] = new HardcopyBook();
    books[0]->setDetails("The Hobbit", "Tolkien", "111", true, "2023-01-01", "hardcopy");
    static_cast<HardcopyBook*>(books[0])->setShelf("A1");

    books[1] = new EBook();
    books[1]->setDetails("1984", "Orwell", "222", true, "2023-01-02", "ebook");
    static_cast<EBook*>(books[1])->setLicense("2025-12-31");

    books[2] = new HardcopyBook();
    books[2]->setDetails("Dune", "Herbert", "333", true, "2023-01-03", "hardcopy");
    static_cast<HardcopyBook*>(books[2])->setShelf("C3");

    books[3] = new EBook();
    books[3]->setDetails("Hamlet", "Shakespeare", "444", true, "2023-01-04", "ebook");
    static_cast<EBook*>(books[3])->setLicense("2024-06-01");

    books[4] = new HardcopyBook();
    books[4]->setDetails("Frankenstein", "Shelley", "555", true, "2023-01-05", "hardcopy");
    static_cast<HardcopyBook*>(books[4])->setShelf("B2");

    while (true) {
        // show menu
        cout << "\nMENU\n"
             << "1- List all Books\n"
             << "2- Borrow a Book\n"
             << "3- Return a Book\n"
             << "4- Add a new Book\n"
             << "5- Exit\n"
             << "Choose: ";

        int choice;
        if (!(cin >> choice)) {
            // invalid input
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter a number 1–5.\n";
            continue;
        }

        if (choice == 5) {
            cout << "Goodbye!\n";
            break;
        }

        if (choice == 1) {
            // list all books
            showAll(books, size);
        }
        else if (choice == 2 || choice == 3) {
            // borrow or return
            showAll(books, size);
            string isbn;
            while (true) {
                cout << "Enter ISBN: ";
                cin >> isbn;
                bool ok = false;
                for (int i = 0; i < size; i++) {
                    if (books[i]->isbn == isbn) {
                        if (choice == 2) books[i]->borrow();
                        else            books[i]->returnBook();
                        ok = true;
                        break;
                    }
                }
                if (ok) break;
                cout << "Not found, try again.\n";
            }
        }
        else if (choice == 4) {
            // add new book
            cin.ignore(1000, '\n');
            string title, author, isbn, date, type;
            bool avail;

            cout << "Add New Book\n";
            cout << "Title: ";   getline(cin, title);
            cout << "Author: ";  getline(cin, author);

            // ISBN: digits only + unique
            while (true) {
                cout << "ISBN (digits only): ";
                getline(cin, isbn);
                if (!isNumeric(isbn)) {
                    cout << "Must be digits.\n"; continue;
                }
                bool dup = false;
                for (int i = 0; i < size; i++)
                    if (books[i]->isbn == isbn) { dup = true; break; }
                if (dup) { cout << "That ISBN exists.\n"; continue; }
                break;
            }

            // date added
            while (true) {
                cout << "Date Added (YYYY-MM-DD): ";
                getline(cin, date);
                if (!isValidDate(date)) {
                    cout << "Format YYYY-MM-DD.\n"; continue;
                }
                break;
            }

            // availability
            while (true) {
                cout << "Available? (1=Yes,0=No): ";
                if (cin >> avail && (avail==0||avail==1)) {
                    cin.ignore(1000, '\n');
                    break;
                }
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter 1 or 0.\n";
            }

            // type
            while (true) {
                cout << "Type (hardcopy/ebook): ";
                getline(cin, type);
                if (type=="hardcopy"||type=="ebook") break;
                cout << "Enter hardcopy or ebook.\n";
            }

            // create and add
            if (type == "hardcopy") {
                string shelf;
                cout << "Shelf: "; getline(cin, shelf);
                auto b = new HardcopyBook();
                b->setDetails(title,author,isbn,avail,date,type);
                b->setShelf(shelf);
                books[size++] = b;
            } else {
                string lic;
                while (true) {
                    cout << "License End (YYYY-MM-DD): ";
                    getline(cin, lic);
                    if (!isValidDate(lic)) {
                        cout << "Format YYYY-MM-DD.\n"; continue;
                    }
                    break;
                }
                auto b = new EBook();
                b->setDetails(title,author,isbn,avail,date,type);
                b->setLicense(lic);
                books[size++] = b;
            }

            sortBooks(books, size);
            cout << "Book added.\n";
        }
        else {
            cout << "Choose 1–5.\n";
        }
    }

    return 0;
}
