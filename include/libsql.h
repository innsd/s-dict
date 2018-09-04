#include <sqlite3.h>
#include <map>
#include <iterator>
#include <string>
using namespace std;
//查询sql的回调函数，把数据存到data指针指向的map<string,string>里面
static int callback_sqlite(void * data,int argc,char **argv,char **azColName){
    /*        vector<string> phonetic;
        vector<string> pos;
        vector<string> acceptation;
        vector<string> orig;
        vector<string> trans;*/
    int i=0;
    string keys[]={"word","phonetic","pos","acceptation","orig","trans"};
    for(i=0;i<argc;i++){
        (*(map<string,string>*)data).insert(pair<string,string>(keys[i],argv[i]?argv[i]:"NULL"));
    }
}