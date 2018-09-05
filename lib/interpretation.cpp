#include <iostream>
#include <string>
#include "../include/interpretation.h"
#include "../include/def.h"
#include <vector>
#include <iterator>
using std::cout;
using std::vector;
using std::string;
using std::endl;
Interpretation::Interpretation():isSignificative(false){}
//Interpretation::Interpretation(string __word,string __phonetic,string __explain):word(__word),phonetic(__phonetic),explain(__explain),isSignificative(true){}
void Interpretation::showSimple(){
    if(!isSignificative){
        cout<<"无查询结果."<<endl;
    }
    string accStr;
    vector<string>::iterator itPos;
    vector<string>::iterator itAcc;
    for(itPos=pos.begin(),itAcc=acceptation.begin();(itPos!=pos.end())&&(itAcc!=acceptation.end());++itPos,++itAcc){
        accStr=accStr+*itPos+*itAcc+'\n';
    }
    cout<<"单词："<<word<<endl;
    cout<<"释义：\n"<<accStr;
}
void Interpretation::showDetail(){
    string accStr;
    string psStr;
    string sentenceStr;
    vector<string>::iterator itPos;
    vector<string>::iterator itAcc;
    vector<string>::iterator itPs;
    vector<string>::iterator itOrig;
    vector<string>::iterator itTrans;
    for(itPos=pos.begin(),itAcc=acceptation.begin();(itPos!=pos.end())&&(itAcc!=acceptation.end());++itPos,++itAcc){
        accStr=accStr+*itPos+*itAcc+'\n';
    }
    for(itPs=phonetic.begin();itPs!=phonetic.end();++itPs){
        psStr=psStr+'['+*itPs+']'+' ';
    }
    for(itOrig=orig.begin(),itTrans=trans.begin();(itOrig!=orig.end())&&(itTrans!=trans.end());++itOrig,++itTrans){
        sentenceStr=sentenceStr+*itOrig+'\n'+*itTrans+"\n\n";
    }
    cout<<"单词："<<word<<endl;
    cout<<"音标："<<psStr<<endl;
    cout<<"释义：\n"<<accStr<<endl;
    cout<<"句子：\n"<<sentenceStr<<endl;
}
string Interpretation::getAccString(){
    string temp;
    vector<string>::iterator itPos;
    vector<string>::iterator itAcc;
    for(itPos=pos.begin(),itAcc=acceptation.begin();(itPos!=pos.end())&&(itAcc!=acceptation.end());++itPos,++itAcc){
        temp=temp+*itPos+","+*itAcc+";";
    }
    return temp;
}
void Interpretation::setWord(string w){
    this->word=w;
    #ifdef _DEBUG_
    cout<<"设置单词为："<<w<<endl;
    #endif
}
void Interpretation::addPhonetic(string p){
    this->phonetic.push_back(p);
    #ifdef _DEBUG_
    cout<<"添加音标："<<p<<endl;
    #endif
}
void Interpretation::addPos(string p){
    this->pos.push_back(p);
    #ifdef _DEBUG_
    cout<<"添加POS："<<p<<endl;
    #endif
}
void Interpretation::addAcceptation(string acc){
    this->acceptation.push_back(acc);
    #ifdef _DEBUG_
    cout<<"添加意思："<<acc<<endl;
    #endif
}
void Interpretation::addOrig(string o){
    this->orig.push_back(o);
    #ifdef _DEBUG_
    cout<<"添加例句："<<o<<endl;
    #endif
}
void Interpretation::addTrans(string t){
    this->trans.push_back(t);
    #ifdef _DEBUG_
    cout<<"添加翻译："<<t<<endl;
    #endif
}
void Interpretation::setSginificative(bool b){
    isSignificative=b;
}