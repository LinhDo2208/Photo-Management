#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <ctype.h>
#include <windows.h>

#define MAX_STRING 1000

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
typedef struct
{
    char name[MAX_STRING];
    char datec[11];
    char datem[11];
    char datea[11];
    char path[MAX_STRING];
    long size;
} FileInfo;

struct node
{
    FileInfo data;
    struct node *next;
};
typedef struct node *Pnode;
typedef struct node *Linkedlist;

Pnode makeNode(char a[], char b[], char c[], char d[], char e[], long size)
{
    Pnode anode = (Pnode)malloc(sizeof(struct node));
    strcpy(anode->data.name, a);
    strcpy(anode->data.datec, b);
    strcpy(anode->data.datem, c);
    strcpy(anode->data.datea, d);
    strcpy(anode->data.path, e);
    anode->data.size = size;
    anode->next = NULL;
    return anode;
}

void swap(Pnode a, Pnode b)
{
    FileInfo temp = a->data;
    a->data = b->data;
    b->data = temp;
}

Pnode addNode(Linkedlist H, char a[], char b[], char c[], char d[], char e[], long size)
{
    Pnode p = makeNode(a, b, c, d, e, size);
    if (H == NULL)
        H = p;
    else
    {
        p->next = H;
        H = p;
    }
    return H;
}

void showlist(Linkedlist H)
{
    if (H == NULL)
        printf("Empty\n");
    else
    {
        Pnode q = H;
        while (q != NULL)
        {
            setColor(14);
            printf("\U0001F4C4 Name: ");
            setColor(15);
            printf("%s\n", q->data.name);

            setColor(14);
            printf("\U0001F4C5 Date of creation: ");
            setColor(15);
            printf("%s\n", q->data.datec);

            setColor(14);
            printf("\u2692\uFE0F Date of modification: ");
            setColor(15);
            printf("%s\n", q->data.datem);

            setColor(14);
            printf("\U0001F552 Date of access: ");
            setColor(15);
            printf("%s\n", q->data.datea);

            setColor(14);
            printf("\U0001F4C2 Path: ");
            setColor(15);
            printf("%s\n", q->data.path);

            setColor(14);
            printf("\U0001F4BE Size: ");
            setColor(15);
            printf("%ld bytes\n", q->data.size);

            setColor(8);
            printf("-------------------------\n");
            setColor(15);
            printf("-------------------------\n");
            q = q->next;
        }
    }
}

void showRubbishlist(Linkedlist R)
{
    printf("----------RECYCLE BIN----------\n");
    showlist(R);
}

void Lower(char *a)
{
    if (a == NULL)
        return;
    for (int i = 0; a[i] != '\0'; i++)
        a[i] = tolower(a[i]);
}

// find photo by name
Pnode findName(Linkedlist H, char a[])
{
    Pnode q = H;
    Linkedlist A = NULL;
    int n = strlen(a);
    while (q != NULL)
    {
        char b[MAX_STRING];
        char c[MAX_STRING];
        strcpy(b, q->data.name);
        strcpy(c, a);
        Lower(b);
        Lower(c);
        if (strncmp(b, c, n) == 0)
            A = addNode(A, q->data.name, q->data.datec, q->data.datem, q->data.datec, q->data.path, q->data.size);
        q = q->next;
    }
    return A;
}

Pnode findFirstName(Linkedlist H, char a[])
{
    a[strcspn(a, "\n")] = '\0';
    Pnode q = H;
    while (q != NULL)
    {
        if (strcmp(q->data.name, a) == 0)
            return q;
        q = q->next;
    }
    return NULL;
}

// edit photo by name
void editPhoto(Linkedlist H, char a[])
{
    Pnode q = findFirstName(H, a);
    if (q == NULL)
        printf("Not found!\n");
    else
    {
        getchar();
        printf("New name: ");
        gets(q->data.name);
        printf("New date of creation (dd/mm/yyyy): ");
        gets(q->data.datec);
        printf("New date of modification (dd/mm/yyyy): ");
        gets(q->data.datem);
        printf("New date of access (dd/mm/yyyy): ");
        gets(q->data.datea);
        printf("Done!\n");
    }
}

Pnode delete_1(Linkedlist H, Pnode P)
{
    if (P == H)
    {
        H = H->next;
        P->next = NULL;
        free(P);
    }
    else if (P != NULL)
    {
        Pnode R = H;
        while (R->next != NULL && R->next != P)
        {
            R = R->next;
        }

        if (R->next == P)
        {
            R->next = P->next;
            P->next = NULL;
            free(P);
        }
    }
    return H;
}

Pnode delete_2(Linkedlist H, Pnode P)
{
    if (P == H)
    {
        H = H->next;
        P->next = NULL;
        free(P);
    }
    else if (P->next != NULL)
    {
        Pnode temp = P->next;
        P->data = temp->data;
        P->next = temp->next;
        free(temp);
    }
    else
    {
        H = delete_1(H, P);
    }
    return H;
}

Pnode delete(Linkedlist H, char a[])
{
    Pnode q = findFirstName(H, a);
    if (q != NULL)
    {
        H = delete_2(H, q);
    }
    else
    {
        printf("Photo not found!\n");
    }
    return H;
}

int compareDate(const char *a, const char *b)
{
    int day_a, month_a, year_a, day_b, month_b, year_b;
    sscanf(a, "%d/%d/%d", &day_a, &month_a, &year_a);
    sscanf(b, "%d/%d/%d", &day_b, &month_b, &year_b);
    if (year_a != year_b)
        return year_b - year_a;
    if (month_a != month_b)
        return month_b - month_a;
    return day_b - day_a;
}

Pnode sortListByDate(Linkedlist H, int mode, int dateType)
{
    Pnode p, q;
    for (p = H; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            const char *date1, *date2;
            switch (dateType)
            {
            case 1:
                date1 = p->data.datec;
                date2 = q->data.datec;
                break;
            case 2:
                date1 = p->data.datem;
                date2 = q->data.datem;
                break;
            case 3:
                date1 = p->data.datea;
                date2 = q->data.datea;
                break;
            default:
                return H;
            }
            int cmp = compareDate(date1, date2);
            if ((mode == 1 && cmp > 0) || (mode == 2 && cmp < 0))
                swap(p, q);
        }
    }
    return H;
}

Pnode sortingSize(Linkedlist H, int mode)
{
    // mode = 1 sort in ascending order, mode = 2 sort in descending order
    Pnode p, q;
    for (p = H; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (((mode == 1) && (p->data.size > q->data.size)) || ((mode == 2) && (p->data.size < q->data.size)))
                swap(p, q);
        }
    }
    return H;
}

Pnode sortingName(Linkedlist H, int mode)
{
    // mode = 1 sorts from A-Z, mode = 2 sorts from Z-A
    Pnode p, q;
    for (p = H; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            char a[MAX_STRING];
            char b[MAX_STRING];
            strcpy(a, p->data.name);
            strcpy(b, q->data.name);
            Lower(a);
            Lower(b);
            int cmp = strcmp(a, b);
            if (((mode == 2) && (cmp < 0)) || ((mode == 1) && (cmp > 0)))
                swap(p, q);
        }
    }
    return H;
}

int compareFile(char path1[], char path2[])
{
    FILE *fp1 = fopen(path1, "rb");
    FILE *fp2 = fopen(path2, "rb");

    int ch1, ch2;
    do
    {
        ch1 = fgetc(fp1);
        ch2 = fgetc(fp2);
        if (ch1 != ch2)
        {
            fclose(fp1);
            fclose(fp2);
            return 0;
        }
    } while (ch1 != EOF && ch2 != EOF);
    return (ch1 == ch2);
}

int isSame(Linkedlist H, char newPath[])
{
    Pnode p = H;
    while (p != NULL)
    {
        if (compareFile(p->data.path, newPath))
            return 1; // Trùng
        p = p->next;
    }
    return 0; // Không trùng
}

int isSameName(Linkedlist H, char name[])
{
    Pnode Q = H;
    while (Q != NULL)
    {
        if (strcmp(Q->data.name, name) == 0)
            return 1;
        Q = Q->next;
    }
    return 0;
}

void formatDate(time_t rawTime, char *buffer) // Date from raw time to string
{
    struct tm *timeinfo = localtime(&rawTime);
    strftime(buffer, 20, "%d/%m/%Y", timeinfo);
}

// Get information from file path
int getFileInfo(const char *filepath, char *filename, char *datecStr, char *datemStr, char *dateaStr, long *size)
{
    struct stat fileStat;
    if (stat(filepath, &fileStat) == -1)
    {
        perror("Can not get file information!");
        return 0;
    }

    const char *file_name = strrchr(filepath, '\\');

    strcpy(filename, file_name + 1);
    formatDate(fileStat.st_ctime, datecStr);
    formatDate(fileStat.st_mtime, datemStr);
    formatDate(fileStat.st_atime, dateaStr);
    *size = fileStat.st_size;
    return 1;
}

Linkedlist loadFromFile(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return NULL;
    Linkedlist H = NULL;
    char line[MAX_STRING * 4];
    while (fgets(line, sizeof(line), fp))
    {
        char *name = strtok(line, "|");
        char *datec = strtok(NULL, "|");
        char *datem = strtok(NULL, "|");
        char *datea = strtok(NULL, "|");
        char *path = strtok(NULL, "|");
        char *Strsize = strtok(NULL, "\n");
        if (name && datec && datem && datea && path && Strsize)
        {
            long size = atol(Strsize); // Convert char to long int
            H = addNode(H, name, datec, datem, datea, path, size);
        }
    }
    fclose(fp);
    return H;
}

void saveToFile(Linkedlist H, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("Can not open file.\n");
        return;
    }
    Pnode p = H;
    while (p != NULL)
    {
        fprintf(fp, "%s|%s|%s|%s|%s|%ld\n", p->data.name, p->data.datec, p->data.datem, p->data.datea, p->data.path, p->data.size);
        p = p->next;
    }
    fclose(fp);
}

void showlistName(Linkedlist H)
{
    int index = 1;
    Pnode P = H;
    while (P != NULL)
    {
        printf("%d. ", index);
        printf("%s\n--------------------\n", P->data.name);
        index++;
        P = P->next;
    }
}

void menu()
{
    printf("========================================\n");
    printf("---          PHOTO LIBRARY           ---\n");
    printf("========================================\n");
    printf("1. Add new photos\n");
    printf("2. Show the list\n");
    printf("3. Find the photo by name\n");
    printf("4. Edit the photo\n");
    printf("5. Delete the photo\n");
    printf("6. Recycle bin\n");
    printf("7. Sort\n");
    printf("0. Exit\n");
}
int main()
{
    Linkedlist H = loadFromFile("photos.txt");
    Linkedlist R = loadFromFile("Rubbish.txt");

    int choice = -1;
    char name[MAX_STRING];
    char datec[11];
    char datem[11];
    char datea[11];
    char path[MAX_STRING];
    char path1[MAX_STRING];
    long size;

    while (choice != 0)
    {
        setColor(11);
        printf("========================================\n");
        printf("---     \033[1;36m📸    PHOTO LIBRARY\033[0m           ---\n");
        printf("========================================\n");

        setColor(14);
        printf("1.");
        setColor(15);
        printf(" \033[1;32m➕ Add new photos\033[0m\n");

        setColor(14);
        printf("2.");
        setColor(15);
        printf(" \033[1;34m📂 Show the list\033[0m\n");

        setColor(14);
        printf("3.");
        setColor(15);
        printf(" \033[1;33m🔍 Find the photo by name\033[0m\n");

        setColor(14);
        printf("4.");
        setColor(15);
        printf(" \033[1;35m✏️  Edit the photo\033[0m\n");

        setColor(14);
        printf("5.");
        setColor(15);
        printf(" \033[1;31m❌ Delete the photo\033[0m\n");

        setColor(14);
        printf("6.");
        setColor(15);
        printf(" \033[1;36m🗑️  Recycle bin\033[0m\n");

        setColor(14);
        printf("7.");
        setColor(15);
        printf(" \033[1;35m🔃 Sort\033[0m\n");

        setColor(14);
        printf("0.");
        setColor(15);
        printf(" \033[1;31m🚪 Exit\033[0m\n");

        setColor(10);
        printf("\n\033[1;33m👉 Choose:\033[0m ");
        setColor(15);
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {

        case 1:
            setColor(10);
            printf("\n==> ➕ ADD NEW PHOTO\n\n");
            setColor(15);
            while (1)
            {
                printf("Enter photo path: ");
                gets(path1);
                path1[strcspn(path1, "\n")] = '\0';

                FILE *fp1 = fopen(path1, "rb");
                if (!fp1)
                {
                    printf("Can not open file. Try again!\n");
                    fclose(fp1);
                }
                else if (isSame(H, path1) == 1)
                {
                    printf("This photo is existed. Try again!\n");
                }

                else if (isSame(H, path1) != 1)
                    break;
            }
            getFileInfo(path1, name, datec, datem, datea, &size);
            while (1)
            {
                if (isSameName(H, name) == 1)
                {
                    printf("This name was exited. Try again!\n");
                    printf("Enter a new name:");
                    gets(name);
                }
                else
                    break;
            }
            H = addNode(H, name, datec, datem, datea, path1, size);
            saveToFile(H, "photos.txt");
            printf("----------PHOTOS LIST----------\n");
            showlist(H);
            break;
        case 2:
            setColor(11);
            printf("\n==> 📂 PHOTO LIST\n\n");
            setColor(15);
            showlist(H);
            break;
        case 3:
            setColor(13);
            printf("\n==> 🔍 FIND PHOTO\n\n");
            setColor(15);
            printf("Enter the name of finding photo: ");
            gets(name);
            showlist(findName(H, name));
            break;
        case 4:
            setColor(14);
            printf("\n==> ✏️  EDIT PHOTO\n\n");
            setColor(15);
            {
                showlistName(H);
                printf("Select the serial number corresponding to the name you want to edit (0 to back): ");
                int select;
                int base = 1;
                scanf("%d", &select);
                Pnode P = H;
                if (select == 0)
                    break;
                else
                {
                    while (P != NULL && base != select)
                    {
                        P = P->next;
                        base++;
                    }
                    editPhoto(H, P->data.name);
                    saveToFile(H, "photos.txt");
                    break;
                }
            }
        case 5:
            setColor(12);
            printf("\n==> ❌ DELETE PHOTO\n\n");
            setColor(15);
            {
                showlistName(H);
                printf("Select the serial number corresponding to the name you want to delete (0 to back): ");
                int select;
                int base = 1;
                scanf("%d", &select);
                Pnode C = H;
                if (select == 0)
                    break;
                else
                {
                    while (C != NULL && base != select)
                    {
                        C = C->next;
                        base++;
                    }
                    R = addNode(R, C->data.name, C->data.datec, C->data.datec, C->data.datea, C->data.path, C->data.size);
                    H = delete(H, C->data.name);
                    printf("Deleted Successfully!\n");
                    saveToFile(R, "Rubbish.txt");
                    saveToFile(H, "photos.txt");
                    break;
                }
            }
        case 6:
            setColor(9);
            printf("\n==> 🗑️  RECYCLE BIN\n\n");
            setColor(15);
            {
                R = loadFromFile("Rubbish.txt");
                showRubbishlist(R);
                int choice_rub = -1;
                while (choice_rub != 0)
                {
                    setColor(14);
                    printf("\n1.");
                    setColor(15);
                    printf(" \U0001F5C4 Restore");

                    setColor(14);
                    printf("\n2.");
                    setColor(15);
                    printf(" ❌ Permanently Delete");

                    setColor(14);
                    printf("\n0.");
                    setColor(15);
                    printf(" \U0001F519 Back");

                    setColor(14);
                    printf("\n\U0001F53D Choice: ");
                    setColor(15);

                    scanf("%d", &choice_rub);

                    switch (choice_rub)
                    {
                    case 1:
                    {
                        int base = 1, select;
                        Pnode P = R;

                        if (R == NULL)
                        {
                            printf("The recycle bin is empty!\n");
                            break;
                        }

                        showlistName(R);
                        printf("Select the serial number corresponding to the name you want to restore (0 to back): ");
                        scanf("%d", &select);

                        if (select == 0)
                            break;

                        while (P != NULL && base < select)
                        {
                            P = P->next;
                            base++;
                        }

                        if (P == NULL)
                        {
                            printf("⚠️ Invalid selection. Please try again.\n");
                            break;
                        }

                        if (isSame(H, P->data.path) == 1)
                        {
                            printf("This file already exists in your main list. Try again!\n");
                        }
                        else
                        {
                            H = addNode(H, P->data.name, P->data.datec, P->data.datem, P->data.datea, P->data.path, P->data.size);
                            R = delete(R, P->data.name);

                            printf("Restore Completed!\n--------------------\n");
                            saveToFile(R, "Rubbish.txt");
                            saveToFile(H, "photos.txt");
                            choice_rub = 0;
                        }
                        break;
                    }

                    case 2:
                    {
                        int base = 1;
                        Pnode P = R;

                        if (R == NULL)
                        {
                            printf("The recycle bin is empty! Nothing to delete.\n");
                            break;
                        }

                        showlistName(R);
                        int select;
                        printf("Select the serial number corresponding to the name you want to delete permanently (0 to back): ");
                        scanf("%d", &select);

                        if (select == 0)
                            break;
                        while (P != NULL && base < select)
                        {
                            P = P->next;
                            base++;
                        }

                        if (P == NULL)
                        {
                            printf("⚠️ Invalid selection. Please enter a valid serial number.\n");
                            break;
                        }
                        R = delete(R, P->data.name);
                        printf("Permanent Deletion Completed!\n--------------------\n");

                        saveToFile(R, "Rubbish.txt");

                        choice_rub = 0;
                        break;
                    }
                    case 0:
                        printf("Returning to the main menu...\n--------------------\n");
                        break;
                    }
                }
            }
            break;
        case 7:
            setColor(14);
            printf("\n==> 🔃 SORT OPTIONS\n\n");
            setColor(15);
            {
                int sort = -1;
                while (sort != 6)
                {
                    setColor(14);
                    printf("1.");
                    setColor(15);
                    printf(" 📛 Name\n");
                    setColor(14);
                    printf("2.");
                    setColor(15);
                    printf(" 📅 Creation Date\n");
                    setColor(14);
                    printf("3.");
                    setColor(15);
                    printf(" 🛠️ Modification Date\n");
                    setColor(14);
                    printf("4.");
                    setColor(15);
                    printf(" 🕒 Access Date\n");
                    setColor(14);
                    printf("5.");
                    setColor(15);
                    printf(" 📦 Size\n");
                    setColor(14);
                    printf("0.");
                    setColor(15);
                    printf(" 🔙 Back\n");
                    printf("\n🔽 Choice: ");
                    scanf("%d", &sort);

                    switch (sort)
                    {
                    case 1:
                    {
                        int mode;
                        printf("\n1.⬆️ A-Z");
                        printf("\n2.⬇️ Z-A");
                        printf("\n0.🔙 Back");
                        printf("\n👉 Choose: ");
                        scanf("%d", &mode);

                        if (mode == 0)
                            break;
                        else if (mode == 1)
                            printf("🔤 Sort by name from A to Z\n");
                        else if (mode == 2)
                            printf("🔤 Sort by name from Z to A\n");
                        H = sortingName(H, mode);
                        showlist(H);
                        break;
                    }
                    case 2:
                    {
                        int modec;
                        setColor(14);
                        printf("1.");
                        setColor(15);
                        printf(" ⬆️ Ascending\n");
                        setColor(14);
                        printf("2.");
                        setColor(15);
                        printf(" ⬇️ Descending\n");
                        setColor(14);
                        printf("0.");
                        setColor(15);
                        printf(" 🔙 Back");

                        printf("\n👉 Choose: ");
                        scanf("%d", &modec);

                        if (modec == 0)
                            break;
                        else if (modec == 1)
                            printf("📅 Sort by date of creation in ascending order.\n");
                        else if (modec == 2)
                            printf("🛠️ Sort by date of creation in descending order.\n");
                        H = sortListByDate(H, modec, 1);
                        showlist(H);
                        break;
                    }
                    case 3:
                    {
                        int modem;
                        setColor(14);
                        printf("1.");
                        setColor(15);
                        printf(" ⬆️ Ascending\n");
                        setColor(14);
                        printf("2.");
                        setColor(15);
                        printf(" 🔽 Descending\n");
                        setColor(14);
                        printf("0.");
                        setColor(15);
                        printf(" 🔙 Back");
                        printf("\n👉 Choose: ");
                        scanf("%d", &modem);

                        if (modem == 0)
                            break;
                        else if (modem == 1)
                            printf("🛠️ Sort by date of modification in ascending order.\n");
                        else if (modem == 2)
                            printf("🛠️ Sort by date of modification in descending order.\n");
                        H = sortListByDate(H, modem, 1);
                        showlist(H);
                        break;
                    }
                    case 4:
                    {
                        int modea;
                        setColor(14);
                        printf("1.");
                        setColor(15);
                        printf(" ⬆️ Ascending\n");
                        setColor(14);
                        printf("2.");
                        setColor(15);
                        printf(" 🔽 Descending\n");
                        setColor(14);
                        printf("0.");
                        setColor(15);
                        printf(" 🔙 Back");
                        printf("\n👉 Choose: ");
                        scanf("%d", &modea);

                        if (modea == 0)
                            break;
                        else if (modea == 1)
                            printf("🕒 Sort by date of access in ascending order.\n");
                        else if (modea == 2)
                            printf("🕒 Sort by date of creation in descending order.\n");
                        H = sortListByDate(H, modea, 1);
                        showlist(H);
                        break;
                    }
                    case 5:
                    {
                        int modes;
                        setColor(14);
                        printf("1.");
                        setColor(15);
                        printf(" ⬆️ Ascending\n");
                        setColor(14);
                        printf("2.");
                        setColor(15);
                        printf(" 🔽 Descending\n");
                        setColor(14);
                        printf("0.");
                        setColor(15);
                        printf(" 🔙 Back");

                        printf("\n👉 Choose: ");
                        scanf("%d", &modes);

                        if (modes == 0)
                            break;
                        else if (modes == 1)
                            printf("⬆️📦Sort by size in ascending order.\n");
                        else if (modes == 2)
                            printf("⬇️📦Sort by size in descending order.\n");
                        H = sortingSize(H, modes);
                        showlist(H);
                        break;
                    }
                    case 0:
                        setColor(2);
                        printf("\n==> 🚪 EXITING...\n");
                        setColor(15);
                        break;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}