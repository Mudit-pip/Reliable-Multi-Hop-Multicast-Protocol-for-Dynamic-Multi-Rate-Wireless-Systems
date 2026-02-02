#include <bits/stdc++.h>
using namespace std;

int main() {

    // Visual representation
    cout << "Network Topology:\n\n";
    cout << "        (ETX=2, Rate=2)\n";
    cout << "     0 ---------------- 1\n";
    cout << "     |                  |\n";
    cout << "     |                  |\n";
    cout << "(ETX=3,Rate=3)      (ETX=2,Rate=2)\n";
    cout << "     |                  |\n";
    cout << "     |                  |\n";
    cout << "     2 ---------------- 3\n";
    cout << "        (ETX=3, Rate=3)\n\n";

    // Link success probabilities
    double p01 = 1.0 / 2.0;   // 0 -> 1
    double p02 = 1.0 / 3.0;   // 0 -> 2

    // ETX from intermediate nodes to destination
    double ETX_13 = 2.0;
    double ETX_23 = 3.0;

    // AnyPath ETX calculation
    double pfail = (1 - p01) * (1 - p02);

    double ETX_03 = (1 + p01 * ETX_13 + (1 - p01) * p02 * ETX_23)
                    / (1 - pfail);

    // ETT calculations
    double rate01 = 2.0, rate02 = 3.0;
    double rate13 = 2.0, rate23 = 3.0;

    double ETT_13 = ETX_13 / rate13;
    double ETT_23 = ETX_23 / rate23;

    double ETT_03 = (1 + p01 * ETT_13 + (1 - p01) * p02 * ETT_23)
                    / (1 - pfail);

    // Output results
    cout << fixed << setprecision(2);
    cout << "Final Results:\n";
    cout << "-----------------------------\n";
    cout << "ETX from Node 0 to Node 3 = " << ETX_03 << endl;
    cout << "ETT from Node 0 to Node 3 = " << ETT_03 << endl;

    return 0;
}