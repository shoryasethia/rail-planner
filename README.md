# RAIL PLANNER

* [x] **Trie** and **DFS** based Autocomplete for Station Names
* [ ] Implement **KMP Algorithm** for keyword-based review search
* [x] Use **Heap** to filter and prioritize user reviews by rating or staion/train name
* [ ] Represent station network as a **Graph** (client-server model)
* [ ] Store journeys using **AVL / BST Trees**
* [ ] Sort journeys or reviews using **Quicksort on Linked Lists**

---

# 🚉 Trie-based Autocomplete for Station Names

This is a **Trie-based autocomplete system** implementaion for station names.

## ✅ Functionality

* **Reads station data** from a CSV file (`station_name,station_id,location`).
* Converts all names and locations to lowercase for **case-insensitive matching**.
* **Stores station names** in a Trie data structure.
* **Performs prefix search** to return the **top K matching station names** using DFS.
* Outputs the matched results in lexicographical order (default DFS traversal order).

## 🔧 Key Components

* `struct Station`
  Represents a station with `name`, `id`, and `location`.

* `void getStations(const string& data, vector<Station>& stations)`
  Parses the CSV file and populates the `stations` vector.

* `class Trie`
  * `void insert(string s)` – Inserts a station name into the Trie.
  * `vector<string> search(const string& prefix, int topK)` – Returns top K station names matching the given prefix.

* `struct Node`
  Internal Trie node structure with child pointers and a flag indicating word-end.

* `int main()`
  * Loads station data from csv.
  * Inserts all station names into the Trie.
  * Searches for a given `prefix`.
  * Displays top `K` autocomplete results.

---

# 🌟 Heap-based Filtering for Top-Rated Reviews

This functionality uses **Max-Heaps** (priority queues) to extract the best-rated reviews for stations and trains via there name or a threshold rating.

## ✅ Functionality

* **Reads review data** from a CSV file (`username,target_type,target_name,rating,comment`).
* Converts all target names and types to lowercase for **case-insensitive matching**.
* Separates reviews into **stations** and **trains** using the `target_type` field.
* Uses a **Max-Heap** to extract the top `K` reviews with **rating >= threshold**.
* Also supports fetching reviews for a specific **station or train name**.

## 🔧 Key Components

* `struct Review`
  Represents a review with `username`, `target_type`, `target_name`, `rating`, and `comment`.

* `void getReviews(const string& data, vector<Review>& reviews)`
  Parses the CSV review data and populates the `reviews` vector.

* `priority_queue<pair<float,string>> createMaxHeapStations(vector<Review>& reviews)`
  Builds a max-heap of comments for **station-type** reviews.

* `priority_queue<pair<float,string>> createMaxHeapTrains(vector<Review>& reviews)`
  Builds a max-heap of comments for **train-type** reviews.

* `priority_queue<pair<float,string>> createMaxHeapByTargetName(vector<Review>& reviews, const string& type, const string& name)`
  Builds a max-heap of reviews for a **specific station or train name**.

* `vector<pair<float,string>> getResults(priority_queue<pair<float,string>>& pq, float threshold, int firstK)`
  Extracts top `K` reviews with rating ≥ `threshold` from the given heap.

* `int main()`
  * Loads review data from CSV.
  * Builds relevant heap(s) based on search type or specific target name.
  * Filters and displays top-rated reviews with rating above the threshold.
  * Supports both general type-based and name-specific search modes.

---
