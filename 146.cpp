class LRUCache {
private:
    int capacity;

    // Stores keys and values in usage order
    list<pair<int, int>> cache;

    // Maps each key to its position in the list
    unordered_map<int, list<pair<int, int>>::iterator> mp;

    // Move an existing key to the front
    void makeRecentlyUsed(int key) {
        auto it = mp[key];

        cache.splice(cache.begin(), cache, it);
    }

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {

        // Key does not exist
        if (mp.find(key) == mp.end()) {
            return -1;
        }

        // Mark as recently used
        makeRecentlyUsed(key);

        return mp[key]->second;
    }

    void put(int key, int value) {

        // Key already exists
        if (mp.find(key) != mp.end()) {

            auto it = mp[key];

            // Update its value
            it->second = value;

            // Move it to the front
            makeRecentlyUsed(key);

            return;
        }

        // Cache is full
        if (cache.size() == capacity) {

            // Remove least recently used key
            int lruKey = cache.back().first;

            cache.pop_back();
            mp.erase(lruKey);
        }

        // Insert new key at the front
        cache.push_front({key, value});

        // Store its iterator in the map
        mp[key] = cache.begin();
    }
};