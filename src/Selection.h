/**
 *
 * Viewpoint Cursor - Mapping 2D user input to 3D SAR environments.
 * Written by Michael Marner <michael@20papercups.net>
 *
 * Copyright (c) 2014 Wearable Computer Lab @ University of South Australia
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef VIEWPOINT_CURSOR_SELECTION_H
#define VIEWPOINT_CURSOR_SELECTION_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>


namespace wcl {
    // forward dec
    class Selectable;

    /**
     * Selection holds information about objects and points of interest selected by
     * Viewpoint Cursor.
     */
    struct Selection {
        /**
         * The selected position in 3D world coordinates.
         */
        glm::vec3 pos;

        /**
         * The surface normal at the selection point.
         */
        glm::vec3 normal;


        /**
         * A rotation matrix that can be used to rotate the target so it's
         * drawn perpenducular to the surface.
         */
        glm::mat4 rotationMatrix;

        /**
         * The selected object.
         */
        Selectable* object;

        float distance;
    };

};
#endif

