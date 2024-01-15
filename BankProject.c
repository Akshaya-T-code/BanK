#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_YR 2024
#define MIN_YR 1900
#include "validate.h"

//Structure index
int n = 0;
//Bank Structure
struct BANKACC {

  char bname[25];
  char acc[7];
  char ifsc[9];
  char username[50];
  int age;
  char gen;
  char DOB[50];
  char address[100];
  char PAN[15];
  char typacc[20];
  char city[40];
  int Bal;
  char AAD[20];
  Date D;
} B[50];

//Generate Account Number
char *genaccno(struct BANKACC B) {
  char *acc = malloc(7 * sizeof(char));
  acc[0] = B.username[0];
  int cnt = 1;
  for (int i = 1; B.username[i] != '\0'; i++) {
    if (cnt < 3) {
      if (B.username[i] == ' ') {
        acc[cnt] = B.username[i + 1];
        cnt++;
      }
    }
  }

  for (int i = 3; i < 6; i++) {
    acc[i] = (char)('0' + (rand() % 9) + 1);
  }
  acc[6] = '\0';
  return acc;
}

//Accept details 
struct BANKACC accept() {
  // Create Account
  struct BANKACC B;
printf("\n______________________________________\n");
  do {
    printf("\nEnter the Name : ");
    fgets(B.username, 25, stdin);
  } while (validName(B.username) == 0);
  B.username[strlen(B.username) - 1] = '\0';

  do {
    printf("\n Enter the age (age>0) : ");
    scanf("%d", &B.age);
    getchar();
  } while (B.age == 0);
  
  do {
    printf("\n Enter the gender (F/M): ");
    scanf("%c", &B.gen);
  } while (B.gen != 'M' && B.gen != 'F' && B.gen != 'm' && B.gen != 'f');
  
  getchar();
  
  do {
    printf("\n Enter the Balance : ");
    scanf("%d", &B.Bal);
  } while (B.Bal <= 0);
  
  do {
    printf("\n\n Enter date in format (day/month/year): ");
    scanf("%d/%d/%d", &B.D.dd, &B.D.mm, &B.D.yyyy);
  } while (isValidDate(&B.D) == 0);
 
  strcpy(B.ifsc, "SBI0801");
 // Initialize IFSC and Bank Name
  strcpy(B.bname, "SBI");
  //copy account number
  char accno[7];
  strcpy(accno, genaccno(B));
  strcpy(B.acc, accno);
  
  getchar();
  
  do {
    printf(
        "\nEnter the type of account : (Salary(Sal)/Current(C))/Savings(S) : ");
    fgets(B.typacc, 20, stdin);
    B.typacc[strlen(B.typacc) - 1] = '\0';
  } while (validTYP(B.typacc) == 0);
  do {
    printf("\n  Enter the address : ");
    fgets(B.address, 100, stdin);
    B.address[strlen(B.address) - 1] = '\0';
  } while (B.address[0] == '\0');

  do {
    printf("\n  Enter the city : ");
    fgets(B.city, 40, stdin);
    B.city[strlen(B.city) - 1] = '\0';
  } while (B.city[0] == '\0');

  do {
    printf("\n Enter PAN number : ");
    scanf("%s", B.PAN);
  } while (isValidPAN(B.PAN) == 0);

  do {
    printf("\n Enter Aadhar Number : ");
    scanf("%s", B.AAD);
  } while (isValidAadhar(B.AAD) == 0);
  printf("\n______________________________________\n");
  getchar();

  return B;
};

//Search index of Bank Account Number
int search(struct BANKACC B[], int s, char acc[]) {
  for (int i = 0; i < s; i++) {
    if (strcmp(acc, B[i].acc) == 0)
      return i + 1;
  }
  return 0;
}

//Deposit
void deposit(struct BANKACC B[], int s) {
  struct BANKACC db;
  printf("\n__________Deposit______________\n");
  do {
    printf("Enter the Account Number : ");
    scanf("%s", db.acc);
  } while (db.acc[0] == '\0');
  int deposit;

  if (search(B, s, db.acc)) {
    printf("\nEnter the amount to deposit: ");
    scanf("%d", &deposit);
    if (deposit > 0) {
      B[search(B, s, db.acc) - 1].Bal += deposit;
      printf("\nBalance : %d", B[search(B, s, db.acc) - 1].Bal);
    } else
      printf("\nInvalid amount ");

  } else
    printf("\nInvalid Account Number ");
}
// is alpha IN validate name
//Display Details
void display(struct BANKACC *B) {
  printf("\n Account Details");
  printf("\n____________________________________");
  printf("\nName: %s \nAccount Number:  %s \nBank Name: %s \nIFSC: %s "
         "\nAddress : %s \nCity: %s \nPAN No.: %s \nAadhar No.: %s\nBalance:  %d",
         B->username, B->acc, B->bname, B->ifsc, B->address, B->city,B->PAN,B->AAD, B->Bal);
  printf("\n____________________________________");
}

//Search record by account type
void searchTYP(struct BANKACC B[], int s) {
  char typ[20];
  int flag=1;
  do {
    printf("\nEnter the type of account to search : ");
    scanf("%s", typ);
  } while (validTYP(typ) == 0);
  for (int i = 0; i < s; i++) {
    if (strcmp(typ, B[i].typacc) == 0)
    {display(&B[i]);
     flag=0;
  }
  }
  if(flag)
    printf("User not found");
}
//Search record by name
void searchBNAME(struct BANKACC B[], int s) {
  int flag = 1;
  char uname[100];
  do {
    printf("\nEnter the Name : ");
    fgets(uname, 100, stdin);
  } while (validName(uname) == 0);
  uname[strlen(uname) - 1] = '\0';
  for (int i = 0; i < s; i++) {
    if (strcmp(uname, B[i].username) == 0) {
      display(&B[i]);
      flag = 0;
    }
  }
  if (flag)
    printf("\nNo such user ");
}
//Withdraw 
void withdraw(struct BANKACC B[], int s) {
  struct BANKACC db;
  printf("\n__________Withdraw______________\n");
  do {
    printf("Enter the Account Number : ");
    scanf("%s", db.acc);
  } while (db.acc[0] == '\0');
  int withdraw;
  if (search(B, s, db.acc)) {
    printf("\nEnter the amount to withdraw: ");
    scanf("%d", &withdraw);
    if (B[search(B, s, db.acc) - 1].Bal >= withdraw) {
      B[search(B, s, db.acc) - 1].Bal -= withdraw;
      printf("\nBalance : %d", B[search(B, s, db.acc) - 1].Bal);
    } else
      printf("\nInsufficient Balance ");

  } else
    printf("\nInvalid Account Number ");
  printf("\n______________________________________\n");
}
//Balance Enquiry
void BalEnquiry(struct BANKACC B[], int s) {
  struct BANKACC db;
  printf("\n__________Mini Statement______________\n");
  do {
    printf("\nEnter the  bank Account number : ");
    scanf("%s", db.acc);
  } while (search(B, s, db.acc) == 0);
  printf("\nBalance : %d", B[search(B, s, db.acc) - 1].Bal);
  printf("\n______________________________________\n");
}

//Fund Transfer
void FundTransfer(struct BANKACC B[], int s) {
  struct BANKACC RB;
  struct BANKACC DB;
  int transfer;
  printf("\n\n _____________Fund Transfer_____________________\n");
  do {
    printf("\nEnter the sender bank Account number : ");
    scanf("%s", DB.acc);
  } while (search(B, s, DB.acc) == 0);
  do {
    printf("\nEnter the receiver bank Account number : ");
    scanf("%s", RB.acc);
  } while (search(B, s, RB.acc) == 0);
  do {
    printf("\nEnter the amount to transfer : ");
    scanf("%d", &transfer);
  } while (transfer <= 0);
  if (transfer > B[search(B, s, DB.acc) - 1].Bal) {
    printf("\n Insufficient Balance ");
  } else {
    B[search(B, s, DB.acc) - 1].Bal -= transfer;
    B[search(B, s, RB.acc) - 1].Bal += transfer;
    printf("\nSender Balance : %d", B[search(B, s, DB.acc) - 1].Bal);
    printf("\nReciever Balance : %d", B[search(B, s, RB.acc) - 1].Bal);
    printf("\nFunds Transfered ");
  }
  printf("\n______________________________________\n");
}
//Update
void update(struct BANKACC B[], int s) {
  struct BANKACC B1;
  printf("\n\n _____________Update_____________________\n");
  do {
    printf("\nEnter the bank Account number to update details: ");
    scanf("%s", B1.acc);
  } while (search(B, s, B1.acc) == 0);
  int choice;
  do {
    printf("\n1.Update Name");
    printf("\n2.Update Address");
    printf("\n3.Update DOB \n");
    printf("\nEnter Choice : ");
    scanf("%d", &choice);
    getchar();
    switch (choice) {
    case 1:
      do {
        printf("\nEnter the New Name : ");
        fgets(B1.username, 25, stdin);
        B1.username[strlen(B1.username) - 1] = '\0';
      } while (validName(B1.username) == 0);
      printf("Details Updated ");
      strcpy(B[search(B, s, B1.acc) - 1].username, B1.username);
      break;
    case 2:
      do {
        printf("\n  Enter the address : ");
        fgets(B1.address, 100, stdin);
        B1.address[strlen(B1.address) - 1] = '\0';
      } while (B1.address[0] == '\0');
      strcpy(B[search(B, s, B1.acc) - 1].address, B1.address);
      printf("Details Updated ");
      break;
    case 3:
      do {
        printf("\n\n Enter date in format (day/month/year): ");
        scanf("%d/%d/%d", &B1.D.dd, &B1.D.mm, &B1.D.yyyy);
      } while (isValidDate(&B1.D) == 0);
      B[search(B, s, B1.acc) - 1].D = B1.D;
      printf("Details Updated ");
      break;
    default:
      printf("\nInvalid Choice ");
      break;
    }
  } while (choice < 1 || choice > 3);
  printf("\n__________________________\n");
}
//Search by Account Number
void searchACC(struct BANKACC B[], int s) {
  struct BANKACC B1;
  do {
    printf("Enter the Account Number : ");
    scanf("%s", B1.acc);
  } while (search(B, s, B1.acc) == 0);
  display(&B[search(B, s, B1.acc) - 1]);
}

int main() {
  printf("\n Welcome to BANK OF INDIA \n \n");
  int choice;
  while (1) {
    printf(" \n1.Create Account \n2.Display \n3.Search "
           "\n4.Deposit \n5.Withdraw \n6.Balance Enquiry \n7.Fund Transfer "
           "\n8.Update \n9.Exit \n Enter Choice :");
    scanf("%d", &choice);
    getchar();
    switch (choice) {
    case 1:
      B[n++] = accept();
      break;
    case 2:
      if(n==0)
      {
        printf("\nNo Records Found\n");
      }
      for (int i = 0; i < n; i++) {
        display(&B[i]);
      }
      break;

    case 3:
      printf("\nSearch by \n1.type of account \n2.By user name \n3.By Account "
             "Number ");
      int ch;
      scanf("%d", &ch);
      switch (ch) {
      case 1:
        searchTYP(B, n);
        break;
      case 2:
        searchBNAME(B, n);
        break;
      case 3:
        searchACC(B, n);
        break;
      default:
        printf("\nInvalid Choice ");
        break;
      }
      break;
    case 4:
      deposit(B, n);
      break;
    case 5:
      withdraw(B, n);
      break;
    case 6:
      BalEnquiry(B, n);
      break;
    case 7:
      FundTransfer(B, n);
      break;
    case 8:
      update(B, n);
      break;
    case 9:
      exit(0);
    }
  }
}
