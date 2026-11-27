#include <stdio.h>

// Function to check if a given year is a leap year
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to calculate the day of the week for Jan 1st of the given year
// Returns 0 = Sunday, 1 = Monday, ..., 6 = Saturday
int getFirstDayOfYear(int year) {
    int y = year - 1;
    return (y * 365 + y / 4 - y / 100 + y / 400 + 1) % 7;
}

int main() {
    int year;
    const char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("Enter a year (e.g., 2026): ");
    if (scanf("%d", &year) != 1 || year < 1) {
        printf("Invalid year entered.\n");
        return 1;
    }

    // Adjust February for leap years
    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    int startDay = getFirstDayOfYear(year);

    printf("\n==================== CALENDAR FOR %d ====================\n", year);

    for (int m = 0; m < 12; m++) {
        printf("\n  --------------- %s ---------------\n", months[m]);
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        // Print leading spaces for the first week of the month
        for (int space = 0; space < startDay; space++) {
            printf("     ");
        }

        // Print all days of the current month
        for (int day = 1; day <= daysInMonth[m]; day++) {
            printf("%5d", day);

            // Move to the next line after Saturday (every 7th column)
            if ((day + startDay) % 7 == 0) {
                printf("\n");
            }
        }

        // Ensure a newline before the next month if the month didn't end on Saturday
        if ((daysInMonth[m] + startDay) % 7 != 0) {
            printf("\n");
        }

        // Update startDay for the next month
        startDay = (startDay + daysInMonth[m]) % 7;
    }

    printf("\n===========================================================\n");
    return 0;
}
