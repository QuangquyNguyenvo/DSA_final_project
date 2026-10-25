#ifndef BENCHMARK_H
#define BENCHMARK_H
// Benchmark cơ bản: đo thời gian sinh (không in) của 3 thuật toán trong comb_gen.cpp
// và so sánh với công thức số cấu hình n!, C(n, k), 2^n.
// Kết quả in ra màn hình và ghi vào bench_results.csv
#include <bits/stdc++.h>
using namespace std;

// các hàm định nghĩa trong comb_gen.cpp
bool nextPermutation(vector<int>& a);
bool nextCombination(vector<int>& a, int n);
bool verifyGray(int current, int previous, vector<bool>& seen);

const int REPS = 5;  // số lần đo, lấy median (chưa tính 1 lần khởi động)
long long bCnt;      // số cấu hình mà hàm sinh vừa tạo ra
ofstream csv;

// chạy fn 1 lần khởi động + REPS lần, trả về median thời gian (ms)
template<class F> double medianMs(F fn) {
    vector<double> times;
    for (int r = 0; r <= REPS; r++) {
        bCnt = 0;
        auto start = chrono::steady_clock::now();
        fn();
        auto end = chrono::steady_clock::now();
        if (r > 0) times.push_back(chrono::duration<double, milli>(end - start).count());
    }
    sort(times.begin(), times.end());
    return times[REPS / 2];
}

// ---------- công thức ----------

long long fact(int n) {
    return n < 2 ? 1 : n * fact(n - 1);
}
long long binom(int n, int k) {
    long long r = 1;
    for (int i = 1; i <= k; i++) r = r * (n - k + i) / i;
    return r;
}

// ---------- hàm sinh không in (gọi đúng hàm của comb_gen.cpp) ----------

void genPerm(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    do { bCnt++; } while (nextPermutation(a));
}
void genComb(int n, int k) {
    vector<int> a(k);
    iota(a.begin(), a.end(), 1);
    do { bCnt++; } while (nextCombination(a, n));
}
void genGray(int n) { // giống graycode() nhưng không in
    vector<bool> seen(1 << n, false);
    int previous = -1;
    for (int i = 0; i < (1 << n); i++) {
        int gray = i ^ (i >> 1);
        verifyGray(gray, previous, seen);
        previous = gray;
        bCnt++;
    }
}

// ---------- chạy một bộ dữ liệu ----------

// time_ratio = thời gian dòng này / dòng trước, formula_ratio = công thức dòng này / dòng trước.
// Hai tỉ lệ gần bằng nhau nghĩa là thời gian tăng đúng theo công thức.
template<class F> void run(const string& algo, int n, int k, long long formula, F fn) {
    static string prevAlgo;
    static double prevMs, prevFormula;

    double ms = medianMs(fn);
    ostringstream line;
    line << setprecision(4) << algo << ',' << n << ',' << k << ',' << formula << ',' << ms << ','
         << ms * 1e6 / formula << ',';
    if (algo == prevAlgo) line << ms / prevMs << ',' << (double)formula / prevFormula;
    else line << ',';
    line << '\n';

    cout << line.str();
    csv << line.str();
    if (bCnt != formula) cout << "  ^ SAI SO LUONG: dem duoc " << bCnt << "\n";

    prevAlgo = algo;
    prevMs = ms;
    prevFormula = formula;
}

void runBenchmark() {
    csv.open("bench_results.csv");
    string header = "algo,n,k,formula,median_ms,ns_per_item,time_ratio,formula_ratio\n";
    cout << header;
    csv << header;

    for (int n = 8; n <= 12; n++)                                   // hoán vị: n!
        run("permutation", n, 0, fact(n), [&] { genPerm(n); });
    for (int n = 16; n <= 30; n += 2)                               // tổ hợp: C(n, n/2)
        run("combination", n, n / 2, binom(n, n / 2), [&] { genComb(n, n / 2); });
    for (int n = 16; n <= 28; n += 2)                               // Gray Code: 2^n
        run("gray", n, 0, 1LL << n, [&] { genGray(n); });

    csv.close();
    cout << "Da ghi ket qua vao bench_results.csv\n";
}
#endif
