#include <bits/stdc++.h>
using namespace std;

// ── RNG (same as your code) ───────────────────────────
#define IM1 2147483563
#define IM2 2147483399
#define AM  (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS  1.2e-7
#define RNMX (1.0-EPS)

static long seed = time(NULL);
float counter = 0;

float randomgeneration(long idum) {
    int j; long k;
    static long idum2 = 123456789;
    static long iy = 0;
    static long iv[NTAB];
    float temp;
    if (idum <= 0) {
        if (-(idum) < 1) idum = 1; else idum = -(idum);
        idum2 = idum;
        for (j = NTAB+7; j >= 0; j--) {
            k = idum/IQ1; idum = IA1*(idum-k*IQ1)-k*IR1;
            if (idum < 0) idum += IM1;
            if (j < NTAB) iv[j] = idum;
        }
        iy = iv[0];
    }
    k = idum/IQ1;
    idum = IA1*(idum-k*IQ1)-k*IR1;
    if (idum < 0) idum += IM1;
    k = idum2/IQ2;
    idum2 = IA2*(idum2-k*IQ2)-k*IR2;
    if (idum2 < 0) idum2 += IM2;
    j = iy/NDIV;
    iy = iv[j]-idum2;
    iv[j] = idum;
    if (iy < 1) iy += IMM1;
    if ((temp = AM*iy) > RNMX) return RNMX;
    else return temp;
}

float getRandom() {
    float r = randomgeneration(seed);
    seed = seed + time(NULL);
    return r;
}


void sim_etx(float a, float b, float c, float d, bool gotA, bool gotB){
    if (gotA || gotB) {
        float etx_fwd;
        if (gotA && gotB) {
            if (c <= d) { etx_fwd = c; }
            else         { etx_fwd = d; }
        } else if (gotA) {
            etx_fwd = c;
        } else {
            etx_fwd = d;
        }
        while (true) {
            counter += 1;
            float r = getRandom();
            if (r <= 1.0f / etx_fwd) return;
        }
    }
    counter += 1;
    float q1 = 1.0f / a;
    float q2 = 1.0f / b;
    float p_none  = (1-q1)*(1-q2);
    float p_Aonly = q1*(1-q2);
    float p_Bonly = (1-q1)*q2;
    float r = getRandom();
    if (r < p_none) {
        sim_etx(a, b, c, d, false, false);
    } else if (r < p_none + p_Aonly) {
        sim_etx(a, b, c, d, true,  false);
    } else if (r < p_none + p_Aonly + p_Bonly) {
        sim_etx(a, b, c, d, false, true);
    } else {
        sim_etx(a, b, c, d, true,  true);
    }
}



void sim_ett(float a, float b, float c, float d, float al, float bl, float cl, float dl, bool gotA, bool gotB){
    if (gotA || gotB) {
        float etx_fwd, linkrate_fwd;
        if (gotA && gotB) {
            if (c/cl <= d/dl) { etx_fwd = c; linkrate_fwd = cl; }
            else               { etx_fwd = d; linkrate_fwd = dl; }
        } else if (gotA) {
            etx_fwd = c; linkrate_fwd = cl;
        } else {
            etx_fwd = d; linkrate_fwd = dl;
        }
        while (true) {
            counter += 1.0f / linkrate_fwd;
            float r = getRandom();
            if (r <= 1.0f / etx_fwd) return;
        }
    }
    counter += 1.0f / min(al, bl);
    float q1 = 1.0f / a;
    float q2 = 1.0f / b;
    float p_none  = (1-q1)*(1-q2);
    float p_Aonly = q1*(1-q2);
    float p_Bonly = (1-q1)*q2;
    float r = getRandom();
    if (r < p_none) {
        sim_ett(a, b, c, d, al, bl, cl, dl, false, false);
    } else if (r < p_none + p_Aonly) {
        sim_ett(a, b, c, d, al, bl, cl, dl, true,  false);
    } else if (r < p_none + p_Aonly + p_Bonly) {
        sim_ett(a, b, c, d, al, bl, cl, dl, false, true);
    } else {
        sim_ett(a, b, c, d, al, bl, cl, dl, true,  true);
    }
}

int main() {
    float a = 2.0, b = 2.0, c = 3.0, d = 4.0;
    float al = 1.0, bl = 2.0, cl = 2.0, dl = 4.0;

    int N = 300000;

    counter = 0;
    for (int i = 0; i < N; i++)
        sim_etx(a, b, c, d, false, false);
    cout << "Simulated ETX = " << counter/N << endl;

    counter = 0;
    for (int i = 0; i < N; i++)
        sim_ett(a, b, c, d, al, bl, cl, dl, false, false);
    cout << "Simulated ETT = " << counter/N << endl;

    return 0;
}
