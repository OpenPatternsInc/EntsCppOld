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

#include "EntsInterface.h"
#include "TreeInstance.h"
#include "Tests.h"

class TreeInstance;

EntsInterface::EntsInterface() {
}

EntsInterface::~EntsInterface() {
    
    //Because this class holds a vector of Tree pointers, we need to release
    //those trees manually. Down the road, we may wish to do something
    //different, allowing the user to pass a tree from one program to another
    //pointers rather than copying the whole thing, but not yet.
    for (Tree* tree : trees) {
        delete tree;
    }
    
}

inline EntX EntsInterface::getEmptyEntInstance() {
    return EntX();
}


const TreeInstance EntsInterface::requestNewTree() {
    //The user must first name the new Tree.
    string message = "Enter a name for the new Tree.";
    //Give the user a few tries.
    for (int n = 0; n < 3; n++) { 
        //First we need a name for the tree. Get one from the subclass.
        string potentialName;
        //Ask the user for text input with the given message as instructions.
        queryUserForText(&potentialName, message);
        //Now we must test if it is a valid name. If it is, the function will
        //return true. If invalid, it will return false and alter failureMessage
        //to describe why the text is invalid.
        if (Tests::isValidTreeName(potentialName, &message)) {
            //Valid name.
            //Make a new Tree with the given name.
            Tree* newTree = new Tree(potentialName);
            //Add it to the list of trees.
            trees.push_back(newTree);
            //Return a copy of the TreeInstance. It just contains a pointer.
            return TreeInstance(newTree);
        }
    } //end of for loop
    //If we get here, the user did not provide a valid name.
    //Return an empty TreeInstance.
    return TreeInstance();
}

const EntX EntsInterface::requestToCreateNewEnt(TreeInstance tree) {
    
    string message = "Enter name of new Ent.";
    for (int num = 0; num < 3; num++) {
        
        string potentialName;
        queryUserForText(&potentialName, message);
        if (Tests::isValidEntName(potentialName, &message)) {
            //Valid name!
            //Is it free?
            if (tree.isEntNameFree(potentialName)) {
                //Hey, it's available!
                //Make the new Ent. On the heap and everything!
                Ent* newEnt = new Ent(potentialName);
                //Add it to the tree.
                tree.addEnt(newEnt);
                //Return a copy of an EntX containing a pointer to the Ent.
                return EntX(newEnt);;
            } else {
                message = "That name is already taken!";
            }
        }
    }
    //If it gets here, then the user used up their chances.
    return EntX();
}


void EntsInterface::requestToRenameTree(TreeInstance tree) {
    
    string instructions = "Enter the Tree's new name.";
    
    for (int num = 0; num < 3; num++) {
        
        string potentialName;
        
        queryUserForText(&potentialName, instructions);
        
        if (Tests::isValidTreeName(potentialName, &instructions)) {
            //valid name
            tree.rename(potentialName);
            //TODO should we hard-code the message within TreeInstance::rename
            //in order to assure that the user is always informed?
            //Inform the user that the name was changed. Gotta respect the user!
            displayMessageToUser("Tree name changed to \"" + potentialName + "\".");
            //ok exit now
            return;
        }
    }
    displayMessageToUser("Tree name was not changed.");
}