struct segtree{
    int size;
    vector<int> tree_array;
    void init(int n){
        size=1;
        while(size<n)
        size*=2;
        tree_array.assign(2*size,INT_MAX);
    }

    void set(int i,int v,int x,int lx,int rx){
        if(rx-lx==1){
            tree_array[x] = v;
            return;
        }
        int m = lx + (rx-lx)/2;
        if(i<m){
            set(i,v,2*x+1,lx,m);
        }else{
            set(i,v,2*x+2,m,rx);
        }
        tree_array[x] = min(tree_array[2*x+1],tree_array[2*x+2]);
    }

    void set(int i,int v){
        set(i,v,0,0,size);
    }

    int query(int l,int r,int x,int lx,int rx){
        if(lx>=r||rx<=l)return INT_MAX;
        if(lx>=l&&rx<=r)return tree_array[x];
        int m = lx + (rx-lx)/2;
        int left = query(l,r,2*x+1,lx,m);
        int right = query(l,r,2*x+2,m,rx);
        return min(left,right);
    }

    int query(int l,int r){
        return query(l,r,0,0,size);
    }
};