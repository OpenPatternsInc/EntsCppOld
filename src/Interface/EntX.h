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

#ifndef ENTX_H
#define ENTX_H

#include <vector>
#include <unordered_set>
#include "../Core/Ent.h"

class EntX {
    
    friend class TreeInstance;
    friend class EntsInterface;
    
    /*
     * Pointer to the Ent object this represents.
     */
    Ent* ent;
    /*
     * Private constructor only accessible to the friend class TreeInstance.
     * Takes as an argument the Ent object which it will point to.
     */
    EntX(Ent*);
    /*
     * Creates a vector of EntInstances from a vector of Ents.
     */
    vector<EntX> wrap(vector<Ent*>);
    
    vector<EntX> wrap(unordered_set<Ent*>);
    
public:
    
    /*
     * No-arg constructor of empty wrapper.
     * Can be used like a nullptr to indicate no Ent.
     * Is public because it can't screw anything up.
     * Allows us to create an Array of them perhaps
     * within subclasses of EntsInterface
     */
    EntX();
    /*
     * Copy constructor available to EntsInterface subclasses to make copies of
     * an EntX and pass it via value between functions. Because only its value
     * is of importance, it can be declared on the stack and its memory freed
     * up automatically when it leaves scope!
     */
    EntX(const EntX &entX);
    /*
     * Anyone can destroy an EntX. We need subclasses of EntsInterface to be
     * able to destroy it when it leaves scope.
     * 
     * The pointer does not need to be destroyed itself. It is a stack variable,
     * though what it points to is not.
     */
    ~EntX();
    
    /**************************************************************************
     * Public functions for use in subclasses of EntsInterface.
     * 
     * EntX acts as a way to force subclasses to retrieve information by value,
     * and so that information should be constant. There is no need to change
     * it, only read.
     * 
     * isEmpty() 
     **************************************************************************/
    
    const bool isEmpty();
    
    const string getName() {
        return ent->getName();
    }
    
    
    
    const vector<EntX> getParents() {
        return wrap(ent->getParents());
    }
    
    const vector<EntX> getChildren() {
        return wrap(ent->getChildren());
    }
    
    const vector<EntX> getAncestors() {
        return wrap(ent->getAncestors());
    }
    
    const vector<EntX> getDescendants() {
        return wrap(ent->getDescendents());
    }
    
    const vector<EntX> getSiblings() {
        return wrap(ent->getSiblings());
    }
    
    /**
     * This tests to see if the Ent held within this EntX is the same as that
     * held in another.
     * Because a function within EntX has access to the private data members
     * of other EntX instances, because a class is essentially friends with
     * itself, we can use that here to access otherEntX.ent directly, and
     * compare the two pointers.
     * TODO Should we make a special test for if the same two EntXs are
     * compared? That may indicate a problem in the program.
     * TODO If the EntX holds a pointer to nullptr, that's a problem in the
     * program's protocol. Should we test or assert?
     * @param otherEntX     A second EntX with which to compare two.
     * @return              Returns true only if both EntX point to the same
     *                      Ent.
     */
    const bool equals(EntX otherEntX);
    
    
};


#endif /* ENTX_H */

