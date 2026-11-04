class Solution {
public:
    int minDistance(string word1, string word2) {

        int m = word1.size();
        int n = word2.size();

        // Create DP table
        vector<vector<int>> dp(
            m + 1, vector<int>(n + 1, 0)
        );

        // Base case: delete all characters
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }

        // Base case: insert all characters
        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        // Fill the DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {

                // Characters match
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }

                // Characters do not match
                else {
                    int insertOp = dp[i][j - 1];
                    int deleteOp = dp[i - 1][j];
                    int replaceOp = dp[i - 1][j - 1];

                    dp[i][j] = 1 + min({
                        insertOp,
                        deleteOp,
                        replaceOp
                    });
                }
            }
        }

        return dp[m][n];
    }
};
