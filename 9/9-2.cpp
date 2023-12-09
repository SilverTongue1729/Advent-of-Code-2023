#include <stdio.h>

int solve(long long int arr[],int n){
       long long int value = 0;
       long long int sub[n-1];
         for(int j = 0; j < n-1; j++){
              sub[j] = arr[j+1]-arr[j];
         }
         int flag = 1;
            for(int j = 0; j < n-2; j++){
                if(sub[j]!=0 ){
                    flag = 0;
                    break;
                }
            }
          if(flag){
             return 0;
         }
         else{
                value = sub[0] - solve(sub, n-1);
                printf("%lld\n", value);
            return value;
         }

}


int main(){
    long long int arr[200][21];
    for(int i = 0; i < 200; i++){
        for(int j = 0; j < 21; j++){
            scanf("%lld", &arr[i][j]);
        }
    }
    long long int ans = 0;
    for(int i=0;i<200;i++){
        long long int val = arr[i][0]-solve(arr[i],21);
         ans += val;
         printf("%lld\n", val);
         printf("%lld\n", arr[i][20]);

        printf("%lld\n", ans);
    }
    printf("%lld\n", ans);
}
