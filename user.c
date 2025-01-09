/*#include <stdio.h>
#include <string.h>
#include "user.h"

void initializeUser(User *user, const char *username, const char *password)
{
    strcpy(user->username, username);
    strcpy(user->password, password);
    user->isLoggedIn = 0;
}


int loginUser(User *user, const char *username, const char *password)
{
    if (strcmp(user->username, username) == 0 && strcmp(user->password, password) == 0)
    {
        user->isLoggedIn = 1;
        printf("Login successful. Welcome, %s!\n\n", username);
        return 1;
    }
    else
    {
        printf("Login failed. Please check your credentials.\n\n");
        return 0;
    }
}

void logoutUser(User *user)
{
    user->isLoggedIn = 0;
    printf("Logout successful.\n");
}

void displayLoginScreen(User *user)
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    loginUser(user, username, password);
}*/

/*#include <stdio.h>
#include <string.h>
#include "user.h"

#define MAX_USERS 100

static User users[MAX_USERS];
static int userCount = 0;


// Initialize a user
void initializeUser(User *user, const char *name, const char *password, UserRole role)
{
    strcpy(user->name, name);
    strcpy(user->password, password);
    user->role = role;
    user->isLoggedIn = 0;
}

// Handle user login
void login(User *user)
{
    char enteredName[50], enteredPassword[20];

    printf("Enter username: ");
    scanf("%s", enteredName);
    printf("Enter password: ");
    scanf("%s", enteredPassword);

    if (strcmp(user->name, enteredName) == 0 && strcmp(user->password, enteredPassword) == 0)
    {
        printf("Login successful! Welcome, %s.\n", user->name);
        user->isLoggedIn = 1;
    }
    else
    {
        printf("Invalid credentials. Please try again.\n");
    }
}
void loadUsersFromFile()
{
    FILE *file = fopen("users.txt", "r+");
    if (file == NULL)
    {
        file = fopen("users.txt", "w+");
        if(file == NULL)
        {
            printf("No user file found. Starting with an empty user list.");
            return;
        }
    }

    fscanf(file, "%d", &userCount);
    for (int i = 0; i < userCount; i++)
    {
        fscanf(file, "%s %s %d", users[i].name, users[i].password, &users[i].role);
    }
    fclose(file);
}
void saveUsersToFile()
{
    FILE *file = fopen("users.txt", "w");
    if (file == NULL)
    {
        printf("Error: Could not save users to file.");
        return;
    }

    fprintf(file, "%d\n", userCount);
    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%s %s %d\n", users[i].name, users[i].password, users[i].role);
    }
    fclose(file);
}

int addUser(const char *username, const char *password, int role)
{
    if (userCount >= MAX_USERS)
    {
        printf("User limit reached. Cannot add more users.\n");
        return 0;
    }

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0)
        {
            printf("Error: User with username '%s' already exists.\n", username);
            return 0;
        }
    }

    strcpy(users[userCount].name, username);
    strcpy(users[userCount].password, password);
    users[userCount].role = role;
    users[userCount].isLoggedIn = 0;
    userCount++;

    saveUsersToFile();
    printf("User '%s' added successfully.\n", username);
    return 1;
}

int deleteUser(const char *username)
{
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0)
        {
            for (int j = i; j < userCount - 1; j++)
            {
                users[j] = users[j + 1];
            }
            userCount--;
            saveUsersToFile();
            printf("User '%s' deleted successfully.\n", username);
            return 1;
        }
    }

    printf("Error: User with username '%s' not found.\n", username);
    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

// Global variable to hold the current logged-in user
User* currentUser = NULL;
FILE* userFile = NULL;  // Global file pointer for users file

// Function to load users from file
User* loadUsersFromFile(Userlist * userlist)
{
    userFile = fopen("users.txt", "r+");
    if (!userFile)
    {
        userFile = fopen("users.txt", "w+");
        if (!userFile)
        {
            return 0;
        }
    }

    User* temp;

    // Read users from file
    while (!userFile)
    {
        temp = (User*)malloc(sizeof(User));
        if (fscanf(userFile, "%s %s %d", temp->username, temp->password, &temp->isAdmin) != 3) {
            free(temp);
            break;
        }
        temp->next = userlist->head;
        userlist->head = temp;
    }

    return userlist->head;
}

// Function to save users to file (only the updates to the file)
void saveUsersToFile(Userlist * userlist)
{
    // We need to rewrite the file with the updated list of users.
    // To avoid opening/closing the file repeatedly, we'll use the global file pointer.
    if (userFile == NULL) {
        return;
    }

    // Move the file pointer back to the beginning
    rewind(userFile);

    // Save each user to the file
    User* temp =userlist->head;
    while (temp != NULL) {
        fprintf(userFile, "%s %s %d\n", temp->username, temp->password, temp->isAdmin);
        temp = temp->next;
    }

    // Ensure the file is properly flushed and updated
    fflush(userFile);
}

// Function to create a new user
User* createUser(Userlist * userlist, int isAdmin) {
    User* newUser = (User*)malloc(sizeof(User));
    if (newUser == NULL) {
        printf("Memory allocation failed!\n");
        return userlist->head;
    }

    printf("Enter username: ");
    scanf("%s", newUser->username);
    printf("Enter password: ");
    scanf("%s", newUser->password);
    newUser->isAdmin = isAdmin;  // Set admin status (isAdmin passed as argument)

    newUser->next = userlist->head;  // Add the new user at the beginning of the list
    userlist->head = newUser;

    printf("User created successfully.\n");
    return userlist->head;
}

User* setAdmin(Userlist * userlist)
{
    char username[MAX_USERNAME_LENGTH];
    printf("Enter the username of the user you want to make an admin: ");
    scanf("%s", username);

    User* current = userlist->head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            current->isAdmin = 1;  // Set the user's admin status
            printf("User %s is now an admin.\n", current->username);
            return userlist->head;
        }
        current = current->next;
    }

    printf("User not found!\n");
    return userlist->head;
}

// Function to login and handle user operations
void login(Userlist * userlist) {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];
    int found = 0;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Search for the user and check the credentials
    User* temp = userlist->head;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && strcmp(temp->password, password) == 0) {
            found = 1;
            printf("Login successful\n\n");

            currentUser = temp;  // Set the logged-in user

            if (temp->isAdmin) {
                // Perform admin operations here
            } else {
                // Perform normal user operations here
            }
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Invalid username or password.\n");
    }
}

// Function to check if the logged-in user is an admin
int isAdminLoggedIn() {
    if (currentUser != NULL && currentUser->isAdmin) {
        return 1;  // User is an admin
    }
    return 0;  // User is not an admin
}

// Function to change password
User* changePassword(Userlist * userlist) {
    char username[MAX_USERNAME_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    // Find the user in the list
    User* temp = userlist->head;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0) {
            printf("Enter new password: ");
            scanf("%s", password);
            strcpy(temp->password, password);
            printf("Password updated successfully.\n");

            // Save the updated list to the file immediately
            saveUsersToFile(userlist->head);
            return userlist->head;
        }
        temp = temp->next;
    }

    printf("User not found.\n");
    return userlist->head;
}

// Function to free the linked list memory
void freeList(Userlist * userlist) {
    User* temp;
    while (userlist->head != NULL) {
        temp = userlist->head;
        userlist->head= userlist->head->next;
        free(temp);
    }
}

// Function to close the file when exiting the program
void closeUserFile() {
    if (userFile != NULL) {
        fclose(userFile);
        userFile = NULL;  // Reset the file pointer
    }
}


