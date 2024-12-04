#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter the no of cylinders : ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the cylinder array : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int entryPoint = 0;
    printf("Enter the RW entry point : ");
    scanf("%d", &entryPoint);
    int ans = 0;
    ans += abs(entryPoint - arr[0]);
    for (int i = 1; i < n; i++)
    {
        ans += abs(arr[i] - arr[i - 1]);
    }
    printf("Result: %d \n", ans);
    printf("Average seek time: %.2f \n", (float)ans / n);

    return 0;
}