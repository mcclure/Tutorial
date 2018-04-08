#include "Template.hpp"
#include "DelayBase.hpp"
#include <sstream>

#define MAX_SEC 10
#define MAX_MSEC 10*1000
#define MAX_HISTORY (44100 * 10 + 4410)

struct DelayModule : DelayBase {
	float history[MAX_HISTORY];
	int delayPhase;

	DelayModule() : DelayBase() {
		memset(history, 0, sizeof(history));
		delayPhase = 0;
	}
	int delayMs() {
		return std::max(std::min<float>(
				(params[COARSE_PARAM].value + (params[FINE_PARAM].value - 0.5)/10),
				1.0f), 0.0f)*MAX_MSEC;
	}
	int delaySamples() {
		int amount = delayMs() * engineGetSampleRate() / 1000;
		if (amount > MAX_HISTORY)
			amount = MAX_HISTORY;
		return amount;
	}

	void step() override {
		int backLook = delaySamples();
		bool mute = params[MUTE_PARAM].value > 0.5;

		int inPhase = delayPhase;
		int outPhase = (delayPhase - backLook + MAX_HISTORY) % MAX_HISTORY;
		delayPhase++;
		delayPhase %= MAX_HISTORY;

		float outValue = history[outPhase];

		history[inPhase] = 0;
		if (!mute)
			history[inPhase] += inputs[I_INPUT].value;
		history[inPhase] += inputs[SENDIN_INPUT].value;

		outputs[O_OUTPUT].value = history[inPhase];
		if (mute)
			outputs[O_OUTPUT].value += inputs[I_INPUT].value;

		outputs[SENDOUT_OUTPUT].value = outValue;
	}
};

struct DelayWidget : DelayBaseWidget {
	Label *labelWidget;
	DelayModule *myModule;
	ToggleSwitch *muteSwitch;

	DelayWidget(DelayModule *m) : DelayBaseWidget(m) {
		labelWidget = new Label();
		labelWidget->box.pos = Vec(5, 315);
		labelWidget->color = {{0,0,0,1}};
		//labelWidget->box.size = Vec(100, 50);
		addChild(labelWidget);

		myModule = m;
	}

	void draw(NVGcontext *vg) override {
		std::ostringstream ss;
		//ss << myModule->params[MyModule::COARSE_PARAM].value << ", " << myModule->params[MyModule::FINE_PARAM].value;
		//ss << myModule->delaySamples() << " samples";
		ss << myModule->delayMs() << " ms";
		labelWidget->text = ss.str();

		ModuleWidget::draw(vg);
	}
};

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelDelay = Model::create<DelayModule, DelayWidget>("Dryad Technology", "PureDelay", "Pure Delay", OSCILLATOR_TAG);
