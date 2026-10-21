#include<bits/stdc++.h>
#define ll long long
using namespace std;
bool hoanvi(vector<int>& a){
    int i=a.size()-2;
    while(i>=0 && a[i]>=a[i+1]) i--; //tìm pivot: vị trí phải nhất có a[i] < a[i+1]
    if(i<0) return false; //dãy giảm dần -> hết hoán vị

    int j=a.size()-1;
    while(a[j]<=a[i]) j--; //tìm phần tử phải nhất lớn hơn pivot

    swap(a[i],a[j]);
    reverse(a.begin()+i+1, a.end()); //đoạn sau pivot đang giảm dần, đảo lại cho nhỏ nhất
    return true;
}
bool tohop(vector<int>& a, int n){
    int k = a.size();
    int i=k-1;
    while(i>=0 && a[i]==n-k+i+1) i--; //bỏ qua vị trí đã đạt giá trị tối đa n-k+i+1
    if(i<0) return false; //mọi vị trí đều tối đa -> hết tổ hợp
    a[i]++;
    for(int j=i+1;j<k;j++) a[j]=a[j-1]+1; //đặt phần sau về nhỏ nhất (tăng dần liên tiếp)
    return true;
}
bool NextGray(vector<int>& a, int& tmp){
    tmp ^= 1; //lật cộng thêm 1 hoặc chuyển đổi kế tiếp
    int j = 0; 
    if(tmp == 0){
        while(j < a.size() && a[j] != 1){
            ++j; //tăng lên tìm 1 gần nhất
        } ++j; //số ngay sau 1
    }
    if(j >= a.size()) return false; //đã hết
    a[j] ^= 1; //lật tại 0 hoặc sau j đã tìm thấy 1
    return true; //tìm tiếp
}
void print(const vector<int>& a){
    cout<<"{";
    for(int i=0;i<a.size();i++) {
        if(i) cout<<", ";
        cout<<a[i];
    }
    cout<<"}\n";
}

int main() {
    while(true){
        cout<<"1. hoan vi \n";
        cout<<"2. to hop \n";
        cout<<"3. tap con Greycode\n";
        cout<<"0. Exit \n choice: ";
        ll choice;
        if(!(cin>>choice)) break; //nhập chữ thay vì số thì dừng while để thoát chương trình
        if(choice==0) break;
        if(choice==1) { // lexicographic permutation (hoán vị)
            ll n; cout<<"n: "; cin>>n;
            //chặn n âm (có thể gây crash) và n quá lớn (sẽ in quá nhiều dòng)
            if(n<0||n>10) {
                cout<<"nhap sai n roi kia (0 <= n <= 10) \n";
                continue;
            }
            vector<int> a(n);
            for(int i=0;i<n;i++) cout<<"a["<<i<<"]: ",cin>>a[i]; //nhập phần tử
            sort(a.begin(),a.end()); //sắp xếp về hoán vị đầu tiên
            ll cnt=0;//đếm lượt hoán vị
            do{
                print(a);
                cnt++;
            } while(hoanvi(a)); //tìm hoán vị tiếp theo, false là hết
            cout<<"total permutation: "<<cnt<<'\n'; //để đối chiếu với n!
        }
        else if(choice==2){
            ll n,k; cout<<"n k: "; cin>>n>>k; //chọn k phần tử từ {1..n}
            //chặn k > n, số âm và n quá lớn
            if(n<0||n>20 || k<0 || k>n) {
                cout<<"nhap sai n roi kia \n";
                continue;
            }
            vector<int> a(k);
            //tổ hợp đầu tiên {1,2,...,k}
            for(int i=0; i<k; i++) a[i]=i+1;
            ll cnt=0; //đếm lượt tạo tổ hợp
            do{
                print(a);
                cnt++;
            } while(tohop(a,n)); //lặp đến khi tohop trả false (hết tổ hợp)
            cout<<"total combination: "<<cnt<<'\n'; //để đối chiếu với C(n,k)

        }
        else if(choice==3){
            cout <<"kích cỡ subset mã Grey: ";
            int n; cin >> n;
            int tmp = 0;
            vector<int> a(n, 0); //bắt đầu với subset đầu tiên: 000...0
            int cnt = 1;
            do{  
            cout<< cnt <<setw(2)<<". { ";
                 for(auto x:a){
                    cout << x <<" ";
                }
                cout <<"}\n";
                  cnt++;
            } while(NextGray(a, tmp));
        }
    }
}
