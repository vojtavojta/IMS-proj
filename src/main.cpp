//
//  main.cpp
//  Run
//
//  Created by Radovan Klembara on 30/11/2020.
//

#include <iostream>

#include "simSimLib.hpp"



auto cashDesk = std::make_shared<Facility>("Cash_desk");
auto shoppingTrolley = std::make_shared<Resources>("shopping_trolley", 25);
auto delicatessen = std::make_shared<Resources>("delicatessen", 2);



class leaving: public RREvent {
    void behaviour() override {
        for (int i = 0; i < this->resource_handler.size(); i++) {
           if (this->resource_handler[i]->service_line->name != "delicatessen") {
                  this->resource_handler[i]->release();
                }
        }


    }
};

class payment: public RREvent {
    void behaviour() override {
        std::cout << "customer payment " << this->get_id() << "\n" ;
        auto l = std::make_shared<leaving>();
        l->resource_handler = this->resource_handler;
        l->plan(current_time + Exp_Random(7)); 
    };
};

class goods_selected: public RREvent {
    void behaviour() override {
        std::cout << "goods selected" << this->get_id() << "\n";
        auto a = cashDesk->seize_or_reserve();
        auto d = this->resource_handler;
        auto l = [d](){
            std::cout << "ERROR customer cant leave without paying\n";
        };
        a->on_fail(120000, l);
        auto p = std::make_shared<leaving>();
        p->resource_handler = this->resource_handler;
        a->on_success(p);
        
    }
};


class shoping: public RREvent {
    void behaviour() override {
        std::cout << "customer is shoping" << this->get_id() << "\n" ;
        auto goods = std::make_shared<goods_selected>();
        goods->resource_handler = this->resource_handler;
        goods->plan(current_time + Exp_Random(15));
    };
};

class delicatessen_end: public RREvent {
    void behaviour() override {
        std::cout << "customer is ending delicatessen" << this->get_id() << "\n" ;
        for (int i = 0; i < this->resource_handler.size(); i++) {
                if (this->resource_handler[i]->service_line->name == "delicatessen") {
                    this->resource_handler[i]->release();
                }
            }
        auto goods = std::make_shared<shoping>();
        goods->resource_handler = this->resource_handler;
        goods->plan(current_time + Exp_Random(4));
    };
};

class delicatessen_shoping: public RREvent {
    void behaviour() override {
        std::cout << "customer is shopingin delicatessen" << this->get_id() << "\n" ;
        auto goods = std::make_shared<delicatessen_end>();
        goods->resource_handler = this->resource_handler;
        goods->plan(current_time + Exp_Random(4));
    };
};

class delicatessen_queue: public RREvent {
    void behaviour() override {
        std::cout << "customer in delicatessen queue" << this->get_id() << "\n";
        auto a = delicatessen->seize_or_reserve(1);
        auto d = this->resource_handler;
        auto l = [d](){
            std::cout << "ERROR customer cant leave without paying\n";
        };
        a->on_fail(120000, l);
        auto p = std::make_shared<delicatessen_shoping>();
        p->resource_handler = this->resource_handler;
        a->on_success(p);
        
    }
};


class choosing_customer_type: public RREvent {
    void behaviour() override {
        if(Norm_Random(0, 100) > 70){
            auto s = std::make_shared<delicatessen_queue>();
            s->resource_handler = this->resource_handler;
            s->plan();
        }
        else {
            auto m = std::make_shared<shoping>();
            m->resource_handler = this->resource_handler;
            m->plan();
        }
    }
};

class take_trolley:public Event{
    void behaviour() override {
            std::cout << "customer created " << this->get_id() << "\n";
            auto a = shoppingTrolley->seize_or_reserve(1);
            auto w = std::make_shared<choosing_customer_type>();
            auto l = [](){
                std::cout << "I am leaving\n";
            };
            a->on_fail(1, l);
            a->on_success(w);
    }
};

class customer_generator: public Event{
    void behaviour() override{
        auto a = std::make_shared<take_trolley>();
        a->plan();
        this->plan(current_time + (Exp_Random(5))); 
    }
};


class delivery_end: public RREvent {
    void behaviour() override {
        std::cout << "delivery is ending delicatessen" << this->get_id() << "\n" ;
        for (int i = 0; i < this->resource_handler.size(); i++) {
                if (this->resource_handler[i]->service_line->name == "delicatessen") {
                    this->resource_handler[i]->release();
                }
            }
    };
};

class delivery_working: public RREvent {
    void behaviour() override {
        std::cout << "delivery working" << this->get_id() << "\n" ;
        auto d = std::make_shared<delivery_end>();
        d->resource_handler = this->resource_handler;
        d->plan(current_time + Exp_Random(15));
    };
};


class delivery_in_delicatessen:public Event{
    void behaviour() override {
            std::cout << "delivery in delicatessen" << this->get_id() << "\n";
            auto a = delicatessen->seize_or_reserve(1,1);
            auto w = std::make_shared<delivery_working>();
            auto l = [](){
                std::cout << "can't delivery\n";
            };
            a->on_fail(30, l);
            a->on_success(w);
    }
};

class delivery_generator: public Event{
    void behaviour() override{
        std::cout << "delivery of goods\n";
        auto a = std::make_shared<delivery_in_delicatessen>();
        a->plan();
        this->plan(current_time + (Norm_Random(30,1))); 
    }
};

int main(int argc, const char * argv[]) {
    std::cout << "start\n";
    auto sim = std::make_shared<Simulator>(0, 480);
    std::cout << "simulator created\n";
    auto a = std::make_shared<customer_generator>();
    a->plan();
    std::cout << "customer_genterator prepared\n";
    auto d = std::make_shared<delivery_generator>();
    d->plan(current_time + (Norm_Random(30,1)));
    std::cout << "delivery_genterator prepared\n";
    sim->run();
    simulation_info->print_out();
    //generated_numbers_statistics->print_out();
    return 0;
}
