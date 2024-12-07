/******************
Name: Thomas Kowalski
ID: *********
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

#define INIT_VALUE -1

int isDayDone(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void clearBuffer();
int isBrandSet(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int localDay);
int getDelta(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndex, int firstDay, int secDay);

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

int day = 0;

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    
    // initialize
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int k = 0; k < NUM_OF_TYPES; k++) {
                cube[i][j][k] = INIT_VALUE;
            }
        }
    }

    int choice;
    int brandInput;
    int dayInput;
    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            
            case addOne:
                // brand input
                printf("What brand?\n");
                scanf("%d", &brandInput);
                if (brandInput < 0 || brandInput >= NUM_OF_BRANDS) {
                    printf("This brand is not valid\n");
                    break;
                }
                // scans sales into the cube
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    scanf("%d", &cube[day][brandInput][i]);
                }
                break;

            case addAll:
                
                // check if day is done
                if (isDayDone(cube)) {
                    day++;
                }
                else {
                // if not:
                    while (!(isDayDone(cube))) { // while the day is not done:
                        printf("No data for brands ");
                        
                        for (int i = 0; i < NUM_OF_BRANDS; i++) { // checks which brands are not filled
                            int missFlag = 0; // print brands name once (will 'switch' after the first print)
                            for (int j = 0; j < NUM_OF_TYPES; j++) {
                                if (cube[day][i][j] <= INIT_VALUE) {
                                    if (missFlag == 0) {
                                        printf("%s ", brands[i]); // brand i is missing data
                                    }
                                }
                                missFlag = 1;
                            }
                        }
                        printf("\n");
                        printf("Please complete the data\n");

                        // input brand
                        scanf("%d", &brandInput);

                        if (brandInput < 0 || brandInput >= NUM_OF_BRANDS || isBrandSet(cube, brandInput, day)) {
                            printf("This brand is not valid\n");
                            clearBuffer();
                            continue;
                        }
                        for (int i = 0; i < NUM_OF_TYPES; i++) {
                            scanf("%d", &cube[day][brandInput][i]);
                        }

                        
                    }
                    day++; // day is done!
                }
                break;

            case stats:
                // input loop
                int isValid = 1;
                do {
                    if (isValid == 0) {
                        printf("Please enter a valid day.\n");
                    }
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &dayInput);
                    isValid = 0;
                } while (!(dayInput <= day && dayInput > 0));
                printf("In day number %d:\n", dayInput);
                dayInput--; // converts from human days to index

                // total sales sum
                int salesSum = 0;
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        salesSum += cube[dayInput][i][j];
                    }
                }

                printf("The sales total was %d\n", salesSum);
                
                // most sold brand
                int mostSoldIndex;
                int mostSoldSum = 0;
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    salesSum = 0;
                    for (int j = 0; j < NUM_OF_TYPES; j++) {
                        salesSum += cube[dayInput][i][j];
                    }
                    if (salesSum > mostSoldSum) {
                        mostSoldSum = salesSum;
                        mostSoldIndex = i;
                    }
                }

                printf("The best sold brand with %d sales was %s\n", mostSoldSum, brands[mostSoldIndex]);

                // most sold car type
                mostSoldSum = 0;
                for (int i = 0; i < NUM_OF_TYPES; i++) {
                    salesSum = 0;
                    for(int j = 0; j < NUM_OF_BRANDS; j++) {
                    salesSum += cube[dayInput][j][i];
                    }
                    if (salesSum > mostSoldSum) {
                        mostSoldSum = salesSum;
                        mostSoldIndex = i;
                    }
                }
                printf("The best sold type with %d sales was %s\n", mostSoldSum, types[mostSoldIndex]);

                break;
            
            case print:
                printf("*****************************************\n\n");
                for (int i = 0; i < NUM_OF_BRANDS; i++) { // i = current brand
                    printf("Sales for %s:\n", brands[i]);

                    for (int j = 0; j < day; j++) { // j = current day

                        printf("Day %d- ", j + 1); //index starts at 0 so +1 for human day
                        for (int k = 0; k < NUM_OF_TYPES; k++) { // k = current type
                            printf("%s: %d ", types[k], cube[j][i][k]);
                        }
                        printf("\n");
                    }
                }
                printf("\n*****************************************\n");
                break;

            case insights:
                //best brand
                mostSoldSum = 0;
                for (int curBrand = 0; curBrand < NUM_OF_BRANDS; curBrand++) {
                salesSum = 0;
                    for (int curDay = 0; curDay < day; curDay++) {
                        for (int curType = 0; curType < NUM_OF_TYPES; curType++) {
                            salesSum += cube[curDay][curBrand][curType];
                        }
                    }
                    if (salesSum > mostSoldSum) {
                        mostSoldIndex = curBrand;
                        mostSoldSum = salesSum;
                    }
                }
                printf("The best-selling brand overall is %s: %d$\n", brands[mostSoldIndex], mostSoldSum);

                //best type
                mostSoldSum = 0;
                for (int curType = 0; curType < NUM_OF_TYPES; curType++) {
                salesSum = 0;
                    for (int curDay = 0; curDay < day; curDay++) {
                        for (int curBrand = 0; curBrand < NUM_OF_BRANDS; curBrand++) {
                            salesSum += cube[curDay][curBrand][curType];
                        }
                    }
                    if (salesSum > mostSoldSum) {
                        mostSoldIndex = curType;
                        mostSoldSum = salesSum;
                    }
                }
                printf("The best-selling type of car is %s: %d$\n", types[mostSoldIndex], mostSoldSum);

                //best day
                int mostSoldDay;
                mostSoldSum = 0;
                for (int curDay = 0; curDay < day; curDay++) {
                salesSum = 0;
                    for (int curBrand = 0; curBrand < NUM_OF_BRANDS; curBrand++) {
                        for (int curType = 0; curType < NUM_OF_TYPES; curType++) {
                            salesSum += cube[curDay][curBrand][curType];
                        }
                    }
                    if (salesSum > mostSoldSum) {
                        mostSoldDay = curDay;
                        mostSoldSum = salesSum;
                    }
                }
                printf("The most profitable day was day number %d: %d$\n", mostSoldDay+1, mostSoldSum);
                break;
            
            case deltas:
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    int numeratorSum = 0;
                    int denominator = day - 1; // according to the formula...
                    for (int curDay = 0; curDay < day-1; curDay++) { // no need to check the last day (no days after it)
                        if (isBrandSet(cube, i, curDay+1)) { // if the next day has data
                            numeratorSum += getDelta(cube, i, curDay, curDay+1);
                        }
                    }

                    float averageDelta = (float)numeratorSum / (float)denominator;
                    printf("Brand: %s, Average Delta: %f\n", brands[i], averageDelta);
                }
                
                break;
            
            
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


int isDayDone(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) { // func that checks if the current day is done
    int isDataFilled = 1;

    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            if (arr[day][i][j] <= INIT_VALUE){
                isDataFilled = 0;
            }
        }
    }   
    return isDataFilled;
}

void clearBuffer() { // it clears the buffer...
    scanf("%*[^\n]");
}

// checks if the brand is set in a selected day
int isBrandSet(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int localDay) { 
    int flag = 1;
        for (int i = 0; i < NUM_OF_TYPES; i++) {
            if (arr[localDay][brand][i] <= INIT_VALUE) {
                flag = 0;
            }
        }
    return flag;
}

// gets the delta from a brand sales between two following days
int getDelta(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brandIndex, int firstDay, int secDay) {
    int sum = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        sum += arr[firstDay][brandIndex][i];
    }
    int firstSum = sum;
    
    sum = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        sum += arr[secDay][brandIndex][i];
    }
    int secSum = sum;
    return secSum - firstSum;
}