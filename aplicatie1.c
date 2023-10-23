/* IN C

I. Să se realizeze o aplicație pentru gestionarea unor filme, a căror informații sunt reținute în fișierul Filme.txt. 
Formatul fișierului este următorul:

An    Durata    Titlu    Categorie    Premii
An- intreg, Durata - intreg, Titlu - sir de caractere continand spatii, Categorii - sir de caractere, Premii (Da/Nu).
Se consideră ca separator între elemente TAB ('\t')
Să se implementeze următoarele funcționalități:
S1. Să se citească datele din fișier și să se definească structurile de date potrivite
S2. Să se afișeze filmele alfabetic după titlu folosind  bubble sort.
S2'. Să se ordoneze printr-o singură parcurgere a tabloului filmele astfel încăt filmele premiate să fie pe primele poziții urmate de filmele nepremiate, fără a folosi o altă structură de tip tablou, față de cea inițială.
S3.  Să se afișeze filmele crescător după anul apariției folosind quicksort sau o altă sortare avansată
*/ 
//folositi typedef si nu uita sa afisezi rezultatele!
//linii 50-51
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definim o structură pentru filme
typedef struct 
{
    int an;
    int durata;
    char titlu[100]; // presupunem că titlul are maxim 100 de caractere
    char categorie[50]; // presupunem că categoria are maxim 50 de caractere
    char premii[3]; // "Da" sau "Nu"
} Film;


// Funcție pentru afișarea filmelor într-un fișier
void afiseazaFilme(Film *filme, int numarFilme, const char *numeFisier) 
{
	int i;
    FILE *fisier = fopen(numeFisier, "w");
    if (fisier == NULL)
	 {
        printf("Eroare la deschiderea fișierului %s pentru scriere.\n", numeFisier);
        return;
    }

    for (i=0; i<numarFilme; i++) 
    {
        fprintf(fisier, "%d\t%d\t%s\t%s\t%s\n", filme[i].an, filme[i].durata, filme[i].titlu, filme[i].categorie, filme[i].premii);
    }

    fclose(fisier);
}

void swap(Film *a, Film *b)
{
    Film temp = *a;
    *a = *b; 
    *b = temp;
}

// Funcție pentru bubble sort după titlu
void bubbleSort(Film *filme, int numarFilme) 
{
	int i, j;
    for (i=0; i<numarFilme; i++) 
	{
        for (j=0; j<numarFilme-i-1; j++)
		 {
            if (strcmp(filme[j].titlu, filme[j + 1].titlu) > 0) 
			{
                swap(&filme[j], &filme[j+1]);
            }
        }
    }
}

// Funcție pentru partition în quicksort
int partition(Film *filme, int low, int high) 
{
    Film pivot = filme[low];
    int i, j;
    i=low;
    j=high;

    while(i<j)
    {
        do
        {
            i++;
        }
        while(filme[i].an <= pivot.an);

        do
        {
            j--;
        }
        while(filme[j].an > pivot.an);

        if(i<j)
        {
            swap(&filme[j], &filme[i]);
        }
    }

    swap(&filme[j], &filme[low]);
    return j;
}

// Funcție pentru quicksort
void quicksort(Film *filme, int low, int high) 
{
    int j;
    if (low < high) 
    {
        j = partition(filme, low, high);
        quicksort(filme, low, j);
        quicksort(filme, j+1, high);
    }
}

int main(void) 
{
    Film *filme;
    int i=0, numarDeFilme = 0;
    char linie[200]; // presupunem că o linie are maxim 200 de caractere

    FILE *fisier = fopen("Filme.txt", "r");
    if (fisier == NULL) 
    {
        printf("Eroare la deschiderea fișierului Filme.txt.\n");
        return 1;
    }

    while (fgets(linie, sizeof(linie), fisier)) 
	{
        numarDeFilme++;
    }

    // Alocăm memorie pentru vectorul de filme
    filme = (Film *)malloc(numarDeFilme * sizeof(Film));

    // Resetăm cursorul la începutul fișierului
    fseek(fisier, 0, SEEK_SET);
    while (i<numarDeFilme && fgets(linie, sizeof(linie), fisier)) 
    {
        sscanf(linie, "%d\t%d\t%99[^\t]\t%49[^\t]\t%2s", &filme[i].an, &filme[i].durata, filme[i].titlu, 
        filme[i].categorie, filme[i].premii);
        i++;
    }

    fclose(fisier);
    
    // Sortăm filmele după titlu folosind bubble sort
    bubbleSort(filme, numarDeFilme);

    // Afișăm filmele sortate după titlu într-un fișier
    afiseazaFilme(filme, numarDeFilme, "FilmeSortateDupaTitlu.txt");

    // Sortăm filmele după an folosind quicksort
    quicksort(filme, 0, numarDeFilme - 1);

    // Afișăm filmele sortate după an într-un alt fișier
    afiseazaFilme(filme, numarDeFilme, "FilmeSortateDupaAn.txt");

    // Eliberăm memoria alocată pentru filme
    free(filme);
    return 0;
}
