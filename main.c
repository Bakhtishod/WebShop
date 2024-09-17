#include <stdio.h>
#include "assistant.h"

int main() {
    Store store;
    Cart cart;

    initializeStore(&store);
    initializeCart(&cart);

    int option;

    do {
        printf("Menu:\n"
               "1. Load webshop store from a file\n"
               "2. Write the content of the store to a file\n"
               "3. Insert an item to cart\n"
               "4. Get the price of cart\n"
               "5. Buy the products\n"
               "6. Exit the program\n");

        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                loadWebShop(&store);
                break;
            case 2:
                updateWebShop(&store);
                break;
            case 3:
                insertToCart(&store, &cart);
                break;
            case 4:
                overallPriceCart(&cart);
                break;
            case 5:
                buyProductsCart(&store, &cart);
                break;
            case 6:
                exitProgram(&store, &cart);
                break;
//            case 7:
//                allStoreProducts(&store);
//                break;
//            case 8:
//                allCartProducts(&cart);
//                break;
            default:
                printf("Invalid choice. Please, try again!\n");
        }
    } while (option != 6);
    return 0;
}
