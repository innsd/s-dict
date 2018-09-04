/*
*Interpretation类的原型文件，该类封装了单词及其词典信息，以及show方法
*/
#ifndef __H__INTERPRETATION__CLASS_
#define __H__INTERPRETATION__CLASS_
#include <string>
#include <vector>
using std::string;
using std::vector;
class Interpretation{
    public:
        Interpretation();
        //void cache();
        void showDetail();
        void showSimple();
        bool isSignificFunc(){return isSignificative;}
        string getWord(){return word;}
        string getAccString();//返回释义的string数据，格式为"词性1,释义;词性2,释义;……"
        vector<string> getPhonetic(){return phonetic;}
        vector<string> getAcceptation(){return acceptation;}
        vector<string> getPos(){return pos;}
        vector<string> getOrig(){return orig;}
        vector<string> getTrans(){return trans;}
        void setWord(string);
        void setSginificative(bool);
        void addPhonetic(string);
        void addPos(string);
        void addAcceptation(string);
        void addOrig(string);
        void addTrans(string);
    private:
        bool isSignificative;
        string word;
        vector<string> phonetic;
        vector<string> pos;
        vector<string> acceptation;
        vector<string> orig;
        vector<string> trans;
};
#endif