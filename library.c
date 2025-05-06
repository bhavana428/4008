#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

// Structure to store book information
typedef struct 
{
    int id;
    char title[100];
    char author[50];
} Book;


// Function prototypes

void addBook(Book books[], int *count);
void displayBooks(Book books[], int count);
void searchBookByID(Book books[], int count, int id);
void deleteBookByID(Book books[], int *count, int id);
void updateBookByID(Book books[], int count, int id);
void countBooks(int count);

int main() 
{
    Book books[MAX_BOOKS];
    int count = 0;
    int choice;
    int id;

    while (1) 
    {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Delete Book by ID\n");
        printf("5. Update Book by ID\n");
        printf("6. Count Total Books\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) 
        {
            case 1:
                addBook(books, &count);
                break;
            case 2:
                displayBooks(books, count);
                break;
            case 3:
                printf("Enter Book ID to search: ");
                scanf("%d", &id);
                searchBookByID(books, count, id);
                break;
            case 4:
                printf("Enter Book ID to delete: ");
                scanf("%d", &id);
                deleteBookByID(books, &count, id);
                break;
            case 5:
                printf("Enter Book ID to update: ");
                scanf("%d", &id);
                updateBookByID(books, count, id);
                break;
            case 6:
                countBooks(count);
                break;
            case 7:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add a new book

void addBook(Book books[], int *count) 
{
    if (*count >= MAX_BOOKS) 
    {
        printf("Cannot add more books. Maximum limit reached.\n");
        return;
    }

    Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    getchar(); // Consume newline character

    printf("Enter Book Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // Remove newline character

    printf("Enter Book Author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0'; // Remove newline character

    books[*count] = newBook;
    (*count)++;

    printf("Book added successfully!\n");
}

// Function to display all books

void displayBooks(Book books[], int count) 
{
    if (count == 0) 
    {
        printf("No books to display.\n");
        return;
    }

    printf("\n--- Book List ---\n");
    for (int i = 0; i < count; i++) 
    {
        printf("ID: %d\n", books[i].id);
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("-----------------------\n");
    }
}

// Function to search for a book by ID

void searchBookByID(Book books[], int count, int id) 
{
    for (int i = 0; i < count; i++) 
    {
        if (books[i].id == id) 
        {
            printf("\nBook Found:\n");
            printf("ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            return;
        }
    }
    printf("Book with ID %d not found.\n", id);
}

// Function to delete a book by ID

void deleteBookByID(Book books[], int *count, int id) 
{
    int found = 0;
    for (int i = 0; i < *count; i++) 
    {
        if (books[i].id == id) 
        {
            found = 1;
            for (int j = i; j < *count - 1; j++) 
            {
                books[j] = books[j + 1];
            }
            (*count)--;
            printf("Book with ID %d deleted successfully.\n", id);
            break;
        }
    }
    if (!found) 
    {
        printf("Book with ID %d not found.\n", id);
    }
}

// Function to update a book by ID

void updateBookByID(Book books[], int count, int id) 
{
    for (int i = 0; i < count; i++) 
    {
        if (books[i].id == id) 
        {
            printf("Enter new title: ");
            getchar(); // Consume newline character
            fgets(books[i].title, sizeof(books[i].title), stdin);
            books[i].title[strcspn(books[i].title, "\n")] = '\0'; // Remove newline character

            printf("Enter new author: ");
            fgets(books[i].author, sizeof(books[i].author), stdin);
            books[i].author[strcspn(books[i].author, "\n")] = '\0'; // Remove newline character

            printf("Book with ID %d updated successfully.\n", id);
            return;
        }
    }
    printf("Book with ID %d not found.\n", id);
}

// Function to count total number of books

void countBooks(int count) 
{
    printf("Total number of books: %d\n", count);
}

