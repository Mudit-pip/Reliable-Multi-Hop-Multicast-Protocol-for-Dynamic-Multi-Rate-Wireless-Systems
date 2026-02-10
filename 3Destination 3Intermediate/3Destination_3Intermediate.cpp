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
//used to calculate ETX of reacing 4,6 form 1,2
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
//used to calculate ETX of reacing 5 form 1,2
//used to calculate ETX of reacing 6 form 1,2,3
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
//used to calculate ETX of reacing 5,6 form 1,2
//used to calculate ETX of reacing 5,4 form 1,2
//used to calculate ETX of reacing 5,6 form 1,3
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

//same for 0->{1,3}->{4,5,6}
float ETX456destFrom12(float a,float b, float d, float e, float f, float g,
    float al,float bl, float dl, float el, float fl, float gl
    ){
    float q1 = 1/a;
    float q2 = 1/b;
    float ett01 = a/al;
    float ett02 = b/bl;
    float ett14 = d/dl;
    float ett15 = e/el;
    float ett25 = f/fl;
    float ett26 = g/gl;

    float numerator = 
        (1-q1)*(1-q2)+
        (q1)*(1-q2)*(1+ett02+min({ETX_2dest1src(d,e,dl,el)+ett26,ett14+ETX_2dest1src(f,g,fl,gl)}))+
        (1-q1)*(q2)*(1+ett01+min({ETX_2dest1src(d,e,dl,el)+ett26,ett14+ETX_2dest1src(f,g,fl,gl)}))+
        (q1)*(q2)*(1+min({ETX_2dest1src(d,e,dl,el)+ett26,ett14+ETX_2dest1src(f,g,fl,gl)}));

    float denominator =  1-((1-q1)*(1-q2));
    return numerator/denominator;

}

//for 0->{1,2,3}->{5}
float ETX5destFrom123(float a,float b, float c, float e, float f, float h,
    float al,float bl, float cl, float el, float fl, float hl
    ){
    float q1 = 1/a;
    float q2 = 1/b;
    float q3 = 1/c;
    float ett1 = a/al;  
    float ett2 = b/bl;
    float ett3 = c/cl;
    float ett4 = e/el;  
    float ett5 = f/fl;
    float ett6 = h/hl;


    float numerator =
        (1 - q1)*(1 - q2)*(1 - q3)
        + (1 - q1)*(1 - q2)*(q3)*(1+ett6)
        + (1-q1)*(q2)*(1-q3)*(1+ett5)
        + (q1)*(1 - q2)*(1-q3)*(1+ett4)

        + (1 - q1)*(q2)*(q3)*(1+min(ett5, ett6))
        + (q1)*(q2)*(1-q3)*(1+min(ett5, ett4))
        + (q1)*(1-q2)*(q3)*(1+min(ett4, ett6))

        + (q1)*(q2)*(q3)*(1+min({ett4, ett5, ett6}));

    // success = at least one of {2,3}
    float denominator =
        1 - (1 - q1)*(1 - q2)*(1 - q3);

    return numerator / denominator;
}

//for 0->{1,2,3}->{5,6}
float ETX56destFrom123(float a,float b, float c, float e, float f, float g, float h, float i,
    float al,float bl, float cl, float el, float fl, float gl, float hl, float il, int zerotosix
    ){
    float q1 = 1/a;
    float q2 = 1/b;
    float q3 = 1/c;
    float etta = a/al;  
    float ettb = b/bl;
    float ettc = c/cl;
    float ette = e/el;  
    float ettf = f/fl;
    float ettg = g/gl;
    float etth = h/hl;
    float etti = i/il;
    float two56 = ETX_2dest1src(f,fl,g,gl);
    float three56 = ETX_2dest1src(h,hl,i,il);

    float numerator =
        (1 - q1)*(1 - q2)*(1 - q3)
        + (1 - q1)*(1 - q2)*(q3)*(1+etth + etti)
        + (1 - q1)*(q2)*(1-q3)*(1+ettf + ettg)
        + (q1)*(1 - q2)*(1-q3)*(1+ette + zerotosix)

        + (1 - q1)*(q2)*(q3)*(1+min({two56,three56,ettf+etti,ettg+etth}))
        + (q1)*(q2)*(1-q3)*(1+min(ette+ettg, two56))
        + (q1)*(1-q2)*(q3)*(1+min(ette+etti, three56))

        + (q1)*(q2)*(q3)*(1+min({ette+etti,ette+ettg,two56,three56,ettf+etti,ettg+etth}));

    // success = at least one of {2,3}
    float denominator =
        1 - (1 - q1)*(1 - q2)*(1 - q3);

    return numerator / denominator;
}

//for 0->{1,2,3}->{4,6}
float ETX46destFrom123(float a,float b, float c, float d, float g,float i,
    float al,float bl, float cl, float dl, float gl,float il, float zerotosix
    ){
    float q1 = 1/a;
    float q2 = 1/b;
    float q3 = 1/c;
    float etta = a/al;  
    float ettb = b/bl;
    float ettc = c/cl;
    float ettd = d/dl;
    float ettg = g/gl;
    float etti = i/il;

    float numerator =
        (1 - q1)*(1 - q2)*(1 - q3)
        + (1 - q1)*(1 - q2)*(q3)*(1+etta + ettd + etti)
        + (1 - q1)*(q2)*(1-q3)*(1+etta + ettd + ettg)
        + (q1)*(1 - q2)*(1-q3)*(1+ettd + zerotosix)

        + (1 - q1)*(q2)*(q3)*(1+etta + ettd + min(etti,ettg))
        + (q1)*(q2)*(1-q3)*(1 + ettd+ettg)
        + (q1)*(1-q2)*(q3)*(1 + etti + ettd)

        + (q1)*(q2)*(q3)*(1 + ettd + min(etti, ettg));

    // success = at least one of {2,3}
    float denominator =
        1 - (1 - q1)*(1 - q2)*(1 - q3);

    return numerator / denominator;
}


//for 0->{1,2,3}->{4,5}
float ETX45destFrom123(float a,float b, float c, float d, float e,float f, float h,
    float al,float bl, float cl, float dl, float el,float fl, float hl
    ){
    float q1 = 1/a;
    float q2 = 1/b;
    float q3 = 1/c;
    float etta = a/al;  
    float ettb = b/bl;
    float ettc = c/cl;
    float ettd = d/dl;
    float ette = e/el;  
    float ettf = f/fl;
    float etth = h/hl;
    float oneto45 = ETX_2dest1src(d,e,dl,el);

    float numerator =
        (1 - q1)*(1 - q2)*(1 - q3)
        + (1 - q1)*(1 - q2)*(q3)*(1+etta + ettd + etth)
        + (1 - q1)*(q2)*(1-q3)*(1+etta + ettd + ettf)
        + (q1)*(1 - q2)*(1-q3)*(1+oneto45)

        + (1 - q1)*(q2)*(q3)*(1+etta + ettd + min(ettf,etth))
        + (q1)*(q2)*(1-q3)*(1 + min(oneto45,ettd+ettf))
        + (q1)*(1-q2)*(q3)*(1 + min(oneto45,ettd+etth))

        + (q1)*(q2)*(q3)*(1 + ettd + min({ette,ettf,etth}));

    // success = at least one of {2,3}
    float denominator =
        1 - (1 - q1)*(1 - q2)*(1 - q3);

    return numerator / denominator;
}


//for 0->{1,2,3}->{4,5,6}
float ETX456destFrom123(float a,float b, float c, float d, float e,float f,float g, float h, float i,
    float al,float bl, float cl, float dl, float el,float fl,float gl, float hl, float il, float zeroto56
    ){
    float q1 = 1/a;
    float q2 = 1/b;
    float q3 = 1/c;
    float etta = a/al;  
    float ettb = b/bl;
    float ettc = c/cl;
    float ettd = d/dl;
    float ette = e/el;  
    float ettf = f/fl;
    float ettg = g/gl;
    float etth = h/hl;
    float etti = i/il;
    float two56 = ETX_2dest1src(f,fl,g,gl);
    float three56 = ETX_2dest1src(h,hl,i,il);

    float numerator =
        (1 - q1)*(1 - q2)*(1 - q3)
        + (1 - q1)*(1 - q2)*(q3)*(1+three56+etta+ettd)
        + (1 - q1)*(q2)*(1-q3)*(1+two56+etta+ettd)
        + (q1)*(1 - q2)*(1-q3)*(1+ettd + zeroto56)

        + (1 - q1)*(q2)*(q3)*(1+etta + ettd + min({two56,three56,ettf+etti,ettg+etth}))
        + (q1)*(q2)*(1-q3)*(1 + ettd + two56)
        + (q1)*(1-q2)*(q3)*(1 + ettd + three56)

        + (q1)*(q2)*(q3)*(1 + ettd + min({two56,three56,ettf+etti,ettg+etth,ette+ettg,etti+ette}));

    // success = at least one of {2,3}
    float denominator =
        1 - (1 - q1)*(1 - q2)*(1 - q3);

    return numerator / denominator;
}


// ETX from 0 → {4,5,6}
void ETX_0_to_456_3intermediate(
    float a, float al, float b, float bl, float c, float cl, 
    float d, float dl, float e, float el, float f, float fl,  
    float g, float gl, float h, float hl, float i, float il) {

    vector<vector<float>> cost(7, vector<float>(3, 0));

///////////////////////////////////////////////////
    cost[0][0] = b/bl + g/gl;
    cost[1][0] = ETX_1dest12(a,b,e,el,f,fl);
    cost[2][0] = ETX_2dest12(a,al,b,bl,e,el,f,fl,g,gl);
    cost[3][0] = (a/al)+(d/dl);
    cost[4][0] = ETX_2dest13(a,d,b,g,al,dl,bl,gl);
    cost[5][0] = ETX_2dest12(b,bl,a,al,f,fl,e,el,d,dl);
    cost[6][0] = ETX456destFrom12(a,b,d,e,f,g,al,bl,dl,el,fl,gl);
//////////////////////////////////////////////


///////////////////////////////////////////////////
    cost[0][1] = c/cl+i/il;
    cost[1][1] = ETX5destFrom123(a,b,c,e,f,h,al,bl,cl,el,fl,hl);
    cost[2][1] = ETX_2dest12(a,al,c,cl,e,el,h,hl,i,il);
    cost[3][1] = (a/al)+(d/dl);
    cost[4][1] = ETX_2dest13(a,d,c,i,al,dl,cl,il);
    cost[5][1] = ETX_2dest12(c,cl,a,al,h,hl,e,el,d,dl);
    cost[6][1] = ETX456destFrom12(a,c,d,e,h,i,al,cl,dl,el,hl,il);
//////////////////////////////////////////////


///////////////////////////////////////////////////
    cost[0][2] = ETX_1dest12(b,c,g,gl,i,il);
    float x3 = cost[0][2];

    cost[1][2] = ETX5destFrom123(a,b,c,e,f,h,al,bl,cl,el,fl,hl);

    cost[2][2] = ETX56destFrom123(a,b,c,e,f,g,h,i,al,bl,cl,el,fl,gl,hl,il,x3);
    float x4 = cost[2][2];
    cost[3][2] = (a/al)+(d/dl);
    cost[4][2] = ETX46destFrom123(a,b,c,d,g,i,al,bl,cl,dl,gl,il, x3);
    cost[5][2] = ETX45destFrom123(a,b,c,d,e,f,h,al,bl,cl,dl,el,fl,hl);
    cost[6][2] = ETX456destFrom123(a,b,c,d,e,f,g,h,i,al,bl,cl,dl,el,fl,gl,hl,il,x4);
//////////////////////////////////////////////

   vector<vector<int>> fs = {{1,2}, {1,3}, {1,2,3}};

   vector<int> ans_set = fs[0];
   float mini = cost[6][0];

   for(int i=1; i<3; i++){
    if(cost[6][i] < mini){
        mini = cost[6][i];
        ans_set = fs[i];
    }
   }

   cout << "Minimum ETT from Node 0 to {4,5,6} is " << mini << endl;
   cout << "Path = ";
   for(auto it : ans_set){
    cout << it << " ";
   }
}




int main() {
    // 0 → intermediates
    float a = 3, b = 2, c = 40, d = 3, e = 2, f = 3, g = 4, h = 3, i = 5;
    float al = 1, bl = 2, cl = 2, dl = 3, el = 1, fl = 4, gl = 1, hl = 1, il = 2;

    ETX_0_to_456_3intermediate(a, al, b, bl, c, cl,  d, dl, e, el, f, fl, g, gl, h, hl, i, il);


    return 0;
}