#include "../include/analyzer.h"
#include "../include/exceptions.h"
#include "../include/iohandler.h"
//#include "../header/macro.h"
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <dirent.h>
#include <map>
#include <algorithm>
#define _DEBUG_
using std::ifstream;
using std::map;
using std::fstream;
using std::ios_base;
using std::pair;
using std::iterator;
using std::cout;
using std::endl;
Analyzer::Analyzer(int argc,char **argv){
    #ifdef _DEBUG_
    cout<<"argc:"<<argc<<endl;
    #endif
    __argn__=0;
    l=false;
    n=false;
    a=false;
    h=false;
    o=false;
    num_read_history=10;
    num_read_strange=10;
    char argMatchList[][3]={"-l","-n","-a","-h","-o","d","dl","ld","nl","ln"};
    if(argc>=2){
        if(!(strcmp(argMatchList[0],argv[1]))) {l=true;__argn__++;cout<<'l'<<endl;}
        if(!(strcmp(argMatchList[1],argv[1]))) {n=true;__argn__++;cout<<'n'<<endl;}
        if(!(strcmp(argMatchList[2],argv[1]))) {a=true;__argn__++;cout<<'a'<<endl;}
        if(!(strcmp(argMatchList[3],argv[1]))) {h=true;__argn__++;cout<<'h'<<endl;}
        if(!(strcmp(argMatchList[4],argv[1]))) {o=true;__argn__++;cout<<'o'<<endl;}
        if(!(strcmp(argMatchList[5],argv[1])&&strcmp(argMatchList[6],argv[1])&&strcmp(argMatchList[7],argv[1]))) {d=true;l=true;__argn__++;}
        if(!(strcmp(argMatchList[8],argv[1])&&strcmp(argMatchList[9],argv[1]))) {d=true;n=true;__argn__++;}

    }else if(argc<=1){
        throw ArgException();//没有任何参数，抛出异常
    }
    if((n||l)&&(argc>=3)){//如果有三个以上参数，只看第三个，其他扔掉
        word=string(argv[2]);
        #ifdef _DEBUG_
        cout<<"要查询的单词："<<word<<endl;
        #endif
    }else if((__argn__==0)&&(argc==2)){//如果只有单词参数(sdict {word})，那就默认进行本地查询
        l=true;
        __argn__++;
        word=string(argv[1]);
        #ifdef _DEBUG_
        cout<<"要查询的单词："<<word<<endl;
        #endif
    }
    if(h){
        if(argc>=3) num_read_history=atoi(argv[2]);//如果有第三个参数，就把第三个参数转化为数字
        else num_read_history=10;//如果没有，就默认显示十条历史记录
    }
    ifstream fin("/home/cheng/.simple-dict/config.cfg",ios_base::in);
    if(!fin){
        std::cout<<"读取配置文件失败\n";
        throw ConfigIoException();
    }else{
        std::cout<<"配置文件读取成功\n";
        string temp;
        string key_;
        string value_;
        int sign;
        map<string,string> conf;
        while(!fin.eof()){
            getline(fin,temp);
            cout<<"debug:"<<temp<<endl;
            sign=temp.find_first_of(':');
            key_.assign(temp,0,sign++);
            value_.assign(temp,sign,temp.length()-sign);
            cout<<"key:"<<key_<<"\tvalue"<<value_<<endl;
            conf.insert(pair<string,string>(key_,value_));
        }
        cout<<"声明迭代器"<<endl;
        map<string,string>::iterator it;
        for(it=conf.begin();it!=conf.end();it++){
            cout<<it->first<<'\t'<<it->second<<endl;
        }
        it=conf.find(string("dict"));
        cout<<"迭代器赋值"<<endl;
        dict_file=it->second;
        cout<<"访问迭代器元素"<<endl;
        cout<<dict_file<<endl;//debug
        it=conf.find(string("cache"));
        cache_path=it->second;
        cout<<cache_path<<endl;//
        it=conf.find(string("strange-word-dir"));
        strange_word_path=it->second;
        cout<<strange_word_path<<endl;//
        it=conf.find(string("history-record"));
        his_path=it->second;
        cout<<his_path<<endl;//
        it=conf.find(string("pri-query"));
        if(it->second==string("net")){
            pri_query=string("net");
        }else{
            pri_query=string("local");
        }
        cout<<pri_query<<endl;//
    }
}
bool Analyzer::check_arg(){
    if(__argn__>1){
        throw ArgException();
    }
    return true;
}
bool Analyzer::check_dict(){
    ifstream fin;
    fin.open(dict_file.c_str(),ios_base::in);
    if(!fin.is_open()){
        fin.close();
        throw DictIoException();
    }
    return true;
}
bool Analyzer::check_cache(){
    DIR* dir;
    if((dir=opendir(cache_path.c_str()))==NULL){
        system(string("mkdir "+cache_path).c_str());
    }
    string CacheFile=cache_path+CACHE_NAME;
    string hisCacheFile=cache_path+HISTORICAL_RECORD_NAME;
    fstream fio;
    fio.open(CacheFile.c_str(),ios_base::out|ios_base::app);
    if(!fio.is_open()){
        throw CacheIoException();
    }
    fio.close();
    fio.clear();
    fio.open(hisCacheFile.c_str(),ios_base::out|ios_base::app|ios_base::in);
    if(!fio.is_open()){
        throw CacheIoException();
    }
    fio.close();
    return false;
}
bool Analyzer::check_strange(){
    DIR* dir;
    if((dir=opendir(strange_word_path.c_str()))==NULL){
        system(string("mkdir "+strange_word_path).c_str());
    }
    string StrangeWordData=strange_word_path+STRANGE_WORD_NAME;
    fstream fio;
    fio.open(StrangeWordData.c_str(),ios_base::out|ios_base::app);
    if(!fio.is_open()){
        throw StrangeIoException();
    }
    fio.close();
    return true;
}
bool Analyzer::check(){
    check_arg();
    check_cache();
    check_dict();
    check_strange();
    return true;
}
