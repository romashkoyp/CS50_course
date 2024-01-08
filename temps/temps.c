// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

/*void sort_cities(void);*/

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    /*// Bubble sort algorithm
    avg_temp temp;
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        for (int j = 0; j < NUM_CITIES - i - 1; j++)
        {
            if (temps[j].temp < temps[j + 1].temp)
            {
                temp = temps[j];
                temps[j] = temps[j + 1];
                temps[j + 1] = temp;
            }
        }
    }*/

    // Selection sort algorithm
    int max;
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        max = i;
        for (int j = i + 1; j < NUM_CITIES; j++)
        {
            if (temps[j].temp > temps[max].temp)
            {
                max = j;
            }
        }
        avg_temp temp = temps[max];
        temps[max] = temps[i];
        temps[i] = temp;
    }
}

/*void merge(int start, int mid, int end)
    {
    int i, j, k;
    int left_size = mid - start + 1;
    int right_size = end - mid;

    avg_temp left[left_size], right[right_size];

    for (i = 0; i < left_size; i++) {
        left[i] = temps[start + i];
    }

    for (j = 0; j < right_size; j++) {
        right[j] = temps[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = start;

    while (i < left_size && j < right_size) {
        if (left[i].temp >= right[j].temp) {
            temps[k] = left[i];
            i++;
        } else {
            temps[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        temps[k] = left[i];
        i++;
        k++;
    }

    while (j < right_size) {
        temps[k] = right[j];
        j++;
        k++;
    }
}

void sort_cities(int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        sort_cities(start, mid);
        sort_cities(mid + 1, end);
        merge(start, mid, end);
    }
}*/