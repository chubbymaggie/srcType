#ifndef SRCTYPE_HPP
#define SRCTYPE_HPP

#include <srcTypeHandler.hpp>
#include <srcSAXController.hpp>
#include <iostream> 

namespace srcTypeNS{
    class srcType{
        TypeDictionary dictionary;
        public:
            srcType();
            srcType(const char*, const char*);
            srcType(std::string, const char*);
            srcType(FILE*, const char*);
            srcType(int, const char*);
            void ReadArchiveFile(std::string);
            int size()const {return dictionary.fvMap.size();}
            SScopeProfile GetScopeProfile() const{
                return SScopeProfile(dictionary.currentContext.currentFunc->second);
            }
            bool SetContext(std::string fn, int linenumber){
                FunctionVarMap::iterator it = dictionary.fvMap.find(fn);
                if(it != dictionary.fvMap.end()){
                    dictionary.currentContext.currentFunc = it;
                    dictionary.currentContext.ln = linenumber;
                    dictionary.currentContext.functionName = fn;
                    return true;
                }
                return false;
            }
            bool SetContext(int linenumber){
                if(dictionary.currentContext.currentFunc != dictionary.fvMap.end()){
                    dictionary.currentContext.ln = linenumber;
                    return true;
                }
                return false;
            }
            //Definition of find that assumes the user didn't give a context (They should just give a context, though, tbh).
            std::pair<bool, NameProfile> Find(std::string funcname, std::string varname, int lineNumber)const{
                FunctionVarMap::const_iterator fvmIt = dictionary.fvMap.find(funcname);
                if(fvmIt != dictionary.fvMap.end()){
                    VarTypeMap::const_iterator vtmIt = fvmIt->second.vtMap.find(varname+std::to_string(lineNumber));
                    if(vtmIt != fvmIt->second.vtMap.end()){
                        return std::make_pair(true, vtmIt->second);
                    }
                }
                return std::make_pair(false, NameProfile());
            }
            //Definition of find that uses the context (so it doesn't need to take a function name as context)
            std::pair<bool, NameProfile> Find(std::string varname) const{
                if(!dictionary.currentContext.IsSet()){
                    throw std::runtime_error("Context not set"); //for now, std exception
                }else{
                    VarTypeMap::const_iterator it = dictionary.currentContext.currentFunc->second.vtMap.find(varname+std::to_string(dictionary.currentContext.ln));
                    if(it != dictionary.currentContext.currentFunc->second.vtMap.end()){
                        return std::make_pair(true, it->second);
                    }
                    return std::make_pair(false, NameProfile());
                }
            }
            bool Insert(std::string funcname, const NameProfile& np){
                FunctionVarMap::iterator fvmIt = dictionary.fvMap.find(funcname);
                if(fvmIt != dictionary.fvMap.end()){
                    VarTypeMap::iterator vtmIt = fvmIt->second.vtMap.find(np.name+std::to_string(np.linenumber));
                    if(vtmIt != fvmIt->second.vtMap.end()){
                        vtmIt->second = np;
                        return true;
                    }else{
                        fvmIt->second.vtMap.insert(std::make_pair(np.name, np));
                        return true;
                    }
                }
                return false;
            }
            bool Insert(const NameProfile& np){
                if(dictionary.currentContext.ln == -1){
                    throw std::runtime_error("Context not set"); //for now, std exception
                }else{
                    auto it = dictionary.currentContext.currentFunc->second.vtMap.find(np.name+std::to_string(np.linenumber));
                    if(it != dictionary.currentContext.currentFunc->second.vtMap.end()){
                        it->second = np;
                        return true;
                    }else{
                        dictionary.currentContext.currentFunc->second.vtMap.insert(std::make_pair(np.name, np));
                        return true;
                    }
                }
                return false;
            }
    
    };
}
#endif