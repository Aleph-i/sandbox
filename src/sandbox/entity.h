#ifndef SANDBOX_ENTITY_H_
#define SANDBOX_ENTITY_H_

#include <vector>
#include <string>
#include "component.h"

namespace sandbox {

class TaskContext {
public:
    virtual ~TaskContext() {}
    virtual void push() {}
    virtual void pop() {}
};

class Task {
public:
    virtual ~Task() {}
    virtual void run(Entity& entity, TaskContext* context) = 0;
    virtual TaskContext* createContext() { return NULL; }
};

class RecursiveTask : public Task {
public:
    virtual ~RecursiveTask() {}
    virtual void run(Entity& entity, TaskContext* context);
    virtual void runEntity(Entity& entity, TaskContext* context) = 0;
};

class Entity {
public:
    Entity(const std::string& name) : parent(nullptr), name(name) {}
    virtual ~Entity();

    Component& addComponent(Component* component);
    void deleteComponent(Component* component);
    const std::vector<Component*>& getComponents() const { return components; }

    Entity& addChild(Entity* child);
    void deleteChild(Entity* child);
    const std::vector<Entity*>& getChildren() const { return children; }

    void runTask(Task& task);
    void runTask(Task& task, TaskContext* context);

    Entity* getParent() { return parent; }
    const std::string& getName() { return name; }

private:
    void removeComponent(Component* component);
    void removeChild(Entity* child);
    void setParent(Entity* parent) { this->parent = parent; }

    std::vector<Component*> components;
    std::vector<Entity*> children;
    Entity* parent;
    std::string name;
};

}

#endif