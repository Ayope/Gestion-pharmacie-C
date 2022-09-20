#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#define max 1000 // defining a max size for arrays

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
    float pricePerUnit;
}Stat;

// Global variables and arrays section
Product product[max]; // structure of the list of our product
int varproducts = 0; //count the number of products that we have in our list

Stat prodachete[max]; // Purchased products structure 
int var_products_achete = 0; //count the number of products that we have in our list of purchased items

// FUNCTIONS SECTION

/*Search the product by his code (parameter) and: 
1- return his index as indication that he is exist in the array
2- return -1 = Not found 
 */
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

// Check if the choices is right
int checkChoice(int limit1, int limit2, int choice){
    do{
    	printf("Enter choice: ");
    	scanf("%d", &choice); 
    }while(choice<limit1 || choice>limit2);
	
    return choice;
}

// This function takes as parameter the number of products that user want to add to the structure (No return)

void addProduct(int n)
{
    int products1 = varproducts;
    for (int i = products1; i < n + products1; i++)
    {
        char testcode[max];
        fflush(stdin);
        printf("entrer le code de produit: ");
        scanf("%[^\n]%*c", &testcode);

        while (rech(testcode) >= 0){
            fflush(stdin);
            printf("le produit exist deja!\n");
            printf("entrer un nouveau code pour le produit: ");
            scanf("%[^\n]%*c", &testcode);
        }
        
        strcpy(product[i].code, testcode);
        printf("entrer le nom : ");
        scanf("%s", product[i].name);
        for(int k = 0; product[i].name[k]!='\0'; k++){ //ToLowerCase
            product[i].name[k] = tolower(product[i].name[k]);
        }
        printf("entrer la quantite: ");
        scanf("%d", &product[i].quantity);
        printf("entrer le prix : ");
        scanf("%f", &product[i].price);
        varproducts++;
        printf("Felicitons vous avez ajouter le produit numero %d!\n", i+1);
        printf("-----------------------------------------------\n");
    }
}

//This function list and sort all products by two orders (A->Z)||(100->0) using selection sort Algorithm

void produitList(){
    int choice;
    printf("1-Lister par ordre alphabetique (A->Z)\n");
    printf("2-Lister par ordre decroissante des prix (include Prix TTC)\n");
    
    choice = checkChoice(1, 2, choice);

    int i;
    Product temprod;
    
    if(choice == 1){
        for(i = 0; i < varproducts; i++){
            for(int j = i+1; j < varproducts; j++){
                if(strcmp(product[i].name, product[j].name)>0){ //(s2 < s1)
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

// this function has no return and its role is to update the quantity of products by
// 1- taking there code, the new quantity to add or to subtract and what operation should it do (parameters)

void updateQuantite(char code[max], int NewQuantite, char operation){
    if(operation == '-'){
        product[rech(code)].quantity -= NewQuantite;
    } else if(operation == '+'){
        product[rech(code)].quantity += NewQuantite;
    }
}

//this function let you buy products with the quantity you wnat and then add the infos of your purchase to the purchased products struct

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
    
    while(product[rech(testcode)].quantity == 0){ // Stops you if the product is not available //rep1
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

    // Pour ajouter les infors d'achat a la liste des achats
    for(int i = var_products_achete; i < var_products_achete+1; i++){
        updateQuantite(testcode, acheteQuantite, '-'); // deduire la quantite que le client achete

        prodachete[i].pricePerUnit = product[rech(testcode)].price; // ajouter le prix d'un seul piece 

        strcpy(prodachete[i].name, product[rech(testcode)].name); // ajouter le nom de produit 

        // Calculer le prix total des achats et l'ajoute au structure total pour enregistrer le total profit de ce produit dans cette journee
        prodachete[i].totalTTC += (product[rech(testcode)].price + ((product[rech(testcode)].price * 0.15)))*acheteQuantite;//

        /*ajouter la date d'achat de ce produit
        1-prendre le temps de notre local machine
        2-transferer a la format dd/mm/YYYY et puis en string*/
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        strftime(prodachete[i].date, sizeof(prodachete[i].date), "%d/%m/%Y", t);        
    }
    var_products_achete++;
}

//this function "recherche" searching the products by code or quantity using linear search algorithm

void recherche(){
    int choice, testQuantite;
    char testcode[max];
    printf("1-Chercher par code\n");
    printf("2-Chercher par quantite\n");
    
    choice = checkChoice(1, 2, choice);
    
    if(choice == 1){ //Use the previous "void rech(code)" function to find the index 
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
    }
    else if (choice == 2){ //list all the products with the quantity you search for
        int var=0;
        do{
            printf("Entrer la quantite: ");
            scanf("%d", &testQuantite);
        }while(testQuantite < 0);

        printf("------------------------------------------------------------------------------------------\n");
        printf("|   Name       |       Code      |     Quantite       |    Price      |     Price TTC |\n");
        printf("------------------------------------------------------------------------------------------\n");
        
        for (int j = 0; j <= varproducts; j++){
            if (product[j].quantity == testQuantite){
                printf("   %s           %s                %d                    %.2f DH           %.2f DH TTC\n", product[j].name, product[j].code, product[j].quantity, product[j].price, product[j].price + ((product[j].price * 0.15)));
                var++;
            }
        }
        if(var == 0){
            printf("|                                 NO RESULTS                                          |");
        }
    }
}

// this function show all the products that's there quantity is less than 3

void EtatDuStock(){
        int var;
        printf("------------------------------------------------------------------------------------------\n");
        printf("|   Name       |       Code      |     Quantite       |    Price      |     Price TTC |\n");
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

// This function gives you the option of add quantity to your stock using the previous updateQuantite function  

void alimenterStock(){
    char testcode[max];
    int AddQuantite;
    printf("Enter le code de votre produit: ");
    scanf("%s", &testcode);

    while(rech(testcode) < 0){
        printf("le produit n'existe pas!\n");
        printf("Entrer le code de produit a achete: ");
        scanf("%s", &testcode);
    }

    do{    
        printf("Entrer la quantite que voulez vous ajouter: ");
        scanf("%d", &AddQuantite);
    }while(AddQuantite>0);

    updateQuantite(testcode, AddQuantite, '+');
}

// This function gives you the option to delete a product from your list using code 

void supprimer(){
    char testcode[max];
    printf("Enter le code de produit qui vou voulez supprimer: ");
    scanf("%s", &testcode);

    while(rech(testcode) < 0){
        printf("le produit n'existe pas!\n");
        printf("Entrer le code de produit a supprimer: ");
        scanf("%s", &testcode);
    }

    for(int i = rech(testcode); i < varproducts - 1; i++){
        product[i] = product[i+1];
    }
    varproducts--; 
}

// Show you the statistique of the products in the current day

void statistique(){
    int choice;

    char todydatecmp[max];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(todydatecmp, sizeof(todydatecmp), "%d/%m/%Y", t);

    Stat todayachat[max];

    int j = 0; //nombre des produits en journee courante

    for(int i = 0; i <= var_products_achete; i++){
        if(strcmp(prodachete[i].date, todydatecmp) == 0){
            todayachat[j] = prodachete[i];
            j++;
        }
    }

    printf("1-Afficher le total des prix des produits vendus en journee courante\n");
    printf("2-Afficher la moyenne des prix des produits vendus en journee courante\n");
    printf("3-Afficher le Max des prix des produits vendus en journee courante\n");
    printf("4-Afficher le Min des prix des produits vendus en journee courante\n");

    choice = checkChoice(1, 4, choice);

    if(choice == 1){
        float total = 0;
        for(int i = 0; i<j; i++){
            total += todayachat[i].totalTTC;
        }
        printf("Le total des prix des produits vendus en journee courante est: %.4f\n", total);
    } else if(choice == 2){
        float total = 0;
        for(int i = 0; i<j; i++){
            total += todayachat[i].totalTTC;
        }
        float moyen = total/j;
        printf("la moyenne des prix des produits vendus en journee courante est: %.4f\n", moyen);
    } else if(choice == 3){
        int i = 0;
        float maxi;
        char name[max];
        maxi = todayachat[i].pricePerUnit;
        for(i = 1; i<j; i++){
            if(maxi < todayachat[i].pricePerUnit){
                maxi = todayachat[i].pricePerUnit;
                strcpy(name , todayachat[i].name);
            }
        }
        printf("le Max des prix des produits vendus en journee courante est de %s de prix: %.4fDH\n", name, maxi);
    } else if(choice == 4){
        int i = 0;
        float mini;
        char name[max];
        mini = todayachat[i].pricePerUnit;
        for(i = 1; i<j; i++){
            if(mini > todayachat[i].pricePerUnit){
                mini = todayachat[i].pricePerUnit;
                strcpy(name , todayachat[i].name);
            }
        }
        printf("le Min des prix des produits vendus en journee courante est de %s de prix: %.4fDH\n", name, mini);
    }
}

// The main function: 

int main(){

int choix;

printf("\n================ Application de Gestion de pharmacie ================\n\n");
do{
        printf("\n:::::::::::::::::::::::::: Menu Principale ::::::::::::::::::::::::::\n\n");
        printf("\t 1  -  Ajouter un nouveau produit \n");
        printf("\t 2  -  Ajouter plusieurs nouveaux produits \n");
        printf("\t 3  -  Lister tous les produits \n");
        printf("\t 4  -  Acheter un produit \n");
        printf("\t 5  -  Rechercher un produit \n");
        printf("\t 6  -  Etat du stock \n");
        printf("\t 7  -  Alimenter le stock \n");
        printf("\t 8  -  Supprimer un produit \n");
        printf("\t 9  -  Statistique de vente \n");
        printf("\t 10 -  Quitter L'\application\n\n");
        printf("Entrer votre choix : ");
        scanf("%d",&choix);
            
    
    int n;
    
    switch(choix){
        case1:
            system("cls");
            addProduct(1);
            break;
        case2:
            printf("Entrer le numero des produits: ");
            scanf("%d", &n);
            addProduct(n);
            break;
        default:
            printf("votre choix doit etre comprime entre 1 et 10");
            break;
    }


}while(choix != 10);
    return 0;
}