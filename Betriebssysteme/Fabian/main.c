#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(char *password) {
    int auth_flag = 0;
    char password_buffer[16];
    strncpy(password_buffer, password, 16);
    
    if (strcmp(password_buffer, "achtlos") == 0)
        auth_flag = 1;
    if (strcmp(password_buffer, "nikolaus") == 0)
        auth_flag = 1;
    return auth_flag;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <password>\n", argv[0]);
        exit(0);
    }
    if (check(argv[1])) {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf(" Access Granted.\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    } else {
        printf("\nAccess Denied.\n");
    }
    return EXIT_SUCCESS;
}