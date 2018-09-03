/*
*analyzer类封装着各项参数，例如本地查询/网络查询？生次本文件地址等
*并且封装了异常检查函数，检测参数异常
*L N A H O D
*优先进行本地查询
*L:local本地数据库查询 sdict -l {word}/sdict {word}都将进行本地查询
*N：Net网络查询 sdict -n {word}
*A：add生词本，sdict -a默认添加上一次查询的单词到生词本sdict -a {word}添加指定单词到生次本
*H：历史记录查询，默认显示十条历史记录，
*O：
*D：详细信息查询，默认查询出来的都显示简要信息，加d参数显示单词详细音标例句信息用法sdict -d {word}/sdict -(ld/dl) {word} 查询本地详细单词信息
*sdict -(nd/dn) {word}查询网络详细信息
*/
#ifndef __H__ANALYZER__CLASS__
#define __H__ANALYZER__CLASS__
#include <string>
using std::string;
class Analyzer{
    public:
        Analyzer(int argc,char **argv);
        ~Analyzer(){};
        int getNumReadHis(){return num_read_history;}
        int getNumReadStr(){return num_read_strange;}
        string getWord(){return word;}
        string getDict_file(){return dict_file;}
        string getCache_path(){return cache_path;}
        string getStrange_word_path(){return strange_word_path;}
        string getHis_path(){return his_path;}
        string getPri_query(){return pri_query;}
        void setPri_query(string pri){pri_query=pri;}
        bool getL(){return l;}
        bool getN(){return n;}
        bool getA(){return a;}
        bool getH(){return h;}
        bool getD(){return d;}
        bool getO(){return o;}
        bool check_arg();
        bool check_cache();
        bool check_dict();
        bool check_strange();
        bool check();
    private:
        string word;
        string dict_file;
        string cache_path;
        string his_path;
        string strange_word_path;
        string pri_query;
        int __argn__;
        bool l;//是否指定本地查询
        bool n;//是否指定网络擦汗
        bool a;//添加生次本
        bool h;//是否查询历史记录
        bool d;//是否显示详细信息
        bool o;//
        int num_read_history;
        int num_read_strange;
};
#endif