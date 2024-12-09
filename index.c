#include <stdio.h>
#include <string.h>

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
    char rs; // Raison sociale
    int capacity; // Nombre des examens par filière et par semestre
    Date created_at;
    Location location;
    Examen exam_list[100];
} Establishment;

// Question 2 -------------------------------------------------

typedef struct {
    int counter;
    Establishment establishments[20];
} STR_UH2;

// Question 3 -------------------------------------------------

void addEstablishments(STR_UH2 *university, int num) {
    for (int i = 0; i < num; i++) {
        if (university->counter >= 20) { continue; }

        printf("############################## Establishment: %d ##############################\n", i);

        Establishment *current_establishment = &university->establishments[university->counter++];

        printf("Enter the RS of Establishment: ");
        scanf("%s", &current_establishment->rs);

        printf("Enter creation date (day month year): ");
        scanf(
            "%d %d %d",
            &current_establishment->created_at.day,
            &current_establishment->created_at.month,
            &current_establishment->created_at.year
        );

        printf("Enter location (city and country<(2-letter code)>): ");
        scanf("%s %s", current_establishment->location.city, current_establishment->location.country);

        printf("Enter capacity: ");
        scanf("%d", &current_establishment->capacity);

        // Other fields if necessary ...

        printf("############################## Establishments: %d Added ##############################\n", i);
    }
}

// Question 4 -------------------------------------------------

void displayEstablishments(STR_UH2 *university) {
    for (int i = 0; i < university->counter; i++) {
        Establishment _establishment = university->establishments[i];
        printf(
                "Name: %s, Created at: %02d/%02d/%04d, Location: %s, %s, Capacity: %d\n",
                _establishment.rs,
                _establishment.created_at.day,
                _establishment.created_at.month,
                _establishment.created_at.year,
                _establishment.location.city,
                _establishment.location.country,
                _establishment.capacity
            );
    }
}

// Question 5 -------------------------------------------------

void modifyExamList(STR_UH2 *university, char *_rs, int _new_capacity) {
    for (int i = 0; i < university->counter; i++) {
        if (strcmp(university->establishments[i].rs, _rs) == 0) {
            university->establishments[i].capacity = _new_capacity;
            // Run update here ...
            printf("Exam list updated for %s.\n", _rs);
            return;
        }
    }
    printf("Establishment not found!\n");
}

// Question 6 -------------------------------------------------

void displayPassedExams(STR_UH2 *university, char *_cin) {
    for (int i = 0; i < university->counter; i++) {
        Establishment _establishment = university->establishments[i];
        for (int j = 0; j < _establishment.capacity; j++) {
            Examen _examen = _establishment.exam_list[j];
            for (int k = 0; k < _examen.tests_count; k++) {
                Test _test = _examen.tests_list[k];
                for (int l = 0; l < _test.copy_count; l++) {
                    Test_Copy _test_copy = _test.copy_list[k];
                    if (strcmp(_test_copy.student.cin, _cin) == 0 && _test_copy.grade >= 10) {
                        printf("Passed: %s, Grade: %.2f\n", _test.subject, _test_copy.grade);
                    }
                }
            }
        }
    }
}

// Question 7 -------------------------------------------------

void displayProgramming2Passers(STR_UH2 *university) {
    for (int i = 0; i < university->counter; i++) {
        Establishment _establishment = university->establishments[i];
        for (int j = 0; j < 10; j++) {
            Examen _examen = _establishment.exam_list[j];
            for (int k = 0; k < _examen.tests_count; k++) {
                Test _test = _examen.tests_list[k];
                if (strcmp(_test.subject, "Programming 2") == 0) {
                    for (int l = 0; l < _test.copy_count; l++) {
                        Test_Copy _test_copy = _test.copy_list[l];
                        if (_test_copy.grade >= 10) {
                            printf(
                                "Student: %s,Passed Programming 2 with Grade: %.2f\n",
                                _test_copy.student.fulll_name,
                                _test_copy.grade
                            );
                        }
                    }
                }
            }
        }
    }
}

// Question 8 -------------------------------------------------

int catch_up_count(Test *test) { // rattrapage count
    int _count = 0;
    for (int i = 0; i < test->copy_count; i++) {
        if (test->copy_list[i].grade < 10) {
            _count++;
        }
    }
    return _count;
}

void drop_SMPC_S5_max_catchUp_test(STR_UH2 *university) {
    for (int i = 0; i < university->counter; i++) {
        Establishment _establishment = university->establishments[i];
        for (int j = 0; j < 10; j++) {
            Examen _examen = _establishment.exam_list[j];
            if ((strcmp(_examen.branch, "SMPC") == 0) && (_examen.semestre == 5)) {
                int max_catchUp = 0;
                int max_catchUp_test_idx = 0; // Index of the TEST with max catch-ups
                for (int k = 0; k < _examen.tests_count; k++) {
                    Test _test = _examen.tests_list[k];
                    int _catchUp = catch_up_count(&_test);
                    if (_catchUp > max_catchUp) {
                        max_catchUp = _catchUp;
                        max_catchUp_test_idx = k;
                    }
                }
                
                for (int p = max_catchUp_test_idx; p < _examen.tests_count - 1; p++) { // Drop Test
                    _examen.tests_list[p] = _examen.tests_list[p + 1];
                };

                _examen.tests_count--;

                return;
            };
        }
    }
}

// Question 9 -------------------------------------------------

void exportToTextFile(const char *filename, Test tests[]) {
    int size = sizeof(tests) / sizeof(tests[0]);

    FILE *file = fopen(filename, "w"); // Open file in write mode
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write a header
    fprintf(file, "Subject,Date,Time,Teacher\n");

    for (int i = 0; i < size; i++) {
        Test _test = tests[i];
        fprintf(
                file, 
                "%s,%02d/%02d/%04d,%02d:%02d,%s\n",
                _test.subject,
                _test.datetime.date.day,
                _test.datetime.date.month,
                _test.datetime.date.year,
                _test.datetime.time.hour,
                _test.datetime.time.minute,
                _test.teacher.fulll_name
            );
    }

    fclose(file); // Close the file
    printf("Data exported to %s successfully.\n", filename);
}

void export_SMPC_S3_tests(STR_UH2 *university) {
    for (int i = 0; i < university->counter; i++) {
        Establishment _establishment = university->establishments[i];
        for (int j = 0; j < 10; j++) {
            Examen _examen = _establishment.exam_list[j];
            if ((strcmp(_examen.branch, "SMPC") == 0) && (_examen.semestre == 3)) {
                exportToTextFile('SMPC_S3_tests.txt', _examen.tests_list);
                return;
            };
        }
    }
}

// Question 10 -------------------------------------------------

int readFromTextFile(const char *filename, Test tests[]) {
    int size = sizeof(tests) / sizeof(tests[0]);

    FILE *file = fopen(filename, "r"); // Open file in read mode
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int count = 0;

    // Read data line by line
    while (fscanf(
        file,
        "%50[^,],%d,%d,%d,%d,%d,%100[^,]",
        &tests[count].subject,
        &tests[count].datetime.date.day,
        &tests[count].datetime.date.month,
        &tests[count].datetime.date.year,
        &tests[count].datetime.time.hour,
        &tests[count].datetime.time.minute,
        &tests[count].teacher.fulll_name
    ) == 7) { count++; }

    fclose(file); // Close the file

    printf("Data read from %s successfully.\n", filename);

    return count;
}

void import_SMPC_3_tests(STR_UH2 *university) {
    for (int i = 0; i < university->counter; i++) {
        Establishment _establishment = university->establishments[i];
        for (int j = 0; j < 10; j++) {
            Examen _examen = _establishment.exam_list[j];
            if ((strcmp(_examen.branch, "SMPC") == 0) && (_examen.semestre == 3)) {
                readFromTextFile('SMPC_S3_tests.txt', _examen.tests_list);
                return;
            };
        }
    }
}

int main()
{
    STR_UH2 university = { 0 };
    
    addEstablishments(&university, 5);

    return 0;
}
