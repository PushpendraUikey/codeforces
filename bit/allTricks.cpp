#include <bits/stdc++.h>
using namespace std;

/*
Bitwise &:
both bits 1 then sets it to 1 otherwise set it to 0.

Bitwise |:
one of the bit is 1 set it to 1 otherwise set it to 0.

Bitwise ^:
one of the bit is set then set it to 1 otherwise keep it 0.

Bitwise ~:
flip all the bits of a the given number.

Left Shift <<:
shift all bits by n positions to the left and append zero at the end. Multiplication by 2's powers

Right Shift >>:
shift all bits to right by n positions and append zero at the beginning. Division by 2's powers.

If you need a bigger number you need to use 1LL instead of 1 which is int.
*/

bool useBuiltIn = false;

bool is_Even(int x){
    return !(x & 1);
}

bool is_Set(int x, int k) {
    return ( (x>>k) & 1 ) || ( x & (1<<k) );
}

void iterate_Bits(int x) {
    for (int i=31; i>=0; i--) {
        cout << ((x>>i) & 1) << ' ';
    }
    cout << '\n';
}

int count_Set_Bits(int x) {
    if(useBuiltIn) return __builtin_popcount(x);
    int cnt = 0;
    while(x) {
        cnt += (x&1);
        x >>= 1;
    }
    return cnt;
}

int count_Set_Bits_eff(int x) {
    if(useBuiltIn) return __builtin_popcount(x);
    int cnt = 0;
    while(x) {
        x = x & (x-1);
        cnt++;
    }
}

int set_Bit(int x, int k) {
    return (x | 1<<k);
}

int clear_Bit(int x, int k) {
    return (x & ~(1<<k));
}

int toggle_Bit(int x, int k) {
    return (x ^ (1<<k));
}

int multiply_By_2(int x, int k) {
    return (x<<k);
}

int divide_By_2(int x, int k) {
    return (x>>k);
}

int remove_Lowest_Set_Bit(int x) {
    return (x & (x-1));
}

int lowest_Set_Bit(int x) {
    return (x & (-x));
}

int count_Leading_Zero(int x) {
    if(useBuiltIn) {
        return __builtin_clz(x);
    }
    int cnt = 0;
    while(x) {
        cnt++;
        x >>= 1;
    }
    return 31-cnt;
}

int count_Trailing_Zero(int x) {
    if(useBuiltIn) {
        return __builtin_ctz(x);
    }
    int cnt = 0;
    while(cnt < 32 && !(x&1)){
        cnt++;
        x >>= 1;
    }
    return cnt;
}

int highest_Set_Bit_Position(int x) {
    if(useBuiltIn) {
        return 31 - __builtin_clz(x);
    }
    for (int k=31; k>=0; k--) {
        if((x>>k) & 1) {
            return k;
        }
    }
    return -1;
}

bool is_Power_Of_2(int x) {
    return (x>0) && !(x & (x-1));
}

int unique_Element(vector<int>& a) {
    int ele=0;
    for( auto e : a ) {
        ele = ele ^ e;
    }
    return ele;
}

void generate_Subsets(vector<int>& a) {
    int n = a.size();
    for (int mask=0; mask < (1<<n); mask++) {
        for(int i=0; i<n; i++) {
            if( (mask >> i) & 1 ) {
                cout << a[i] << ' ';
            }
        }
        cout << '\n';
    }
}