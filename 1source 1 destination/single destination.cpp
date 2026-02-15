#include <bits/stdc++.h>
using namespace std;


void ETX_ETT_1src_1dest_2int(float a,float b, float c, float d, float cl, float dl) {
    float q1 = 1.0/a;
    float q2 = 1.0/b;
    

    float numerator =
        (1 - q1)*(1 - q2)
      + (1 - q1)*q2*(1 + d)
      + q1*(1 - q2)*(1 + c)
      + q1*q2*(1+min(c,d));

    float denominator = 1 - (1 - q1)*(1 - q2);
    cout <<  "ETX = " << numerator / denominator << endl;


    float numerator1 =
        (1 - q1)*(1 - q2)
      + (1 - q1)*q2*(1 + d/dl)
      + q1*(1 - q2)*(1 + c/cl)
      + q1*q2*(1+min(c/cl,d/dl));

    float denominator1 = 1 - (1 - q1)*(1 - q2);
    cout <<  "ETT = " << numerator1 / denominator1 << endl;
}

int main() {

    float a = 2, b=2, c=3, d=4;
    float cl = 2, dl = 4;
    ETX_ETT_1src_1dest_2int(a,b,c,d, cl, dl);

    return 0;

}
