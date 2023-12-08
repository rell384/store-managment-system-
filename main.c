#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

void setColor(int ForgC) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

COORD coord = {0, 0};

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

typedef struct product {
    int ID;
    char name[20];
    float price;
    int quantity;
} product;

typedef struct category {
    char name[20];
    product p[100];
    int numProducts;
} category;

int catCount = 0;
int oldCatCount = 0;
category c[20];
int x = 0;
int u = 0;

// Function prototypes
void addNewCategory();
void sellProduct();
void moveProduct();
void showAvailableGoods();
void addNewProduct();
void removeProduct(int categoryIndex, int productIndex);

int main() {

    char menu[6][150] = {" Add New Category", " Add New Product", " Sell Product", " Move Product", " Show Available Products", " Exit"};

    int index = 0;
    while (true) {
        system("cls");
        for (int i = 0; i < 6; i++) {
            gotoxy(20, i + 10);
            if (i == index) {
                setColor(12);
            } else {
                setColor(15);
            }
            printf(" %i )  %s \n", i + 1, menu[i]);
        }

        char current_key = getch();
        if (current_key == -32) {
            current_key = getch();

            if (current_key == 80) // down
            {
                index = (index + 1) % 6;
            } else if (current_key == 72) // up
            {
                index = (index - 1 + 6) % 6;  // Change 3 to 6
            } else if (current_key == 71) // home
            {
                index = 0;
            } else if (current_key == 79) // end
            {
                index = 6;  // Change 2 to 6
            }
        } else if (current_key == 27) // esc
        {
            exit(0);
        } else if (current_key == 13) // enter
        {
            switch (index) {
                case 0:
                    system("cls");
                    printf("\n****************************************************************************(WELCOME TO REHAM SUPERMARKET) *************************************************************\n");

                    addNewCategory();
                    break;
                case 1:
                    system("cls");
                    printf("\n***************************************************************************(WELCOME TO REHAM SUPERMARKET) **************************************************************\n");

                    addNewProduct();
                    break;
                case 2:
                    system("cls");
                    printf("\n******************************************************************************(WELCOME TO REHAM SUPERMARKET) *****************************************************************\n");

                    sellProduct();
                    break;
                case 3:
                    system("cls");
                    printf("\n*****************************************************************************(WELCOME TO REHAM SUPERMARKET) *****************************************************************\n");

                    moveProduct();
                    break;
                case 4:
                    system("cls");
                    printf("\n*****************************************************************************(WELCOME TO REHAM SUPERMARKET) *****************************************************************\n");

                    showAvailableProducts();
                    break;
                case 5:
                    system("cls");
                    //printf("Exiting the program.\n");
                    printf("\n******************************************************************************(WELCOME TO REHAM SUPERMARKET) *****************************************************************\n");

                    exit(0);
                    break;
                default:
                    system("cls");
                    printf("INVALID CHOICE. PLEASE TRY AGAIN\n");
            }
            system("pause");
        }
    }

    return 0;
}

// Implement the functions...
 int isAlphaString(const char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0;  // False  non-alphabetic characters
        }
        str++;
    }
    return 1;  // True  alphabetic
}

int isDigitInteger(int num) {
    char str[20];
    sprintf(str, "%d", num);

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;  // False non-digit characters
        }
    }
    return 1;  // True digits
}


void addNewCategory() {


    printf("Enter Number of Category to Add: \n");
    scanf("%d", &catCount);


    if (x == 0) {
        for (int i = 0; i < catCount; i++) {
            printf("Enter category %d Name : \n ", i + 1);
            scanf("%s", c[i].name);
            //check category uniqeness
            for(int f=0;f<i;f++)
            {
                while(!strcmp(c[f].name,c[i].name))
                {
                    printf("duplictaed! \n");
                    printf("please Enter new Category name \n");
                    scanf("%s", c[i].name);
                }

            }

           // Check if the string consists only of alphabetic characters
              if (isAlphaString(c[i].name)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", c[i].name);

                       }


            printf("Enter Product Count : \n ");
            scanf("%d", &c[i].numProducts);
            for (int j = 0; j < c[i].numProducts; j++) {


                printf("Enter Product %d Name: \n", j + 1);
                scanf("%s", c[i].p[j].name);
                //check product name unique

                for(int f=0;f<j;f++)
            {
                while(!strcmp(c[i].p[f].name,c[i].p[j].name))
                {
                    printf("duplictaed! \n");
                    printf("please Enter new product name \n");
                    scanf("%s", c[i].p[j].name);
                }

            }


            // Check if the string consists only of alphabetic characters
              if (isAlphaString(c[i].p[j].name)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", c[i].p[j].name);

                       }
                printf("ID: (!!note: it must be unique)  \n");
                scanf("%d",&c[i].p[j].ID);
                // check ID uniqueness
                 for(int f=0;f<j;f++)
                    {
                while(c[i].p[f].ID == c[i].p[j].ID)
                {
                    printf("duplictaed! \n");
                    printf("please Enter new ID name \n");
                    scanf("%d", &c[i].p[j].ID);
                }

                     }


                printf("Enter Product %d price: \n", j + 1);
                scanf("%f", &c[i].p[j].price);
                printf("Enter Product %d quantity: \n", j + 1);
                scanf("%d", &c[i].p[j].quantity);
            }
        }
        x += 1;
        oldCatCount = catCount;
    } else {
        for (int i = oldCatCount; i < (oldCatCount + catCount); i++) {
            printf("Enter category %d Name : \n ", i + 1);
            scanf("%s", c[i].name);

            //check category uniqeness
            for(int f=0;f<i;f++)
            {
                while(!strcmp(c[f].name,c[i].name))
                {
                    printf("duplictaed! \n");
                    printf("please Enter new Category name \n");
                    scanf("%s", c[i].name);
                }

            }

            // Check if the string consists only of alphabetic characters
              if (isAlphaString(c[i].name)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", c[i].name);

                       }
            printf("Enter Product Count : \n ");
            scanf("%d", &c[i].numProducts);
            for (int j = 0; j < c[i].numProducts; j++) {

                printf("Enter Product %d Name: \n", j + 1);
                scanf("%s", c[i].p[j].name);

                //check product name unique

                for(int f=0;f<j;f++)
            {
                while(!strcmp(c[i].p[f].name,c[i].p[j].name))
                {
                    printf("duplictaed! \n");
                    printf("please Enter new product name \n");
                    scanf("%s", c[i].p[j].name);
                }

            }


            // Check if the string consists only of alphabetic characters
              if (isAlphaString(c[i].p[j].name)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", c[i].p[j].name);

                       }

                printf("Enter Product %d ID: \n", j + 1);
                scanf("%d",&c[i].p[j].ID);

                // check ID uniqueness
                 for(int f=0;f<j;f++)
                    {
                while(c[i].p[f].ID == c[i].p[j].ID)
                {
                    printf("duplictaed! \n");
                    printf("please Enter new ID name \n");
                    scanf("%d", &c[i].p[j].ID);
                }

                     }


                printf("Enter Product %d price: \n", j + 1);
                scanf("%f", &c[i].p[j].price);
                printf("Enter Product %d quantity: \n", j + 1);
                scanf("%d", &c[i].p[j].quantity);
            }
        }
        oldCatCount += catCount;
    }
}
void addNewProduct()
{
    char Cname[50];
    char Pname[50];
    int Quantity=0,Id;
    float Price=0;
    printf("Product Name :  \n");
    scanf("%s",Pname);

            // Check if the string consists only of alphabetic characters
              if (isAlphaString(Pname)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", Pname);

                       }

    printf("Enter Category Name To Add Product Inside It:  \n");
    scanf("%s",Cname);


            // Check if the string consists only of alphabetic characters
              if (isAlphaString(Cname)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", Cname);

                       }

    printf("Product Price:  \n");
    scanf("%f",&Price);

    printf("Product quantity:  \n");
    scanf("%d",&Quantity);

    printf("Product ID:  \n");
    scanf("%d",&Id);


    for(int i = 0 ; i < oldCatCount ; i++){
        if(!strcmp(Cname,c[i].name))
        {
            int x = c[i].numProducts;
                    strcpy (c[i].p[x].name,Pname);
                    c[i].p[x].ID=Id;
                    c[i].p[x].price=Price;
                    c[i].p[x].quantity=Quantity;
                    c[i]. numProducts+=1;

        }

    }


}
void sellProduct() {
    for(int i=0;i<oldCatCount;i++)
    {
        printf("\n %s    \n",c[i].name);
        for(int j=0;j<c[i].numProducts;j++)
        {
            printf("   |[%s] ID: %d      |",c[i].p[j].name,c[i].p[j].ID);
        }

    }
int total_price = 0;
    printf("\n Please Enter Total Number Of Products:\n");
    scanf("%d", &u);
    int tPrice[20];
    for (int i = 0; i < u; i++) {
        char Cname[50];
        int id = 0;
        int quantity = 0;


        printf("Please Enter the Category name: \n");
        scanf("%s", Cname);


            // Check if the string consists only of alphabetic characters
              if (isAlphaString(Cname)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", Cname);

                       }

        printf("Please Enter the ID name:\n ");
        scanf("%d", &id);
        printf("Please Enter %d quantity: ", id);
        scanf("%d", &quantity);

        int found = 0;

        for (int i = 0; i < oldCatCount; i++) {
            if (!strcmp(c[i].name, Cname)) {
                for (int j = 0; j < c[i].numProducts; j++) {
                    if (id == c[i].p[j].ID) {
                        if (c[i].p[j].quantity >= quantity) {
                            c[i].p[j].quantity -= quantity;
                            int product_price = c[i].p[j].price * quantity;
                             total_price+=product_price;
                            printf("Product name: %s | Product Price: %d\n", c[i].p[j].name,  product_price);

                            // Remove product if quantity is 0
                            if (c[i].p[j].quantity == 0) {
                                removeProduct(i, j);
                            }

                            found = 1;
                            break;
                        } else {
                            printf("Not enough quantity available for %d.\n\n\n", id);
                            found = 1;
                            break;
                        }
                    }
                }
            }
        }

        if (!found) {
            printf("Product not found in any category.\n");
            i--;
        }
    }

    printf("Total Price %d | total products %d\n", total_price, u);
}


void moveProduct() {
    char oldCategoryName[20];
    char newCategoryName[20];

    // Check if the string consists only of alphabetic characters
              if (isAlphaString(oldCategoryName)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", oldCategoryName);

                       }



    for(int i=0;i<oldCatCount;i++)
    {
        printf("%s    :\n",c[i].name);
        for(int j=0;j<c[i].numProducts;j++)
        {
            printf("[%s]  \n",c[i].p[j].name);
        }
    }
    printf("Enter the old category name: \n");
    scanf("%s", oldCategoryName);

    // Check if the string consists only of alphabetic characters
              if (isAlphaString(oldCategoryName)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", oldCategoryName);

                       }

    printf("Enter the new category name: \n");
    scanf("%s", newCategoryName);

    // Check if the string consists only of alphabetic characters
              if (isAlphaString(newCategoryName)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", newCategoryName);

                       }

    int foundOldCategory = 0;
    int foundNewCategory = 0;

    int oldCategoryIndex, newCategoryIndex;
    for (int i = 0; i < oldCatCount; i++) {
        if (!strcmp(c[i].name, oldCategoryName)) {
            foundOldCategory = 1;
            oldCategoryIndex = i;
        }

        if (!strcmp(c[i].name, newCategoryName)) {
            foundNewCategory = 1;
            newCategoryIndex = i;
        }

        if (foundOldCategory && foundNewCategory) {
            break;
        }
    }

    if (!foundOldCategory || !foundNewCategory) {
        printf("One or both categories not found.\n");
        return;
    }

    char productName[20];
    printf("Enter the product name to move: \n");
    scanf("%s", productName);

   // Check if the string consists only of alphabetic characters
              if (isAlphaString(productName)) {

                    }
                     else {
                    printf("Please Enter alphabetic characters.\n");
                    scanf("%s", productName);

                       }


    int foundProduct = 0;
    int productIndex;

    for (int j = 0; j < c[oldCategoryIndex].numProducts; j++) {
        if (!strcmp(c[oldCategoryIndex].p[j].name, productName)) {
            foundProduct = 1;
            productIndex = j;
            break;
        }
    }

    if (!foundProduct) {
        printf("Product not found in the old category.\n");
        return;
    }

    int moveQuantity;
    printf("Enter the quantity to move: \n");
    scanf("%d", &moveQuantity);

    if (moveQuantity > c[oldCategoryIndex].p[productIndex].quantity) {
        printf("Not enough quantity available in the old category.\n");
        return;
    }

    strcpy(c[newCategoryIndex].p[c[newCategoryIndex].numProducts].name, c[oldCategoryIndex].p[productIndex].name);
    c[newCategoryIndex].p[c[newCategoryIndex].numProducts].ID = c[oldCategoryIndex].p[productIndex].ID;
    c[newCategoryIndex].p[c[newCategoryIndex].numProducts].price = c[oldCategoryIndex].p[productIndex].price;
    c[newCategoryIndex].p[c[newCategoryIndex].numProducts].quantity = moveQuantity;
    c[newCategoryIndex].numProducts++;

    c[oldCategoryIndex].p[productIndex].quantity -= moveQuantity;

    // Remove product from old category if quantity is 0
    if (c[oldCategoryIndex].p[productIndex].quantity == 0) {
        removeProduct(oldCategoryIndex, productIndex);
    }

    printf("Product moved successfully.\n");
}


void showAvailableProducts() {
    for (int i = 0; i < oldCatCount; i++) {
        printf("  %s Category Have  :  %d Products \n", c[i].name, c[i].numProducts);

        for (int j = 0; j < c[i].numProducts; j++) {
            printf("  %d)%s : \n", j + 1, c[i].p[j].name);
            printf("      |Price    |%.2f\n", c[i].p[j].price);
            printf("      |Quantity | %d \n", c[i].p[j].quantity);
            printf("      |ID       |%d\n", c[i].p[j].ID);
            printf("------------------------------------------------------------------------------------------------------------------\n");
        }
    }
}

void removeProduct(int categoryIndex, int productIndex) {
    // Shift products to fill the empty space
    for (int i = productIndex; i < c[categoryIndex].numProducts - 1; i++) {
        strcpy(c[categoryIndex].p[i].name, c[categoryIndex].p[i + 1].name);
        c[categoryIndex].p[i].ID = c[categoryIndex].p[i + 1].ID;
        c[categoryIndex].p[i].price = c[categoryIndex].p[i + 1].price;
        c[categoryIndex].p[i].quantity = c[categoryIndex].p[i + 1].quantity;
    }

    // Decrease the number of products in the category
    c[categoryIndex].numProducts--;

    printf("Product removed successfully.\n");
}
