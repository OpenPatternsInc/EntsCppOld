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
#include <unordered_set>
//Not dependent on the class Tree. Ents are 

using namespace std;

/**
 * An Ent object instance represents and Ent node within a Tree.
 * Ent nodes represent things which satisfy a condition.
 * They could be "all animals", "dogs", "small dogs", "my favorite colors", etc.
 * For two groups to be a parent and child pair, the parent must contain all the
 * things contained in the child category, and also additional things.
 * Each Ent has a unique name within its hierarchy-Tree.
 * Ents hold pointers to the Ent objects it is directly related to.
 * These containers are Parents, Children, Exclusives, and Overlaps.
 * An Ent represents, in an abstract sense, a group of things, or a single thing.
 * Parents are more general groups, and children are more specific groups which
 * are subsets of their parents.
 * The Root class extends the Ent class and is used to represent "everything"
 * in the most general sense. The logic of the Ents Hierarchy makes this possible,
 * and demands that there be only one root per Tree.
 * Each Ent will eventually have a unique identifier (UID) which will be used when
 * writing a Tree to file, allowing each Ent to reference its direct relatives
 * unambiguously. UIDs will also allow the Ents within two separate Trees to
 * represent the same abstract concept and allow for the merging of trees.
 */


/**
 *
 * Ent is the most basic class. It does not require any code from any other file
 * within the library. It does not call any functions of Tree.
 * 
 * This means other classes don't need to use forward declaration.
 * 
 */
class Ent {
    
    
    friend class Tree;
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
    
    //TODO Change the following 4 containers to unordered_sets for efficiency.
    
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
     */
    Ent(string name);
    /**
     * Delete the vectors holding pointers to parents and children.
     * No need to delete those Ent object instances here, that's handled
     * in the Tree class.
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
    static int connectUnchecked(Ent* parent, Ent* child);
    
    /**
     * Connects the two given Ents as parent and child, but doesn't check that it
     * is a legal operation. This function does however do some tree pruning.
     * If the new parent is the descendent of one of the existing parents of the
     * new child, then that existing connection must be removed because it has
     * become redundant.
     * TODO There may be an analogue to this on the child side, but it is late
     * and I am having a hard time proving or disproving it.
     * @param parent
     * @param child
     * @return 
     */
    static int connectUncheckedAndPrune(Ent* parent, Ent* child);
    
    /**
     * Disconnects a parent and child from each other, but doesn't do anything
     * else like check for if that's a good idea...
     */
    static int disconnectUnchecked(Ent* parent, Ent* child);
    
    /**
     * TODO Test for consistency somewhere.
     * @param a
     * @param b
     * @return 
     */
    static int setOverlap(Ent* a, Ent* b);
    
    static int setExclusive(Ent* a, Ent* b);
    
    /**
     * The set of this Ent's ancestors can't overlap at all with the set of the
     * given Ent's descendents.
     * @return  Returns any Ents which actually do overlap, because something
     *          must be done about them. Empty set if there are no problems.
     */
    unordered_set<Ent*> canBeParentOf(Ent* entPtr);
    
    /**
     * Generate a set of all this Ent's ancestors recursively and return that set.
     * TODO Optimize this so it's not so bad lol.
     * @param depth     Make sure we don't get caught in a loop and crash the system.
     * @return 
     */
    unordered_set<Ent*> getAncestors(unsigned short depth = 0);
    
    /**
     * Generate a set of all this Ent's descendents recursively and return that set.
     * TODO Optimize this so it's not so crude lol.
     * @param depth     Make sure we don't get caught in a loop and crash the system.
     * @return 
     */
    unordered_set<Ent*> getDescendents(unsigned short depth = 0);
    
    
    unordered_set<Ent*> getSiblings();
    

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
    
    void setUID(unsigned int n) {
        uid = n;
    }

    /**
     * Adds an Ent as a parent of this one, but doesn't check anything.
     * @param parentPtr
     */
    void addParentUnchecked(Ent* parentPtr);

    vector<Ent*> getParents() {
        return parents;
    }

    /**
     * Adds an Ent as a child of this one, but doesn't check anything.
     * @param childPtr
     */
    void addChildUnchecked(Ent* childPtr) {
        children.push_back(childPtr);
    }

    vector<Ent*> getChildren() {
        return children;
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

