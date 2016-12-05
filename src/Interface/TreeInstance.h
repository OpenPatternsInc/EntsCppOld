/*
 * This file is part of the Ents Hierarchy Database Project.
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

/******************************************************************************
 * TreeInstance is a wrapper for the Tree class.
 * It is used by subclasses of EntsInterface to  a pointer to an instance of the Tree class itself,
 * which would allow
 * for unchecked manipulation
 * subclasses of EntsInterface. Information can be retrieved, but not changed.
 * Changes are handled by 
 ******************************************************************************/

#ifndef TREEINSTANCE_H
#define TREEINSTANCE_H

#include "EntX.h"
#include "../Core/Tree.h"
#include "InterfaceExceptions.h"

/**
 * TODO We need to be able to handle the copying of an Ent or group of Ents
 * over to another Tree, within a UserInterface. This means we need to copy that
 * Ent so they both don't have the same pointer. We don't want a UI to have 2
 * Trees open at once and accidentally change an Ent in the other tree.
 * Or do we? Well, we need to be explicit about such things.
 */


class TreeInstance {
    
    friend class EntsInterface;
    
    /**************************************************************************
     * Private Data Members
     **************************************************************************/
    
    /*
     * This is a pointer to the Tree this object represents. Subclasses of
     * EntsInterface can not access it, and so they can't manipulate the
     * original directly.
     */
    Tree* tree;
    
    /**************************************************************************
     * Private functions only available to EntsInterface
     **************************************************************************/
    
    /*
     * Explicit inline function for getting the Tree instance.
     * Only accessible to abstract EntsInterface class.
     * Maybe just access it with the . operator?
     */
    Tree* getTree() {
        return tree;
    }
    
    /**
     * 
     */
    void addEnt(Ent* ent, Ent* parent = nullptr);
    
    void rename(string newName);
    
public:
    
    /*
     * Only let the abstract class EntsInterface access the constructor.
     * 
     * The creation of TreeWrappers will also be handled privately by 
     * EntsInterface in order to encapsulate from subclasses via sanitized
     * functions.
     * 
     * When a TreeX is created from a Tree, as an argument a Tree is given.
     * This Tree is then copied into a Tree newly allocated on the heap,
     * and a pointer to it is saved.
     */
    TreeInstance(Tree* givenTree = nullptr);
    
    
    TreeInstance(const TreeInstance &treeInstance);
    
    /*
     * Also private to EntsInterface because we want EntsInterface to handle
     * destruction via calls to virtual methods of the subclass. For instance,
     * if the user needs to do something before closing. But it may just
     * save the Tree to a new file or something.
     * 
     * Notedly can't be called by subclasses directly, they need to go through
     * protected methods to request it.
     */
    ~TreeInstance();
    
    /**************************************************************************
     * Public functions that subclasses of EntsInterface may call.
     * Functions are sanitized so that they don't screw stuff up.
     **************************************************************************/
    
    /**
     * 
     */
    void addEnt(EntX ent, EntX parent = EntX());
    
    const EntX getRoot();
    
    const EntX getEntByName(const string name);
    
    const bool isEntNameFree(const string name);
    
    const string getName();
    
    const bool isEmpty();
    
};



#endif /* TREEINSTANCE_H */

