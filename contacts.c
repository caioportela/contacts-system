#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>

struct {
  long phone;
  char name[20], email[30];
} list;

FILE *fp, *ft;

int main() {
  int menu; 
  
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
      scanf("%ld", &list.phone);

      printf("Email: ");
      scanf(" %s", &list.email);

      fwrite(&list, sizeof(list), 1, fp);
      
      fclose(fp);
      break;
  }
  
    case 2:
      /*--------------------------- List contacts ---------------------------*/
      system("cls");
      printf("\n\t\t========================");
      printf("\n\t\t\tCONTACTS");
      printf("\n\t\t========================");
      printf("\n\nName\t\tPhone\t   Email");
      printf("\n===================================================\n\n");

      for(int i = 97; i <= 122; i++) {
        fp = fopen("contact.dll", "r");
        
        found = 0;
        while(fread(&list, sizeof(list), 1, fp) == 1) {
          if(list.name[0] == i || list.name[0] == i-32) {
            printf("\nName\t: %s\nPhone\t: %ld\nEmail\t: %s\n", list.name, list.phone, list.email);
            found++;
          }
        }

        if(found != 0) {
          printf("========================================= [%c] - (%d) \n\n", i-32, found);
          getch();
        }
      
      fclose(fp);
      }

      break;
  }  
  return 0;
}
