#pragma once
// Benchmark: đo thời gian sinh (không in) của 3 thuật toán, so với công thức n!, C(n,k), 2^n
// Kết quả in ra màn hình và ghi vào bench_results.csv
#include<bits/stdc++.h>
#define ll long long
using namespace std;

// các hàm định nghĩa trong comb_gen.cpp
bool nextPermutation(vector<int>& a);
bool nextCombination(vector<int>& a, int n);

// tính n! = số hoán vị của n phần tử
ll fact(int n){
    ll r=1;
    for(int i=2;i<=n;i++) r*=i;
    return r;
}
// tính C(n,k) = số cách chọn k phần tử từ n phần tử
ll binom(int n, int k){
    ll r=1;
    for(int i=1;i<=k;i++) r=r*(n-k+i)/i; //sau bước này r = C(n-k+i, i) nên phép chia luôn hết
    return r;
}
ll grayXor = 0; //XOR dồn các mã Gray để trình biên dịch không bỏ vòng lặp khi tối ưu -O2
// sinh toàn bộ cấu hình nhưng không in, trả về số cấu hình đã sinh
ll generate(const string& algo, int n, int k){ // algo: "permutation" = hoán vị, "combination" = tổ hợp, "gray" = Gray Code
    ll cnt=0;
    if(algo=="permutation"){
        vector<int> a(n);
        for(int i=0;i<n;i++) a[i]=i+1; //hoán vị đầu tiên {1..n}
        do cnt++; while(nextPermutation(a));
    }
    else if(algo=="combination"){
        vector<int> a(k);
        for(int i=0;i<k;i++) a[i]=i+1; //tổ hợp đầu tiên {1..k}
        do cnt++; while(nextCombination(a,n));
    }
    else{
        for(int i=0;i<(1<<n);i++){
            grayXor ^= i^(i>>1); //mã Gray thứ i
            cnt++;
        }
    }
    return cnt;
}

// chạy 1 lần khởi động + 5 lần đo, trả về median thời gian (ms)
double measure(const string& algo, int n, int k, ll& cnt){
    vector<double> times;
    for(int r=0;r<=5;r++){
        auto start=chrono::steady_clock::now();
        cnt=generate(algo,n,k);
        auto end=chrono::steady_clock::now();
        if(r>0) times.push_back(chrono::duration<double, milli>(end-start).count()); //bỏ lần khởi động
    }
    sort(times.begin(),times.end());
    return times[2]; //median của 5 lần
}

// đo một thuật toán với n chạy từ from đến to (bước step), mỗi n in và ghi một dòng
void runAlgo(ofstream& csv, const string& algo, int from, int to, int step){
    double prevTime=0; //thời gian của dòng trước, 0 = chưa có
    ll prevTotal=0;    //số cấu hình của dòng trước
    for(int n=from;n<=to;n+=step){
        int k=0;
        ll total; //số cấu hình theo công thức
        if(algo=="permutation") total=fact(n);
        else if(algo=="combination"){
            k=n/2;
            total=binom(n,k);
        }
        else total=1LL<<n;

        ll cnt;
        double time=measure(algo,n,k,cnt);

        ostringstream line;
        line<<setprecision(4)<<algo<<','<<n<<','<<k<<','<<total<<','<<time<<','<<time*1e6/total<<',';
        if(prevTime>0) line<<time/prevTime<<','<<(double)total/prevTotal; //2 tỉ lệ gần nhau = tăng đúng công thức
        else line<<',';
        line<<'\n';
        cout<<line.str();
        csv<<line.str();

        if(cnt!=total) cout<<"  ^ SAI SO LUONG: dem duoc "<<cnt<<"\n"; //phải khớp n!, C(n,k), 2^n
        prevTime=time;
        prevTotal=total;
    }
}

void runBenchmark(){
    ofstream csv("bench_results.csv");
    string header="algo,n,k,formula,median_ms,ns_per_item,time_ratio,formula_ratio\n"; //thead của cái bảng csv xuất ra
    cout<<"Dang do, mat khoang 10-15 giay...\n"<<header;
    csv<<header;
    //runAlgo(file csv, algo, from, to, step)
    runAlgo(csv, "permutation", 8, 12, 1);  //hoán vị: n!, n từ 8 đến 12
    runAlgo(csv, "combination", 16, 30, 2); //tổ hợp: C(n, n/2), n từ 16 đến 30, mỗi lần tăng 2
    runAlgo(csv, "gray", 16, 28, 2);        //Gray Code: 2^n, n từ 16 đến 28, mỗi lần tăng 2
    cout<<"Da ghi ket qua vao bench_results.csv\n";
}
