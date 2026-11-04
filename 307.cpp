class NumArray {
private:
    vector<int> tree;
    int n;

    // Build the segment tree
    void build(vector<int>& nums, int node,
               int start, int end) {

        if (start == end) {
            tree[node] = nums[start];
            return;
        }

        int mid = start + (end - start) / 2;

        build(nums, 2 * node, start, mid);
        build(nums, 2 * node + 1, mid + 1, end);

        tree[node] = tree[2 * node] +
                     tree[2 * node + 1];
    }

    // Update an element
    void updateTree(int node, int start, int end,
                    int index, int val) {

        if (start == end) {
            tree[node] = val;
            return;
        }

        int mid = start + (end - start) / 2;

        if (index <= mid) {
            updateTree(2 * node, start, mid,
                       index, val);
        } else {
            updateTree(2 * node + 1, mid + 1, end,
                       index, val);
        }

        tree[node] = tree[2 * node] +
                     tree[2 * node + 1];
    }

    // Calculate range sum
    int query(int node, int start, int end,
              int left, int right) {

        // No overlap
        if (right < start || end < left) {
            return 0;
        }

        // Complete overlap
        if (left <= start && end <= right) {
            return tree[node];
        }

        // Partial overlap
        int mid = start + (end - start) / 2;

        int leftSum = query(2 * node, start, mid,
                            left, right);

        int rightSum = query(2 * node + 1,
                             mid + 1, end,
                             left, right);

        return leftSum + rightSum;
    }

public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
    }

    void update(int index, int val) {
        updateTree(1, 0, n - 1, index, val);
    }

    int sumRange(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }
};
