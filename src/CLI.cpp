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

CLI::CLI(Hierarchy* arch_ptr) {
    setArch(arch_ptr);
}

CLI::~CLI() {
}

void CLI::listen() {
    //Initiate the listening sequence with no intention to exit yet.
    exiting_ = false;
    //Declare string to hold future commands here. Maybe just redeclare each time instead?
    string command;
    //Let the user know what Ent will start out as the focus.
    cout << "Focus: " << focus_ptr_->getName() << endl;
    //Loop to repeatedly input commands.
    do {
        //Use the standard > to indicate we're listening for commands.
        cout << ">";
        //Read from console.
        getline(cin, command);
        parse(command);
    } while (!exiting_);
    //Keep going till we're told to exit with "e" or "exit".

}


void CLI::parse(string str) {
    
    //string to hold the arguments substring if necessary.
    string argument;

    //first handle the 1 character commands
    if (str.size() == 1) {
        if (str == "f") {
            //list the current ent of focus
            cout << "Focus: " << focus_ptr_->getName() << endl;
        } else if (str == "e") {
            cout << "Exiting..." << endl;
            exiting_ = true;
        } else if (str == "c") {
            listChildren(focus_ptr_);
        } else if (str == "p") {
            listParents(focus_ptr_);
        } else if (str == "b") {
            //Do a break point. perhaps useful in debugging.
            //TODO implement as optional via preprocessor hiding to disable in production.
            cout << "breakpoint\n";
        } else if (str == "h") {
            printHelp();
        } else {
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
            Ent * const new_focus_ptr = arch_ptr_->getEntPtrByName(argument);
            //did we find one with that name? If so, the pointer should be nonzero.
            if (new_focus_ptr == 0) {
                cout << "No Ent found with that name.\n";
            } else {
                if (focus_ptr_ == new_focus_ptr) {
                    cout << "That Ent is already the focus.\n";
                } else {
                    setFocus(new_focus_ptr);
                    cout << "Focus: " << focus_ptr_->getName() << endl;
                }
            }
        } else if (isCommand("n", str, &argument)) {
            //User wants to create a new ent. Add it under root.
            if (arch_ptr_->getEntPtrByName(argument) == 0) {
                //No ent with that name yet, so make a new one.
                //TODO Check for correct Ent name format (not too long, etc.)
                //Create new Ent with the given name and allocate mem on the heap.
                Ent* newEntPtr = new Ent(argument);
                arch_ptr_->addEntToNameMap(newEntPtr);
            } else {
                cout << "An Ent with that name already exists.\n";
            }

        } else if (isCommand("p", str, &argument)) {
            //User wants to add the given Ent as a parent to focus.
            //Retrieve a pointer to the given Ent.
            Ent* entPtr = arch_ptr_->getEntPtrByName(argument);
            if (entPtr == 0) {
                cout << "No Ent found with that name.";
            } else if (entPtr == focus_ptr_) {
                cout << "Can't add the focus Ent as its own parent.";
            } else {
                //OK, so the Ent exists and it isn't the focus. We need to test
                //if adding it as a parent to focus is a legal operation.
                
            }
        } else {
            cout << "Unknown command.\n";
        }
    }


}


void CLI::listChildren(Ent* ent_ptr) {
    //Get the Ent's children.
    vector<Ent*>* children = ent_ptr->getChildren();
    //If it has no children, say so, don't just give a blank list.
    if (children->size() == 0) {
        cout << "\"" << ent_ptr->getName() << "\" has no children.\n";
    } else {
        //List each child on its own line, indent with a tab.
        //TODO Would indenting with spaces help with portability?
        cout << "Children of \"" << ent_ptr->getName() << "\":\n";
        for (Ent* child_ptr : *children) {
            cout << "\t" << child_ptr->getName() << "\n";
        }
    }
}


void CLI::listParents(Ent* ent_ptr) {
    //Get the Ent's parents.
    vector<Ent*>* parents = ent_ptr->getParents();
    //Is the Ent a parent-less node?
    if (parents->size() == 0) {
        //the only Ent with no parents should be root...
        if (ent_ptr == arch_ptr_->getRoot()) {
            //Use this opportunity to educate the user about the Hierarchy protocol.
            cout << "By definition, root can not have any parents!\n";
        } else {
            //If the parent-less Ent isn't root, then there is a big problem.
            //This is an invalid state and shouldn't be reachable.
            cout << "ERROR: INVALID STATE: \"" << ent_ptr->getName() << "\" does not have any "
            << "parents, this shouldn't have happened...\n";
        }
    } else {
        //List each parent on its own line, indented with a tab.
        cout << "Parents of \"" << ent_ptr->getName() << "\":\n";
        for (Ent* parent_ptr : *parents) {
            cout << "\t" << parent_ptr->getName() << "\n";
        }
    }
}