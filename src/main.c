# Hospital-Patient-Record-System

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50
#define NUM_DEPT 4

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    int priority;   // 1=Emergency 2=Normal 3=Routine
};

struct Queue {
    struct Patient list[MAX];
    int front, rear, count;
};

struct Doctor {
    char name[30];
    char spec[30];      
    char room[10];
    char timing[20];
};


struct Queue deptQueue[NUM_DEPT];

struct Doctor doctors[NUM_DEPT] = {
    {"Dr. Rajesh Arora",  "Orthopedic",  "Room 101", "9AM-1PM"},
    {"Dr. Sneha Mehta",   "Dermatology", "Room 102", "10AM-2PM"},
    {"Dr. Anil Sharma",   "Cardiology",  "Room 103", "8AM-12PM"},
    {"Dr. Priya Gupta",   "General",     "Room 104", "9AM-5PM"}
};

char deptName[NUM_DEPT][20] = {
    "Orthopedic", "Dermatology", "Cardiology", "General"
};

int next_id = 101;



void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isEmpty(struct Queue *q) {
    return q->count == 0;
}

int isFull(struct Queue *q) {
    return q->count == MAX;
}

void enqueue(struct Queue *q, struct Patient p) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->list[q->rear] = p;
    q->count++;
}

struct Patient dequeue(struct Queue *q) {
    struct Patient p = q->list[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return p;
}

int chooseDept() {
    int d;
    printf("\nDepartments:\n");
    printf("  1. Orthopedic\n");
    printf("  2. Dermatology\n");
    printf("  3. Cardiology\n");
    printf("  4. General\n");
    printf("Choose: ");
    scanf("%d", &d);

    if (d < 1 || d > 4) {
        printf("Invalid, selecting General by default.\n");
        return 3;
    }
    return d - 1;
}

struct Patient createPatient() {
    struct Patient p;
    p.id = next_id++;

    getchar(); // clear buffer
    printf("Patient Name : ");
    fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Age          : ");
    scanf("%d", &p.age);

    getchar();
    printf("Disease      : ");
    fgets(p.disease, 50, stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

    printf("Priority (1=Emergency, 2=Normal, 3=Routine) : ");
    scanf("%d", &p.priority);

    if (p.priority < 1 || p.priority > 3) {
        printf("Bad input, setting Normal.\n");
        p.priority = 2;
    }

    return p;
}

void addPatient() {
    struct Patient p = createPatient();
    int dept = chooseDept();

    enqueue(&deptQueue[dept], p);

    printf("\nPatient added!\n");
    printf("ID         : %d\n", p.id);
    printf("Name       : %s\n", p.name);
    printf("Department : %s\n", deptName[dept]);
    printf("\nDoctor Info:\n");
    printf("  %s | %s | %s\n",
        doctors[dept].name,
        doctors[dept].room,
        doctors[dept].timing);
}

void servePatient() {
    int dept = chooseDept();

    if (isEmpty(&deptQueue[dept])) {
        printf("No patients waiting in this department.\n");
        return;
    }

    struct Patient p = dequeue(&deptQueue[dept]);
    printf("\nNow serving:\n");
    printf("  ID      : %d\n", p.id);
    printf("  Name    : %s\n", p.name);
    printf("  Disease : %s\n", p.disease);
}

void viewAllPatients() {
    int i, d;
    for (d = 0; d < NUM_DEPT; d++) {
        printf("\n[%s]\n", deptName[d]);

        if (isEmpty(&deptQueue[d])) {
            printf("  (empty)\n");
            continue;
        }

        for (i = 0; i < deptQueue[d].count; i++) {
            int idx = (deptQueue[d].front + i) % MAX;
            struct Patient p = deptQueue[d].list[idx];

            char *prio;
            if (p.priority == 1)      prio = "Emergency";
            else if (p.priority == 2) prio = "Normal";
            else                      prio = "Routine";

            printf("  %d. ID:%-4d  %-20s  Age:%-3d  %s\n",
                i+1, p.id, p.name, p.age, prio);
        }
    }
}

void searchPatient() {
    int id, d, i;
    printf("Enter Patient ID: ");
    scanf("%d", &id);

    for (d = 0; d < NUM_DEPT; d++) {
        for (i = 0; i < deptQueue[d].count; i++) {
            int idx = (deptQueue[d].front + i) % MAX;
            struct Patient p = deptQueue[d].list[idx];

            if (p.id == id) {
                printf("\nFound in %s department.\n", deptName[d]);
                printf("  Name     : %s\n", p.name);
                printf("  Age      : %d\n", p.age);
                printf("  Disease  : %s\n", p.disease);
                printf("  Priority : %d\n", p.priority);
                return;
            }
        }
    }
    printf("No patient with ID %d found.\n", id);
}

void dischargePatient() {
    int id;
    printf("Enter Patient ID to discharge: ");
    scanf("%d", &id);

    int d, i;
    for (d = 0; d < NUM_DEPT; d++) {
        struct Queue *q = &deptQueue[d];

        for (i = 0; i < q->count; i++) {
            int idx = (q->front + i) % MAX;

            if (q->list[idx].id == id) {
                // shift everything left to fill the gap
                int j;
                for (j = i; j < q->count - 1; j++) {
                    int cur  = (q->front + j)     % MAX;
                    int nxt  = (q->front + j + 1) % MAX;
                    q->list[cur] = q->list[nxt];
                }
                q->rear = (q->rear - 1 + MAX) % MAX;
                q->count--;

                printf("Patient %d discharged from %s.\n", id, deptName[d]);
                return;
            }
        }
    }
    printf("Patient not found.\n");
}

void showStatistics() {
    int d, total = 0;

    printf("\n===== Statistics =====\n");
    for (d = 0; d < NUM_DEPT; d++) {
        printf("  %-15s : %d patient(s)\n",
            deptName[d], deptQueue[d].count);
        total += deptQueue[d].count;
    }
    printf("  ----------------------\n");
    printf("  Total          : %d\n", total);
    printf("  Slots free     : %d\n", (MAX * NUM_DEPT) - total);
}

void printMenu() {
    printf("\n==============================\n");
    printf("   Hospital Management System\n");
    printf("==============================\n");
    printf(" 1. Add Patient\n");
    printf(" 2. Serve Next Patient\n");
    printf(" 3. View All Patients\n");
    printf(" 4. Search by ID\n");
    printf(" 5. Discharge Patient\n");
    printf(" 6. Statistics\n");
    printf(" 0. Exit\n");
    printf("------------------------------\n");
    printf("Choice: ");
}

int main() {
    int i;
    for (i = 0; i < NUM_DEPT; i++)
        initQueue(&deptQueue[i]);

    int choice;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient();       break;
            case 2: servePatient();     break;
            case 3: viewAllPatients();  break;
            case 4: searchPatient();    break;
            case 5: dischargePatient(); break;
            case 6: showStatistics();   break;
            case 0:
                printf("Exiting. Goodbye!\n");
                return 0;
            default:
                printf("Invalid option, try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar(); getchar();
    }

    return 0;
}



