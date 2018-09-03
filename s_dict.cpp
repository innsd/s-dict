#include <memory>
#include "include/analyzer.h"
#include "include/exceptions.h"
#include "include/interpretation.h"
#include "include/iohandler.h"
#define _DEBUG_
int main(int argc,char *argv[]){
    using std::cerr;
    using std::cout;
    using std::endl;
    using std::unique_ptr;
    unique_ptr<Analyzer> ptr_Analyz;//指向分析器的一个智能指针
    try{
        ptr_Analyz=unique_ptr<Analyzer>(new Analyzer(argc,argv));//用命令行传入的参数，初始化这个分析器
        cout<<"分析器初始化完成！"<<endl;
        ptr_Analyz->check();
    }catch(ArgException& e){
        cerr << e.what() << '\n';
        //cout<<help
        return 1;
    }catch(FileIoException& e){
        cerr << e.what() << '\n';
    }catch( ... ){
        cerr<<"未知异常，请联系innsd@qq.com修复BUG\n";
    }
    if(ptr_Analyz->getH()){
        #ifdef _DEBUG_
        cout<<"最近"<<ptr_Analyz->getNumReadHis()<<"历史记录"<<endl;
        #endif
        RecordReader File_reader(*ptr_Analyz);
        File_reader.showHis();
    }else if(ptr_Analyz->getA()){
        //生词本添加
    }else if(ptr_Analyz->getL()||ptr_Analyz->getN()){
        //查询
        Interpretation InterpretedDataObj;//把翻译好的数据封装成对象
        if(ptr_Analyz->getN()){//优先判断是否网络查询
            //网络查询
            //暂时不打算写，因为本地使用的55000条单词数据就是从网上抓取的
            //感觉写网络查询的意义好像不是很大
            //
        }else{
            query qer(*ptr_Analyz);//生成一个查询器
            //本地查询
            #ifdef _DEBUG_
            cout<<"开始本地查询"<<endl;
            #endif
            InterpretedDataObj=qer.search();//查询器，从数据库里面分析数据，返回一个封装好的对象
           if(!(InterpretedDataObj.isSignificFunc())){//如果没有查到，就会返回一个无效的对象，对象的isSignificFunc()方法返回为0
                cout<<"没有查询到本地结果,正在进行网络查询..."<<endl;
                //网络查询
                //a=...
            }
        }
        if(!(InterpretedDataObj.isSignificFunc())){
            cout<<"没有查询到单词的意思！\n";
            return 2;
        }
        #ifdef _DEBUG_
        cout<<"---------DEBUG---------"<<endl;
        #endif
        if(ptr_Analyz->getD()){
            InterpretedDataObj.showDetail();//显示单词详细
        }
        else{
            InterpretedDataObj.showSimple();//简略信息显示
        }
        storageWord owo(*ptr_Analyz,InterpretedDataObj);
        owo.historyRecord();
    }else if(ptr_Analyz->getO()){
        //输出生词本
    }
    return 0;
}
