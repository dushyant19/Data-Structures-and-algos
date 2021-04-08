

struct segtree{
    int size;
    vector<vi> tree_array;
    void init(int n){
        size=1;
        while(size<n)
        size*=2;
        size1=size;
        vi v{};
        tree_array.assign(2*size,v);
    }

    void build(vi& a,int x,int lx,int rx){
        if(rx-lx==1){
            tree_array[x].push_back(a[lx]);
            return;
        }
        int mid = lx + (rx-lx)/2;
        build(a,2*x+1,lx,mid);
        build(a,2*x+2,mid,rx);
        merge(tree_array[2*x+1],tree_array[2*x+2],tree_array[x]);
    }

    void set(int i,int v,int x,int lx,int rx){
        if(rx-lx==1){
            tree_array[x].push_back(v);
            return;
        }
        int m = lx + (rx-lx)/2;
        if(i<m){
            set(i,v,2*x+1,lx,m);
        }else{
            set(i,v,2*x+2,m,rx);
        }
        merge(tree_array[2*x+1],tree_array[2*x+2],tree_array[x]);
    }

    void set(int i,int v){
        set(i,v,0,0,size);
    }

    int query(int l,int r,int k,int x,int lx,int rx){
        if(lx>=r||rx<=l)return 0;
        if(lx>=l&&rx<=r){
            int ans = upper_bound(all(tree_array[x]),k) - tree_array[x].begin();
            return ans; 
        }
        int m = lx + (rx-lx)/2;
        int left = query(l,r,k,2*x+1,lx,m);
        int right = query(l,r,k,2*x+2,m,rx);
        return left+right;
    }

    int query(int l,int r,int k){
        return query(l,r,k,0,0,size);
    }
};