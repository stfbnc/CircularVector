#include <iostream>
#include <memory>
#include "circular_vector.hpp"

class A
{
public:
    A() {}
    ~A() { std::cout << "A destroyed" << std::endl; }
    std::string print() { return "AA"; }
};

int main()
{
    size_t sz = 11;
    CircularVector<int> vec = CircularVector<int>(sz);

    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
    vec.push_back(7);
    vec.push_back(8);
    vec.push_back(9);
    vec.push_back(10);
    vec.push_back(11);
    vec.push_back(12);

    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << "vec[" << i << "] = " << vec.at(i) << std::endl;
    }

    std::vector<std::shared_ptr<A>> a;
    a.reserve(4);
    std::cout << 1 << std::endl;
    //A *tmp = new A();
    std::shared_ptr<A> tmp = std::shared_ptr<A>(new A());
    a.push_back(tmp);
    std::cout << &tmp << std::endl;
    std::cout << &a.at(0) << std::endl;
    std::cout << &a.back() << std::endl;
    //delete tmp;
    tmp->~A();
    std::cout << 2 << std::endl;
    a.push_back(std::shared_ptr<A>(new A()));
    std::cout << 3 << std::endl;
    a.push_back(std::shared_ptr<A>(new A()));
    std::cout << 4 << std::endl;
    a.push_back(std::shared_ptr<A>(new A()));
    std::cout << 5 << std::endl;
    for(int i = 0; i < a.size(); i++)
    {
        std::cout << a.at(i)->print() << " " << i << std::endl;
    }
    //delete a.at(2);
    a.erase(a.begin() + 2);
    //a.push_back(6);

    /*std::vector<A *> b = a;

    for(int i = 0; i < b.size(); i++)
    {
        std::cout << b.at(i)->print() << " " << i << std::endl;
    }

    a.clear();

    std::cout << "End" << std::endl;*/

    /*CircularVector<int> vec_2 = CircularVector<int>(sz);
    vec_2.push_back(9);
    vec_2.push_back(10);
    vec_2.push_back(11);
    vec_2.push_back(12);
    vec_2.push_back(13);
    vec_2.push_back(14);
    vec_2.push_back(15);
    vec_2.push_back(16);
    vec_2.push_back(17);
    vec_2.push_back(18);
    vec_2.push_back(19);

    for(int i = 0; i < vec_2.size(); i++)
    {
        std::cout << "vec[" << i << "] = " << vec_2.at(i) << std::endl;
    }

    std::cout << (vec != vec_2) << std::endl;
    std::cout << (vec == vec_2) << std::endl;*/

    /*CircularVector<int> vec_3(sz);
    vec_3.push_back(1);
    vec_3.push_back(2);
    vec_3.push_back(3);
    //vec_3 = vec;
    vec.clear();
    vec = vec_3;
    //std::cout << (vec != vec_3) << std::endl;
    std::cout << (vec == vec_3) << std::endl;

    //vec_3.at(0) = 1000;
    for(int i = 0; i < vec_3.size(); i++)
    {
        std::cout << "vec_3[" << i << "] = " << vec_3.at(i) << std::endl;
    }

    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << "vec[" << i << "] = " << vec.at(i) << std::endl;
    }
    //std::cout << (vec != vec_3) << std::endl;
    //std::cout << (vec == vec_3) << std::endl;*/
}
