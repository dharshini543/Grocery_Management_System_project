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
#ifndef USER_H
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

#endif


