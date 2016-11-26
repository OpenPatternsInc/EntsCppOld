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

#include "EntsClient.h"

using boost::asio::ip::tcp;

using namespace std;

int EntsClient::connect() {

    try {

        tcp::iostream s("35.160.222.230:1307", "tcp");
        if (!s) {
            cout << "Unable to connect: " << s.error().message() << endl;
            return 1;
        }

        string line;
        getline(s, line);
        cout << line << endl;

    } catch (exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}