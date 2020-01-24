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

template <typename S>
class CacheManager {
 protected:
  // limit size of space in the cache
  unsigned int limitSize = 5;
 public:
  virtual ~CacheManager() {};
  // the cache;
  unordered_map<string, typename list<pair<string, S>>::iterator> cacheMap;
  // list for priority for the cache
  list<pair<string, S>> cacheList;
  /**
   * insert object S to the cache
   * @param key name of object
   * @param obj the object we want to save
   */
  virtual void insert(string key, S obj) = 0;
  /**
   * load our solution
   * @param key name of the solution
   * @return solution S
   */
  virtual S get(string key) = 0;
  /**
   * check if the solution exist in the cache
   * @param key name of the solution
   * @return boolean answer
   */
  virtual bool  checkSolutionExistent(string key) = 0;
  virtual void  foreach(const function<void(S&)> func) = 0;
};


template <typename S>
class FileCacheManager : public CacheManager<S> {
 private:

 public:
  FileCacheManager(int num) {
    this->limitSize = num;
  }
  void insert(string key, S obj) {
    typename unordered_map<string,typename list<pair<string,S>>::iterator>::iterator itMap
        = this->cacheMap.find(key);
    ofstream newFile;
    typename list<pair<string,S>>::iterator itList;
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
    this->cacheList.push_front(pair<string, S>(key, obj));
    // insert/update the object to the map
    itList = this->cacheList.begin();
    this->cacheMap[key] = itList;
    // write the object to file
    newFile.open (key, ios::binary);
//    newFile.open (T::class_name+key, ios::binary);
    if(!newFile) {
      throw "problem! can't open file";
    } else {
      newFile.write((char *) & obj, sizeof(S));
      newFile.close();
    }
  }


  S get(string key) {
    ifstream inFile;
    S newObj;
//    S* newObj;
    typename unordered_map<string,typename list<pair<string,S>>::iterator>::iterator itMap
        = this->cacheMap.find(key);
    // if the key is not exists in the map
    if(itMap == this->cacheMap.end()) {
//      inFile.open(T::class_name+key, ios::binary);
      inFile.open(key, ios::binary);

      // check if exist in the files
      if(!inFile) {
        throw "problem! can't open file, maybe file is not exist";
      } else {
        inFile.read((char *) & newObj, sizeof(S));
        inFile.close();
      }
      // key exist in the map
    } else {
      newObj=itMap->second->second;
    }
    insert(key, newObj);
    return newObj;
  }

  bool checkSolutionExistent(string key) {
    ifstream inFile;
//    S newObj;
    typename unordered_map<string,typename list<pair<string,S>>::iterator>::iterator itMap
        = this->cacheMap.find(key);
    // if the key is not exists in the map
    if(itMap == this->cacheMap.end()) {
      inFile.open(key, ios::binary);
//      inFile.open(T::class_name+key, ios::binary);
      // check if exist in the files
      if(!inFile) {
        return false;
      // // not exist in the files
      } else {
        return true;
      }
      // key exist in the map
    } else {
      return true;
    }
  }

  void foreach(const function<void(S&)> func) {
    typename list<pair<string,S>>::iterator itList = this->cacheList.begin();
    while(itList != this->cacheList.end()) {
      func(itList->second);
      advance(itList,1);
    }
  }

};

#endif //EX4__CACHEMANAGER_H_
