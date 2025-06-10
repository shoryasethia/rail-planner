#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Review {
    string username;
    string target_type;
    string target_name;
    float rating;
    string comment;
};

void getReviews(const string& data, vector<Review>& reviews) {
    ifstream file(data);
    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string username, target_type, target_name, rating_str, comment;

        getline(ss, username, ',');
        getline(ss, target_type, ',');
        getline(ss, target_name, ',');
        getline(ss, rating_str, ',');
        getline(ss, comment); 

        transform(username.begin(), username.end(), username.begin(), ::tolower);
        transform(target_type.begin(), target_type.end(), target_type.begin(), ::tolower);
        transform(target_name.begin(), target_name.end(), target_name.begin(), ::tolower);

        if (rating_str.empty()) continue;

        try {
            float rating = stof(rating_str);

            Review r;
            r.username = username;
            r.target_type = target_type;
            r.target_name = target_name;
            r.rating = rating;
            r.comment = comment;

            reviews.push_back(r);
        } catch (...) {
            continue;
        }
    }
}

priority_queue<pair<float,string>> createMaxHeapByTargetName(vector<Review>& reviews, const string& type, const string& name) {
    priority_queue<pair<float,string>> pq;
    bool found = false;

    for(auto& r : reviews){
        if(r.target_type == type && r.target_name == name){
            pq.push({r.rating, r.comment});
            found = true;
        }
    }

    if(!found){
        cout<<"INVALID "<<type<<" NAME!"<<endl;
    }

    return pq;
}

vector<pair<float,string>> getResults(priority_queue<pair<float,string>>& pq, float threshold, int firstK){
    vector<pair<float,string>> result;

    while(!pq.empty() && firstK--){
        auto review = pq.top();
        pq.pop();
        if(review.first >= threshold)
            result.push_back({review.first, review.second});
    }

    return result;
}

int main() {
    vector<Review> reviews;
    string path = "../data/reviews.csv";
    getReviews(path, reviews);

    string searchType = "station"; // 'station' or 'train'
    string searchName = "MUMBAICSMT";
    float threshold = 3.8; // 0 to 5
    int firstK = 3;

    transform(searchName.begin(),searchName.end(),searchName.begin(),::tolower);

    auto heap = createMaxHeapByTargetName(reviews,searchType,searchName);
    vector<pair<float,string>> result = getResults(heap,threshold,firstK);

    for(int i=0;i<result.size();i++){
        cout<<"Rating: "<<result[i].first<<endl;
        cout<<"Comment: "<<result[i].second<<endl;
        cout<<"-----------------------------------"<<endl;
    }

    return 0;
}