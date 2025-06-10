#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Station {
    string station_name;
    int station_id;
    string location;
};

void getStations(const string& data, vector<Station>& stations){
    ifstream file(data);
    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, id_str, location;

        getline(ss, name, ',');
        getline(ss, id_str, ',');
        getline(ss, location, ',');

        // ensure id_str is numeric
        if (id_str.empty() || !isdigit(id_str[0])) continue;

        Station s;
        
        transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return tolower(c); });
        transform(location.begin(), location.end(), location.begin(), [](unsigned char c){ return tolower(c); });
        
        s.station_name = name;
        s.station_id = stoi(id_str);
        s.location = location;

        stations.push_back(s);
    }
}

struct Node{
    Node* link[26] = {NULL};
    string prev = "";
    bool flag = false;

    bool containsKey(char ch){
        return link[ch-'a']!=NULL;
    }

    void addNode(char ch, Node* node){
        link[ch-'a'] = node;
        return;
    }
    
    Node* getNode(char ch){
        return link[ch-'a'];
    }
};

class Trie{
private:
    Node* root;
public:
    Trie(){
        root = new Node();
    }

    void insert(string s){
        Node* node = root;
        for(int i=0;i<s.size();i++){
            if(!node->containsKey(s[i])){
                node->addNode(s[i],new Node());
            }
            Node* next = node->getNode(s[i]);
            next->prev = node->prev + s[i];
            node = next;
        }
        node->flag = true;
    }

    void dfs(Node* node, vector<string>& result, int topK){
        if(result.size()==topK) return;
        if(node && node->flag) result.push_back(node->prev);
        for(char i='a';i<='z';i++){
            if(node->containsKey(i)){
                dfs(node->getNode(i),result,topK);
            }
        }

        return;
    }

    vector<string> search(const string& prefix, int topK){
        vector<string> result;
        Node* node = root;
        for(int i=0;i<prefix.size();i++){
            if(node->containsKey(prefix[i])){
                node = node->getNode(prefix[i]);
            }
            else{
                return result;
            }
        }
        dfs(node,result,topK);

        return result;
    }
};

int main() {
    string data = "../data/stations.csv";
    vector<Station> stations;
    getStations(data,stations);

    Trie trie;

    for(int i=0;i<stations.size();i++){
        trie.insert(stations[i].station_name);
    }

    string toSearch = "MU";
    transform(toSearch.begin(), toSearch.end(), toSearch.begin(), [](unsigned char c){ return tolower(c); });


    int topK = 3;
    vector<string> topKresults = trie.search(toSearch,topK);

    cout<<"Top "<<min(topK,(int)topKresults.size())<<" result matching with "<<toSearch<< " are:"<<endl;
    for(int i=0;i<topKresults.size();i++){
        cout<<topKresults[i]<<endl;
    }

    // Top 2 result matching with mu are:
    // mumbaicsmt
    // muzaffarpurjn

    return 0;
}