#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_YR 2024
#define MIN_YR 1900

//date
typedef struct {
  int yyyy;
  int mm;
  int dd;
} Date;

//Validate Name
int validName(char name[]) {
  int cnt = 0;
  for (int i = 0; name[i] != '\0'; i++) {
    if(isalpha(name[i])||name[i]==' ')
    {
    if (name[i] == ' ') {
      cnt++;
    }
    }
  }
  if (cnt == 2)
    return 1;
  else
  {
    printf("Enter a valid Name ");
    return 0;
  }
}

//Validate account type
int validTYP(char typ[]) {
  if (strcmp(typ, "savings") == 0 || strcmp(typ, "current") == 0 ||
      strcmp(typ, "Savings") == 0 || strcmp(typ, "Current") == 0 ||
      strcmp(typ, "C") == 0 || strcmp(typ, "S") == 0 ||
      strcmp(typ, "Salary") == 0 || strcmp(typ, "salary") == 0 ||
      strcmp(typ, "Sal") == 0)
    return 1;
  else
  {
    printf("Enter valid account type ");
    return 0;
  }
}
//Validate PAN
int isValidPAN(char PAN[]) {
  if (strlen(PAN) == 10) {
    for (int i = 0; i < 5; i++) {
      if (isalpha(PAN[i]) && isupper(PAN[i]))
        continue;
      else {
        return 0;
      }
    }
    for (int i = 5; i < 9; i++) {
      if (isdigit(PAN[i]))
        continue;
      else {
        return 0;
      }
    }
    if (isupper(PAN[9]))
      return 1;
    else
    {
      printf("Enter valid PAN ");
      return 0;
    }

  } else
  {  printf("Enter valid PAN ");
    return 0;
  }
}

//Validate AADHAR
int isValidAadhar(char Aadhar[]) {
  if (strlen(Aadhar) == 12) {
    for (int i = 0; i < strlen(Aadhar); i++) {
      if (!isdigit(Aadhar[i])) {
        return 0;
      }
    }
    return 1;
  }
  return 0;
}
//Validate date
int IsLeapYear(int year) {
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate) {
  // check range of year,month and day
  if (validDate->yyyy > MAX_YR || validDate->yyyy < MIN_YR)
    return 0;
  if (validDate->mm < 1 || validDate->mm > 12)
    return 0;
  if (validDate->dd < 1 || validDate->dd > 31)
    return 0;
  // Handle feb days in leap year
  if (validDate->mm == 2) {
    if (IsLeapYear(validDate->yyyy))
      return (validDate->dd <= 29);
    else
      return (validDate->dd <= 28);
  }
  // handle months which has only 30 days
  if (validDate->mm == 4 || validDate->mm == 6 || validDate->mm == 9 ||
      validDate->mm == 11)
    return (validDate->dd <= 30);
  return 1;
}