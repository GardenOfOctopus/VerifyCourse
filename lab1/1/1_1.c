#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define add_crashes(a, b) \
    (a > INT_MAX || a < INT_MIN || \
    b > INT_MAX || b < INT_MIN || \
    a + b > INT_MAX || a + b < INT_MIN)

#define sub_crashes(a, b) \
    (a > INT_MAX || a < INT_MIN || \
    b > INT_MAX || b < INT_MIN || \
    a - b > INT_MAX || a - b < INT_MIN) 


void funP1(int64_t x1, int64_t x2, int64_t x3, int64_t * z1){
    int64_t y1 = 0;

    y1 = x1 - x3;
    if sub_crashes(x1, x3) while(1);

    y1 = y1 + x2;
    if add_crashes(y1, x2) while(1);

    *z1 = y1;
}

void x1x2(int64_t y1, int64_t x1, int64_t x2, int64_t x3, int64_t * z1){ //x1x2
    y1 = x1 + x2;
    if add_crashes(x1, x2) while(1);

    y1 = y1 - x3;
    if sub_crashes(y1, x3) while(1);

    *z1 = y1;
    return;
}

void x1x3(int64_t y1, int64_t x1, int64_t x2, int64_t x3, int64_t * z1){ //x1x3

    y1 = x1 - x3;
    if sub_crashes(x1, x3) while(1);

    y1 = y1 + x2;
    if add_crashes(y1, x2) while(1);

    *z1 = y1;
    return;
}

//((x1 > 0 && x2 > 0 && not sub_crashes(INT_MAX, x1) &&  || x1 < 0 && x2 < 0 && not sub_crashes(INT_MIN, x1) || x1 <= 0 && x2 >= 0 || x1 >= 0 && x2 <= 0) && not add_crashes(x1, x2) && not sub_crashes(x1 + x2, x3)) || 

//x1 > 0 && x3 < 0 && sub_crashes(x1, INT_MAX) || x1 < 0 && x3 > 0 && add_crashes(INT_MIN, x3) || 

//(b1_1 || b1_2 || b1_3)

void funP2(int64_t x1, int64_t x2, int64_t x3, int64_t * z1){
    int64_t y1, y2 = 0;

    if (x1 > 0 && x2 > 0){ // b1_1
        y1 = INT_MAX - x1;
        if sub_crashes(INT_MAX, x1) while(1);

        if (y1 >= x2){
            x1x2(y1, x1, x2, x3, z1);
            return;
        }
    } 
    if (x1 < 0 && x2 < 0){ // b1_2
        y1 = x1 - INT_MIN;
        if sub_crashes(INT_MIN, x1) while(1);

        if (y1 >= x2){
            x1x2(y1, x1, x2, x3, z1);
            return;
        }
    }
    if (x1 <= 0 && x2 >= 0 || x1 >= 0 && x2 <= 0){ // b1_3
        x1x2(y1, x1, x2, x3, z1);
        return;
    }

    if (x1 > 0 && x3 < 0){ // b2_1
        y1 = x1 - INT_MAX;
        if sub_crashes(x1, INT_MAX) while(1);

        if (y1 <= x3){
            x1x3(y1, x1, x2, x3, z1);
            return;
        }
    } 
    if (x1 < 0 && x3 > 0){ // b2_2
        y1 = INT_MIN + x3;
        if add_crashes(INT_MIN, x3) while(1);

        if (y1 <= x1){
            x1x3(y1, x1, x2, x3, z1);
            return;
        }
    }
    if (x1 <= 0 && x3 <= 0 || x1 >= 0 && x3 >= 0){ // b2_3
        x1x3(y1, x1, x2, x3, z1);
        return;
    }

    // b3_0
    y1 = x2 - x3; 
    if sub_crashes(x2, x3) while(1);

    y1 = y1 + x1;
    if add_crashes(y1, x1) while(1);

    *z1 = y1;
    return;
}

void main(){
    int64_t res;
    funP1(4, 2, 3, &res);
    funP2(4, 2, 3, &res);
}