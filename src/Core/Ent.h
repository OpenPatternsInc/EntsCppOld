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
 * within the library.
 * 
 * This means other classes can  
 * 
 * 
 * 
 * 
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
    static int connectUnchecked(Ent* parent, Ent* child) {
        //Add references to the vectors holding the lists.
        parent->addChildUnchecked(child);
        child->addParentUnchecked(parent);
        
        cout << parent->getName() << " is now a parent of " << child->getName()
                << ".\n";

        return 0;
    }
    
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
    static int connectUncheckedAndPrune(Ent* parent, Ent* child) {
        
        //Get the new parent's ancestors.
        unordered_set<Ent*>* pAncestors = parent->getAncestors();
        //Get a pointer to the child's parents.
        vector<Ent*>* existingParents = child->getParents();
        //Check if any of child's direct parents are in this set already.
        for (Ent* existingParent : *existingParents) {
            //Insert it into the set. second indicates if it was added or not.
            if (!pAncestors->insert(existingParent).second) {
                //It wasn't added, so it must have already been there.
                disconnectUnchecked(existingParent, child);
                //TODO Should we break here?
            }
        }
        //Free the set!
        delete pAncestors;
        
        //Now actually connect them up!
        connectUnchecked(parent, child);
        
        //TODO Implement an analogous pruning algorithm for the child's descendents?
        
        return 0;
    }
    
    /**
     * Disconnects a parent and child from each other, but doesn't do anything
     * else like check for if that's a good idea...
     */
    static int disconnectUnchecked(Ent* parent, Ent* child) {
        //Get the parent's children.
        vector<Ent*>* children = parent->getChildren();
        //Find child in the vector and remove it.
        for (vector<Ent*>::iterator it = children->begin(); it != children->end(); it++) {
            if (*it == child) {
                children->erase(it);
                //There should be only one, so break early.
                break;
            }
        }
        //Now get the child's parents.
        vector<Ent*>* parents = child->getParents();
        //Find parent in the vector and remove it.
        for (vector<Ent*>::iterator it = parents->begin(); it != parents->end(); it++) {
            if (*it == parent) {
                parents->erase(it);
                //There should be only one, so break early.
                break;
            }
        }
        //No need to free the vectors, they are owned by the Ents themselves.
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
     * The set of this Ent's ancestors can't overlap at all with the set of the
     * given Ent's descendents.
     * @return  Returns any Ents which actually do overlap, because something
     *          must be done about them. Empty set if there are no problems.
     */
    unordered_set<Ent*>* canBeParentOf(Ent* entPtr) {
        //Create an empty unordered_set. Add any overlaps to it as we go.
        unordered_set<Ent*>* overlap = new unordered_set<Ent*>;
        //Make sure they aren't the same Ent. Do so by comparing unique names for now.
        if (name == entPtr->getName()) {
            //This shouldn't happen... well... return a set with just this Ent...
            overlap->insert(this);
            return overlap;
        }
        //Get this Ent's ancestors.
        unordered_set<Ent*>* setA = getAncestors();
        //Add this Ent to the list, it counts.
        setA->insert(this);
        //Get the given Ent's descendents.
        unordered_set<Ent*>* setB = entPtr->getDescendents();
        //Add the supplied Ent to the list as well.
        setB->insert(entPtr);
        //Find the smaller of the two sets. Ancestors should be smaller on average?
        if (setA->size() > setB->size()) {
            //temp will free itself automatically at the end of the if statement.
            unordered_set<Ent*>* temp = setA;
            setA = setB;
            setB = temp;
        }
        //Now setA is smaller, or they are equal, so, insert it into setB.
        //If the size of setB doesn't change after an Ent pointer is added,
        //then that Ent pointer was already there, and so is a overlap.
        for (Ent* ent : *setA) {
            //Try to insert this ent into setB. If it doesn't work, we found overlap.
            if (!setB->insert(ent).second)
                overlap->insert(ent);
        }
        //Return what we've found. If the set is empty, then it can be the parent. 
        return overlap;
    }
    
    /**
     * Generate a set of all this Ent's ancestors recursively and return that set.
     * TODO Optimize this so it's not so bad lol.
     * @param depth     Make sure we don't get caught in a loop and crash the system.
     * @return 
     */
    unordered_set<Ent*>* getAncestors(unsigned short depth = 0) {
        //List for this iteration of the recursion.
        unordered_set<Ent*>* localList = new unordered_set<Ent*>;
        //Have to draw the line somewhere. If we're too far down, return and empty set.
        if (depth > 50) return localList;
        //If there are no parents, the recursion will just stop.
        for (Ent* parent : parents) {
            localList->insert(parent);
            //get the parents of the parent
            unordered_set<Ent*> *grandparents = parent->getAncestors(depth + 1);
            //add them to this list
            for (auto g : *grandparents)
                localList->insert(g);
            //Now release the memory.
            delete grandparents;
        }
        //now return the localList for this iteration of the recursion.
        return localList;
    }
    
    /**
     * Generate a set of all this Ent's descendents recursively and return that set.
     * TODO Optimize this so it's not so crude lol.
     * @param depth     Make sure we don't get caught in a loop and crash the system.
     * @return 
     */
    unordered_set<Ent*>* getDescendents(unsigned short depth = 0) {
        //List for this iteration of the recursion.
        unordered_set<Ent*>* localList = new unordered_set<Ent*>;
        //Make sure we don't blow up the universe. If we're too far in, just stop.
        if (depth > 50) return localList;
        //If there are no parents, the recursion will just stop.
        for (Ent* child : children) {
            localList->insert(child);
            //get the parents of the parent
            unordered_set<Ent*> *grandparents = child->getDescendents(depth + 1);
            //add them to this list
            for (auto g : *grandparents)
                localList->insert(g);
            //Now release the memory.
            delete grandparents;
        }
        //now return the localList for this iteration of the recursion.
        return localList;
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
    
    void setUID(unsigned int n) {
        uid = n;
    }

    /**
     * Adds an Ent as a parent of this one, but doesn't check anything.
     * @param parentPtr
     */
    void addParentUnchecked(Ent* parentPtr) {
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
    void addChildUnchecked(Ent* childPtr) {
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

