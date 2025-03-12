#include <stdio.h>
#include <string.h>

#define SIZE 100

int main() {
    char filename[SIZE + 4];
    char inputname[SIZE];
    char login[SIZE];
    char password[SIZE];
    char passwordcheck[SIZE];
    char lineprint[SIZE];
    char linescan[SIZE];
    char edit[SIZE];
    FILE *file;

    printf("Type 'login' for existing user and 'register' for new user: ");
    scanf("%s", login);

    if (strcmp(login, "login") == 0) {
        printf("Enter user name (no space): ");
        scanf("%s", inputname);
        printf("Enter password: ");
        scanf("%s", password);
        getchar();

        strcpy(filename, inputname);
        strcat(filename, ".txt");

        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error: Could not open your file '%s'.\n", filename);
            return 1;
        }

        fscanf(file, "%s", passwordcheck);
        if (strcmp(password, passwordcheck) != 0) {
            printf("Incorrect password.\n");
            fclose(file);
            return 1;
        }

        printf("YOUR DATA:\n");
        while (fgets(lineprint, SIZE, file) != NULL) {
            printf("%s", lineprint);
        }

        printf("Type 'edit' to edit the file or 'close' to close the file: ");
        scanf("%s", edit);
        if (strcmp(edit, "edit") == 0) {
            file = fopen(filename, "a");
            if (file == NULL) {
                printf("Error: Could not open file for editing.\n");
                return 1;
            }

            printf("Enter content (type 'exit' to stop):\n");
            while (1) {
                printf("> ");
                fgets(linescan, SIZE, stdin);
                linescan[strcspn(linescan, "\n")] = 0;

                if (strcmp(linescan, "exit") == 0) {
                    break;
                }

                fprintf(file, "%s\n", linescan);
            }
            fclose(file);
            printf("File saved successfully.\n");
        } else if (strcmp(edit, "close") == 0) {
            fclose(file);
        }
    } else if (strcmp(login, "register") == 0) {
        printf("Enter user name (no space): ");
        scanf("%s", inputname);
        printf("Enter password: ");
        scanf("%s", password);
        getchar();

        strcpy(filename, inputname);
        strcat(filename, ".txt");

        file = fopen(filename, "r");
        if (file == NULL) {
            file = fopen(filename, "w");
            if (file == NULL) {
                printf("Error: Could not create file.\n");
                return 1;
            }

            fprintf(file, "%s\n", password);

            printf("Enter your content (type 'exit' to stop):\n");
            while (1) {
                printf("> ");
                fgets(linescan, SIZE, stdin);
                linescan[strcspn(linescan, "\n")] = 0;

                if (strcmp(linescan, "exit") == 0) {
                    break;
                }

                fprintf(file, "%s\n", linescan);
            }
            fclose(file);
            printf("Content saved successfully.\n");
        } else {
            fclose(file);
            printf("File already exists. Please login.\n");
        }
    } else {
        printf("Invalid input. Please type 'login' or 'register'.\n");
    }

    return 0;
}
