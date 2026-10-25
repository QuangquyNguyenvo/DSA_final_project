#include<bits/stdc++.h>
#define ll long long
using namespace std;
#include "benchmark.h"
//hiện tại việc đổi màu đang dựa vào các mã ANSI escape, nó phần nào tác động vào terminal khi terminal thực hiện đọc code và visualize
//nguồn: https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences

bool nextPermutation(vector<int>& a){
    int i=a.size()-2;
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
bool legacyNextGray(vector<int>& a, int& tmp){
    tmp ^= 1; //lật cộng thêm 1 hoặc chuyển đổi kế tiếp
    int j = 0;
    if(tmp == 0){
        while(j < (int)a.size() && a[j] != 1){
            ++j; //tăng lên tìm 1 gần nhất
        } ++j; //số ngay sau 1
    }
    if(j >= (int)a.size()) return false; //đã hết
    a[j] ^= 1; //lật tại 0 hoặc sau j đã tìm thấy 1
    return true; //tìm tiếp
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
// Gray Code: sinh, in và đưa từng mã qua verifyGray() để kiểm tra
bool graycode(int n){
    int total = 1<<n; //2^n
    vector<bool> seen(total, false); //seen[x]=true nếu mã x đã xuất hiện
    int previous = -1; // -1 = chưa có mã trước nó
    int cnt = 0; //đếm số mã đã sinh
    bool ok = true;

    for(int i=0; i<total;i++) {
        int gray= i^(i>>1);
        cout<<"{ ";
        for(int j=n-1; j>=0;j--) cout<<((gray>>j)&1)<<" ";
        cout<<"}\n";

        if(!verifyGray(gray, previous, seen)) ok = false;
        previous = gray;
        cnt++;
    }
    cout<<"\033[36m"<<"Tong so ma Gray: "<<cnt<<"\033[0m"<<'\n';
    return ok && cnt==total; //4. tổng số mã đã sinh đúng bằng 2^n
}
void print(const vector<int>& a){
    cout<<"{";
    for(int i=0;i<(int)a.size();i++) {
        if(i) cout<<", ";
        cout<<a[i];
    }
    cout<<"}\n";
}

int main() {
    while(true){
        cout<<"\033[33m"<<"===========COMBINATION GENERATOR==========="<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     1. Sinh hoan vi (Algorithm L)"<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     2. Sinh to hop chap k cua n"<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     3. Sinh tap con bang Gray Code"<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     4. Benchmark"<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"     0. Thoat\n ";
        cout<<"\033[36m"<<" -> Lua chon: "<<"\033[0m"<<"\n";
        cout<<"\033[33m"<<"============================================"<<"\033[0m"<<"\n";
        ll choice;
        if(!(cin>>choice)) break; //nhập chữ thay vì số thì dừng while để thoát chương trình
        if(choice==0) break;
        if(choice==1) { // lexicographic permutation (hoán vị)
            cout<<"\033[33m"<<"============================================"<<"\033[0m"<<"\n";
            ll n; cout<<"So luong phan tu (n): "; cin>>n;
            //chặn n âm (có thể gây crash) và n quá lớn (sẽ in quá nhiều dòng)
            cout<<"--------------------------------------------\n";
            if(n<0||n>10) {
                cout<<"Loi: n phai thoa 0 <= n <= 10\n";
                continue;
            }
            vector<int> a(n);
            for(int i=0;i<n;i++) cout<<"Phan tu ["<<i<<"] = ", cin>>a[i]; //nhập phần tử
            sort(a.begin(),a.end()); //sắp xếp về hoán vị đầu tiên
            ll cnt=0;//đếm lượt hoán vị
            cout<<"--------------------------------------------\n";
            do{
                print(a);
                cnt++;
            } while(nextPermutation(a)); //tìm hoán vị tiếp theo, false là hết
            cout<<"\033[36m"<<"Tong so hoan vi: "<<cnt<<"\033[0m"<<'\n'; //để đối chiếu với n!
            cout<<"\n";
        }
        else if(choice==2){
            cout<<"\033[33m"<<"============================================"<<"\033[0m"<<"\n";
            ll n,k; cout<<"Co bao nhieu phan tu {1->n}: "; cin>>n; //chọn k phần tử từ {1..n}
            cout<<"--------------------------------------------\n";
            cout<<"Kich thuoc cua to hop: "; cin>>k;
            cout<<"--------------------------------------------\n";
            //chặn k > n, số âm và n quá lớn
            if(n<0||n>20 || k<0 || k>n) {
                cout<<"Loi: can 0 <= k <= n <= 20\n";
                continue;
            }
            vector<int> a(k);
            //tổ hợp đầu tiên {1,2,...,k}
            for(int i=0; i<k; i++) a[i]=i+1;
            ll cnt=0; //đếm lượt tạo tổ hợp
            do{
                print(a);
                cnt++;
            } while(nextCombination(a,n)); //lặp đến khi nextCombination trả false (hết tổ hợp)
            cout<<"\033[36m"<<"Tong so to hop: "<<cnt<<"\033[0m"<<'\n'; //để đối chiếu với C(n,k)
            cout<<"\n";

        }
        else if(choice==3){
            cout<<"\033[33m"<<"============================================"<<"\033[0m"<<"\n";
            int n; cout<<"Kich thuoc cua cac tap con Greycode: "; cin>>n;
            //chặn n âm (1<<n không hợp lệ) và n > 30 (1<<n tràn int)
            cout<<"--------------------------------------------\n";
            if(n<0||n>30) {
                cout<<"Loi: n phai thoa 0 <= n <= 30\n";
                continue;
            }
            if(graycode(n)) cout<<"\033[36m"<<"Kiem tra Gray Code: DUNG"<<"\033[0m"<<"\n";
            else cout<<"\033[31m"<<"Kiem tra Gray Code: SAI""\033[0m"<<"\n";
            cout<<"\n";
        }
        else if(choice==4){
            runBenchmark(); //đo thời gian 3 thuật toán, ghi kết quả vào bench_results.csv
            cout<<"\n";
        }
    }
}
