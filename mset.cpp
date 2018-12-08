#include <QtGui>
#include "mset.h"
#include "complex.h"
// for our timer function:
#include <time.h>
#include <inttypes.h>

// for debugging:
#include <iostream>
using std::cout;
using std::endl;


// hack: keep a variable to let us know if the application
// has been initialized so that we can draw the set on startup
bool drawnYet = false;


// In case you want to time your routines, the following function
// should give you a microsecond timer.
uint64_t clockGetTime_mu()
{
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (uint64_t)ts.tv_sec * 1000000LL + (uint64_t)ts.tv_nsec / 1000LL;
}

mandelbrotArea::mandelbrotArea(QWidget *parent) : QWidget(parent)
{
	// set our inital view to hold the entire mandelbrot set.
	// a 3x3 square with -2,-1.5 as the lower left should work.
	llCoord.real = -2;
	llCoord.imag = 1.5;
	windowWidth = 3;
	this->maxIterations = 200; // a decent default
	setAttribute(Qt::WA_StaticContents);
}

bool mandelbrotArea::saveImage(const QString &fileName, const char *fileFormat)
{
	QImage visibleImage = image;
	resizeImage(&visibleImage, size());
	visibleImage.save(fileName, fileFormat);
	return true;
}

void mandelbrotArea::refreshImage()
{
	// this is just an example.  by making this function a "slot" (see the
	// header file) we can easily connect it to events from other objects
	// just as an illustration, we'll draw the gradient the other way.
#if 0
	QPainter qp(&image);
	QColor qc;
	QPen qpen;
	// get the dimensions of our image in terms of pixels:
	unsigned long iwidth = image.width();
	unsigned long iheight = image.height();
	double unit = 1.0 / iwidth; // on a scale of 0-1, how wide is a pixel?
	for (unsigned long i = 0; i < iwidth; i++) {
		qc.setRgbF(i*unit,sqrt(i*unit),i*unit); // set the color we want to draw.
		qpen.setColor(qc); // apply the color to the pen
		qp.setPen(qpen);   // set the painter to use that pen
		qp.drawLine(iwidth-i-1,0,iwidth-i-1,iheight); // draw a line of the specified color.
	}
	update(); // repaint screen contents
	return;
#else
	this->render(); //calls render() again
	return;
#endif
}

void mandelbrotArea::mouseDoubleClickEvent(QMouseEvent *event)
{
	// TODO: write the code for the zoom operation.  You can get
	// the mouse button from event->button() and check for
	// event->button() == Qt::LeftButton, etc. to figure out what
	// button is being pressed.

	/*When the user double-clicks on the window (left mouse)
	> Recenter the window at those coordinates, and zoom by factor of two.
	> Region will be half as wide and half as high as before.
	> When user double clicks with right mouse button, zoom back out
	> Window centered at coordinates of mouse click.
	*/


	unsigned long iwidth = image.width();
	unsigned long iheight = image.height();

	// new x/y coordinates
	double newX=  (windowWidth/iwidth) * event->x() + llCoord.real;
	double newY= -(windowWidth/iheight) * event->y() + llCoord.imag;

	// If left button clicked, zooming in
	if (event->button() == Qt::LeftButton){

		windowWidth=windowWidth/2;
		// since the corner is in the upper right, we must adjust based on that
		llCoord.real= newX - windowWidth/2;
		llCoord.imag= newY + windowWidth/2;

		maxIterations+=100; // for better resolution
		this->render();
			return;

	}
	// If right button clicked, zooming out
	if (event->button() == Qt::RightButton){
		windowWidth=windowWidth*2;

		llCoord.real= newX - windowWidth/2;
		llCoord.imag= newY + windowWidth/2;
		maxIterations-=100;
		this->render();
			return;

	}
}

void mandelbrotArea::mousePressEvent(QMouseEvent *event)
{
	// if you want your application to respond to mouse
	// clicks, implement this function.  You can figure out
	// which mouse button was pressed by examining event->button()
	// and you can get the position from event->pos()

}

void mandelbrotArea::mouseMoveEvent(QMouseEvent *event)
{
	// This will be called whenever the mouse moves across your
	// window.  Might be useful for dragging the image, should
	// you decide to implement it.
}

void mandelbrotArea::mouseReleaseEvent(QMouseEvent *event)
{
	// this would be useful to implement the drag operation.
}

void mandelbrotArea::paintEvent(QPaintEvent *event)
{
	// check: if blank, render first.
	if (!drawnYet) {
		drawnYet = true;
		this->render();
	}
	// otherwise, just repaint the portion of the screen that needs it.
	QPainter painter(this);
	QRect dirtyRect = event->rect();
	painter.drawImage(dirtyRect, image, dirtyRect);
}

void mandelbrotArea::resizeEvent(QResizeEvent *event)
{
	resizeImage(&image, QSize(width(), height()));
	update();
	QWidget::resizeEvent(event);
	return;
}

void mandelbrotArea::render()
{
	// TODO: write this function.
	// draw the portion of the mandelbrot set that lies in our window.
	// idea: loop through all the pixels, iterate the function figure out how
	// quickly the point is diverging, and color it based on the result

	// to give you some idea of what you need to do, I've drawn a nice green
	// gradient on the screen.  You will want to set the individual pixels
	// using the qp.drawPoint(x,y) function, instead of drawing a line.
	QPainter qp(&image);
	QColor qc;
	QPen qpen;
	// get the dimensions of our image in terms of pixels:
	unsigned long iwidth = image.width();
	unsigned long iheight = image.height();
	//double unit = 1.0 / iwidth; // on a scale of 0-1, how wide is a pixel?
	/*
		// This is the example Skeith gave us:
	for (unsigned long i = 0; i < iwidth; i++) {
		qc.setRgbF(i*unit,sqrt(i*unit),i*unit); // set the color we want to draw.
		qpen.setColor(qc); // apply the color to the pen
		qp.setPen(qpen);   // set the painter to use that pen
		qp.drawLine(i,0,i,iheight); // draw a line of the specified color.
	}
	*/


	// This for loop iterates through each pixel in the screen
	for (unsigned int x=0; x<iwidth; x++){ //x is the real # axis
			for (unsigned int y=0; y<iheight; y++){ // y is the complex # axis
				//convert computer (x,y) plane to complex plane
					double complexR = (windowWidth/iwidth) * x + llCoord.real;
					double complexI = -(windowWidth/iwidth) *  y + llCoord.imag; //use iwidth since drawing space is a square

					complex c  = complex(complexR, complexI);
					complex M = complex(), W = complex();
					bool explodeSet = false; //if z^2 + c diverges when iterated

					long numI = 1; //number of iterations. starts at 1 to prevent division by 0 (see colors below)
					for(numI = 1; numI < maxIterations ; numI++) {
						 W  = M * M + c;
						if(W.norm() > 2){
							explodeSet = true; //z^2 + c diverges
							break;
						}
						M = W;
					}

					if (explodeSet) {
						qc.setRgbF(1.0-1.0/numI,1.0-sqrt(1.0/numI),1.0-1.0/numI);
						/* can't really explain the math behind this LOL~
						 * But setRgbF takes only numbers <= 1.0.
						 * The lighter colors are closer to the Mandelbrot set.*/

						qpen.setColor(qc);  // gives the color to the pen
						qp.setPen(qpen); // gives the pen to the painter
						qp.drawPoint(x,y);
					} else {
						qc.setRgbF(0,0,0); //colors the region in the Mandelbrot set black
						qpen.setColor(qc);
						qp.setPen(qpen);
						qp.drawPoint(x,y);
					}

			}
	}
	update(); // repaint screen contents
	return;
}

void mandelbrotArea::resizeImage(QImage *image, const QSize &newSize)
{
	// your custom resize code would go here...
	if (image->size() == newSize)
		return;

	// for now, we will just expand our image with blank (white) space.
	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}

unsigned long mandelbrotArea::getIterations()
{
	/* NOTE: this is used by MainWindow for the initial value to place
	 * in the iteration control dialog. */
	return this->maxIterations;
}

void mandelbrotArea::setIterations(unsigned long newMax)
{
	/* NOTE: this is called by MainWindow once the iterations
	 * dialog has been processed. */
	this->maxIterations = newMax;
}
