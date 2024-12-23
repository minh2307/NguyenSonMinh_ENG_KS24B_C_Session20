#include <stdio.h>
#include <string.h>

typedef struct {
    int productId;
    char productName[50];
    float importPrice;
    float sellPrice;
    int quantity;
} Product;

void Menu();
void addProduct(Product products[], int *n, float *revenue);
void showProducts(Product products[], int n);
void importProduct(Product products[], int *n, float *revenue);
void updateProduct(Product products[], int n);
void sortProducts(Product products[], int n);
void searchProduct(Product products[], int n);
void sellProduct(Product products[], int *n, float *revenue);
void displayRevenue(float revenue);

int main() {
    int choice;
    int n = 0; 
    float revenue = 0.0f; 
    Product products[100];

    do {
        Menu();
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addProduct(products, &n, &revenue);
                break;
            case 2:
                showProducts(products, n);
                break;
            case 3:
                importProduct(products, &n, &revenue);
                break;
            case 4:
                updateProduct(products, n);
                break;
            case 5:
                sortProducts(products, n);
                showProducts(products, n);
                break;
            case 6:
                searchProduct(products, n);
                break;
            case 7:
                sellProduct(products, &n, &revenue);
                break;
            case 8:
                displayRevenue(revenue);
                break;
            case 9:
                printf("Thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
        }
    } while (choice != 9);

    return 0;
}

void Menu() {
    printf("\nMENU\n");
    printf("1. Nhap so luong va thong tin san pham.\n");
    printf("2. Hien thi danh sach san pham.\n");
    printf("3. Nhap san pham.\n");
    printf("4. Cap nhat thong tin san pham.\n");
    printf("5. Sap xep san pham theo gia (tang/giam).\n");
    printf("6. Tim kiem san pham.\n");
    printf("7. Ban san pham.\n");
    printf("8. Doanh thu hien tai.\n");
    printf("9. Thoat.\n");
}

void addProduct(Product products[], int *n, float *revenue) {
    int quantity;
    printf("Nhap so luong san pham muon them: ");
    scanf("%d", &quantity);
    for (int i = 0; i < quantity; i++) {
        printf("Nhap thong tin san pham thu %d:\n", i + 1);
        printf("Ma san pham: ");
        scanf("%d", &products[*n].productId);
        getchar();
        printf("Ten san pham: ");
        fgets(products[*n].productName, sizeof(products[*n].productName), stdin);
        products[*n].productName[strcspn(products[*n].productName, "\n")] = 0;
        printf("Gia nhap: ");
        scanf("%f", &products[*n].importPrice);
        printf("Gia ban: ");
        scanf("%f", &products[*n].sellPrice);
        printf("So luong: ");
        scanf("%d", &products[*n].quantity);
        *revenue -= products[*n].quantity * products[*n].importPrice;
        (*n)++;
    }
}

void showProducts(Product products[], int n) {
    printf("\nDanh sach san pham:\n");
    for (int i = 0; i < n; i++) {
        printf("Ma SP: %d \t Ten SP: %s \t Gia nhap: %.2f \t Gia ban: %.2f \t So luong: %d\n",
               products[i].productId, products[i].productName, products[i].importPrice, products[i].sellPrice, products[i].quantity);
    }
}

void importProduct(Product products[], int *n, float *revenue) {
    int productId, additionalQuantity;
    printf("Nhap ma san pham muon nhap: ");
    scanf("%d", &productId);
    for (int i = 0; i < *n; i++) {
        if (products[i].productId == productId) {
            printf("Nhap so luong muon them: ");
            scanf("%d", &additionalQuantity);
            products[i].quantity += additionalQuantity;
            *revenue -= additionalQuantity * products[i].importPrice;
            printf("Nhap hang thanh cong!\n");
            return;
        }
    }

    printf("San pham khong ton tai trong danh sach, vui long them moi!\n");
}

void updateProduct(Product products[], int n) {
    int productId, index = -1;
    printf("Nhap ma san pham can cap nhat: ");
    scanf("%d", &productId);
    for (int i = 0; i < n; i++) {
        if (products[i].productId == productId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay san pham voi ma %d\n", productId);
        return;
    }

    printf("Nhap thong tin moi cho san pham:\n");
    getchar();
    printf("Ten san pham: ");
    fgets(products[index].productName, sizeof(products[index].productName), stdin);
    products[index].productName[strcspn(products[index].productName, "\n")] = 0;
    printf("Gia nhap: ");
    scanf("%f", &products[index].importPrice);
    printf("Gia ban: ");
    scanf("%f", &products[index].sellPrice);
    printf("So luong: ");
    scanf("%d", &products[index].quantity);

    printf("Cap nhat thong tin thanh cong!\n");
}

void sortProducts(Product products[], int n) {
    int choice;
    printf("Sap xep san pham theo gia: 1. Tang dan, 2. Giam dan\n");
    printf("Lua chon cua ban: ");
    scanf("%d", &choice);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((choice == 1 && products[i].sellPrice > products[j].sellPrice) ||
                (choice == 2 && products[i].sellPrice < products[j].sellPrice)) {
                Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }

    printf("Sap xep thanh cong!\n");
}

void searchProduct(Product products[], int n) {
    char searchName[50];
    getchar(); 
    printf("Nhap ten san pham can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(products[i].productName, searchName)) {
            printf("Ma SP: %d \t Ten SP: %s \t Gia nhap: %.2f \t Gia ban: %.2f \t So luong: %d\n",
                   products[i].productId, products[i].productName, products[i].importPrice, products[i].sellPrice, products[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("Khong tim thay san pham voi ten: %s\n", searchName);
    }
}

void sellProduct(Product products[], int *n, float *revenue) {
    int productId, sellQuantity;
    printf("Nhap ma san pham can ban: ");
    scanf("%d", &productId);

    for (int i = 0; i < *n; i++) {
        if (products[i].productId == productId) {
            if (products[i].quantity == 0) {
                printf("San pham da het hang!\n");
                return;
            }

            printf("Nhap so luong can ban: ");
            scanf("%d", &sellQuantity);

            if (sellQuantity > products[i].quantity) {
                printf("Khong du hang de ban!\n");
                return;
            }

            products[i].quantity -= sellQuantity;
            *revenue += sellQuantity * products[i].sellPrice;
            printf("Ban hang thanh cong!\n");
            return;
        }
    }

    printf("San pham khong ton tai!\n");
}

void displayRevenue(float revenue) {
    printf("Doanh thu hien tai: %.2f\n", revenue);
}

