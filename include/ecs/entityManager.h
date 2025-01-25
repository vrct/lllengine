//
// Created by Furkan ARICAN on 18.01.2025.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include <bitset>
#include "ecs/componentManager.h"

class EntityManager {

    private:

        // Entity'lerin bitmask'lerini saklayan harita
        std::unordered_map<unsigned int, unsigned int> entityBitmasks;

        // ComponentManager'a referans (EntityManager, ComponentManager ile iletişim kurar)

        // Benzersiz ID üreteci
        unsigned int nextEntityId = 1;

    public:
        // Constructor
        EntityManager(ComponentManager& cm) : componentManager(cm) {}
        ComponentManager& componentManager;

        template <typename T>
        T* getCompData(int componentType) {
            return componentManager.getCompData<T>(componentType);
        }

        // Entity listesi
        std::vector<unsigned int> entities;

        // Yeni bir entity oluşturma
        unsigned int createEntity() {
            unsigned int entityId = nextEntityId++;
            entities.push_back(entityId);
            entityBitmasks[entityId] = 0; // Başlangıçta component yok
            return entityId;
        }

        // Entity'yi kaldırma
        void removeEntity(unsigned int entityId) {
            // Entity bitmask'ini kaldır
            entityBitmasks.erase(entityId);

            // ComponentManager'daki tüm component'leri kaldır
            for (int i = 0; i < 32; ++i) { // Maksimum 32 component varsayımı
                if (entityBitmasks[entityId] & (1 << i)) {
                    componentManager.removeComponent(entityId, i);
                }
            }

            // Entity'yi listeden kaldır
            entities.erase(std::remove(entities.begin(), entities.end(), entityId), entities.end());
        }

        // Entity'ye component ekleme
        template <typename T>
        void addComponent(unsigned int entityId, int componentType, const T& component) {
            // ComponentManager'a component ekle
            componentManager.addComponent(entityId, component);
            // componentManager.addComponent(entityId, componentType, component);

            // Bitmask güncelle
            entityBitmasks[entityId] |= (1 << componentType);
        }

        // Entity'den component kaldırma
        void removeComponent(unsigned int entityId, int componentType) {
            if (entityBitmasks[entityId] & (1 << componentType)) {
                componentManager.removeComponent(entityId, componentType);

                // Bitmask'ten çıkar
                entityBitmasks[entityId] &= ~(1 << componentType);
            }
        }

        // Entity'nin bir component'e sahip olup olmadığını kontrol etme
        bool hasComponent(unsigned int entityId, int componentType) const {
            return entityBitmasks.at(entityId) & (1 << componentType);
        }

        // Entity'nin component'ine erişim
        template <typename T>
        T* getComponent(unsigned int entityId, int componentType) {
            if (!hasComponent(entityId, componentType)) {
                return nullptr; // Component yoksa null döner
            }

            return componentManager.getComponent<T>(entityId, componentType);
        }

        // Tüm entity'leri ve bitmask'lerini yazdırma (debug için)
        void debugEntities() const {
            for (const auto& entityId : entities) {
                std::cout << "Entity ID: " << entityId
                          << ", Components: " << std::bitset<32>(entityBitmasks.at(entityId)) << std::endl;
            }
        }
};

#endif //ENTITYMANAGER_H
