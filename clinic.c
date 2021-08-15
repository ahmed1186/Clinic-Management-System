/*********************************************

  Author        :    Ahmed Adel Radwan
  Date          :    15/8/2021
  Github        :    https://github.com/ahmed1186
  Description   :    Clinic Mangament System
  
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 255
#define MAX_NAME_LENGTH 50

const int default_admin_password = 1234;
int current_records_count = 0;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int id;
    int age;
    char gender;
}patient;

patient *patients_array[MAX_RECORDS];
int reservation_slots[6] = {-1, -1, -1, -1, -1, -1};

void view_record(void)
{
    printf("\nUser mode --> View patient record\n");
    printf("-------------------------------------\n");
    int patient_id = -1;
    do
    {
        printf("Enter patient ID to view record (max is 255): ");
        scanf("%d", &patient_id);
    }
    while(patient_id < 0 || patient_id > 255);

    if(search_patients(patients_array, current_records_count, patient_id) == -1)
    {
        printf("\n*No patient with the provided ID was found*\n");
        printf("*Press any key to return*\n");
        fflush(stdin);
        if(getchar())
            return;
    }

    int index = search_patients(patients_array, current_records_count, patient_id);
    printf(" Patient name: %s Patient ID: %d\n Patient Age: %d\n Pateint gender: %c\n", 
            patients_array[index]->name,
            patients_array[index]->id,
            patients_array[index]->age,
            patients_array[index]->gender);

    printf("*Press any key to return*\n");
    fflush(stdin);
    if(getchar())
        return;
}

void view_reservations(void)
{
    printf("\nUser mode --> Viewing reservations\n");
    printf("-------------------------------------\n");
    if(reservation_slots[1] == -1 && reservation_slots[2] == -1 && reservation_slots[3] == -1 && 
        reservation_slots[4] == -1 && reservation_slots[5] == -1)
    {
        printf("*All slots are free*\n");
    }
    else
    {
        printf("*Reserved doctor slots are:\n");
        if(reservation_slots[1] != -1)
            printf(" Slot 1: 2:00PM to 2:30PM\n");
        if(reservation_slots[2] != -1)
            printf(" Slot 2: 2:30PM to 3:00PM\n");
        if(reservation_slots[3] != -1)
            printf(" Slot 3: 3:00PM to 3:30PM\n");
        if(reservation_slots[4] != -1)
            printf(" Slot 4: 4:00PM to 4:30PM\n");
        if(reservation_slots[5] != -1)
            printf(" Slot 5: 4:30PM to 5:00PM\n");
    }

    printf("*Press any key to return*\n");
    fflush(stdin);
    if(getchar())
        return;
}

void print_available_slots(void)
{   
    printf(" Available doctor slots are:\n");
    if(reservation_slots[1] == -1)
        printf("  Slot 1: 2:00PM to 2:30PM\n");
    if(reservation_slots[2] == -1)
        printf("  Slot 2: 2:30PM to 3:00PM\n");
    if(reservation_slots[3] == -1)
        printf("  Slot 3: 3:00PM to 3:30PM\n");
    if(reservation_slots[4] == -1)
        printf("  Slot 4: 4:00PM to 4:30PM\n");
    if(reservation_slots[5] == -1)
        printf("  Slot 5: 4:30PM to 5:00PM\n");
}

int search_patients(patient *patients[], int size, int desired_id)
{
    int index = -1;
    for(int i = 0; i < size; i++)
    {
        if(patients[i]->id == desired_id)
        {
            index = i;
            break;
        }
    }
    
    return index;
}

void admin_add_new_patient(void)
{   
    printf("\nAdmin mode --> Adding new patient record\n");
    printf("------------------------------------------\n");
    patient *new_patient_ptr = (patient *) malloc(sizeof(patient));

    printf(" Enter new patient name: ");
    fflush(stdin);
    fgets(new_patient_ptr->name, MAX_NAME_LENGTH, stdin);

    int new_id = -1;
    do
    {
        printf(" Enter new patient ID (max is 255): ");
        scanf("%d", &new_id);
    }
    while(new_id < 0 || new_id > 255);
    
    while(search_patients(patients_array, current_records_count, new_id) != -1)
    {
        printf(" A patient with the same ID already exists, Enter a different ID: ");
        scanf("%d", &new_id);
        while(new_id < 0 || new_id > 255)
        {
            printf(" Enter patient new ID (max is 255): ");
            scanf("%d", &new_id);
        }
    }
    new_patient_ptr->id = new_id;

    int new_age = -1;
    do
    {
        printf(" Enter new patient age (must be positive number): ");
        scanf("%d", &new_age);
    }
    while(new_age < 0);
    new_patient_ptr->age = new_age;

    char new_gender;
    do
    {
        printf(" Enter new patient gender (must be M or F only): ");
        fflush(stdin);
        new_gender = getchar();
    }
    while(new_gender != 'M' && new_gender != 'F' && new_gender != 'm' && new_gender != 'f');
    new_patient_ptr->gender = new_gender;

    patients_array[current_records_count] = new_patient_ptr;
    current_records_count++;

    printf("\n*New patient record added successfully.*\n");
    printf("*Press any key to return*\n");
    fflush(stdin);
    if(getchar())
        return;
}

void admin_edit_patient_record(void)
{
    printf("\nAdmin mode --> Editing patient record\n");
    printf("-----------------------------------------\n");
    int patient_id = -1;
    do
    {
        printf("\n Enter patient ID to edit a record: ");
        scanf("%d", &patient_id);
    }
    while(patient_id < 0 || patient_id > 255);

    if(search_patients(patients_array, current_records_count, patient_id) == -1)
    {
        printf("\n*No records found for the provided ID.*\n");
        printf("*Press any key to return*\n");
        fflush(stdin);
        if(getchar())
            return;
    }

    int patient_index = search_patients(patients_array, current_records_count, patient_id);
    int operation = 0;
    printf("  1- Edit patient name.\n  2- Edit patient ID.\n  3- Edit patient age.\n  4- Edit patient gender\n\n");
    do
    {
        printf("  Enter yor choice: ");
        scanf("%d", &operation);
    }
    while(operation < 1 || operation > 4);

    if(operation == 1)
    {
        printf("   Enter patient new name: ");
        fflush(stdin);
        fgets(patients_array[patient_index]->name, MAX_NAME_LENGTH, stdin);
        printf("\n*Patient name is changed successfully.*\n");
    }

    else if(operation == 2)
    {   
        int new_id = -1;
        do
        {
            printf("   Enter patient new ID (max is 255): ");
            scanf("%d", &new_id);
        }
        while(new_id < 0 || new_id > 255);
        
        while(search_patients(patients_array, current_records_count, new_id) != -1)
        {
            printf("   A patient with the same ID already exists, Enter a different ID: ");
            scanf("%d", &new_id);
            while(new_id < 0 || new_id > 255)
            {
                printf("   Enter patient new ID (max is 255): ");
                scanf("%d", &new_id);
            }
        }

        patients_array[patient_index]->id = new_id;
        printf("\n*Patient ID is changed successfully.*\n");
    }

    else if(operation == 3)
    {
        int new_age = -1;
        do
        {
            printf("   Enter patient new age (must be positive number): ");
            fflush(stdin);
            scanf("%d", &new_age);
        }
        while(new_age < 0);

        patients_array[patient_index]->age = new_age;
        printf("\n*Patient age is changed successfully.*\n");
    }
    else if(operation == 4)
    {
        char new_gender = -1;
        do
        {
            printf("   Enter patient new gender (must be M or F only): ");
            fflush(stdin);
            scanf("%c", &new_gender);
        }
        while(new_gender != 'M' && new_gender != 'F' && new_gender != 'm' && new_gender != 'f');

        patients_array[patient_index]->gender = new_gender;
        printf("\n*Patient gender is changed successfully.*\n");        
    }

    printf("*Press any key to return*\n");
    fflush(stdin);
    if(getchar())
        return;
}

void admin_reserve_slot(void)
{
    printf("\nAdmin mode --> Doctor slot reservation\n");
    printf("-----------------------------------------\n");
    int patient_id = -1;
    do
    {
        printf(" Enter patient ID to reserve a slot: ");
        scanf("%d", &patient_id);
    }
    while(patient_id < 0 || patient_id > 255);

    if(search_patients(patients_array, current_records_count, patient_id) == -1)
    {
        printf("\n*No patient with the provided ID was found*\n");
        printf("*Press any key to return*\n");
        fflush(stdin);
        if(getchar())
            return;
    }
    for(int i = 1; i <= 5; i++)
    {
        if(reservation_slots[i] == patient_id)
        {
            printf("*Can't reserve, This patient has already reserved slot %d*\n", i);
            printf("*Press any key to return*\n");
            fflush(stdin);
            if(getchar())
                return;
        }
    }

    int desired_slot = -1;
    print_available_slots();
    printf(" Enter one slot from the list to reserve: ");
    scanf("%d", &desired_slot);
    while(desired_slot < 1 || desired_slot > 5 || reservation_slots[desired_slot] != -1)
    {
        printf(" Enter a valid slot number from the list: ");
        scanf("%d", &desired_slot);    
    }

    reservation_slots[desired_slot] = patient_id;
    printf("\n*Slot %d is reserved successfully.*\n", desired_slot);
    printf("*Press any key to return*\n");
    fflush(stdin);
    if(getchar())
        return;
}

void admin_cancel_reservation(void)
{
    printf("\nAdmin mode --> Cancel reservation\n");
    printf("-------------------------------------\n");
    int patient_id = -1;
    do
    {
        printf(" Enter patient ID to cancel a reservation: ");
        scanf("%d", &patient_id);
    }
    while(patient_id < 0 || patient_id > 255);

    while(search_patients(patients_array, current_records_count, patient_id) == -1)
    {
        printf(" No patient with the provided ID was found, Enter a correct ID: ");
        scanf("%d", &patient_id);
        while(patient_id < 0 || patient_id > 255)
        {
            printf(" Enter patient ID to cancel a reservation: ");
            scanf("%d", &patient_id);
        }
    }

    int corresponding_slot = 0;
    for(int i = 1; i <= 5; i++)
    {
        if(reservation_slots[i] == patient_id)
        {
            corresponding_slot = i;
            break;
        }
    }
    if(corresponding_slot != 0)
    {
        reservation_slots[corresponding_slot] = -1;
        printf("\n*Reservation cancelled successfully.*\n");
    }
    else
    {
        printf("\n*This patient has no reservations. Nothing was cancelled.*\n");
    }
    printf("*Press any key to return*\n");
    fflush(stdin);
    if(getchar())
        return;
}


int main(void)
{
    int mode = 0;
    int admin_function = 0;
    int user_function = 0;

    printf("Welcome to hospital system\n");
    printf("===========================\n");

    while(1)
    {
        printf("\n------------------------");
        printf("\nAvalaible system modes:\n");
        printf("------------------------\n");
        printf(" 1- Admin mode\n 2- User mode\n");
        do
        {
            printf("\nEnter mode of choice: ");
            scanf("%d", &mode);
        }
        while(mode < 1 || mode > 2);

        if(mode == 1)
        {
            while(1)
            {
                printf("\n---------------------------");
                printf("\nAvailable admin functions:\n");
                printf("---------------------------\n");
                printf(" 1- Add a new patient record\n");
                printf(" 2- Edit existing patient record\n");
                printf(" 3- Reserve a slot with a doctor\n");
                printf(" 4- Cancel a reservation\n");
                printf(" 5- Go back\n");
                printf("\nEnter desired function: ");
                scanf("%d", &admin_function);            
                while(admin_function > 5 || admin_function < 1)
                {
                    printf("Enter a valid admin function: ");
                    scanf("%d", &admin_function);
                }

                if(admin_function == 1)
                {
                    if(current_records_count == 255)
                    {
                        printf("\n*Database is full, can't add new patients.*\n");
                    }
                    else
                    {
                        admin_add_new_patient();
                    }
                }
                if(admin_function == 2)
                {
                    admin_edit_patient_record();
                }
                if(admin_function == 3)
                {
                    admin_reserve_slot();
                }
                if(admin_function == 4)
                {
                    admin_cancel_reservation();
                }
                if(admin_function == 5)
                {
                    break;
                }
            }
        }
        if(mode == 2)
        {
            while(1)
            {
                printf("\n---------------------------");
                printf("\nAvailable user functions:\n");
                printf("---------------------------\n");
                printf(" 1- View existing patient record\n");
                printf(" 2- View today's reservations\n");
                printf(" 3- Go back\n");
                printf("\nEnter desired function: ");     
                scanf("%d", &user_function);            
                while(user_function > 3 || user_function < 1)
                {
                    printf("Enter a valid user function: ");
                    scanf("%d", &user_function);
                }

                if(user_function == 1)
                {      
                    view_record(); 
                }
                if(user_function == 2)
                {
                    view_reservations();
                }
                if(user_function == 3)
                {
                    break;
                }   
            }
        }
    }
	
	return 0;
}