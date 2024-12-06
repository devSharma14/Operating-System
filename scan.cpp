#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    printf("Enter n : ");
    cin >> n;
    vector<int> arr;
    int index = 0;
    printf("Enter the array : ");
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        arr.push_back(num);
    }
    float head = 0;
    printf("Enter the initial head point : ");
    cin >> head;
    vector<int> left, right;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] < head)
        {
            left.push_back(arr[i]);
        }
        else
        {
            right.push_back(arr[i]);
        }
    }
    int sum = 0;
    int direction = 0;
    printf("Enter direction (0 for left and 1 for right) : ");
    scanf("%d", &direction);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    reverse(left.begin(), left.end());
    if (direction == 0)
    {
        for (int i = 1; i < left.size(); i++)
        {
            sum += abs(head - left[i]);
            head = left[i];
        }
        sum += abs(0 - head);
        head = 0;
        for (int i = 0; i < right.size(); i++)
        {
            sum += abs(head - right[i]);
            head = right[i];
        }
    }
    else
    {
        for (int i = 1; i < right.size(); i++)
        {
            sum += abs(head - right[i]);
            head = right[i];
        }
        sum += abs(199 - head);
        head = 199;
        for (int i = 0; i < left.size(); i++)
        {
            sum += abs(head - left[i]);
            head = left[i];
        }
    }
    printf("Sum : %d \n", sum);
}