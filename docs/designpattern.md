# Design Pattern Description (Design Patterns 30%) 
## Entity Component System

The Entity-Component-System (ECS) design pattern consists of entities, which are 
composed of components, alongside systems that perform on the components. The ECS 
design pattern offers developers lots of flexibility and performance optimisation, 
and works with separation of concern.

But what are entities, components and systems? Entities are unique objects that 
exist in a game scene. Entities then have a list of components, which hold data 
structures for attributes such as position or speed. Systems then process the 
components and update them.

## Pseudocode

```c++
for(auto& entity : allEntities) {
    for(auto& component : entity.components) {
        component->update();
    }
}
```

The above code very simply demonstrates the power of the ECS design pattern. The 
outside for loop is iterating through all of the entities in a scene or system, 
and for each one, runs another for loop that iterates through all components 
attached to that entity. Every component on the entity is then updated, which 
effects the entity itself.

## Advantages

The ECS design pattern has many advantages, such as the vastly lesser complexity 
of code that it offers, along with separating different features into their own 
components, decoupling them from unrelated code. ECS also makes it incredibly 
easy to add to already existing components, and to create entirely new ones, even 
with inheritance.