#include "Template.hpp"
#include "HoldBase.hpp"
#include <sstream>

#define HOLDS 4
#define RISING 0.55
#define FALLING 0.45

struct HoldModule : HoldBase {
	float holds[HOLDS];
	bool high;

	HoldModule() : HoldBase() {
		memset(holds, 0, sizeof(holds));
		high = false;
	}

	void step() override {
		if (!high && inputs[CONTROL_INPUT].value > RISING) {
			holds[0] = inputs[IN1_INPUT].value;
			holds[1] = inputs[IN2_INPUT].value;
			holds[2] = inputs[IN3_INPUT].value;
			holds[3] = inputs[IN4_INPUT].value;
			high = true;
		} else if (high && inputs[CONTROL_INPUT].value < FALLING) {
			high = false;
		}

		outputs[OUT1_OUTPUT].value = holds[0];
		outputs[OUT2_OUTPUT].value = holds[1];
		outputs[OUT3_OUTPUT].value = holds[2];
		outputs[OUT4_OUTPUT].value = holds[3];
	}
};

struct HoldWidget : HoldBaseWidget {
	HoldWidget(HoldModule *m) : HoldBaseWidget(m) {
	}
};

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelHold = Model::create<HoldModule, HoldWidget>("Dryad Technology", "Hold", "Hold", OSCILLATOR_TAG);
