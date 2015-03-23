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


#ifndef VIEWPOINT_CURSOR_PLANE_H
#define VIEWPOINT_CURSOR_PLANE_H

#include <glm/vec3.hpp>

namespace wcl {


    // look we need a simple Plane class for doing fallback intersections.
    class Plane {
        struct Intersection  {
            bool intersects;
            glm::vec3 intersectionPoint;
        };

        public:
            Plane(const glm::vec3& point, const glm::vec3& normal);
            Intersection intersect(glm::vec3 start, glm::vec3 direction);


        private:
			/**
			 * The surface normal of the plane (A,B,C).
			 */
            glm::vec3 normal;

			/**
			 * A point that lies on the plane.
			 */
            glm::vec3 point;
    };
};



#endif

