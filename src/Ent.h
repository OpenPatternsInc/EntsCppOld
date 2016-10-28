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

#ifndef ENT_H
#define ENT_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

/**
 * An Ent object instance represents and Ent node within a Hierarchy.
 * Each Ent has a unique name within its hierarchy, and two vector lists
 * which hold pointers to its parents and children.
 * An Ent represents, in an abstract sense, a group of things, or a single thing.
 * Parents are more general, and children are more specific.
 * The Root class extends the Ent class and is used to represent "everything"
 * in the most general sense. The logic of the Ents Hierarchy makes this possible,
 * and demands that there be only one root per Hierarchy.
 * Each Ent will eventually have a unique identifier (UID) which will be used when
 * writing a Hierarchy to file, allowing each Ent to reference its direct relatives
 * unambiguously.
 */
class Ent {
    /**
     * The name of the given Ent. Should ideally be unique.
     */
    string name;
    /**
     * The unique identifier of the Ent. UIDs not implemented yet.
     * Will be useful when writing Hierarchies to file, but not as useful
     * when all Ents are just stored in heap memory like as of now.
     */
    unsigned int uid;
    /**
     * Vector of pointers to the Ent's parents.
     */
    vector<Ent*> parents;
    /**
     * Vector of pointers to the Ent's children.
     */
    vector<Ent*> children;
    /**
     * Vector of pointers to the Ents which are directly exclusive to this one.
     */
    vector<Ent*> exclusives;
    /**
     * Vector of pointers to the Ents which overlap with this one.
     */
    vector<Ent*> overlaps;
    

public:

    /**
     * Initialize an Ent with no properties yet.
     * Probably no need to call this as of now.
     */
    Ent();
    /**
     * Initialize a new Ent object.
     * @param name  The name of this new Ent. We don't check if it is unique here.
     * @param arch  The Hierarchy object to add this Ent to.
     */
    Ent(string name);
    /**
     * Delete the vectors holding pointers to parents and children.
     * No need to delete those Ent object instances here, that's handled
     * in the Hierarchy class.
     */
    ~Ent();

    /**
     * Connect two Ents, one as the parent and one as the child. Does not check
     * for logical consistency yet. For instance, if we have two Ents which are
     * parent and child, we can't make the child as a new parent for the parent.
     * @param parent    Pointer to parent.
     * @param child     Pointer to child.
     * @return          Soon the return variable will indicate success or failure.
     */
    static int connect(Ent* parent, Ent* child) {
        //Add references to the vectors holding the lists.
        parent->addChild(child);
        child->addParent(parent);

        return 0;
    }
    
    /**
     * TODO Test for consistency somewhere.
     * @param a
     * @param b
     * @return 
     */
    static int setOverlap(Ent* a, Ent* b) {
        a->addOverlaps(b);
        b->addOverlaps(a);
        
        return 0;
    }
    
    static int setExclusive(Ent* a, Ent* b) {
        a->addExclusive(b);
        b->addExclusive(a);
        
        return 0;
    }

    /**
     * Prints the name of the Ent to the stdout.
     */
    void printName() {
        cout << "Ent name: \"" << name << "\"\n";
    }

    /**
     * Sets the name of the Ent, without checking its uniqueness.
     */
    void setName(const string newName) {
        name = newName;
    }

    string getName() {
        return name;
    }

    /**
     * Gets the Ent's unique identifier. UIDs not implemented yet.
     * @return 
     */
    unsigned int getUID() {
        return uid;
    }

    /**
     * Adds an Ent as a parent of this one, but doesn't check anything.
     * @param parentPtr
     */
    void addParent(Ent* parentPtr) {
        assert(parentPtr != 0);
        parents.push_back(parentPtr);
    }

    vector<Ent*>* getParents() {
        return &parents;
    }

    /**
     * Adds an Ent as a child of this one, but doesn't check anything.
     * @param childPtr
     */
    void addChild(Ent* childPtr) {
        children.push_back(childPtr);
    }

    vector<Ent*>* getChildren() {
        return &children;
    }
    
    /**
     * Add an Ent to the vector of exclusives to this Ent.
     * @param exPtr
     */
    void addExclusive(Ent* exPtr) {
        exclusives.push_back(exPtr);
    }
    
    vector<Ent*>* getExclusives() {
        return &exclusives;
    }
    
    /**
     * Overlaps
     * @param ovPtr
     */
    void addOverlaps(Ent* ovPtr) {
        overlaps.push_back(ovPtr);
    }
    
    vector<Ent*>* getOverlaps() {
        return &overlaps;
    }


};



#endif /* ENT_H */

