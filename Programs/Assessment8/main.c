#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIMIT 1000
#define NULL_PTR NULL

enum month {
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};

typedef struct {
    int emp_id;
    char* emp_name;
    enum month emp_month;
    int present_day;
    int salary;
    int deducted_sal;
    int net_sal;
} emp_details;

const char* getMonthName(int m) {
    switch (m) {
        case 1: return "Jan";
        case 2: return "Feb";
        case 3: return "Mar";
        case 4: return "Apr";
        case 5: return "May";
        case 6: return "Jun";
        case 7: return "Jul";
        case 8: return "Aug";
        case 9: return "Sep";
        case 10: return "Oct";
        case 11: return "Nov";
        case 12: return "Dec";
        default: return "Invalid month";
    }
}

// Function to return the number of days in a given month
int getDaysInMonth(int month, int year) {
    switch (month) {
        case Jan: return 31;
        case Mar: return 31;
        case May: return 31;
        case Jul: return 31;
        case Aug: return 31;
        case Oct: return 31;
        case Dec: return 31;
        case Apr: return 30;
        case Jun: return 30;
        case Sep: return 30;
        case Nov: return 30;
        case Feb:
            // Leap year check for February
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                return 29;
            } else {
                return 28;
            }
        default: return 0; // Invalid month
    }
}

int main() {
    int num_of_employees = 100;
    FILE *fp;
    FILE *emp_ctc;
    FILE *emp_atn;

    fp = fopen("emp_details.txt", "w+");
    emp_ctc = fopen("emp_ctc.txt", "r");
    emp_atn = fopen("emp_atn.txt", "r");

    if (fp == NULL_PTR || emp_ctc == NULL_PTR || emp_atn == NULL_PTR) {
        printf("Error opening file(s)\n");
        return 1;
    }

    emp_details* emp = (emp_details*)malloc(sizeof(emp_details) * num_of_employees);

    for (int i = 0; i < num_of_employees; i++) {
        emp[i].emp_name = (char*)malloc(MAX_LIMIT * sizeof(char));
    }

    int i = 0;
    int emp_id_atn, present_day;
    char month_str_atn[MAX_LIMIT];

    printf("%-10s %-20s %-10s %-15s %-10s %-15s %-10s\n", 
           "Emp ID", "Emp Name", "Month", "Present Days", "Salary", "Deducted Salary", "Net Salary");

    fprintf(fp, "%-10s %-20s %-10s %-15s %-10s %-15s %-10s\n", 
            "Emp ID", "Emp Name", "Month", "Present Days", "Salary", "Deducted Salary", "Net Salary");

    while (fscanf(emp_ctc, "%d %s %s %d", &emp[i].emp_id, emp[i].emp_name, month_str_atn, &emp[i].salary) != EOF) {
        fscanf(emp_atn, "%d %s %d", &emp_id_atn, month_str_atn, &present_day);

        if (emp[i].emp_id != emp_id_atn) {
            printf("Mismatch in employee ID between attendance and CTC file.\n");
            continue;
        }

        if (strcmp(month_str_atn, "Jan") == 0) emp[i].emp_month = Jan;
        else if (strcmp(month_str_atn, "Feb") == 0) emp[i].emp_month = Feb;
        else if (strcmp(month_str_atn, "Mar") == 0) emp[i].emp_month = Mar;
        else if (strcmp(month_str_atn, "Apr") == 0) emp[i].emp_month = Apr;
        else if (strcmp(month_str_atn, "May") == 0) emp[i].emp_month = May;
        else if (strcmp(month_str_atn, "Jun") == 0) emp[i].emp_month = Jun;
        else if (strcmp(month_str_atn, "Jul") == 0) emp[i].emp_month = Jul;
        else if (strcmp(month_str_atn, "Aug") == 0) emp[i].emp_month = Aug;
        else if (strcmp(month_str_atn, "Sep") == 0) emp[i].emp_month = Sep;
        else if (strcmp(month_str_atn, "Oct") == 0) emp[i].emp_month = Oct;
        else if (strcmp(month_str_atn, "Nov") == 0) emp[i].emp_month = Nov;
        else if (strcmp(month_str_atn, "Dec") == 0) emp[i].emp_month = Dec;
        else {
            printf("Invalid month for employee ID %d\n", emp[i].emp_id);
            continue;
        }

        emp[i].present_day = present_day;

        if (emp[i].emp_month < 1 || emp[i].emp_month > 12) {
            printf("Invalid month for employee ID %d\n", emp[i].emp_id);
            continue;
        }

        // Get the actual number of days in the month
        int num_days_in_month = getDaysInMonth(emp[i].emp_month, 2025); // Use current year (2025 or any year) for days in month

        // Calculate net salary based on the number of days in the month
        emp[i].net_sal = (emp[i].salary / num_days_in_month) * emp[i].present_day;

        emp[i].deducted_sal = emp[i].salary - emp[i].net_sal;

        fprintf(fp, "%-10d %-20s %-10s %-15d %-10d %-15d %-10d\n", 
                emp[i].emp_id, emp[i].emp_name, getMonthName(emp[i].emp_month), 
                emp[i].present_day, emp[i].salary, 
                emp[i].deducted_sal, emp[i].net_sal);

        printf("%-10d %-20s %-10s %-15d %-10d %-15d %-10d\n", 
               emp[i].emp_id, emp[i].emp_name, getMonthName(emp[i].emp_month), 
               emp[i].present_day, emp[i].salary, 
               emp[i].deducted_sal, emp[i].net_sal);

        i++;
    }

    fclose(fp);
    fclose(emp_ctc);
    fclose(emp_atn);

    for (int j = 0; j < num_of_employees; j++) {
        free(emp[j].emp_name);
    }
    free(emp);

    return 0;
}

