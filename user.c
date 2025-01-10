#include <stdio.h>
#include <string.h>
#include "user.h"

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


User* loginUser(Userlist *userlist, const char *username, const char *password)
{
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

void addUser(Userlist *userlist, const char *username, const char *password, UserRole role)
{
    if (userlist->userCount < MAX_USERS)
    {
        User *newUser = &userlist->users[userlist->userCount++];
        initializeUser(newUser, username, password, role);
        printf("User %s added successfully.\n", username);
    }
    else
    {
        printf("User limit reached. Cannot add more users.\n");
    }
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
}

void saveUsersToFile(Userlist *userlist)
{
    FILE *file = fopen("Users.txt", "w"); // Open the file in write mode
    if (file != NULL)
    {
        for (int i = 0; i < userlist->userCount; i++)
        {
            fprintf(file, "%s\n", userlist->users[i].username);
            fprintf(file, "%s\n", userlist->users[i].password);
            fprintf(file, "%d\n", userlist->users[i].role);
            fprintf(file, "%d\n", userlist->users[i].isLoggedIn);
        }
        fclose(file);
        printf("Users saved to file.\n");
    }
    else
    {
        printf("Error saving users to file.\n");
    }
}

void loadUsersFromFile(Userlist *userlist)
{
    FILE *file = fopen("Users.txt", "r");
    if (file != NULL)
    {
        userlist->userCount = 0;
        while (!feof(file))
        {
            if (userlist->userCount >= MAX_USERS)
                break;

            User *user = &userlist->users[userlist->userCount];

            fgets(user->username, MAX_USERNAME_LENGTH, file);
            user->username[strcspn(user->username, "\n")] = '\0';

            fgets(user->password, MAX_PASSWORD_LENGTH, file);
            user->password[strcspn(user->password, "\n")] = '\0';

            fscanf(file, "%d", &user->role);
            fscanf(file, "%d", &user->isLoggedIn);

            fgetc(file);

            userlist->userCount++;
        }
        fclose(file);
        printf("Users loaded from file.\n");
    }
    else
    {
        printf("Error loading users from file.\n");
    }
}




