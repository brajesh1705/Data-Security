#include <bits/stdc++.h>

using namespace std;

#define N 50//Max r_len
 
//functiont to encode
int n;
char *encode(char *str)
{     
  int r_len;
  char count[n];
  int length = strlen(str);
  //max size will be 2*length + 1 
  char *result = (char *)malloc(sizeof(char)*(length*2 + 1));
  int i, j = 0, k;
  /* traverse the input str one by one */
  for(i = 0; i < length; i++)
  {
    //First occurence of char
    result[j++] = str[i];
    //Find the number of occurences
    r_len = 1;     
    while(i + 1 < length && str[i] == str[i+1])
    {
      r_len++;
      i++;
    }
    //store it in count array   
    sprintf(count, "%d", r_len);
    for(k = 0; *(count+k); k++, j++)
    { 
      result[j] = count[k];//copy to destination
    } 
  }
  //Null termination  
  result[j] = '\0';
  return result;
}     
//Main function 
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
        cout << "Before encoding: " << file_content.size() << " bytes" << endl;
        
		n = file_content.length();
		char *result = encode(const_cast<char*>(file_content.c_str()));
		string data(result);
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
        cout << "After encoding: " << data.size() << " bytes" << endl;
    }
    catch(string& e)
    {
        cout << e << endl;
    }
	/*
  char string[] = "aaaabbbddddzz";    
  char *result = encode(string);
  cout<<"Output string:";
  cout<<result;
  */
}