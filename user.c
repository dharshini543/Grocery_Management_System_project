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

#include <stdio.h>
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
}


