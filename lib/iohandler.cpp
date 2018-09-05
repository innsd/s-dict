#include "../include/interpretation.h"
#include "../include/iohandler.h"
#include "../include/analyzer.h"
#include "../include/libsql.h"
#include "../include/def.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <cstdlib>
#include <sqlite3.h>
#include <iterator>
#include <string>
#include <vector>
#include <cstring>
using std::endl;
using std::ofstream;
using std::ifstream;
using std::map;
using std::pair;
using std::iterator;
using std::ios_base;
using std::cout;
using std::string;
Interpretation inquire_core(sqlite3 * db,string word);
iohandler::iohandler(Analyzer& _info):word(_info.getWord()),dict_file(_info.getDict_file()),cache_path(_info.getCache_path()),strange_word_path(_info.getStrange_word_path()),his_path(_info.getHis_path()),read_history(_info.getNumReadHis()),read_strange(_info.getNumReadStr()){}
Interpretation query::getInterpretedDataObj(){//包装一下
    int rc;
    sqlite3 * db;
    rc=sqlite3_open(getDic_file().c_str(),&db);
    #ifdef _DEBUG_
    cout<<"字典文件路径："<<getDic_file()<<endl;
    #endif
    if(rc){cout<<"字典文件Error"<<endl;exit(0);}
    return inquire_core(db,getWord());
}
Interpretation inquire_core(sqlite3 * db,string word){
    Interpretation tempTransDataObj;
    char *ErrorInfo=0;
    int rc;
    map<string,string> WordData;
    WordData.insert(pair<string,string>("isExistWord","false"));
    string sql_cmd="select word,ps,pos,acceptation,orig,trans from words where word=\'";
    sql_cmd=sql_cmd+word+"\';";
    rc=sqlite3_exec(db,sql_cmd.c_str(),callback_sqlite,(void *)&WordData,&ErrorInfo);
    if(rc!=SQLITE_OK){
        cout<<"SQL ERROR:"<<ErrorInfo<<endl;
        sqlite3_free(ErrorInfo);
        exit(0);
    }else{
        #ifdef _DEBUG_
        cout<<"查询数据库成功"<<endl;
        #endif
    }
    sqlite3_close(db);
    map<string,string>::iterator it;
    it=WordData.find(string("isExistWord"));
    if(it->second!="true"){
        return tempTransDataObj;
    }
    string tempDataOfTrans;
    char *p;
    char *s;
    const char *delim="|QAQ|";
    #ifdef _DEBUG_
    cout<<"分割符："<<delim<<endl;
    #endif
    //"word","phonetic","pos","acceptation","orig","trans"
    it=WordData.find(string("word"));
    #ifdef _DEBUG_
    cout<<"查询的单词："<<it->second<<endl;
    #endif
    tempDataOfTrans=it->second;
    #ifdef _DEBUG_
    cout<<"单词str："<<tempDataOfTrans<<endl;
    #endif
    tempTransDataObj.setWord(tempDataOfTrans);
    it=WordData.find(string("phonetic"));
    tempDataOfTrans=it->second;
    s=(char *)tempDataOfTrans.c_str();
    p=strtok(s,delim);
    while(p){
        tempTransDataObj.addPhonetic(string(p));
        p=strtok(NULL,delim);
    }
    it=WordData.find(string("pos"));
    tempDataOfTrans=it->second;
    s=(char *)tempDataOfTrans.c_str();
    p=strtok(s,delim);
    while(p){
        tempTransDataObj.addPos(string(p));
        p=strtok(NULL,delim);
    }
    it=WordData.find(string("acceptation"));
    tempDataOfTrans=it->second;
    #ifdef _DEBUG_
    cout<<"意思str："<<tempDataOfTrans<<endl;
    #endif
    s=(char *)tempDataOfTrans.c_str();
    p=strtok(s,delim);
    while(p){
        tempTransDataObj.addAcceptation(string(p));
        p=strtok(NULL,delim);
    }
    it=WordData.find(string("orig"));
    tempDataOfTrans=it->second;
    #ifdef _DEBUG_
    cout<<"例句str："<<tempDataOfTrans<<endl;
    #endif
    s=(char *)tempDataOfTrans.c_str();
    p=strtok(s,delim);
    while(p){
        tempTransDataObj.addOrig(string(p));
        p=strtok(NULL,delim);
    }
    it=WordData.find(string("trans"));
    tempDataOfTrans=it->second;
    #ifdef _DEBUG_
    cout<<"翻译str："<<tempDataOfTrans<<endl;
    #endif
    s=(char *)tempDataOfTrans.c_str();
    p=strtok(s,delim);
    while(p){
        tempTransDataObj.addTrans(string(p));
        p=strtok(NULL,delim);
    }
    tempTransDataObj.setSginificative(true);
    return tempTransDataObj;
}
/*//缓存功能废弃。。。没啥用
void storageWord::cache(){
    string filepath=getCache_path()+CACHE_NAME;
    ofstream fout(filepath,ios_base::out|ios_base::app);
    fout<<translation.getWord()<<translation.getphonetic()<<translation.getExplain()<<endl;
    fout.close();
}*/
storageWord::storageWord(Analyzer& _info,Interpretation& _a):iohandler(_info),InterpretedDataObj(_a){
    stdStorageData=InterpretedDataObj.getWord()+"|"+InterpretedDataObj.getAccString();
}
void storageWord::strange(){
    string filepath=getStrang_word_path()+STRANGE_WORD_NAME;
    ofstream fout(filepath,ios_base::out|ios_base::app);
    fout<<stdStorageData<<endl;
    fout.close();
}
void storageWord::historyRecord(){//把这次查询的历史记录写入开头的办法就是，先写入一个临时文件，然后把原来的文件写入临时文件后面，然后用临时文件替换源文件
    #ifdef _DEBUG_
    cout<<"存储历史记录中"<<endl;
    #endif
    string filepath=getHis_path()+HISTORICAL_RECORD_NAME;
    string tempfile=getHis_path()+"h.temp";
    string temp;
    ofstream fout(tempfile,ios_base::out);
    ifstream fin(filepath,ios_base::in);
    fout<<stdStorageData<<endl;
    while(!fin.eof()){
        getline(fin,temp);
        fout<<temp<<endl;;
    }
    fin.close();
    fout.close();
    system(string("rm "+filepath).c_str());
    system(string("mv "+tempfile+" "+filepath).c_str());
}
void RecordReader::show_core(ifstream& fin,int n){
    int i=0;
    string temp;
    while((!fin.eof())&&i<n){
        getline(fin,temp);
        cout<<temp<<endl;
        i++;
    }
}
void RecordReader::showHis(){
    ifstream fin;
    fin.open(getHis_path()+HISTORICAL_RECORD_NAME,ios_base::in);
    show_core(fin,getRead_His_Num());
    fin.close();
}
void RecordReader::showStrange(){
    ifstream fin;
    fin.open(getStrang_word_path()+STRANGE_WORD_NAME,ios_base::in);
    show_core(fin,getRead_Str_Num());
    fin.close();
}

/*这个是以前用的自写的查询函数，因为使用了SQLite3,所以弃用了，但是。。。。emmmm自己写的垃圾代码。。。删掉也心疼啊。。。注释起来吧。
。。。。
代码："我佛慈悲，感谢不杀之恩！"
Interpretation inquire_core(ifstream& fin,string word){//核心函数
    string temp;
    string word_in_file;
    string phonetic_in_file;
    string explain_in_file;
    int line_n=0;//总行数
    int line_of_abc=0;//a'b'c'……开头的行数的临时标记
    const char abc[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    map<char,int> signs;
    getline(fin,temp);
    line_n=atoi(temp.c_str()+4);
    int i=0;
    for(i=0;i<26;i++){
        getline(fin,temp);
        line_of_abc=atoi(temp.c_str()+2);
        signs.insert(pair<char,int>(abc[i],line_of_abc));
    }
    ////!DEBUG!!!
    map<char,int>::iterator iter;
    for(iter=signs.begin();iter!=signs.end();iter++){
        cout<<iter->first<<':'<<iter->second<<endl;
    }
    ////!DEBUG!!!
    char initials;
    map<char,int>::iterator index=signs.find(initials=word.c_str()[0]);
    int front=index->second;
    index=signs.find(char((int)initials+1));
    int rear=index->second;
    i=(signs.find('a'))->second;
    while(i<front){//把文件指针移动到索引起始位置
        getline(fin,temp);
        i++;
    }
    while(i<rear){
        getline(fin,temp);
        int phonetic_front=temp.find_first_of('[');
        word_in_file.assign(temp,0,phonetic_front);
        if(word_in_file!=word){//如果不是要找的单词
            i++;
            continue;
        }else{//如果是
            cout<<temp<<endl;
            int phonetic_rear=temp.find_first_of(']');
            cout<<"phon_fort:"<<phonetic_front<<endl;
            cout<<"phon_rear:"<<phonetic_rear<<endl;
            phonetic_in_file.assign(temp,phonetic_front,++phonetic_rear-phonetic_front);
            explain_in_file.assign(temp,phonetic_rear,temp.length()-phonetic_rear);
            fin.close();
            return Interpretation(word_in_file,phonetic_in_file,explain_in_file);
        }
    }
    fin.close();
    return Interpretation();
}
*/