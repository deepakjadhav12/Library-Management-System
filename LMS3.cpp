#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool issued;
};

vector<Book> library;

void addBook() {
    Book newBook;
    cout << "Enter Book ID: ";
    cin >> newBook.id;
    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, newBook.title);

    cout << "Enter Author Name: ";
    getline(cin, newBook.author);

    newBook.issued = false;

    library.push_back(newBook);
    cout << "Book added successfully!\n";
}

void printTableHeader() {
    cout << left << setw(10) << "ID" << setw(30) << "Title" << setw(30) 
         << "Author" << setw(10) << "Issued" << endl;
    cout << string(80, '-') << endl;  // Draw a separator line
}

void printBookInfo(const Book& book) {
    cout << left << setw(10) << book.id << setw(30) << book.title 
         << setw(30) << book.author << setw(10) 
         << (book.issued ? "Yes" : "No") << endl;
}

void searchBook() {
    int choice;
    cout << "Search by:\n1. ID\n2. Title\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        int searchId;
        cout << "Enter Book ID to search: ";
        cin >> searchId;

        bool found = false;
        for (const Book& book : library) {
            if (book.id == searchId) {
                printTableHeader();
                printBookInfo(book);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found.\n";
        }

    } else if (choice == 2) {
        string searchTitle;
        cin.ignore();
        cout << "Enter Book Title to search: ";
        getline(cin, searchTitle);

        bool found = false;
        for (const Book& book : library) {
            if (book.title == searchTitle) {
                printTableHeader();
                printBookInfo(book);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found.\n";
        }

    } else {
        cout << "Invalid choice.\n";
    }
}

void issueBook() {
    int bookId;
    cout << "Enter Book ID to issue: ";
    cin >> bookId;

    for (Book& book : library) {
        if (book.id == bookId && !book.issued) {
            book.issued = true;
            cout << "Book issued successfully!\n";
            return;
        }
    }
    cout << "Book not found or already issued.\n";
}

void returnBook() {
    int bookId;
    cout << "Enter Book ID to return: ";
    cin >> bookId;

    for (Book& book : library) {
        if (book.id == bookId && book.issued) {
            book.issued = false;
            cout << "Book returned successfully!\n";
            return;
        }
    }
    cout << "Book not found or not issued.\n";
}

void listBooks() {
    if (library.empty()) {
        cout << "Library is empty.\n";
        return;
    }

    sort(library.begin(), library.end(), [](const Book& a, const Book& b) {
        return a.id < b.id; 
    });

    printTableHeader();

    for (const Book& book : library) {
        printBookInfo(book);
    }
}

void deleteBook() {
    int bookId;
    cout << "Enter Book ID to delete: ";
    cin >> bookId;

    for (auto it = library.begin(); it != library.end(); ++it) {
        if (it->id == bookId) {
            library.erase(it);
            cout << "Book deleted successfully!\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add New Book\n";
        cout << "2. Search for a Book\n";
        cout << "3. Issue a Book\n";
        cout << "4. Return a Book\n";
        cout << "5. List All Books\n";
        cout << "6. Delete a Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                issueBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                listBooks();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
