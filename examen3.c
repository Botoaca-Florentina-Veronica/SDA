/*
   Fie un sistem de gestionare a unor sesiuni de conferințe online Zoom.
O conferinţă este caracterizată printr-un ID unic de conferință (Meeting ID), data desfasurarii si numele persoanei ce gazduieste conferinta. 
   Intr-o sesiune pot participa mai multi studenti, un student fiind caracterizat printr-un nume si eu email personal.
Sa se scrie si sa se implementeze o structura multilista adecvată pentru gestionarea acestor conferințe. 
   Structura va avea urmatoarea componenta: Fiecare conferinţă reprezintă o intrare separată într-o lista principală, si fiecare 
conferință conține o listă secundară ordonată alfabetic după numele studenţilor (cel putin una din liste va fi implementata dinamic).
Sa se implementeze structurile de date necesare si urmatoarele functionalitati:
• Modificare_email_participant(id_conferinta, nume_student, email_nou) - pentru un anumit student identificat dupa nume, dintr-o anumita conferinta, 
se inlocuieste vechiul email cu cel nou dat ca parametru
   Sa se aleaga un exemplu de lista care sa cuprinda cel putin 3 conferințe, fiecare cu cel putin 5 studenți. 
   Să se reprezinte grafic structura multilistă pentru acest exemplu, inainte si dupa apelul functiei Acceptare în meeting.

Nota:
   Algoritmul poate fi scris in pseudocod (C like).
   Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), comentarea structurilor de date alese,
precum si justificarea alegerii acestora.
   Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student {
    char nume[35];
    char email[40];
    struct student *link;
} student_t;

typedef struct conferinta {
    int ID;
    int data;
    char numeGazda[35];
    student_t *studenti; // Lista dinamica de studenti
    struct conferinta *link;
} conferinta_t;


void printMultilist(conferinta_t *head) 
{
    conferinta_t *ptr;
    ptr = head;
    printf("Multilista cu studentii participanti la conferinte:\n");

    while (ptr != NULL) 
    {
        printf("ID Conferinta: %d, Gazda: %s, Data: %d\n", ptr->ID, ptr->numeGazda, ptr->data);
        student_t *studentPtr = ptr->studenti;
        while (studentPtr != NULL) 
        {
            printf("\tNume student: %s, Email: %s\n", studentPtr->nume, studentPtr->email);
            studentPtr = studentPtr->link;
        }
        ptr = ptr->link;
    }
    printf("\n");
}


void adaugaStudentLaConferinta(conferinta_t *conferinta, const char *nume, const char *email) 
{
    student_t *participantNou = (student_t *)malloc(sizeof(student_t));
    strncpy(participantNou->nume, nume, 35);
    strncpy(participantNou->email, email, 40);
    participantNou->link = NULL;

    // Daca nu exista studenti in conferinta, adauga primul student
    if (conferinta->studenti == NULL) 
    {
        conferinta->studenti = participantNou;
        return;
    } 

    // Altfel, gaseste ultimul student si adauga noul student la sfarsitul listei
    student_t *studentPtr = conferinta->studenti;
    while (studentPtr->link != NULL) 
    {
        studentPtr = studentPtr->link;
    }
    studentPtr->link = participantNou;

}

// Functie pentru crearea unei conferinte si adaugarea ei la sfarsitul listei
conferinta_t *adaugaConferinta(conferinta_t *head, int ID, int data, const char *numeGazda) {
    conferinta_t *conferintaNoua = (conferinta_t *)malloc(sizeof(conferinta_t));
    conferintaNoua->ID = ID;
    conferintaNoua->data = data;
    strncpy(conferintaNoua->numeGazda, numeGazda, 35);
    conferintaNoua->studenti = NULL;
    conferintaNoua->link = NULL;

    // Daca nu exista conferinte, returneaza prima conferinta
    if (head == NULL) 
    {
        return conferintaNoua;
    } 
    else 
    {
        // Altfel, gaseste ultima conferinta si adauga noua conferinta la sfarsitul listei
        conferinta_t *conferintaPtr = head;
        while (conferintaPtr->link != NULL) 
        {
            conferintaPtr = conferintaPtr->link;
        }
        conferintaPtr->link = conferintaNoua;
        return head;
    }
}


void modificareEmailParticipant(int ID, conferinta_t *head, const char *nume, const char *email) 
{
    conferinta_t *ptr;
    ptr = head;
    while (ptr!= NULL && ptr->ID != ID) 
    {
        ptr = ptr->link;
    }
   //aici practic am parcurs lista de conferinte pentru a afla care este cea cu ID-ul dat ca parametru
   //cand ptr->ID == ID, bucla se opreste, iar in ptr este stocata conferinta cautata

    if (ptr != NULL) 
    {
        student_t *studentPtr = ptr->studenti;
        while (studentPtr != NULL && strcmp(studentPtr->nume, nume) != 0) 
        {
            studentPtr = studentPtr->link;
        }
        if (studentPtr != NULL) 
        {
            strncpy(studentPtr->email, email, 40);
        }
        else
        {
            printf("Student not found in the specified conference.\n");
        }
    }
    else
    {
        printf("Conference not found.\n");
    }
}


void eliberareMemorie(conferinta_t *head) 
{
    conferinta_t *conferintaPtr = head;
    while (conferintaPtr != NULL) 
    {
        student_t *studentPtr = conferintaPtr->studenti;
        while (studentPtr != NULL) 
        {
            student_t *temp = studentPtr;
            studentPtr = studentPtr->link;
            free(temp);
        }

        conferinta_t *temp = conferintaPtr;
        conferintaPtr = conferintaPtr->link;
        free(temp);
    }
}

int main(void) 
{
    conferinta_t *head = NULL;
    conferinta_t *c1, *c2, *c3;
    c1=c2=c3=head;

    // Adaugare studenti la conferinte
    c1 = adaugaConferinta(head, 1, 20220101, "Gazda1");
    adaugaStudentLaConferinta(c1, "Student1", "student1@example.com");
    adaugaStudentLaConferinta(c1, "Student2", "student2@example.com");
    adaugaStudentLaConferinta(c1, "Student3", "student3@example.com");
    adaugaStudentLaConferinta(c1, "Student4", "student4@example.com");
    adaugaStudentLaConferinta(c1, "Student5", "student5@example.com");

    c2 = adaugaConferinta(c2, 2, 20220102, "Gazda2");
    adaugaStudentLaConferinta(c2, "StudentA", "studentA@example.com");
    adaugaStudentLaConferinta(c2, "StudentB", "studentB@example.com");
    adaugaStudentLaConferinta(c2, "StudentC", "studentC@example.com");
    adaugaStudentLaConferinta(c2, "StudentD", "studentD@example.com");
    adaugaStudentLaConferinta(c2, "StudentE", "studentE@example.com");

    c3 = adaugaConferinta(c3, 3, 20220103, "Gazda3");
    adaugaStudentLaConferinta(c3, "Participant1", "participant1@example.com");
    adaugaStudentLaConferinta(c3, "Participant2", "participant2@example.com");
    adaugaStudentLaConferinta(c3, "Participant3", "participant3@example.com");
    adaugaStudentLaConferinta(c3, "Participant4", "participant4@example.com");
    adaugaStudentLaConferinta(c3, "Participant5", "participant5@example.com");

    c1->link = c2;
    c2->link = c3;

    // Afisare inainte de modificare
    printf("Inainte de modificare:\n");
    printMultilist(c1);

    // Modificare email participant
    modificareEmailParticipant(2, c2, "StudentB", "studentB_modified@example.com");

    // Afisare dupa modificare
    printf("\nDupa modificare:\n");
    printMultilist(c1);

    // Eliberare memorie
    eliberareMemorie(head);
    return 0;
}
