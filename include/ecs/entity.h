//
// Created by Furkan ARICAN on 24.12.2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <map>

#include "unordered_map"
#include "string"

enum ComponentType {
    None,
    Position = 0,
    Size = 1,
    Color = 2,
    Texture = 3
};

class Component {
    private:
        ComponentType _id = None;
    public:
        virtual ~Component() = default;
        ComponentType get_id() const { return _id; }
};

class Entity {
private:
    unsigned int id;
    //todo: change here to something clever not ordered
    static unsigned int idCounter;
    unsigned int compData;
    std::map<int, std::shared_ptr<Component>> componentsMap;

public:
    //todo: change idCounter here
    Entity() : id(idCounter++) {}
    unsigned int getId() const { return id; }

    bool hasComponent(const ComponentType c) const {
        return compData & (1 << c);
    }

    //addComponent
    template<typename T, typename... Args>
    void addComponent(ComponentType type, Args&&... args) {
        compData |= (1 << type);
        componentsMap[type] = std::make_shared<T>(std::forward<Args>(args)...);
    }

    //getComponent
    template<typename T>
    T* getComponent(ComponentType type) {
        if (!hasComponent(type)) return nullptr;
        auto it = componentsMap.find(type);
        return static_cast<T*>(it->second.get());
        //auto it = components.find(std::string(typeid(T).name()));
        // if (it != components.end()) {
        //     return static_cast<T*>(it->second.get());
        // }
        // return nullptr;
    }

    //getComponent
    template<typename T>
    const T* getComponent(ComponentType type) const {
        if (!hasComponent(type)) return nullptr;
        auto it = componentsMap.find(type);
        return static_cast<T*>(it->second.get());
    }

    //todo: removeComponent?
};

//her entitynin unique id alabilmesi icin statik disarida tanimliyoruz
static unsigned int idCounter;


#endif //ENTITY_H
