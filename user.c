#include <stdio.h>
#include <string.h>
#include "user.h"

void initializeUser(User *user, const char *username, const char *password)
{
    strncpy(user->username, username, MAX_USERNAME_LENGTH - 1);
    strncpy(user->password, password, MAX_PASSWORD_LENGTH - 1);
    user->isLoggedIn = 0;
}

int loginUser(User *user, const char *username, const char *password)
{
    if (strcmp(user->username, username) == 0 && strcmp(user->password, password) == 0)
    {
        user->isLoggedIn = 1;
        printf("Login successful. Welcome, %s!\n", username);
        return 1;
    }
    else
    {
        printf("Login failed. Please check your credentials.\n");
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
}
