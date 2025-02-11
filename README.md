# **LibraryBookManagementSystem**

# 📚 **Library Book Management System**

## 📖 Project Overview
This **Library Management System** allows users to **borrow and return books**, while librarians manage book inventory and user accounts.  
The project follows a **CRUD-based approach** but also incorporates **efficient data structures and algorithms** to optimize book management, searching, and borrowing.

---

## 🎯 User Story

### **Library Users**
- 🔍 **Search for books** by **title, author, or category**.
- 📖 **Borrow books** with an automatic due date.
- 📑 **View borrowed books list**.
- 🔄 **Return books** when done.

### **Librarians**
- 📌 **Add, update, and remove books** from the system.
- 🏷 **Manage user accounts** and approve new members.
- ⏳ **Track overdue books** and send reminders.

---

## 🛠️ Data Structures Used

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

## 📌 Algorithms Used

| **Algorithm** | **Use Case** |
|--------------|-------------|
| **Sorting (`Merge Sort` / `Quick Sort`)** | Keeps books sorted alphabetically for efficient searching. |
| **Binary Search** | Fast O(log n) lookup for books in sorted lists. |
| **Queue (`FIFO`)** | Ensures fair processing of book borrowing requests. |
| **Greedy Algorithm** | Optimizes book borrowing decisions when demand is high. |

---

## 🚀 Installation & Setup

### **1️⃣ Clone the Repository**
```bash
git clone https://github.com/your-username/library-management-system.git
cd library-management-system
