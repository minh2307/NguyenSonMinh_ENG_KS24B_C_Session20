#include <stdio.h>
#include <string.h>

typedef struct {
    int bookId;
    char bookName[50];
    char author[50];
    float price;
    char category[50];
} book;

void Menu();
void addBook(book book[], int n);
void show(book book[], int n);
void insertBook(book book[], int *n);
void delBook(book book[], int *n);
void updateBook(book book[], int n);
void sortBooks(book book[], int n);
void searchBook(book book[], int n);

int main() {
    int choice;
    int n = 0;
    book books[100];

    do {
        Menu();
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Moi ban nhap vao so luong sach: ");
                scanf("%d", &n);
                addBook(books, n);
                break;
            case 2:
                show(books, n);
                break;
            case 3:
                insertBook(books, &n);
                show(books, n);
                break;
            case 4:
                delBook(books, &n);
                show(books, n);
                break;
            case 5:
                updateBook(books, n);
                break;
            case 6:
                sortBooks(books, n);
                show(books, n);
                break;
            case 7:
                searchBook(books, n);
                break;
            case 8:
                printf("Thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
        }
    } while (choice != 8);

    return 0;
}

void Menu() {
    printf("\nMenu\n");
    printf("1. Nhap so luong va thong tin\n");
    printf("2. Hien thi thong tin\n");
    printf("3. Them sach vao vi tri\n");
    printf("4. Xoa sach theo ma\n");
    printf("5. Cap nhat thong tin theo ma sach\n");
    printf("6. Sap xep sach theo gia (tang/giam)\n");
    printf("7. Tim kiem sach theo ten sach\n");
    printf("8. Thoat\n");
}

void addBook(book books[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Nhap vao thong tin cua quyen sach thu %d:\n", i + 1);
        printf("Id cua sach: ");
        scanf("%d", &books[i].bookId);
        getchar();
        printf("Nhap vao ten sach: ");
        fgets(books[i].bookName, sizeof(books[i].bookName), stdin);
        books[i].bookName[strcspn(books[i].bookName, "\n")] = 0;
        printf("Ten tac gia: ");
        fgets(books[i].author, sizeof(books[i].author), stdin);
        books[i].author[strcspn(books[i].author, "\n")] = 0;
        printf("Gia sach: ");
        scanf("%f", &books[i].price);
        getchar();
        printf("The loai cua sach: ");
        fgets(books[i].category, sizeof(books[i].category), stdin);
        books[i].category[strcspn(books[i].category, "\n")] = 0;
    }
}

void show(book books[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Id: %d \t Ten sach: %s \t Ten tac gia: %s \t Gia tien: %.2f \t The loai: %s\n",
               books[i].bookId, books[i].bookName, books[i].author, books[i].price, books[i].category);
    }
}

void insertBook(book books[], int *n) {
    int index;
    printf("Nhap vao vi tri muon them sach: ");
    scanf("%d", &index);
    if (index < 0 || index > *n) {
        printf("Vi tri khong hop le!\n");
        return;
    }

    for (int i = *n; i > index; i--) {
        books[i] = books[i - 1];
    }

    printf("Nhap vao thong tin cua quyen sach moi:\n");
    printf("Id cua sach: ");
    scanf("%d", &books[index].bookId);
    getchar();
    printf("Nhap vao ten sach: ");
    fgets(books[index].bookName, sizeof(books[index].bookName), stdin);
    books[index].bookName[strcspn(books[index].bookName, "\n")] = 0;
    printf("Ten tac gia: ");
    fgets(books[index].author, sizeof(books[index].author), stdin);
    books[index].author[strcspn(books[index].author, "\n")] = 0;
    printf("Gia sach: ");
    scanf("%f", &books[index].price);
    getchar();
    printf("The loai cua sach: ");
    fgets(books[index].category, sizeof(books[index].category), stdin);
    books[index].category[strcspn(books[index].category, "\n")] = 0;

    (*n)++;
}

void delBook(book books[], int *n) {
    int delBookId, index = -1;
    printf("Nhap ID sach muon xoa: ");
    scanf("%d", &delBookId);
    for (int i = 0; i < *n; i++) {
        if (books[i].bookId == delBookId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay sach voi ID %d\n", delBookId);
        return;
    }

    for (int i = index; i < *n - 1; i++) {
        books[i] = books[i + 1];
    }

    (*n)--;
    printf("Xoa thanh cong!\n");
}

void updateBook(book books[], int n) {
    int bookId, index = -1;
    printf("Nhap ID sach muon cap nhat: ");
    scanf("%d", &bookId);
    for (int i = 0; i < n; i++) {
        if (books[i].bookId == bookId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay sach voi ID %d\n", bookId);
        return;
    }

    printf("Nhap vao thong tin moi:\n");
    printf("Nhap vao ten sach: ");
    getchar();
    fgets(books[index].bookName, sizeof(books[index].bookName), stdin);
    books[index].bookName[strcspn(books[index].bookName, "\n")] = 0;
    printf("Ten tac gia: ");
    fgets(books[index].author, sizeof(books[index].author), stdin);
    books[index].author[strcspn(books[index].author, "\n")] = 0;
    printf("Gia sach: ");
    scanf("%f", &books[index].price);
    getchar();
    printf("The loai cua sach: ");
    fgets(books[index].category, sizeof(books[index].category), stdin);
    books[index].category[strcspn(books[index].category, "\n")] = 0;

    printf("Cap nhat thanh cong!\n");
}

void sortBooks(book books[], int n) {
    int choice;
    printf("Sap xep sach theo gia: 1. Tang dan, 2. Giam dan\n");
    printf("Lua chon cua ban: ");
    scanf("%d", &choice);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((choice == 1 && books[i].price > books[j].price) ||
                (choice == 2 && books[i].price < books[j].price)) {
                book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

    printf("Sap xep thanh cong!\n");
}

void searchBook(book books[], int n) {
    char searchName[50];
    getchar();
    printf("Nhap ten sach can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(books[i].bookName, searchName)) {
            printf("Id: %d \t Ten sach: %s \t Ten tac gia: %s \t Gia tien: %.2f \t The loai: %s\n",
                   books[i].bookId, books[i].bookName, books[i].author, books[i].price, books[i].category);
            found = 1;
        }
    }

    if (!found) {
        printf("Khong tim thay sach voi ten: %s\n", searchName);
    }
}

