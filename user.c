#include <stdio.h>
#include <string.h>
#include "user.h"
#include "enum.h"

FILE * UserFile = NULL;

void openUserFile()
{
    UserFile = fopen("Users.txt", "r+");
    if (!UserFile)
    {
        UserFile = fopen("Users.txt", "w+");
        if (!UserFile)
        {
            return;
        }
    }
    return;
}

void closeUserFile()
{
    if (UserFile != NULL)
    {
        fflush(UserFile);
        fclose(UserFile);
    }
}

void initializeUser(User *user, const char *username, const char *password, UserRole role)
{
    strcpy(user->username, username);
    strcpy(user->password, password);
    user->isLoggedIn = 0;
    user->role = role;
}


User* loginUser(Userlist *userlist)
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\t ------- LOGIN -------\n");
    printf("\t Enter username: ");
    scanf("%s", username);
    printf("\t Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userlist->userCount; i++)
    {
        if (strcmp(userlist->users[i].username, username) == 0 &&
            strcmp(userlist->users[i].password, password) == 0)
        {
            userlist->users[i].isLoggedIn = 1;
            return &userlist->users[i];
        }
    }
    return NULL;
}


void logoutUser(User *user)
{
    user->isLoggedIn = 0;
    printf("Logout successful.\n");
}


int addUser(Userlist *userlist, const char *username, const char *password, UserRole role)
{
    if (userlist->userCount < MAX_USERS)
    {
        User *newUser = &userlist->users[userlist->userCount++];
        initializeUser(newUser, username, password, role);
        printf("User %s added successfully.\n", username);
        return Success;
    }
    else
    {
        printf("User limit reached. Cannot add more users.\n");
        return Failure;
    }
    printUsers(userlist);
}


void deleteUser(Userlist *userlist, const char *username)
{
    for (int i = 0; i < userlist->userCount; i++)
    {
        if (strcmp(userlist->users[i].username, username) == 0)
        {
            for (int j = i; j < userlist->userCount - 1; j++)
            {
                userlist->users[j] = userlist->users[j + 1];
            }
            userlist->userCount--;
            printf("User %s deleted successfully.\n", username);
            return;
        }
    }
    printf("User %s not found.\n", username);
    printUsers(userlist);
}


void printUsers(Userlist *userlist)
{
    return;
    for (int i = 0; i < userlist->userCount; i++)
    {
        printf("User %d %s %s\n", i+1, userlist->users[i].username, userlist->users[i].password);
    }
}


void saveUsersToFile(Userlist *userlist)
{
    FILE *file = fopen("Users.txt", "w");
    if (file != NULL)
    {
        for (int i = 0; i < userlist->userCount; i++)
        {
            fprintf(file, "%s\n", userlist->users[i].username);
            fprintf(file, "%s\n", userlist->users[i].password);
            fprintf(file, "%d\n", userlist->users[i].role);
        }
        fclose(file);
    }
    else
    {
        printf("Error saving users to file.\n");
    }
    printUsers(userlist);
}

void loadUsersFromFile(Userlist *userlist)
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    userlist->userCount = 0;

    while (fscanf(file, " %29s %29s %d %d",
                  userlist->users[userlist->userCount].username,
                  userlist->users[userlist->userCount].password,
                  (int *)&userlist->users[userlist->userCount].role) == 3)
    {
        userlist->userCount++;
        if (userlist->userCount >= MAX_USERS)
        {
            fprintf(stderr, "Maximum user limit reached, some users may not be loaded.\n");
            break;
        }
    }

    fclose(file);
    printUsers(userlist);
}

void addFirstAdminUser(Userlist *userlist)
{
    if (userlist->userCount == 0)
    {
        printf("Please create the first admin user:\n");
        printf("\t Enter username: ");
        scanf(" %29s", userlist->users[0].username);
        printf("\t Enter password: ");
        scanf(" %29s", userlist->users[0].password);
        userlist->users[0].isLoggedIn = 0;
        userlist->users[0].role = ROLE_ADMIN;
        userlist->userCount = 1;
        printf("Admin user created successfully!\n");
    }
}

