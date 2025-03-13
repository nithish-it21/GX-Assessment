#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include "base.c"

#define PORT 8888

typedef struct {
    char *username;
    char *password;
    char *email;
} PostData;

USER user_info = {0};

int send_response(struct MHD_Connection *connection, const char *response_text, int status_code) {
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_text), (void*)response_text, MHD_RESPMEM_PERSISTENT);
    MHD_add_response_header(response, "Access-Control-Allow-Origin", "*");
    MHD_add_response_header(response, "Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    MHD_add_response_header(response, "Access-Control-Allow-Headers", "Content-Type");
    int ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);
    return ret;
}

static int post_iterator(void *cls, enum MHD_ValueKind kind, const char *key,
                         const char *filename, const char *content_type,
                         const char *transfer_encoding, const char *data,
                         uint64_t off, size_t size) {
    PostData *post_data = (PostData *)cls;
    if (strcmp(key, "username") == 0) {
        strcpy(user_info.NAME, data);
    } else if (strcmp(key, "password") == 0) {
        strcpy(user_info.PASSWORD, data);
    } else if (strcmp(key, "email") == 0) {
        strcpy(user_info.EMAIL, data);
    }
    return MHD_YES;
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                 const char *url, const char *method,
                                 const char *version, const char *upload_data,
                                 size_t *upload_data_size, void **con_cls) {

    if (strcmp(method, "POST") != 0) {
        return send_response(connection, "Unsupported method", MHD_HTTP_METHOD_NOT_ALLOWED);
    }

    if (*con_cls == NULL) {
        PostData *post_data = calloc(1, sizeof(PostData));
        struct MHD_PostProcessor *pp = MHD_create_post_processor(connection, 1024, post_iterator, post_data);
        if (!pp) {
            free(post_data);
            return MHD_NO;
        }
        *con_cls = pp;
        return MHD_YES;
    }

    struct MHD_PostProcessor *pp = *con_cls;
    PostData *post_data = NULL;
    if (*upload_data_size != 0) {
        MHD_post_process(pp, upload_data, *upload_data_size);
        *upload_data_size = 0;
        return MHD_YES;
    } else {
        post_data = (PostData *)(*con_cls);
    }

    if (strcmp(url, "/login") == 0) {
        if (!post_data->username || !post_data->password) {
            return send_response(connection, "Missing credentials", MHD_HTTP_BAD_REQUEST);
        }

        printf("Login - Username: %s, Password: %s\n", user_info.NAME, user_info.PASSWORD);
        int login_result = login_user(&user_info);
        if (login_result == 1) {
            return send_response(connection, "Login successful", MHD_HTTP_OK);
        } 
        else if (login_result == 2)
        {
            return send_response(connection,"Incorrect Username or PassWord", MHD_HTTP_UNAUTHORIZED);
        }
        else{
            return send_response(connection, "Invalid credentials", MHD_HTTP_UNAUTHORIZED);
        }
    }
    
    if (strcmp(url, "/register") == 0) {
        if (!post_data->username || !post_data->password || !post_data->email) {
            return send_response(connection, "Missing registration data", MHD_HTTP_BAD_REQUEST);
        }

        printf("Registration - Username: %s, Password: %s, Email: %s\n", user_info.NAME, user_info.PASSWORD, user_info.EMAIL);
        int register_result = register_user(&user_info);
        if(register_result==2){
            printf("User Name Already Found\n\n");
            return send_response(connection, "User Name Already Found", MHD_HTTP_UNAUTHORIZED);
            return 2;
        }
        else if(register_result==3){
            printf("Email Already Found.\n\n");
            return send_response(connection, "Email Already Found.", MHD_HTTP_UNAUTHORIZED);
            return 3;
        }	
        else if(register_result==1){
            printf("User Already Found.\n\n");
            return send_response(connection, "User Already Found.", MHD_HTTP_UNAUTHORIZED);
            return 1;
        }
        return send_response(connection, "Registration successful", MHD_HTTP_OK);
    }

    return send_response(connection, "Not found", MHD_HTTP_NOT_FOUND);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (daemon == NULL) {
        fprintf(stderr, "Error starting server.\n");
        return 1;
    }

    printf("Server running on http://localhost:%d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}
