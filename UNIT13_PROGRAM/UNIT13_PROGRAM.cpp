/*
 * Talha Arda Boz
 * 11/27/2025
 * UNIT13_PROGRAM - Library Inventory System with Operator Overloading and Templates
 * This program demonstrates mastery of operator overloading, templates, and dynamic memory
 * management in C++ by implementing a menu-driven library inventory system that manages book
 * objects. The program showcases proper use of the Book class with overloaded operators
 * (<<, >>, ==, ++), function templates, class templates, friend functions, and file I/O for
 * persistent storage. Features include loading books from file, displaying all books,
 * adding new books, comparing books, increasing stock, and template demonstrations.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

// ========== FUNCTION TEMPLATE: maxValue ==========
template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

// ========== CLASS TEMPLATE: Box ==========
template <typename T>
class Box {
private:
    T value;

public:
    Box() : value(T()) {}

    Box(T val) : value(val) {}

    void setValue(T val) {
        value = val;
    }

    T getValue() const {
        return value;
    }

    void display() const {
        cout << "Box<" << typeid(T).name() << "> contains: " << value << endl;
    }
};

// Forward declaration for friend functions
class Book;
ostream& operator<<(ostream& out, const Book& book);
istream& operator>>(istream& in, Book& book);

// ========== BOOK CLASS ==========
class Book {
private:
    string title;
    char* author;
    double price;
    int stock;

public:
    // Default constructor
    Book() : title(""), author(nullptr), price(0.0), stock(0) {
        author = new char[1];
        author[0] = '\0';
    }

    // Parameterized constructor
    Book(string t, const char* a, double p, int s) : title(t), price(p), stock(s) {
        if (a != nullptr) {
            int len = 0;
            while (a[len] != '\0') len++;
            author = new char[len + 1];
            for (int i = 0; i <= len; i++) {
                author[i] = a[i];
            }
        } else {
            author = new char[1];
            author[0] = '\0';
        }
    }

    // Copy constructor (deep copy)
    Book(const Book& other) : title(other.title), price(other.price), stock(other.stock) {
        if (other.author != nullptr) {
            int len = 0;
            while (other.author[len] != '\0') len++;
            author = new char[len + 1];
            for (int i = 0; i <= len; i++) {
                author[i] = other.author[i];
            }
        } else {
            author = new char[1];
            author[0] = '\0';
        }
    }

    // Destructor
    ~Book() {
        if (author != nullptr) {
            delete[] author;
            author = nullptr;
        }
    }

    // Setters
    void setTitle(string t) {
        title = t;
    }

    void setAuthor(const char* a) {
        if (author != nullptr) {
            delete[] author;
        }
        if (a != nullptr) {
            int len = 0;
            while (a[len] != '\0') len++;
            author = new char[len + 1];
            for (int i = 0; i <= len; i++) {
                author[i] = a[i];
            }
        } else {
            author = new char[1];
            author[0] = '\0';
        }
    }

    void setPrice(double p) {
        price = p;
    }

    void setStock(int s) {
        stock = s;
    }

    // Getters
    string getTitle() const {
        return title;
    }

    const char* getAuthor() const {
        return author;
    }

    double getPrice() const {
        return price;
    }

    int getStock() const {
        return stock;
    }

    // Member function using this pointer
    void displayInfo() const {
        cout << "--- Book Record ---" << endl;
        cout << "Title: " << this->title << endl;
        cout << "Author: " << this->author << endl;
        cout << "Price: $" << fixed << setprecision(2) << this->price << endl;
        cout << "Stock: " << this->stock << endl;
        cout << "------------------" << endl;
    }

    // Overloaded == operator (member or friend; title and author determine equality)
    bool operator==(const Book& other) const {
        bool titleMatch = (title == other.title);
        bool authorMatch = true;

        if (author != nullptr && other.author != nullptr) {
            int i = 0;
            while (author[i] != '\0' && other.author[i] != '\0') {
                if (author[i] != other.author[i]) {
                    authorMatch = false;
                    break;
                }
                i++;
            }
            if (author[i] != other.author[i]) {
                authorMatch = false;
            }
        }

        return titleMatch && authorMatch;
    }

    // Overloaded ++ operator (pre-increment) - increases stock by 1
    Book& operator++() {
        ++stock;
        return *this;
    }

    // Friend functions for stream operators
    friend ostream& operator<<(ostream& out, const Book& book);
    friend istream& operator>>(istream& in, Book& book);
};

// ========== OVERLOADED << OPERATOR (output stream) ==========
ostream& operator<<(ostream& out, const Book& book) {
    out << "--- Book Record ---" << endl;
    out << "Title: " << book.title << endl;
    out << "Author: " << book.author << endl;
    out << "Price: $" << fixed << setprecision(2) << book.price << endl;
    out << "Stock: " << book.stock << endl;
    out << "------------------";
    return out;
}

// ========== OVERLOADED >> OPERATOR (input stream) ==========
istream& operator>>(istream& in, Book& book) {
    cout << "Enter Title: ";
    if (in.peek() == '\n') in.ignore();
    getline(in, book.title);

    cout << "Enter Author: ";
    string authorStr;
    getline(in, authorStr);

    if (book.author != nullptr) {
        delete[] book.author;
    }
    book.author = new char[authorStr.length() + 1];
    for (size_t i = 0; i < authorStr.length(); i++) {
        book.author[i] = authorStr[i];
    }
    book.author[authorStr.length()] = '\0';

    cout << "Enter Price: ";
    in >> book.price;
    while (book.price < 0) {
        cout << "Error: Price cannot be negative. Enter Price: ";
        in >> book.price;
    }

    cout << "Enter Stock: ";
    in >> book.stock;
    while (book.stock < 0) {
        cout << "Error: Stock cannot be negative. Enter Stock: ";
        in >> book.stock;
    }

    return in;
}

// ========== FUNCTION PROTOTYPES ==========
void displayMenu();
void loadBooksFromFile(Book*& books, int& bookCount, int& capacity);
void displayAllBooks(Book* books, int bookCount);
void addNewBook(Book*& books, int& bookCount, int& capacity);
void compareTwoBooks(Book* books, int bookCount);
void increaseStock(Book* books, int bookCount);
void templateDemonstrations(Book* books, int bookCount);
void saveBooksAndExit(Book* books, int bookCount);
void resizeArray(Book*& books, int& capacity);
int findBookByTitle(Book* books, int bookCount, const string& title);

// ========== MAIN FUNCTION ==========
int main() {
    Book* books = nullptr;
    int bookCount = 0;
    int capacity = 0;
    int choice;

    // Main program loop
    do {
        displayMenu();
        cin >> choice;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Invalid input. Please enter a number (1-7): ";
            cin >> choice;
        }

        cout << endl;

        switch (choice) {
            case 1: {
                // Load Books from File
                loadBooksFromFile(books, bookCount, capacity);
                break;
            }

            case 2: {
                // Display All Books
                displayAllBooks(books, bookCount);
                break;
            }

            case 3: {
                // Add a New Book
                addNewBook(books, bookCount, capacity);
                break;
            }

            case 4: {
                // Compare Two Books
                compareTwoBooks(books, bookCount);
                break;
            }

            case 5: {
                // Increase Stock (Using ++ Operator)
                increaseStock(books, bookCount);
                break;
            }

            case 6: {
                // Use Template Demonstrations
                templateDemonstrations(books, bookCount);
                break;
            }

            case 7: {
                // Save Books and Exit
                saveBooksAndExit(books, bookCount);
                break;
            }

            default: {
                cout << "Error: Invalid choice. Please select a valid option (1-7)." << endl;
                break;
            }
        }

        if (choice != 7) {
            cout << endl;
        }

    } while (choice != 7);

    // Clean up dynamically allocated memory
    if (books != nullptr) {
        delete[] books;
    }

    return 0;
}

// ========== FUNCTION DEFINITIONS ==========

// Function to display the main menu
void displayMenu() {
    cout << "=============================================" << endl;
    cout << "       LIBRARY INVENTORY SYSTEM" << endl;
    cout << "=============================================" << endl;
    cout << "1. Load Books from File" << endl;
    cout << "2. Display All Books" << endl;
    cout << "3. Add a New Book" << endl;
    cout << "4. Compare Two Books" << endl;
    cout << "5. Increase Stock (Using ++ Operator)" << endl;
    cout << "6. Use Template Demonstrations" << endl;
    cout << "7. Save Books and Exit" << endl;
    cout << "Enter your choice (1-7): ";
}

// Function to resize the dynamic array
void resizeArray(Book*& books, int& capacity) {
    int newCapacity = (capacity == 0) ? 5 : capacity * 2;
    Book* newBooks = new Book[newCapacity];

    for (int i = 0; i < capacity; i++) {
        newBooks[i] = books[i];
    }

    if (books != nullptr) {
        delete[] books;
    }

    books = newBooks;
    capacity = newCapacity;
}

// Function to find a book by title
int findBookByTitle(Book* books, int bookCount, const string& title) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getTitle() == title) {
            return i;
        }
    }
    return -1;
}

// Option 1: Load Books from File
void loadBooksFromFile(Book*& books, int& bookCount, int& capacity) {
    ifstream inFile("books.txt");

    if (!inFile) {
        cout << "Error: Could not open 'books.txt' file." << endl;
        return;
    }

    // Clear existing books
    if (books != nullptr) {
        delete[] books;
        books = nullptr;
        bookCount = 0;
        capacity = 0;
    }

    string title;
    string author;
    double price;
    int stock;

    while (getline(inFile, title)) {
        getline(inFile, author);
        inFile >> price;
        inFile >> stock;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (bookCount >= capacity) {
            resizeArray(books, capacity);
        }

        books[bookCount].setTitle(title);
        books[bookCount].setAuthor(author.c_str());
        books[bookCount].setPrice(price);
        books[bookCount].setStock(stock);
        bookCount++;
    }

    inFile.close();

    cout << "Books successfully loaded from file." << endl;
    cout << bookCount << " books available in inventory." << endl;
}

// Option 2: Display All Books
void displayAllBooks(Book* books, int bookCount) {
    if (bookCount == 0) {
        cout << "No books in inventory." << endl;
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        cout << books[i] << endl;
    }
}

// Option 3: Add a New Book
void addNewBook(Book*& books, int& bookCount, int& capacity) {
    if (bookCount >= capacity) {
        resizeArray(books, capacity);
    }

    cin >> books[bookCount];
    bookCount++;

    cout << "Book added successfully." << endl;
}

// Option 4: Compare Two Books
void compareTwoBooks(Book* books, int bookCount) {
    if (bookCount == 0) {
        cout << "No books in inventory to compare." << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string title1, title2;
    cout << "Enter title of first book: ";
    getline(cin, title1);

    cout << "Enter title of second book: ";
    getline(cin, title2);

    int index1 = findBookByTitle(books, bookCount, title1);
    int index2 = findBookByTitle(books, bookCount, title2);

    if (index1 == -1) {
        cout << "Error: First book not found in inventory." << endl;
        return;
    }

    if (index2 == -1) {
        cout << "Error: Second book not found in inventory." << endl;
        return;
    }

    if (books[index1] == books[index2]) {
        cout << "The books are equal." << endl;
    } else {
        cout << "The books are not equal." << endl;
    }
}

// Option 5: Increase Stock (Using ++ Operator)
void increaseStock(Book* books, int bookCount) {
    if (bookCount == 0) {
        cout << "No books in inventory." << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string title;
    cout << "Enter book title: ";
    getline(cin, title);

    int index = findBookByTitle(books, bookCount, title);

    if (index == -1) {
        cout << "Error: Book not found in inventory." << endl;
        return;
    }

    ++books[index];
    cout << "Stock increased. New stock: " << books[index].getStock() << endl;
}

// Option 6: Use Template Demonstrations
void templateDemonstrations(Book* books, int bookCount) {
    // Function template demonstration
    int result1 = maxValue(10, 25);
    cout << "maxValue(10, 25) = " << result1 << endl;

    // Alternative demonstration
    int result2 = maxValue(3, 9);
    cout << "maxValue(3, 9) = " << result2 << endl;

    // Class template demonstration with int
    Box<int> intBox(42);
    intBox.display();

    // Class template demonstration with Book
    if (bookCount > 0) {
        Box<Book> bookBox(books[0]);
        cout << "Box<Book> contains a book titled: " << bookBox.getValue().getTitle() << endl;
    } else {
        Book tempBook;
        tempBook.setTitle("Hamlet");
        tempBook.setAuthor("Shakespeare");
        tempBook.setPrice(9.50);
        tempBook.setStock(12);

        Box<Book> bookBox(tempBook);
        cout << "Box<Book> contains a book titled: " << bookBox.getValue().getTitle() << endl;
    }
}

// Option 7: Save Books and Exit
void saveBooksAndExit(Book* books, int bookCount) {
    ofstream outFile("books.txt");

    if (!outFile) {
        cout << "Error: Could not create output file." << endl;
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        outFile << books[i].getTitle() << endl;
        outFile << books[i].getAuthor() << endl;
        outFile << fixed << setprecision(2) << books[i].getPrice() << endl;
        outFile << books[i].getStock();
        if (i < bookCount - 1) {
            outFile << endl;
        }
    }

    outFile.close();

    cout << "Books successfully saved to 'books.txt'." << endl;
    cout << "Exiting program. Goodbye!" << endl;
}