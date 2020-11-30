////
////  facilityClass.cpp
////  SimSimLib
////
////  Created by Radovan Klembara on 29/11/2020.
////
//
//#include "facilityClass.hpp"
//#include <algorithm>
//
//
//Facility::Facility(std::string name){
//    this->name = name;
//}
//
//void Facility::sieze(){
//    this->fac_mutex.lock();
//}
//
//void Facility::release(){
//    this->fac_mutex.unlock();
//}
//
//
//bool Facility::try_lock(){
//    if (this->fac_mutex.try_lock()) {
//        return true;
//    } else {
//        return false;
//    }
//}
//
//
