//
//  main.cpp
//  Run
//
//  Created by Radovan Klembara on 30/11/2020.
//

#include <iostream>

#include "simSimLib.hpp"


//auto narocne = std::make_shared<Facility>("Narocne");
auto normalni = std::make_shared<Facility>("Normalni");
auto kosik = std::make_shared<Resources>("kosik", 4);



class working: public RREvent {
    void behaviour() override {
        for (int i = 0; i < this->resource_handler.size(); i++) {
            this->resource_handler[i]->release();
        }
        std::cout << "zakaznik release " << this->get_id() << "\n";
    }
};

class work: public RREvent {
    void behaviour() override {
        std::cout << "zakaznik work " << this->get_id() << "\n";
        auto a = normalni->seize_or_reserve();
        auto d = this->resource_handler;
        auto l = [d](){
            std::cout << "kosik leave\n";
            for (int i = 0; i < d.size(); i++) {
                if (d[i]->service_line->name == "kosik") {
                    d[i]->release();
                }
            }
        };
        a->on_fail(20, l);
        auto workingg = std::make_shared<working>();
        workingg->resource_handler = this->resource_handler;
        a->on_success(workingg);
        
    }
};

class working_weak:public RREvent{
    void behaviour() override {
        this->resource_handler[0]->release();
        std::cout << "zakaznik weak release " << this->get_id() << "\n";
    }
};

class weak_work: public RREvent {
    void behaviour() override {
        std::cout << "zakaznik weak work " << this->get_id() << "\n" ;
        auto workingg = std::make_shared<working_weak>();
        workingg->resource_handler = this->resource_handler;
        workingg->plan(current_time + 10);
    };
};

class leave: public Event{
    void behaviour() override{
        std::cout << "weak work leaving " << this->get_id() << "\n";
    }
};

class zakaznik:public Event{
    void behaviour() override {
        if( Uniform_Random(0, 100) < 33 ){
            std::cout << "zakaznik created " << this->get_id() << "\n";
            auto a = kosik->seize_or_reserve(1);
            auto w = std::make_shared<work>();
            auto l = [](){
                std::cout << "I am leaving\n";
            };
            a->on_fail(20, l);
            a->on_success(w);
        } else {
            std::cout << "zakaznik weak created " << this->get_id() << "\n";
            auto a = normalni->seize_or_reserve();
//            auto w = std::make_shared<weak_work>();
            auto r = a->resource_handler;
            auto w = [](std::vector<std::shared_ptr<ResourceHandler>> r){
                std::cout << "zakaznik weak work in LAMBDA \n";
                auto workingg = std::make_shared<working_weak>();
                workingg->resource_handler = r;
                workingg->plan(current_time + 10);
            };
            auto l = std::make_shared<leave>();
            a->on_fail(10, l);
            a->on_success(w);
        }
    }
};

class generator: public Event{
    void behaviour() override{
        auto a = std::make_shared<zakaznik>();
        a->plan();
        this->plan(current_time + (rand()%20));
    }
};

int main(int argc, const char * argv[]) {
    std::cout << "start\n";
    auto sim = std::make_shared<Simulator>(0, 200);
    std::cout << "simulator created\n";
    auto a = std::make_shared<generator>();
    a->plan();
    std::cout << "genterator prepared\n";
    sim->run();
    simulation_info->print_out();
    generated_numbers_statistics->print_out();
    return 0;
}
