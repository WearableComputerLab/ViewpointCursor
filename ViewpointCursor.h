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

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace wcl {

    /**
     * The ViewpointCursor maps 2D user input to 3D Spatial Augmented Reality
     * environments.
     */
    class ViewpointCursor
    {
        /**
         * Controls how 2D input is interpreted.
         */
        enum MouseMode {
            /**
             * Use input as provided.
             */
            NORMAL,

            /**
             * Invert Y axis. This is needed depending on how you calibrate
             * your projector.
             */
            INVERT_Y
        };

        public:
            /**
             * Construct a new ViewpointCursor object.
             *
             * @param inputScale A scalar for mouse input controlling sensitivity.
             * @param mode How to interpret 2D input.
             */
            ViewpointCursor(float inputScale=1.0f, MouseMode mode = NORMAL);


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
             * Get the rotation of the cursor.              *
             *
             * The cursor should be rotated so it's always drawn perpendicular
             * to the surface normal. This function returns a 4x4
             * matrix that can be given straight to OpenGL either via
             * glMultMatrixf or as a uniform to a shader.
             *
             * @return The rotation matrix for rendering the cursor
             * perpendicular to the selection.
             */
            glm::mat4 getCursorRotation();

            
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
            void setUserPosition(glm::vec3 position);

            /**
             * Set the direction the user is looking.
             *
             * Like with position, this needs to be transformed into the SAR
             * world coordinate system.
             *
             * @param The direction vector for the user.
             */
            void setViewDirection(glm::vec3 direction);

        private:
            /**
             * The 2D Device cursor.
             */
            glm::vec2 cursor2D;

            /**
             * The 3D Viewpoint Cursor
             */
            glm::vec3 cursor3D;

            /**
             * The surface normal at the cursor location.
             */
            glm::vec3 cursorNormal;

            glm::vec3 backCursor;
            glm::vec3 planePos;
            floatplaneDistance;

            /**
             * Whether to invert Y axis input.
             */
            MouseMode mode;

            /**
             * Scalar for mouse input
             */
            float mouseScale;

            bool updatePending;

            /**
             * User position.
             */
            glm::vec3 userPos;
            glm::vec3 poi;

            /**
             * Initial placement of cursor.
             */
            bool cursorPlaced; 

            glm::vec3 getViewDirection() const;
            glm::mat4 getUserRotation() const;
            glm::mat3  getUserTransform() const;
            glm::vec3  getUserPosition() const;
            glm::vec3  getCursorDirection() const;
            glm::mat4 getCursorTransform() const; 

    };

};

#endif


