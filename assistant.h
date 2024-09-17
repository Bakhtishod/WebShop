#ifndef ASSIGNMENT_ASSISTANT_H
#define ASSIGNMENT_ASSISTANT_H

#define NAME_LENGTH 50


typedef struct {
    char name[NAME_LENGTH];
    int price;
    int quantity;
} Product;

typedef struct {
    Product *products;
    int size;
    int capacity;
} Store, Cart;

void initializeStore(Store *store);

void initializeCart(Cart *cart);

void addProductToStore(Store *store, const char *name, int price, int quantity);

void loadWebShop(Store *store);

void updateWebShop(Store *store);

void allStoreProducts(Store *store);

void insertToCart(Store *store, Cart *cart);

void allCartProducts(Cart *cart);

void overallPriceCart(Cart *cart);

void buyProductsCart(Store *store, Cart *cart);

void exitProgram(Store *store, Cart *cart);

#endif
