#include <bits/stdc++.h>
using namespace std;

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define RNMX (1.0-EPS)
#define EPS 1.2e-7



float counter = 0;
static long seed=time(NULL);

float randomgeneration(long idum){
    int j;
    long k;
    static long idum2=123456789;
    static long iy=0;
    static long iv[NTAB];
    float temp;
    if (idum <= 0){                                //Initialize.
        if (-(idum) < 1)
            idum=1;                          //Be sure to preventidum=0.
        else idum = -(idum);

        idum2=(idum);
        for (j=NTAB+7;j>=0;j--){ //Load the shue table (after 8 warm-ups).
            k=(idum)/IQ1;
            idum=IA1*(idum-k*IQ1)-k*IR1;
            if (idum < 0)
            idum += IM1;
            if (j < NTAB)
            iv[j] = idum;
        }

        iy=iv[0];
    }
    k=(idum)/IQ1; //Start here when not initializing.
    idum=IA1*(idum-k*IQ1)-k*IR1; //Computeidum=(IA1*idum) % IM1without overflows by Schrage's method.

    if (idum < 0)
        idum += IM1;
    k=idum2/IQ2;
    idum2=IA2*(idum2-k*IQ2)-k*IR2; //Computeidum2=(IA2*idum) % IM2likewise.

    if (idum2 < 0) idum2 += IM2;

    j=iy/NDIV; //Will be in the range0..NTAB-1.
    iy=iv[j]-idum2; //Hereidumis shued, idumandidum2are combined to generate output.
    iv[j] = idum;

    if (iy < 1) iy += IMM1;
    if ((temp=AM*iy) > RNMX) return RNMX; //Because users don't expect endpoint values.
    else return temp;
}

float getRandom(){
    // counter++;
    float r=randomgeneration(seed);
    seed=seed+time(NULL);

    return r;
}


//2 destination 1 src verification for ETX
void verification_etx(float a, float b, bool flaga, bool flagb){
    if(flaga && flagb) return;

    float r = getRandom();

    float q1 = 1/a;
    float q2 = 1/b;

    float p1 = (1-q1)*(1-q2);
    float p2 = (1-q1)*(q2);
    float p3 = (q1)*(1-q2);
    float p4 = (q1)*(q2);

    float c1 = p1;
    float c2 = p1 + p2;
    float c3 = p1 + p2 + p3;

    if(r <= c1){
        verification_etx(a, b, flaga, flagb);
        counter += 1;
    } else if(r <= c2){
        verification_etx(a, b, flaga, true);
        counter += 1;
    } else if(r <= c3){
        verification_etx(a, b, true, flagb);
        counter += 1;
    } else {
        verification_etx(a, b, true, true);
        counter += 1;
    }
}


//2 destination 1 src verification for ETT
void verification_ett(float a, float b, bool flaga, bool flagb, float al, float bl){
    if(flaga && flagb) return;

    float r = getRandom();
    float q1 = 1.0/a;
    float q2 = 1.0/b;

    float l1 = 1.0/al;
    float l2 = 1.0/bl;

    //Only B pending
    if(flaga && !flagb){
        counter += l2;                 // time for retry to B
        if(r <= q2)
            verification_ett(a, b, true, true, al, bl);
        else
            verification_ett(a, b, true, false, al, bl);
        return;
    }

    //Only A pending
    if(!flaga && flagb){
        counter += l1;                 // time for retry to A
        if(r <= q1)
            verification_ett(a, b, true, true, al, bl);
        else
            verification_ett(a, b, false, true, al, bl);
        return;
    }

    // ---- Both pending ----
    counter += 1.0;                    // base transmission

    float p1 = (1-q1)*(1-q2);          // none success
    float p2 = (q1)*(1-q2);            // only A success
    float p3 = (1-q1)*(q2);            // only B success
    float p4 = (q1)*(q2);              // both success

    float c1 = p1;
    float c2 = p1 + p2;
    float c3 = p1 + p2 + p3;

    if(r <= c1){
        verification_ett(a, b, false, false, al, bl);
    } 
    else if(r <= c2){
        verification_ett(a, b, true, false, al, bl);
    } 
    else if(r <= c3){
        verification_ett(a, b, false, true, al, bl);
    } 
    else {
        verification_ett(a, b, true, true, al, bl);
    }
}

int main() {

    for(int i=0; i<300000; i++){
        // verification_etx(3, 2, false, false);

        verification_ett(11, 5, false, false, 3, 7);

    }

    cout << counter/300000 << endl;


    return 0;
}