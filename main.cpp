#include <iostream>
#include <regex>
#include <string>
#include <stdlib.h>
#include <curses.h>


#define  MAXLINE 100
#define  MAXARG 20
#define  MAXFILE 1000
#define Debug true

using namespace std;
int argc;
bool right = true;
char *argv[MAXARG] = {};

struct Terminal {
    char user[MAXLINE]; // 用户名
    char mach[MAXLINE]; // 计算机名
    char root[MAXLINE]; // 根目录
    char wdir[MAXLINE]; // 工作目录
    char strin[MAXFILE]; // 重定向标准输入
    char strout[MAXFILE]; // 重定向标准输出
};
Terminal gTerm;


void printHeading(bool right) {
    if (right)cout << "\e[92;1m" << gTerm.mach << "@" << gTerm.user << "\e[0m:" << "\e[94;1m" << gTerm.wdir << "\e[0m$";
    else
        cout << "\e[92;1m" << gTerm.mach << "@" << gTerm.user << "\e[0m:" << "\e[94;1m" << gTerm.wdir
             << "\e[91;1m$\e[0m";
}

void GetAccountInit() {
    cout << "Machine Name:";
    bool flag = false;
    while (!flag) {
        cin >> gTerm.mach;
        flag = regex_match(gTerm.mach, regex("(_|[a-z]|[A-Z])\\w*"));
        if (!flag)cerr << "invalid name, please input again!\n";
    }
    cout << "Root Dir:";
    flag = false;
    while (!flag) {
        cin >> gTerm.root;
        flag = regex_match(gTerm.root, regex("/(\\w*/)*\\w*"));
        if (!flag)cerr << "invalid name, please input again!\n";
    }
    cout << "Login:";
    flag = false;
    while (!flag) {
        cin >> gTerm.user;
        flag = regex_match(gTerm.user, regex("(_|[a-z]|[A-Z])\\w*"));
        if (!flag)cerr << "invalid name, please input again!\n";
    }
    memcpy(gTerm.wdir, gTerm.root, strlen(gTerm.root));
}


void doEcho(int argc, char *argv[]) {
    int posi = 0;
    if (regex_match(argv[1], regex("-n"))) {
        posi = 1;
    }
    for (int i = 1; i < argc; ++i) {
        if (i != posi) {
            cout << argv[i] << " ";
        }
    }
    if (!posi) { cout << endl; }
}

void doDiff(int argc, char *argv[]) {
    cout << "diff!" << endl;
}

void doGrep(int argc, char *argv[]) {
    cout << "grip!" << endl;
}

void doTee(int argc, char *argv[]) {
    cout << "Tee" << endl;
}

void doCat(int argc, char *argv[]) {
    cout << "cat" << endl;
}

void doCp(int argc, char *argv[]) {
    cout << "cp!" << endl;
}

void doCd(int argc, char *argv[]) {
    cout << "cd" << endl;
}


void doPwd(int argc, char *argv[]) {
    cout << "pwd" << endl;
}

void doLs(int argc, char *argv[]) {
    cout << "ls" << endl;
}

void doCls(int argc, char *argv[]){
    system("clear");
}

void doVim(int argc, char *argv[]){
    if (argc == 1){system("vim");}
    if (argc == 2){
        if (regex_match(argv[1],regex("([0-9]|[a-z]|[A-z])+(.)?[a-z]+"))){
            string a = "vim ";
            a.append(argv[1]);
            system(a.c_str());
        } else{
            cerr<<"invalid file name!"<<endl;
        }
    }
}


bool selectInstr() {
    if (regex_match(argv[0], regex("echo"))) {
        doEcho(argc, argv);
    } else if (regex_match(argv[0], regex("cd"))) {
        doCd(argc, argv);
    } else if (regex_match(argv[0], regex("pwd"))) {
        doPwd(argc, argv);
    } else if (regex_match(argv[0], regex("ls"))) {
        doLs(argc, argv);
    } else if (regex_match(argv[0], regex("cat"))) {
        doCat(argc, argv);
    } else if (regex_match(argv[0], regex("tee"))) {
        doTee(argc, argv);
    } else if (regex_match(argv[0], regex("cp"))) {
        doCp(argc, argv);
    } else if (regex_match(argv[0], regex("diff"))) {
        doDiff(argc, argv);
    } else if (regex_match(argv[0], regex("grep"))) {
        doGrep(argc, argv);
    }else if (regex_match(argv[0], regex("clear|cls"))) {
        doCls(argc, argv);
    } else if (regex_match(argv[0], regex("vim"))) {
        doVim(argc, argv);
    }  else {
        if (strlen(argv[0]) > 0)return false;
    }
    return true;
}

void proceseInstr(string tmp) {
    argc = 0;
    regex parttern("\\s+");
    tmp.erase(0, tmp.find_first_not_of(' '));
    sregex_token_iterator pos(tmp.begin(), tmp.end(), parttern, -1);
    decltype(pos) end;
    for (; pos != end; ++pos) {
        memset(argv[argc], 0, sizeof(char) * MAXLINE);
        memcpy(argv[argc], pos->str().c_str(), strlen(pos->str().c_str()));
        argc++;
    }
}

bool splitInstr(string tmp) {
    bool flag = true;
    regex parttern("\\|");
    sregex_token_iterator pos(tmp.begin(), tmp.end(), parttern, -1);
    decltype(pos) end;
    for (; pos != end; ++pos) {
        proceseInstr(pos->str());
        flag = flag && selectInstr();
    }
    return flag;
}

int main() {
//    freopen("/Users/xxy/CLionProjects/basic_programing/homeproject/input.txt", "r", stdin);
//    GetAccountInit();
    getchar();
    string tmp;
    smatch args;
    for (int i = 0; i < MAXARG; ++i) {
        argv[i] = new char[MAXLINE];
    }
    bool right = true;
    while (true) {
        printHeading(right);
        getline(cin, tmp);
        right = splitInstr(tmp);
        if (regex_match(argv[0], regex("exit")))break;
    }

    for (int i = 0; i < MAXARG; ++i) {
        delete argv[i];
    }
    return 0;
}
