/*
*异常处理
*/
#ifndef __H__EXCEPTIONS__CLASS__
#define __H__EXCEPTIONS__CLASS__
#include <exception>
#include <string>
using std::string;
using std::exception;
class ArgException:public exception{
    public:
        ArgException(const char _des_[]="参数错误！"){des=string(_des_);}
        const char* what(){
            return des.c_str();
        }
        string& getDes(){return des;}
    private:
        string des;//异常描述
};
class FileIoException:public exception{
    public:
        FileIoException(const char _des_[]="文件IO错误"){des=string(_des_);}
        const char* what(){
            return des.c_str();
        }
        string& getDes(){return des;}
    private:
        string des;//异常描述
};
class CacheIoException:public FileIoException{
    public:
        CacheIoException(const char _des_[]="缓存文件无法正确读写！"):FileIoException(_des_){}
        const char* what(){
            return this->getDes().c_str();
        }
};
class DictIoException:public FileIoException{
    public:
        DictIoException(const char _des_[]="字典文件无法正确读写！"):FileIoException(_des_){}
        const char* what(){
            return this->getDes().c_str();
        }
};
class StrangeIoException:public FileIoException{
    public:
        StrangeIoException(const char _des_[]="无法正确读写生词本文件/文件夹"):FileIoException(_des_){}
        const char* what(){
            return this->getDes().c_str();
        }
};
class ConfigIoException:public FileIoException{
    public:
        ConfigIoException(const char _des_[]="无法正确读取配置文件~/.simple-dict/config.cfg"):FileIoException(_des_){}
        const char* what(){
            return this->getDes().c_str();
        }
};
#endif