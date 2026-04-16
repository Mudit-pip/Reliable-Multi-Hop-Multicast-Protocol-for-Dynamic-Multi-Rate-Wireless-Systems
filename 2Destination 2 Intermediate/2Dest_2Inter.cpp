#include <bits/stdc++.h>
using namespace std;

//returns etx from 0 to {1,2}
float ETX_2dest1src(float etx1, float etx2) {
    float q1 = 1.0 / etx1;
    float q2 = 1.0 / etx2;

    float numerator =
        (1 - q1)*(1 - q2)
        + (1 - q1)*q2*(1 + etx1)
      + q1*(1 - q2)*(1 + etx2)
      + q1*q2;

    float denominator = 1 - (1 - q1)*(1 - q2);

    return numerator / denominator;
}


float ETT_2dest1src(float etx1, float etx2, float al, float bl) {
    float q1 = 1.0 / etx1;
    float q2 = 1.0 / etx2;
 
    float ett1 = etx1 / al;
    float ett2 = etx2 / bl;
    float slot = 1.0 / min(al, bl);
 
    float numerator =
        (1 - q1)*(1 - q2) * slot
      + (1 - q1)*q2       * (slot + ett2)
      + q1*(1 - q2)       * (slot + ett1)
      + q1*q2             * (slot + min(ett1, ett2));
    float denominator = 1 - (1 - q1)*(1 - q2);
    return numerator / denominator;
}


// returns ETX from node 0 to {3,4}
// a = ETX(0,1), b = ETX(0,2)
// c = ETX(1,3), d = ETX(1,4)
// e = ETX(2,3), f = ETX(2,4)
float ETX_2dest2intermediate(float a, float b, float c, float d, float e, float f) {
    // Step 1: ETX from intermediates to destinations
    float ETX_1_to_34 = ETX_2dest1src(c, d);  // 1 → {3,4}
    float ETX_2_to_34 = ETX_2dest1src(e, f);  // 2 → {3,4}



    // Each destination can be reached by either node, success probability:
    float q13 = 1.0 / c; // node 1 → 3
    float q23 = 1.0 / e; // node 2 → 3
    float q14 = 1.0 / d; // node 1 → 4
    float q24 = 1.0 / f; // node 2 → 4

    float p3 = q13 + q23 - q13*q23; // probability 3 receives
    float p4 = q14 + q24 - q14*q24; // probability 4 receives

    // ETX_12_to_34 using dest2 function
    float ETX_12_to_34 = ETX_2dest1src(1.0/p3, 1.0/p4);


    // Step 2: success probabilities from source
    float q1 = 1.0 / a;   // 0 → 1
    float q2 = 1.0 / b;   // 0 → 2

    float numerator =
        (1 - q1 - q2 + q1*q2)
      + q1*(1 - q2)*(1 + ETX_1_to_34)
      + (1 - q1)*q2*(1 + ETX_2_to_34)
      + q1*q2*(1 + min({ETX_1_to_34, ETX_2_to_34, ETX_12_to_34}));


    float denominator = q1 + q2 - q1*q2;

    return numerator / denominator;
}


float ETT_2dest2intermediate(float a,  float b, float c,  float d, float e,  float f, float al, float bl, float cl, float dl, float el, float fl) {
    float ETT_1_to_34 = ETT_2dest1src(c, d, cl, dl);   // 1 → {3,4}
    float ETT_2_to_34 = ETT_2dest1src(e, f, el, fl);   // 2 → {3,4}
 
    // Combined delivery probabilities at each destination
    float q13 = 1.0 / c;
    float q23 = 1.0 / e;
    float q14 = 1.0 / d;
    float q24 = 1.0 / f;
 
    float p3 = q13 + q23 - q13*q23;
    float p4 = q14 + q24 - q14*q24;
 

    float best_ett_to_3 = min(c/cl, e/el);
    float best_ett_to_4 = min(d/dl, f/fl);
    float ETT_12_to_34 = ETT_2dest1src(1.0/p3, 1.0/p4, 1.0/best_ett_to_3, 1.0/best_ett_to_4);
 
    
    float q1   = 1.0 / a;
    float q2   = 1.0 / b;
    float slot = 1.0 / min(al, bl);



    float numerator =
        (1 - q1)*(1 - q2) * slot 
      + q1*(1 - q2)       * (slot + ETT_1_to_34)
      + (1 - q1)*q2       * (slot + ETT_2_to_34)
      + q1*q2             * (slot + min({ETT_1_to_34, ETT_2_to_34, ETT_12_to_34}));


    float denominator = q1 + q2 - q1*q2;
    return numerator / denominator;
}

int main() {
    float a = 3; // 0->1
    float b = 2; // 0->2
    float c = 3; // 1->3
    float d = 3; // 1->4
    float e = 2; // 2->3
    float f = 3; // 2->4

    float al = 2, bl = 4;        // 0→1, 0→2
    float cl = 2, dl = 2;        // 1→3, 1→4
    float el = 4, fl = 2;        // 2→3, 2→4

    float etx_total = ETX_2dest2intermediate(a, b, c, d, e, f);
    float ett_total = ETT_2dest2intermediate(a, b, c, d, e, f, al, bl, cl, dl, el, fl);
 
    cout << "\nETX from source 0 to destinations {3,4} = " << etx_total << endl;
    cout << "ETT from source 0 to destinations {3,4} = " << ett_total << endl;

    return 0;
}
