/*Fie o aplicatie care gestioneaza o retea de profesionisti din intreaga lume, de tip Linkedin. Pentru o persoana
se memoreaza un ID(intreg), un nume (max 35 caractere) si o ocupatie (max 35 de caractere), precum si o lista
de conexiuni profesionale. Sa se scrie si sa se implementeze o structura bazata pe lista simplu inlantuita(dinamica)
articulata cu tablouri (eficienta din punct de vedere al timpului de rulare) pentru a gestiona persoanele. Structura
va avea urmatoarea componenta: Fiecare persoana reprezinta un nod intr-o lista, si fiecare persoana contine un tablou
implementat in mod static, cu conexiunile profesionale pe care le are(colegi de echipa, persoane de la resurse
umane, etc).
   Sa se implementeze structurile de date necesare si urmatoare functionalitate:
* Adaugare conexiune in lista unei persoane(adaugare in lista secundara)

   Sa se aleaga un exemplu de lista care sa cuprinda cel putin 3 persoane, fiecare cu cel putin 5 conexiuni.
Sa se reprezinte grafic structura multilista pentru acest exemplu, inainte si dupa apelul functiei adaugareConexiune.

   Este obligatorie comentarea algoritmului si specificarea complexitati acestuia in termeni de O(f(n)), comentarea structurilor de date
alese, precum si justificarea alegerii acestora.
   Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct conexiune{
   int count;
   int IDconexiuni[5];
}conexiune_t;

typedef struct persoana{
   int ID;
   char nume[35];
   char ocupatie[35];
   conexiune_t conexiuni; 
   struct persoana *link;
}persoana_t;

void adaugareConexiune(persoana_t *persoana, int IDconexiune)
{
   //verificam daca exista loc in tabloul de conexiuni:
   if(persoana->conexiuni.count < 10)
   {
      persoana->conexiuni.IDconexiuni[persoana->conexiuni.count++] = IDconexiune;
   }
   else
   {
      printf("Nu se poate adauga conexiunea, lista de conexiuni aferenta este plina!\n");
   }
}

void afiseazaDetaliiPersoana(persoana_t *persoana)
{
   printf("ID: %d\n", persoana->ID);
   printf("Nume: %s\n", persoana->nume);
   printf("Ocupatie: %s\n", persoana->ocupatie);
   int i;
   printf("Conexiuni: ");
   for(i=0; i<persoana->conexiuni.count; i++)
   {
      printf("%d ",  persoana->conexiuni.IDconexiuni[i]);
   }
   printf("\n\n");
}

void printList(persoana_t *head)
{
   persoana_t *ptr;
   ptr = head;
   while(ptr!=NULL)
   {
      afiseazaDetaliiPersoana(ptr);
      ptr=ptr->link;
   }
   printf("\n");
}

//functie pentru creearea unei persoane:
persoana_t *creearePersoana(int ID, const char *nume, const char *ocupatie)
{
   persoana_t *newPerson;
   newPerson = (persoana_t *)malloc(sizeof(persoana_t));
   newPerson->ID = ID;
   strncpy(newPerson->nume, nume, 35);
   strncpy(newPerson->ocupatie, ocupatie, 35);
   newPerson->conexiuni.count = 0;
   newPerson->link = NULL;
   return newPerson;
}


int main(void)
{
   persoana_t *pers1 = creearePersoana(1, "Vera", "Inginera");
   persoana_t *pers2 = creearePersoana(2, "Sandra", "Profesoara");
   persoana_t *pers3 = creearePersoana(3, "Maria", "Doctor");

   pers1->link = pers2;
   pers2->link = pers3;

   adaugareConexiune(pers1, 2);
   adaugareConexiune(pers1, 3);
   adaugareConexiune(pers2, 1);
   adaugareConexiune(pers2, 3);
   adaugareConexiune(pers3, 1);
   adaugareConexiune(pers3, 2);

   // Afisarea structurii inainte de adaugarea conexiunii
   printf("Inainte de adaugarea conexiunii:\n");
   printList(pers1);

   // Adaugarea unei noi conexiuni
   adaugareConexiune(pers1, 4);

   // Afisarea structurii dupa adaugarea conexiunii
   printf("Dupa adaugarea conexiunii:\n");
   printList(pers1);

   // Eliberarea memoriei la finalul programului
   free(pers1);
   free(pers2);
   free(pers3);
   return 0;
}
