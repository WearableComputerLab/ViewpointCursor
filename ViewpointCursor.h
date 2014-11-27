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


#ifndef VIEWPOINT_CURSOR_H 
#define VIEWPOINT_CURSOR_H 

#include <base/Module.h>
#include <graphics/Texture.h>

#include <wcl/maths/Vector.h>
#include <wcl/maths/Quaternion.h>


namespace wcl {

    /**
     * The ViewpointCursor maps 2D user input to 3D Spatial Augmented Reality
     * environments.
     */
    class ViewpointCursor
    {
        public:
            /**
             * Construct a new ViewpointCursor object.
             *
             * @param inputScale A scalar for mouse input controlling sensitivity.
             * @param cursorSize The size of the cursor, visible to the user. We
             *                   use mm as the units in our SAR system, so 20mm works for us.
             * @param invertY Whether to invert Y axis input.
             */
            ViewpointCursor(float inputScale=1.0f, bool invertY = false);


            /**
             * DESTRUCTOR!
             */
            ~ViewpointCursor();

            /**
             * Move the cursor based on 2D input from the user.
             *
             * @param dx Relative movement in X.
             * @param dy Relative movement in Y.
             */
            void moveCursor(float dx, float dy);

            /**
             * Returns information about the current cursor location.
             * Returns a pointer to a Selectable object if the cursor is
             * placed over the object.
             */
            Selection getCursor();

            /**
             * Get the rotation of the cursor.
             *
             * The cursor should be rotated so it's always drawn perpendicular
             * to the surface normal.
             */
            wcl::SMatrix getCursorRotation();

            
            /**
             * Set the user's position.
             *
             * This should be the (approximate) position of the user's point of
             * view. In other words, their head.
             *
             * This information would typically come from a tracking system,
             * and should be transformed into the SAR world coordinate space.
             *
             * @param position The position of the user.
             */
            void setUserPosition(wcl::Vector position);

            /**
             * Set the direction the user is looking.
             *
             * Like with position, this needs to be transformed into the SAR
             * world coordinate system.
             *
             * @param The direction vector for the user.
             */
            void setViewDirection(wcl::Vector direction);

        private:
            /**
             * The 2D Device cursor.
             */
            wcl::Vector cursor2D;

            /**
             * The 3D Viewpoint Cursor
             */
            wcl::Vector cursor3D;

            /**
             * The surface normal at the cursor location.
             */
            wcl::Vector cursorNormal;

            wcl::Vector backCursor;
            wcl::Vector planePos;
            double planeDistance;

            /**
             * Whether to invert Y axis input.
             */
            bool invertY;

            /**
             * Scalar for mouse input
             */
            double mouseScale;

            bool updatePending;

            /**
             * User position.
             */
            wcl::Vector userPos;
            wcl::Vector poi;

            /**
             * Initial placement of cursor.
             */
            bool cursorPlaced; 

            wcl::Vector getViewDirection() const;
            wcl::SMatrix getUserRotation() const;
            wcl::SMatrix getUserTransform() const;
            wcl::Vector getUserPosition() const;
            wcl::Vector getCursorDirection() const;
            wcl::SMatrix getCursorTransform() const; 

    };

};

#endif


