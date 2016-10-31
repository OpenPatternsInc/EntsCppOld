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

/**
 * Construct a CLI object with the given Tree. We don't give a no-arg
 * constructor because we just want to always initialize a CLI with a
 * Tree anyways.
 * @param arch_ptr
 */
CLI::CLI(EntsFile* entsFile) {
    setEntsFile(entsFile);
}

/**
 * Do not deallocate the Tree or the Ent of focus.
 * The user may want to instead open up a GUI or something else.
 * There is no other way to browse Hierarchies yet though.
 */
CLI::~CLI() {
}

/**
 * Starts listening for commands in the console. Commands are used to explore
 * and edit the Tree.
 */
void CLI::listen() {
    //Initiate the listening sequence with no intention to exit yet.
    exiting_ = false;
    //Declare string to hold future commands here.
    //Maybe just redeclare each time instead?
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
} //end of listen()

/**
* Parse the given command and carry out the actions it represents.
* @param str   Raw string of the command. Doesn't include the "<".
*/
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
            //TODO implement as optional via preprocessor.
            cout << "breakpoint\n";
        } else if (str == "h") {
            printHelp();
        } else if (str == "a") {
            //Get a pointer to a vector containing any estranged pairs
            EstrangedChildrenResolution result = checkForEstrangedChildren(focusPtr);
            //If the result was NO_PAIRS or ERROR, inform the user.
            if (result == NO_PAIRS_FOUND) {
                cout << "No estranged children found.\n";
            } else if (result == RESOLUTION_ERROR) {
                cout << "ERROR: Problem resolving estranged children.";
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
                cout << "Siblings of " << focusPtr->getName()
                        << " under " << parent->getName() << ":\n";
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
            //User wants to change focus.
            //Argument should be the Ent's name to be made focus.
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
                checkForEstrangedChildren(treePtr->getRoot());
                
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
        else if (str == "save") {
            saveTree();
        }
        else {
            cout << "Unknown command.\n";
        }
    }
} //end of parseCommand()

/**
     * Sees if the given text is a command, and if so, sets the given argument
     * string to the substring after the command.
     * @param command       The command identifier used first.
     * @param text          The full input text.
     * @param argument      Pointer to the string holding the argument.
     * @return 
     */
const bool CLI::isCommand(const string command, const string text, string *argument) {

    if (text.find((command + " ")) == 0) {
        //The text started with the command and then a space.
        //Extract the argument and set the string given.
        *argument = text.substr(command.size() + 1);
        return true;
    } else {
        //The text did not start with the given command, so, return false.
        return false;
    }
} //end of isCommand

/**
* List the given Ent's children.
* Do not alter the Ent!
* @param entPtr
*/
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
} //end of listChildren

/**
* Lists the given Ent's parents.
* Do not alter the Ent!
* @param entPtr
*/
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
} //end of listParents


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
} //end of listAncestors


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
} //end of listDescendents()

/**
 * Estranged children which don't reference each other indicates missing useful
 * information. Any two direct children of a parent must either overlap, be
 * exclusive, or have a parent-child connection.
 * 
 * This method is a CLI implementation to identify and help the user address
 * this issue. The children of a parent are analyzed by searching for a pair of
 * Ents which don't reference each other. This pair is then presented to the
 * user to address.
 * 
 * Once the user addresses this estranged pair, the algorithm is repeated. One
 * pair is handled at a time because altering that pair's relationship may
 * invalidate other pairs which existed before.
 * 
 * TODO Make the return variable to be something descriptive.
 * 
 * @param parent
 */
EstrangedChildrenResolution CLI::checkForEstrangedChildren(Ent *parent) {
    //Records the result of this algorithm. Default is ERROR.
    EstrangedChildrenResolution result = RESOLUTION_ERROR;
    //Generate a vector containing any pairs of children that don't reference each other.
    EstrangedPair *pair = TreeAnalyzer::analyzeForEstrangedChildren(parent);
    //If none were found, just return now.
    if (pair == nullptr) return NO_PAIRS_FOUND;
    //Extract Ent A and B from the pair.
    Ent* a = pair->getA();
    Ent* b = pair->getB();
    //Tell the user that more info is needed.
    cout << "Additional information required for "
            << a->getName() << " and " << b->getName() << ".\n";
    //Store responses in this string.
    string response;
    //Exclusive?
    cout << "Are " + a->getName() << " and " << b->getName()
            << " exclusive to each other?\ny/n: ";
    getline(cin, response);
    if (response == "y") {
        Ent::setExclusive(a, b);
        cout << "OK, they are exclusive now.\n";
        return PAIR_RESOLVED;
    }
    //Overlap?
    cout << "Do " << a->getName() << " and " << b->getName() << " overlap?\ny/n: ";
    getline(cin, response);
    if (response == "y") {
        Ent::setOverlap(a, b);
        cout << "OK, they overlap now.\n";
        return PAIR_RESOLVED;
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
            //Connect them and prune the tree if necessary.
            Ent::connectUncheckedAndPrune(a, b);
            //Good results.
            result = PAIR_RESOLVED;
            //Now we need to analyze the children of A.
            checkForEstrangedChildren(a);
        } else {
            //Connect them and prune the tree if necessary.
            Ent::connectUncheckedAndPrune(b, a);
            //Good results
            result = PAIR_RESOLVED;
            //Now we need to analyze the children of B.
            checkForEstrangedChildren(b);
        }
    }

    //Release the unordered_sets.
    delete aOverlap;
    delete bOverlap;
    //TODO We should probably change these to smart pointers...
        
    //memory cleanup
    delete pair;
    //Return the result.
    return result;
} //end of checkForEstrangedChildren()


/**
 * Prints the help section to console.
 */
void CLI::printHelp() {
    cout << "Commands with no argument:\n"
            << "\t>f\t\tPrints out current Ent of focus.\n"
            << "\t>p\t\tLists the focus' parents.\n"
            << "\t>c\t\tLists the focus' children.\n"
            << "\t>s\t\tLists the siblings of focus.\n"
            << "\t>e or >exit\tExits command interface.\n"
            << "\t>h\t\tPrints this help section.\n"
            << "\t>b\t\tUsed to bring up an optional breakpoint if desired.\n"
            << "Commands with one argument:\n"
            << "\t>f [Ent name]\tChanges focus to the Ent with the given name.\n"
            << "\t>n [Ent name]\tCreates a new Ent with the given name, if available,\n"
            << "\t\t\tand sets its only parent as root.\n";
} //end of printHelp()


bool CLI::saveTree() {
    
    //Does the EntsFile have a file name?
    if (entsFile->getFileName() != "") {
        //We have a filename already.
    } else {
        bool hasName = false;
        //Give the user 3 chances to input a valid name.
        for (int count = 0; count < 3; count++) {
            if (queryFileName()) {
                hasName = true;
                break;
            }
        }
        if (!hasName) {
            cout << "File was not saved.\n";
            return false;
        }
        //OK, so we got a file name!
        entsFile->save();
        
        
        
        
        return true;
    }
    
    
    return false;
}

/**
* Asks the user what they want to name the tree.
* @return 
*/
bool CLI::queryTreeName(EntsFile* entsFile) {
    bool success = false;
    cout << "What would you like to name this tree: ";
    string response;
    getline(cin, response);
    //TODO Check for valid characters and stuff like that.
    if (response.size() > 2) {
        entsFile->getTree()->setName(response);
        cout << "OK, the tree has been named \"" << response << "\".\n";
        success = true;
    } else {
        cout << "Please, use at least 3 characters.\n";
        success = false;
    }
    return success;
} //end of queryTreeName()

/**
* Ask the user to input a filename they want to use to save the tree.
* @return 
*/
bool CLI::queryFileName() {
    bool success = false;

    cout << "What is the name of the .ents file you wish to save the tree as?\n>";
    string response;
    getline(cin, response);
    if (response.size() > 2) {
        entsFile->setFileName(response);
        success = true;
        cout << "File will be saved as \"" << response << "." << EntsFile::getPostfix() << "\".\n";
    } else {
        cout << "Please use a file name with at least 2 characters.\n";
        success = false;
    }
    return success;
} //end of queryFileName()