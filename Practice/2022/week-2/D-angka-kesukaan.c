/**
 * fundamental code written by : Bayu Laksana
 * @date 2019-02-29
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-03-22
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(){
    int n;
    int min = 1001, index = 0;
    scanf("%d", &n);
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d", &arr[i]);
        // determine the minimum value of array while insert it
        // and determine the index of minimum value
        if(arr[i] < min){
            min = arr[i];
            index = i;
        }
    }
    int t;
    scanf("%d", &t);
    int command, x, y, temp_min;
    while(t--){
        scanf("%d", &command);
        scanf("%d %d", &x, &y);
        switch(command){
            case 1:
                arr[x] = y;
                /**
                 * if y is smaller than minimum value, change the minimum value with y,
                 * and change the index of minimum value with x
                 */
                if(y < min){
                    min = y;
                    index = x;
                }
                /**
                 * if x equal to index of minimum value, 
                 * check the array again to get the minimum value,
                 * and index of the minimum value
                 */
                else if(x==index){
                    min = arr[x];
                    for(int i=0;i<n;i++){
                        if(arr[i] < min){
                            min = arr[i];
                            index = i;    
                        }
                    }
                }
            break;
            default: // 2
                /**
                 * if index of minimum value is in range x and y,
                 * print the minimum value
                 */
                if(x <= index && index <= y)
                    printf("%d\n", min);
                /**
                 * else, set the arr[x] to temporary variable (temp_min)
                 * check the array again to get the minimum value,
                 * with looping started from indexArray = x, until indexArray = y
                 */
                else{
                    temp_min = arr[x];
                    for(int j=x;j<=y;j++){
                        if(arr[j] < temp_min)
                            temp_min = arr[j];
                    }
                    printf("%d\n", temp_min);
                }
            break;
        }
    }
    return 0;
}