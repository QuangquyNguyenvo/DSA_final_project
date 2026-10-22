#include<bits/stdc++.h>
#define ll long long
using namespace std;
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
// Gray Code
void graycode(int n){
    int total = 1<<n; //2^n

    for(int i=0; i<total;i++) {
        int gray= i^(i>>1);
        cout<<"{ ";
        for(int j=n-1; j>=0;j--) cout<<((gray>>j)&1)<<" ";
        cout<<"}\n";
    }
    cout<<"Tong so ma Gray: "<<total<<'\n';
}
// Verify xem gray code mình sinh ra có đúng quy tắc không
bool verifyGray(int n){
    int total = 1<<n; //số tập con 2^n
    int previous = -1; // -1 = chưa có mã trước nó
    vector<bool> seen(total, false); //seen[i]=true if x đã xuất hiện
    int cnt=0; //đếm số tập đã sinh

    for(int i=0;i<total;i++){
        //tạo lại graycode theo quy tắc của mình;
        int current = i^(i>>1);
        
        //1. kiểm tra phạm vi
        if(current<0 || current>=total) return false;

        //2. kiểm tra trùng lặp
        if(seen[current]) return false;
        else seen[current] = true;

        //3. check xem có thật sự đảo đúng chính xác 1 bit không
        if(previous!=-1){
            int diff = previous ^ current;
            if(__builtin_popcount(diff)!=1) return false;
        } 
        previous = current;
        cnt++;
    }
    return cnt==total; //4. tổng số tập đã sinh đúng bằng 2^n;
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
        cout<<"1. Sinh hoan vi (Algorithm L)\n";
        cout<<"2. Sinh to hop chap k cua n\n";
        cout<<"3. Sinh tap con bang Gray Code\n";
        cout<<"0. Thoat\n Lua chon: ";
        ll choice;
        if(!(cin>>choice)) break; //nhập chữ thay vì số thì dừng while để thoát chương trình
        if(choice==0) break;
        if(choice==1) { // lexicographic permutation (hoán vị)
            ll n; cout<<"n: "; cin>>n;
            //chặn n âm (có thể gây crash) và n quá lớn (sẽ in quá nhiều dòng)
            if(n<0||n>10) {
                cout<<"Loi: n phai thoa 0 <= n <= 10\n";
                continue;
            }
            vector<int> a(n);
            for(int i=0;i<n;i++) cout<<"a["<<i<<"]: ",cin>>a[i]; //nhập phần tử
            sort(a.begin(),a.end()); //sắp xếp về hoán vị đầu tiên
            ll cnt=0;//đếm lượt hoán vị
            do{
                print(a);
                cnt++;
            } while(nextPermutation(a)); //tìm hoán vị tiếp theo, false là hết
            cout<<"Tong so hoan vi: "<<cnt<<'\n'; //để đối chiếu với n!
        }
        else if(choice==2){
            ll n,k; cout<<"n k: "; cin>>n>>k; //chọn k phần tử từ {1..n}
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
            cout<<"Tong so to hop: "<<cnt<<'\n'; //để đối chiếu với C(n,k)

        }
        else if(choice==3){
            int n; cout<<"n: "; cin>>n;
            //chặn n âm (1<<n không hợp lệ) và n > 30 (1<<n tràn int)
            if(n<0||n>30) {
                cout<<"Loi: n phai thoa 0 <= n <= 30\n";
                continue;
            }
            graycode(n);
            if(verifyGray(n)) cout<<"Kiem tra Gray Code: DUNG\n";
            else cout<<"Kiem tra Gray Code: SAI\n";
        }
    }
}
