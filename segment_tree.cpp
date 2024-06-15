#include<bits/stdc++.h>
using namespace std;
#define ll long long int
 
class SGTree{
   vector<int>seg;
public:
    SGTree(int n){
        seg.resize(4*n+1);
    }
    void build(int ind, int low, int high, int arr[]){
        if(low==high){
            seg[ind]=arr[low]; return;
        }
        int mid=low+(high-low)/2;
        build(2*ind+1,low, mid, arr);
        build(2*ind+2, mid+1, high, arr);
        seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
    }
    int query(int ind, int low, int high, int l, int r){
        if(r<low or high<l){return INT_MAX;}
        if(low>=l and high<=r){return seg[ind];}
        
        int mid=low+(high-low)/2;
        int left=query(2*ind+1, low, mid, l, r);
        int right=query(2*ind+2, mid+1, high, l, r);
        return min(left, right);
    }
    void update(int ind, int low, int high, int i, int val){
        if(low==high){seg[ind]=val; return;}
        int mid=low+(high-low)/2;
        if(i<=mid){update(2*ind+1, low, mid, i, val);}
        else{update(2*ind+2, mid+1, high, i, val);}
        seg[ind]=min(seg[2*ind+1], seg[2*ind+2]);
    }
    void print(){
        for(auto B: seg){cout<<B<<" ";}
    }
};
void solve(){
    int n; cin>>n;
    int arr[n];
    for(int i=0; i<n; i++){cin>>arr[i];}
    SGTree sg1(n); 
    sg1.build(0,0,n-1,arr);

    // for update
    int t; cin>>t;
    while(t--){
        int i, val; cin>>i>>val;
        sg1.update(0,0,n-1,i,val);
        arr[i]=val;
    } 

    // to get min in range l to r
    int q; cin>>q;
    while(q--){
        int l, r; cin>>l>>r;
        int minn=sg1.query(0,0,n-1,l,r);
        cout<<minn<<"\n";
    }
}

int main()
{  
    solve();
    return 0;
}
