#ifndef SANDBOX_FACTORY_OBJECT_FACTORY_H_
#define SANDBOX_FACTORY_OBJECT_FACTORY_H_

#include <vector>

namespace sandbox {

template <typename BASE>
class ObjectFactory {
public:
    virtual ~ObjectFactory() {}
    virtual BASE* create(const std::string& typeName) = 0;
};

template <typename T, typename BASE>
class TypedObjectFactory : public ObjectFactory<BASE> {
public:
    TypedObjectFactory(const std::string& typeName) : typeName(typeName) {}
    virtual ~TypedObjectFactory() {}
    BASE* create(const std::string& typeName) { 
        if (typeName == this->typeName) {
            return new T();
        }
        else {
            return NULL;
        } 
    }
private:
    std::string typeName;
};

template <typename T, typename BASE, typename PARAM>
class TypedObjectFactoryWithParam : public ObjectFactory<BASE> {
public:
    TypedObjectFactoryWithParam(const std::string& typeName, PARAM p) : typeName(typeName), p(p) {}
    virtual ~TypedObjectFactoryWithParam() {}
    BASE* create(const std::string& typeName) { 
        if (typeName == this->typeName) {
            return new T(p);
        }
        else {
            return NULL;
        } 
    }
private:
    std::string typeName;
    PARAM p;
};

template <typename BASE>
class CompositeObjectFactory : public ObjectFactory<BASE> {
public:
    virtual ~CompositeObjectFactory() {}

    template <typename T>
    void addType(const std::string& typeName) { addFactory(new TypedObjectFactory<T, BASE>(typeName)); }
    template <typename T, typename PARAM>
    void addTypeWithParam(const std::string& typeName, PARAM param) { addFactory(new TypedObjectFactoryWithParam<T, BASE, PARAM>(typeName, param)); }
    void addFactory(ObjectFactory<BASE>* factory) {
        factories.push_back(factory);
    }
    virtual BASE* create(const std::string& typeName) {
        for (int i = 0; i < factories.size(); i++) {
            BASE* item = factories[i]->create(typeName);
            if (item) {
                return item;
            }
        }

        return NULL;
    }

private:
    std::vector< ObjectFactory<BASE>* > factories;
};

}

#endif