/*
 * This file is part of the Ents Tree Database Project.
 * Copyright (C) 2016 OpenPatterns Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TREE_H
#define TREE_H

#include <vector>
#include <unordered_map>
#include <iterator>
#include <string>
#include "Ent.h"
#include "Root.h"

using namespace std;
/**
 * EntNameMap is an unordered_map which retrieves pointers to Ent instances
 * given the input of their names. Alias is made to make it pretty.
 */
typedef std::unordered_map<string, Ent*> EntNameMap;

/** Used to represent the success of adding a new Ent
 * to the Tree by name.*/
typedef enum {
    UNDEFINED_ERROR,
    SUCCESS,
    NAME_TAKEN
} NewEntStatus;

/**
 * Class holding a hierarchy of Ent objects. Uses an unorganized hashmap to organize
 * all the Ents via their names for easy lookup. Each Ent holds vector lists pointing
 * to their parents or children.
 * Each Tree contains on Root Ent, pointed to by root_.
 * Logical organization is not yet implemented, for instance the preventing of
 * illegal operations which would create an invalid state.
 */
class Tree {
    
    /**
     * The name of the Tree.
     */
    string name;
    /**
     * Ents are allocated on heap memory and deallocated later as needed.
     * References to them are held for now within an unordered_map with the
     * keys being the Ent names and the values being pointers to the Ents.
     */
    EntNameMap entNameMap;
    /**
     * Pointer to the root of the hierarchy. No need to make a setter method
     * because the root never needs to change.
     */
    Root* root;
    
public:

    /**
    * Adds an Ent to entNameMap_ and sets its only parent as parentPtr.
    * If we add an Ent to the Tree, it will always need a parent,
    * unless it's root.
    * Root is added manually.
    * @param entPtr    Pointer to the Ent being added.
    * @param parentPtr Pointer to the parent of the Ent being added.
    */
    void addEntToNameMap(Ent* entPtr, Ent* parentPtr = nullptr);
    /**
     * If the name is not already taken, create a new one and add it to the map.
     * Set the new Ent as root's child for now.
     * @param name  Desired name.
     * @return      Returns and enum value: UNDEFINED_ERROR, SUCCESS, NAME_TAKEN
     */
    NewEntStatus tryToCreateNewEnt(const string name);
    /**
     * Retrieves a pointer to an Ent of the given name, if one exists.
     * @param name  Name being searched for.
     * @return      Returns pointer to Ent if found, 0 if not.
     */
    Ent* getEntPtrByName(const string name);
    
    void setName(string newName) {
        name = newName;
    }

    /**
     * Create a new Tree and add a root Ent to it. Also initialize the NameMap.
     * Because of this explicit 1 arg constructor, there is not a no-arg
     * constructor to use, so we can't make arrays of Trees. May need to change
     * later.
     */
    Tree(string name);

    EntNameMap* getNameMap() {
        return &entNameMap;
    }
    
    const string getName() {
        return name;
    }
    /**
     * What do do when the Tree is removed from memory. Maybe save to file?
     * For now we delete entNameMap and all the Ents it points to.
     */
    ~Tree();
    
    Root* getRoot() {
        return root;
    }
    
    

}; //end class Tree


#endif /* TREE_H */

