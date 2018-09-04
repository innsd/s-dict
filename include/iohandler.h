/*
*
*/
#ifndef __H__IOHANDLER__
#define __H__IOHANDLER__
#define CONFIG_FILE_LOC "~/.simple-dict/config.cfg"
#define CACHE_NAME "Cache.cache"
#define HISTORICAL_RECORD_NAME "His.cache"
#define STRANGE_WORD_NAME "strange.dat"
#include <iostream>
#include <string>
#include <fstream>
#include "analyzer.h"
#include "interpretation.h"
using std::ifstream;
using std::ostream;
using std::string;
class iohandler{
    public:
        iohandler(Analyzer& _info);
        int getRead_His_Num(){return read_history;}//查询历史记录的条数
        int getRead_Str_Num(){return read_strange;}//查询生词的条数
        string getWord(){return word;}
        string getDic_file(){return dict_file;}
        string getCache_path(){return cache_path;}
        string getStrang_word_path(){return strange_word_path;}
        string getHis_path(){return his_path;}
    private:
        int read_history;
        int read_strange;
        string word;
        string dict_file;
        string cache_path;
        string his_path;
        string strange_word_path;
};
class query:public iohandler{//查询器
    public:
        query(Analyzer& _info):iohandler(_info){}
        Interpretation getInterpretedDataObj();
        friend Interpretation inquire_core(ifstream& fin);
};
class storageWord:public iohandler{//单词存储器
    public:
        storageWord(Analyzer& _info,Interpretation& _a);
        void strange();
        void historyRecord();
    private:
        Interpretation InterpretedDataObj;
        string stdStorageData;//一行标准存储数据，格式为：单词|意思
};
class RecordReader:public iohandler{//记录阅读器
    public:
        RecordReader(Analyzer& _info):iohandler(_info){}
        void show_core(ifstream &fin,int n);
        void showHis();
        void showStrange();
};
#endif
