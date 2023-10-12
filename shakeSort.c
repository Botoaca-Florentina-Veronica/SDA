//shake sort
#include<stdio.h>
#define n 10

void shakeSort(int *v)
{
    int j, temp, dr, st, k;
    dr=n-1;
    st=0;
    k=n-1;
    do
    {
        //pentru parcurgerea de la dreapta ->stanga avem minimul impins spre inceputul tabloului
        for(j=dr; j>=st; j--)
        {
            if(v[j-1]>v[j])
            {
                temp=v[j-1];
                v[j-1]=v[j];
                v[j]=temp;
                k=j;
            }
        }
        st=k+1;
        //la fiecare parcurgere dreapta->stanga se memoreaza indicele k al celui mai din dreapta element
        //implicat in ultima interschimbare

        //pentru parcurgerea de la stanga->dreapta avem maximul impins spre finalul tabloului
        //adica chiar bubbleSort
        for(j=st; j<=dr; j++)
        {
            if(v[j]>v[j+1])
            {
                temp=v[j];
                v[j]=v[j+1];
                v[j+1]=temp;
                k=j;
            }
        }
        dr=k-1;
        //la parcurgerea stanga->dreapta se pleaca de la k, adica nu se mai compara elementele ordonate!
    }
    while(st<=dr);
}


int main(void)
{
    int v[10]={4, 7, 9, 2, 5, 12, 66, 1, 21, 3};
    shakeSort(v);
    int i;
    printf("Tabloul sortat:\n");
    for(i=0; i<n; i++)
    {
        printf("%d ", v[i]);
    }
    return 0;
}
