#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"


//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

#define BLK   "\e[0;30m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"

//Reset
#define reset "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"


void print_date(){
     time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf(GRN);
        printf("Current date and time: %d-%02d-%02d %02d:%02d:%02d\n", 
           tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
           tm.tm_hour, tm.tm_min, tm.tm_sec);
           printf(reset);

}


void sleeptracker();
void moodtracker();
void videocall();
void chat();
void userProfile();
void sdcProfile();
void meditation();
void toLowerCase(char str[]);
int cekusn(char usn[]);

typedef struct{
    int day;
    int month;
    int year;

    }dates;

    

typedef struct {
    char username[50];
    dates date;
    char yisheng[20];
    char shijian[20];
    char app[20];
}appointments;
appointments appointment[1000];

typedef struct{
    int mood;
    int year;
    int month;



}xinqingtracker;



typedef struct{
	char username[50];
	char password[50];
	char name[100];
	char date[15];
	char email[100];
}mindwell;

mindwell data;
mindwell temp;


void printMoodTrackerDescription() {
    printf("\n\n----Color coding system----\n");
    printf(RED); printf("1: Red (Very bad)\n"); printf(reset);
    printf(MAG); printf("2: Magenta (Bad)\n"); printf(reset);
    printf(GRN); printf("3: Green (Okay)\n"); printf(reset);
    printf(CYN); printf("4: Cyan (Good)\n"); printf(reset);
    printf(BLU); printf("5: Blue (Very good)\n"); printf(reset);
    printf(WHT); printf("0: White\n"); printf(reset);
    printf("---------------------------\n\n");
}


void printSleepTrackerDescription(){
    printf("\n\n----Color coding system----\n");
    printf(GRN); printf("7-9: Green (Good)\n"); printf(reset);
    printf(RED); printf("Less than 7 or more than 9: Red (Bad)\n"); printf(reset);
    printf(WHT); printf("0: White (No data)\n"); printf(reset);
    printf("---------------------------\n\n");

}


int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


void printMonthCalendar(int month, int year) {
    char* months[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Get the current date
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    int currentDay = now->tm_mday;
    int currentMonth = now->tm_mon + 1; // tm_mon is 0-indexed
    int currentYear = now->tm_year + 1900; // tm_year is years since 1900

    

    // Check for leap year
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        daysInMonth[2] = 29;
    }

    // Calculate day of week for first day of month using Zeller's Congruence
    int zellerMonth = month;
    int zellerYear = year;
    if (zellerMonth < 3) {
        zellerMonth += 12;
        zellerYear -= 1;
    }
    int k = zellerYear % 100;
    int j = zellerYear / 100;
    int f = k + k/4 + 5*j + j/4 + 13*(zellerMonth+1)/5 - 1;
    int dayOfWeek = f % 7;

    printf("\033[1;35m"); // Set the text color to magenta
    printf("====== %s %d ======\n", months[month], year);
    printf("\033[0m"); // Reset the text color

    // Print the days of the week
    for (int i = 0; i < 7; i++) {
        printf("%s ", days[i]);
    }
    printf("\n");

    // Print spaces until the start of the month
    for (int i = 0; i < dayOfWeek; i++) {
        printf("    ");
    }

    // Print the days of the month
    for (int day = 1; day <= daysInMonth[month]; day++) {
        if (day == currentDay && month == currentMonth && year == currentYear){
        printf("\033[1;32m%3d\033[0m ", day); }// This will print the date in bold green}
    else{
        printf("%3d ", day);}



        //printf("%3d ", day);

        // Go to the next line after Saturday
        if ((day + dayOfWeek) % 7 == 0) {
            printf("\n");
        }
    }
    printf(BMAG);
    printf("\n===========================\n\n"); printf(reset);
}








int getStartingDay(int month, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int h = (1 + (13 * (month + 1)) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
    return (h + 5) % 7; // Convert from 0=Saturday to 0=Sunday
}

// Define the moods
char* moodNames[] = {"Very Bad", "Bad", "Neutral", "Good", "Very Good"};
char* moodColors[] = {"\033[0;31m", "\033[0;35m", "\033[0;37m", "\033[0;36m", "\033[0;34m"};
int moods[365] = {0};

int sleeps[365] = {0}; // Initialize all moods to 0
int sleep[31] = {0};


void printMonthWithMoods(int month, int year, int moods[]) {
    char* months[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int start = getStartingDay(month, year);

    // Create a filename using the username
    char filename[50];
    sprintf(filename, "%s_moods.txt", data.username);

    // Open the file for reading
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Read the mood data from the file
    //int moods[31] = {0}; // Initialize all moods to 0
    int fileYear, fileMonth, fileDay, mood;
    while (fscanf(file, "%d-%d-%d: %d\n", &fileYear, &fileMonth, &fileDay, &mood) == 4) {
        if (fileYear == year && fileMonth == month) {
            moods[fileDay - 1] = mood;
        }
    }

    // Close the file
    fclose(file);

    // Check for leap year
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        daysInMonth[2] = 29;
printf(MAG);
    printf("\n   %s %d\n", months[month], year); printf(reset);
printf("   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

// Print spaces until the start of the month
for (int day = 0; day < start; day++)
    printf("     ");

// Print the normal calendar
for (int day = 1; day <= daysInMonth[month]; day++) {
    printf("%5d", day);

    // Go to the next line after Saturday
    if ((day + start) % 7 == 0)
        printf("\n");
}
printf(BLU);
printf("\n\n   Mood Calendar\n"); printf(reset);
printf("   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

// Print spaces until the start of the month
for (int day = 0; day < start; day++)
    printf("     ");

// Print the calendar with moods
for (int day = 1; day <= daysInMonth[month]; day++) {
    switch (moods[day-1]) {
            case 1:
                printf(RED);
                break;
            case 2:
                printf(MAG);
                break;
            case 3:
                printf(GRN);
                break;
            case 4:
                printf(CYN);
                break;
            case 5:
                printf(BLU);
                break;
            default:
                printf(WHT);
                break;
        }

    printf("%5d", moods[day - 1]);
    printf(reset); // Reset the color

    // Go to the next line after Saturday
    if ((day + start) % 7 == 0)
        printf("\n");
}
printMoodTrackerDescription();

}





void inputMoods(char* username, int moods[]) {
    
    int year, month, day, mood;

   
    // Create a filename using the username
    char filename[50];
    sprintf(filename, "%s_moods.txt", username);

    // Open the file for writing
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (1) {
        system("cls");
        print_date();
        printf(BCYN);
        printf("\n\n\n\n\n======== Mood Tracker ========\n\n"); printf(reset);
        
        //print calendar--------------------------
        // Get the current time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // Get the current month and year
    month = tm->tm_mon + 1; // tm_mon is months since January, so add 1
    year = tm->tm_year + 1900; // tm_year is years since 1900

    // Print the current month's calendar
    printMonthCalendar(month, year);
    //------------------------------------------


        printf(MAG);
        printf("Enter the year (yy), or 0 to exit: "); printf(reset);
        scanf("%d", &year);
        if (year == 0) break;
        printf("\n\n");

        printf(MAG);
        printf("Enter the month (1-12): "); printf(reset);
        scanf("%d", &month);
        printf("\n\n");

        printf(MAG);
        printf("Enter the day (1-31), or 0 to exit: "); printf(reset);
        scanf("%d", &day);
        if (day == 0) break;
        printf("\n\n");

        printf(MAG);
        printf("From 1 to 5, how was your mood today? (1 = Very Bad, 5 = Very Good): "); printf(reset);
        scanf("%d", &mood);


        char confirm;
    do {
    printf("Confirm data input? (y/n): ");
    scanf(" %c", &confirm); // Add a space before %c to skip any whitespace characters

    if (confirm == 'n') {
        printf(YEL);
        printf("\nReturning to main menu...\n\n");
        printf("\nPress enter to continue..."); getchar(); getchar();
        printf(reset);
        system("cls");
        return;
    }
    else if (confirm == 'y') {
            // Store the mood for that day
             moods[day - 1] = mood;
            // Write the mood data to the file
            fprintf(file, "%d-%d-%d: %d\n", year, month, day, mood);
            printf(YEL);
            printf("Input successful, press enter to continue"); getchar(); getchar(); 
            printf(reset);

            // Clear the console
            system("cls");

            break;
        }


    else {
        printf(RED);
        printf("Invalid input!\n");
        printf(reset);
        printf(YEL);
        printf("\nPress enter to continue..."); getchar();
        printf(reset);
    }
} while (confirm != 'y' && confirm != 'n');
    
    }
    fclose(file);

   
}









void printMonthWithSleep(int month, int year, int sleeps[]) {
    // Reset the sleeps array
    for (int i = 0; i < 31; i++) {
        sleeps[i] = 0;
    }

    char* months[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int start = getStartingDay(month, year);

    // Create a filename using the username
    char filename[50];
    sprintf(filename, "%s_sleep.txt", data.username);

    // Open the file for reading
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    
    int fileYear, fileMonth, fileDay, sleepHours;

    int result;
while ((result = fscanf(file, "%d-%d-%d: %d\n", &fileYear, &fileMonth, &fileDay, &sleepHours)) != EOF) {
    if (result < 4) {
        // fscanf failed to read 4 items, break the loop
        break;
    }

    if (fileYear == year && fileMonth == month) {
        sleeps[fileDay - 1] = sleepHours;
    }
}

    // Close the file
    fclose(file);

    // Check for leap year
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        daysInMonth[2] = 29;

    printf(BMAG); printf("\n   %s %d\n", months[month], year); printf(reset);
printf("   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

// Print spaces until the start of the month
for (int day = 0; day < start; day++)
    printf("     ");

// Print the normal calendar
for (int day = 1; day <= daysInMonth[month]; day++) {
    printf("%5d", day);

    // Go to the next line after Saturday
    if ((day + start) % 7 == 0)
        printf("\n");
}

printf(BLU);
printf("\n\n   Sleep Calendar\n"); printf(reset);
printf("   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

// Print spaces until the start of the month
for (int day = 0; day < start; day++)
    printf("     ");

// Print the calendar with moods

for (int day = 1; day <= daysInMonth[month]; day++) {
    if (sleeps[day-1]>=7 && sleeps[day-1]<=9){
    printf(GRN);
    printf("%5d", sleeps[day - 1]); printf(reset);
    }

    else if (sleeps[day-1]<7 && sleeps[day-1]>0){
        printf(RED);
        printf("%5d", sleeps[day - 1]); printf(reset);
    }
    else if (sleeps[day-1]==0){
        printf(WHT); 
        printf("%5d", sleeps[day - 1]); printf(reset);
    }
    else{
        printf(RED);
        printf("%5d", sleeps[day - 1]); printf(reset);
    }

    // Go to the next line after Saturday
    if ((day + start) % 7 == 0)
        printf("\n");
}

printSleepTrackerDescription();
}






void inputSleep(char* username, int sleeps[]) {
    int year, month, day, sleep;

    // Create a filename using the username
    char filename[50];
    sprintf(filename, "%s_sleep.txt", username);

    // Open the file for writing
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }


    while (1) {
        system("cls");
        print_date();
        printf(BCYN);
        printf("\n\n\n\n\n======== Sleep Tracker ========\n\n"); printf(reset);

        //print calendar--------------------------
        // Get the current time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // Get the current month and year
    month = tm->tm_mon + 1; // tm_mon is months since January, so add 1
    year = tm->tm_year + 1900; // tm_year is years since 1900

    // Print the current month's calendar
    printMonthCalendar(month, year);
    //------------------------------------------

printf(MAG);
printf("Enter the year (yy), or 0 to exit: "); printf(reset);
scanf("%d", &year); getchar(); // Add getchar() to consume the newline character
if (year == 0) break;
printf("\n\n");

printf(MAG);
printf("Enter the month (1-12), or 0 to exit: "); printf(reset);
scanf("%d", &month); getchar(); // Add getchar() to consume the newline character
if (month == 0) break;
printf("\n\n");

printf(MAG);
printf("Enter the day (1-31), or 0 to exit: "); printf(reset);
scanf("%d", &day); getchar(); // Add getchar() to consume the newline character
if (day == 0) break;
printf("\n\n");

printf(MAG);
printf("How many hours did you sleep?: "); printf(reset);
scanf("%d", &sleep); getchar(); // Add getchar() to consume the newline character

char confirm;
    do {
    printf("Confirm data input? (y/n): ");
    scanf(" %c", &confirm); // Add a space before %c to skip any whitespace characters

    if (confirm == 'n') {
        printf(YEL);
        printf("\nReturning to main menu...\n\n");
        printf("\nPress enter to continue..."); getchar(); getchar();
        printf(reset);
        system("cls");
        return;
    }
    else if (confirm == 'y') {
            // Store the sleep for that day
            sleeps[day - 1] = sleep;
            fprintf(file, "%d-%d-%d: %d\n", year, month, day, sleep);
            printf(YEL);
            printf("Input successful, press enter to continue"); getchar(); getchar(); 
            printf(reset);

            // Clear the console
            system("cls");

            break;
        }


    else {
        printf(RED);
        printf("Invalid input!\n");
        printf(reset);
        printf(YEL);
        printf("\nPress enter to continue..."); getchar();
        printf(reset);
    }
} while (confirm != 'y' && confirm != 'n');
    
    }
    fclose(file);

   
}








//fungsi utk cek email

bool check_email(char email[]) {
    int atCount = 0;
    int dotCount = 0;

    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            atCount++;
        } else if (email[i] == '.') {
            dotCount++;
        }
    }

    if (atCount != 1 || dotCount < 1) {
        return false;
    }

    return true;  // Add this line
}




void home() {
    int choice;
   
    
   do{ 
     system("cls");
     print_date();
    printf(BCYN);
    printf("\n\n\n\n\n============HOME==============\n\n");
   printf(reset);
    printf(MAG);

    int month, year;
    //print calendar--------------------------
        // Get the current time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // Get the current month and year
    month = tm->tm_mon + 1; // tm_mon is months since January, so add 1
    year = tm->tm_year + 1900; // tm_year is years since 1900

    // Print the current month's calendar
    printMonthCalendar(month, year);
    //------------------------------------------

    printf(MAG);
    printf("Welcome, ");
    printf(reset);
    printf(CYN);
    printf("%s", data.name);
    printf(reset);
    printf(MAG);
    printf("! Hope you feel good today! \\(>w<)\n");
    printf(reset);

    printf("\n1. User Profile\n");
    printf("2. SDC Profile\n");
    printf("3. Meditation\n");
    printf("4. Video call\n");
    printf("5. Chat\n");
    printf("6. Mood Tracker\n");
    printf("7. Sleep Tracker\n");
    printf("0. Logout\n\n");
    printf(BCYN);
    printf("=============================\n\n");
    printf(reset);
    printf(YEL);
    printf("Enter your choice (number): ");
    printf(reset);
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            userProfile();
            break;
        case 2:
            sdcProfile();
            break;
        case 3:
            meditation();
            break;
        case 0:
            printf(YEL);
            printf("\nLogout successful!\n");
            printf("\nReturning to main menu...\n\n");
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
            break;
        case 4:{
            system("cls");
            videocall();
            break;
        }
        case 5:{
            system("cls");
            chat();
            break;
        }

        case 6:{
            system("cls");
            moodtracker();
            break;
        }

        case 7:{
            system("cls");
            sleeptracker();
            break;
        }   

        default:
            printf(RED);
            printf("Invalid choice.\n");
            printf(reset);

            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
            break;
    }
   }while (choice!=0);
}


void toLowerCase(char str[]) {
    int i = 0;
    while (str[i]) {
        str[i] = tolower(str[i]);
        i++;
    }
}

// Function to authenticate user login
int loginUser() {
    system("cls");
    int i;
    mindwell matcha[1000];
    char username[50], password[50];
    char usn[50];
    char u[50], p[50];
    FILE *fp;
    int loginSuccess = 0; // Flag to indicate whether login was successful

    do {
        print_date();
        fp = fopen("users.txt", "r");
        if (fp == NULL) {
            printf(RED);
            printf("Error in opening file.\n");
            printf(reset);
            return -1;
        }
        printf(BCYN);
        printf("\n\n\n\n\n==========LOGIN PAGE============\n\n\n");
        printf(reset);
        printf(MAG);
        printf("Enter Username: ");
        printf(reset);
        scanf("%49s", username); // Limit input length to prevent buffer overflow
        toLowerCase(username);
        strcpy(usn, username);
        printf("\n");
        printf(MAG);
        printf("Enter Password: ");
        printf(reset);
        scanf("%49s", password); // Limit input length to prevent buffer overflow
        i=0;
        while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", u, p, matcha[i].name, matcha[i].date, matcha[i].email) == 5) {
            if (strcmp(username, u) == 0 && strcmp(password, p) == 0) {
                loginSuccess = 1; // Set flag to indicate successful login
                break;
            }
            i++;
        }

        if (!loginSuccess) { // If login was not successful
            printf(RED);
            printf("\nLogin failed: Incorrect username or password.\n");
            printf(reset);
            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
        }

        fclose(fp);
    } while (!loginSuccess); // Repeat until login is successful


    //isi struct dgn data org yg login
    strcpy(data.username, usn);
    strcpy(data.password, password);
    strcpy(data.name, matcha[i].name);
    strcpy(data.date, matcha[i].date);
    strcpy(data.email, matcha[i].email);

    home();


    return 1; // Return 1 if login successful
}

int cekusn(char usn[]) {
    char username[50];
    FILE *fp;

    fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error in opening file.\n");
        return -1;
    }

    while (fscanf(fp, "%[^,]", username) != EOF) { // Parse the username from each line
        if (strcmp(username, usn) == 0) {
            fclose(fp);
            return 1; // Return 1 if username already exists
        }
        fscanf(fp, "%*[^\n]"); // Skip the rest of the line
    }
    fclose(fp);
    return 0; // Return 0 if username doesn't exist
}

void registerUser() {
    system("cls");
    char usn[50];
    char username[50], password[50];
    FILE *fp;

    fp = fopen("users.txt", "a");
    if (fp == NULL) {
        printf("Error in opening file.\n");
        return;
    }
    print_date();
    printf(BCYN);
    printf("\n\n\n\n\n==========REGISTER PAGE============\n");
    printf(reset);
    do {
        printf(MAG);
        printf("Enter Username: ");
        printf(reset);
        scanf("%49s", username);
        toLowerCase(username);
        strcpy(usn, username);

        if (cekusn(usn) == 1) {
            printf(RED);
            printf("\nUsername already exists. Choose another username.\n");
            printf(reset);
        }
    } while (cekusn(usn) == 1); // Keep asking for a username until a unique one is entered

    strcpy(data.username, usn);

    printf(MAG);
    printf("Enter Name: ");
    printf(reset);
    scanf(" %[^\n]", data.name); getchar();

    printf(MAG);
    printf("Enter register date (dd/mm/yy):");
    printf(reset);
    scanf(" %[^\n]", data.date); getchar();

do{ 
    printf(MAG);
    printf("Enter email:");
    printf(reset);
    scanf(" %[^\n]", data.email); getchar();

    check_email(data.email);

    if (check_email(data.email)==false){
        printf(RED);
        printf("Invalid email format!\n");
        printf(reset);
        printf(YEL);
        printf("\nPress enter to continue..."); getchar();
        printf(reset);
        system("cls");
    }

}while(check_email(data.email)==false);
    printf(MAG);
    printf("Enter Password: ");
    printf(reset);

    scanf("%s", data.password); getchar();

    fprintf(fp, "%s,%s,%s,%s,%s\n", data.username, data.password, data.name, data.date, data.email);
    fclose(fp);
    printf(YEL);
    printf("\n\nRegistration successful!\n");
    printf("\nReturning to main menu...\n\n");
    printf("\nPress enter to continue..."); getchar();
    printf(reset);
    system("cls");
}

    


int main() {
    system("cls");
    int choice;
    
    do {
        print_date();
        printf(BCYN);
        printf("\n\n\n\n\n=========WELCOME TO MINDWELL============");
        printf(reset);
        printf("\n\n");
        printf(MAG);
        printf("Let's start your journey to a better mental health! <3\n\n");
        printf(reset);
        printf("1. Register\n2. Login\n3. Exit\n");
        printf(BCYN);
        printf("\n========================================\n\n");
        printf(reset);
        printf(YEL);
        printf("Enter your choice (number): ");
        printf(reset);
        scanf("%d", &choice);
       
       
      

        if (choice == 1) {
            registerUser();
        } 
        else if (choice == 2) {
            int status = loginUser();

            if (status == 0) {
                printf(RED);
                printf("\nLogin failed: Incorrect username or password.\n");
                printf(reset);
            }
        } 
        else if (choice == 3) {
            printf(YEL);
            printf("Exiting...\n");
            printf(reset);
            exit(0);
        } 
        else {
            printf(RED);
            printf("\nInvalid choice.\n");
            printf(reset);
            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
        }
    } while (choice != 3);

    return 0;
}




void editProfile(){
    system("cls");
    int choice;
    do {
        print_date();
        system("cls");
        printf(BCYN);
        printf("\n\n\n\n\n==========EDIT PROFILE============\n");
        printf(reset);
        printf(MAG);
        printf("Name: ");
        printf(reset);
        printf("%s\n", data.name);
        printf(MAG);
        printf("Username: ");
        printf(reset);
        printf("%s\n", data.username);
        printf(MAG);
        printf("Register Date: ");
        printf(reset);
        printf("%s\n", data.date);
        printf(MAG);
        printf("Email: ");
        printf(reset);
        printf("%s\n", data.email);
        printf(BCYN);
        printf("==================================\n");
        printf(reset);
        mindwell matcha[1000];

        printf("1. Edit Name\n");
        printf("2. Edit Password\n");
        printf("3. Edit Email\n");
        printf("4. Back\n");
        printf(YEL);
        printf("Enter your choice (number): ");
        printf(reset);
        scanf("%d", &choice); getchar(); 

        switch (choice) {
            case 1:{
                printf(YEL);
                printf("Enter new name: ");
                printf(reset);
                scanf(" %[^\n]", temp.name); getchar();
                
            

            FILE *fp;
            fp = fopen("users.txt", "r");
            if (fp == NULL) {
                printf(RED);
                printf("Error in opening file.\n");
                printf(reset);
                return;
            }

            int i=0; 
                while (!feof(fp)) {
                    fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", matcha[i].username, matcha[i].password, 
                    matcha[i].name, matcha[i].date, matcha[i].email);
                    i++;    
                }
                fclose(fp);

            for (int j=0; j<i; j++){
                if (strcmp(matcha[j].username, data.username)==0){
                    strcpy(matcha[j].name, temp.name);
                }
            }
            strcpy(data.name, temp.name);

            fp= fopen("users.txt", "w");
            for (int j=0; j<i; j++){
                fprintf(fp, "%s,%s,%s,%s,%s\n", matcha[j].username, matcha[j].password, 
                matcha[j].name, matcha[j].date, matcha[j].email);
            }
            fclose(fp);
            printf(YEL);
            printf("\nEdit successful!\n");
            printf("\nPress enter to continue..."); getchar();
            printf(reset);
            break;
        }


        case 2:{
            do{
            printf(YEL);
            printf("Enter old password:");
            printf(reset);
            scanf(" %[^\n]", temp.password); getchar();
            if (strcmp(temp.password, data.password)!=0){
                printf(RED);
                printf("Wrong password!\n");
                printf(reset);
                printf(YEL);
                printf("\nPress enter to continue..."); getchar();
                printf(reset);
                system("cls");
            }
            }while (strcmp(temp.password, data.password)!=0);

            printf(YEL);
            printf("Enter new password: ");
            printf(reset);
            scanf("%[^\n]", temp.password); getchar();

            FILE *fp;
            fp = fopen("users.txt", "r");
            if (fp == NULL) {
                printf(RED);
                printf("Error in opening file.\n");
                printf(reset);
                return;
            }

            int i=0;
            while (!feof(fp)) {
                fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", matcha[i].username, matcha[i].password, 
                matcha[i].name, matcha[i].date, matcha[i].email);
                i++;    
                }
            fclose(fp);

            for (int j=0; j<i; j++){
                if (strcmp(matcha[j].username, data.username)==0){
                    strcpy(matcha[j].password, temp.password);
                }
            }

            strcpy(data.password, temp.password);

            fp= fopen("users.txt", "w");
            for (int j=0; j<i; j++){
                fprintf(fp, "%s,%s,%s,%s,%s\n", matcha[j].username, matcha[j].password, 
                matcha[j].name, matcha[j].date, matcha[j].email);
            }
            fclose(fp);
            printf(YEL);
            printf("\nEdit successful!\n");
            printf("\nPress enter to continue..."); getchar();
            printf(reset);
            break;
        }


        case 3:{
            do{
            printf(YEL);
            printf("Enter new email: ");
            printf(reset);
            scanf(" %[^\n]", temp.email); getchar();
            check_email(temp.email);
            if (check_email(temp.email)==false){
                printf(RED);
                printf("Invalid email format!\n");
                printf(reset);
                printf(YEL);
                printf("\nPress enter to continue..."); getchar();
                printf(reset);
                system("cls");
            }
            }while(check_email(temp.email)==false); 

            FILE *fp;
            fp = fopen("users.txt", "r");
            if (fp == NULL) {
                printf(RED);
                printf("Error in opening file.\n");
                printf(reset);
                return;
            }

            int i=0;
            while (!feof(fp)) {
                fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", matcha[i].username, matcha[i].password, 
                matcha[i].name, matcha[i].date, matcha[i].email);
                i++;    
                }
            fclose(fp);

            for (int j=0; j<i; j++){
                if (strcmp(matcha[j].username, data.username)==0){
                    strcpy(matcha[j].email, temp.email);
                }
            }
            strcpy(data.email, temp.email);

            fp= fopen("users.txt", "w");
            for (int j=0; j<i; j++){
                fprintf(fp, "%s,%s,%s,%s,%s\n", matcha[j].username, matcha[j].password, 
                matcha[j].name, matcha[j].date, matcha[j].email);
            }
            printf(YEL);
            printf("\nEdit successful! Confirmation email has been sent to %s\n", temp.email);
            printf("\nPress enter to continue..."); getchar();
            printf(reset);
            fclose(fp);
            break;
        }

        case 4:{
                userProfile();
                break;
            }
        }
    } while (choice != 4); // Repeat until the user chooses to go back
}


void userProfile(){
    print_date();
    system("cls");
    printf(BCYN);
	printf("\n\n\n\n\n==========USER PROFILE============\n");
    printf(reset);

    printf(MAG);
	printf("Name: ");
    printf(reset);
    printf("%s\n", data.name);

    printf(MAG);
	printf("Username: ");
    printf(reset);
    printf("%s\n", data.username);

    printf(MAG);
	printf("Register Date: ");
    printf(reset);
    printf("%s\n", data.date);

    printf(MAG);
	printf("Email: ");
    printf(reset);
    printf("%s\n", data.email);

    printf(BCYN);
	printf("==================================\n");
    printf(reset);

	printf("1. Edit Profile\n");
	printf("2. Back\n");
	int choice;
    printf(YEL);
	printf("\nEnter your choice (number): ");
    printf(reset);
	scanf("%d", &choice);
	switch (choice) {
		case 1:
			editProfile();
			break;
		case 2:
			home();
			break;
	}
}





void sdcProfile() {
    int choice;
   

    system("cls");
do {
     print_date();
    printf(BBLU);
    printf("\n\n\n\n\n==========SDC PROFILE============\n");
    printf(reset);
    printf("Data staff yang sedang bertugas:\n");
    printf(YEL); printf("(1)\n"); printf(reset);
    printf(MAG);
    printf("Nama: ");
    printf(reset);
    printf("Dr. Jesslyn\n");
    printf(MAG);
    printf("Spesialis: ");
    printf(reset);
    printf("Psikolog klinis\n");
    printf(MAG);
    printf("Jadwal kerja: ");
    printf(reset);
    printf("Senin - Jumat, 08.00 - 18.00\n");

    printf(YEL); printf("(2)\n"); printf(reset);
    printf(MAG);
    printf("Nama: ");
    printf(reset);
    printf("Dr. Nando\n");
    printf(MAG);
    printf("Spesialis: ");
    printf(reset);
    printf("Psikolog pendidikan\n");
    printf(MAG);
    printf("Jadwal kerja: ");
    printf(reset);
    printf("Senin - Jumat, 08.00 - 18.00\n");

    printf(YEL); printf("(3)\n"); printf(reset);
    printf(MAG);
    printf("Nama: ");
    printf(reset);
    printf("Dr. Bintang\n");
    printf(MAG);
    printf("Spesialis: ");
    printf(reset);
    printf("Psikolog klinis\n");
    printf(MAG);
    printf("Jadwal kerja: ");
    printf(reset);
    printf("Senin - Jumat, 08.00 - 18.00\n");

    printf(YEL); printf("(4)\n"); printf(reset);
    printf(MAG);
    printf("Nama: ");
    printf(reset);
    printf("Dr. Haidar\n");
    printf(MAG);
    printf("Spesialis: ");
    printf(reset);
    printf("Psikolog pendidikan\n");
    printf(MAG);
    printf("Jadwal kerja: ");
    printf(reset);
    printf("Senin - Jumat, 08.00 - 18.00\n");

    printf(BBLU);
    printf("==================================\n\n");
    printf(reset);
    printf("Press 1 to see terms and conditions\n");
    printf("Press 2 to go back to main menu\n\n");
    scanf("%d", &choice);


    if (choice==1){
         printf(MAG);
    printf("Syarat dan ketentuan:\n");
    printf(reset);
    printf("1. Permintaan Rujukan: Beberapa psikiater mungkin mengharuskan pasien memiliki rujukan dari dokter umum atau profesional kesehatan lain sebelum menerima konsultasi.\n");
    printf("2. Jadwal Janji: Pasien biasanya perlu membuat janji terlebih dahulu untuk konsultasi dengan psikiater. Kebanyakan psikiater menerima janji melalui telepon atau lewat situs web atau aplikasi resmi.\n");
    printf("3. Informasi Identitas: Pasien harus memberikan informasi identitas yang akurat, termasuk nama, alamat, nomor telepon, dan data kontak lainnya. Ini diperlukan untuk keperluan administratif dan komunikasi.\n");
    printf("4. Informasi Medis: Pasien harus memberikan riwayat medis yang akurat dan lengkap, termasuk catatan tentang masalah kesehatan mental yang telah dialami, pengobatan sebelumnya, dan penggunaan obat-obatan.\n");
    printf("5. Batal atau Ubah Janji: Jika perlu membatalkan atau mengubah janji, pasien biasanya harus memberi tahu psikiater dalam waktu yang cukup lama sebelum janji tersebut.\n");
    printf("6. Privasi dan Kerahasiaan: Psikiater berkewajiban untuk menjaga kerahasiaan informasi yang dibagikan oleh pasien selama sesi konsultasi. Ini adalah prinsip etika yang sangat penting dalam praktik psikiatri.\n");
    printf("7. Etika dan Perilaku: Pasien diharapkan untuk menjaga perilaku yang sesuai selama sesi konsultasi dan menghormati psikiater serta staf lainnya.\n");
    printf("8. Kerjasama dengan Pengobatan: Pasien diharapkan untuk berkomunikasi secara jujur dengan psikiater dan mengikuti panduan dan rekomendasi yang diberikan dalam pengobatan mereka.\n");
    printf("9. Keamanan: Jika psikiater memiliki kekhawatiran tentang bahaya diri sendiri atau orang lain yang mungkin dilakukan oleh pasien, mereka dapat memiliki kewajiban hukum untuk melaporkan ke pihak berwenang.\n");
    printf("10. Pemutusan Hubungan: Baik pasien maupun psikiater memiliki hak untuk mengakhiri hubungan profesional jika diperlukan. Psikiater biasanya akan memberi pemberitahuan yang cukup waktu jika mereka memutuskan untuk menghentikan perawatan.\n");
    printf("11. Evaluasi Lanjutan: Psikiater dapat merekomendasikan evaluasi atau perawatan lanjutan, termasuk terapi atau pengobatan lainnya, jika dianggap perlu.\n");
    printf("Harap diingat bahwa syarat dan ketentuan ini dapat berbeda antara praktek-praktek psikiater, sehingga penting untuk mendiskusikannya dengan psikiater yang Anda pilih sebelum mulai sesi konsultasi.\n");
    printf(MAG); printf("==================================\n\n"); printf(reset);
    printf(YEL);
    printf("\nPress enter to continue..."); getchar(); getchar();
    printf(reset);
     system("cls");
     break;
    }

    else if (choice==2){
        break;
    }

    else {printf(RED); printf("Invalid choice.\n"); printf(reset);}
   

} while (choice!=2);
}




void meditation() {
     system("cls");
    int choice;
    do {
    print_date();
    
    printf(BMAG);
    printf("\n\n\n\n\n==========MEDITATION============\n");
    printf(reset);
    printf("\n\n1. Meditation for Sadness\n");
    printf("2. Meditation for Anger\n");
    printf("3. Meditation for Anxiety\n");
    printf("4. Meditation for Stress\n");
    printf("5. Meditation for Insomnia\n");
    printf("0. Back to home\n\n");
    printf(BMAG);
    printf("=================================\n\n");
    printf(reset);
    printf(YEL);
    printf("Enter your choice (number): ");
    printf(reset);
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            do{
            system("cls");
            print_date();
            printf(BCYN);
            printf("\n\n\n\n\n======Meditation for Sadness======\n");
            printf(reset);
            printf("\n1. Meditation guide\n");
            printf("2. Meditation video\n");
            printf("3. Back\n\n");
            printf(BCYN);
            printf("==================================\n\n");
            printf(reset);
             printf(YEL);
            printf("Enter your choice (number): ");
            printf(reset);
            scanf("%d", &choice);
        if (choice==1){
           
            char* meditation_steps[] = {
                "Temukan tempat yang tenang dan nyaman untuk duduk.",
                "Tutup mata dan fokus perlahan pada pernafasan.",
                "Rasakan aliran udara masuk dan keluar dari tubuhmu.",
                "Biarkan pikiranmu datang dan pergi tanpa menilainya.",
                "Sentuh titik-titik rasa di tubuhmu, mulai dari ujung jari hingga ujung kepala.",
                "Fokus pada suara di sekitarmu tanpa terikat padanya.",
                "Kenali perasaan dan emosi tanpa terikat padanya.",
                "Visualisasikan tempat damai dalam pikiranmu, seperti pantai atau hutan.",
                "Biarkan dirimu meresapi kedamaian dan ketenangan tersebut.",
                "Buka mata perlahan dan lanjutkan hari dengan ketenangan yang baru ditemukan."
            };

            // Cetak langkah-langkah meditasi
            printf(MAG);
            printf("Langkah-langkah Meditasi:\n");
            printf(reset);
            for (int i = 0; i < sizeof(meditation_steps) / sizeof(meditation_steps[0]); ++i) {
                printf("%d. %s\n", i + 1, meditation_steps[i]);
            }

            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);

            system("cls");
        }

        else if (choice==2){
            printf(BMAG);
            printf("\n\n======Meditation for Sadness======\n");
            printf(reset);
            printf("\nWe've chosen the best meditation video guide for you!\nYou can watch the video here:\n");
            printf(BBLU);
            printf("\nhttps://www.youtube.com/watch?v=ogwYBpRhMeQ&ab_channel=GreatMeditation \n");
            printf(reset);
            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
        }

        else if (choice==3){
            system("cls");
            break;
        }

        else {printf(RED); printf("Invalid choice.\n"); printf(reset); 
        printf("Press enter to continue..."); getchar(); getchar(); system("cls");}
        }while(choice!=3); break;
        }

       case 2: {
            do{
            system("cls");
            print_date();
            printf(BCYN);
            printf("\n\n\n\n\n======Meditation for Anger======\n");
            printf(reset);
            printf("\n1. Meditation guide\n");
            printf("2. Meditation video\n");
            printf("3. Back\n\n");
            printf(BCYN);
            printf("==================================\n\n");
            printf(reset);
             printf(YEL);
            printf("Enter your choice (number): ");
            printf(reset);
            scanf("%d", &choice);
        if (choice==1){
           
            char* anger_management_steps[] = {
                "Temukan tempat yang tenang dan nyaman untuk duduk.",
                "Ambil napas dalam-dalam, masukkan melalui hidung dan keluarkan melalui mulut.",
                "Akui perasaan kemarahan tanpa penilaian.",
                "Hitung hingga sepuluh dengan perlahan, beri diri Anda waktu untuk tenang.",
                "Fokus pada merilekskan setiap bagian tubuh, mulai dari jari kaki hingga kepala.",
                "Visualisasikan suasana yang tenang dan damai untuk mengalihkan perhatian.",
                "Ulangi mantra atau frase yang menenangkan pada diri sendiri.",
                "Pertimbangkan perspektif orang lain atau situasi tersebut.",
                "Terapkan komunikasi tegas daripada reaksi agresif.",
                "Beri diri Anda waktu dan ruang sebelum merespons, berikan ruang untuk reaksi yang lebih dipertimbangkan."
            };

            // Cetak langkah-langkah meditasi
            printf(MAG);
            printf("Langkah-langkah Meditasi:\n");
            printf(reset);
            for (int i = 0; i < sizeof(anger_management_steps) / sizeof(anger_management_steps[0]); ++i) {
                printf("%d. %s\n", i + 1, anger_management_steps[i]);
            }

            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);

            system("cls");
        }

        else if (choice==2){
            printf(BMAG);
            printf("\n\n======Meditation for Anger======\n");
            printf(reset);
            printf("\nWe've chosen the best meditation video guide for you!\nYou can watch the video here:\n");
            printf(BBLU);
            printf("\nhttps://www.youtube.com/watch?v=wkse4PPxkk4&ab_channel=Goodful \n");
            printf(reset);
            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
        }

        else if (choice==3){
            system("cls");
            break;
        }

        else {printf(RED); printf("Invalid choice.\n"); printf(reset); 
        printf("Press enter to continue..."); getchar(); getchar(); system("cls");}
        }while(choice!=3); break;
        }

     case 3: {
            do{
            system("cls");
            print_date();
            printf(BCYN);
            printf("\n\n\n\n\n======Meditation for Anxiety======\n");
            printf(reset);
            printf("\n1. Meditation guide\n");
            printf("2. Meditation video\n");
            printf("3. Back\n\n");
            printf(BCYN);
            printf("==================================\n\n");
            printf(reset);
             printf(YEL);
            printf("Enter your choice (number): ");
            printf(reset);
            scanf("%d", &choice);

        if (choice==1){
           
            char* worry_management_steps[] = {
                "Carilah tempat yang tenang untuk duduk dengan nyaman.",
                "Fokus pada pernapasan, ambil napas dalam-dalam dan buang secara perlahan.",
                "Akui kekhawatiran tanpa membiarkan diri terbawa olehnya.",
                "Bayangkan diri Anda melepaskan kekhawatiran seperti daun yang terbawa arus sungai.",
                "Fokus pada saat ini dan terima keadaan dengan penuh kesadaran.",
                "Rilekskan tubuh Anda dari ujung kepala hingga ujung kaki.",
                "Pikirkan solusi yang mungkin untuk masalah, tanpa larut dalam kekhawatiran.",
                "Ulangi mantra positif untuk menenangkan pikiran Anda.",
                "Beri diri Anda izin untuk melepaskan kontrol atas hal-hal yang tidak dapat Anda ubah.",
                "Buka mata perlahan dan lanjutkan hari dengan ketenangan pikiran."
            };

            // Cetak langkah-langkah meditasi
            printf(MAG);
            printf("Langkah-langkah Meditasi:\n");
            printf(reset);
            for (int i = 0; i < sizeof(worry_management_steps) / sizeof(worry_management_steps[0]); ++i) {
                printf("%d. %s\n", i + 1, worry_management_steps[i]);
            }

            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);

            system("cls");
        }

        else if (choice==2){
            printf(BMAG);
            printf("\n\n======Meditation for Anxiety======\n");
            printf(reset);
            printf("\nWe've chosen the best meditation video guide for you!\nYou can watch the video here:\n");
            printf(BBLU);
            printf("\nhttps://www.youtube.com/watch?v=4pLUleLdwY4&ab_channel=YogaWithAdriene \n");
            printf(reset);
            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
        }

        else if (choice==3){
            system("cls");
            break;
        }

        else {printf(RED); printf("Invalid choice.\n"); printf(reset); 
        printf("Press enter to continue..."); getchar(); getchar(); system("cls");}
        }while(choice!=3); break;
        }

           case 4: {
            do{
            system("cls");
            print_date();
            printf(BCYN);
            printf("\n\n\n\n\n======Meditation for Stress======\n");
            printf(reset);
            printf("\n1. Meditation guide\n");
            printf("2. Meditation video\n");
            printf("3. Back\n\n");
            printf(BCYN);
            printf("==================================\n\n");
            printf(reset);
             printf(YEL);
            printf("Enter your choice (number): ");
            printf(reset);
            scanf("%d", &choice);

        if (choice==1){
           
            char* stress_management_steps[] = {
                "Cari tempat yang tenang dan nyaman untuk duduk.",
                "Ambil napas dalam-dalam, tahan sebentar, dan lepaskan perlahan-lahan.",
                "Fokus pada perasaan di tubuh Anda, sadari ketegangan dan lepaskan.",
                "Bayangkan diri Anda berada di tempat yang tenang dan damai.",
                "Rilekskan satu per satu bagian tubuh, mulai dari ujung kaki hingga kepala.",
                "Fokus pada pikiran positif dan menggantikan pikiran stres dengan afirmasi positif.",
                "Ulangi kata-kata yang menenangkan atau mantra yang Anda pilih.",
                "Bayangkan diri Anda mengatasi tantangan dengan tenang dan penuh keyakinan.",
                "Terima dan hargai momen sekarang tanpa khawatir akan masa depan.",
                "Buka mata perlahan dan lanjutkan hari dengan ketenangan dan ketegangan yang berkurang."
            };

            // Cetak langkah-langkah meditasi
            printf(MAG);
            printf("Langkah-langkah Meditasi:\n");
            printf(reset);
            for (int i = 0; i < sizeof(stress_management_steps) / sizeof(stress_management_steps[0]); ++i) {
                printf("%d. %s\n", i + 1, stress_management_steps[i]);
            }

            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);

            system("cls");
        }

        else if (choice==2){
            printf(BMAG);
            printf("\n\n======Meditation for Stress======\n");
            printf(reset);
            printf("We've chosen the best meditation video guide for you!\nYou can watch the video here:\n");
            printf(BBLU);
            printf("\nhttps://www.youtube.com/watch?v=ZsJ9utjAqZU&ab_channel=JennIm \n");
            printf(reset);
            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
        }

        else if (choice==3){
            system("cls");
            break;
        }

        else {printf(RED); printf("Invalid choice.\n"); printf(reset); 
        printf("Press enter to continue..."); getchar(); getchar(); system("cls");}
        }while(choice!=3); break;
        }

        case 5: {
            do{
            system("cls");
            print_date();
            printf(BCYN);
            printf("\n\n\n\n\n======Meditation for Insomnia======\n");
            printf(reset);
            printf("\n1. Meditation guide\n");
            printf("2. Meditation video\n");
            printf("3. Back\n\n");
            printf(BCYN);
            printf("==================================\n\n");
            printf(reset);
             printf(YEL);
            printf("Enter your choice (number): ");
            printf(reset);
            scanf("%d", &choice);

        if (choice==1){
           
            char* insomnia_management_steps[] = {
        
				"Ciptakan lingkungan tidur yang nyaman dan gelap.",
                "Ambil napas dalam-dalam dan perlahan, fokus pada pernafasan Anda.",
                "Rilekskan satu per satu bagian tubuh Anda, mulai dari kaki hingga kepala.",
                "Bayangkan diri Anda berada di tempat yang tenang dan nyaman.",
                "Hindari melihat jam dan pikirkan hal-hal yang menenangkan daripada kekhawatiran tidur.",
                "Jauhi perangkat elektronik setidaknya 30 menit sebelum tidur.",
                "Gunakan teknik meditasi pernapasan untuk menenangkan pikiran.",
                "Jika Anda tidak bisa tidur, bangun dan lakukan aktivitas yang tenang hingga Anda merasa mengantuk.",
                "Buka mata perlahan dan bersiap untuk tidur dengan rasa tenang.",
                "Terima dan hargai momen tidur Anda."
            };

            // Cetak langkah-langkah meditasi
            printf(MAG);
            printf("Langkah-langkah Meditasi:\n");
            printf(reset);
            for (int i = 0; i < sizeof(insomnia_management_steps) / sizeof(insomnia_management_steps[0]); ++i) {
                printf("%d. %s\n", i + 1, insomnia_management_steps[i]);
            }

            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);

            system("cls");
        }

        else if (choice==2){
            printf(BMAG);
            printf("\n\n======Meditation for Insomnia======\n");
            printf(reset);
            printf("\nWe've chosen the best meditation video guide for you!\nYou can watch the video here:\n");
            printf(BBLU);
            printf("\nhttps://www.youtube.com/watch?v=aEqlQvczMJQ&ab_channel=Goodful \n");
            printf(reset);
            printf(YEL);
            printf("\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
        }

        else if (choice==3){
            system("cls");
            break;
        }

        else {printf(RED); printf("Invalid choice.\n"); printf(reset); 
        printf("Press enter to continue..."); getchar(); getchar(); system("cls");}
        }while(choice!=3); break;
        }


        
        case 0: {
            home();
            system("cls");
            break;
        }

        default:
            printf(RED);
            {printf("Invalid choice.\n"); 
            printf("\nPress enter to continue..."); getchar(); getchar();
            system("cls"); break;}
            printf(reset);
    }
    } while (choice!=0);

}


void appointment_history(){
    system("cls");
    print_date();   
    printf(BCYN);
    printf("\n\n\n\n\n==========APPOINTMENT HISTORY============\n\n");
    int flag=0;
    printf(reset);
    FILE *fa;
    fa = fopen("appointment.txt", "r");
    if (fa == NULL) {
        printf(RED);
        printf("Error in opening file.\n");
        printf(reset);
        return;
    }
    int i=0;
    while (!feof(fa)) {
        fscanf(fa, " %[^,] ,%d /%d /%d ,%[^,] ,%[^,] ,%[^\n] ", appointment[i].username, &appointment[i].date.day, &appointment[i].date.month, &appointment[i].date.year, appointment[i].yisheng, appointment[i].shijian, appointment[i].app);
        i++;
    }
    fclose(fa);

    for (int j=0; j<i; j++){
        if (strcmp(appointment[j].username, data.username)==0){
            printf("-------------------------------------------\n\n");
            printf(MAG);
            printf("Date: ");
            printf(reset);
            printf("%d/%d/%d\n", appointment[j].date.day, appointment[j].date.month, appointment[j].date.year);
            printf(MAG);
            printf("Doctor: ");
            printf(reset);
            printf("%s\n", appointment[j].yisheng);
            printf(MAG);
            printf("Time: ");
            printf(reset);
            printf("%s\n", appointment[j].shijian);
            printf(MAG);
            printf("Platform: ");
            printf(reset);
            printf("%s\n", appointment[j].app);
            printf("\n");
            printf("-------------------------------------------\n\n");
            flag=1;
        }
    }

    if (flag==0){
        printf(RED);
        printf("You have no appointment history.\n\n");
        printf(reset);
        printf(BCYN);
        printf("==================================\n\n");
        printf(reset);
    }

    printf(YEL);
    printf("\nPress enter to continue..."); getchar(); getchar();
    system("cls");
}



void videocall(){
    system("cls");
    print_date();
     int choice;
     appointments temp;

    int yishengxuan; int shijianxuan; int appxuan;
    

    
do{
    system("cls");
    print_date();
    printf(BCYN);
    printf("\n\n\n\n\n============VIDEO CALL============\n\n");
    printf(reset);
    printf("1. Book your appointment\n");
    printf("2. View appointment history\n");
    printf("3. Back\n\n");
    printf(BCYN);
    printf("==================================\n\n");
    printf(reset); printf(YEL);
    printf("Enter your choice (number): ");
    printf(reset);
    scanf("%d", &choice);
    system("cls");



    switch (choice) {
        case 1:
            print_date();
            printf(BMAG);
            printf("\n\n\n\n\n==========Book Appointment==========\n\n");
            printf(reset); printf(YEL);
            printf("Enter date (dd/mm/yy): ");
            printf(reset);
             scanf("%d/%d/%d", &temp.date.day, &temp.date.month, &temp.date.year);

             do{
    printf("\n\n");
    printf(YEL);
    printf("Choose your doctor:\n");
    printf(reset); 
    printf("1. Dr. Jesslyn\n");
    printf("2. Dr. Nando\n");
    printf("3. Dr. Bintang\n");
    printf("4. Dr. Haidar\n");
    printf(YEL);
    printf("Enter your choice (number): ");
    printf(reset);
    scanf("%d", &yishengxuan);
        switch(yishengxuan){
            case 1:
            strcpy(temp.yisheng, "Dr. Jesslyn");
            break;
            case 2:
            strcpy(temp.yisheng, "Dr. Nando");
            break;
            case 3:
            strcpy(temp.yisheng, "Dr. Bintang");
            break;
            case 4:
            strcpy(temp.yisheng, "Dr. Haidar");
            break;
            default:{
            printf(RED);
            printf("Invalid choice.\n"); printf(reset);}
        }
    }while(yishengxuan!=1 && yishengxuan!=2 && yishengxuan!=3 && yishengxuan!=4);
    
    do{
    printf("\n\n");
        printf(YEL);
    printf("Choose your preferred time slot:\n");
    printf(reset);
    printf("1. 08.10 - 09.00\n");
    printf("2. 09.10 - 10.00\n");
    printf("3. 10.10 - 11.00\n");
    printf("4. 11.10 - 12.00\n");
    printf("5. 14.10 - 15.00\n");
    printf("6. 15.10 - 16.00\n");
    printf("7. 16.10 - 17.00\n");
    printf("8. 17.10 - 18.00\n");
    printf(YEL);
    printf("Enter your choice (number): ");
    printf(reset);
    scanf("%d", &shijianxuan);
        switch(shijianxuan){
            case 1:
            strcpy(temp.shijian, "08.10 - 09.00");
            break;
            case 2:
            strcpy(temp.shijian, "09.10 - 10.00");
            break;
            case 3:
            strcpy(temp.shijian, "10.10 - 11.00");
            break;
            case 4:
            strcpy(temp.shijian, "11.10 - 12.00");
            break;
            case 5:
            strcpy(temp.shijian, "14.10 - 15.00");
            break;
            case 6:
            strcpy(temp.shijian, "15.10 - 16.00");
            break;
            case 7:
            strcpy(temp.shijian, "16.10 - 17.00");
            break;
            case 8:
            strcpy(temp.shijian, "17.10 - 18.00");
            break;
            default:{
            printf(RED);
            printf("Invalid choice.\n"); printf(reset);}
        }
    }while(shijianxuan!=1 && shijianxuan!=2 && shijianxuan!=3 && shijianxuan!=4 && shijianxuan!=5 && shijianxuan!=6 && shijianxuan!=7 && shijianxuan!=8);
        
   
   do{
    printf("\n\n");
    printf(YEL);
    printf("Choose your preferred platform:\n");
    printf(reset);
    printf("1. Zoom\n");
    printf("2. Google Meet\n");
    printf(YEL);
    printf("Enter your choice (number): ");
    printf(reset);
    scanf("%d", &appxuan);
        switch(appxuan){
            case 1:
            strcpy(temp.app, "Zoom");
            break;
            case 2:
            strcpy(temp.app, "Google Meet");
            break;
            default:{
            printf(RED);
            printf("Invalid choice.\n"); printf(reset);}
        }
   }while(appxuan!=1 && appxuan!=2);
            printf(YEL);
            printf("\n\nPress enter to continue..."); getchar(); getchar();
            printf(reset);
            system("cls");
        

    printf(MAG);    
    printf("\n\n\n\n\n\nYour appointment has been booked!\n");
    printf(reset);
    printf("Date: %d/%d/%d\n", temp.date.day, temp.date.month, temp.date.year);
    printf("Doctor: %s\n", temp.yisheng);
    printf("Time: %s\n", temp.shijian);
    printf("Platform: %s\n", temp.app);
    if (appxuan==1){
        printf("Zoom link: https://binus.zoom.us/j/96147460670?pwd=aktKMHo0dGF2S1NrNlBYcWFxTmoxQT09\n");
    }
    else if (appxuan==2){
        printf("Google Meet link: https://meet.google.com/sow-mode-hxv\n");
    }
    strcpy(temp.username, data.username);
    FILE *fa;
    fa= fopen("appointment.txt", "a");
    fprintf(fa, "%s,%d/%d/%d,%s,%s,%s\n", temp.username, temp.date.day, temp.date.month, temp.date.year, temp.yisheng, temp.shijian, temp.app);
    printf(YEL);
    printf("\nPress enter to continue..."); getchar(); printf(reset);
    fclose(fa);
    system("cls");
            break;



        case 2:
            appointment_history();
            break;
        default: printf(RED); printf("Invalid choice.\n"); printf(reset);
    }

    
}while (choice!=3);
}




void chat(){
    int choice,xuan;
    do{
    system("cls");
    print_date();
    printf(BCYN);
    printf("\n\n\n\n\n============CHAT============\n\n"); printf(reset);
    printf("1. Dr. Jesslyn\n");
    printf("2. Dr. Nando\n");
    printf("3. Dr. Bintang\n");
    printf("4. Dr. Haidar\n");
    printf("0. Back\n\n");
    printf(BCYN); printf("=============================\n\n"); printf(reset); 
    
    printf(YEL);
    printf("Enter your choice (number): "); printf(reset);
    scanf("%d", &choice);
    switch (choice) {
        case 0:{
            break;
        }
        case 1:{
            printf(MAG);
            printf("\nChoose your preferred platform:\n"); printf(reset);
            printf("1. WhatsApp\n2. Line\n3. Telegram\n");
            printf(YEL); printf("Enter your choice (number): "); 
            printf(reset);
            scanf("%d", &xuan); getchar();
            switch(xuan){
                case 1: {
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Jesslyn\n"); printf(reset);
                    printf(CYN); printf("https://wa.me/62881037037426\n");  printf(reset);
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                case 2:{
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Jesslyn\n"); printf(reset);
                    printf(CYN); printf("https://line.me/ti/p/gbR1foBo7Y\n"); 
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                case 3:{
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Jesslyn\n"); printf(reset);
                    printf(CYN); printf("https://t.me/jesslyntrie\n");
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                default: {
                    printf(RED);
                    printf("Invalid choice.\n");
                    printf(reset); break;
                }
            }
            
            break;
        }

        case 2:{
            printf(MAG);
            printf("\nChoose your preferred platform:\n"); printf(reset);
            printf("1. WhatsApp\n2. Line\n3. Telegram\n");
            printf(YEL); printf("Enter your choice (number): "); 
            printf(reset);
            scanf("%d", &xuan);
            switch(xuan){
                case 1: {
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Nando\n"); printf(reset);
                    printf("https://wa.me/62881037037426\n"); 
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                case 2:{
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Nando\n"); printf(reset);
                    printf(CYN); printf("https://line.me/ti/p/gbR1foBo7Y\n"); 
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                case 3:{
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Nando\n"); printf(reset);
                    printf(CYN); printf("https://t.me/fernandodr\n");
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                default: {
                    printf(RED);
                    printf("Invalid choice.\n");
                    printf(reset); break;
                }
            }
            break;
        }

        case 3:{
            printf(MAG);
            printf("\nChoose your preferred platform:\n"); printf(reset);
            printf("1. WhatsApp\n2. Line\n3. Telegram\n");
            printf(YEL); printf("Enter your choice (number): "); 
            printf(reset);
            scanf("%d", &xuan);
            switch(xuan){
                case 1: {
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Bintang\n"); printf(reset);
                    printf(CYN); printf("https://wa.me/62881037037426\n"); 
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                case 2:{
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Bintang\n"); printf(reset);
                    printf(CYN); printf("https://line.me/ti/p/gbR1foBo7Yn"); 
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                case 3:{
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Bintang\n"); printf(reset);
                    printf(CYN); printf("https://t.me/bintangbintang\n");
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                default: {
                    printf(RED);
                    printf("Invalid choice.\n");
                    printf(reset); break;
                }
            }
            break;
        }
        
        case 4: {
            printf(MAG);
            printf("\nChoose your preferred platform:\n"); printf(reset);
            printf("1. WhatsApp\n2. Line\n3. Telegram\n");
            printf(YEL); printf("Enter your choice (number): "); 
            printf(reset);
            scanf(" %d", &xuan);
            switch(xuan){
                case 1: {
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Haidar\n"); printf(reset);
                    printf("https://wa.me/6281234567890\n"); 
                    printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
               case 2:{
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Haidar\n"); printf(reset);
                    printf(CYN); printf("https://line.me/ti/p/~drhaidar\n"); 
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                case 3:{
                    printf(MAG); printf("\n\nPlease kindly click the link below to chat with Dr. Haidar\n"); printf(reset);
                    printf(CYN); printf("https://t.me/drhaidar\n");
                    printf(YEL); printf("\nPress enter to continue..."); getchar(); getchar();
                    break;
                }
                default: {
                    printf(RED);
                    printf("Invalid choice.\n");
                    printf(reset); break;
                }
                    
            }

        }
        
        default:{
            //printf(RED);
            //printf("Invalid choice.\n");
            //printf(reset);
            //printf(YEL); printf("Press enter to continue.."); getchar(); getchar();
            break;
        }
    }
           
    }while (choice!=0);
}

        

   

void moodtracker(){
     int mood,choice;
    do{
        int month, year;
        system("cls");
        print_date();
        printf(BBLU);
        printf("\n\n\n\n\n==============MOOD TRACKER==============\n\n");
        printf(reset);

        //print calendar--------------------------
        // Get the current time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // Get the current month and year
    month = tm->tm_mon + 1; // tm_mon is months since January, so add 1
    year = tm->tm_year + 1900; // tm_year is years since 1900

    // Print the current month's calendar
    printMonthCalendar(month, year);
    //------------------------------------------



       
     
        printf("\n1. Enter moods\n");
        printf("2. Print month with moods\n");
        printf("0. Exit\n\n");
        printf(BBLU);
        printf("===========================================\n\n");
        printf(reset); printf(YEL);
        printf("Enter your choice: "); printf(reset);
        scanf("%d", &choice);

        switch(choice) {
           
            case 1:
                inputMoods(data.username, moods);
                break;
            case 2:
                printf(MAG);
                printf("Enter month and year (mm yy): "); printf(reset);
                scanf("%d %d", &month, &year);
                printMonthWithMoods(month, year, moods);
                printf(YEL);
                printf("\nPress enter to continue..."); getchar(); getchar();
                break;
            case 0:
                break;
            default:
                printf(RED);
                printf("Invalid choice\n");
                printf(reset); printf(YEL);
                printf("\nPress enter to continue..."); getchar(); getchar();
        }
    } while (choice != 0); 
    
}


void sleeptracker(){
    int sleep[31], choice;
    do{
        system("cls");
        print_date();
        printf(BBLU);
        printf("\n\n\n\n\n============SLEEP TRACKER============\n\n");
        printf(reset);

        int month, year;
        //print calendar--------------------------
        // Get the current time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // Get the current month and year
    month = tm->tm_mon + 1; // tm_mon is months since January, so add 1
    year = tm->tm_year + 1900; // tm_year is years since 1900

    // Print the current month's calendar
    printMonthCalendar(month, year);
    //------------------------------------------
     
        printf("1. Enter sleep\n");
        printf("2. Print month with sleep\n");
        printf("0. Exit\n\n");
        printf(BBLU);
        printf("=====================================\n\n");
        printf(reset); printf(YEL);
        printf("Enter your choice: "); printf(reset);
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                inputSleep(data.username, sleep);
                break;
            case 2:
                printf(MAG);
                printf("Enter month and year (mm yy): "); printf(reset);
                scanf("%d %d", &month, &year);
                printMonthWithSleep(month, year, sleep);
                printf(YEL);
                printf("\nPress enter to continue..."); getchar(); getchar();
                break;
            case 0:
                break;
            default:
                printf(RED);
                printf("Invalid choice\n");
                printf(reset); printf(YEL);
                printf("\nPress enter to continue..."); getchar(); getchar();
        }
    } while (choice != 0); 
}