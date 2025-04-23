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
             << setw(12) << dateAdd << endl;
    }
};

// Bubble sort (by ISBN)
void sortBooks(Book books[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (books[j].isbn > books[j + 1].isbn) {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

// Print helper
void printBooks(Book books[], int size) {
    for (int i = 0; i < size; i++) {
        books[i].displayRow();
    }
}

int main() {
    cout << "✅ Correct Book Initialization:\n";
    Book b1, b2, b3;
    b1.setDetails("The Hobbit", "J.R.R. Tolkien", "111", true, "2023-01-01");
    b2.setDetails("1984", "George Orwell", "222", false, "2023-01-02");
    b3.setDetails("Dune", "Frank Herbert", "333", true, "2023-01-03");
    b1.displayRow(); b2.displayRow(); b3.displayRow();

    cout << "\n❌ Incorrect Book Initialization:\n";
    Book w1, w2, w3;
    w1.setDetails("", "", "ABC", true, "not-a-date");
    w2.setDetails("???", "!!!", "", false, "");
    w3.setDetails("Book", "Author", "", false, "??/??/????");
    w1.displayRow(); w2.displayRow(); w3.displayRow();

    // ASCENDING SORT TEST
    cout << "\n📚 Ascending Sort Test (before):\n";
    Book asc[3];
    asc[0].setDetails("C Book", "Author C", "333", true, "2023-01-03");
    asc[1].setDetails("A Book", "Author A", "111", true, "2023-01-01");
    asc[2].setDetails("B Book", "Author B", "222", true, "2023-01-02");
    printBooks(asc, 3);

    sortBooks(asc, 3);
    cout << "📚 Ascending Sort Test (after):\n";
    printBooks(asc, 3);

    // DESCENDING SORT TEST
    cout << "\n📚 Descending Sort Test (before):\n";
    Book desc[3];
    desc[0].setDetails("A Book", "Author A", "111", true, "2023-01-01");
    desc[1].setDetails("C Book", "Author C", "333", true, "2023-01-03");
    desc[2].setDetails("B Book", "Author B", "222", true, "2023-01-02");
    printBooks(desc, 3);

    sortBooks(desc, 3);
    cout << "📚 Descending Sort Test (after):\n";
    printBooks(desc, 3);

    // MIXED SORT TEST
    cout << "\n📚 Mixed Sort Test (before):\n";
    Book mix[3];
    mix[0].setDetails("B Book", "Author B", "222", true, "2023-01-02");
    mix[1].setDetails("A Book", "Author A", "111", true, "2023-01-01");
    mix[2].setDetails("C Book", "Author C", "333", true, "2023-01-03");
    printBooks(mix, 3);

    sortBooks(mix, 3);
    cout << "📚 Mixed Sort Test (after):\n";
    printBooks(mix, 3);

    return 0;
}
