#include <bits/stdc++.h>
using namespace std;

int knapsack(int W, int weight[], int value[], int N){
    if(N==0 || W==0)
        return 0;

    if(weight[N-1] > W){
        return knapsack(W, weight, value, N-1); // exclude current weight
    }

    int included = knapsack(W-weight[N-1], weight, value, N-1); // include current weight
    int excluded = knapsack(W, weight, value, N-1); // exclude
    return max(included+value[N-1], excluded);
}

int knapsack_tabulation(int W, int weight[], int value[], int N){
    int table[N+1][W+1];

    for(int i=0; i<=N; i++) table[i][0] = 0;
    for(int i=0; i<=W; i++) table[0][i] = 0;

    for(int i=1; i<=N; i++){
        for(int w=1; w<=W; w++) {
            if(weight[i-1] >= w){
                table[i][w] = max(table[i-1][w], table[i-1][w-weight[i-1]]+value[i-1]);
            }else{
                table[i][w] = table[i-1][w];
            }
        }
    }
}

