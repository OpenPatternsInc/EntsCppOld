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

#include "CLI.h"

//TODO Implement singleton stuff. Only need one of these running at a time.

using namespace std;

CLI::CLI(Tree* treePtr_) {
    setArch(treePtr_);
}

CLI::~CLI() {
}

void CLI::listen() {
    //Initiate the listening sequence with no intention to exit yet.
    exiting_ = false;
    //Declare string to hold future commands here. Maybe just redeclare each time instead?
    string command;
    //Let the user know what Ent will start out as the focus.
    cout << "Focus: " << focusPtr->getName() << endl;
    //Loop to repeatedly input commands.
    do {
        //Use the standard > to indicate we're listening for commands.
        cout << ">";
        //Read from console.
        getline(cin, command);
        parseCommand(command);
    } while (!exiting_);
    //Keep going till we're told to exit with "e" or "exit".

}


void CLI::parseCommand(string str) {
    
    //string to hold the arguments substring if necessary.
    string argument;

    //first handle the 1 character commands
    if (str.size() == 1) {
        if (str == "f") {
            //list the current ent of focus
            cout << "Focus: " << focusPtr->getName() << endl;
        } else if (str == "e") {
            cout << "Exiting..." << endl;
            exiting_ = true;
        } else if (str == "c") {
            listChildren(focusPtr);
        } else if (str == "p") {
            listParents(focusPtr);
        } else if (str == "b") {
            //Do a break point. perhaps useful in debugging.
            //TODO implement as optional via preprocessor hiding to disable in production.
            cout << "breakpoint\n";
        } else if (str == "h") {
            printHelp();
        } else if (str == "a") {
            //Get a pointer to a vector containing any estranged pairs of siblings under focus.
            vector<EstrangedPair*>* pairs = Analyzer::analyzeForEstrangedPairs(focusPtr);
            //Were there any estranged pairs? If so, handle it!
            if (pairs->size() == 0) {
                cout << focusPtr->getName() << " has no estranged children.\n";
                //clean up memory
                delete pairs;
                return;
            } else {
                handleEstrangedPairs(pairs, treePtr->getRoot());
            }
        } //end "a"
        else if (str == "s") {
            //Display siblings of focus
            //If it's root, educate the user a bit
            if (focusPtr == treePtr->getRoot()) {
                cout << "By definition, root can not have any siblings.\n";
                return;
            }
            vector<Ent*>* parents = focusPtr->getParents();
            for (Ent* parent : *parents) {
                cout << "Siblings of " << focusPtr->getName() << " under " << parent->getName() << ":\n";
                vector<Ent*>* children = parent->getChildren();
                if (children->size() > 1) {
                    for (int a = 0; a < children->size(); a++)
                        if (children->at(a) != focusPtr)
                            cout << "\t" << children->at(a)->getName() << endl;
                } else {
                    cout << "\t None" << endl;
                }
            }
        } //end "s"
        else {
            //The single character command was not recognized.
            cout << "Unknown single-character command.\n";
        }
    } else {
        //Command has multiple characters.
        //Use isCommand to check for commands and if found set argument substring.
        
        //User just wants to exit. No arguments needed.
        if (str == "exit") {
            cout << "Exiting..." << endl;
            exiting_ = true;
        } else if (str == "help") {
            printHelp();
        } else if (isCommand("f", str, &argument)) {
            //User wants to change focus. Argument should be the Ent's name to be made focus.
            Ent * const new_focus_ptr = treePtr->getEntPtrByName(argument);
            //did we find one with that name? If so, the pointer should be nonzero.
            if (new_focus_ptr == nullptr) {
                cout << "No Ent found with that name.\n";
            } else {
                if (focusPtr == new_focus_ptr) {
                    cout << "That Ent is already the focus.\n";
                } else {
                    setFocus(new_focus_ptr);
                    cout << "Focus: " << focusPtr->getName() << endl;
                }
            }
        } //end "f"
        else if (isCommand("n", str, &argument)) {
            //User wants to create a new ent. Add it under root.
            if (treePtr->getEntPtrByName(argument) == nullptr) {
                //No ent with that name yet, so make a new one.
                //TODO Check for correct Ent name format (not too long, etc.)
                //Create new Ent with the given name and allocate mem on the heap.
                Ent* newEntPtr = new Ent(argument);
                treePtr->addEntToNameMap(newEntPtr);
                //Now we should ask the user to classify the new Ent within the
                //existing hierarchy!
                //Since the new Ent was added as a child of root, analyze root
                //for any estranged children.
                analyzeForEstrangedChildren(treePtr->getRoot());
                
            } else {
                cout << "An Ent with that name already exists.\n";
            }

        } //end "n"
        else if (isCommand("p", str, &argument)) {
            //User wants to add the given Ent as a parent to focus.
            //Retrieve a pointer to the given Ent.
            Ent* entPtr = treePtr->getEntPtrByName(argument);
            if (entPtr == nullptr) {
                cout << "No Ent found with that name.";
            } else if (entPtr == focusPtr) {
                cout << "Can't add the focus Ent as its own parent.";
            } else {
                //OK, so the Ent exists and it isn't the focus. We need to test
                //if adding it as a parent to focus is a legal operation.
                
            }
        } //end "p"
        else if (str == "desc") {
            listDescendents(focusPtr);
        }
        else if (str == "anc") {
            listAncestors(focusPtr);
        }
        else {
            cout << "Unknown command.\n";
        }
    }


}


void CLI::listChildren(Ent* entPtr) {
    //Get the Ent's children.
    vector<Ent*>* children = entPtr->getChildren();
    //If it has no children, say so, don't just give a blank list.
    if (children->size() == 0) {
        cout << "\"" << entPtr->getName() << "\" has no children.\n";
    } else {
        //List each child on its own line, indent with a tab.
        //TODO Would indenting with spaces help with portability?
        cout << "Children of \"" << entPtr->getName() << "\":\n";
        for (Ent* child_ptr : *children) {
            cout << "\t" << child_ptr->getName() << "\n";
        }
    }
}


void CLI::listParents(Ent* entPtr) {
    //Get the Ent's parents.
    vector<Ent*>* parents = entPtr->getParents();
    //Is the Ent a parent-less node?
    if (parents->size() == 0) {
        //the only Ent with no parents should be root...
        if (entPtr == treePtr->getRoot()) {
            //Use this opportunity to educate the user about the Hierarchy protocol.
            cout << "By definition, root can not have any parents!\n";
        } else {
            //If the parent-less Ent isn't root, then there is a big problem.
            //This is an invalid state and shouldn't be reachable.
            cout << "ERROR: INVALID STATE: \"" << entPtr->getName() << "\" does not have any "
            << "parents, this shouldn't have happened...\n";
        }
    } else {
        //List each parent on its own line, indented with a tab.
        cout << "Parents of \"" << entPtr->getName() << "\":\n";
        for (Ent* parent_ptr : *parents) {
            cout << "\t" << parent_ptr->getName() << "\n";
        }
    }
}

void CLI::listAncestors(Ent* entPtr) {
    //
    unordered_set<Ent*>* ancestors = entPtr->getAncestors();
    //
    if (ancestors->size() == 0) {
        //Is it root?
        if (entPtr == treePtr->getRoot()) {
            cout << "By definition, root will not have any ancestors.\n";
        } else {
            //So, it's not root...... that's a problem...
            cout << "FATAL ERROR: " << entPtr->getName() << " should have at least one parent...";
            //TODO No need to throw anything for now.
        }
    } else {
        //OK, we have some ancestors to list.
        cout << "Ancestors of " << entPtr->getName() << ":\n";
        for (const auto anc : *ancestors) {
            cout << "\t" << anc->getName() << endl;
        }
    }
    delete ancestors;
}

void CLI::listDescendents(Ent* entPtr) {
    //
    unordered_set<Ent*>* descendents = entPtr->getDescendents();
    //
    if (descendents->size() == 0) {
        //No descendents.
        cout << entPtr->getName() << " doesn't have any descendents.\n";
    } else {
        //OK, we have some descendents to list.
        cout << "Descendents of " << entPtr->getName() << ":\n";
        for (const auto desc : *descendents) {
            cout << "\t" << desc->getName() << endl;
        }
    }
    delete descendents;
}


void CLI::analyzeForEstrangedChildren(Ent *entPtr) {
    
    vector<EstrangedPair*>* pairs = Analyzer::analyzeForEstrangedPairs(entPtr);
    //If there are any, then handle them.
    if (pairs->size() == 0) {
        //Nothing to do here except cleanup memory.
        delete pairs;
    } else {
        //This function will free pairs when needed, so don't do it here.
        handleEstrangedPairs(pairs, entPtr);
    }
}


void CLI::handleEstrangedPairs(vector<EstrangedPair*> *pairs, Ent *parent) {
    
    //If the state is changed in this function, we should not loop through pairs,
    //but rather reiterate starting with analyzeForEstrangedChildren.
    bool additionalIterationNeeded = false;
    
    //ok, so we found some pairs
    cout << parent->getName() << " has " << pairs->size() << " estranged pairs of children.\n";
    
    //Go through each pair and decide what to do.
    //TODO Should we re-analyze the situation after each change made within the loop?
    for (EstrangedPair* pair : *pairs) {
        
        Ent* a = pair->getA();
        Ent* b = pair->getB();
        //Store responses in this string.
        string response;
        //Exclusive?
        cout << "Are " + a->getName() << " and " << b->getName()
                << " exclusive to each other?\ny/n: ";
        getline(cin, response);
        if (response == "y") {
            Ent::setExclusive(a, b);
            cout << "OK, they are exclusive now.\n";
            continue;
        }
        //Overlap?
        cout << "Do " << a->getName() << " and " << b->getName() << " overlap?\ny/n: ";
        getline(cin, response);
        if (response == "y") {
            Ent::setOverlap(a, b);
            cout << "OK, they overlap now.\n";
            continue;
        }
        
        //If it gets here, the one of these must be the parent of the other.
        //Those are the only other 2 logical options.
        //Lets see if they are even logically consistent themselves.
        //A can only be B's parent if the set of A's ancestors don't overlap with
        //the set of B's descendents.
        
        //Can A be B's parent? Get any Ents which prevent this.
        unordered_set<Ent*>* aOverlap = a->canBeParentOf(b);
        //If this set is empty, A can be B's parent with no logical problems.
        bool aCanBeParent = aOverlap->size() == 0;
        //What about B?
        unordered_set<Ent*>* bOverlap = b->canBeParentOf(a);
        //Can B be A's parent?
        bool bCanBeParent = bOverlap->size() == 0;
        //Results of user input.
        bool aIsParent, neitherIsParent = false, overlapIssue = false;
        //Go through the combination of possibilities.
        if (aCanBeParent) {
            if (bCanBeParent) {
                //Either could be the parent...
                cout << "Is " << a->getName() << " the parent or child of "
                        << b->getName() << ", or neither?\np/c/n: ";
                getline(cin, response);
                if (response == "p")
                    aIsParent = true;
                else if (response == "c")
                    aIsParent = false;
                else
                    neitherIsParent = true;
            } else {
                //B can be the parent, but A can't.
                cout << "So, " << a->getName() << " must be the parent of "
                        << b->getName() << ". Correct?\ny/n: ";
                getline(cin, response);
                //If response is "y", then A is parent.
                if (response == "y") {
                    aIsParent = true;
                } else {
                    neitherIsParent = true;
                    overlapIssue = true;
                }
            }
        } else {
            //A can't be the parent.
            if (bCanBeParent) {
                //A can't but B can.
                cout << "So, " << b->getName() << " must be the parent of "
                        << a->getName() << ". Correct?\ny/n: ";
                getline(cin, response);
                //If response is "y", then B is parent.
                if (response == "y") {
                    aIsParent = false;
                } else {
                    neitherIsParent = true;
                    overlapIssue = true;
                }
            } else {
                //So, neither can be the parent, according to the logical analysis...
                neitherIsParent = true;
                overlapIssue = true;
            }
        } //end of user input
        
        if (neitherIsParent) {
            //Neither has been chosen to the be parent. If there is an overlap
            //issue, then tell the user.
            if (overlapIssue) {
                //TODO make this more detailed and inform user of what Ents
                //are to blame.
                cout << "Error: Action would cause invalid state. Action is denied.\n";
            } else {
                cout << "Error: If these two Ents aren't exclusive and don't overlap, "
                        << "then one must be a parent of the other. Invalid state.\n";
            }
        } else {
            //OK, good, one of them has been deemed parent.
            if (aIsParent) {
                Ent::connectUncheckedAndPrune(a, b);
                //Now we need to analyze the children of A.
                analyzeForEstrangedChildren(a);
            } else {
                Ent::connectUncheckedAndPrune(b, a);
                //Now we need to analyze the children of B.
                analyzeForEstrangedChildren(b);
            }
        }
        
        //Release the unordered_sets.
        delete aOverlap;
        delete bOverlap;
        //TODO We should probably change these to smart pointers...
    }
    
    //memory cleanup
    for (EstrangedPair* pair : *pairs)
        delete pair;
    delete pairs;
    
    //TODO Implement boolean additionalIterationsNeeded to keep house-keeping.
}