#include <stdio.h>

#define MAX 100

/* Utility Functions */

/* Return the smaller of two integers */
int min(int a, int b)
{
    return (a < b) ? a : b;
}

/* Print the array */
void printArray(int arr[], int n)
{
    printf("\nArray: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

/* Check whether the array is sorted in ascending order */
int isSorted(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return 0;
        }
    }

    return 1;
}


/* 1. Linear Search  */


int linearSearch_19(int arr[], int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }

    return -1;
}


/*2. Iterative Binary Search */



int binarySearch_19(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }

        if (arr[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}


/* 3. Recursive Binary Search */



int binarySearchRecursive_19(int arr[], int low, int high, int target)
{
    if (low > high)
    {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (arr[mid] == target)
    {
        return mid;
    }

    if (arr[mid] > target)
    {
        return binarySearchRecursive_19(
            arr,
            low,
            mid - 1,
            target
        );
    }

    return binarySearchRecursive_19(
        arr,
        mid + 1,
        high,
        target
    );
}


/*  4. Fibonacci Search */



int fibonacciSearch_19(int arr[], int n, int target)
{
    /*
       Fibonacci numbers:

       fibMm2 = F(k-2)
       fibMm1 = F(k-1)
       fibM   = F(k)
    */

    int fibMm2 = 0;
    int fibMm1 = 1;
    int fibM = fibMm2 + fibMm1;


    while (fibM < n)
    {
        fibMm2 = fibMm1;
        fibMm1 = fibM;
        fibM = fibMm2 + fibMm1;
    }


    int offset = -1;

    while (fibM > 1)
    {

        int i = min(offset + fibMm2, n - 1);

        if (arr[i] < target)
        {

            fibM = fibMm1;
            fibMm1 = fibMm2;
            fibMm2 = fibM - fibMm1;

            offset = i;
        }
        else if (arr[i] > target)
        {

            fibM = fibMm2;
            fibMm1 = fibMm1 - fibMm2;
            fibMm2 = fibM - fibMm1;
        }
        else
        {
            /* Target found. */
            return i;
        }
    }

    /* Check the last possible element */
    if (fibMm1 == 1 &&
        offset + 1 < n &&
        arr[offset + 1] == target)
    {
        return offset + 1;
    }

    return -1;
}


/* Search Result Function */


void printSearchResult_19(int index)
{
    if (index == -1)
    {
        printf("\nTarget NOT found.\n");
    }
    else
    {
        printf("\nTarget found at index: %d\n", index);
    }
}


/*  Menu */

void displayMenu()
{
    printf("\n");

    printf("          SEARCHING ALGORITHMS\n");

    printf("1. Linear Search\n");
    printf("2. Binary Search - Iterative\n");
    printf("3. Binary Search - Recursive\n");
    printf("4. Fibonacci Search\n");
    printf("5. Display Array\n");
    printf("6. Enter New Array\n");
    printf("7. Exit\n");
    printf("       \n");
    printf("Enter your choice: ");
}


int main()
{
    int arr[MAX];
    int n;
    int target;
    int choice;


    printf("Enter number of elements (1-%d): ", MAX);
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }


    printf("\nEnter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        printf("Element [%d]: ", i);
        scanf("%d", &arr[i]);
    }


    do
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
            /* Linear Search */
            case 1:

                printf("\n LINEAR SEARCH \n");

                printArray(arr, n);

                printf("Enter target element: ");
                scanf("%d", &target);

                printf("\nSearching for %d \n", target);

                int linearIndex =
                    linearSearch_19(arr, n, target);

                printSearchResult_19(linearIndex);

                printf("Time Complexity: O(n)\n");

                break;


            /*  Iterative Binary Search */
            case 2:

                printf("\n ITERATIVE BINARY SEARCH \n");

                if (!isSorted(arr, n))
                {
                    printf("\nError: Binary Search requires "
                           "a sorted array.\n");

                    printf("Please enter a sorted array "
                           "or use option 6.\n");

                    break;
                }

                printArray(arr, n);

                printf("Enter target element: ");
                scanf("%d", &target);

                printf("\nSearching for %d...\n", target);

                int binaryIndex =
                    binarySearch_19(arr, n, target);

                printSearchResult_19(binaryIndex);

                printf("Time Complexity: O(log n)\n");

                break;


            /* Recursive Binary Search */
            case 3:

                printf("\n RECURSIVE BINARY SEARCH \n");

                if (!isSorted(arr, n))
                {
                    printf("\nError: Binary Search requires "
                           "a sorted array.\n");

                    printf("Please enter a sorted array "
                           "or use option 6.\n");

                    break;
                }

                printArray(arr, n);

                printf("Enter target element: ");
                scanf("%d", &target);

                printf("\nSearching for %d...\n", target);

                int recursiveIndex =
                    binarySearchRecursive_19(
                        arr,
                        0,
                        n - 1,
                        target
                    );

                printSearchResult_19(recursiveIndex);

                printf("Time Complexity: O(log n)\n");
                printf("Space Complexity: O(log n)\n");

                break;


            /* Fibonacci Search */
            case 4:

                printf("\n  FIBONACCI SEARCH \n");

                if (!isSorted(arr, n))
                {
                    printf("\nError: Fibonacci Search requires "
                           "a sorted array.\n");

                    printf("Please enter a sorted array "
                           "or use option 6.\n");

                    break;
                }

                printArray(arr, n);

                printf("Enter target element: ");
                scanf("%d", &target);

                printf("\nSearching for %d...\n", target);

                int fibonacciIndex =
                    fibonacciSearch_19(arr, n, target);

                printSearchResult_19(fibonacciIndex);

                printf("Time Complexity: O(log n)\n");

                break;


            /* Display Array  */
            case 5:

                printf("\n CURRENT ARRAY  \n");

                printArray(arr, n);

                if (isSorted(arr, n))
                {
                    printf("Status: SORTED\n");
                }
                else
                {
                    printf("Status: NOT SORTED\n");
                }

                break;


            /* Enter New Array */
            case 6:

                printf("\n ENTER NEW ARRAY \n");

                printf("Enter number of elements (1-%d): ", MAX);
                scanf("%d", &n);

                if (n <= 0 || n > MAX)
                {
                    printf("Invalid number of elements.\n");
                    break;
                }

                printf("\nEnter %d elements:\n", n);

                for (int i = 0; i < n; i++)
                {
                    printf("Element [%d]: ", i);
                    scanf("%d", &arr[i]);
                }

                printf("\nNew array stored successfully.\n");

                printArray(arr, n);

                break;


            case 7:

                printf("\nExiting program \n");
                break;


            /*  Invalid Choice*/
            default:

                printf("\nInvalid choice!\n");
                printf("Please select a number from 1 to 7.\n");

                break;
        }

    } while (choice != 7);

    return 0;
}
