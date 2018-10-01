#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int interface ();//forward declaration aka prototyping
void clearingAFile();//forward declaration aka prototyping
void addToFile(string url);//forward declaration aka prototyping
void printFile(string url);//forward declaration aka prototyping

/* these are just the functions i created as drafts to help me understand how to approach the problem
void singleLineEntry (){
    ofstream file ("example.txt"); // this is how you create a new file
    cout << "add something to the file" << endl;
    string text;
    getline(cin, text); // getline is used to capture sentances.
    cin.ignore(); // only reqired if cin and getline() are used sequentially
    file << text << endl;
    file.close();
    interface();
}
void multiLineEntry (){
    ofstream file;
    string content, address;
    
    cout << "Enter address of file:" << endl;
    cin >> address;
    cin.ignore();
    file.open (address.c_str(), fstream::out | fstream::app);
    
    if(file.is_open()){
        cout << "Write something press space to end input" << endl;
        while(content != " "){
            getline(cin, content);
            file << content << endl;
        }
        file.close();
    }else{
        cout << "File does not exist" << endl;
    }
    interface();
}
*/

void clearingAFile (){
    ofstream file;
    string address;
    
    cout << "Enter address of file:" << endl;
    cin >> address;
    cin.ignore();//used because cin >> address was used after getline() was called in interface()
    
    file.open (address.c_str(), fstream::trunc | fstream::out);//fstream::trunc used to clear all contents in file.
    if(file.is_open()){
        file << "";
        file.close();        
    }else{ cout << "The addess you entered does not exist" << endl; }
    interface();
}
void addToFile (string url = ""){ 
    ofstream file;
    string address = url;
    string content;
    
    if(url == ""){//if url passed to function is blank ask user to input address
        cout << "Enter address of file:" << endl;
        cin >> address;
        cin.ignore();    
        file.open(address.c_str(), fstream::out | fstream::app);//fstream::app used to 'append' strings to the end of a file
    }else{ file.open(url.c_str(), fstream::out | fstream::app); }//c_str() is used to convert user input to be acceptable to open() function
    
    if(file.is_open()){
        cout << "Add content press space to end input" << endl;
        while(content != " "){//this is the only way i could come up with in the form of an escape sequence 
            getline(cin, content);//gets the whole line as opposed tp cin which only gets the first word in the line
            file << content << endl;
        }
        file.close();
    }else{ 
        cout << "The address you entered does not exist" << endl; 
        interface();
    }
    cout << "Would you like to view the file? y or n" << endl;
    string a;
    cin >> a;
    if(a == "y"){ printFile(address); }//calls printFile() function and passes address to it. Thought it would be easier for the user
    else if(a == "n"){ interface(); }
}
void printFile (string url = ""){
    ifstream file;
    string line;
    string address = url;
    int numberOfLines = 0;
    
    if(url == ""){
        cout << "Enter address" << endl;
        cin >> address;
        cin.ignore();
        file.open (address.c_str());
    }else{ file.open (url.c_str()); }
    
    if(file.is_open()){
        cout << endl;
        while ( getline (file,line) ){//loops through every line in the file and prints them out separted by an endl
            cout << line << endl;
            numberOfLines++;//counts number of lines there are in the file
        }
        cout << endl << "This file has " << numberOfLines << " lines" << endl;
        file.close();
    }else{ 
        cout << "Unable to open file - file does not exist" << endl; 
        interface();
    }
    
    cout << "Would you like to add to this file? y or n" << endl;
    string a;
    cin >> a;
    cin.ignore();
    if(a == "y"){ addToFile(address);}//calls addToFile() function and passes address to it
    else if(a == "n"){ interface();}
}
int interface (){//acts something like the home screen allowing the user to change functions
    int a;
    cout << "Welcome to Alex's Text Editor (ATE)" << endl
        << "What would you like to do? " << endl
        << "1. Clear file contents" << endl
        << "2. Add to a file" << endl
        << "3. Print file contents" << endl
        << "4. Close ATE" << endl;
    cin >> a;
    cin.ignore();
    switch (a){
        case 1:
            clearingAFile();
            break;
        case 2:
            addToFile("");
            break;
        case 3:
            printFile("");
            break;
        case 4:
            return 0;
            break;
        default:
            cout << "Please enter a valid input." << endl;
            interface();
            break;
    }
    return 0;
}
int main (){
    interface();
    return 0;
}

// int rc = std::rename("from.txt", "to.txt"); 
// if(rc) { 
//     std::perror("Error renaming"); return 1; 
// }