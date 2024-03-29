#include <iostream>
#include <vector>
using namespace std;

// Returns split point. If not possible, then
// return -1.
int findSplitPoint(int arr[], int n)
{
    int leftSum = 0 ;
  
    // traverse array element
    for (int i = 0; i < n; i++)
    {
        // add current element to left Sum
        leftSum += arr[i] ;
  
        // find sum of rest array elements (rightSum)
        int rightSum = 0 ;
        for (int j = i+1 ; j < n ; j++ )
            rightSum += arr[j] ;
  
        // split point index
        if (leftSum == rightSum)
            return i+1 ;
    }
  
    // if it is not possible to split array into
    // two parts
    return -1;
}
  
// Prints two parts after finding split point using
// findSplitPoint()
void printTwoParts(int arr[], int n)
{
    int splitPoint = findSplitPoint(arr, n);
  
    if (splitPoint == -1 || splitPoint == n )
    {
        cout << "Not Possible" <<endl;
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if(splitPoint == i)
            cout << endl;
        cout << arr[i] << " " ;
    }
}
  
// driver program
int main()
{
    for(int i =0;i < 3;i++){
        cout << i << " ";
    }
    return 0;
}