#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_LIMIT 1000


void view_files() {
    DIR *dir;
    struct dirent *dr;
    struct stat filestat;
    char *filedir = "./str_dir";
    dir = opendir(filedir);
    char buff[1024];
    printf("%-20s%-20s\n", "File", "Size");

    if (dir) {
        while ((dr = readdir(dir)) != NULL) {
            if (strcmp(dr->d_name, ".") == 0 || strcmp(dr->d_name, "..") == 0) {
                continue;
            }
            snprintf(buff, sizeof(buff), "./str_dir/%s", dr->d_name);
            if (stat(buff, &filestat) == 0) {
                printf("%-20s%ld bytes\n", dr->d_name, filestat.st_size);
            }
        }
        closedir(dir);
    } else {
        printf("Directory not exists.\n");
    }
}

void process_file() {
    DIR *dir;
	printf("===============================\n");
    struct dirent *dr;
    struct stat filestat;
    char filepath[1024];
    FILE *fp, *cache;
    char *ch = (char *)malloc(sizeof(char) * MAX_LIMIT);
    
    dir = opendir("./str_dir");
    if (dir) {
        while ((dr = readdir(dir)) != NULL) {
            if (strcmp(dr->d_name, ".") == 0 || strcmp(dr->d_name, "..") == 0) {
                continue;
            }
            snprintf(filepath, sizeof(filepath), "./str_dir/%s", dr->d_name);

            if (stat(filepath, &filestat) == 0) {
                while (filestat.st_size > 1024) {
                    fp = fopen(filepath, "r");
                    if (!fp) {
                        perror("Failed to open file");
                        break;
                    }

                    cache = fopen("./str_dir/cache.txt", "w+");
                    if (!cache) {
                        perror("Failed to open cache file");
                        fclose(fp);
                        break;
                    }

                    int count = 0;

                    while (count < 10 && fgets(ch, MAX_LIMIT, fp) != NULL) {
                        count++;
                    }

                    while (fgets(ch, MAX_LIMIT, fp) != NULL) {
                        fputs(ch, cache);
                    }

                    fclose(fp);
                    fclose(cache);

                    remove(filepath);
                    rename("./str_dir/cache.txt", filepath);

                    stat(filepath, &filestat);
                }
            }
        }
        closedir(dir);
    } else {
        perror("Directory does not exist");
        free(ch);
        return;
    }
    free(ch);
    view_files();
	printf("====================================\n");
    printf("All files processed successfully.\n");
	printf("====================================\n");
}



void file_append() {
    DIR* dr;
    struct dirent* dir;
    struct stat filestat;
    char* filepath = "./str_dir";
    dr = opendir(filepath);
    int check_file = 0;
    char* buff = (char*)malloc(MAX_LIMIT * sizeof(char));
    char str[MAX_LIMIT];
    char ch[MAX_LIMIT];
    printf("Enter the file name: ");
    scanf("%[^\n]", str);
    getchar();
	
    if (dr) {
        while ((dir = readdir(dr)) != NULL) {
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                continue;
            }

            if (strcmp(dir->d_name, str) == 0) {
            	check_file = 1;
                snprintf(buff, MAX_LIMIT, "./str_dir/%s", dir->d_name);
                FILE* fp = fopen(buff, "a+");
                if (!fp) {
                    printf("Failed to open the file for appending.\n");
                    free(buff);
                    closedir(dr);
                    return;
                }
                printf("Enter the string: ");
                char* temp_str = (char*)malloc(MAX_LIMIT * sizeof(char));
                scanf("%[^\n]", temp_str);
                getchar();
                fputs(temp_str, fp);
                free(temp_str);

                fclose(fp);
                

                if (stat(buff, &filestat) == 0) {
	printf("=========================================\n");
                    printf("File size before appending: %ld bytes\n", filestat.st_size);
                    

                    while (filestat.st_size > 1024) {
                        FILE* cache = fopen("./str_dir/cache.txt", "w+");
                        if (!cache) {
                            printf("Failed to open cache file.\n");
                            return;
                        }


                        fp = fopen(buff, "r");
                        if (!fp) {
                            printf("Failed to open the file for reading.\n");
                            fclose(cache);
                            return;
                        }


                        fgets(ch, MAX_LIMIT, fp);


                        while (fgets(ch, MAX_LIMIT, fp) != NULL) {
                            fputs(ch, cache);
                        }


                        fclose(fp);
                        fclose(cache);


                        remove(buff);
                        rename("./str_dir/cache.txt", buff);


                        stat(buff, &filestat);
                    }


                    printf("File size after processing: %ld bytes\n", filestat.st_size);
	printf("=========================================\n");
                }
            }
        }
        if(check_file==0){
        	printf("\nFile not exists in the directory.\n");
        }
        closedir(dr);
    } else {
        printf("Unable to open the directory.\n");
    }

    free(buff);
}





void main() {
    while (1) {
	printf("===============================\n");
        printf("File Operation\n");
	printf("--------------\n");
        printf("\t1. View File Info\n");
        printf("\t2. Process Files\n");
        printf("\t3. Append in a File\n");
        printf("\t4. Exit\n");
	printf("===============================\n");
        printf("\n");
	printf("Enter the Operation: ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            while(getchar()!='\n');
            printf("Invalid entry, enter only integer\n\n");
            continue;
        }
        getchar();
        if (choice == 1) {
            view_files();
        } else if (choice == 2) {
            process_file();
        } else if (choice == 3) {
            file_append();
        } else if (choice == 4) {
            printf("Exiting....\n");
            return;
        } else {
            printf("Invalid entry, enter only integer [1-4]\n");
        }
        printf("\n");
    }
}

