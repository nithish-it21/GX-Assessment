#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#define max_limit 255

typedef struct USER
{
    char NAME[255];
    char PASSWORD[255];
    char EMAIL[255];
}USER;

int login_user(USER* info){

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int partial_user = 0;
	int partial_email = 0;

	conn = mysql_init(NULL);
	if(conn == NULL){
		fprintf(stderr,"Unable to intialize variable.\n");
		exit(1);
	}
	if(mysql_real_connect(conn,"localhost", "nithish", "", "login_system", 0, NULL, 0) == NULL){
		fprintf(stderr,"Unable to connect to database/\n");
		mysql_close(conn);
		exit(1);
	}
	
	if(mysql_query(conn,"SELECT * FROM users")){
		fprintf(stderr,"Unable to execute the querry");
		mysql_close(conn);
		exit(1);
	}
	
	res = mysql_store_result(conn);
	while((row = mysql_fetch_row(res)) != NULL){
		int found_user = 0;
		int found_pass = 0;
		for(int i=0; i<mysql_num_fields(res); i++){
			if(strcmp(row[i],info->NAME)==0){
				found_user = 1;
			}
			if(strcmp(row[i], info->PASSWORD)==0){
				found_pass = 1;
			}
			if(sizeof(info->EMAIL)!=0 && strcmp(row[i],info->EMAIL)==0){
				partial_email = 1;
			}
		}
		if(found_user){
			partial_user = 1;
		}
		if(found_pass && found_user){
			//printf("printing");
			if(strcmp("admin",info->NAME)==0){
				int opt;
				while (1)
				{
					printf("1.To Display the users.\n");
					printf("2.Exit.\n\n");

					printf("Enter the choice: ");
					if(scanf("%d",&opt)!=1){
						printf("Inavlid entry, enter only Integer.");
						while(getchar()!='\n');
						continue;
					}
					if(opt==1){
							if (mysql_query(conn,"SELECT * FROM users"))
							{
								fprintf(stderr,"unable to execute the query");
								break;
							}
							MYSQL_RES* res2 = mysql_store_result(conn);
							MYSQL_ROW row2;
							printf("%-20s %-20s %-20s %-20s %-20s\n","Id","Username","Password","Email","Timestamp");
							while((row2=mysql_fetch_row(res2))!=NULL){
								for(int i=0; i<mysql_num_fields(res2); i++){
									printf("%-20s ",row2[i]);
								}
								printf("\n");
							}
							
					}
					else if (opt==2)
					{
						printf("Exiting");
						break;
					}
					else
					{
						printf("Enter the correct operation [1-2].\n");	
					}
				}
				
			}
			return 1;
		}
		printf("\n");
	}
	if(partial_user){
		return 2;
	}
	if(partial_email){
		return 3;
	}
	mysql_free_result(res);
	mysql_close(conn);
	return 0;
}

int register_user(USER* register_info){
    char* buff = (char*)malloc(sizeof(char) * max_limit); 
	int SUCCESS = login_user(register_info);
	if(SUCCESS==2){
		//Successfull login here
		printf("User Name Already Found\n\n");
		//register_user(register_info);
		return 2;
	}
	else if(SUCCESS==3){
		printf("Email Already Found.\n\n");
		//register_user(register_info);
		return 3;
	}	
	else if(SUCCESS==1){
		printf("User Already Found.\n\n");
		return 1;
	}
	MYSQL *conn;
	// MYSQL_RES *res;
	// MYSQL_ROW row;
	//printf("here");
	conn = mysql_init(NULL);
	if(conn == NULL){
		fprintf(stderr,"Unable to intialize the connection %s\n",mysql_error(conn));
		return 0;
	}

	if(mysql_real_connect(conn,"localhost","nithish","","login_system",0,NULL,0)==NULL){
		fprintf(stderr,"unable to connect to the database %s\n",mysql_error(conn));
		mysql_close(conn);
		return 0;
	}

	sprintf(buff,"INSERT INTO users(username, password, email) VALUES ('%s','%s','%s');",
        register_info->NAME,register_info->PASSWORD,register_info->EMAIL);
	
	if(mysql_query(conn,buff)){
			fprintf(stderr,"Unable to add the user %s",mysql_error(conn));
			mysql_close(conn);
			return 0;
	}else{
			printf("Registration Successfull.\n\n");
	}
}


 
