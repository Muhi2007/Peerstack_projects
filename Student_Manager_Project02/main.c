#include <stdlib.h>
#include <stdio.h>

int main(){
    const char *nFile = "students.txt";
    unsigned char choice = 0; //As it is 1 byte, I thought it will be more efficient than integer which is 4 bytes
    
    printf("1-Add User\n2-Delete User\n3-Show Users\n4-Update User\n5-Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    while (choice != 5){//Case 5 is handled here
        switch (choice)
        {
        case 1:
            printf("Add User\n");
            break;
        case 2:
            printf("Delete User\n");
            break;
        case 3:
            printf("Show Users\n");
            break;
        case 4:
            printf("Delete User\n");
            break;
        default:
            break;
        }
        printf("\n1-Add User\n2-Delete User\n3-Show Users\n4-Update User\n5-Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    }
    

    return 0;
}