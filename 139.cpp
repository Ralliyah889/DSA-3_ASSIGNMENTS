class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {

        int n = s.size();

        // Store dictionary words in a hash set
        unordered_set<string> dict;

        int maxLen = 0;

        for (string word : wordDict) {
            dict.insert(word);
            maxLen = max(maxLen, (int)word.size());
        }

        // dp[i] = can first i characters be segmented?
        vector<bool> dp(n + 1, false);

        // Empty string is always valid
        dp[0] = true;

        // Check every ending position
        for (int i = 1; i <= n; i++) {

            // Check possible previous positions
            for (int j = max(0, i - maxLen); j < i; j++) {

                // Previous part is valid
                if (dp[j]) {

                    // Check whether current substring is a word
                    string word = s.substr(j, i - j);

                    if (dict.count(word)) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }

        return dp[n];
    }
};
