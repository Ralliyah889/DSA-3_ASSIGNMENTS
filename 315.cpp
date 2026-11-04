class Solution {
private:
    vector<int> indices;
    vector<int> counts;
    vector<int> temp;
    vector<int>* arr;

    void mergeSort(int left, int right) {
        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        merge(left, mid, right);
    }

    void merge(int left, int mid, int right) {
        int i = left;
        int j = mid + 1;
        int k = left;

        int smallerCount = 0;

        while (i <= mid && j <= right) {

            // Right element is smaller
            if ((*arr)[indices[j]] < (*arr)[indices[i]]) {
                temp[k++] = indices[j++];
                smallerCount++;
            }

            // Left element is smaller or equal
            else {
                counts[indices[i]] += smallerCount;
                temp[k++] = indices[i++];
            }
        }

        // Remaining left elements
        while (i <= mid) {
            counts[indices[i]] += smallerCount;
            temp[k++] = indices[i++];
        }

        // Remaining right elements
        while (j <= right) {
            temp[k++] = indices[j++];
        }

        // Copy merged indices back
        for (int p = left; p <= right; p++) {
            indices[p] = temp[p];
        }
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();

        indices.resize(n);
        counts.assign(n, 0);
        temp.resize(n);

        arr = &nums;

        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }

        mergeSort(0, n - 1);

        return counts;
    }
};
