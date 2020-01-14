//
// Created by gal on 14/01/2020.
//

#ifndef EX4__CACHEMANAGER_H_
#define EX4__CACHEMANAGER_H_
#include <iostream>
#include <list>
#include <fstream>
#include <unordered_map>
#include <functional>

using namespace std;

template <typename T>
class CacheManager {
 protected:
  unsigned int limitSize = 5;
 public:
  unordered_map<string, typename list<pair<string, T>>::iterator> cacheMap;
  list<pair<string, T>> cacheList;
  virtual void insert(string key, T obj) = 0;
  virtual T get(string key) = 0;
  virtual bool  checkSolutionExistent(string key) = 0;
  virtual void  foreach(const function<void(T&)> func) = 0;
};


template <typename T>
class FileCacheManager : public CacheManager<T> {
 private:

 public:
  FileCacheManager(int num) {
    this->limitSize = num;
  }
  void insert(string key, T obj) {
    typename unordered_map<string,typename list<pair<string,T>>::iterator>::iterator itMap
        = this->cacheMap.find(key);
    ofstream newFile;
    typename list<pair<string,T>>::iterator itList;
    // if the key is not exists in the map
    if(itMap == this->cacheMap.end()) {
      // there is not enough space
      if(this->cacheList.size()==this->limitSize) {
        itList = this->cacheList.begin();
        advance(itList, this->limitSize-1);
        string keyToDelete = itList->first;
        this->cacheList.erase(itList);
        itMap = this->cacheMap.find(keyToDelete);
        this->cacheMap.erase(itMap);
      }
      // if the key exists in the map
    } else {
      // delete the object from the list
      this->cacheList.erase(itMap->second);
    }
    // there is space, just put it on and write
    // insert the object to list
    this->cacheList.push_front(pair<string, T>(key, obj));
    // insert/update the object to the map
    itList = this->cacheList.begin();
    this->cacheMap[key] = itList;
    // write the object to file
    newFile.open (T::class_name+key, ios::binary);
    if(!newFile) {
      throw "problem! can't open file";
    } else {
      newFile.write((char *) & obj, sizeof(T));
      newFile.close();
    }
  }


  T get(string key) {
    ifstream inFile;
    T newObj;
    typename unordered_map<string,typename list<pair<string,T>>::iterator>::iterator itMap
        = this->cacheMap.find(key);
    // if the key is not exists in the map
    if(itMap == this->cacheMap.end()) {
      inFile.open(T::class_name+key, ios::binary);
      // check if exist in the files
      if(!inFile) {
        throw "problem! can't open file, maybe file is not exist";
      } else {
        inFile.read((char *) & newObj, sizeof(T));
        inFile.close();
      }
      // key exist in the map
    } else {
      newObj=itMap->second->second;
    }
    insert(key, newObj);
    return newObj;
  }

  bool virtual checkSolutionExistent(string key) {
    ifstream inFile;
    T newObj;
    typename unordered_map<string,typename list<pair<string,T>>::iterator>::iterator itMap
        = this->cacheMap.find(key);
    // if the key is not exists in the map
    if(itMap == this->cacheMap.end()) {
      inFile.open(T::class_name+key, ios::binary);
      // check if exist in the files
      if(!inFile) {
        return false;
      // // not exist in the files
      } else {
        return false;
      }
      // key exist in the map
    } else {
      return true;
    }
  }

  void foreach(const function<void(T&)> func) {
    typename list<pair<string,T>>::iterator itList = this->cacheList.begin();
    while(itList != this->cacheList.end()) {
      func(itList->second);
      advance(itList,1);
    }
  }







};




#endif //EX4__CACHEMANAGER_H_
