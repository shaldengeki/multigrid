//window.cpp
//window class implementation.

/* THIS CODE IS the best ever. */

#include "window.hpp"
using namespace std;

Window::Window() {
     //constructor.
     set_x(0.0);
     set_y(0.0);
     srand(time(NULL));
}

float Window::get_x() {
      return x;
}

float Window::get_y() {
      return y;
}

void Window::set_x(float new_x) {
     x = new_x;
}

void Window::set_y(float new_y) {
     y = new_y;
}

void Window::draw_grid() {
     //draws grid on map.
     float grid_x, grid_y, start_y, start_x;

     start_x = abs(get_x() - floor(get_x()));
     start_y = abs(get_y() - floor(get_y()));

     glPushMatrix();
     glLineWidth(1.0);
     glColor3f(0.0f,0.5f,0.0f);
     glBegin(GL_LINES);
     for (grid_y = 3.0 - start_y; grid_y >= -3.0 + start_y; grid_y -= 0.6)
     {
          glVertex2f(-3.0f, grid_y);
          glVertex2f(3.0f, grid_y);
     }
     for (grid_x = 3.0 - start_x; grid_x >= -3.0 + start_x; grid_x -= 0.6)
     {
          glVertex2f(grid_x, -3.0f);
          glVertex2f(grid_x, 3.0f);
     }
     glEnd();  
     glPopMatrix();
}

void Window::draw_borders() {
    float horiz_top=3.0f, vert_right=3.4f, horiz_bottom=3.0f, vert_left=3.4f;

    glColor3f(1.0f,1.0f,1.0f);
    //check bounds and draw walls if necessary
    if (get_y() >= 5)
       horiz_top = 2.4f;
    if (get_y() <= -5)
       horiz_bottom = 2.4f;
    if (get_x() >= 5)
       vert_right = 3.0f;
    if (get_x() <= -5)
       vert_left = 3.0f;
    
    
    if (get_x() >= 4.8 && get_x() < 5)
    {
	     glBegin(GL_QUADS);									// scrolling right border.
              glVertex3f(get_x()-1.5, horiz_top, 0.0f);			// Top Left
		      glVertex3f(3.4f, horiz_top, 0.0f);					// Top Right
		      glVertex3f(get_x()-1.5,-horiz_bottom, 0.0f);			// Bottom Right
		      glVertex3f(3.4f,-horiz_bottom, 0.0f);					// Bottom Left
         glEnd();         
    }
    if (get_x() >= 5)
    {
	     glBegin(GL_QUADS);									// right border.
              glVertex3f(3.0f, horiz_top, 0.0f);					// Top Left
		      glVertex3f(3.2f, horiz_top, 0.0f);					// Top Right
		      glVertex3f(3.2f,-horiz_bottom, 0.0f);					// Bottom Right
		      glVertex3f(3.0f,-horiz_bottom, 0.0f);					// Bottom Left
         glEnd();
    }
    if (get_x() <= -4.8 && get_x() > -5)
    {
	     glBegin(GL_QUADS);									// scrolling left border.
              glVertex3f(get_x()+1.5, horiz_top, 0.0f);			// Top Left
		      glVertex3f(-3.4f, horiz_top, 0.0f);		        // Top Right
		      glVertex3f(get_x()+1.5,-horiz_bottom, 0.0f);			// Bottom Right
		      glVertex3f(-3.4f,-horiz_bottom, 0.0f);				// Bottom Left
         glEnd();         
    }
    if (get_x() <= -5)
    {
         glBegin(GL_QUADS);									// left border.
		      glVertex3f(-3.2f, horiz_top, 0.0f);				// Top Left
		      glVertex3f(-3.0f, horiz_top, 0.0f);				// Top Right
		      glVertex3f(-3.0f,-horiz_bottom, 0.0f);				// Bottom Right
		      glVertex3f(-3.2f,-horiz_bottom, 0.0f);				// Bottom Left
	     glEnd();
    }
    if (get_y() >= 4.8 && get_y() < 5)
    {
	     glBegin(GL_QUADS);									// scrolling top border.
              glVertex3f(-vert_left, 2.4f, 0.0f);		        // Top Left
		      glVertex3f(vert_right, 2.4f, 0.0f);					// Top Right
		      glVertex3f(vert_right, get_y()-2.4, 0.0f);		    // Bottom Right
		      glVertex3f(-vert_left,get_y()-2.4,0.0f);		    // Bottom Left
         glEnd();         
    }
    if (get_y() >= 5)
    {
	     glBegin(GL_QUADS);									// top border.
              glVertex3f(-vert_left, 2.4f, 0.0f);		        // Top Left
		      glVertex3f(vert_right, 2.4f, 0.0f);					// Top Right
		      glVertex3f(vert_right, 2.2f, 0.0f);		            // Bottom Right
		      glVertex3f(-vert_left,2.2f,0.0f);		            // Bottom Left
         glEnd();
    }
    if (get_y() <= -4.8 && get_y() > -5)
    {
	     glBegin(GL_QUADS);									// scrolling bottom border.
              glVertex3f(-vert_left, -2.4f, 0.0f);		        // Top Left
		      glVertex3f(vert_right, -2.4f, 0.0f);					// Top Right
		      glVertex3f(vert_right, get_y()+2.6, 0.0f);		    // Bottom Right
		      glVertex3f(-vert_left,get_y()+2.6,0.0f);		    // Bottom Left
         glEnd();         
    }
    if (get_y() <= -5)
    {
         glBegin(GL_QUADS);									// bottom border.
              glVertex3f(-vert_left, -2.2f, 0.0f);		        // Top Left
		      glVertex3f(vert_right, -2.2f, 0.0f);				// Top Right
		      glVertex3f(vert_right, -2.4f, 0.0f);		        // Bottom Right
		      glVertex3f(-vert_left,-2.4f,0.0f);		            // Bottom Left
	     glEnd();
    } 
}
