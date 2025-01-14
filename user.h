#ifndef USER_H
#define USER_H

#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 30
#define MAX_USERS 100

typedef enum {
    ROLE_USER,
    ROLE_ADMIN,
} UserRole;

typedef struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int isLoggedIn;
    UserRole role;
} User;

typedef struct Userlist {
    User users[MAX_USERS];
    int userCount;
} Userlist;

void openUserFile();
void closeUserFile();
void initializeUser(User *user, const char *username, const char *password, UserRole role);
void addFirstAdminUser(Userlist *userlist);
User* loginUser(Userlist *userlist);
void logoutUser(User *user);
int addUser(Userlist *userlist, const char *username, const char *password, UserRole role);
void deleteUser(Userlist *userlist, const char *username);
void printUsers(Userlist *userlist);
void saveUsersToFile(Userlist *userlist);
void loadUsersFromFile(Userlist *userlist);

#endif // USER_H



