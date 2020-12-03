////
////  storeClass.cpp
////  SimSimLib
////
////  Created by Radovan Klembara on 29/11/2020.
////
//
//#include "storeClass.hpp"
//#include "resourcePromiseClass.hpp"
//
//
//Resources::Resources(std::string name, unsigned long sources): Facility(name){
////    this->name = name;
//    this->capacity = sources;
//    this->current_sources = sources;
//}
//
//std::shared_ptr<ResourcePromise> Resources::seize_or_reserve(unsigned long source_number){
//    auto ptr_this = shared_from_this();
//    std::shared_ptr<ResourcePromise> promise(new ResourcePromise(source_number, ptr_this));
//    if (this->current_sources >= source_number && this->promises.empty()) {
//        promise->satisfied = true;
//        this->current_sources -= source_number;
//        promise->resource_handler->receive_resources(source_number);
//    } else {
//        this->promises.push(promise);
//    }
//    return promise;
//}
//
//void Resources::get_back(unsigned long number){
//    this->current_sources += number;
//    if(!this->promises.empty() && this->promises.front()->resource_handler->my_resources() <= this->current_sources){
//        auto new_prom = this->promises.front();
//        unsigned long req_res = new_prom->resource_handler->required_resources();
//        this->current_sources -= req_res;
//        new_prom->resource_handler->receive_resources(req_res);
//        this->promises.pop();
//        new_prom->satisfy();
//    }
//}
//
////void Resources::setName(std::string new_name){
////    name = new_name;
////}
//
////void Resources::remove_promise(ResourcePromise * promise){
////    std::queue<std::shared_ptr<ResourcePromise>> new_queue{};
////    while (!this->promises.empty()) {
////        std::shared_ptr<ResourcePromise> tmp = this->promises.front();
////        this->promises.pop();
////        if (tmp->id != promise->id) {
////            new_queue.push(tmp);
////        }
////    }
////    this->promises = new_queue;
////}
