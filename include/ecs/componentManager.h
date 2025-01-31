//
// Created by Furkan ARICAN on 18.01.2025.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ecs/enum.h"
#include <vector>
#include <unordered_map>

using Entity = unsigned int;
using ComponentMask = std::bitset<32>;

class ComponentManager {

    private:
        std::vector<char> componentData; //ganzen comp data
        //std::unordered_map<ComponentType, size_t> componentSizeMap; //comptype, compsize
        std::unordered_map<unsigned int, std::unordered_map<int, size_t>> entityOffsets; //entityid, {entityStartOffset, entityCompTotalSize}
        //std::unordered_map<unsigned int, unsigned int> entityBitmasks;

        std::vector<ComponentMask> entityMasks;

        std::vector<PositionComponent> positionComponents;
        std::vector<Entity> freePositionIndices;

        std::vector<SizeComponent> sizeComponents;
        std::vector<Entity> freeSizeIndices;

        std::vector<ColorComponent> colorComponents;
        std::vector<Entity> freeColorIndices;

        Entity nextEntityId = 0;


        size_t totalSize = 0;
        size_t positionTotalSize = 0;
        size_t sizeTotalSize = 0;
        size_t colorTotalSize = 0;

    public:

        size_t entityCount = 0;
        std::vector<unsigned int> entityVerticeOffsets;
        bool entitiesUpdated = false;

        std::vector<Entity> freeIndices;
        //entitiy new region

        Entity createEntity() {
            if (!freeIndices.empty()) {
                Entity id = freeIndices.back();
                freeIndices.pop_back();
                for (Entity i = id + 1; i < entityVerticeOffsets.size(); ++i) {
                    entityVerticeOffsets[i] += 4;
                }
                entitiesUpdated = true;
                return id;
            } else {
                Entity id = entityMasks.size();
                entityVerticeOffsets.push_back(entityMasks.size() * 4);
                entityMasks.emplace_back();
                entitiesUpdated = true;
                return id;
            }

            // if (!freePositionIndices.empty()) {
            //     Entity entityId = freePositionIndices.back();
            //     freePositionIndices.pop_back();
            //
            //     ComponentMask& mask = entityMasks[entityId];
            //     mask.reset();
            //
            //     std::cout << "ENTITY ADDED USED FREE INDEXES ID: " << entityId << std::endl;
            //     entityVerticeOffsets[entityId] = positionTotalSize;
            //     return entityId;
            // }
            // std::cout << "ENTITY ADDED NEW ID: " << entityCount + 1 << std::endl;
            // entityMasks.emplace_back();
            // entityVerticeOffsets.emplace_back(entityCount * 4);
            // return entityCount++;

            if (entityMasks.size() == entityCount) {
                entityMasks.emplace_back();
            }
            //return entityCount++;
            ++entityCount;
            return entityCount - 1;

            Entity entityId = nextEntityId++;
            entityMasks[entityId] = ComponentMask(0);
            return entityId;
        }

        void addComponent(Entity entityId, const PositionComponent& component) {
            if (freePositionIndices.empty()) {
                positionComponents.emplace_back(component);
                entityMasks[entityId].set(Position);
            } else {
                Entity index = freePositionIndices.back();
                freePositionIndices.pop_back();
                positionComponents[index] = component;
                entityMasks[entityId].set(Position);
            }
            // if (positionComponents.size() <= entityId) {
            //     positionComponents.resize(entityId + 1);
            // }
            // positionComponents[entityId] = component;
            // entityMasks[entityId].set(Position);
        }

        void addComponent(Entity entityId, const SizeComponent& component) {
            if (freeSizeIndices.empty()) {
                sizeComponents.emplace_back(component);
                entityMasks[entityId].set(Size);
            } else {
                Entity index = freeSizeIndices.back();
                freeSizeIndices.pop_back();
                sizeComponents[index] = component;
                entityMasks[entityId].set(Size);
            }
            // if (sizeComponents.size() <= entityId) {
            //     sizeComponents.resize(entityId + 1);
            // }
            // sizeComponents[entityId] = component;
            // entityMasks[entityId].set(Size);

        }

        void addComponent(Entity entityId, const ColorComponent& component) {
            if (freeColorIndices.empty()) {
                colorComponents.emplace_back(component);
                entityMasks[entityId].set(Color);
            } else {
                Entity index = freeColorIndices.back();
                freeColorIndices.pop_back();
                colorComponents[index] = {component};
                entityMasks[entityId].set(Color);
            }
            // if (colorComponents.size() <= entityId) {
            //     colorComponents.resize(entityId + 1);
            // }
            // colorComponents[entityId] = component;
            // entityMasks[entityId].set(Color);
        }

        PositionComponent* getPositionComponent(Entity entityId) {
                return &positionComponents[entityId];
            if (entityMasks[entityId].test(Position)) {
            }
            return nullptr;
        }

        SizeComponent* getSizeComponent(Entity entityId) {
                return &sizeComponents[entityId];
            if (entityMasks[entityId].test(Size)) {
            }
            return nullptr;
        }

        ColorComponent* getColorComponent(Entity entityId) {
                return &colorComponents[entityId];
            if (entityMasks[entityId].test(Color)) {
            }
            return nullptr;
        }

        //remove
        void removeEntity(Entity entityId) {
            if (entityId >= entityMasks.size()) return;

            // ComponentMask'ı sıfırla

            ComponentMask& mask = entityMasks[entityId];
            if (!mask.any()) return;
            if (mask.test(Position)) {
                freePositionIndices.push_back(entityId);
                // mask.reset(Position);
            }
            if (mask.test(Size)) {
                freeSizeIndices.push_back(entityId);
                // mask.reset(Size);
            }
            if (mask.test(Color)) {
                freeColorIndices.push_back(entityId);
                // mask.reset(Color);
            }
            entityMasks[entityId].reset();


            // Silinen entity'nin offset'ini freeIndices'e eklemek yerine
            // silinen entity'den sonraki tüm offset'leri 4 eksilt
            for (Entity i = entityId + 1; i < entityVerticeOffsets.size(); ++i) {
                entityVerticeOffsets[i] -= 4;
            }

            // Silinen entity'nin ID'sini freeIndices'e ekle
            freeIndices.push_back(entityId);
            entitiesUpdated = true;
            // if (entityId >= entityCount) return;
            //
            // // Bileşen maskesini sıfırla
            // ComponentMask& mask = entityMasks[entityId];
            // if (!mask.any()) return;
            // if (mask.test(Position)) {
            //     freePositionIndices.push_back(entityId);
            //     mask.reset(Position);
            // }
            // if (mask.test(Size)) {
            //     freeSizeIndices.push_back(entityId);
            //     mask.reset(Size);
            // }
            // if (mask.test(Color)) {
            //     freeColorIndices.push_back(entityId);
            //     mask.reset(Color);
            // }
            //
            //
            // while (entityCount > 0 && !entityMasks[entityCount - 1].any()) {
            //     entityCount--;
            // }
            //
            // std::cout << "ENTITY REMOVED ID: " << entityId << std::endl;
            //
            // for (Entity i = entityId + 1; i < entityCount; ++i) {
            //     entityVerticeOffsets[i] -= 4;
            // }
        }

        void removePositionComponent(Entity entityId) {
            if (entityMasks[entityId].test(Position)) {
                freePositionIndices.push_back(entityId);
                entityMasks[entityId].reset(Position);
            }
        }

        void removeSizeComponent(Entity entityId) {
            if (entityMasks[entityId].test(Size)) {
                freeSizeIndices.push_back(entityId);
                entityMasks[entityId].reset(Size);
            }
        }

        void removeColorComponent(Entity entityId) {
            if (entityMasks[entityId].test(Color)) {
                freeColorIndices.push_back(entityId);
                entityMasks[entityId].reset(Color);
            }
        }

        std::vector<ComponentMask>& getEntityMasks() { return entityMasks; }
        //

        // void addComponent(unsigned int entityId, const PositionComponent& position) {
        //     positionComponents.emplace_back(position);
        //     //todo: entityId match
        // }
        //
        // void addComponent(unsigned int entityId, const SizeComponent& size) {
        //     sizeComponents.emplace_back(size);
        //     //todo: entityId match
        // }
        //
        // void addComponent(unsigned int entityId, const ColorComponent& color) {
        //     colorComponents.emplace_back(color);
        //     //todo: entityId match
        // }

        // Component ekleme
        // template <typename T>
        // void addComponent(unsigned int entityId, int componentType, const T& component) {
        //     size_t componentSize = sizeof(T);
        //     size_t alignment = alignof(T);
        //     size_t defTotalSize = 0;
        //     std::vector<T>* defComponentData = nullptr;
        //
        //     if (componentType == Position) {
        //         defTotalSize = positionTotalSize;
        //         //defComponentData = &positionComponents;
        //     }
        //     else if (componentType == Size) {
        //         defTotalSize = sizeTotalSize;
        //         // defComponentData = sizeComponents;
        //     }
        //     else if (componentType == Color) {
        //         defTotalSize = colorTotalSize;
        //         // defComponentData = colorComponents;
        //     }
        //
        //     // Yeni component'in yerini hizalamaya uygun şekilde ayarla
        //     size_t offset = (defTotalSize + alignment - 1) & ~(alignment - 1);
        //     defTotalSize = offset + componentSize;
        //
        //     // Hafızayı genişlet ve yeni component'i ekle
        //     if (defComponentData->size() < defTotalSize) {
        //         defComponentData->resize(std::max(defTotalSize, defComponentData->size())); // 1 KB bloklar halinde artır
        //     }
        //
        //     std::memcpy(&defComponentData[offset], &component, componentSize);
        //
        //     // Entity'nin component offset'ini kaydet
        //     entityOffsets[entityId][componentType] = offset;
        // }

        template <typename T>
        T* getCompData(int componentType) {
            if (componentType == Position) {return &positionComponents;}
            else if (componentType == Size) {return &sizeComponents;}
            else if (componentType == Color) {return &colorComponents;}
        }

        // Component'e erişim
        template <typename T>
        T* getComponent(unsigned int entityId, int componentType) {
            // if (!hasComponent(entityId, componentType)) {
            //     return nullptr; // Component yok
            // }

            size_t offset = entityOffsets[entityId][componentType];
            return reinterpret_cast<T*>(&componentData[offset]);
        }

        // Component kaldırma
        void removeComponent(unsigned int entityId, int componentType) {
            if (!hasComponent(entityId, componentType)) {
                return;
            }

            size_t offset = entityOffsets[entityId][componentType];
            // TODO: Fragmentasyon yönetimi (şu anda bu kısmı es geçiyoruz)
            entityOffsets[entityId].erase(componentType);

            if (entityOffsets[entityId].empty()) {
                entityOffsets.erase(entityId);
            }

            // Bitmask'ten çıkar
            //entityBitmasks[entityId] &= ~(1 << componentType);
        }

        // Bitmask kullanarak component kontrolü
        bool hasComponent(unsigned int entityId, int componentType) const {
            return entityOffsets.find(entityId) != entityOffsets.end() &&
                   entityOffsets.at(entityId).find(componentType) != entityOffsets.at(entityId).end();
        }
};

#endif //COMPONENTMANAGER_H
