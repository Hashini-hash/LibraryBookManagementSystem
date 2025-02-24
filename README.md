#  **Library Book Management System Version 1**

## Project Overview
This **Library Management System** allows users to **borrow and return books**, while librarians manage book inventory and user accounts.  
The project follows a **CRUD-based approach** but also incorporates **efficient data structures and algorithms** to optimize book management, searching, and borrowing.

---

##  User Story

### **Library Users**
-  **Search for books** by **title, author, or category**.
-  **Borrow books** with an automatic due date.
-  **View borrowed books list**.
-  **Return books** when done.

### **Librarians**
-  **Add, update, and remove books** from the system.
-  **Manage user accounts** and approve new members.
-  **Track overdue books** and send reminders.

---

### **Users in the Project**
| ****User Role**** | **Allowed Actions** |
|-------------|----------------|
| ****Library Member**** | **Search books** using optimized data structures (Trie) <br> **View borrowed books** <br> **Borrow books** (if available) <br> **Return books** (to free availability) |
| ****Librarian (Admin)**** | **Manage books** (Add, update, delete books) <br> **Manage users** (Register members, update roles) <br> **View transaction logs** (See book borrow/return history) |

Only **librarians** can modify book and user records, while **members** can only search and borrow books.

##  Data Structures Used

| **Feature** | **Data Structure** | **Purpose** |
|------------|------------------|-------------|
| **Book Storage & Lookup** | `Hash Table` | O(1) search for books by ID/title. |
| **Sorted Book Listings** | `BST / AVL Tree` | Books remain sorted for browsing. |
| **Book Search by Title** | `Trie` | Enables fast prefix-based search (autocomplete). |
| **Borrowed Book Tracking** | `Doubly Linked List` | Keeps track of borrowed books per user. |
| **Scalable Book Storage** | `B+ Tree` | Efficient storage for large book collections. |
| **Dynamic Book Management** | `Vector` | Enables flexible book storage and resizing. |
| **Fast User Lookup** | `Unordered Map` | Quick retrieval of user records. |

---

## Algorithms Used

| **Algorithm** | **Use Case** |
|--------------|-------------|
| **Sorting (`Merge Sort` / `Quick Sort`)** | Keeps books sorted alphabetically for efficient searching. |
| **Binary Search** | Fast O(log n) lookup for books in sorted lists. |
| **Queue (`FIFO`)** | Ensures fair processing of book borrowing requests. |
| **Greedy Algorithm** | Optimizes book borrowing decisions when demand is high. |

---

#  **Library Book Management System Version 2**


A C++ application designed to manage book borrowing and returning operations in a library. The system supports two types of users—Administrators and Members—each with distinct roles and privileges. The application follows a three-layer architecture for clear separation of concerns.

---

## Overview

The system is structured into three main layers:

- **Graphical User Interface (GUI):**  
  Displays menus, search results, and facilitates user interactions.
  
- **Backend (Core Functionalities):**  
  Processes user requests, enforces business rules (e.g., ensuring books can only be borrowed when available), and communicates with the database layer.
  
- **Database (Storage Layer):**  
  Manages data storage using binary files, handling all persistent data operations (books, users, and transaction records).

---

## Users & Features

### Administrator Features

- **Manage Books:** Add, Edit, Delete books.
- **Manage Members:** Create and delete user accounts.
- **View Logs:** Review the history of borrow/return transactions.
- **Logout:** End the current session.

### Member Features

- **Search Books:** Look up books by title, author, or genre.
- **Borrow Books:** Borrow a book if it is available.
- **Return Books:** Return previously borrowed books.
- **Reserve Books:** Join a reservation queue if a book is currently unavailable.
- **Create/Delete Account:** Manage personal account settings.
- **Logout:** End the current session.

---

## Main Components

### 1. GUI (User Interface)
- **Role:** Displays menus, search results, and interactions.
- **Operation:** Triggers backend functions based on user actions.

### 2. Backend (Core Functionalities)
- **Role:** Processes user commands, enforces business logic, and handles requests.
- **Operation:** Interacts with the database to retrieve and update records.

### 3. Database (Data Storage)
- **Role:** Stores and manages persistent data including book details, user accounts, and transaction logs.
- **Operation:** Utilizes file I/O operations with binary files for data persistence.

---

## Data Structures & Algorithms Used

### Data Structures

- **`std::unordered_map<int, User>`**  
  Efficiently stores user accounts for fast lookup.

- **`std::map<int, BookInfo>`**  
  Maintains book details with support for sorted traversal.

- **`std::map<int, BookCopy>`**  
  Manages physical copies of books, allowing multiple copies per title.

- **`std::queue<int>`**  
  Implements a waiting list for book reservations, ensuring FIFO order.

- **`std::vector<>`**  
  Facilitates efficient retrieval of multiple search results.

### Algorithms

- **Binary Search:**  
  Speeds up book searches by title, author, or genre.

- **Hash Table Lookup:**  
  Enhances performance when searching for user records.

- **Queue Processing:**  
  Ensures fairness in fulfilling book reservations.

- **Sorting (Tree-Based using `std::map`):**  
  Keeps book listings ordered for easy browsing.

---

## Typical Flow of Functionalities

### 1. Logging In (Admin/Member)
- **Action:** User enters email and password.
- **Flow:**  
  - GUI sends login details to the Backend.
  - Backend verifies credentials by checking the database.
  - On success, the user is granted access.

### 2. Searching for a Book
- **Action:** User searches by title, author, or genre.
- **Flow:**  
  - GUI sends the query to the Backend.
  - Backend calls database functions (`getBookInfo`, `getBookCopy`) to fetch details.
  - Results are displayed on the UI.

### 3. Borrowing a Book
- **Action:** User selects a book to borrow.
- **Flow:**  
  - GUI sends the request to the Backend.
  - Backend verifies the availability of a copy.
  - If available, the book is marked as borrowed and records are updated (`borrowBookCopy`).

### 4. Returning a Book
- **Action:** User selects a book to return.
- **Flow:**  
  - GUI sends the return request to the Backend.
  - Backend updates the book’s status to Available (`returnBookCopy`).
  - The book becomes available for other users.

### 5. Reserving a Book (If Unavailable)
- **Action:** User requests to reserve a book.
- **Flow:**  
  - GUI forwards the request to the Backend.
  - Backend adds the user to the reservation queue (`reserveBook`).
  - The user is placed on the waiting list.

### 6. Processing a Reservation
- **Action:** Admin processes reservations.
- **Flow:**  
  - GUI sends the command to the Backend.
  - Backend checks the reservation queue and assigns an available book to the next user (`processNextReservation`).

### 7. Managing Users (Admin Only)
- **Adding a Member:**  
  - Function: `createUser(UserType::Member, email, password)`
- **Deleting a Member:**  
  - Function: `deleteUser(userID)`

### 8. Managing Books (Admin Only)
- **Adding a Book:**  
  - Function: `createBookInfo(title, authorID, genreID)`
- **Editing a Book:**  
  - Function: `editBookInfo(bookInfoID, newTitle, newAuthorID, newGenreID)`
- **Deleting a Book:**  
  - Function: `deleteBookInfo(bookInfoID)`

### 9. Viewing Log History (Admin)
- **Action:** Admin selects “View Logs.”
- **Flow:**  
  - GUI sends a request to the Backend.
  - Backend retrieves transaction records (`getBorrowRecord`).
  - Log history is displayed.

### 10. Logging Out
- **Action:** User clicks “Logout.”
- **Flow:**  
  - GUI ends the session and returns to the login screen.

---

## How This Design Enhances Efficiency

- **Data Normalization:**  
  Avoids redundant data storage, ensuring consistency.
  
- **Efficient Data Retrieval:**  
  Utilizes hash maps, binary search, and sorted maps to quickly access data.
  
- **Fair Reservation System:**  
  A queue-based approach guarantees that book reservations are processed in a first-in, first-out order.
  
- **Persistent Storage:**  
  Binary file storage maintains data across sessions reliably.
