#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define max 100
// Structures section

typedef struct 
{
    char code[max];
    char name[max];
    int quantity;
    float price;
} Product;


Product product[max];
int varproducts = 0;

// functions section
int cherch(char rechcode[10])
{
    int check = 0;

    for (int j = 0; j <= varproducts; j++)
    {
        if (strcmp(product[j].code, rechcode) == 0)
        {
            check++;
            break;
        }
    }
    return check;
}

void addProduct(int n)
{
    int products1 = varproducts;
    for (int i = products1; i < n + products1; i++)
    {
        char testcode[max];
        fflush(stdin);
        printf("entrer le code de produit: ");
        scanf("%[^\n]%*c", testcode);
        while (cherch(testcode) > 0)
        {
            fflush(stdin);
            printf("le produit exist deja\n");
            printf("entrer un nouveau code de produit: ");
            scanf("%[^\n]%*c", testcode);
        }
        strcpy(product[i].code, testcode);
        printf("entrer le nom : ");
        scanf("%s", product[i].name);
        printf("entrer la quantite: ");
        scanf("%d", &product[i].quantity);
        printf("entrer le prix :");
        scanf("%f", &product[i].price);
        varproducts++;
        printf("Felicitons vous avez ajouter un produit!\n");
        printf("-----------------------------------------------\n");
    }
}

void ProduitList(){
    int choice;
    printf("1-Lister par ordre alphabetique (A->Z)\n");
    printf("2-Lister par ordre decroissante des prix (include Prix TTC)\n");
    printf("Entrer votre choix (1 ou 2): ");
    scanf("%d", &choice);
    
    int i;
    Product temprod;
    
    if(choice == 1){
        for(i = 0; i < varproducts; i++){
            for(int j = i+1; j < varproducts; j++){
                if(strcmp(product[i].name, product[j].name)>0){ //(s1 < s2)
                    temprod = product[i];
                    product[i] = product[j];
                    product[j] = temprod;
                }
            }
        }
    }else if(choice == 2){
        for(i = 0; i < varproducts; i++){
            for(int j = i+1; j <= varproducts; j++){
                if(product[i].price < product[j].price){ 
                    temprod = product[i];
                    product[i] = product[j];
                    product[j] = temprod;
                }
            }
        }
    }

    printf("------------------------------------------------------------------------------------------\n");
    printf("   Name    |    Code    |    Quantite    |    Price    |     Price TTC     \t|\n");
    printf("------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < varproducts; i++){
        printf("   %s      %s        %d         %.2f DH        %.2f DH TTC\n", product[i].name, product[i].code, product[i].quantity, product[i].price, product[i].price + ((product[i].price * 0.15)));
    }
}


















int main(){
    addProduct(2);

    ProduitList();

    //printf("________________-----_________________\n");
    // switch(){
    //     case1:
    //         addProduct(1);
    //         break;
    //     case2:
    //         int n;
    //         printf("Entrer le numero de produits : ");
    //         scanf("%d", &n);
    // }

    // return 0;
}