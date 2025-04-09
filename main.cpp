#include <iostream>
#include <string>
#include <iomanip> // for setw
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
             << setw(12) << dateAdd << endl;
    }

    void borrow() {
        if (available) {
            available = false;
            cout << "\n✅ Book borrowed successfully!\n";
        } else {
            cout << "\n❌ Sorry, this book is not available.\n";
        }
    }
};

int main() {
    const int SIZE = 5;
    Book books[SIZE];

    books[0].setDetails("The Hobbit", "J.R.R. Tolkien", "111", true, "2023-01-01");
    books[1].setDetails("1984", "George Orwell", "222", true, "2023-01-02");
    books[2].setDetails("Dune", "Frank Herbert", "333", true, "2023-01-03");
    books[3].setDetails("Hamlet", "W. Shakespeare", "444", true, "2023-01-04");
    books[4].setDetails("Frankenstein", "M. Shelley", "555", true, "2023-01-05");

    cout << "\n📚 Welcome to the Library 📚\n";
    cout << "===================================================================\n";
    cout << left << setw(20) << "Title"
         << setw(20) << "Author"
         << setw(10) << "ISBN"
         << setw(10) << "Available"
         << setw(12) << "Date Added" << endl;
    cout << "-------------------------------------------------------------------\n";

    for (int i = 0; i < SIZE; i++) {
        books[i].displayRow();
    }

    string input;
    while (true) {
        cout << "\n🔍 Enter ISBN to borrow a book (or 0 to exit): ";
        cin >> input;

        if (input == "0") {
            cout << "\n👋 Exiting... Have a great day!\n";
            break;
        }

        bool found = false;
        for (int i = 0; i < SIZE; i++) {
            if (books[i].isbn == input) {
                found = true;
                books[i].borrow();
                break;
            }
        }

        if (!found) {
            cout << "\n❌ Book with ISBN " << input << " not found.\n";
        }
    }

    return 0;
}
