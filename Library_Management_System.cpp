#include <bits/stdc++.h>
using namespace std;

class Item
{
public:
    string title;
    string author;
    string genre;
    string isbn_identifier;

    // Default constructor
    Item(string title = "", string author = "", string genre = "", string isbn_identifier = "")
    {
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->isbn_identifier = isbn_identifier;
    }
};

// Deriving class Book from Class Item
class Book : public Item
{
public:
    int numOfPages;
    int numOfCopies;
    string publisher;

    // Default constructor
    Book(string title = "", string author = "", string genre = "", string isbn_identifier = "", int numOfPages = 0, int numOfCopies = 0, string publisher = "") : Item(title, author, genre, isbn_identifier)
    {
        this->numOfPages = numOfPages;
        this->numOfCopies = numOfCopies;
        this->publisher = publisher;
    }
};

class User;
class Admin
{
private:
    // This maps the book title with the other attributes
    unordered_map<string, Book> books;
    // This maps the name of student to the book which he/she has issued.
    unordered_map<string, string> userRecord;

public:
    friend void searchBook(User &obj1, Admin &obj2);  // friend function to search any book used by both user and admin.
    friend void issueBook(User &obj1, Admin &obj2);   // friend function to issue any book by user and to make entry to admin about it.
    friend void returnBook(User &obj1, Admin &obj2);  // friend function to return any book by user and to make entry to admin about it.
    friend void displayBook(User &obj1, Admin &obj2); // friend function to display all the books.

    void bookStock();   // This function indicates the total books available in the library
    void userdetails(); // This function gives the details of which user has issued which book.

    // This function is for the admin to add new books to the Library
    void addBook()
    {
        string title_of_book;
        string author_of_book;
        string genre_of_book;
        string isbn_of_book;
        int pages_in_book;
        int copies_of_book;
        string publisher_of_book;

        cout << "Enter Title of Book: ";
        cin.ignore();
        getline(cin, title_of_book);
        cout << "Enter Author of Book: ";
        getline(cin, author_of_book);
        cout << "Enter Genre of Book: ";
        getline(cin, genre_of_book);
        cout << "Enter ISBN of Book: ";
        getline(cin, isbn_of_book);
        cout << "Enter Number of Pages in Book: ";
        cin >> pages_in_book;
        cout << "Enter total number of copies of Book: ";
        cin >> copies_of_book;

        cin.ignore();

        cout << "Enter Publisher of book: ";
        getline(cin, publisher_of_book);
        Book obj(title_of_book, author_of_book, genre_of_book, isbn_of_book, pages_in_book, copies_of_book, publisher_of_book);
        // inserting the book into unordered map
        books[title_of_book] = obj;
        cout << "Book added to Library Successfully.\n";
    }

    // This funciton is for admin to remove books from the Library
    void removeBook()
    {
        string title_of_book;
        cin.ignore();
        getline(cin, title_of_book);
        auto it = books.find(title_of_book);
        // finding the book into the unordered map using iterator and erasing it if found.
        if (it != books.end())
        {
            books.erase(it);
            cout << "Book removed from Library Successfully.\n";
        }
        else
        {
            cout << "There does not exist any book with bookname " << title_of_book << endl;
        }
    }
};

class User
{
public:
    friend class Admin;                               // Admin class can access userRecord.
    friend void searchBook(User &obj1, Admin &obj2);  // friend function to search any book used by both user and admin.
    friend void issueBook(User &obj1, Admin &obj2);   // friend function to issue any book by user and to make entry to admin about it.
    friend void returnBook(User &obj1, Admin &obj2);  // friend function to return any book by user and to make entry to admin about it.
    friend void displayBook(User &obj1, Admin &obj2); // friend function to display all the books.
};

void Admin::bookStock()
{
    // Made a vector of class Book to add some books into the library.
    vector<Book> booksToAdd;

    booksToAdd.push_back(Book("The Great Gatsby", "F. Scott Fitzgerald", "Fiction", "ISBN123", 320, 5, "Penguin Books"));
    booksToAdd.push_back(Book("1984", "George Orwell", "Science Fiction", "ISBN012", 328, 5, "Penguin Books"));
    booksToAdd.push_back(Book("The Hobbit", "J.R.R. Tolkien", "Fantasy", "ISBN901", 310, 4, "Allen & Unwin"));
    booksToAdd.push_back(Book("The Lord of the Rings", "J.R.R. Tolkien", "Fantasy", "ISBN234", 1178, 2, "Allen & Unwin"));
    booksToAdd.push_back(Book("The Hunger Games", "Suzanne Collins", "Young Adult", "ISBN890", 374, 7, "Scholastic"));
    booksToAdd.push_back(Book("Brave New World", "Aldous Huxley", "Science Fiction", "ISBN5678", 311, 3, "Chatto & Windus"));
    booksToAdd.push_back(Book("The Alchemist", "Paulo Coelho", "Fiction", "ISBN9012", 208, 2, "HarperOne"));
    booksToAdd.push_back(Book("Moby-Dick", "Herman Melville", "Classic", "ISBN3456", 585, 4, "Richard Bentley"));
    booksToAdd.push_back(Book("The Kite Runner", "Khaled Hosseini", "Fiction", "ISBN7890", 371, 1, "Riverhead Books"));
    booksToAdd.push_back(Book("The Great Expectations", "Charles Dickens", "Classic", "ISBN0123", 544, 1, "Chapman & Hall"));
    booksToAdd.push_back(Book("The Odyssey", "Homer", "Epic Poetry", "ISBN4567", 442, 1, "Chapman & Hall"));

    for (auto &itr : booksToAdd)
    {
        books[itr.title] = itr;
    }
}

void Admin::userdetails()
{
    cout << "USER               BOOK\n";
    for (auto it : userRecord)
    {
        cout << it.first << "          " << it.second << endl;
    }
}

// This function is for searching the book into the library.
void searchBook(User &obj1, Admin &obj2)
{
    string title_of_book;
    cout << "Enter Title of Book: ";
    cin.ignore();
    getline(cin, title_of_book);
    // Using iterator to find into the unordered map
    auto it = obj2.books.find(title_of_book);
    if (it == obj2.books.end())
    {
        cout << "Book not found!!\n";
    }
    else
    {
        cout << "---------------------------------------------------------\n";
        cout << "Book found\n";
        cout << "Book Details:\n";
        cout << "BOOK TITLE IS: " << it->second.title << endl;
        cout << "BOOK AUTHOR IS: " << it->second.author << endl;
        cout << "BOOK GENRE IS: " << it->second.genre << endl;
        cout << "BOOK IDENTIFIER IS: " << it->second.isbn_identifier << endl;
        cout << "NUMBER OF COPIES OF BOOK IS: " << it->second.numOfCopies << endl;
        cout << "---------------------------------------------------------\n";
    }
}

// This function is for issuing a book from the library.
void issueBook(User &obj1, Admin &obj2)
{
    string username;
    string title_of_book;
    string contactno;
    cout << "Enter your Name: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter your contact number: ";
    getline(cin, contactno);
    cout << "Enter Title of Book: ";
    getline(cin, title_of_book);
    auto it = obj2.books.find(title_of_book);
    // There may be multiple copies of a same book so finding it and if it is available then decreasing the number of copies.
    if (it == obj2.books.end() || it->second.numOfCopies == 0)
    {
        obj2.books.erase(it);
        cout << "Book is not available.\n";
    }
    else
    {
        obj2.userRecord[username] = title_of_book;
        it->second.numOfCopies--;
        cout << "You have successfully issued the book " << title_of_book << endl;
    }
}

// Returning the book to the library and inserting into the unordered map.
void returnBook(User &obj1, Admin &obj2)
{
    string username;
    string title_of_book;
    string author_of_book;
    string genre_of_book;
    string isbn_of_book;
    int pages_in_book;
    int copies_of_book;
    string publisher_of_book;
    string contactno;
    cout << "Enter your Name: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter your contact number: ";
    getline(cin, contactno);
    cout << "Enter Title of Book: ";
    getline(cin, title_of_book);

    cin.ignore();

    cout << "Enter Publisher of book: ";
    getline(cin, publisher_of_book);

    auto it = obj2.books.find(title_of_book);
    if (it != obj2.books.end())
    {
        auto itr = obj2.userRecord.find(username);
        if (itr != obj2.userRecord.end())
            obj2.userRecord.erase(itr);
        it->second.numOfCopies++;
    }
    else
    {
        auto itr = obj2.userRecord.find(username);
        if (itr != obj2.userRecord.end())
            obj2.userRecord.erase(itr);
        copies_of_book = 1;
        Book obj(title_of_book, author_of_book, genre_of_book, isbn_of_book, pages_in_book, copies_of_book, publisher_of_book);
        obj2.books[title_of_book] = obj;
        cout << "Book returned to Library Successfully.\n";
    }
}

// This function displays all the available books into the library.
void displayBook(User &obj1, Admin &obj2)
{
    for (auto &it : obj2.books)
    {
        cout << "---------------------------------------------------------\n";
        cout << "BOOK TITLE IS: " << it.second.title << endl;
        cout << "BOOK AUTHOR IS: " << it.second.author << endl;
        cout << "BOOK GENRE IS: " << it.second.genre << endl;
        cout << "BOOK IDENTIFIER IS: " << it.second.isbn_identifier << endl;
        cout << "NUMBER OF PAGES IN BOOK: " << it.second.numOfPages << endl;
        cout << "NUMBER OF COPIES OF BOOK: " << it.second.numOfCopies << endl;
        cout << "---------------------------------------------------------\n";
    }
}

int main()
{
    cout << "\n\n";
    cout << "\t\t\t\t\t****         *****   ***********    ***********      *********     ***********   ****      ****\n";
    cout << "\t\t\t\t\t****         *****   ***      ***   ***      ***    **       **    ***      ***   ****    **** \n";
    cout << "\t\t\t\t\t****         *****   ***      ***   ***      ***   ***       ***   ***      ***    ****  ****  \n";
    cout << "\t\t\t\t\t****         *****   ***      ***   ***      ***   ***       ***   ***      ***     ********   \n";
    cout << "\t\t\t\t\t****         *****   ***********    ***********    *************   ***********        ****     \n";
    cout << "\t\t\t\t\t****         *****   ***      ***   ***    **      ***       ***   ***    **          ****     \n";
    cout << "\t\t\t\t\t**********   *****   ***      ***   ***     ***    ***       ***   ***     ***        ****     \n";
    cout << "\t\t\t\t\t**********   *****   ***********    ***      ***   ***       ***   ***      ***       ****     \n";
    cout << "\n";
    Admin adm;
    adm.bookStock();
    User usr;
    while (true)
    {
        cout << "PRESS 1 FOR ADMIN AND 2 FOR USER.\n";
        int loginid;
        cin >> loginid;
        if (loginid == 1)
        {
            // Admin Login
            cout << "Enter 1 to add new books to the Library.\n";
            cout << "Enter 2 to remove books from the Library.\n";
            cout << "Enter 3 to search for any book in the Library.\n";
            cout << "Enter 4 for list of all the Books in the Library.\n";
            cout << "Enter 5 to check the user details.\n";
            int adminOption;
            cin >> adminOption;
            // A switch case for multiple functionalities to Admin.
            switch (adminOption)
            {
            case 1:
                adm.addBook();
                break;
            case 2:
                adm.removeBook();
                break;
            case 3:
                searchBook(usr, adm);
                break;
            case 4:
                displayBook(usr, adm);
                break;
            case 5:
                adm.userdetails();
                break;
            default:
                cout << "Please select appropriate option\n";
                break;
            }
        }
        else if (loginid == 2)
        {
            cout << "Enter 1 to search for any books in the Library\n";
            cout << "Enter 2 to issue any available books in the library\n";
            cout << "Enter 3 to return any book to the library\n";
            cout << "Enter 4 to see the available books in the library\n";
            int useroption;
            cin >> useroption;
            // A switch case for multiple functionalities to User.
            switch (useroption)
            {
            case 1:
                searchBook(usr, adm);
                break;

            case 2:
                issueBook(usr, adm);
                break;

            case 3:
                returnBook(usr, adm);
                break;

            case 4:
                displayBook(usr, adm);
                break;

            default:
                break;
            }
        }
        else
        {
            cout << "No Admin or User details found...Please try again!!!\n";
        }
        char exit;
        cout << "Do you want to exit the program(Y/N): ";
        cin >> exit;
        if (exit == 'Y')
            break;
    }
    return 0;
}
