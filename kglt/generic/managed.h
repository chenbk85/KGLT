#ifndef MANAGED_H
#define MANAGED_H

#include <stdexcept>
#include <tr1/memory>

class InstanceInitializationError :
    public std::runtime_error {

public:
    InstanceInitializationError():
        std::runtime_error("Couldn't initialize the instance") {}
};

template<typename T>
class Managed {
public:
    typedef std::shared_ptr<T> ptr;
    typedef std::tr1::weak_ptr<T> wptr;

    template<typename... Args>
    static typename Managed<T>::ptr create(Args&&... args) {
        typename Managed<T>::ptr instance = std::make_shared<T>(std::forward<Args>(args)...);
        if(!instance->init()) {
            throw InstanceInitializationError();
        }
        return instance;
    }

    static typename Managed<T>::ptr create() {
        typename Managed<T>::ptr instance = typename Managed<T>::ptr(new T());
        if(!instance->init()) {
            throw InstanceInitializationError();
        }
        return instance;
    }

    virtual ~Managed() {}
    virtual bool init() { return true; }

protected:
    template<typename...Args>
    Managed(Args&&... args) {}

};

#endif // MANAGED_H
