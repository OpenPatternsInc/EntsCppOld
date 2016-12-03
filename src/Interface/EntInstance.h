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

/* 
 * Wrapper class for Ent instances. Allows subclasses of EntsInterface to refer to
 * Ents like objects, but without the power to change them directly.
 */

#ifndef ENTINSTANCE_H
#define ENTINSTANCE_H

#include <vector>
#include <unordered_set>
#include "../Core/Ent.h"
#include "../Core/Tree.h"

class EntInstance {
    
    friend class Ent;
    friend class Tree;
    friend class TreeInstance;
    friend class EntsInterface;
    
    /*
     * Pointer to the Ent object this represents.
     */
    Ent* ent;
    /*
     * No-arg constructor of empty wrapper.
     */
    EntInstance();
    /*
     * Private constructor only accessible to the friend class Tree.
     */
    EntInstance(Ent*);
    /*
     * Creates a vector of EntInstances from a vector of Ents.
     */
    vector<EntInstance> wrap(vector<Ent*>*);
    
    vector<EntInstance> wrap(unordered_set<Ent*>*);
    
public:
    
    /*
     * Copy constructor.
     */
    EntInstance(const EntInstance &ent);
    /*
     * Private destructor only accessible to the friend class Tree.
     */
    ~EntInstance();
    
    /**************************************************************************
     * Public functions for use in subclasses of EntsInterface
     **************************************************************************/
    
    const bool isEmpty() {
        return ent == nullptr;
    }
    
    const string getName() {
        return ent->getName();
    }
    
    vector<EntInstance> getParents() {
        return wrap(ent->getParents());
    }
    
    vector<EntInstance> getChildren() {
        return wrap(ent->getChildren());
    }
    
    vector<EntInstance> getAncestors() {
        return wrap(ent->getAncestors());
    }
    
    vector<EntInstance> getDescendants() {
        return wrap(ent->getDescendents());
    }
    
    bool equals(EntInstance otherWrapper) {
        return ent == otherWrapper.ent;
    }
    
    
};


#endif /* ENTINSTANCE_H */

