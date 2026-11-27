#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define FILE_NAME "robot_records.dat"

// Safety Threshold Constants
#define MAX_SAFE_DEPTH 300.0        // in meters
#define MAX_SAFE_PRESSURE 31.0      // in ATM (approx 1 ATM per 10m + 1 ATM surface)
#define MIN_SAFE_TEMP 2.0           // in Celsius
#define MAX_SAFE_TEMP 45.0          // in Celsius
#define MIN_SAFE_BATTERY 20.0       // in percentage (%)

// Structure to hold underwater robot telemetry and inspection data
typedef struct {
    int record_id;
    char timestamp[25];
    float depth;                // meters
    float water_pressure;       // ATM
    float temperature;          // Celsius
    float battery_percentage;   // %
    int structural_defects;     // count of detected defects
} RobotRecord;

// Function Prototypes
void addRecord(RobotRecord records[], int *count);
void saveRecordsToFile(RobotRecord records[], int count);
int loadRecordsFromFile(RobotRecord records[]);
int isUnsafe(RobotRecord r, char reasons[]);
void generateInspectionReport(RobotRecord records[], int count);
void displayAllRecords(RobotRecord records[], int count);

int main() {
    RobotRecord records[MAX_RECORDS];
    int count = loadRecordsFromFile(records);
    int choice;

    do {
        printf("\n======================================================\n");
        printf("   UNDERWATER ROBOT TELEMETRY & INSPECTION SYSTEM\n");
        printf("======================================================\n");
        printf("1. Input / Add New Robot Telemetry Record\n");
        printf("2. View All Historical Records\n");
        printf("3. Process Records & Generate Inspection Report\n");
        printf("4. Save & Exit\n");
        printf("------------------------------------------------------\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear invalid input buffer
            printf("Invalid input! Please enter a number between 1 and 4.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addRecord(records, &count);
                saveRecordsToFile(records, count);
                break;
            case 2:
                displayAllRecords(records, count);
                break;
            case 3:
                generateInspectionReport(records, count);
                break;
            case 4:
                saveRecordsToFile(records, count);
                printf("All records saved to '%s'. Exiting program...\n", FILE_NAME);
                break;
            default:
                printf("Invalid choice! Please select 1-4.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to input new telemetry data
void addRecord(RobotRecord records[], int *count) {
    if (*count >= MAX_RECORDS) {
        printf("Error: Maximum record storage limit reached!\n");
        return;
    }

    RobotRecord newRec;
    newRec.record_id = (*count == 0) ? 101 : records[*count - 1].record_id + 1;

    printf("\n--- Enter Telemetry Data (Record ID: %d) ---\n", newRec.record_id);
    printf("Enter Timestamp (e.g., 2026-11-27_09:30): ");
    scanf("%24s", newRec.timestamp);

    printf("Enter Depth (meters): ");
    scanf("%f", &newRec.depth);

    printf("Enter Water Pressure (ATM): ");
    scanf("%f", &newRec.water_pressure);

    printf("Enter Water Temperature (Celsius): ");
    scanf("%f", &newRec.temperature);

    printf("Enter Battery Percentage (0-100%%): ");
    scanf("%f", &newRec.battery_percentage);

    printf("Enter Number of Detected Structural Defects: ");
    scanf("%d", &newRec.structural_defects);

    records[*count] = newRec;
    (*count)++;
    printf("Record #%d successfully logged!\n", newRec.record_id);
}

// Function to save historical records to a binary file
void saveRecordsToFile(RobotRecord records[], int count) {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("Warning: Unable to open file for saving.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(records, sizeof(RobotRecord), count, fp);
    fclose(fp);
}

// Function to load existing records on startup
int loadRecordsFromFile(RobotRecord records[]) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        return 0; // No previous file exists yet
    }
    int count = 0;
    fread(&count, sizeof(int), 1, fp);
    fread(records, sizeof(RobotRecord), count, fp);
    fclose(fp);
    return count;
}

// Evaluates if a record violates any safety thresholds
int isUnsafe(RobotRecord r, char reasons[]) {
    int unsafe = 0;
    reasons[0] = '\0';

    if (r.depth > MAX_SAFE_DEPTH) {
        strcat(reasons, "[Depth Exceeded] ");
        unsafe = 1;
    }
    if (r.water_pressure > MAX_SAFE_PRESSURE) {
        strcat(reasons, "[High Pressure] ");
        unsafe = 1;
    }
    if (r.temperature < MIN_SAFE_TEMP || r.temperature > MAX_SAFE_TEMP) {
        strcat(reasons, "[Extreme Temp] ");
        unsafe = 1;
    }
    if (r.battery_percentage < MIN_SAFE_BATTERY) {
        strcat(reasons, "[Low Battery] ");
        unsafe = 1;
    }
    if (r.structural_defects > 0) {
        strcat(reasons, "[Structural Defects Found] ");
        unsafe = 1;
    }

    return unsafe;
}

// Displays all stored records in a tabular format
void displayAllRecords(RobotRecord records[], int count) {
    if (count == 0) {
        printf("\nNo historical records found.\n");
        return;
    }

    printf("\n------------------------------------------------------------------------------------------\n");
    printf("%-6s %-18s %-10s %-12s %-10s %-10s %-8s\n", 
           "ID", "Timestamp", "Depth(m)", "Press(ATM)", "Temp(C)", "Batt(%)", "Defects");
    printf("------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-6d %-18s %-10.2f %-12.2f %-10.2f %-10.1f %-8d\n",
               records[i].record_id,
               records[i].timestamp,
               records[i].depth,
               records[i].water_pressure,
               records[i].temperature,
               records[i].battery_percentage,
               records[i].structural_defects);
    }
    printf("------------------------------------------------------------------------------------------\n");
}

// Processes records, flags hazards, and exports a text inspection report
void generateInspectionReport(RobotRecord records[], int count) {
    if (count == 0) {
        printf("\nNo records available to process.\n");
        return;
    }

    FILE *reportFile = fopen("inspection_report.txt", "w");
    int unsafeCount = 0;
    int totalDefects = 0;
    float maxDepth = 0.0;
    char reasons[200];

    printf("\n==================== INSPECTION REPORT ====================\n");
    if (reportFile) {
        fprintf(reportFile, "==================== UNDERWATER ROBOT INSPECTION REPORT ====================\n\n");
    }

    for (int i = 0; i < count; i++) {
        totalDefects += records[i].structural_defects;
        if (records[i].depth > maxDepth) {
            maxDepth = records[i].depth;
        }

        if (isUnsafe(records[i], reasons)) {
            unsafeCount++;
            printf("ALERT | ID: %d (%s) -> UNSAFE: %s\n", 
                   records[i].record_id, records[i].timestamp, reasons);
            if (reportFile) {
                fprintf(reportFile, "ALERT | ID: %d (%s) -> UNSAFE: %s\n", 
                        records[i].record_id, records[i].timestamp, reasons);
            }
        } else {
            printf("OK    | ID: %d (%s) -> Operating within safe limits.\n", 
                   records[i].record_id, records[i].timestamp);
            if (reportFile) {
                fprintf(reportFile, "OK    | ID: %d (%s) -> Operating within safe limits.\n", 
                        records[i].record_id, records[i].timestamp);
            }
        }
    }

    printf("\n--- Summary Statistics ---\n");
    printf("Total Records Analyzed : %d\n", count);
    printf("Unsafe Conditions Found: %d\n", unsafeCount);
    printf("Max Depth Reached      : %.2f m\n", maxDepth);
    printf("Total Structural Defects: %d\n", totalDefects);
    printf("===========================================================\n");

    if (reportFile) {
        fprintf(reportFile, "\n--- Summary Statistics ---\n");
        fprintf(reportFile, "Total Records Analyzed  : %d\n", count);
        fprintf(reportFile, "Unsafe Conditions Found : %d\n", unsafeCount);
        fprintf(reportFile, "Max Depth Reached       : %.2f m\n", maxDepth);
        fprintf(reportFile, "Total Structural Defects: %d\n", totalDefects);
        fclose(reportFile);
        printf("Report also exported to 'inspection_report.txt'!\n");
    }
}
