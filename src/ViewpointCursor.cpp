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


#include <glm/geometric.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Plane.h"
#include "ViewpointCursor.h"


namespace wcl {


    ViewpointCursor::ViewpointCursor(float inputScale, MouseMode mode) 
        : planeDistance(10000), mouseScale(inputScale), mouseMode(mode),
        updatePending(false) {

        }

    ViewpointCursor::~ViewpointCursor() {}


    void ViewpointCursor::moveCursor(glm::vec2 relativeInput) {

        cursor2D.x = cursor2D.x + relativeInput.x*mouseScale;
        if (mouseMode == INVERT_Y) {
            cursor2D.y = cursor2D.y - relativeInput.y*mouseScale;
        }
        else {
            cursor2D.y = cursor2D.y + relativeInput.y*mouseScale;
        }
        updatePending = true;
    }

    Selection ViewpointCursor::getCursor(const SelectableList& selectables) {
        Selectable* closestObject = NULL;
        Selection closestIntersection;
        if (updatePending) {

            closestIntersection.distance = std::numeric_limits<float>::max();

            glm::vec3 p = getUserPosition();
            glm::vec3 d = getCursorDirection();


            // First up, see if we intersect one of the objects.
            for (SelectableList::const_iterator it = selectables.begin(); it < selectables.end(); ++it) {
                Selectable* s = *it;
                Selection i = s->intersect(p, d);

                if (i.distance > 0 && i.distance < closestIntersection.distance)
                {
                    closestObject = s;
                    closestIntersection = i;
                }
            }
            updatePending = false;

            // Return the closest object, if there was one.
            if (closestObject != NULL) {
                cursorPlaced = true;
                cursor3D = closestIntersection.pos;
                cursorNormal = closestIntersection.normal;
                closestIntersection.rotationMatrix = getCursorRotation();
                closestIntersection.object = closestObject;
            }

            // intersect with magic plane so at least the cursor appears...
            else {
                glm::vec3 userDirection = getViewDirection();
                Plane plane(p + userDirection*planeDistance, userDirection);
                Plane::Intersection ip = plane.intersect(p, d);
                if (ip.intersects) {
                    cursorPlaced = true;
                    cursor3D = ip.intersectionPoint;
                    cursorNormal = userDirection*-1.0f;
                    cursorPlaced = true;

                    closestIntersection.pos = cursor3D;
                    closestIntersection.normal = cursorNormal;
                    closestIntersection.rotationMatrix = getCursorRotation();
                    closestIntersection.object = NULL;
                }
            }
        }
        return closestIntersection;
    }

    void ViewpointCursor::setUserPosition(glm::vec3 position) {
        userPos = position;
        reverseUpdate();
    }

    void ViewpointCursor::setViewDirection(glm::vec3 direction) {
        viewDirection = direction;
        reverseUpdate();
    }

    void ViewpointCursor::reverseUpdate() {
        glm::vec3 d = glm::normalize(cursor3D - userPos);
        planePos = userPos + viewDirection*planeDistance;

        wcl::Plane p(planePos, viewDirection);

        Plane::Intersection i = p.intersect(userPos, d);

        if (i.intersects) {
            backCursor = glm::vec4(i.intersectionPoint.x, i.intersectionPoint.y, i.intersectionPoint.z, 1);

            // rotate back to local...
            glm::vec4 vi = glm::affineInverse(getUserTransform()) * backCursor;

            cursor2D.x = vi.x;
            cursor2D.y = vi.y;
        }
    }
};
