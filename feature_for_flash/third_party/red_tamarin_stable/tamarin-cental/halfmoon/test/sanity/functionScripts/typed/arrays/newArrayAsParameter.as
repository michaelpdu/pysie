// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


package {

    function printHello(value:Array) {
        otherValue(value);
    }

    function otherValue(value:Array) {
        print(value);
    }


    function createArray() {
        var x:Array = [ 0, 10, 13 ];
        printHello(x);
    }

    createArray();
}


