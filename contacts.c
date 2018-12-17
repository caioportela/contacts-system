#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <conio.h>

struct {
  long phone;
  char name[20], email[30];
} list;

FILE *fp, *ft;

int main() {
  int menu, found;
  
  main:
  /*------------------------------- Main Menu -------------------------------*/
  system("cls");
  printf("\n\t ****** Contact Management System ******");
  printf("\n\n\n\t\t\t MAIN MENU");
  printf("\n\t\t=========================");
  printf("\n\t\t[1] Add a new contact");
  printf("\n\t\t[2] List all contacts");
  printf("\n\t\t[3] Search for contact");
  printf("\n\t\t[4] Edit a contact");
  printf("\n\t\t[5] Delete a contact");
  printf("\n\t\t[0] Exit");
  printf("\n\t\t=========================");
  printf("\n\t\tEnter the choice: ");
  scanf("%d", &menu);

  switch(menu) {
    case 1:
      /*------------------------- Add new contacts --------------------------*/
      system("cls");
      fp = fopen("contact.dll", "a");

      printf("Name: ");
      scanf(" %[^\n]", &list.name);

      printf("Phone: ");
      scanf(" %ld", &list.phone);

      printf("Email: ");
      scanf(" %s", &list.email);

      fwrite(&list, sizeof(list), 1, fp);
      
      fclose(fp);
      break;

    case 2:
      /*--------------------------- List contacts ---------------------------*/
      system("cls");
      printf("\n\t\t========================");
      printf("\n\t\t\tCONTACTS");
      printf("\n\t\t========================");
      printf("\n\nName\t\tPhone\t\tEmail");
      printf("\n==============================================================\n\n");

      for(int i = 97; i <= 122; i++) {
        fp = fopen("contact.dll", "r");
        
        found = 0;
        while(fread(&list, sizeof(list), 1, fp) == 1) {
          if(list.name[0] == i || list.name[0] == i-32) {
            printf("\n%s\t%ld\t%s\n", list.name, list.phone, list.email);
            found++;
          }
        }

        if(found != 0) {
          printf("======================================================== %c (%d) \n\n", i-32, found);
          getch();
        }
      
      fclose(fp);
      }

      break;

    case 3:
      /*-------------------------- Search contacts --------------------------*/
      do {
        system("cls");
        char query[20], name[20];

        printf("\n\n\t\tCONTACT SEARCH");
        printf("\n\t===========================");
        printf("\n\tFind contact: ");
        scanf(" %[^\n]", &query);

        int l = strlen(query);
        fp = fopen("contact.dll", "r");

        system("cls");
        printf("\n\n..::Search results for '%s'", query);
        printf("\n\nName\t\tPhone\t\tEmail");
        printf("\n==============================================================\n");

        found = 0;
        while(fread(&list, sizeof(list), 1, fp) == 1) {
          for(int i = 0; i <= l; i++)
            name[i] = list.name[i];

          name[l] = '\0';

          if(stricmp(name, query) == 0) {
            printf("\n%s\t%ld\t%s\n", list.name, list.phone, list.email);
            found++;
          }
        }

        if(found == 0)
          printf("\n..::No match found!");
        else {
          printf("\n==============================================================\n");
          printf("\n..::%d match(s) found!", found);
        }

        fclose(fp);

        printf("\n..::Try again?");
        printf("\n\n\t[1] Yes\t\t[0] No\n");
        scanf("%d", &menu);
      } while(menu == 1);

      break;
  }
  return 0;
}
