#include "Template.hpp"
#include "DelayBase.hpp"

struct DelayModule : DelayBase {
};

struct DelayWidget : DelayBaseWidget {
	DelayWidget(DelayModule *m) : DelayBaseWidget(m) {}
};

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelDelay = Model::create<DelayModule, DelayWidget>("Template", "PureDelay", "Pure Delay", OSCILLATOR_TAG);
