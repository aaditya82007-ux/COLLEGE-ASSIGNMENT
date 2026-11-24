#include <stdio.h>

// Structure to store sensor details
struct Sensor {
    int id;
    char type[50];
    float measuredValue;
    float minLimit;
    float maxLimit;
};

int main() {
    int n, i;
    int abnormalCount = 0; // Counter for total abnormal sensors (Warning + Anomaly)

    printf("Enter the number of sensors: ");
    scanf("%d", &n);

    // Array of structures
    struct Sensor s[n];

    // Taking input for each sensor
    for (i = 0; i < n; i++) {
        printf("\n--- Enter details for Sensor %d ---\n", i + 1);
        
        printf("Sensor ID: ");
        scanf("%d", &s[i].id);
        
        printf("Sensor Type: ");
        scanf(" %[^\n]", s[i].type); // Reads string including spaces
        
        printf("Measured Value: ");
        scanf("%f", &s[i].measuredValue);
        
        printf("Minimum Limit: ");
        scanf("%f", &s[i].minLimit);
        
        printf("Maximum Limit: ");
        scanf("%f", &s[i].maxLimit);
    }

    // Classifying and displaying each sensor reading
    printf("\n================ SENSOR CLASSIFICATION ================\n");
    for (i = 0; i < n; i++) {
        float range = s[i].maxLimit - s[i].minLimit;
        float margin = 0.10 * range; // 10% of the range

        printf("\nSensor ID: %d | Type: %s | Value: %.2f (Range: %.2f - %.2f)\n", 
               s[i].id, s[i].type, s[i].measuredValue, s[i].minLimit, s[i].maxLimit);

        // Classification logic
        if (s[i].measuredValue >= s[i].minLimit && s[i].measuredValue <= s[i].maxLimit) {
            printf("Status: Normal\n");
        } 
        else if ((s[i].measuredValue >= (s[i].minLimit - margin) && s[i].measuredValue < s[i].minLimit) ||
                 (s[i].measuredValue > s[i].maxLimit && s[i].measuredValue <= (s[i].maxLimit + margin))) {
            printf("Status: Warning (Slightly outside range within 10%%)\n");
            abnormalCount++; // Increment abnormal counter
        } 
        else {
            printf("Status: Anomaly (More than 10%% outside range)\n");
            abnormalCount++; // Increment abnormal counter
        }
    }

    // Display total abnormal sensors (Warning + Anomaly)
    printf("\n=======================================================\n");
    printf("Total Abnormal Sensors (Warning + Anomaly): %d\n", abnormalCount);

    return 0;
}