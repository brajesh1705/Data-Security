#include <bits/stdc++.h>
using namespace std;
vector<int> compressed;
void compress(string &uncompressed) 
{
  int dictSize = 256;
  map<string,int> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[string(1, i)] = i;
  string w;
  for (string::const_iterator it = uncompressed.begin();it != uncompressed.end(); ++it)
  {
    char c = *it;
    string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else 
    {
      compressed.push_back(dictionary[w]);
      dictionary[wc] = dictSize++;
      w = string(1, c);
    }
  }
 
  // Output the code for w.
  if (!w.empty())
    compressed.push_back(dictionary[w]);
}
#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
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
    compress(file_content);
    string ans;
    for(int i=0;i<compressed.size();i++)
      ans+=compressed[i];
    ofstream output("output.txt", ios::binary);
    if (!output.is_open())
        throw "Exception: Unable to open file.";
    output.close();
    cout<<"Output: "<<ans<<endl;
    cout << "After compression: " << ans.size() << " bytes" << endl;


  }
  catch(string& e)
  {
      cout<<e<<endl;
  }
  return 0;
}