#include <bits/stdc++.h>
using namespace std;

// ETX: one source → two destinations
//used for calculating x1 in ETX_1_to_45_3intermediate
float ETX_2dest1src(float e,float f, float el, float fl) {
    float q1 = 1.0/e;
    float q2 = 1.0/f;
    float etx1 = e/el;
    float etx2 = f/fl;
    

    float numerator =
        (1 - q1)*(1 - q2)
      + (1 - q1)*q2*(1 + etx1)
      + q1*(1 - q2)*(1 + etx2)
      + q1*q2;

    float denominator = 1 - (1 - q1)*(1 - q2);
    return numerator / denominator;
}


// ETX from 0 → {1,3} → {4,5} with 2 intermediate nodes
//used to calculate x2 in ETX_1_to_45_3intermediate
float ETX_2dest13(float a, float d, float c, float g, 
    float al, float dl, float cl, float gl) {

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
//used to calculate x3 in ETX_1_to_45_3intermediate
float ETX_1dest12(
    float a, float b,
    float d, float dl,
    float e, float el
    ){

    float q1 = 1.0/a;
    float q2 = 1.0/b;
    float etx1 = d/dl;
    float etx2 = e/el;

    float numerator =
         (1-q1)*(1-q2)
        +(q1)*(1-q2)*(1+etx1)
        +(1-q1)*(q2)*(1+etx2)
        +(q1)*(q2)*(1+min(etx1,etx2));

    float denominator = 1-((1-q1)*(1-q2));

    return numerator/denominator;
}

// ETX from 0 → {1,2} → {4,5} with 2 intermediate nodes
//used to calculate x4 in ETX_1_to_45_3intermediate
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
        +(q1)*(q2)*(1+min(etx14+etx25, etx245));

    float denominator = 1-((1-q1)*(1-q2));

    return numerator/denominator;
}

// ETX from 0 → {2,3} → {5} with 2 intermediate nodes
//used to calculate x5 in ETX_1_to_45_3intermediate
float ETX_1dest23(
    float b, float c,
    float f, float fl,
    float g, float gl
    ){

    float q1 = 1.0/b;
    float q2 = 1.0/c;
    float etx14 = f/fl;
    float etx24 = g/gl;

    float numerator =
         (1-q1)*(1-q2)
        +(q1)*(1-q2)*(1+etx14)
        +(1-q1)*(q2)*(1+etx24)
        +(q1)*(q2)*(1+min(etx14,etx24));

    float denominator = 1-((1-q1)*(1-q2));

    return numerator/denominator;
}

// ETX from 0 → {2,3} → {4,5} with 2 intermediate nodes
//used to calculate x6 in ETX_1_to_45_3intermediate
float ETX_2dest23(
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
//used to calculate x8 in ETX_1_to_45_3intermediate
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
        1 - (1 - q1)*(1 - q2)*(1 - q3) - (1 - q1)*(1 - q2)*q3;

    return numerator / denominator;
}

// ETX from 0 → {1,2,3} → {5}
//used to calculate x7 in ETX_1_to_45_3intermediate
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
        1 - (1-q1)*(1 - q2)*(1 - q3) - (q1)*(1 - q2)*(1 - q3);

    return numerator / denominator;
}

// ETX from 0 → {1,2,3} → {4,5}
//used to calculate x9 in ETX_1_to_45_3intermediate
float ETX_1dest123_to45(
    float a, float al, float b, float bl, float c, float cl,
    float d, float dl, float e, float el, float f, float fl, 
    float g, float gl, float x1, float x3, float x5
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

    float numerator =
        // none OR only 1 receives → retry
        (1 - q1)*(1 - q2)*(1 - q3)
      + q1*(1 - q2)*(1 - q3)*(1 + ett14 + x5)

        // exactly one useful receiver
      + (1 - q1)*q2*(1 - q3)*(1 + x1)
      + (1 - q1)*(1 - q2)*q3*(1 + ett35+x3)
        // combinations with 1
      + q1*q2*(1 - q3)*(1 + ett25 + ett14)
      + q1*(1 - q2)*q3*(1 + ett35 + ett14)

        // 2 & 3
      + (1 - q1)*q2*q3*(1 + ett24 + ett35)
      + q1*q2*q3*(1 + min(ett14 + ett25, ett24 + ett35));

    // success = at least one of {2,3}
    float denominator =
        1 - (1 - q1)*(1 - q2)*(1 - q3);

    return numerator / denominator;
}



// ETX from 0 → {4,5}
void ETX_1_to_45_3intermediate(
    float a, float al, float b, float bl, float c, float cl, 
    float d, float dl, float e, float el, float f, float fl,  
    float g, float gl) {

    vector<vector<float>> cost(3, vector<float>(5, 0));

///////////////////////////////////////////////////
    cost[0][0] = b/bl + f/fl;
    cost[1][0] = b/bl + e/el;

    float x1 = ETX_2dest1src(e,f,el,fl);
    cost[2][0] = b/bl + x1;
//////////////////////////////////////////////


///////////////////////////////////////////////////
    cost[0][1] = c/cl + g/gl;
    cost[1][1] = a/al + d/dl;

    float x2 = ETX_2dest13(a, d, c, g, al, dl, cl, gl);
    cost[2][1] = x2;
//////////////////////////////////////////////


///////////////////////////////////////////////////
    cost[0][2] = b/bl + f/fl;


    float x3 = ETX_1dest12(a, b, d, dl, e, el);
    cost[1][2] = x3;

    float x4 = ETX_2dest12(a, al, b, bl, d, dl, e, el, f, fl);
    cost[2][2] = x4;
//////////////////////////////////////////////

///////////////////////////////////////////////////
    float x5 = ETX_1dest23( b,  c,  f,  fl,  g,  gl);
    cost[0][3] = x5;


    cost[1][3] = b/bl + e/el;

    float x6 = ETX_2dest23(b, bl, c, cl, e, el, f, fl, g,  gl);
    cost[2][3] = x6;
//////////////////////////////////////////////

///////////////////////////////////////////////////
    float x7 = ETX_1dest123_to5(a, b, c, f, fl, g, gl);
    cost[0][4] = x7;

    float x8 = ETX_1dest123_no3(a, b, c, d, dl, e, el);
    cost[1][4] = x8;

    float x9 = ETX_1dest123_to45(a, al, b, bl, c, cl, d, dl,
        e, el, f, fl, g, gl, x1, x3, x5);
    cost[2][4] = x9;
//////////////////////////////////////////////


   vector<vector<int>> fs = {{2}, {1,3}, {1,2}, {2,3}, {1,2,3}};

   vector<int> ans_set = fs[0];
   float mini = cost[2][0];

   for(int i=1; i<5; i++){
    if(cost[2][i] < mini){
        mini = cost[2][i];
        ans_set = fs[i];
    }
   }

   cout << "Minimum ETT from Node 0 to {4,5} is " << mini << endl;
   cout << "Path = ";
   for(auto it : ans_set){
    cout << it << " ";
   }
}




int main() {
    // 0 → intermediates
    float a = 3, b = 20, c = 4;

    // 1 → {4}
    float d = 3;

    // 2 → {4,5}
    float e = 2, f = 3;

    // 3 → {5}
    float g = 4;

    float al = 1, bl = 2, cl = 2, dl = 3, el = 1, fl = 4, gl = 1;

    ETX_1_to_45_3intermediate(a, al, b, bl, c, cl,  d, dl, e, el, f, fl, g, gl);


    return 0;
}