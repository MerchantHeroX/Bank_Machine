/*
 * File:   main.c
 * Author: mobiuszwie
 *
 * Created on December 11, 2017, 10:14 PM
 * Gave myself 2 week deadline. Only work on it mon-fri. work 40hrs that is not a
 * computing job.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/*
 * This is the attempt to make a fully functioing c program according to school assignment
* that isnt even mine.
 
 * Issues that I have discovered so far.
 * There are repeat sections that could be fixed.
 *
 * certain points values of "This action done" need to be written in
 */

struct AccInfo {
    double balance;
    char name[20];
    char account[9];
    char pin[5];
    
    struct AccInfo *next;
};

//make these here so they apply globaly
struct AccInfo *head = NULL;
struct AccInfo *current = NULL;

// Could organize these better.
void UserBankMenu();
int validatePin();
int validateRange (int start, int end);
void fastCase();
void customerEventHandler(int event);
void printlist();
void printlistAbove(double amount);
int length();
void insertAcc(char account[], double balance, char name[], char pin[]);
int printBankMenu();
void bankEventHandler(int event);
void searchByName(char name[20]);
void searchAcc( int num);
int searchByAccount(char account[], int UserType);
void DeleteAcc(int num);
void DeleteByName(char name[20]);
void Sorting(int num);
void SortbyName();
void SortByAccount();
void SortByBalance();
int CustomerMenu();
void printBalance();
void withDrawFunc();
void DepsoitFunc();
int searchlistAbove(double amount);

char * validateInput( int reqLenOFInput);
int lenOfInput( char input[] );


int main(int argc, char** argv) {
    //double amount;
    int event = -1;
    
    // made these for testing purposes
    // now to test without inputs
    /*
    insertAcc("1234", 153, "Somthing O'Ruther", "2342");
    insertAcc("2134", 105, "James Rejek", "1234");
    insertAcc("5351", 98, "Tom Afool", "4283");
    insertAcc("6531", 109,"Sam Green", "2983");
     * */
    
    
    while ( event != 3) {
        
        UserBankMenu();
        event = validateRange(1,3);
        
        switch ( event) {
            case 1:
                 do {   
                     //prints options for banker
                    event =  printBankMenu();
    
                    //handles all the transactions needed on accounts
                     bankEventHandler(event);
    
                     } while (event != 7);
                    break;
                    
            case 2:
            // 0 is false 1 is true - try to keep this pattern
                // this requires them to enter a proper account and pin number before going on
                    if ( validatePin() == 0) {
                        event = 5;
                    }
                    
                    // here is the loop for them to work inside the account
                    while ( event != 5) {
                        event = CustomerMenu();
                        
                        customerEventHandler(event);
                    }
                    break;
                    
            default:
                    break;
        }
    }
    
    printf("Thank you for Using this program\n");
    printf("\t\t-Merchant Hero X\n");


    
    return (EXIT_SUCCESS);
}

int validateRange(int start, int end) {
    // this will only work for input of lenght 1 and
    // used between numbers 0 - 9
 
    int answer;
    char *answerChar = (char *) malloc(64);
    
   scanf("%s", answerChar);
 
    answer =  answerChar[0] - 48;
    
    while ( lenOfInput(answerChar) != 1 ||answer < start || answer > end) {
        printf("Invalid Selection\n");
         scanf("%s", answerChar);
        answer = answerChar[0] - 48;
    }
    
    return answer;
    
}
void UserBankMenu() {
    printf("Accessing\n");
    printf("\n");
    printf("Welcome to BankMachine v0.20\n");
    printf("How would you like to proceed?\n");
    printf("\t1 - Banker\n");
    printf("\t2 - Account Holder\n");
    printf("\t3 - Exit Program\n");
    
}

int validatePin() {
    char pinNum[5];
    int len = 0;
    char AccNum[9];
    int answer = 0;
    int NumAttempts = 0;
    char PinNumber[5];
    
    printf("Our Card Reader is currently out of service\n");
    
    do {
    printf("Please Enter account number\n");
    scanf("%9s", AccNum);
    answer = searchByAccount( AccNum, 1);
    NumAttempts++;
    if ( NumAttempts >= 3) {
        printf("Too many Failed attempts - Exiting\n");
        return 0;
    }
    } while ( answer != 1);
   
    
    NumAttempts = 0;
    
    while ( strcmp(current->pin, pinNum) != 0) {
    printf("Please Enter pin number\n");
    strcpy(pinNum , validateInput(4));
 
    if ( strcmp(pinNum,current->pin) != 0) {
        printf("\tInvalid Pin\n");
        NumAttempts++;
    }
 /*
        NumAttempts++;
      while ( cpyPinNum != 0) {
        len++;
        cpyPinNum /= 10;
    }
    */
    if ( NumAttempts >= 3) {
        printf("Too many failed attempts - Exiting\n");
        return 0;
    };
    }
   
    return 1;
}

char * validateInput( int reqLenOFInput) {
    
    char *word = (char*) malloc(255);
    
    scanf("%9s", word);
    
    int len = lenOfInput(word);
    int i;
    
    
        while ( lenOfInput(word) != reqLenOFInput) {
            printf("\tInvalid Input\n");
            scanf("%9s", word);
        
             for (i = 0; i < reqLenOFInput; i++) {
                if ( isdigit(word[i]) == 0) {
                strcpy( word , "inval");
                 }
    }
    }
        
  return word;  
}

int lenOfInput( char input[] ) {
    
    int len = 0;
    int i = 0;
    
    while ( input[i] != '\0') {
        len++;
        i++;
    }
    
    return len;
}

int CustomerMenu() {
    int answer;
    
    printf("Welcome Customer\n");
    printf("\n");
    printf("What would you like to do?\n");
    printf("\t1 - Fast Cash\n");
    printf("\t2 - WithDraw\n");
    printf("\t3 - Deposit\n");
    printf("\t4 - Balance\n");
    printf("\t5 - Get Card Back\n");
    printf("\n");
    answer = validateRange(1,5);
    
    return answer;
}

void DepsoitFunc() {
    double amount;
    printf("How much would you like to Despoit?\n");
    scanf("%lf", &amount);
    
    current->balance += amount;
    
}
void withDrawFunc() {
    double amount;
    printf("How much would you like to withdraw : \n");
    scanf("%lf", &amount);
    
    if ( current->balance > amount) {
        current->balance -= amount;
    } else {
        printf("Insufficient funds for Transaction\n");
    }
}

void customerEventHandler(int event) {
    
    switch( event) {
        case 1:
            fastCash();
            break;
        case 2:
            //WithDraw
            withDrawFunc();
            break;
        case 3:
            DepsoitFunc();
            //deposit;
            break;
        case 4:
            //print out balance
            printBalance();
            break;
        case 5:
            //end
            break;
        default:
            printf("This shouldnt ever appear\n");
    }
    
}

void fastCash() {
    int answer;
    double amount[] = { 20 , 40, 60 , 80 };
    
    printf("How much would you like to remove?\n");
    printf("\t1 - $20.00 \t3 - $60.00\n");
    printf("\t2 - $40.00 \t4 - $80.00\n");
    printf("\n");
    answer = validateRange(1,4);
    int IndexNum = answer -1;
    
    if ( current->balance > amount[IndexNum] ) {
        current->balance -= amount[IndexNum];
    } else {
        printf("You do not have sufficient funds\n");
    }
    
}

void printBalance() {
    printf("Your Current Balance is : %.2lf\n", current->balance);
    
}
void bankEventHandler(int event) {
    double amount;
    char account[9] ;
    double balance;
    char first[20];
    char last[20];
    int answer;
    char pin[5];
            
    switch (event) {
        case 1:
            // make a list
            printlist();
            break;
        case 2:
            // make a list with only a certain amount above
            printf("How much are you looking for minimum?\n");
            scanf("%lf", &amount);
            printlistAbove(amount);
            break;
        case 3:
            // search for customer
            printf("How would you like to look for customer?\n");
            printf("\t 1 - By Name\n");
            printf("\t 2 - By Account Number\n");
            answer = validateRange(1,2);
            searchAcc(answer);
            break;
        case 4:
            //sort list by name, account, balance
            printf("How would you like to Sort?\n");
            printf("\t 1 - By Name\n");
            printf("\t 2 - By Account\n");
            printf("\t 3 - By Balance\n");
            answer = validateRange(1,3);
            Sorting(answer);
            break;
        case 5:
            //delete a customer
            printf("How would you like to delete account?\n");
            printf("\t 1 - By Name\n");
            printf("\t 2 - By Account\n");
            answer = validateRange(1,2);
            DeleteAcc(answer);
            break;
        case 6:
            //create an account
            printf("What is the First name of the account?\n");
            scanf("%s", first);
            printf("What is the last name of the account?\n");
            scanf("%s", last);
            printf("What is the Account number? [8 digit number]\n");
            do {
            strcpy(account, validateInput(8));
            } while ( searchByAccount(account, 3) == 1);
            
            printf("What is the current balance?\n");
            scanf("%lf", &balance);
            printf("What would you like the four digit pin to be?\n");
            strcpy(pin, validateInput(4));
            
            //concate first and second
            strcat(first, " ");
            strcat(first, last);
            
            insertAcc(account, balance, first, pin);
            break;
        case 7:
            // exit "app"
            break;
        default:
            printf("ERROR With Process\n");
            break;
    }
}


int printBankMenu() {
    int answer;
    
    printf("\t Welcome Employee\n");
    printf("\n");
    printf("What would you like to do?\n");
    printf("\n");
    printf("\t 1 - Display Customers\n");
    printf("\t 2 - Display Customers over a Certain Amount\n");
    printf("\t 3 - Look up Customer\n");
    printf("\t 4 - Sort Customers\n");
    printf("\t 5 - Delete An Account\n");
    printf("\t 6 - Open a new Account\n");
    printf("\t 7 - End Process\n");
    
    answer = validateRange(1,7);
    
    return answer;
}

void DeleteByName(char name[]) {
    struct AccInfo *current = head;
    struct AccInfo *previous = NULL;
    
    if ( head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    while ( strcmp(current->name,name) != 0 ) {
        if ( current->next == NULL) {
        printf("Account for %s not found\n", name);//this ends it if its alreay empty
        return;//this ends it if its alreay empty
        } else {
            // store reference to current link
            previous = current;
            //then move to next link
            current = current->next;
        }
    }
    
    if ( current == head) {
        //change the first to point to next link
        head = head->next;
    } else {
        //bypass curretn link
        previous->next = current->next;
    }
      printf("Account was removed\n");
}
        

void DeleteByAccount(char accNum[]) {
    struct AccInfo *current = head;
    struct AccInfo *previous = NULL;
    
    if ( head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    while ( strcmp(current->account, accNum) != 0) {
        if ( current->next == NULL) {
            printf("Account number %s not found\n", accNum);//this ends it if its alreay empty
        return;
        } else {
            // store reference to current link
            previous = current;
            //then move to next link
            current = current->next;
        }
    }
    
    if ( current == head) {
        //change the first to point to next link
        head = head->next;
    } else {
        //bypass curretn link
        previous->next = current->next;
    }
    
    printf("Account was removed\n");
}
    

void printlist() {
    struct AccInfo *ptr = head;
    
    if ( ptr == NULL) {
        printf("There is no one on the record\n");
        return;
    }
   

    printf("Acount :\tBalance:\tName: \n");
    while ( ptr != NULL) {
        printf("%s   \t", ptr->account);
        printf("%.2lf \t", ptr->balance);
        if ( ptr->balance < 1000) {
            printf("\t");
        }
        printf("%s   \n", ptr->name);
        ptr = ptr->next;
    }
}

void DeleteAcc(int num) {
    int number = num;
    char name[20];
    char account[9];
    

    if ( number == 1) {
        printf("What is the name that you are searching for?\n");
        getchar();
        scanf("%[^\n]", name);
        DeleteByName(name);
    }
    
    if ( number == 2) {
        printf("What is the Account number you are looking for?\n");
        scanf("%s", account);
       DeleteByAccount(account);
    }

}
void searchAcc( int num) {
    int number = num;
    char name[40];
    char account[9];
             

    if ( number == 1) {
        printf("What is the name that you are searching for?\n");
        getchar();
        scanf("%[^\n]", name);
        //scanf("%s", name);
        searchByName(name);
    }
    
    if ( number == 2) {
        printf("What is the Account number you are looking for?\n");
        scanf("%s", account);
        searchByAccount(account, 2);
    }

}

void SortByAccount() {
    int i , j, k, tempBalance;
    char tempName[20];
    char tempAccount[9];
    
    struct AccInfo *current;
    struct AccInfo *next;
    
    int size = length();
    k = size ;
    
    for (i = 0; i < size; i++, k--) {
        current = head;
        next = head->next;
        
        for ( j = 1; j < k; j++) {
            
            // all this needs to take place
            if ( strcmp(current->account, next->account) > 0) {
               strcpy(tempAccount, current->account);
                strcpy(current->account, next->account);
                strcpy(next->account, tempAccount);
                
                tempBalance = current->balance;
                current->balance = next->balance;
                next->balance = tempBalance;
                
                strcpy(tempName, current->name);
                strcpy(current->name, next->name);
                strcpy(next->name, tempName);
            }
            current = current->next;
            next = next->next;
        }
    }
}

void SortByName() {
    int i , j, k,  tempBalance;
    char tempName[20];
    char tempAccount[9];
    
    struct AccInfo *current;
    struct AccInfo *next;
    
    int size = length();
    k = size ;
    
    for (i = 0; i < size; i++, k--) {
        current = head;
        next = head->next;
        
        for ( j = 1; j < k; j++) {
            
            // all this needs to take place
            if ( strcmp(current->name, next->name) >= 0) {
                 strcpy(tempAccount, current->account);
                strcpy(current->account, next->account);
                strcpy(next->account, tempAccount);
                
                tempBalance = current->balance;
                current->balance = next->balance;
                next->balance = tempBalance;
                
                strcpy(tempName, current->name);
                strcpy(current->name, next->name);
                strcpy(next->name, tempName);
            }
            current = current->next;
            next = next->next;
        }
    }
}

void SortByBalance() {
    int i , j, k, tempBalance;
    char tempAccount[9];
    char tempName[20];
    
    struct AccInfo *current;
    struct AccInfo *next;
    
    int size = length();
    k = size ;
    
    for (i = 0; i < size; i++, k--) {
        current = head;
        next = head->next;
        
        for ( j = 1; j < k; j++) {
            
            // all this needs to take place
            if ( current->balance > next->balance) {
                strcpy(tempAccount, current->account);
                strcpy(current->account, next->account);
                strcpy(next->account, tempAccount);
                
                tempBalance = current->balance;
                current->balance = next->balance;
                next->balance = tempBalance;
                
                strcpy(tempName, current->name);
                strcpy(current->name, next->name);
                strcpy(next->name, tempName);
            }
            current = current->next;
            next = next->next;
        }
    }
}

void Sorting( int num) {
    int number = num;
    char name[20];
    
  // number = validateRange(1,3);


    if ( number == 1) {
        SortByName();
        printf("List has been sorted AlphaBetically\n");
    }
    
    if ( number == 2) {
        // account sort
        SortByAccount();
        printf("List has been sorted According to Account Number\n");
    }
    
    if ( number == 3) {
        // balance sorting
        SortByBalance();
        printf("List has been Sorted According to Balance\n");
    }

}

void searchByName(char name[40]){
   
    struct AccInfo *ptr = head;
    int dontlikeflags = 0;
    
    int i , j;
    int lenOfPtr , lenOfName;
    
    printf("\n");
    printf("Results : \n");
    
    while (ptr != NULL) {
        
   
        
    lenOfPtr = lenOfInput(ptr->name);
    lenOfName = lenOfInput(name);
    
        int count = 0;
        
        for ( i = 0; i < lenOfPtr; i++) {
                for ( j = 0; j < lenOfName; j++) {
                        if ( tolower(name[j]) == tolower(ptr->name[i+j])) {
                        count++;
                                 }
                 }            
                if ( count == lenOfName) {
                    printf("%s , %s , %.2lf \n", ptr->account, ptr->name, ptr->balance);
                    dontlikeflags = 1;
                }
        //reset count
        count = 0;
        }
   // }
     ptr = ptr->next;   
    }
        
        /*
        if (strcmp(ptr->name, name) == 0) {
            printf("%s , %s , %.2lf \n", ptr->account, ptr->name, ptr->balance);
            break;
        }
        ptr = ptr->next;
    }
    */ // this was previous attempt but only matched so far
    
    if ( dontlikeflags == 0) {
    printf("Account for customer [%s] not found.\n\n", name);
    // unneccessaryprintf("Input needs to be exact spelling\n");
    }
}

int searchByAccount(char account[], int UserType){
    struct AccInfo *ptr = head;
    // 1 - for verifying the pin for user when account is entered
    // 2 - for bank to display results of searched up accounts
    // 3 - is for strictly verifying if account already exists.
    
    // this should be broken up into different search methods
    // just using these 3 numbers for the moment . might refactor if time
    
    if ( UserType == 2) {
    printf("\n");
    printf("Result: \n");
    }
    
    while (ptr != NULL) {
        
        if ( strcmp(ptr->account, account) == 0 ) {
            if (UserType == 3) {
                printf("Account already Taken : Enter Again\n");
                return 1;
            }
            
            if ( UserType == 2) {
            printf("%s , %s , %.2lf \n", ptr->account, ptr->name, ptr->balance);
            }
            //trying this out
            if ( UserType == 1) {
                current = ptr;
            }
            return 1;
            break;
        }
        ptr = ptr->next;
    }
    if ( UserType == 2) {
    printf("Account number [%s] not found\n", account);
    }
    return 0;
}
// in order to not have to create flags and suchs
// gotta create a search function first to return to the print function
int searchlistAbove(double amount) {
    
    struct AccInfo *ptr = head;
    int isAbove = 0;
    
    if ( ptr == NULL) {
        return isAbove;
    }
    
    while ( ptr != NULL) {
        if ( ptr->balance >= amount) {
        isAbove = 1;
        }
        ptr = ptr->next;
   }
    
 return isAbove;
}
    
   

void printlistAbove(double amount) {
    struct AccInfo *ptr = head;
    // i refuse to make a flag here to display if amount is above or not
    
    if ( searchlistAbove(amount) == 0) {
        printf("No Result found that is > %.2lf \n", amount);
        return;
    } else {
        printf("Account :\tBalance: \tName: \n");
    }
    
    while ( ptr != NULL) {
        if ( ptr->balance >= amount) {
        printf("%s   \t", ptr->account);
        printf("%.2lf \t", ptr->balance);
        if ( ptr->balance < 1000) {   
        printf("\t");
        }
        printf("%s   \n", ptr->name);
        }
        ptr = ptr->next;
    }
    
    
}
int length() {
    int len = 0;
    struct AccInfo *current;
    
    for ( current = head; current != NULL; current= current->next) {
        len++;
    }
    return len;
}



void insertAcc(char account[], double balance, char name[], char pin[])  {
    // this creates a link
    struct AccInfo *current = (struct AccInfo*) malloc(sizeof(struct AccInfo));
    
    strcpy(current->account, account);
    current->balance = balance;
    strcpy(current->pin, pin);
    strcpy( current->name, name);
    
   //point to old first node
    current->next = head;
    
    head = current;
    
}
