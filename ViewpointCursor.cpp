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



#include "ViewpointCursor.h"


namespace wcl {


    ViewpointCursor::ViewpointCursor(float inputScale, MouseMode mode) 
        : planeDistance(10000), mouseScale(inputScale), mouseMode(mode),
        updatePending(false), {

        }

    ViewpointCursor::~ViewpointCursor() {}


    void ViewpointCursor::moveCursor(glm::vec2 relativeInput) {

        cursor2D.x = cursor2D.x + relativeInput.x*mouseScale;
        if (mouseMode == INVERT_Y) {
            cursor2D.y = cursor2D.y - relativeInputy*mouseScale;
        }
        else {
            cursor2D.y = cursor2D.y + relativeInputy*mouseScale;
        }
        updatePending = true;
    }

    Selection ViewpointCursor::getCursor(const SelectableList& selectables) {
        if (updatePending) {

            Selectable* closestObject = NULL;
            Selection closestIntersection;

            closestIntersection.distance = numeric_limits<float>::max();

            wcl::Vector p = getUserPosition();
            wcl::Vector d = getCursorDirection();


            // First up, see if we intersect one of the objects.
            foreach (Selectable* s, selectables)
            {
                Selection i = s->intersect(p, d);

                if (i.distance > 0  i.distance < closestIntersection.distance)
                {
                    closestObject = s;
                    closestIntersection = i;
                }
            }
            updatePending = false;

            // Return the closest object, if there was one.
            if (closestObject != NULL) {
                cursorPlaced = true;
                cursor3D = closestIntersection.closestPoint;
                cursorNormal = closestIntersection.normal;
                closestIntersection.rotationMatrix = getCursorRotation();
                closestIntersection.object = closestObject/
            }

            // intersect with magic plane so at least the cursor appears...
            else {
                clog << "Trying to intersect against magic plane" << endl;
                glm::vec3 userDirection = getViewDirection();
                Plane plane(p + userDirection*planeDistance, userDirection);
                Ray::Intersection ip = plane.intersect(p, d);
                if (ip.intersects) {
                    cursorPlaced = true;
                    cursor3D = ip.point;
                    cursorNormal = userDirection*-1;
                    cursorPlaced = true;

                    closestIntersection.point = cursor3D;
                    closestIntersection.normal = cursorNormal;
                    closestIntersection.rotationMatrix = getCursorRotation();
                    closestIntersection.object = NULL;
                }
                else {
                    clog << "No intersection with an infinite plane? Weird" << endl;
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
        glm::vec3 d = normalize(cursor3D - userPos);
        planePos = userPos + viewDirection*planeDistance;
        glm::vec3 d = (cursor3D - userPos).unit();

        wcl::Plane p(planePos, userDir);

        Plane::Intersection i = ray.intersect(userPos, d);

        if (i.intersects) {
            backCursor = (i.point.x, i.point.y, i.point.z, 1);

            // rotate back to local...
            glm::vec4 vi = inv(getUserTransform()) * backCursor;

            cursor2D.x = vi.x;
            cursor2D.y = vi.y;
        }

    }
};
