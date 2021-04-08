struct segtree{
    int size;
    vector<pair<int,int>> tree_array;
    void init(int n){
        size=1;
        while(size<n)
        size*=2;
        tree_array.assign(2*size,{INT_MAX,1});
    }

    void set(int i,int v,int x,int lx,int rx){
        if(rx-lx==1){
            tree_array[x].F = v;
            tree_array[x].S = 1;
            return;
        }
        int m = lx + (rx-lx)/2;
        if(i<m){
            set(i,v,2*x+1,lx,m);
        }else{
            set(i,v,2*x+2,m,rx);
        }
        tree_array[x].F = min(tree_array[2*x+1].F,tree_array[2*x+2].F);
        if(tree_array[2*x+1].F==tree_array[2*x+2].F){
            tree_array[x].S = tree_array[2*x+1].S + tree_array[2*x+2].S;
        }else{
            if(tree_array[2*x+1].F<tree_array[2*x+2].F){
                tree_array[x].S = tree_array[2*x+1].S;
            }else{
                tree_array[x].S = tree_array[2*x+2].S;
            }
        }
    }

    void set(int i,int v){
        set(i,v,0,0,size);
    }

    pair<int,int> query(int l,int r,int x,int lx,int rx){
        if(lx>=r||rx<=l)return {INT_MAX,1};
        if(lx>=l&&rx<=r)return tree_array[x];
        int m = lx + (rx-lx)/2;
        pair<int,int> left = query(l,r,2*x+1,lx,m);
        pair<int,int> right = query(l,r,2*x+2,m,rx);
        if(left.F<right.F){
            return left;
        }else if(right.F<left.F){
            return right;
        }else{
            return {left.F,left.S+right.S};
        }
    }

    pair<int,int> query(int l,int r){
        return query(l,r,0,0,size);
    }
};