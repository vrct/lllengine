//
// Created by Furkan ARICAN on 18.01.2025.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "ecs/enum.h"
#include <vector>
#include <unordered_map>

class ComponentManager {
    private:
        std::vector<char> componentData; //ganzen comp data
        //std::unordered_map<ComponentType, size_t> componentSizeMap; //comptype, compsize
        std::unordered_map<unsigned int, std::unordered_map<int, size_t>> entityOffsets; //entityid, {entityStartOffset, entityCompTotalSize}
        //std::unordered_map<unsigned int, unsigned int> entityBitmasks;


        size_t totalSize = 0;
        size_t positionTotalSize = 0;
        size_t sizeTotalSize = 0;
        size_t colorTotalSize = 0;

    public:
        std::vector<PositionComponent> positionComponents;
        std::vector<SizeComponent> sizeComponents;
        std::vector<ColorComponent> colorComponents;

        ComponentManager(){}

        void addComponent(unsigned int entityId, const PositionComponent& position) {
            positionComponents.emplace_back(position);
            //todo: entityId match
        }

        void addComponent(unsigned int entityId, const SizeComponent& size) {
            sizeComponents.emplace_back(size);
            //todo: entityId match
        }

        void addComponent(unsigned int entityId, const ColorComponent& color) {
            colorComponents.emplace_back(color);
            //todo: entityId match
        }

        // Component ekleme
        template <typename T>
        void addComponent(unsigned int entityId, int componentType, const T& component) {
            size_t componentSize = sizeof(T);
            size_t alignment = alignof(T);
            size_t defTotalSize = 0;
            std::vector<T>* defComponentData = nullptr;

            if (componentType == Position) {
                defTotalSize = positionTotalSize;
                //defComponentData = &positionComponents;
            }
            else if (componentType == Size) {
                defTotalSize = sizeTotalSize;
                // defComponentData = sizeComponents;
            }
            else if (componentType == Color) {
                defTotalSize = colorTotalSize;
                // defComponentData = colorComponents;
            }

            // Yeni component'in yerini hizalamaya uygun şekilde ayarla
            size_t offset = (defTotalSize + alignment - 1) & ~(alignment - 1);
            defTotalSize = offset + componentSize;

            // Hafızayı genişlet ve yeni component'i ekle
            if (defComponentData->size() < defTotalSize) {
                defComponentData->resize(std::max(defTotalSize, defComponentData->size())); // 1 KB bloklar halinde artır
            }

            std::memcpy(&defComponentData[offset], &component, componentSize);

            // Entity'nin component offset'ini kaydet
            entityOffsets[entityId][componentType] = offset;
        }

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
