#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include "assistant.h"

void initializeStore(Store *store) {
    store->products = (Product *) malloc(sizeof(Product));
    store->size = 0;
    store->capacity = 0;
}

void initializeCart(Cart *cart) {
    cart->products = (Product *) malloc(sizeof(Product));
    cart->size = 0;
    cart->capacity = 0;
}

void addProductToStore(Store *store, const char *name, int price, int quantity) {
    if (store->size == store->capacity) {
        store->capacity++;
        store->products = realloc(store->products, store->capacity * sizeof(Product));
        if (store->products == NULL) {
            printf("Error reallocating memory!");
            exit(0);
        }
    }

    strcpy(store->products[store->size].name, name);
    store->products[store->size].price = price;
    store->products[store->size].quantity = quantity;

    store->size++;
    if (store->size == store->capacity) {
        store->capacity++;
        store->products = realloc(store->products, store->capacity * sizeof(Product));
    }
}

void loadWebShop(Store *store) {
    initializeStore(store);
    char filename[NAME_LENGTH];
    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file");
        exit(0);
    }

    char name[NAME_LENGTH];
    int price, quantity;

    while (fscanf(file, "%s %d %d", name, &price, &quantity) == 3) {
        addProductToStore(store, name, price, quantity);
    }
    printf(" Successfully loaded\n");
    fclose(file);
}

void updateWebShop(Store *store) {
    char filename[NAME_LENGTH];
    printf("Enter the filename: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file!");
        return;
    }

    for (int i = 0; i < store->size; i++) {
        fprintf(file, "%s %d %d\n", store->products[i].name, store->products[i].price, store->products[i].quantity);
    }

    fclose(file);
}

void allStoreProducts(Store *store) {
    if (store->size == 0) {
        printf("Store hasn't been loaded yet or is empty!");
    } else {
        for (int i = 0; i < store->size; i++) {
            printf("Name: %s, price: %d, quantity: %d\n ", store->products[i].name, store->products[i].price,
                   store->products[i].quantity);
        }
    }
}

void insertToCart(Store *store, Cart *cart) {
    char name[NAME_LENGTH];
    int quantity;

    printf("Enter the product details (name and quantity): ");

    if (scanf("%s %d", name, &quantity) == 2) {

        bool storeContains = false;
        int storeIndex;

        for (int i = 0; i < store->size; ++i) {
            if (strcmp(store->products[i].name, name) == 0) {
                storeIndex = i;
                storeContains = true;
            }
        }
        int productIndex = 0;
        bool cartContains = false;

        if (storeContains) {
            for (int i = 0; i < cart->size; ++i) {
                if (strcmp(cart->products[i].name, name) == 0) {
                    productIndex = i;
                    cartContains = true;
                }
            }
            if (cartContains) {
                cart->products[productIndex].quantity += quantity;
                printf("Successfully updated quantity: %s\n", cart->products[productIndex].name);
            } else {
                if (cart->size == cart->capacity) {
                    cart->capacity++;
                    cart->products = realloc(cart->products, cart->capacity * sizeof(Product));
                }
                strcpy(cart->products[cart->size].name, name);
                cart->products[cart->size].price = store->products[storeIndex].price;
                cart->products[cart->size].quantity = quantity;
                printf("Successfully added: %s\n", cart->products[cart->size].name);
                cart->size++;
            }
        } else {
            printf("Store file hasn't been loaded yet or does not contain this product!\n");
        }
    } else {
        printf("Invalid input format! Use 'name price quantity'.\n");
    }
}

void allCartProducts(Cart *cart) {
    for (int i = 0; i < cart->size; i++) {
        printf("Name: %s, price: %d, quantity: %d\n ", cart->products[i].name, cart->products[i].price,
               cart->products[i].quantity);
    }
}

void overallPriceCart(Cart *cart) {
    int overallPrice = 0;
    for (int i = 0; i < cart->size; ++i) {
        overallPrice += cart->products[i].price * cart->products[i].quantity;
    }
    printf("Overall price: %d\n", overallPrice);
}

void buyProductsCart(Store *store, Cart *cart) {
    for (int i = 0; i < cart->size; i++) {
        int requestedQuantity = cart->products[i].quantity;
        int availableQuantity = 0;

        for (int j = 0; j < store->size; j++) {
            if (strcmp(store->products[j].name, cart->products[i].name) == 0) {
                availableQuantity = store->products[j].quantity;
                break;
            }
        }

        if (requestedQuantity <= availableQuantity) {
            for (int j = 0; j < store->size; j++) {
                if (strcmp(store->products[j].name, cart->products[i].name) == 0) {
                    store->products[j].quantity -= requestedQuantity;
                    break;
                }
            }
            printf("Successfully purchased!\n");
        } else {
            printf("%d %s are missing\n", requestedQuantity - availableQuantity, cart->products[i].name);
            for (int j = 0; j < store->size; j++) {
                if (strcmp(store->products[j].name, cart->products[i].name) == 0) {
                    store->products[j].quantity = 0;
                    break;
                }
            }
        }
    }
    initializeCart(cart);
}

void exitProgram(Store *store, Cart *cart) {
    free(store->products);
    free(cart->products);
    exit(0);
}