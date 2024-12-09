#include <stdio.h>

// Question 1 -------------------------------------------------

typedef struct { int day, month, year; } Date;
typedef struct { int hour, minute; } Time;
typedef struct { char country[2], city[50]; } Location; // example: MA, FR ... 

typedef struct {
    int matricule;
    char cin[7];
    char nationality[2];
    char fulll_name[50 * 2];
    Date birth_day;
} Person; // Etudiant ou Enseignant

typedef struct {
    int exam_num;
    Person student;
    float grade; // Note
} Test_Copy;

typedef struct {
    struct { Date date; Time time; } datetime;
    char subject[50];
    Person teacher;
    int copy_count;
    Test_Copy copy_list[];
} Test; // Epreuve

typedef struct {
    char branch[50]; // Filière
    int semestre;
    int tests_count;
    Test tests_list[];
} Examen;

typedef struct {
    char rs; // raison sociale
    int capacity;
    Date created_at;
    Location localisation;
    Examen exam_list[100];
} Establissement;

// Question 2 -------------------------------------------------

typedef struct {
    int counter;
    Establissement establissements[20];
} STR_UH2;

// Question 3 -------------------------------------------------

void addEstablissement(STR_UH2 *university, int num) {
    for (int i = 0; i < num; i++) {
        if (university->counter >= 20) { continue; }

        printf("############################## Establissement: %d ##############################\n", i);

        Establissement *current_establissement = &university->establissements[university->counter++];

        printf("Enter the RS of Establissement: ");
        scanf("%s", &current_establissement->rs);

        printf("Enter creation date (day month year): ");
        scanf(
            "%d %d %d",
            &current_establissement->created_at.day,
            &current_establissement->created_at.month,
            &current_establissement->created_at.year
        );

        printf("Enter location (city and country<(2-letter code)>): ");
        scanf("%s %s", current_establissement->localisation.city, current_establissement->localisation.country);

        printf("Enter capacity: ");
        scanf("%d", &current_establissement->capacity);

        // Other fields if necessary ...

        printf("############################## Establissement: %d Added ##############################\n", i);
    }
}

int main()
{
    STR_UH2 university = { 0 };
    
    addEstablissement(&university, 5);

    return 0;
}
