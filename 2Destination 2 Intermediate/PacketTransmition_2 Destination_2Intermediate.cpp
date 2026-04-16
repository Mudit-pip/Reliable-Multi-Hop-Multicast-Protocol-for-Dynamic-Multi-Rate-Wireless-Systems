#include <bits/stdc++.h>
using namespace std;

// ── RNG ──────────────────────────────────────────────────────────────────────
#define IM1  2147483563
#define IM2  2147483399
#define AM   (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1  40014
#define IA2  40692
#define IQ1  53668
#define IQ2  52774
#define IR1  12211
#define IR2  3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS  1.2e-7
#define RNMX (1.0-EPS)

static long seed = time(NULL);
float counter = 0;

float randomgeneration(long idum) {
    int j; long k;
    static long idum2 = 123456789;
    static long iy    = 0;
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
    k     = idum/IQ1;
    idum  = IA1*(idum-k*IQ1)-k*IR1;
    if (idum  < 0) idum  += IM1;
    k     = idum2/IQ2;
    idum2 = IA2*(idum2-k*IQ2)-k*IR2;
    if (idum2 < 0) idum2 += IM2;
    j  = iy/NDIV;
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


void sim_hop2_etx(float c, float d, float e, float f,
                  bool got1, bool got2,
                  bool dest3_done, bool dest4_done) {

    if (dest3_done && dest4_done) return;

    counter++;  // one transmission

    // success probabilities
    float q13 = got1 ? 1.0f / c : 0.0f;
    float q23 = got2 ? 1.0f / e : 0.0f;
    float q14 = got1 ? 1.0f / d : 0.0f;
    float q24 = got2 ? 1.0f / f : 0.0f;

    // combined probability (handles all cases automatically)
    float p3 = q13 + q23 - q13 * q23;
    float p4 = q14 + q24 - q14 * q24;

    float r3 = getRandom();
    float r4 = getRandom();

    bool rcv3 = (r3 < p3);
    bool rcv4 = (r4 < p4);

    sim_hop2_etx(c, d, e, f, got1, got2, dest3_done || rcv3, dest4_done || rcv4);
}

void sim_hop2_ett(float c, float d, float e, float f,
                  float cl, float dl, float el, float fl,
                  bool got1, bool got2,
                  bool dest3_done, bool dest4_done) {

    if (dest3_done && dest4_done) return;

    // success probabilities (same as ETX)
    float q13 = got1 ? 1.0f / c : 0.0f;
    float q23 = got2 ? 1.0f / e : 0.0f;
    float q14 = got1 ? 1.0f / d : 0.0f;
    float q24 = got2 ? 1.0f / f : 0.0f;

    // combined probabilities
    float p3 = q13 + q23 - q13 * q23;
    float p4 = q14 + q24 - q14 * q24;

    // slot time = bottleneck link
    float slot;
    if (got1 && got2)
        slot = 1.0f / min({cl, dl, el, fl});
    else if (got1)
        slot = 1.0f / min(cl, dl);
    else
        slot = 1.0f / min(el, fl);

    counter += slot;

    // random success
    bool rcv3 = (getRandom() < p3);
    bool rcv4 = (getRandom() < p4);

    sim_hop2_ett(c, d, e, f, cl, dl, el, fl,
                 got1, got2,
                 dest3_done || rcv3,
                 dest4_done || rcv4);
}

void sim_etx(float a, float b, float c, float d, float e, float f,
             bool got1, bool got2) {

    if (got1 || got2) {
        sim_hop2_etx(c, d, e, f, got1, got2, false, false);
        return;
    }

    counter += 1;

    float q1 = 1.0f / a;
    float q2 = 1.0f / b;

    float r1 = getRandom();
    float r2 = getRandom();

    bool rcv1 = (r1 < q1);
    bool rcv2 = (r2 < q2);

    if (!rcv1 && !rcv2) {
        sim_etx(a, b, c, d, e, f, false, false);
    } else {
        sim_hop2_etx(c, d, e, f, rcv1, rcv2, false, false);
    }
}

void sim_ett(float a, float b, float c, float d, float e, float f,
             float al, float bl, float cl, float dl, float el, float fl,
             bool got1, bool got2) {

    if (got1 || got2) {
        sim_hop2_ett(c, d, e, f, cl, dl, el, fl, got1, got2, false, false);
        return;
    }

    // Source transmission slot = bottleneck of outgoing link rates
    counter += 1.0f / min(al, bl);

    float q1 = 1.0f / a;
    float q2 = 1.0f / b;

    float r1 = getRandom();
    float r2 = getRandom();

    bool rcv1 = (r1 < q1);
    bool rcv2 = (r2 < q2);

    if (!rcv1 && !rcv2) {
        sim_ett(a, b, c, d, e, f, al, bl, cl, dl, el, fl, false, false);
    } else {
        sim_hop2_ett(c, d, e, f, cl, dl, el, fl, rcv1, rcv2, false, false);
    }
}

int main() {
    // ETX link values
    float a = 3, b = 2;   // 0→1, 0→2
    float c = 3, d = 3;   // 1→3, 1→4
    float e = 2, f = 3;   // 2→3, 2→4

    // Link rates
    float al = 2, bl = 4;   // 0→1, 0→2
    float cl = 2, dl = 2;   // 1→3, 1→4
    float el = 4, fl = 2;   // 2→3, 2→4

    int N = 300000;

    
    counter = 0;
    for (int i = 0; i < N; i++)
        sim_etx(a, b, c, d, e, f, false, false);
    cout << "Simulated ETX  = " << counter / N << endl;


    counter = 0;
    for (int i = 0; i < N; i++)
        sim_ett(a, b, c, d, e, f, al, bl, cl, dl, el, fl, false, false);
    cout << "Simulated ETT  = " << counter / N << endl;

    return 0;
}
