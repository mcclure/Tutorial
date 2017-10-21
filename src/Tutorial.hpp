#include "rack.hpp"


using namespace rack;


extern Plugin *plugin;

////////////////////
// module widgets
////////////////////

struct MyModule;

struct MyModuleWidget : ModuleWidget {
	MyModule *myModule;
	Label *labelWidget;
	MyModuleWidget();
	virtual void draw(NVGcontext *vg);
};
