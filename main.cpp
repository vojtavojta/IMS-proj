//
//  main.cpp
//  Run
//
//  Created by Vojtech Hranicka on 05/12/2020.
//
//Model of shop
// shop have 25 shopping carts, 2 shop assistants in delicatessen and 1 cash desk. 
// Customers are coming every 1 minute with exponential distribution.
//30% of customers go to the delicatessen. Services in delicatessen last 4 minutes with exponential distribution.
//Customers must pay at the cash desk. Paying last 7 minutes with exponential distribution.
//After payment customers leave shop.
//Every 30 minutes to the delicatessen comes new deliverz of goods and 1 shop assistant must help with it for 15 minutes.

#include <iostream>

#include "src/simSimLib.hpp"

// #include "numberGenerator.hpp"


auto cashDesk = std::make_shared<Facility>("Cash_desk");
auto shoppingTrolley = std::make_shared<Resources>("shopping_trolley", 25);
auto delicatessen = std::make_shared<Resources>("delicatessen", 2);


//customer is leaving the shop
class leaving: public RREvent {
    void behaviour() override {
        for (int i = 0; i < this->resource_handler.size(); i++) {
           if (this->resource_handler[i]->service_line->name != "delicatessen") {
                  this->resource_handler[i]->release();
                }
        }


    }
};
//customer pays
class payment: public RREvent {
    void behaviour() override {
        auto l = std::make_shared<leaving>();
        l->resource_handler = this->resource_handler;
        l->plan(current_time + Exp_Random(7)); 
    };
};
//customer goes to the cash desk
class goods_selected: public RREvent {
    void behaviour() override {
        auto a = cashDesk->seize_or_reserve();
        auto d = this->resource_handler;
        auto l = [d](){
        };
        a->on_fail(120000, l);
        auto p = std::make_shared<leaving>();
        p->resource_handler = this->resource_handler;
        a->on_success(p);
        
    }
};

//customer is shoping
class shoping: public RREvent {
    void behaviour() override {
        auto goods = std::make_shared<goods_selected>();
        goods->resource_handler = this->resource_handler;
        goods->plan(current_time + Exp_Random(15));
    };
};
//customer is leaving delicatessen
class delicatessen_end: public RREvent {
    void behaviour() override {
        for (int i = 0; i < this->resource_handler.size(); i++) {
                if (this->resource_handler[i]->service_line->name == "delicatessen") {
                    this->resource_handler[i]->release();
                }
            }
        auto goods = std::make_shared<shoping>();
        goods->resource_handler = this->resource_handler;
        goods->plan();
    };
};
//customer is shoping in delicatessen
class delicatessen_shoping: public RREvent {
    void behaviour() override {
        auto goods = std::make_shared<delicatessen_end>();
        goods->resource_handler = this->resource_handler;
        goods->plan(current_time + Exp_Random(4));
    };
};
//customer waits in delicatessen
class delicatessen_queue: public RREvent {
    void behaviour() override {
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

// 30% of customers go to the delicatessen 
class choosing_customer_type: public RREvent {
    void behaviour() override {
        if(Uniform_Random(0, 100) > 70){
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
//customer take a shoping trolley 
class take_trolley:public Event{
    void behaviour() override {
            auto a = shoppingTrolley->seize_or_reserve(1);
            auto w = std::make_shared<choosing_customer_type>();
            auto l = [](){
            };
            a->on_fail(1, l);
            a->on_success(w);
    }
};
// every minute comes new customer
class customer_generator: public Event{
    void behaviour() override{
        auto a = std::make_shared<take_trolley>();
        a->plan();
        this->plan(current_time + (Exp_Random(1))); 
    }
};

//shop assistant returns to the delicatessen
class delivery_end: public RREvent {
    void behaviour() override {
        for (int i = 0; i < this->resource_handler.size(); i++) {
                if (this->resource_handler[i]->service_line->name == "delicatessen") {
                    this->resource_handler[i]->release();
                }
            }
    };
};
//shop from delicatessen is helping with delivery
class delivery_working: public RREvent {
    void behaviour() override {
        auto d = std::make_shared<delivery_end>();
        d->resource_handler = this->resource_handler;
        d->plan(current_time + Exp_Random(15));
    };
};

//new delivery of goods comes to the delicatessen
class delivery_in_delicatessen:public Event{
    void behaviour() override {
            auto a = delicatessen->seize_or_reserve(1,1);
            auto w = std::make_shared<delivery_working>();
            auto l = [](){
            };
            a->on_fail(30, l);
            a->on_success(w);
    }
};
// every 30 minutes comes new customer
class delivery_generator: public Event{
    void behaviour() override{
        auto a = std::make_shared<delivery_in_delicatessen>();
        a->plan();
        this->plan(current_time + (Norm_Random(30,1))); 
    }
};

int main(int argc, const char * argv[]) {
    auto sim = std::make_shared<Simulator>(0, 480);
    auto a = std::make_shared<customer_generator>();
    a->plan();
    auto d = std::make_shared<delivery_generator>();
    d->plan(current_time + (Norm_Random(30,1)));
    sim->run();
    simulation_info->print_out();
    GeneratedNumberStatistics::shared.print_out();
    return 0;
}
