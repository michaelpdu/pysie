/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
package PublicFunctionBody {
    public function returnParamsInner(s:String, b:Boolean):String { return s; }
    public function returnParams(s:String, b:Boolean):String { return returnParamsInner(s,b); }
}

