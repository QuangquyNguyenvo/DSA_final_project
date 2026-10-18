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
bool tohop(vector<int>& a, int n){
    int k = a.size();
    int i=k-1; 
    while(i>=0 && a[i]==n-k+i+1) i--; 
    if(i<0) return false;
    a[i]++; 
    for(int j=i+1;j<k;j++) a[j]=a[j-1]+1;
    return true;
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
        if(choice==1) { // lexicographic permutation (hoán vị)
            ll n; cout<<"n: "; cin>>n;
            //lật thêm checker ở đây
            vector<int> a(n); //lập vector
            for(int i=0;i<n;i++) cout<<"a["<<i<<"]: ",cin>>a[i]; //nhập phần tử
            sort(a.begin(),a.end()); //sắp xếp về hoán vị đầu tiên
            ll cnt=0;//đếm lượt hoán vị
            do{
                print(a);
                cnt++; 
            } while(hoanvi(a)); //thực hiện tìm hoán vị tiếp theo cho đến khi trả lại false (tức là hết)
            cout<<"total permutation: "<<cnt<<'\n'; //trả về lượt hoán vị để kiểm chứng
        }
        else if(choice==2){//combination
            ll n,k; cout<<"n k: "; cin>>n>>k; //nhập barrier n và size k
            //để tránh nhập vô tận
            if(n<0||n>20 || k<0 || k>n) {
                cout<<"nhap sai n roi kia \n";
                continue;
            }
            vector<int> a(k);
            //tạo subset n {1,....,n}
            for(int i=0; i<k; i++) a[i]=i+1;
            //combination
            ll cnt=0; //đếm lượt tạo tổ hợp
            do{
                print(a);
                cnt++; //tăng lên khi thao tác
            } while(tohop(a,n)); //trả về tổ hợp khi còn true
            cout<<"total permutation: "<<cnt<<'\n'; //trả về lượt tạo để kiểm chứng

        }
    }
}