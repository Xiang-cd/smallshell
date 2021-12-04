#include <iostream>
#include <regex>
#include <string>
#include <stdlib.h>


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
    int theme;
};
Terminal gTerm;


void printHeading(bool right) {
    if (gTerm.theme == 2){
        if (right)cout <<"\033[1;35m粉红/洋红\033[0m"<< "\e[92;1m" << gTerm.mach << "@" << gTerm.user << "\e[0m:" << "\e[94;1m" << gTerm.wdir << "\e[0m$";
        else
            cout <<"\033[1;35m粉红/洋红\033[0m"<< "\e[92;1m" << gTerm.mach << "@" << gTerm.user << "\e[0m:" << "\e[94;1m" << gTerm.wdir
                 << "\e[91;1m$\e[0m";
    } else if (gTerm.theme ==1){
        if (right)cout  <<"\033[1;45m粉红/洋红\033[0m"<< "\e[92;1m" << gTerm.mach << "@" << gTerm.user << "\e[0m:" << "\e[94;1m" << gTerm.wdir << "\e[0m$";
        else
            cout <<"\033[1;45m粉红/洋红\033[0m" << "\e[92;1m" << gTerm.mach << "@" << gTerm.user << "\e[0m:" << "\e[94;1m" << gTerm.wdir
                 << "\e[91;1m$\e[0m";
    } else{
        if (right)cout <<"\033[4#m  dioghd \033[0m"<< "\e[92;1m" << gTerm.mach << "@" << gTerm.user << "\e[0m:" << "\e[94;1m" << gTerm.wdir << "\e[0m$";
        else
            cout <<"\033[4#m  dioghd \033[0m" << "\e[92;1m" << gTerm.mach << "@" << gTerm.user << "\e[0m:" << "\e[94;1m" << gTerm.wdir
                 << "\e[91;1m$\e[0m";
    }
}

inline string BasicInit(const string input, regex ex) {
    cout << input;
    bool flag = false;
    string temp = "";
    while (!flag) {
        getline(cin, temp);
        if (strlen(temp.c_str()) > MAXLINE) {
            cerr << "too long input name, please input again!\n" << input;
            continue;
        }
        flag = regex_match(temp, ex);
        if (!flag)cerr << "invalid name, please input again!\n" << input;
        else { return temp; }
    }
    return temp;
}

inline void TestArg(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        cerr << "arg" << i << ":" << argv[i] << endl;
    }
    cerr << "stdin:" << gTerm.strin << endl;
    cerr << "stdout:" << gTerm.strout << endl;
}

void GetAccountInit() {
    string tmp = BasicInit("Machine Name:", regex("(_|[a-z]|[A-Z])\\w*"));
    memcpy(gTerm.mach, tmp.c_str(), strlen(tmp.c_str()));
    tmp = BasicInit("Root Dir:", regex("/((\\w|-|.)*/)*(\\w|-|.)*/?"));
    memcpy(gTerm.root, tmp.c_str(), strlen(tmp.c_str()));
    tmp = BasicInit("Login:", regex("(_|[a-z]|[A-Z])\\w*"));
    memcpy(gTerm.user, tmp.c_str(), strlen(tmp.c_str()));
    memcpy(gTerm.wdir, gTerm.root, strlen(gTerm.root));
    gTerm.theme = 0;
}


void doEcho(int argc, char *argv[]) {
    int posi = 0;
    if (regex_match(argv[1], regex("-n"))) posi = 1;
    if (regex_match(argv[1], regex("--help"))) {
        memset(gTerm.strout, 0, MAXFILE);
        string a = "Echo the STRING(s) to standard output.\n-n     do not output the trailing newline\n-e     enable interpretation of backslash escapes\n-E     disable interpretation of backslash escapes (default)\n--help display this help and exit\n--version\noutput version information and exit\n";
        memcpy(gTerm.strout, a.c_str(), strlen(a.c_str()));
        return;
    }
    if (regex_match(argv[1], regex("--version"))) {
        memset(gTerm.strout, 0, MAXFILE);
        string a = "homework for basic programming,version 0.1\n";
        memcpy(gTerm.strout, a.c_str(), strlen(a.c_str()));
        return;
    }
    string temp = "";
    for (int i = posi ? 2 : 1; i < argc; ++i) {
        temp.append(argv[i]);
        if (i != argc - 1) temp.append(" ");
    }
    if (!posi) { temp.append("\n"); }
    memset(gTerm.strout, 0, MAXFILE);
    memcpy(gTerm.strout, temp.c_str(), strlen(temp.c_str()));
}

void doDiff(int argc, char *argv[]) {
    TestArg(argc, argv);
}

void doGrep(int argc, char *argv[]) {
    TestArg(argc, argv);
}

void doTee(int argc, char *argv[]) {
    TestArg(argc, argv);
}

void doCat(int argc, char *argv[]) {
    TestArg(argc, argv);
}

void doCp(int argc, char *argv[]) {
    TestArg(argc, argv);
}

void doCd(int argc, char *argv[]) {
    TestArg(argc, argv);
}

void doPwd(int argc, char *argv[]) {
    TestArg(argc, argv);
    string tmp = "pwd output";
    memcpy(gTerm.strout, tmp.c_str(), strlen(tmp.c_str()));
    cerr << "after pwd strout:" << gTerm.strout << endl;
}

void doLs(int argc, char *argv[]) {
    TestArg(argc, argv);
}

void doCls(int argc, char *argv[]) {
    system("clear");
}

void doChange(int argc, char *argv[]) {
    if (argc <= 1){
        cerr<<"select a theme please~"<<endl;
    } else{
        if (strlen(argv[1])>1){
            cerr<<"select theme from number 0 to 2"<<endl;
        } else if (argv[1][0]>'2' or argv[1][0]<'0'){
            cerr<<"select theme from number 0 to 2"<<endl;
        } else{
            gTerm.theme = argv[1][0]-'0';
        }
    }
}


void doVim(int argc, char *argv[]) {
    if (argc == 1) { system("vim"); }
    if (argc == 2) {
        if (regex_match(argv[1], regex("([0-9]|[a-z]|[A-Z]|-|_)+(.[a-z]+)?"))) {
            string a = "vim ";
            a.append(argv[1]);
            system(a.c_str());
        } else {
            cerr << "invalid file name!" << endl;
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
    } else if (regex_match(argv[0], regex("clear|cls"))) {
        doCls(argc, argv);
    } else if (regex_match(argv[0], regex("vim"))) {
        doVim(argc, argv);
    } else if (regex_match(argv[0], regex("change"))) {
        doChange(argc, argv);
    } else if(regex_match(argv[0],regex("exit"))){
        return true;
    }else {
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
        memcpy(gTerm.strin, gTerm.strout, MAXFILE);
        memset(gTerm.strout,0,MAXFILE);
        bool tmpf = selectInstr();
        flag = flag and tmpf; //如果遇到指令选择错误，则跳出指令的执行
        if (not tmpf)cerr << "command \"" << argv[0] << "\" not found!" << endl;
//        if (not flag) return flag;
    }
    return flag;
}

int main() {
//    freopen("/Users/xxy/CLionProjects/basic_programing/homeproject/input.txt", "r", stdin);
    GetAccountInit();
//    getchar();
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
        else cout << gTerm.strout;
        memset(gTerm.strout, 0, MAXFILE); //每次输出后,都将输出流清空
    }

    for (int i = 0; i < MAXARG; ++i) {
        delete argv[i];
    }
    return 0;
}
