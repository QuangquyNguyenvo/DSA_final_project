#include<bits/stdc++.h>
#define ll long long
using namespace std;
bool hoanvi(vector<int>& a){ 
    int i=a.size()-2;
    while(i>=0 && a[i]>=a[i+1]) i--; 
    if(i<0) return false; 

    int j=a.size()-1; 
    while(a[j]<=a[i]) j--; 

    swap(a[i],a[j]); 
    reverse(a.begin()+i+1, a.end());
    return true;
}
bool tohop(vector<int>& a, int n){ //xây dựng tổ hợp tiếp theo trong tập phần tử: 1->n, với size tổ hợp là k
    int k = a.size(); //số lượng phần tử trong tổ hơp
    int i=k-1; //bắt đầu khởi tạo từ sau cùng 
    while(i>=0 && a[i]==n-k+i+1) i--; //tìm giá trị bên phải chưa cực đại còn cho phép
    if(i<0) return false; //kiểm tra, thoát nếu k còn tổ hợp nào thêm nữa
    a[i]++; //tăng phần tử tìm được lên 1 để có giá trị tiếp theo
    for(int j=i+1;j<k;j++) a[j]=a[j-1]+1; //đảm bảo sau i có thứ tự từ điển nhỏ nhất
    return true;//tìm được thì trả lại
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
        cout<<"0. Exit \n choice: ";
        ll choice; cin>>choice; 
        if(choice==1) { // lexicographic permutation
            ll n; cout<<"n: "; cin>>n;
            //lat them checker o day
            vector<int> a(n);
            for(int i=0;i<n;i++) cout<<"a["<<i<<"]: ",cin>>a[i];
            sort(a.begin(),a.end());
            ll cnt=0;
            do{
                print(a);
                cnt++; 
            } while(hoanvi(a));
            cout<<"total permutation: "<<cnt<<'\n';
        }
        else if(choice==2){//combination
            ll n,k; cout<<"n k: "; cin>>n>>k; 
            //de tranh lap vo tan
            if(n<0||n>20 || k<0 || k>n) {
                cout<<"nhap sai n roi kia \n";
                continue;
            }
            vector<int> a(k);
            //tao subset n {1,....,n}
            for(int i=0; i<k; i++) a[i]=i+1;
            //combination
            ll cnt=0;
            do{
                print(a);
                cnt++;
            } while(tohop(a,n));
            cout<<"total permutation: "<<cnt<<'\n';

        }
    }
}