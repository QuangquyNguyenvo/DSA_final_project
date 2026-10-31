#include<bits/stdc++.h>
#define ll long long
using namespace std;
#include "benchmark.h"
// màu chữ dùng mã ANSI escape (vd \033[33m = vàng, \033[0m = về màu mặc định)
// nguồn: https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences

bool nextPermutation(vector<int>& a){
    int i=static_cast<int>(a.size())-2;
    while(i>=0 && a[i]>=a[i+1]) i--; //tìm pivot: vị trí phải nhất có a[i] < a[i+1]
    if(i<0) return false; //dãy giảm dần -> hết hoán vị

    int j=a.size()-1;
    while(a[j]<=a[i]) j--; //tìm phần tử phải nhất lớn hơn pivot

    swap(a[i],a[j]);
    reverse(a.begin()+i+1, a.end()); //đoạn sau pivot đang giảm dần, đảo lại cho nhỏ nhất
    return true;
}
bool nextCombination(vector<int>& a, int n){
    int k = a.size();
    int i=k-1;
    while(i>=0 && a[i]==n-k+i+1) i--; //bỏ qua vị trí đã đạt giá trị tối đa n-k+i+1
    if(i<0) return false; //mọi vị trí đều tối đa -> hết tổ hợp
    a[i]++;
    for(int j=i+1;j<k;j++) a[j]=a[j-1]+1; //đặt phần sau về nhỏ nhất (tăng dần liên tiếp)
    return true;
}
// Kiểm tra một mã Gray vừa được sinh ra.
// Hàm nhận đúng giá trị mà graycode() đã in, không tự sinh lại mã bằng công thức.
bool verifyGray(int current, int previous, vector<bool>& seen){
    int total = seen.size(); //số tập con 2^n

    //1. kiểm tra phạm vi
    if(current<0 || current>=total) return false;

    //2. kiểm tra trùng lặp
    if(seen[current]) return false;
    seen[current] = true;

    //3. check xem có thật sự đảo đúng chính xác 1 bit không
    if(previous!=-1){
        int diff = previous ^ current;
        if(__builtin_popcount(diff)!=1) return false;
    }
    return true;
}
// Đếm hoán vị phân biệt của dãy đã sắp xếp, có tính phần tử trùng.
ll permutationCount(const vector<int>& a){
    ll denominator=1;
    for(size_t i=0; i<a.size();){
        size_t j=i+1;
        while(j<a.size() && a[j]==a[i]) j++;
        denominator*=fact(static_cast<int>(j-i));
        i=j;
    }
    return fact(static_cast<int>(a.size()))/denominator;
}
// limit > 0: dừng sau limit mã. limit = 0: sinh và kiểm tra toàn bộ.
bool graycode(int n, ll limit){
    int total = 1<<n; //2^n
    int count = limit==0 ? total : static_cast<int>(min<ll>(limit,total));
    vector<bool> seen;
    if(count==total) seen.assign(total, false);
    int previous = -1; // -1 = chưa có mã trước nó
    int cnt = 0; //đếm số mã đã sinh
    bool ok = true;

    for(int i=0; i<count;i++) {
        int gray= i^(i>>1);
        if(limit==0 || cnt<limit){ //chỉ in limit mã đầu tiên
            cout<<"{ ";
            for(int j=n-1; j>=0;j--) cout<<((gray>>j)&1)<<" ";
            cout<<"} -> {";
            bool first = true;
            for(int j=n-1; j>=0; j--) if((gray>>j)&1){
                if(!first) cout<<", ";
                cout<<n-j;
                first = false;
            }
            cout<<"}\n";
        }

        if(count==total){
            if(!verifyGray(gray, previous, seen)) ok = false;
        } else if(previous!=-1 && __builtin_popcount(previous^gray)!=1){
            ok = false;
        }
        previous = gray;
        cnt++;
    }
    if(count<total) cout<<"...\n";
    cout<<"\033[36m"<<"Da sinh: "<<cnt<<"\nTong so ma Gray theo cong thuc: "<<total<<"\033[0m"<<'\n';
    if(count<total) cout<<"Chi kiem tra tinh chat 1 bit tren cac ma da sinh.\n";
    return ok && cnt==count;
}
void print(const vector<int>& a){
    cout<<"{";
    for(int i=0;i<(int)a.size();i++) {
        if(i) cout<<", ";
        cout<<a[i];
    }
    cout<<"}\n";
}

// đọc một số nguyên; nhập chữ thì báo lỗi, xóa lỗi của cin và trả về false để quay lại menu
template<class T> bool readNumber(T& x){
    if(cin>>x) return true;
    cin.clear();
    cin.ignore(1000, '\n');
    cout<<"\033[31m"<<"Loi: can nhap so nguyen"<<"\033[0m"<<"\n";
    return false;
}

// hỏi số cấu hình đầu tiên cần in, trả về -1 nếu nhập sai
ll readLimit(){
    ll limit;
    cout<<"So cau hinh muon in (0 = tat ca): ";
    if(!(cin>>limit) || limit<0){
        cin.clear(); //nhập chữ làm cin bị lỗi, xóa trạng thái lỗi để quay lại menu được
        cin.ignore(1000, '\n'); //bỏ phần chữ còn lại trên dòng vừa nhập (tối đa 1000 ký tự)
        cout<<"\033[31m"<<"Loi: so cau hinh can in phai >= 0"<<"\033[0m"<<"\n";
        return -1;
    }
    return limit;
}

// Giữ ngưỡng 10! để vẫn cho phép các test in toàn bộ hoán vị n <= 10.
constexpr ll MAX_FULL_OUTPUT=3628800;
bool checkOutputLimit(ll total, ll limit){
    if(limit!=0 || total<=MAX_FULL_OUTPUT) return true;
    cout<<"\033[31m"<<"Loi: tong so cau hinh la "<<total
        <<", vuot nguong in tat ca "<<MAX_FULL_OUTPUT
        <<". Hay nhap limit > 0."<<"\033[0m"<<"\n";
    return false;
}

int main() {
    ios::sync_with_stdio(false); //tách cin/cout khỏi printf/scanf để in nhanh hơn (chương trình chỉ dùng cin/cout)
    while(true){
        cout<<"\033[33m"<<"===========COMBINATION GENERATOR==========="<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     1. Sinh hoan vi (Algorithm L)"<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     2. Sinh to hop chap k cua n"<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     3. Sinh tap con bang Gray Code"<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     4. Benchmark"<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     0. Thoat"<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"============================================"<<"\033[0m"<<"\n";
        cout<<"\033[36m"<<"  -> Lua chon: "<<"\033[0m";
        ll choice;
        if(!(cin>>choice)) break; //nhập chữ thay vì số thì dừng while để thoát chương trình
        if(choice==0) break;
        if(choice==1) { // lexicographic permutation (hoán vị)
            cout<<"\033[33m"<<"============================================"<<"\033[0m"<<"\n";
            ll n; cout<<"So luong phan tu (n): ";
            if(!readNumber(n)) continue;
            //20! vẫn nằm trong long long.
            cout<<"--------------------------------------------\n";
            if(n<0||n>20) {
                cout<<"\033[31m"<<"Loi: n phai thoa 0 <= n <= 20"<<"\033[0m"<<"\n";
                continue;
            }
            vector<int> a(n);
            bool ok=true;
            for(int i=0;i<n && ok;i++) { //nhập phần tử
                cout<<"Phan tu ["<<i<<"] = ";
                ok=readNumber(a[i]);
            }
            if(!ok) continue;
            ll limit=readLimit();
            if(limit<0) continue;
            sort(a.begin(),a.end()); //sắp xếp về hoán vị đầu tiên
            ll total=permutationCount(a);
            if(!checkOutputLimit(total,limit)) continue;
            ll cnt=0;//đếm lượt hoán vị
            cout<<"--------------------------------------------\n";
            do{
                print(a);
                cnt++;
                if(limit>0 && cnt>=limit) break;
            } while(nextPermutation(a)); //tìm hoán vị tiếp theo, false là hết
            if(cnt<total) cout<<"...\n";
            cout<<"\033[36m"<<"Da sinh: "<<cnt<<"\nTong so hoan vi theo cong thuc: "<<total<<"\033[0m"<<'\n';
            cout<<"\n";
        }
        else if(choice==2){
            cout<<"\033[33m"<<"============================================"<<"\033[0m"<<"\n";
            ll n,k; cout<<"Co bao nhieu phan tu {1->n}: "; //chọn k phần tử từ {1..n}
            if(!readNumber(n)) continue;
            cout<<"--------------------------------------------\n";
            cout<<"Kich thuoc cua to hop: ";
            if(!readNumber(k)) continue;
            cout<<"--------------------------------------------\n";
            //chặn k > n, số âm và n quá lớn
            if(n<0||n>20 || k<0 || k>n) {
                cout<<"\033[31m"<<"Loi: can 0 <= k <= n <= 20"<<"\033[0m"<<"\n";
                continue;
            }
            ll limit=readLimit();
            if(limit<0) continue;
            ll total=binom(n,k);
            if(!checkOutputLimit(total,limit)) continue;
            cout<<"--------------------------------------------\n";
            vector<int> a(k);
            //tổ hợp đầu tiên {1,2,...,k}
            for(int i=0; i<k; i++) a[i]=i+1;
            ll cnt=0; //đếm lượt tạo tổ hợp
            do{
                print(a);
                cnt++;
                if(limit>0 && cnt>=limit) break;
            } while(nextCombination(a,n)); //lặp đến khi nextCombination trả false (hết tổ hợp)
            if(cnt<total) cout<<"...\n";
            cout<<"\033[36m"<<"Da sinh: "<<cnt<<"\nTong so to hop theo cong thuc: "<<total<<"\033[0m"<<'\n';
            cout<<"\n";

        }
        else if(choice==3){
            cout<<"\033[33m"<<"============================================"<<"\033[0m"<<"\n";
            int n; cout<<"Kich thuoc cua cac tap con Gray Code: ";
            if(!readNumber(n)) continue;
            //chặn n âm (1<<n không hợp lệ) và n > 30 (1<<n tràn int)
            cout<<"--------------------------------------------\n";
            if(n<0||n>30) {
                cout<<"\033[31m"<<"Loi: n phai thoa 0 <= n <= 30"<<"\033[0m"<<"\n";
                continue;
            }
            ll limit=readLimit();
            if(limit<0) continue;
            if(!checkOutputLimit(1LL<<n,limit)) continue;
            cout<<"--------------------------------------------\n";
            if(graycode(n, limit)) cout<<"\033[36m"<<"Kiem tra cac ma Gray da sinh: DUNG"<<"\033[0m"<<"\n";
            else cout<<"\033[31m"<<"Kiem tra cac ma Gray da sinh: SAI"<<"\033[0m"<<"\n";
            cout<<"\n";
        }
        else if(choice==4){
            runBenchmark(); //đo thời gian 3 thuật toán, ghi kết quả vào results/bench_results.csv
            cout<<"\n";
        }
    }
}
