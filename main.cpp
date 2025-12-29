#include <bits/stdc++.h>
using namespace std;

string REPO_PATH = "repo/";
string INDEX_FILE = "repo/index.txt";
string LOG_FILE = "repo/log.txt";

string getTimeStamp() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string s(dt);
    s.pop_back();
    return s;
}

// ---------------- HASH FUNCTION ----------------
string generateHash(string filename) {
    ifstream file(filename);
    if(!file) return "NULL";

    string content, line;
    while(getline(file, line))
        content += line;

    unsigned long hash = 5381;
    for(char c : content)
        hash = ((hash << 5) + hash) + c;

    return to_string(hash);
}

// ---------------- VERSION NODE ----------------
struct Commit {
    int id;
    string message;
    string timestamp;
    unordered_map<string,string> files; 
    Commit* prev;

    Commit(int id,string msg,Commit* p){
        this->id=id;
        message=msg;
        timestamp=getTimeStamp();
        prev=p;
    }
};

Commit* HEAD = NULL;
int commitCount = 0;

// ---------------- INITIALIZE ----------------
void initRepo(){
    system("mkdir repo");
    system("mkdir repo/commits");

    ofstream f(INDEX_FILE);
    f.close();
    
    ofstream l(LOG_FILE);
    l.close();
    
    cout << "Repository initialized successfully!\n";
}

// ---------------- ADD FILE ----------------
void addFile(string filename){
    ifstream file(filename);
    if(!file){
        cout<<"File not found!\n";
        return;
    }

    string hash = generateHash(filename);

    ofstream idx(INDEX_FILE, ios::app);
    idx << filename << " " << hash << endl;

    cout<<"File added successfully.\n";
}

// ---------------- COMMIT ----------------
void commit(string msg){
    commitCount++;
    Commit* newCommit = new Commit(commitCount,msg,HEAD);

    ifstream idx(INDEX_FILE);
    string file, hash;

    while(idx >> file >> hash){
        newCommit->files[file] = hash;

        string dest = REPO_PATH + string("commits/") + 
                      "commit_" + to_string(commitCount) + "_" + file;

        ifstream src(file,ios::binary);
        ofstream copy(dest,ios::binary);
        copy << src.rdbuf();
    }

    ofstream log(LOG_FILE,ios::app);
    log << "Commit #" << commitCount << " : " << msg 
        << " @ " << newCommit->timestamp << endl;

    HEAD = newCommit;

    cout<<"Commit created successfully!\n";
}

// ---------------- LOG HISTORY ----------------
void showLog(){
    Commit* temp = HEAD;
    if(!temp){
        cout<<"No commits yet!\n";
        return;
    }

    while(temp){
        cout<<"Commit #"<<temp->id<<" - "<<temp->message
            <<" ("<<temp->timestamp<<")"<<endl;
        temp=temp->prev;
    }
}

// ---------------- ROLLBACK ----------------
void rollback(int version){
    Commit* temp = HEAD;

    while(temp && temp->id != version)
        temp = temp->prev;

    if(!temp){
        cout<<"Version not found!\n";
        return;
    }

    for(auto it : temp->files){
        string src = REPO_PATH + "commits/commit_" +
                     to_string(temp->id) + "_" + it.first;

        ifstream s(src,ios::binary);
        ofstream d(it.first,ios::binary);
        d << s.rdbuf();
    }

    HEAD = temp;
    cout<<"Rolled back to commit "<<version<<" successfully!\n";
}

// ---------------- MAIN ----------------
int main(){
    cout<<"Mini Git - Version Control System\n";

    while(true){
        cout<<"\n1. init\n2. add\n3. commit\n4. log\n5. rollback\n6. exit\n";
        cout<<"Choose: ";

        int ch;
        cin>>ch;

        if(ch==1) initRepo();
        else if(ch==2){
            string f;
            cout<<"Enter filename: ";
            cin>>f;
            addFile(f);
        }
        else if(ch==3){
            string msg;
            cout<<"Enter commit message: ";
            cin.ignore();
            getline(cin,msg);
            commit(msg);
        }
        else if(ch==4) showLog();
        else if(ch==5){
            int v;
            cout<<"Enter version: ";
            cin>>v;
            rollback(v);
        }
        else break;
    }
}
