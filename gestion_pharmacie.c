#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define max 100
// Structures section

typedef struct 
{
    char code[max];
    char name[max];
    int quantity;
    float price;
} Product;

typedef struct {
    char name[max];
    char date[max];
    float totalTTC;
}stat;

stat prodachete[max];
int var_products_achete = 0;

Product product[max];
int varproducts = 0;

// functions section
int rech(char rechcode[max])
{
    for (int j = 0; j <= varproducts; j++)
    {
        if (strcmp(product[j].code, rechcode) == 0)
        {
            return j;
        }
    }
    return -1;
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
        while (rech(testcode) >= 0)
        {
            fflush(stdin);
            printf("le produit exist deja!\n");
            printf("entrer un nouveau code de produit: ");
            scanf("%[^\n]%*c", testcode);
        }
        strcpy(product[i].code, testcode);
        printf("entrer le nom : ");
        scanf("%s", product[i].name);
        for(int k = 0; product[i].name[k]!='\0'; k++){
            product[i].name[k] = tolower(product[i].name[k]);
        }
        printf("entrer la quantite: ");
        scanf("%d", &product[i].quantity);
        printf("entrer le prix : ");
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
    
    do{
        printf("Entrer votre choix (1 ou 2): ");
        scanf("%d", &choice);
    }while(choice < 1|| choice > 2);

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
        printf("   %s           %s          %d           %.2f DH          %.2f DH TTC\n", product[i].name, product[i].code, product[i].quantity, product[i].price, product[i].price + ((product[i].price * 0.15)));
    }
}

void updateQuantite(char code[max], int NewQuantite, char operation){
    if(operation =='-'){
        product[rech(code)].quantity -= NewQuantite;
    } else if(operation == '+'){
        product[rech(code)].quantity += NewQuantite;
    }
    

}

void achete(){
    char testcode[max];
    int acheteQuantite;

    printf("Entrer le code de produit a achete: ");
    scanf("%s", &testcode);

    while(rech(testcode) < 0){ // Be sure if the product exist
        printf("le produit n'existe pas!\n");
        printf("Entrer le code de produit a achete: ");
        scanf("%s", &testcode);
    }
    
    while(product[rech(testcode)].quantity == 0){
        printf("SOLD OUT!\n");
        printf("Entrer le code de produit a achete: ");
        scanf("%s", &testcode);
    }

    printf("Entrer combien de quantite que voulez vous achete: ");
    scanf("%d", &acheteQuantite);
    
    while(acheteQuantite > product[rech(testcode)].quantity){ //S'assurer que la quantite a deduire est inferieur a la quantite de stock
        printf("la quanite que vous avez entrer est superieur a la quantite au stock!\n");
        printf("Entrer combien de quantite voulez vous achete: ");
        scanf("%d", &acheteQuantite);
    }

    // Pour mettre l'achat dans la fin de list des achats precedents
    for(int i = var_products_achete; i < var_products_achete+1; i++){
        updateQuantite(testcode, acheteQuantite, '-'); // deduire la quantite que le client achete
    
        strcpy(prodachete[i].name, product[rech(testcode)].name); // ajouter le nom de produit a la structure stat

        // Calculer le prix total des achats et l'ajoute au structure total pour enregistrer le total profit de ce produit dans cette journee
        prodachete[i].totalTTC += (product[rech(testcode)].price + ((product[rech(testcode)].price * 0.15)))*acheteQuantite;//

        //ajouter la date d'achat de ce produit
        time_t dateDachat;
        time(&dateDachat);
        strcpy(prodachete[i].date, ctime(&dateDachat));
        
    }
        
    var_products_achete++;
    
    // for(int i = 0; i < var_products_achete; i++){
    //     printf("%s\n", prodachete[i].name);
    //     printf("%.2f\n", prodachete[i].totalTTC);
    //     printf("%s", prodachete[i].date);
    // }
}


void recherche(){
    int choice, testQuantite;
    char testcode[max];
    printf("1-Chercher par code\n");
    printf("2-Chercher par quantite\n");
    do{
        printf("Entrer votre choix (1 ou 2): ");
        scanf("%d", &choice);
    }while(choice < 1|| choice > 2);
    
    if(choice == 1){
        printf("Entrer le code: ");
        scanf("%s", &testcode);

        while(rech(testcode) < 0){
            printf("le produit n'existe pas!\n");
            printf("Entrer un nouveau code: ");
            scanf("%s", &testcode);
        }

        int result = rech(testcode);

        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("   Name       |       Code      |     Quantite       |          Price           |       Price TTC      \n");
        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("   %s           %s                %d                    %.2f DH           %.2f DH TTC\n", product[result].name, product[result].code, product[result].quantity, product[result].price, product[result].price + ((product[result].price * 0.15)));
    } else if (choice == 2){
        int var=0;
        do{
            printf("Entrer la quantite: ");
            scanf("%d", &testQuantite);
        }while(testQuantite < 0);

        printf("------------------------------------------------------------------------------------------\n");
        printf("|   Name       |       Code      |     Quantite       |    Price      |     Price TTC |\n");
        printf("------------------------------------------------------------------------------------------\n");
        
        for (int j = 0; j <= varproducts; j++)
        {
            if (product[j].quantity == testQuantite)
            {
                printf("   %s           %s                %d                    %.2f DH           %.2f DH TTC\n", product[j].name, product[j].code, product[j].quantity, product[j].price, product[j].price + ((product[j].price * 0.15)));
                var++;
            }
        }
        if(var == 0){
            printf("|                                 NO RESULTS                                          |");
        }
    }
}

void EtatDuStock(){
        int var;
        printf("------------------------------------------------------------------------------------------\n");
        printf("|   Name            |       Code             |     Quantite             |    Price            |     Price TTC |\n");
        printf("------------------------------------------------------------------------------------------\n");
        
        for (int j = 0; j < varproducts; j++)
        {
            if (product[j].quantity < 3)
            {
                printf("   %s           %s                %d                    %.2f DH           %.2f DH TTC\n", product[j].name, product[j].code, product[j].quantity, product[j].price, product[j].price + ((product[j].price * 0.15)));
                var++;
            }
        }
        
        if(var == 0){
            printf("|                                 NO RESULTS                                          |");
        }
    }


void alimenterStock(){
    char testcode[max];
    int AddQuantite;
    printf("Enter le code de votre produit: ");
    scanf("%s", &testcode);

    while(rech(testcode) < 0){ // Be sure if the product exist
        printf("le produit n'existe pas!\n");
        printf("Entrer le code de produit a achete: ");
        scanf("%s", &testcode);
    }

    printf("Entrer la quantite que voulez vous ajouter: ");
    scanf("%d", &AddQuantite);
    updateQuantite(testcode, AddQuantite, '+');
}







int main(){
    addProduct(2);
    ProduitList();
    alimenterStock();
    ProduitList();
    alimenterStock();
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
    //         addProduct(n);
    // }

    // return 0;
}