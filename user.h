/*#ifndef USER_H
#define USER_H

#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 30

typedef struct User
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
    int isAdmin;
} User;

typedef struct Userlist
{
    User * UserHead;
    int Usercount;
}Userlist;

void addUser(Userlist * userlist);
void initializeUser(User *user, const char *username, const char *password);
int loginUser(User *user, const char *username, const char *password);
void logoutUser(User *user);
void displayLoginScreen(User *user);

#endif // USER_H*/
/*#ifndef USER_H
#define USER_H

// User roles
typedef enum {
    ROLE_ADMIN,
    ROLE_USER
} UserRole;

// User structure
typedef struct {
    char name[50];
    char password[20];
    UserRole role;
    int isLoggedIn;
} User;

void loadUsersFromFile();
void saveUsersToFile();
int addUser(const char *username, const char *password, int role);
int deleteUser(const char *username);
void initializeUser(User *user, const char *name, const char *password, UserRole role);
void login(User *user);

#endif*/
#ifndef USER_H
#define USER_H

#include <stdio.h>
#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 30

// User structure
typedef struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isAdmin;  // 1 for admin, 0 for normal user
    struct User* next;  // Pointer to the next user in the linked list
} User;

typedef struct Userlist
{
    User * head;
    int Usercount;
}Userlist;

// Global variable to hold the currently logged-in user
extern User* currentUser;
extern FILE* userFile;  // Global file pointer

// Function prototypes for user operations
User* createUser(Userlist * userlist, int isAdmin);
User* setAdmin(Userlist * userlist);
void login(Userlist * userlist);
User* changePassword(Userlist * userlist);
void freeList(Userlist * userlist);

// Function to check if the logged-in user is an admin
int isAdminLoggedIn();

// Load and save users from/to file
User* loadUsersFromFile(Userlist * userlist);
void saveUsersToFile(Userlist * userlist);

void closeUserFile();
#endif // USER_H


