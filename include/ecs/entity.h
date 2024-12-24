//
// Created by Furkan ARICAN on 24.12.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include "unordered_map"
#include "string"
#include "memory"

class Component {
public:
    virtual ~Component() = default;
};

class Entity {
private:
    unsigned int id;
    //todo: change here to something clever not ordered
    static unsigned int idCounter;
    std::unordered_map<std::string, std::shared_ptr<Component>> components;

public:
    //todo: change idCounter here
    Entity() : id(idCounter++) {}
    unsigned int getId() const { return id; }

    //addComponent
    template<typename T, typename... Args>
    void addComponent(Args&&... args) {
        components[std::string(typeid(T).name())] = std::make_shared<T>(std::forward<Args>(args)...);
    }

    //getComponent
    template<typename T>
    T* getComponent() {
        auto it = components.find(std::string(typeid(T).name()));
        if (it != components.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    //getComponent
    template<typename T>
    const T* getComponent() const {
        auto it = components.find(std::string(typeid(T).name()));
        if (it != components.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    //todo: removeComponent?
};

//her entitynin unique id alabilmesi icin statik disarida tanimliyoruz
static unsigned int idCounter;


#endif //ENTITY_H
