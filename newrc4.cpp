#include <bits/stdc++.h>

using namespace std;


typedef vector<unsigned char> ustring;

void rc4(ustring ByteInput, ustring pwd,
		   ustring &ByteOutput){
	ustring temp;
	int i,j=0,t,tmp,tmp2,s[256], k[256];
	for (tmp=0;tmp<256;tmp++){
		s[tmp]=tmp;
		k[tmp]=pwd[(tmp % pwd.size())];
	}
		for (i=0;i<256;i++){
		j = (j + s[i] + k[i]) % 256;
		tmp=s[i];
		s[i]=s[j];
		s[j]=tmp;
	}
//temp = new unsigned char [ (int)strlen((char *)ByteInput)  + 1 ] ;
temp = ustring(ByteInput.size()+1,'a');
	i=j=0;
	for (tmp=0;tmp<ByteInput.size();tmp++){
	    i = (i + 1) % 256;
        j = (j + s[i]) % 256;
		tmp2=s[i];
		s[i]=s[j];
		s[j]=tmp2;
        t = (s[i] + s[j]) % 256;
if (s[t]==ByteInput[tmp])
	temp[tmp]=ByteInput[tmp];
else
	temp[tmp]=s[t]^ByteInput[tmp];
	}
temp[tmp]='\0';
ByteOutput=temp;
}

int main(){
    ustring message;
	ustring pwd;
	ustring encrypted;
	ustring decrypted;
	//message=ustring("Hello world!");
	//pwd=ustring("abc");
	 try
    {
        ifstream file("input.txt");
        if (!file.is_open()) throw "Exception: Unable to open file.";

        stringstream stream;
        stream << file.rdbuf();
        file.close();

        string file_content = stream.str();
        cout<<"Input: "<<file_content<<endl;
        cout << "Before encryption: " << file_content.size() << " bytes" << endl;
		
    	unsigned char *message1=new unsigned char [ file_content.size()  + 1 ];
		
    	for(int i=0; i<file_content.size(); i++)
    	    message1[i] = (unsigned char)file_content[i];
    	message1[file_content.size()] = '\0';
		
    	unsigned char *pwd1=(unsigned char *)"abc";
		
    	for(int i=0; i<(int)strlen((char *)message1); i++)
    	    message.push_back(message1[i]);
		
		
    	for(int i=0; i<(int)strlen((char *)pwd1); i++)
    	    pwd.push_back(pwd1[i]);
    	    
    	rc4(message,pwd,encrypted);
		
    	rc4(encrypted,pwd,decrypted);
		
    	//cout<<"Test"<<endl<<endl;
		/*
    	cout<<"Message: ";
    	for(int i=0; i<message.size(); i++)
    	    cout<<message[i];
    	cout << endl;
		*/
    	cout<<"Password: ";
    	for(int i=0; i<pwd.size(); i++)
    	    cout<<pwd[i];
    	cout << endl;
    	cout<<"Message encrypted: ";
    	for(int i=0; i<encrypted.size(); i++)
    	    cout<<encrypted[i];
    	cout << endl;
    	cout<<"Message decrypted: ";
    	for(int i=0; i<decrypted.size(); i++)
    	    cout<<decrypted[i];
    	cout << endl;
		
        ofstream output("output.txt", ios::binary);
        if (!output.is_open())
            throw "Exception: Unable to open file.";
        copy(
            encrypted.begin(),
            encrypted.end(),
            ostream_iterator<unsigned char>(output));
        output.close();
        cout<<"Output: ";
        for(int i=0;i<encrypted.size();i++)
        {
            cout<<encrypted[i];
        }
        cout<<endl;
        cout << "After encryption: " << encrypted.size() << " bytes" << endl;
    }
    catch(string& e)
    {
        cout << e << endl;
    }
}