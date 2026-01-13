#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TABLE_LENGTH 10 //This will NOT determine the maximum size, rather speeds up the process


//----------------Structs-------------------//
typedef struct {
    unsigned int ID;
    char name[50];
    char surname[50];
    unsigned int age;
}Student;

typedef struct NodeStudent{
    unsigned int key;
    Student *student;
    struct NodeStudent *next;
}NodeStudent;

typedef struct{
    NodeStudent *arrayStudents[TABLE_LENGTH];
}StudentDictionary;

//---------------Functions-----------------//
int convert_valid_key(const unsigned int id){
    return id % TABLE_LENGTH;
}

void dict_insert(StudentDictionary *dict, unsigned int id, Student *newStu){
    unsigned int index = convert_valid_key(id);

    NodeStudent *newNode = malloc(sizeof(NodeStudent));
    newNode->key = id;
    newNode->student = newStu;
    newNode->next = NULL;

    newNode->next = dict->arrayStudents[index];//Assigns the newNode to the start
    dict->arrayStudents[index] = newNode;//Then makes the dictionary's index point to our new node (in other words start of linked list)
}

unsigned int loadUsers(StudentDictionary *dict ,const char *fName){
    FILE *fptr = fopen(fName, "r");

    //Error handling for any case//
    if (!fptr){
        printf("Error while opening the file");
        return 0; //Error code
    }

    char line[256];
    fgets(line, sizeof line, fptr);//As the first line is for names of the rows, we skip it

    unsigned int id = 0;
    unsigned int age;
    char name[50], surname[50];

    while(fscanf(fptr, "%u,%49[^,],%49[^,],%u", &id, name, surname, &age) == 4){
        Student *newStu = malloc(sizeof(Student));
        newStu->ID = id;
        newStu->age = age;
        strcpy(newStu->name, name);
        strcpy(newStu->surname, surname);
        
        dict_insert(dict, id, newStu);
    }

    fclose(fptr);
    id++;
    return id;//Returns the final id+1 of the saves, a.k.a start id of our main function
}

int saveUsers(StudentDictionary *dict, const char *fName) {
    FILE *fptr = fopen(fName, "w");

    if (!fptr) {
        printf("Error while opening the file\n");
        return 1;
    }

    fprintf(fptr, "ID,name,surname,age\n");

    for (int i = 0; i<TABLE_LENGTH; i++){
        NodeStudent *current = dict->arrayStudents[i];

        while (current != NULL){
            Student *saveStu = current->student;
            fprintf(fptr, "%u,%s,%s,%u\n", saveStu->ID, saveStu->name, saveStu->surname, saveStu->age);
            current = current->next;//As the dicitonary can have more than 1 nodes in one index
        }
    }

    fclose(fptr);
    printf("Success: Files saved successfully\n");
    return 0;
}

int is_valid_stu_str(const char *name){
    int i = 0;
    while (name[i]){
        if (!((name[i] >= 'a' && name[i] <= 'z')||(name[i] >= 'A' && name[i] <= 'Z'))){
            printf("Error: Usage of invalid characters\n");
            return 0;
        }
        i++;
    }
    return 1;
}


//-----------------------Main--------------------------//
int main(){
    const char *fName = "students.csv";
    int choice = 0;
    StudentDictionary id_Dict;
    for (int i = 0; i<TABLE_LENGTH; i++) { //For initilizing all the values with Null or 0
        id_Dict.arrayStudents[i] = NULL;
    }

    unsigned int start_id = loadUsers(&id_Dict, fName);
    if (start_id == 0) return 1; //Kills program if loadUsers() returns error message
    
    printf("1-Add User\n2-Delete User\n3-Show Users\n4-Update User\n5-Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    while (choice != 5){//Case 5 is handled here
        switch (choice)
        {
        case 1:
            Student *stu = malloc(sizeof(Student));
            char str_input[50];
            unsigned int int_input;

            printf("Enter name for student: ");
            scanf("%49s", str_input);
            while (!is_valid_stu_str(str_input)){
                printf("Enter name for student: ");
                scanf("%49s", str_input);//For the size and safety
            }
            strcpy(stu->name, str_input);

            printf("Enter surname for student: ");
            scanf("%49s", str_input);
            while (!is_valid_stu_str(str_input)){
                printf("Enter surname for student: ");
                scanf("%49s", str_input);
            }
            strcpy(stu->surname, str_input);

            printf("Enter age for student: ");
            scanf("%d", &int_input);
            while (int_input < 0 || int_input > 200){
                printf("Error: Invalid age input\n");
                printf("Enter age for student: ");
                scanf("%d", &int_input);
            }
            stu->age = int_input;
            stu->ID = start_id;

            dict_insert(&id_Dict, start_id, stu);
            start_id++;

            printf("Name: %s\nSurname: %s\nAge:%d", stu->name, stu->surname, stu->age);
            break;
        case 2:
            printf("Delete User\n");
            break;
        case 3:
            printf("Show Users\n");
            break;
        case 4:
            printf("Update User\n");
            break;
        default:
            printf("Error: Invalid input. Please enter values betweem 1 and 5\n");
            break;
        }
        printf("\n1-Add User\n2-Delete User\n3-Show Users\n4-Update User\n5-Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
    }

    saveUsers(&id_Dict, fName);
    printf("Goodbye!");
    return 0;
}