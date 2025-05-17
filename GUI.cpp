#include "GUI.h"
#include "Database.h"
#include "Library.h"
#include <imgui.h>
#include <iostream>
#include <cstring>

// Global Variables
std::string GUI::username = "";
std::string GUI::password = "";
std::string GUI::userRole = "";
bool GUI::showUserTypeWindow = true;
bool GUI::showLoginWindow = false;
bool GUI::showAdminDashboard = false;
bool GUI::showMemberDashboard = false;

// Popup visibility
bool showAddBookPopup = false;
bool showDeleteBookPopup = false;
bool showAddMemberPopup = false;
bool showDeleteMemberPopup = false;
bool showAddAdminPopup = false;
bool showDeleteAdminPopup = false;
bool showBorrowBookPopup = false;
bool showReturnBookPopup = false;

// Input fields
static char bookTitle[64] = "";
static char bookAuthor[64] = "";
static char bookGenre[64] = "";
static int bookCopies = 0;
static int bookDeleteAmount = 0;
static char memberUsername[32] = "";
static char memberPassword[32] = "";
static char adminUsername[32] = "";
static char adminPassword[32] = "";
static char borrowBookTitle[64] = "";
static char returnBookTitle[64] = "";

void GUI::showUserTypeSelection(Library &library) {
    if (!showUserTypeWindow) return;

    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Always);

    // Set Header Color to Orange
    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));

    ImGui::Begin("Select User Type", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::PopStyleColor(2); // Reset title bar color

    // Welcome Message
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Welcome to the Library System!").x) * 0.5f);
    ImGui::Text("Welcome to Metropolia Library!");

    ImGui::Spacing();
    ImGui::Spacing();

    float buttonWidth = 200.0f;
    float buttonHeight = 50.0f;
    float windowWidth = ImGui::GetWindowSize().x;

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.2f, 0.6f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.4f, 0.0f, 1.0f));

    ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
    if (ImGui::Button("Administrator", ImVec2(buttonWidth, buttonHeight))) {
        GUI::userRole = "admin";
        GUI::showUserTypeWindow = false;
        GUI::showLoginWindow = true;
    }

    ImGui::Spacing();

    ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
    if (ImGui::Button("Member", ImVec2(buttonWidth, buttonHeight))) {
        GUI::userRole = "member";
        GUI::showUserTypeWindow = false;
        GUI::showLoginWindow = true;
    }

    ImGui::PopStyleColor(3);
    ImGui::End();
}


void GUI::showLogin(Library &library) {
    if (!showLoginWindow) return;

    ImGui::SetNextWindowSize(ImVec2(350, 230), ImGuiCond_Always);

    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));

    ImGui::Begin("Login Page", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::PopStyleColor(2); // Reset title bar color

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Enter your credentials to log in:").x) * 0.5f);
    ImGui::Text("Enter your credentials to log in:");
    ImGui::Spacing();

    static char usernameBuffer[32] = "";
    static char passwordBuffer[32] = "";
    static bool showAccessDenied = false;

    float inputWidth = 250.0f;
    float buttonWidth = 130.0f;

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - inputWidth) * 0.5f);
    ImGui::InputText("##username", usernameBuffer, sizeof(usernameBuffer));
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - inputWidth) * 0.5f);
    ImGui::InputText("##password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_Password);

    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.2f, 0.6f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.4f, 0.0f, 1.0f));

    float windowWidth = ImGui::GetWindowSize().x;
    ImGui::SetCursorPosX((windowWidth - (buttonWidth * 2 + 10)) * 0.5f);

    if (ImGui::Button("Login", ImVec2(buttonWidth, 40))) {
        std::string enteredUsername(usernameBuffer);
        std::string enteredPassword(passwordBuffer);
        std::string role;

        if (library.authenticateUser(enteredUsername, enteredPassword, role)) {
            if ((GUI::userRole == "admin" && role != "admin") || (GUI::userRole == "member" && role != "member")) {
                showAccessDenied = true;
            } else {
                GUI::showLoginWindow = false;
                showAccessDenied = false;
                GUI::username = enteredUsername;
                (role == "admin") ? GUI::showAdminDashboard = true : GUI::showMemberDashboard = true;
            }
        } else {
            showAccessDenied = true;
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel", ImVec2(buttonWidth, 40))) {
        GUI::showLoginWindow = false;
        GUI::showUserTypeWindow = true;
        showAccessDenied = false;
    }

    ImGui::PopStyleColor(3); 

    if (showAccessDenied) {
        ImGui::Spacing();
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Invalid username or password!").x) * 0.5f);
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid username or password!");
    }

    ImGui::End();
}

void GUI::showAdminDashboardPage(Library &library) {
    if (!showAdminDashboard) return;

    ImGui::Begin("Admin Dashboard");

    ImGui::Text("Admin Controls");

    if (ImGui::Button("Add Administrator")) showAddAdminPopup = true;
    if (ImGui::Button("Delete Administrator")) showDeleteAdminPopup = true;
    if (ImGui::Button("Add Member")) showAddMemberPopup = true;
    if (ImGui::Button("Delete Member")) showDeleteMemberPopup = true;
    if (ImGui::Button("Add Book")) showAddBookPopup = true;
    if (ImGui::Button("Delete Book")) showDeleteBookPopup = true;
    if (ImGui::Button("Logout")) {
        showAdminDashboard = false;
        showUserTypeWindow = true;
    }

    showAdminPopups(library);

    ImGui::Separator();


    ImGui::Text("Library Books:");
    auto books = library.getBooks();
    if (books.empty()) {
        ImGui::Text("No books available.");
    } else {
        for (const auto &book : books) {
            ImGui::Text("Title: %s | Author: %s | Genre: %s | Available: %d",
                book.title.c_str(), book.author.c_str(), book.genre.c_str(), book.availableCopies);
        }
    }

    ImGui::Separator();

    ImGui::Text("Registered Administrators:");
    auto users = library.getUsers();
    for (const auto &user : users) {
        if (user.second == "admin") {
            ImGui::Text("Username: %s", user.first.c_str());
        }
    }

    ImGui::Separator();

    ImGui::Text("Registered Members:");
    for (const auto &user : users) {
        if (user.second == "member") {
            ImGui::Text("Username: %s", user.first.c_str());
        }
    }


    ImGui::End();
}

void GUI::showMemberDashboardPage(Library &library) {
    if (!showMemberDashboard) return;

    ImGui::Begin("Member Dashboard");

    ImGui::Text("Member Controls");

    if (ImGui::Button("Borrow Book")) showBorrowBookPopup = true;
    if (ImGui::Button("Return Book")) showReturnBookPopup = true;
    if (ImGui::Button("Logout")) {
        showMemberDashboard = false;
        showUserTypeWindow = true;
    }

    ImGui::Separator();
    ImGui::Text("Your Borrowed Books:");

    auto &database = library.getDatabase();
    if (database.contains("borrowedBooks") && database["borrowedBooks"].contains(username)) {
        for (const auto &book : database["borrowedBooks"][username]) {
            ImGui::Text("%s", book.get<std::string>().c_str());
        }
    } else {
        ImGui::Text("No borrowed books.");
    }

    showMemberPopups(library);

    ImGui::End();
}

void GUI::showAdminPopups(Library &library) {

    if (showAddAdminPopup) {
        ImGui::Begin("Add Administrator", &showAddAdminPopup);

        ImGui::InputText("Username", adminUsername, sizeof(adminUsername));
        ImGui::InputText("Password", adminPassword, sizeof(adminPassword), ImGuiInputTextFlags_Password);

        if (ImGui::Button("Add")) {
            if (strlen(adminUsername) > 0 && strlen(adminPassword) > 0) {
                library.addAdmin(adminUsername, adminPassword);
                memset(adminUsername, 0, sizeof(adminUsername));
                memset(adminPassword, 0, sizeof(adminPassword));
                showAddAdminPopup = false;
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            showAddAdminPopup = false;
        }

        ImGui::End();
    }



    if (showDeleteAdminPopup) {
        ImGui::Begin("Delete Administrator", &showDeleteAdminPopup);

        ImGui::InputText("Username", adminUsername, sizeof(adminUsername));

        if (ImGui::Button("Delete")) {
            if (strlen(adminUsername) > 0) {
                library.deleteAdmin(adminUsername);
                memset(adminUsername, 0, sizeof(adminUsername));
                showDeleteAdminPopup = false;
            } else {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid input!");
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) showDeleteAdminPopup = false;

        ImGui::End();
    }

    if (showAddMemberPopup) {
        ImGui::Begin("Add Member", &showAddMemberPopup);

        ImGui::InputText("Username", memberUsername, sizeof(memberUsername));
        ImGui::InputText("Password", memberPassword, sizeof(memberPassword), ImGuiInputTextFlags_Password);

        if (ImGui::Button("Add")) {
            if (strlen(memberUsername) > 0 && strlen(memberPassword) > 0) {
                library.addMember(memberUsername, memberPassword);
                memset(memberUsername, 0, sizeof(memberUsername));
                memset(memberPassword, 0, sizeof(memberPassword));
                showAddMemberPopup = false;
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) showAddMemberPopup = false;

        ImGui::End();
    }

    if (showDeleteMemberPopup) {
        ImGui::Begin("Delete Member", &showDeleteMemberPopup);

        ImGui::InputText("Username", memberUsername, sizeof(memberUsername));

        if (ImGui::Button("Delete")) {
            if (strlen(memberUsername) > 0) {
                library.deleteMember(memberUsername);
                memset(memberUsername, 0, sizeof(memberUsername));
                showDeleteMemberPopup = false;
            } else {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid input!");
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) showDeleteMemberPopup = false;

        ImGui::End();
    }

    if (showAddBookPopup) {
        ImGui::Begin("Add Book", &showAddBookPopup);

        ImGui::InputText("Title", bookTitle, sizeof(bookTitle));
        ImGui::InputText("Author", bookAuthor, sizeof(bookAuthor));
        ImGui::InputText("Genre", bookGenre, sizeof(bookGenre));
        ImGui::InputInt("Available Copies", &bookCopies);

        if (ImGui::Button("Add")) {
            if (strlen(bookTitle) > 0 && strlen(bookAuthor) > 0 && strlen(bookGenre) > 0 && bookCopies > 0) {
                library.addBook(bookTitle, bookAuthor, bookGenre, bookCopies);
                memset(bookTitle, 0, sizeof(bookTitle));
                memset(bookAuthor, 0, sizeof(bookAuthor));
                memset(bookGenre, 0, sizeof(bookGenre));
                bookCopies = 0;
                showAddBookPopup = false;
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) showAddBookPopup = false;

        ImGui::End();
    }

    if (showDeleteBookPopup) {
        ImGui::Begin("Delete Book", &showDeleteBookPopup);

        ImGui::InputText("Title", bookTitle, sizeof(bookTitle));
        ImGui::InputInt("Amount to Delete", &bookDeleteAmount);

        if (ImGui::Button("Delete")) {
            if (strlen(bookTitle) > 0 && bookDeleteAmount > 0) {
                library.deleteBook(bookTitle, bookDeleteAmount);
                memset(bookTitle, 0, sizeof(bookTitle));
                bookDeleteAmount = 0;
                showDeleteBookPopup = false;
            } else {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid input!");
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) showDeleteBookPopup = false;

        ImGui::End();
    }
}

void GUI::showMemberPopups(Library &library) {

    if (showBorrowBookPopup) {
        ImGui::Begin("Borrow Book", &showBorrowBookPopup);

        ImGui::InputText("Book Title", borrowBookTitle, sizeof(borrowBookTitle));

        if (ImGui::Button("Borrow")) {
            if (strlen(borrowBookTitle) > 0) {
                if (library.borrowBook(username, borrowBookTitle)) {
                    showBorrowBookPopup = false;
                } else {
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "Failed to borrow book!");
                }
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) showBorrowBookPopup = false;

        ImGui::End();
    }


    if (showReturnBookPopup) {
        ImGui::Begin("Return Book", &showReturnBookPopup);

        ImGui::InputText("Book Title", returnBookTitle, sizeof(returnBookTitle));

        if (ImGui::Button("Return")) {
            if (strlen(returnBookTitle) > 0) {
                if (library.returnBook(username, returnBookTitle)) {
                    showReturnBookPopup = false;
                } else {
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "Failed to return book!");
                }
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel")) showReturnBookPopup = false;

        ImGui::End();
    }
}
