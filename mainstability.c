#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int key;
    int original_position;
} Record;

/* Swap two records */
void swap(Record *a, Record *b)
{
    Record temp = *a;
    *a = *b;
    *b = temp;
}

/* Print records */
void printArray_19(Record arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("(%d,%d) ", arr[i].key, arr[i].original_position);
    }
    printf("\n");
}

/*BUBBLE SORT */

void bubbleSort_19(Record arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {

        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j].key > arr[j + 1].key) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

/* INSERTION SORT */
void insertionSort_19(Record arr[], int n)
{
    for (int i = 1; i < n; i++) {

        Record key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].key > key.key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

/* SELECTION SORT */
void selectionSort_19(Record arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < n; j++) {

            if (arr[j].key < arr[minIndex].key) {
                minIndex = j;
            }
        }

        swap(&arr[i], &arr[minIndex]);
    }
}

/* QUICK SORT  */
int partition(Record arr[], int low, int high)
{
    int pivot = arr[high].key;
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j].key < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

void quickSort_19(Record arr[], int low, int high)
{
    if (low < high) {

        int pi = partition(arr, low, high);

        quickSort_19(arr, low, pi - 1);
        quickSort_19(arr, pi + 1, high);
    }
}

/* MERGE SORT  */
void merge(Record arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Record L[n1];
    Record R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {

        /*
         * <= is important for stability.
         */
        if (L[i].key <= R[j].key) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort_19(Record arr[], int left, int right)
{
    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort_19(arr, left, mid);
        mergeSort_19(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* HEAP SORT  */
void heapify(Record arr[], int n, int i)
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].key > arr[largest].key)
        largest = left;

    if (right < n && arr[right].key > arr[largest].key)
        largest = right;

    if (largest != i) {

        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort_19(Record arr[], int n)
{
    /* Build max heap */
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {

        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}


void copyArray(Record destination[], Record source[], int n)
{
    memcpy(destination, source, n * sizeof(Record));
}


int checkStable(Record arr[], int n)
{
    for (int i = 0; i < n; i++) {

        for (int j = i + 1; j < n; j++) {

            if (arr[i].key == arr[j].key) {

                if (arr[i].original_position >
                    arr[j].original_position) {

                    return 0;
                }
            }
        }
    }

    return 1;
}


void demonstrate(
    Record original[],
    int n,
    void (*sortFunction)(Record[], int),
    const char *name)
{
    Record arr[MAX];

    copyArray(arr, original, n);

    printf("\n \n");
    printf("%s\n", name);
    printf("--\n");

    printf("Before sorting:\n");
    printArray_19(arr, n);

    sortFunction(arr, n);

    printf("After sorting:\n");
    printArray_19(arr, n);

    if (checkStable(arr, n))
        printf("Result for this input: STABLE\n");
    else
        printf("Result for this input: UNSTABLE\n");
}

/*
 * Wrappers for algorithms requiring different parameters
 */
void quickSortWrapper(Record arr[], int n)
{
    quickSort_19(arr, 0, n - 1);
}

void mergeSortWrapper(Record arr[], int n)
{
    mergeSort_19(arr, 0, n - 1);
}


void displayMenu()
{

    printf("       SORTING ALGORITHM MENU\n");

    printf("1. Bubble Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Selection Sort\n");
    printf("4. Quick Sort\n");
    printf("5. Merge Sort\n");
    printf("6. Heap Sort\n");
    printf("7. Display Original Array\n");
    printf("8. Exit\n");
    printf("                    \n");
    printf("Enter your choice: ");
}


int main()
{
    int n;
    int choice;

    Record original[MAX];
    Record arr[MAX];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid size.\n");
        return 1;
    }

    printf("\nEnter the elements:\n");

    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &original[i].key);


        original[i].original_position = i + 1;
    }

    do {

        displayMenu();

        scanf("%d", &choice);


        copyArray(arr, original, n);

        switch (choice) {

            case 1:

                printf("\n  BUBBLE SORT \n");

                printf("Before sorting:\n");
                printArray_19(arr, n);

                bubbleSort_19(arr, n);

                printf("After sorting:\n");
                printArray_19(arr, n);

                if (checkStable(arr, n))
                    printf("Stable for this input.\n");
                else
                    printf("Unstable for this input.\n");

                break;


            case 2:

                printf("\n INSERTION SORT \n");

                printf("Before sorting:\n");
                printArray_19(arr, n);

                insertionSort_19(arr, n);

                printf("After sorting:\n");
                printArray_19(arr, n);

                if (checkStable(arr, n))
                    printf("Stable for this input.\n");
                else
                    printf("Unstable for this input.\n");

                break;


            case 3:

                printf("\n SELECTION SORT \n");

                printf("Before sorting:\n");
                printArray_19(arr, n);

                selectionSort_19(arr, n);

                printf("After sorting:\n");
                printArray_19(arr, n);

                if (checkStable(arr, n))
                    printf("Stable for this input.\n");
                else
                    printf("Unstable for this input.\n");

                break;


            case 4:

                printf("\n QUICK SORT  \n");

                printf("Before sorting:\n");
                printArray_19(arr, n);

                quickSortWrapper(arr, n);

                printf("After sorting:\n");
                printArray_19(arr, n);

                if (checkStable(arr, n))
                    printf("Stable for this input.\n");
                else
                    printf("Unstable for this input.\n");

                break;


            case 5:

                printf("\n MERGE SORT \n");

                printf("Before sorting:\n");
                printArray_19(arr, n);

                mergeSortWrapper(arr, n);

                printf("After sorting:\n");
                printArray_19(arr, n);

                if (checkStable(arr, n))
                    printf("Stable for this input.\n");
                else
                    printf("Unstable for this input.\n");

                break;


            case 6:

                printf("\n HEAP SORT \n");

                printf("Before sorting:\n");
                printArray_19(arr, n);

                heapSort_19(arr, n);

                printf("After sorting:\n");
                printArray_19(arr, n);

                if (checkStable(arr, n))
                    printf("Stable for this input.\n");
                else
                    printf("Unstable for this input.\n");

                break;


            case 7:

                printf("\n ORIGINAL ARRAY \n");
                printArray_19(original, n);

                break;


            case 8:

                printf("\nExit program \n");
                break;


            default:

                printf("\nInvalid choice.\n");
        }

    } while (choice != 8);

    return 0;
}
