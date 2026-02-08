#include <bits/stdc++.h>
using namespace std;

// ETX: one source → two destinations
float ETX_2dest1src(float e,float f, float el, float fl) {
    float q1 = 1.0/e;
    float q2 = 1.0/f;
    float etx1 = e/el;
    float etx2 = f/fl;
    

    float numerator =
        (1 - q1 - q2 + q1*q2)
      + (1 - q1)*q2*(1 + etx1)
      + q1*(1 - q2)*(1 + etx2)
      + q1*q2*(1+min(etx1,etx2));

    float denominator = q1 + q2 - q1*q2;
    return numerator / denominator;
}


// ETX from 0 → {1,3} → {4,5} with 2 intermediate nodes
float ETX_2dest13(float a, float d, float c, float g, float al, float dl, float cl, float gl) {
    float q1 = 1.0/a;
    float q3 = 1.0/c;
    float etx1 = a/al;
    float etx3 = c/cl;
    float etx4 = d/dl;
    float etx5 = g/gl;

    float numerator =
         (1-q1)*(1-q3)
        +(q1)*(1-q3)*(1+etx4+etx3+etx5)
        +(1-q1)*(q3)*(1+etx5+etx1+etx4)
        +(q1)*(q3)*(1+etx4+etx5);
    float denominator = 1-((1-q1)*(1-q3));

    return numerator/denominator;
}

// ETX from 0 → {1,2} → {4} with 2 intermediate nodes
float ETX_1dest12(
    float a, float b,
    float d, float dl,
    float e, float el,
    ){

    float q1 = 1.0/a;
    float q2 = 1.0/b;
    float etx14 = d/dl;
    float etx24 = e/el;

    float numerator =
         (1-q1)*(1-q2)
        +(q1)*(1-q2)*(1+etx24)
        +(1-q1)*(q2)*(1+etx14)
        +(q1)*(q2)*(1+min(etx14,etx24));
    float denominator = 1-((1-q1)*(1-q2));

    return numerator/denominator;
}

// ETX from 0 → {1,2} → {4,5} with 2 intermediate nodes
float ETX_2dest12(
    float a, float al,
    float b, float bl,
    float d, float dl,
    float e, float el,
    float f, float fl
    ){

    float q1 = 1.0/a;
    float q2 = 1.0/b;
    float etx14 = d/dl;
    float etx24 = e/el;
    float etx25 = f/fl;
    float etx02 = b/bl;
    float etx245 = ETX_2dest1src(e,f,el,fl);

    float numerator =
         (1-q1)*(1-q2)
        +(q1)*(1-q2)*(1+min(etx14+etx25+etx02, etx02+etx245))
        +(1-q1)*(q2)*(1+etx245)
        +(q1)*(q2)*(1+min(etx14+etx25,etx245));
    float denominator = 1-((1-q1)*(1-q2));

    return numerator/denominator;
}

// ETX from 0 → {2,3} → {5} with 2 intermediate nodes
float ETX_1dest23(
    float b, float c,
    float f, float fl,
    float g, float gl,
    ){

    float q1 = 1.0/b;
    float q2 = 1.0/c;
    float etx14 = f/fl;
    float etx24 = g/gl;

    float numerator =
         (1-q1)*(1-q2)
        +(q1)*(1-q2)*(1+etx24)
        +(1-q1)*(q2)*(1+etx14)
        +(q1)*(q2)*(1+min(etx14,etx24));
    float denominator = 1-((1-q1)*(1-q2));

    return numerator/denominator;
}

// ETX from 0 → {2,3} → {4,5} with 2 intermediate nodes
float ETX_2dest12(
    float b, float bl,
    float c, float cl,
    float e, float el,
    float f, float fl,
    float g, float gl
    ){

    float q1 = 1.0/b;
    float q2 = 1.0/c;
    float etx24 = e/el;
    float etx35 = g/gl;
    float etx25 = f/fl;
    float etx02 = b/bl;
    float etx245 = ETX_2dest1src(e,f,el,fl);

    float numerator =
         (1-q1)*(1-q2)
        +(q1)*(1-q2)*(1+etx245)
        +(1-q1)*(q2)*(1+min(etx24+etx35+etx02, etx02+etx245))
        +(q1)*(q2)*(1+min(etx24+etx35,etx245));
    float denominator = 1-((1-q1)*(1-q2));

    return numerator/denominator;
}

// ETX from 0 → {1,2,3} → {4}
float ETX_1dest123_no3(
    float a, float b, float c,
    float d, float dl,
    float e, float el
    ) {
    float q1 = 1.0 / a;   // 0→1
    float q2 = 1.0 / b;   // 0→2
    float q3 = 1.0 / c;   // 0→3

    float ett14 = d / dl;
    float ett24 = e / el;

    float numerator =
        // none OR only 3 receives → retry
        (1 - q1)*(1 - q2)*(1 - q3)
      + (1 - q1)*(1 - q2)*q3

        // exactly one useful receiver
      + q1*(1 - q2)*(1 - q3)*(1 + ett14)
      + (1 - q1)*q2*(1 - q3)*(1 + ett24)

        // combinations involving 3
      + q1*(1 - q2)*q3*(1 + ett14)
      + (1 - q1)*q2*q3*(1 + ett24)

        // 1 & 2 (with or without 3)
      + q1*q2*(1 - q3)*(1 + min(ett14, ett24))
      + q1*q2*q3*(1 + min(ett14, ett24));

    // Success = at least one of {1,2} receives
    float denominator =
        1 - (1 - q1)*(1 - q2);

    return numerator / denominator;
}

// ETX from 0 → {1,2,3} → {5}
float ETX_1dest123_to5(
    float a, float b, float c,
    float f, float fl,
    float g, float gl
    ) {
    float q1 = 1.0 / a;   // 0→1
    float q2 = 1.0 / b;   // 0→2
    float q3 = 1.0 / c;   // 0→3

    float ett25 = f / fl;
    float ett35 = g / gl;

    float numerator =
        // none OR only 1 receives → retry
        (1 - q1)*(1 - q2)*(1 - q3)
      + q1*(1 - q2)*(1 - q3)

        // exactly one useful receiver
      + (1 - q1)*q2*(1 - q3)*(1 + ett25)
      + (1 - q1)*(1 - q2)*q3*(1 + ett35)

        // combinations with 1
      + q1*q2*(1 - q3)*(1 + ett25)
      + q1*(1 - q2)*q3*(1 + ett35)

        // 2 & 3
      + (1 - q1)*q2*q3*(1 + min(ett25, ett35))
      + q1*q2*q3*(1 + min(ett25, ett35));

    // success = at least one of {2,3}
    float denominator =
        1 - (1 - q2)*(1 - q3);

    return numerator / denominator;
}

// ETX from 0 → {1,2,3} → {4,5}
float ETX_1dest123_to5(
    float a, float al, float b, float bl, float c, float cl,
    float f, float fl, float e, float el, float d, float dl,
    float g, float gl
    ) {
    float q1 = 1.0 / a;   // 0→1
    float q2 = 1.0 / b;   // 0→2
    float q3 = 1.0 / c;   // 0→3

    float ett14 = d / dl;
    float ett24 = e / el;
    float ett25 = f / fl;
    float ett35 = g / gl;
    float ett01 = a/al;
    float ett02 = b/bl;
    float ett03 = c/cl;
    float ett245 = ETX_2dest1src(e,f,el,fl);
    float numerator =
        // none OR only 1 receives → retry
        (1 - q1)*(1 - q2)*(1 - q3)
      + q1*(1 - q2)*(1 - q3)(1+ett14+min({ett02+ett25, ett03+ett35, ETX_1dest23(b,c,f,fl,g,gl)}))

        // exactly one useful receiver
      + (1 - q1)*q2*(1 - q3)*(1 + min({ett245,ett01+ett14 + ett03+ett35}))
      + (1 - q1)*(1 - q2)*q3*(1 + ett35+min({ett02+ett24, ett01+ett14, ETX_1dest12(a,b,d,dl,e,el)}))
        // combinations with 1
      + q1*q2*(1 - q3)*(1 + ett25)
      + q1*(1 - q2)*q3*(1 + ett35)

        // 2 & 3
      + (1 - q1)*q2*q3*(1 + min(ett25, ett35))
      + q1*q2*q3*(1 + min(ett25, ett35));

    // success = at least one of {2,3}
    float denominator =
        1 - (1 - q2)*(1 - q3);

    return numerator / denominator;
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
