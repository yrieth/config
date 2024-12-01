#include <iostream>
#include "config.hpp"

yth::config::config(std::string name){
    this->configName=name;
}

void yth::config::addKey(std::string key, std::string value){
    std::ifstream fileToRead(this->configName);
    std::ofstream fileToWrite(TEMP_NAME);
    if (fileToRead.is_open() && fileToWrite.is_open()){
        std::string StrBuffer;
        fileToRead >> StrBuffer;
        while(!fileToRead.eof() && StrBuffer.compare(key)<0){
            fileToWrite << StrBuffer;
            fileToWrite << std::endl;
            fileToRead >> StrBuffer;
            fileToWrite << StrBuffer;
            fileToWrite << std::endl;
            fileToRead >> StrBuffer;
        }
        if (fileToRead.eof()){
            fileToWrite << key;
            fileToWrite << std::endl;
            fileToWrite << value;
            fileToWrite << std::endl;
        }
        else if (StrBuffer == key){
            fileToRead.close();
            fileToWrite.close();
            remove(TEMP_NAME);
            throw "The given key already exists";
        }
        else{
            fileToWrite << key;
            fileToWrite << std::endl;
            fileToWrite << value;
            fileToWrite << std::endl;
            while(!fileToRead.eof()){
                fileToWrite << StrBuffer;
                fileToWrite << std::endl;
                fileToRead >> StrBuffer;
                fileToWrite << StrBuffer;
                fileToWrite << std::endl;
                fileToRead >> StrBuffer;
            }
        }
        fileToRead.close();
        fileToWrite.close();
        remove(this->configName.c_str());
        rename(TEMP_NAME, this->configName.c_str());
        
    }
    else if (!fileToRead.is_open() && fileToWrite.is_open()){
        fileToWrite << key << std::endl;
        fileToWrite << value << std::endl;

        fileToWrite.close();
        rename(config::TEMP_NAME, this->configName.c_str());
    }
    else {
        throw "Can not write in the given file";
    }
}

void yth::config::addKey(std::string key){
    addKey(key, NULL_VALUE);
}

void yth::config::removeKey(std::string key){
    std::ifstream fileToRead(this->configName);
    std::ofstream fileToWrite(TEMP_NAME);
    if (fileToRead.is_open() && fileToWrite.is_open()){
        std::string StrBuffer;
        fileToRead >> StrBuffer;
        while(!fileToRead.eof() && StrBuffer.compare(key)<0){
            fileToWrite << StrBuffer;
            fileToWrite << std::endl;
            fileToRead >> StrBuffer;
            fileToWrite << StrBuffer;
            fileToWrite << std::endl;
            fileToRead >> StrBuffer;
        }
        if (fileToRead.eof()){}
        else{
            if (StrBuffer == key){
                fileToRead >> StrBuffer;
                fileToRead >> StrBuffer;
            }
            while(!fileToRead.eof()){
                fileToWrite << StrBuffer;
                fileToWrite << std::endl;
                fileToRead >> StrBuffer;
                fileToWrite << StrBuffer;
                fileToWrite << std::endl;
                fileToRead >> StrBuffer;
            }
        }
        fileToRead.close();
        fileToWrite.close();
        remove(this->configName.c_str());
        rename(TEMP_NAME, this->configName.c_str());
        
    }
    else {
        throw "Config not found";
    }
}

void yth::config::setValue(std::string key, std::string value){
    std::ifstream fileToRead(this->configName);
    std::ofstream fileToWrite(TEMP_NAME);
    if (fileToRead.is_open() && fileToWrite.is_open()){
        std::string StrBuffer;
        fileToRead >> StrBuffer;
        while(!fileToRead.eof() && StrBuffer.compare(key)<0){
            fileToWrite << StrBuffer;
            fileToWrite << std::endl;
            fileToRead >> StrBuffer;
            fileToWrite << StrBuffer;
            fileToWrite << std::endl;
            fileToRead >> StrBuffer;
        }
        if (fileToRead.eof() || StrBuffer != key){
            fileToRead.close();
            fileToWrite.close();
            remove(TEMP_NAME);
            throw "Key not found";
        }
        else{
            fileToWrite << StrBuffer;
            fileToWrite << std::endl;
            fileToRead >> StrBuffer;
            fileToWrite << value;
            fileToWrite << std::endl;
            fileToRead >> StrBuffer;
            while(!fileToRead.eof()){
                fileToWrite << StrBuffer;
                fileToWrite << std::endl;
                fileToRead >> StrBuffer;
                fileToWrite << StrBuffer;
                fileToWrite << std::endl;
                fileToRead >> StrBuffer;
            }
        }
        fileToRead.close();
        fileToWrite.close();
        remove(this->configName.c_str());
        rename(TEMP_NAME, this->configName.c_str());
        
    }
    else {
        throw "Can not write in the given file";
    }
}

std::string yth::config::getValue(std::string key){
    std::ifstream fileToRead(this->configName);
    if (fileToRead.is_open()){
        std::string StrBuffer;
        fileToRead >> StrBuffer;
        while (!fileToRead.eof() && StrBuffer.compare(key)<0){
            fileToRead >> StrBuffer;
            fileToRead >> StrBuffer;
        }
        if (StrBuffer == key){
            fileToRead >> StrBuffer;
            fileToRead.close();
            return StrBuffer;
        }
        else {
            fileToRead.close();
            throw "Key not found";
        }
    }
    else {
        throw "Config not found";
    }
}
