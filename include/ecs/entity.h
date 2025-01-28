// //
// // Created by Furkan ARICAN on 24.12.2024.
// //
//
// #ifndef ENTITY_H
// #define ENTITY_H
//
// #include <map>
// #include "string"
// #include "ecs/enum.h"
//
//
//
// class Component {
//     private:
//         unsigned int _versionId = 0;
//     public:
//         virtual ~Component() = default;
//
//         template <typename T>
//         void updateValue(T newValue) {
//             static_assert(sizeof(T) == 0, "updateValue must be specialized for each component type.");
//         }
//
//         void incrementVersion() { _versionId++; }
//         unsigned int getVersion() const { return _versionId; }
// };
//
// class Entity {
// private:
//     unsigned int id;
//     //todo: change here to something clever not ordered
//     static unsigned int idCounter;
//     unsigned int compData;
//     mutable unsigned int _cachedVersion = -1;
//     std::map<int, std::shared_ptr<Component>> componentsMap;
//     unsigned int vertexOffset;
//     unsigned int indiceOffset;
//
// public:
//     //todo: change idCounter here
//     Entity() : id(idCounter++) {}
//     unsigned int getId() const { return id; }
//
//     unsigned int getUpdatedVersion() const {
//         if (componentsMap.empty())  return -1;
//         unsigned int result = 0;
//         for (const auto & it : componentsMap) {
//             result += it.second->getVersion();
//         }
//
//         return result;
//     }
//
//     void updateCachedVersion() const {
//         _cachedVersion = getUpdatedVersion();
//     }
//
//     //todo: delete afterwards
//     void makeDirty() const {_cachedVersion = -1;}
//
//     bool isDirty() const {
//         return getUpdatedVersion() != _cachedVersion;
//         // unsigned int currentVersion = getUpdatedVersion();
//         // if (currentVersion != _cachedVersion) {
//         //     _cachedVersion = currentVersion;
//         //     return true;
//         // }
//         //
//         // return false;
//     }
//
//     unsigned int getVertexOffset() const {return vertexOffset;}
//     unsigned int getIndicesOffset() const {return indiceOffset;}
//     void setVertexOffset(unsigned int offset) { vertexOffset = offset; }
//     void setIndicesOffset(unsigned int offset) { indiceOffset = offset; }
//
//     bool hasComponent(const ComponentType c) const {
//         return compData & (1 << c);
//     }
//
//     //addComponent
//     template<typename T, typename... Args>
//     void addComponent(ComponentType type, Args&&... args) {
//         compData |= (1 << type);
//         componentsMap[type] = std::make_shared<T>(std::forward<Args>(args)...);
//         updateCachedVersion();
//     }
//
//     //getComponent
//     template<typename T>
//     T* getComponent(ComponentType type) {
//         if (!hasComponent(type)) return nullptr;
//         auto it = componentsMap.find(type);
//         return static_cast<T*>(it->second.get());
//         //auto it = components.find(std::string(typeid(T).name()));
//         // if (it != components.end()) {
//         //     return static_cast<T*>(it->second.get());
//         // }
//         // return nullptr;
//     }
//
//     //getComponent
//     template<typename T>
//     const T* getComponent(ComponentType type) const {
//         if (!hasComponent(type)) return nullptr;
//         auto it = componentsMap.find(type);
//         return static_cast<T*>(it->second.get());
//     }
//
//     //todo: removeComponent?
// };
//
// //her entitynin unique id alabilmesi icin statik disarida tanimliyoruz
// static unsigned int idCounter;
//
//
// #endif //ENTITY_H
