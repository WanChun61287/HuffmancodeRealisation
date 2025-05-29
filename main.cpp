
#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <iomanip>
using namespace std;

struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode *left, *right;
    
    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;
    
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }
    
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

void printHuffmanCodes(const unordered_map<char, string>& huffmanCodes) {
    cout << "Huffman Codes Table:\n";
    cout << "-------------------\n";
    cout << left << setw(10) << "Char" << setw(15) << "Code" << "Frequency\n";
    cout << "-------------------\n";
    
    vector<pair<char, string>> sortedCodes(huffmanCodes.begin(), huffmanCodes.end());
    (sortedCodes.begin(), sortedCodes.end(), 
        [](const auto& a, const auto& b) {
            return a.second.length() < b.second.length();
        });
    
    for (const auto& pair : sortedCodes) {
        if (pair.first == ' ') {
            cout << setw(10) << "'space'";
        } else if (pair.first == '\n') {
            cout << setw(10) << "'newline'";
        } else {
            cout << setw(10) << pair.first;
        }
        cout << setw(15) << pair.second << "\n";
    }
    cout << "-------------------\n\n";
}

string compress(const string& text, unordered_map<char, string>& huffmanCodes) {
    string compressed;
    for (char c : text) {
        compressed += huffmanCodes[c];
    }
    return compressed;
}

int main() {
    string darcyQuote = "In vain have I struggled. It will not do. My feelings will not be repressed. You must allow me to tell you how ardently I admire and love you.";
    
 
    unordered_map<char, int> freq;
    for (char c : darcyQuote) freq[c]++;
    
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto& pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        auto newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    
   
    unordered_map<char, string> huffmanCodes;
    generateCodes(pq.top(), "", huffmanCodes);
    
    
    printHuffmanCodes(huffmanCodes);
    
  
    string compressed = compress(darcyQuote, huffmanCodes);
    
    cout << "Original text:\n" << darcyQuote << "\n\n";
    cout << "Compressed binary:\n" << compressed << "\n\n";
    cout << "Original size: " << darcyQuote.size() * 8 << " bits\n";
    cout << "Compressed size: " << compressed.size() << " bits\n";
    cout << "Compression ratio: " << fixed << setprecision(2) 
         << (float)(darcyQuote.size() * 8) / compressed.size() << ":1\n";
    
    return 0;
}
