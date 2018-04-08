#include "Template.hpp"
#include "PlayBase.hpp"
#include <sstream>

#define MAX_SEC 10
#define MAX_MSEC 10*1000
#define MAX_HISTORY (44100 * 10 + 4410)

struct PlayModule : PlayBase {
	PlayModule() : PlayBase() {
	}

	void step() override {
	}
};

struct PlayWidget : PlayBaseWidget {
	PlayWidget(PlayModule *m) : PlayBaseWidget(m) {
	}
};

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelPlay = Model::create<PlayModule, PlayWidget>("Dryad Technology", "MiniPiano_1oct", "Play", OSCILLATOR_TAG);
