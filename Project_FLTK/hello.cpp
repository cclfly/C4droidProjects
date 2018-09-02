#include <FL/Fl.H>
#include <FL/Fl_Window.H>

int main()
{
	Fl_Window *window = new Fl_Window(300,180);
	window->label("hello");
	window->show();
	return Fl::run();
}