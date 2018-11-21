// C++ program for Huffman Coding 
#include <bits/stdc++.h> 
using namespace std; 
map<char,string> m;
// A Huffman tree node 
struct MinHeapNode { 
  
    // One of the input characters 
    char data; 
  
    // Frequency of the character 
    unsigned freq; 
  
    // Left and right child 
    MinHeapNode *left, *right; 
  
    MinHeapNode(char data, unsigned freq) 
  
    { 
  
        left = right = NULL; 
        this->data = data; 
        this->freq = freq; 
    } 
}; 
  
// For comparison of 
// two heap nodes (needed in min heap) 
struct compare { 
  
    bool operator()(MinHeapNode* l, MinHeapNode* r) 
  
    { 
        return (l->freq > r->freq); 
    } 
}; 
  
// Prints huffman codes from 
// the root of Huffman Tree. 
void printCodes(struct MinHeapNode* root, string str) 
{ 
  
    if (!root) 
        return; 
  
    if (root->data != '$') 
        m[root->data]=str; 
  
    printCodes(root->left, str + "0"); 
    printCodes(root->right, str + "1"); 
} 
  
// The main function that builds a Huffman Tree and 
// print codes by traversing the built Huffman Tree 
void HuffmanCodes(vector<char> data, vector<int> freq, int size) 
{ 
    struct MinHeapNode *left, *right, *top; 
  
    // Create a min heap & inserts all characters of data[] 
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap; 
  
    for (int i = 0; i < size; ++i) 
        minHeap.push(new MinHeapNode(data[i], freq[i])); 
  
    // Iterate while size of heap doesn't become 1 
    while (minHeap.size() != 1) { 
  
        // Extract the two minimum 
        // freq items from min heap 
        left = minHeap.top(); 
        minHeap.pop(); 
  
        right = minHeap.top(); 
        minHeap.pop(); 
  
        // Create a new internal node with 
        // frequency equal to the sum of the 
        // two nodes frequencies. Make the 
        // two extracted node as left and right children 
        // of this new node. Add this node 
        // to the min heap '$' is a special value 
        // for internal nodes, not used 
        top = new MinHeapNode('$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        minHeap.push(top); 
    } 
  
    // Print Huffman codes using 
    // the Huffman tree built above 
    printCodes(minHeap.top(), ""); 
} 
  
// Driver program to test above functions 
int main() 
{
    vector<int> freq;
    vector<char> arr;
    try
    {
        ifstream file("input.txt");
        if (!file.is_open()) throw "Exception: Unable to open file.";

        stringstream stream;
        stream << file.rdbuf();
        file.close();

        string file_content = stream.str();
        cout<<"Input: "<<file_content<<endl;
        cout << "Before compression: " << file_content.size() << " bytes" << endl;
        int dp[256];
        for(int i=0;i<256;i++)
        {
            dp[i]=0;
        }
        for(int i=0;i<file_content.size();i++)
        {
            dp[file_content[i]]++;
        }
        for(int i=0;i<256;i++)
        {
            if(dp[i]!=0)
            {
                arr.push_back((char)i);
                freq.push_back(dp[i]);
            }
        }
        int size = sizeof(arr) / sizeof(arr[0]); 
  
        HuffmanCodes(arr, freq, size);
        string ans;
        for(int i=0;i<file_content.size();i++)
        {
            ans+=m[file_content[i]];
        }
        const short byte_size = 8;
        const char * const buffer_ptr = ans.c_str();
            vector<unsigned char> data;
        for (int pos = 0; pos / 8 < ans.size() / byte_size; pos += 8)
        {
            unsigned byte = 0x00;
            for (int b = 0; b < byte_size; ++b)
            {
                byte <<= 1;
                if (*(buffer_ptr + b + pos) == '1') byte |= 0x01;
            }
            data.push_back(byte);
        }

        ofstream output("output.txt", ios::binary);
        if (!output.is_open())
            throw "Exception: Unable to open file.";
        copy(
            data.begin(),
            data.end(),
            ostream_iterator<unsigned char>(output));
        output.close();
        cout<<"Output: ";
        for(int i=0;i<data.size();i++)
        {
            cout<<data[i];
        }
        cout<<endl;
        cout << "After compression: " << data.size() << " bytes" << endl;
    }
    catch(string& e)
    {
        cout << e << endl;
    }
    return 0;
} 