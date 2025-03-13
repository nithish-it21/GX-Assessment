#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#define max_limit 256

static int count_file = 0;

void update_file_count() {
    DIR* dr;
    struct dirent *dir;
    count_file = 0;
    dr = opendir("./str_dir");
    if (dr) {
        while ((dir = readdir(dr)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                count_file++;
            }
        }
        closedir(dr);
    }
}

void print_file_dir() {
    update_file_count();

    DIR* dr;
    struct dirent *dir;
    dr = opendir("./str_dir");
    if (dr) {
        while ((dir = readdir(dr)) != NULL) {
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                continue;
            }
            printf("%s %d\n", dir->d_name,dir->d_reclen);
        }
        closedir(dr);
    }

    if (count_file == 0) {
        printf("No files in the Directory.\n");
    }
    printf("\n");
}

void print_file() {
    char *ch = (char *)malloc(max_limit * sizeof(char));
    char *buff = (char *)malloc(max_limit * sizeof(char));
    printf("Enter the file name: ");
    scanf("%[^\n]", ch);

    FILE *fp = NULL;
    DIR *dr;
    struct dirent *dir;
    dr = opendir("./str_dir");
    int count = 0;

    if (dr) {
        while ((dir = readdir(dr)) != NULL) {
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                continue;
            }

            if (strcmp(ch, dir->d_name) == 0) {
                char filepath[max_limit];
                snprintf(filepath, sizeof(filepath), "./str_dir/%s", ch);
                fp = fopen(filepath, "r+");
                if (fp) {
                    while (fgets(buff, max_limit, fp) != NULL) {
                        printf("%s", buff);
                    }
                    count++;
                    fclose(fp);
                } else {
                    printf("Error opening the file: %s\n", ch);
                }
            }
        }
        closedir(dr);
    }

    free(ch);
    free(buff);

    if (count_file == 0) {
        printf("No files in the Directory.\n");
    }

    if (count == 0) {
        printf("File not found\n\n");
    }

    printf("\n");
}

void remove_file() {
    char *ch = (char *)malloc(max_limit * sizeof(char));
    printf("Enter the file name: ");
    scanf("%[^\n]", ch);
    char filepath[max_limit];
    snprintf(filepath, max_limit, "./str_dir/%s", ch);
    FILE *file = fopen(filepath, "r");
    if (file) {
        fclose(file);
        if (remove(filepath) == 0) {
            update_file_count();  
            printf("Deleted successfully\n\n");
        }
    } else {
        printf("File not found\n\n");
    }

    if (count_file == 0) {
        printf("No files in the Directory.\n");
    }

    free(ch);
}

void remove_file_all() {
    DIR* dr;
    struct dirent* dir;
    dr = opendir("./str_dir");
    if (dr) {
        while ((dir = readdir(dr)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                char file_path[max_limit];
                snprintf(file_path, max_limit+10, "./str_dir/%s", dir->d_name);
                remove(file_path);
            }
        }
        closedir(dr);
    }

    update_file_count();
    printf("All files are removed successfully\n");
}

void main() {
    while (1) {
        printf("Operations\n");
        printf("1. Display the files\n");
        printf("2. Display the content in file\n");
        printf("3. Remove file\n");
        printf("4. Remove all File\n");
        printf("5. Exit\n\n");
        int choice;
        printf("Enter :");
        if (scanf("%d", &choice) != 1) {
            perror("Invalid entry, enter only integer [1-4].\n\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();
        if (choice == 1) {
            print_file_dir();
        } else if (choice == 2) {
            print_file();
        } else if (choice == 3) {
            remove_file();
        } else if (choice == 4) {
            remove_file_all();
        } else if (choice == 5) {
            printf("Exiting.....\n");
            return;
        } else {
            printf("Invalid entry, enter only integer [1-4].\n\n");
        }
    }
}

