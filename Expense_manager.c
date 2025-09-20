#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// getting week of day it returns number.
// 1 -> monday
// 2 -> tuesday
// 3 -> wednesday
// 4 -> thursday
// 5 -> friday
// 6 -> saturday
// 7 -> sunday
int get_week_of_day(int month, int year)
{
    struct tm t = {0};
    t.tm_mday = 1;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;

    mktime(&t);
    int wday = t.tm_wday;
    if (wday == 0)
        return 7;
    return wday;
}

// structure of expense.
struct expense
{
    char date[20];
    int money;
    char catagory[50];
    char Description[200];
};
int expense_count; // expense count for last number of entry
int main()
{
    int choice;
    printf("Welcome to Expense manager.");
    while (1) // infinite loop.
    {
        printf("\n=====================================================\n");
        printf("Choose From following option: \n");
        printf("1.Add new Expense\n");
        printf("2.View all Expense\n");
        printf("3.Edit Entry\n");
        printf("4.Delete Entry\n");
        printf("5.Total Expenses\n");
        printf("6.Filter month Expenses\n");
        printf("7.Filter catagory Expenses\n");
        printf("8.Make a monthly expense report\n");
        printf("9.Save and Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice); // choice filled by user.
        getchar();
        printf("\n=====================================================\n");

        if (choice == 1)
        {
            Add_Expense();
        }
        if (choice == 2)
        {
            View_Expense();
        }
        if (choice == 3)
        {
            View_Expense();
            Edit_Expense();
        }
        if (choice == 4)
        {
            View_Expense();
            Delete_Expnese();
        }
        if (choice == 5)
        {
            Total_Expense();
        }
        if (choice == 6)
        {
            Filter_Monthly_Expense();
        }
        if (choice == 7)
        {
            Filter_Catagory_Expense();
        }
        if (choice == 8)
        {
            Monthly_Full_Expense();
        }
        if (choice == 9)
        {
            printf("Thank You for using this!");
            return 0;
        }
    }
    return 0;
}

void Add_Expense()
{
    FILE *fr = fopen("expense.csv", "r"); // reading expense.csv for number of expense entry.
    struct expense expenses[100]; // making expenses arry of 100 to store data.
    char line[200]; // temorary string to store strings
    expense_count = 0; // By default expense_count.
    while (fgets(line, sizeof(line), fr)) // fgets give true if it gets string from fr and store it in line string length will be sizeof(line).
    {
        if (sscanf(line, "%19[^,],%49[^,],%99[^,],%d", &expenses[expense_count].date, &expenses[expense_count].catagory, &expenses[expense_count].Description, &expenses[expense_count].money) == 4) // ssscanf will read line as given formate and seprate it with , then gives them string and integer variables.
        {
            expense_count++; // expense count stop at last entry then expense_count give us new entry number
        }
    }
    fclose(fr);

    printf("Enter date of expense:(dd-mm-yyyy)\n");
    fgets(expenses[expense_count].date, sizeof(expenses[expense_count].date), stdin); // this will get string and store it in expenes[e_c].date stdin represent keyboard input.
    expenses[expense_count].date[strcspn(expenses[expense_count].date, "\n")] = '\0'; //This will remove last \n from fget and add null charachter \0.
    printf("Enter catagory of expense:(Food/Shopping/Auto)\n");
    fgets(expenses[expense_count].catagory, sizeof(expenses[expense_count].catagory), stdin);
    expenses[expense_count].catagory[strcspn(expenses[expense_count].catagory, "\n")] = '\0';
    printf("Enter description of expense:\n");
    fgets(expenses[expense_count].Description, sizeof(expenses[expense_count].Description), stdin);
    expenses[expense_count].Description[strcspn(expenses[expense_count].Description, "\n")] = '\0';
    printf("Enter money payed in expense:\n");
    char moneyStr[20]; // making string to store money
    fgets(moneyStr, sizeof(moneyStr), stdin);
    expenses[expense_count].money = atoi(moneyStr); // making money string a integer and giveing value to expenses arry.

    FILE *fw = fopen("expense.csv", "a"); //now appending file of new entry.
    fprintf(fw, "%s,%s,%s,%d\n", expenses[expense_count].date, expenses[expense_count].catagory, expenses[expense_count].Description, expenses[expense_count].money); //This will add new entry of expense in file in format of ,(comma) sepration (csv).
    fclose(fw);
    printf("expense added sucessfully");
}

void View_Expense()
{
    FILE *fr = fopen("expense.csv", "r"); // again reading file and storing entry in expenes arry with last count as expense_count.
    struct expense expenses[100];
    char line[200];
    expense_count = 0;
    while (fgets(line, sizeof(line), fr))
    {
        if (sscanf(line, "%19[^,],%49[^,],%99[^,],%d", &expenses[expense_count].date, &expenses[expense_count].catagory, &expenses[expense_count].Description, &expenses[expense_count].money) == 4)
        {
            expense_count++;
        }
    }
    fclose(fr);
    // printing in console with good format to look.
    printf("\n------------------------------------------------------------\n");
    printf("%-2s | %-12s | %-12s | %-25s | %-5s", "No", "DATE", "Catagory", "Description", "Amount");
    printf("\n------------------------------------------------------------\n");
    for (int i = 0; i < expense_count; i++)
    {
        printf("%d | %-12s | %-12s | %-25s | %d \n", i, expenses[i].date, expenses[i].catagory, expenses[i].Description, expenses[i].money);
    }
}

void Edit_Expense()
{
    FILE *fr = fopen("expense.csv", "r"); // same thing opening and reading file for entries
    struct expense expenses[100];
    char line[200];
    expense_count = 0;
    while (fgets(line, sizeof(line), fr))
    {
        if (sscanf(line, "%19[^,],%49[^,],%99[^,],%d", &expenses[expense_count].date, &expenses[expense_count].catagory, &expenses[expense_count].Description, &expenses[expense_count].money) == 4)
        {
            expense_count++;
        }
    }
    fclose(fr);
    FILE *tw = fopen("temp.csv", "a"); //now making temp.csv file and storing entry
    int id;
    printf("Enter Index you want to Edit: ");
    scanf("%d", &id);

    for (int i = 0; i < expense_count; i++)
    {
        if (i == id)
        {
            // Asking user for waht to change and storing it in a variable
            printf("current data is:\n");
            printf("%d | %-12s | %-12s | %-25s | %d \n", i, expenses[i].date, expenses[i].catagory, expenses[i].Description, expenses[i].money);
            printf("Which part you want to edit\n");
            printf("1.date\n");
            printf("2.catagory\n");
            printf("3.description\n");
            printf("4.money\n");
            int change_choice;
            char new_date[20];
            char new_catagory[50];
            char new_description[200];
            int new_money;
            printf("Your choice: ");
            scanf("%d", &change_choice);
            if (change_choice == 1)
            {
                printf("Enter new date: ");
                fgets(new_date, sizeof(new_date), stdin);
                new_date[strcspn(new_date, "\n")] = '\0';
                fprintf(tw, "%s,%s,%s,%d\n", new_date, expenses[i].catagory, expenses[i].Description, expenses[i].money); // printing changed part.
            }
            if (change_choice == 2)
            {
                printf("Enter new catagory:(Food/Shopping/Auto) ");
                fgets(new_catagory, sizeof(new_catagory), stdin);
                new_catagory[strcspn(new_catagory, "\n")] = '\0';
                fprintf(tw, "%s,%s,%s,%d\n", expenses[i].date, new_catagory, expenses[i].Description, expenses[i].money); // printing changed part.
            }
            if (change_choice == 3)
            {
                printf("Enter new description: ");
                fgets(new_description, sizeof(new_description), stdin);
                new_description[strcspn(new_description, "\n")] = '\0';
                fprintf(tw, "%s,%s,%s,%d\n", expenses[i].date, expenses[i].catagory, new_description, expenses[i].money); // printing changed part.
            }
            if (change_choice == 4)
            {
                printf("Enter new money payed: ");
                scanf("%d", &new_money);
                fprintf(tw, "%s,%s,%s,%d\n", expenses[i].date, expenses[i].catagory, expenses[i].Description, new_money); // printing changed part.
            }
            continue; // skipping loop.
        }
        fprintf(tw, "%s,%s,%s,%d\n", expenses[i].date, expenses[i].catagory, expenses[i].Description, expenses[i].money); // printing unchanged part.
    }
    fclose(tw);
    remove("expense.csv"); //removing old file
    rename("temp.csv", "expense.csv"); //making temp file as main file
}

void Delete_Expnese()
{
    FILE *fr = fopen("expense.csv", "r"); // reading expense file.
    struct expense expenses[100];
    char line[200];
    expense_count = 0;
    while (fgets(line, sizeof(line), fr))
    {
        if (sscanf(line, "%19[^,],%49[^,],%99[^,],%d", &expenses[expense_count].date, &expenses[expense_count].catagory, &expenses[expense_count].Description, &expenses[expense_count].money) == 4)
        {
            expense_count++;
        }
    }
    fclose(fr);
    FILE *tw = fopen("temp.csv", "a");
    int id;
    printf("Enter Index you want to Edit: ");
    scanf("%d", &id);

    for (int i = 0; i < expense_count; i++)
    {
        if (i == id)
        {
            printf("current data is:\n");
            printf("%d | %-12s | %-12s | %-25s | %d \n", i, expenses[i].date, expenses[i].catagory, expenses[i].Description, expenses[i].money);
            printf("Are you sure you want to delete it?[y/n]\n");
            char del_confirm;
            printf("Your choice: ");
            scanf(" %c", &del_confirm);
            if (del_confirm == 'y')
            {
                continue; // not printing part that user dant want.
            }
        }
        fprintf(tw, "%s,%s,%s,%d\n", expenses[i].date, expenses[i].catagory, expenses[i].Description, expenses[i].money); // printing unchanged part.
    }
    fclose(tw);
    remove("expense.csv"); // removing old file
    rename("temp.csv", "expense.csv"); // making temp file as main file.
}

void Total_Expense()
{
    FILE *fr = fopen("expense.csv", "r"); // reading file
    struct expense expenses[100];
    char line[200];
    expense_count = 0;
    while (fgets(line, sizeof(line), fr))
    {
        if (sscanf(line, "%19[^,],%49[^,],%99[^,],%d", &expenses[expense_count].date, &expenses[expense_count].catagory, &expenses[expense_count].Description, &expenses[expense_count].money) == 4)
        {
            expense_count++;
        }
    }
    fclose(fr);
    //printing file in a good way.
    int Total_Value = 0;
    printf("\n------------------------------------------------------------\n");
    printf("%-2s | %-12s | %-12s | %-25s | %-5s", "No", "DATE", "Catagory", "Description", "Amount");
    printf("\n------------------------------------------------------------\n");
    for (int i = 0; i < expense_count; i++)
    {
        printf("%d | %-12s | %-12s | %-25s | %d \n", i, expenses[i].date, expenses[i].catagory, expenses[i].Description, expenses[i].money);
        Total_Value += expenses[i].money;
    }
    printf("The Total amout of Expense is %d\n", Total_Value);
}

void Filter_Monthly_Expense()
{
    FILE *fr = fopen("expense.csv", "r"); // reading file
    struct expense expenses[100];
    struct date // defining struct for date to filter
    {
        int day, month, year;
    };
    struct date d[100]; // making d arry with date structure.
    char line[200];
    expense_count = 0;
    while (fgets(line, sizeof(line), fr))
    {
        if (sscanf(line, "%19[^,],%49[^,],%99[^,],%d", &expenses[expense_count].date, &expenses[expense_count].catagory, &expenses[expense_count].Description, &expenses[expense_count].money) == 4)
        {
            expense_count++;
        }
    }
    fclose(fr);
    int Total_month_money = 0;
    printf("Enter month you want to filter: ");
    int filtering_month;
    scanf("%d", &filtering_month); // month filter user want to check.
    for (int i = 0; i < expense_count; i++) // checking i to expense_count for date to match here i is index of entry taking from our expenses arry.
    {
        sscanf(expenses[i].date, "%2d-%2d-%4d", &d[i].day, &d[i].month, &d[i].year); // this will devide date string into 3 integer of day,month,year.

        if (filtering_month == d[i].month) // matching day to filtering month.
        {
            printf("%d | %-12s | %-12s | %-25s | %d \n", i, expenses[i].date, expenses[i].catagory, expenses[i].Description, expenses[i].money); // printing all result of month user want
            Total_month_money += expenses[i].money; // increasing total of filtering month.
        }
    }
    printf("Total Monthly Expense is: %d", Total_month_money);
}

void Filter_Catagory_Expense()
{
    FILE *fr = fopen("expense.csv", "r"); // reading file.
    struct expense expenses[100];
    char line[200];
    expense_count = 0;
    while (fgets(line, sizeof(line), fr))
    {
        if (sscanf(line, "%19[^,],%49[^,],%99[^,],%d", &expenses[expense_count].date, &expenses[expense_count].catagory, &expenses[expense_count].Description, &expenses[expense_count].money) == 4)
        {
            expense_count++;
        }
    }
    fclose(fr);
    int Total_catagory_money = 0;
    printf("Enter catagory you want to filter: (Food/Shopping/Auto) ");
    char filter_catagory[50];
    fgets(filter_catagory, sizeof(filter_catagory), stdin); // filtering through catagory.
    filter_catagory[strcspn(filter_catagory, "\n")] = '\0';
    for (int i = 0; i < expense_count; i++)
    {
        if (strcmp(filter_catagory, expenses[i].catagory) == 0) // comparing catagory filter and all expense for that catagory.
        {
            printf("%d", i);
            printf("%d | %-12s | %-12s | %-25s | %d \n", i, expenses[i].date, expenses[i].catagory, expenses[i].Description, expenses[i].money);
            Total_catagory_money += expenses[i].money;
        }
    }
    printf("Total Catagory Expense is: %d", Total_catagory_money);
}

void Monthly_Full_Expense()
{
    FILE *fr = fopen("expense.csv", "r"); //reading file
    struct expense expenses[100];
    struct date
    {
        int day, month, year;
    };
    struct date d[100];
    char line[200];
    expense_count = 0;
    while (fgets(line, sizeof(line), fr))
    {
        if (sscanf(line, "%19[^,],%49[^,],%99[^,],%d", &expenses[expense_count].date, &expenses[expense_count].catagory, &expenses[expense_count].Description, &expenses[expense_count].money) == 4)
        {
            expense_count++;
        }
    }
    fclose(fr);
    int Filter_month, Filter_year; //using month and year filter to get filter month for making report
    printf("Enter month,year: ");
    scanf("%d,%d", &Filter_month, &Filter_year);
    int w = get_week_of_day(Filter_month, Filter_year); // whis will give what is w(day) at date 1-month-year.
    // defining total of catagory and grand total arry with default value 0.
    int weekly_Total[5] = {0, 0, 0, 0, 0};
    int Food_weekly_Total[5] = {0, 0, 0, 0, 0};
    int Shopping_weekly_Total[5] = {0, 0, 0, 0, 0};
    int Auto_weekly_Total[5] = {0, 0, 0, 0, 0};
    // week calculator according to date
    // week-1: 0 to 7-w
    // week-2: 8-w to 14-w
    // week-3: 15-w to 21-w
    // week-4: 23-w to 28-w
    // week-5: 29-w to 35-w
    for (int i = 0; i < expense_count; i++) // this will devide date string into day,month,year format with integert entry in date structure.
    {
        sscanf(expenses[i].date, "%2d-%2d-%4d", &d[i].day, &d[i].month, &d[i].year);
    }
    for (int i = 0; i < 32; i++) // this will go i for 1 to 31 to check date.
    {
        for (int j = 0; j < expense_count; j++) // j is index number for expenses arry which will give all entry one by one.
        {
            if (i == d[j].day) // checking if day[j] is equal to i(date).
            {
                if (0 <= i && i <= 7 - w) //week 1 condition
                {
                    weekly_Total[0] += expenses[j].money;
                    if (strcmp(expenses[j].catagory, "Food") == 0)
                    {
                        Food_weekly_Total[0] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Shopping") == 0)
                    {
                        Shopping_weekly_Total[0] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Auto") == 0)
                    {
                        Auto_weekly_Total[0] += expenses[j].money;
                    }
                }
                if (7 - w <= i && i <= 14 - w) //week 2 condition
                {
                    weekly_Total[1] += expenses[j].money;
                    if (strcmp(expenses[j].catagory, "Food") == 0)
                    {
                        Food_weekly_Total[1] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Shopping") == 0)
                    {
                        Shopping_weekly_Total[1] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Auto") == 0)
                    {
                        Auto_weekly_Total[1] += expenses[j].money;
                    }
                }
                if (15 - w <= i && i <= 21 - w) //week 3 condition
                {
                    weekly_Total[2] += expenses[j].money;
                    if (strcmp(expenses[j].catagory, "Food") == 0)
                    {
                        Food_weekly_Total[2] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Shopping") == 0)
                    {
                        Shopping_weekly_Total[2] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Auto") == 0)
                    {
                        Auto_weekly_Total[2] += expenses[j].money;
                    }
                }
                if (22 - w <= i && i <= 28 - w) //week 4 condition
                {
                    weekly_Total[3] += expenses[j].money;
                    if (strcmp(expenses[j].catagory, "Food") == 0)
                    {
                        Food_weekly_Total[3] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Shopping") == 0)
                    {
                        Shopping_weekly_Total[3] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Auto") == 0)
                    {
                        Auto_weekly_Total[3] += expenses[j].money;
                    }
                }
                if (29 - w <= i && i <= 35 - w) //week 5 condition
                {
                    weekly_Total[4] += expenses[j].money;
                    if (strcmp(expenses[j].catagory, "Food") == 0)
                    {
                        Food_weekly_Total[4] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Shopping") == 0)
                    {
                        Shopping_weekly_Total[4] += expenses[j].money;
                    }
                    if (strcmp(expenses[j].catagory, "Auto") == 0)
                    {
                        Auto_weekly_Total[4] += expenses[j].money;
                    }
                }
            }
        }
    }
    // writing report in console.
    printf("---Week:1---\n");
    printf("Food: %d\n", Food_weekly_Total[0]);
    printf("Shopping: %d\n", Shopping_weekly_Total[0]);
    printf("Auto: %d\n", Auto_weekly_Total[0]);
    printf("Total Week expense: %d\n", weekly_Total[0]);
    printf("---Week:2---\n");
    printf("Food: %d\n", Food_weekly_Total[1]);
    printf("Shopping: %d\n", Shopping_weekly_Total[1]);
    printf("Auto: %d\n", Auto_weekly_Total[1]);
    printf("Total Week expense: %d\n", weekly_Total[1]);
    printf("---Week:3---\n");
    printf("Food: %d\n", Food_weekly_Total[2]);
    printf("Shopping: %d\n", Shopping_weekly_Total[2]);
    printf("Auto: %d\n", Auto_weekly_Total[2]);
    printf("Total Week expense: %d\n", weekly_Total[2]);
    printf("---Week:4---\n");
    printf("Food: %d\n", Food_weekly_Total[3]);
    printf("Shopping: %d\n", Shopping_weekly_Total[3]);
    printf("Auto: %d\n", Auto_weekly_Total[3]);
    printf("Total Week expense: %d\n", weekly_Total[3]);
    printf("---Week:5---\n");
    printf("Food: %d\n", Food_weekly_Total[4]);
    printf("Shopping: %d\n", Shopping_weekly_Total[4]);
    printf("Auto: %d\n", Auto_weekly_Total[4]);
    printf("Total Week expense: %d\n", weekly_Total[4]);
    int Food_total, Shopping_total, Auto_total, Total;
    float avrg_Food, avrg_Shopping, avrg_Auto;
    float avrg_week;
    //mathematics time.
    Food_total = Food_weekly_Total[0] + Food_weekly_Total[1] + Food_weekly_Total[2] + Food_weekly_Total[3] + Food_weekly_Total[4];
    Shopping_total = Shopping_weekly_Total[0] + Shopping_weekly_Total[1] + Shopping_weekly_Total[2] + Shopping_weekly_Total[3] + Shopping_weekly_Total[4];
    Auto_total = Auto_weekly_Total[0] + Auto_weekly_Total[1] + Auto_weekly_Total[2] + Auto_weekly_Total[3] + Auto_weekly_Total[4];

    avrg_Food = (float)(Food_weekly_Total[0] + Food_weekly_Total[1] + Food_weekly_Total[2] + Food_weekly_Total[3] + Food_weekly_Total[4]) / 5;
    avrg_Shopping = (float)(Shopping_weekly_Total[0] + Shopping_weekly_Total[1] + Shopping_weekly_Total[2] + Shopping_weekly_Total[3] + Shopping_weekly_Total[4]) / 5;
    avrg_Auto = (float)(Auto_weekly_Total[0] + Auto_weekly_Total[1] + Auto_weekly_Total[2] + Auto_weekly_Total[3] + Auto_weekly_Total[4]) / 5;

    Total = weekly_Total[0] + weekly_Total[1] + weekly_Total[2] + weekly_Total[3] + weekly_Total[4];
    avrg_week = (float)Total / (float)5;
    // agian printing grand total.
    printf("Week Total\n");
    printf("Food: %d\n", Food_total);
    printf("Shopping: %d\n", Shopping_total);
    printf("Auto: %d\n", Auto_total);
    printf("Total: %d\n", Total);
    printf("Averages\n");
    printf("Food-averg: %.2f\n", avrg_Food);
    printf("Shopping-averg: %.2f\n", avrg_Shopping);
    printf("Auto-averg: %.2f\n", avrg_Auto);
    printf("weekly-averg: %.2f\n", avrg_week);
}
