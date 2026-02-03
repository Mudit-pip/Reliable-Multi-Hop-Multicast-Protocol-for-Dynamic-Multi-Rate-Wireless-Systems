#include <bits/stdc++.h>
using namespace std;

// ETX: one source → two destinations
float ETX_2dest1src(float etx1, float etx2) {
    float q1 = 1.0 / etx1;
    float q2 = 1.0 / etx2;

    float numerator =
        (1 - q1 - q2 + q1*q2)
      + (1 - q1)*q2*(1 + etx1)
      + q1*(1 - q2)*(1 + etx2)
      + q1*q2;

    float denominator = q1 + q2 - q1*q2;
    return numerator / denominator;
}

// ETX: one source → three destinations (used for 0 → {1,2,3})
float ETX_3dest1src(float e1, float e2, float e3) {
    float q1 = 1.0 / e1;
    float q2 = 1.0 / e2;
    float q3 = 1.0 / e3;

    float p = q1 + q2 + q3
            - q1*q2 - q1*q3 - q2*q3
            + q1*q2*q3;

    return 1.0 / p;
}

// ETX from 0 → {4,5} with 3 intermediate nodes
float ETX_2dest3intermediate(
    float a, float b, float c,
    float d, float e,
    float f, float g,
    float h, float i
) {
    // Step 1: intermediate → destinations
    float ETX_1_to_45 = ETX_2dest1src(d, e);
    float ETX_2_to_45 = ETX_2dest1src(f, g);
    float ETX_3_to_45 = ETX_2dest1src(h, i);

    // Step 2: probability that destinations receive from any intermediate
    float p4 = (1.0/d + 1.0/f + 1.0/h)
             - (1.0/d)*(1.0/f)
             - (1.0/d)*(1.0/h)
             - (1.0/f)*(1.0/h)
             + (1.0/d)*(1.0/f)*(1.0/h);

    float p5 = (1.0/e + 1.0/g + 1.0/i)
             - (1.0/e)*(1.0/g)
             - (1.0/e)*(1.0/i)
             - (1.0/g)*(1.0/i)
             + (1.0/e)*(1.0/g)*(1.0/i);

    float ETX_123_to_45 = ETX_2dest1src(1.0/p4, 1.0/p5);

    // Step 3: source → intermediates
    float q1 = 1.0 / a;
    float q2 = 1.0 / b;
    float q3 = 1.0 / c;

    float p_any =
        q1 + q2 + q3
      - q1*q2 - q1*q3 - q2*q3
      + q1*q2*q3;

    float best_next = min({ETX_1_to_45, ETX_2_to_45, ETX_3_to_45});

    return (1 + best_next) / p_any;
}

int main() {
    // 0 → intermediates
    float a = 3, b = 2, c = 4;

    // 1 → {4,5}
    float d = 3, e = 3;

    // 2 → {4,5}
    float f = 2, g = 3;

    // 3 → {4,5}
    float h = 4, i = 2;

    float result = ETX_2dest3intermediate(
        a,b,c,d,e,f,g,h,i
    );

    cout << fixed << setprecision(2);
    cout << "ETX from 0 to {4,5} = " << result << endl;
    return 0;
}
