#include <sqlite3.h>
#include <map>
#include <iterator>
#include <string>
#include "def.h"
using namespace std;
//查询sql的回调函数，把数据存到data指针指向的map<string,string>里面
static int callback_sqlite(void * data,int argc,char **argv,char **azColName){
    /*        vector<string> phonetic;
        vector<string> pos;
        vector<string> acceptation;
        vector<string> orig;
        vector<string> trans;*/
    int i=0;
    #ifdef _DEBUG_
    printf("进入回调函数\n");
    #endif
    string keys[]={"word","phonetic","pos","acceptation","orig","trans"};
    for(i=0;i<argc;i++){
        #ifdef _DEBUG_
        printf("内存地址：%p\n",argv);
        printf("数据库查询中：%s\n",argv[i]);
        #endif
        (*(map<string,string>*)data).insert(pair<string,string>(keys[i],argv[i]?string(argv[i]):string("NULL")));
    }
    #ifdef _DEBUG_
    printf("退出回调函数\n");
    #endif
    (*(map<string,string>*)data)["isExistWord"]="true";
    return 0;
}
