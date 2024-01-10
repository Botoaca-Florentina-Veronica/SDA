/*   Fie un sistem de gestionare a unor produse intr-un lant de magazine. Magazinul este caracterizat printr-un nume unic, iar produsele
printr-un cod numeric(max 8 cifre). Sa se scrie si sa se implementeze o structura multilista adecvate pentru gestionarea acestor magazine.
Structura va avea urmatoarea componenta: Fiecare magazin reprezinta o intrare separata intr-o lista principala, si fiecare magazin contine 
o lista secundara ordonata dupa cod a produselor din acel magazin(cel putin una din liste va fi implementata dinamic).

Sa se implementeze structurile de date necesare si urmatoarele functionalitati:
  *Eliminare produse - sterge un produs identificat dupa cod din toate magazinele.

   Sa se aleaga un exemplu de lista care sa cuprinda cel putin 3 magazine, fiecare cu cel putin 5 produse. Sa se reprezinte grafic structura
multilista pentru acest exemplu, inainte si dupa apelul functiei Eliminare produs.

NOTA!
   Este obligatorie comentarea algoritmului si specificarea complexitatii acestuia in termeni de O(f(n)), comentarea structurilor de date
alese, precum si justificarea alegerii acestora.
   Este obligatorie exemplificarea efectului apelului functiilor implementate pe un exemplu ales.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct produs 
{
    int cod; // Codul unic al produsului (max 8 cifre)
    struct produs *link;
}produs_t;



typedef struct magazin 
{
    char name[50]; // Numele unic al magazinului
    produs_t *produse; // Lista secundară de produse în magazin
    struct magazin *link; 
}magazin_t;

// Funcție pentru a crea un nou produs
produs_t *createProduct(int cod) 
{
    produs_t *produsNou = (produs_t *)malloc(sizeof(produs_t));
    produsNou->cod = cod;
    produsNou->link = NULL;
    return produsNou;
}

// Funcție pentru a crea un nou magazin
magazin_t *createStore(const char* name) 
{
    magazin_t *newStore= (magazin_t *)malloc(sizeof(magazin_t));
    strcpy(newStore->name, name);
    newStore->produse = NULL;  //initializam neaparat la creearea unui magazin campurile specifice!!
    newStore->link = NULL;
    return newStore;
}

// Funcție pentru a elimina un produs din toate magazinele după cod
void removeProductFromAllStores(magazin_t *head, int cod) 
{
    magazin_t *store = head;

    // Parcurgem lista principală (magazinele)
    while (store != NULL) 
    {
        produs_t *curr = store->produse;
        produs_t *prev = NULL; //(nu iti afiseaza corect daca declari curr si prev in afara while ului)

        // Parcurgem lista secundară (produsele din magazin)
        while (curr != NULL) 
        {
            if (curr->cod == cod) 
            {
                // Eliminăm produsul din magazin
                if (prev == NULL) 
                {
                    //daca nu mai avem produse in lista, atunci primul nod, adica chiar capul listei, va fi sters
                    //pentru asta, pur si simplu vom initializa noul cap al listei cu urmatorul produs
                    store->produse = curr->link;
                } 
                else 
                {
                    //daca lista noastra nu e goala, atunci vom sari elementul curent pe care dorim sa il stergem:
                    prev->link = curr->link;
                }
                free(curr);
                break; // Ne oprim după găsirea primului produs cu codul dat
            }
            else
            {
                //daca nodul nostru din lista nu este cel cautat pentru stergere, mergem mai departe si parcurgem restul listei
                prev = curr;
                curr = curr->link;
            }
        }
        //parcurgem restul magazinelor
        store = store->link;
    }
}

// Funcție pentru a afișa structura multilistă
void printMultilist(magazin_t *head) 
{
    magazin_t *store;   //store reprezinta magazinul curent la care ma aflu
    store = head;   
    while (store != NULL) 
    {
        printf("Magazin: %s\n", store->name);
        produs_t *curr;
        curr = store->produse;   // curr reprezinta produsul curent
        while (curr != NULL) 
        {
            printf("  Cod produs: %d\n", curr->cod);
            curr = curr->link;
        }
        store = store->link;
    }
}

// Funcție pentru a elibera memoria ocupată de structura multilistă
void freeMultilist(magazin_t *head) 
{
    while (head != NULL) 
    {
        magazin_t *tempStore = head;
        head = head->link;

        produs_t *currentProduct = tempStore->produse;
        while (currentProduct != NULL) 
        {
            produs_t* tempProduct = currentProduct;
            currentProduct = currentProduct->link;
            free(tempProduct);
        }

        free(tempStore);
    }
}

int main(void) 
{
    // Exemplu de listă cu cel puțin 3 magazine, fiecare cu cel puțin 5 produse
    magazin_t *m1 = createStore("Magazin A");
    m1->produse = createProduct(123);
    m1->produse->link = createProduct(456);

    magazin_t *m2 = createStore("Magazin B");
    m2->produse = createProduct(789);

    magazin_t *m3 = createStore("Magazin C");
    m3->produse = createProduct(123); // Produsul cu același cod există în store1

    // Adaugăm magazinele la lista principală
    m1->link = m2;
    m2->link = m3;

    // Afișăm structura multilistă înainte de eliminarea produsului
    printf("Before removing product:\n");
    printMultilist(m1);

    // Eliminăm produsul cu codul 123 din toate magazinele
    removeProductFromAllStores(m1, 123);

    // Afișăm structura multilistă după eliminarea produsului
    printf("\nAfter removing product:\n");
    printMultilist(m1);

    // Eliberăm memoria ocupată de structura multilistă
    freeMultilist(m1);
    return 0;
}
