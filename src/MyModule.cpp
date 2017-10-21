#include "Tutorial.hpp"
#include <sstream>

#define MAX_HISTORY (44100 * 10 + 4410)

struct MyModule : Module {
	enum ParamIds {
		COARSE_PARAM,
		FINE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IO_INPUT,
		SEND_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		IO_OUTPUT,
		SEND_OUTPUT,
		NUM_OUTPUTS
	};

	float history[MAX_HISTORY];
	int delayPhase;

	MyModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
		memset(history, 0, sizeof(history));
		delayPhase = 0;
	}
	void step();
	int delayMs() {
		return params[COARSE_PARAM].value + params[FINE_PARAM].value;
	}
	int delaySamples() {
		int amount = delayMs() * gSampleRate / 1000;
		if (amount > MAX_HISTORY)
			amount = MAX_HISTORY;
		return amount;
	}

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - initialize, randomize: implements special behavior when user clicks these from the context menu
};


void MyModule::step() {
	int backLook = delaySamples();

	int inPhase = delayPhase;
	int outPhase = (delayPhase - backLook + MAX_HISTORY) % MAX_HISTORY;
	delayPhase++;
	delayPhase %= MAX_HISTORY;

	float outValue = history[outPhase];

	history[inPhase] = 0;
	history[inPhase] += inputs[IO_INPUT].value;
	history[inPhase] += inputs[SEND_INPUT].value;

	outputs[IO_OUTPUT].value = 0;
	outputs[IO_OUTPUT].value   += outValue;
	outputs[IO_OUTPUT].value   += inputs[IO_INPUT].value;

	outputs[SEND_OUTPUT].value = outValue;
}

void MyModuleWidget::draw(NVGcontext *vg) {
	std::ostringstream ss;
	//ss << myModule->params[MyModule::COARSE_PARAM].value << ", " << myModule->params[MyModule::FINE_PARAM].value;
	//ss << myModule->delaySamples() << " samples";
	ss << myModule->delayMs() << " ms";
	labelWidget->text = ss.str();

	ModuleWidget::draw(vg);
}

MyModuleWidget::MyModuleWidget() {
	MyModule *module = new MyModule();
	myModule = module;
	setModule(module);
	box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/MyModule.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 365)));

	addInput(createInput<PJ301MPort>(Vec(15, 70), module, MyModule::IO_INPUT));
	addInput(createInput<PJ301MPort>(Vec(15, 100), module, MyModule::SEND_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(60, 70), module, MyModule::IO_OUTPUT));
	addOutput(createOutput<PJ301MPort>(Vec(60, 100), module, MyModule::SEND_OUTPUT));

	addParam(createParam<Davies1900hBlackKnob>(Vec(15, 160), module, MyModule::COARSE_PARAM, 100, 10000, 1000));
	addParam(createParam<Davies1900hBlackKnob>(Vec(60, 160), module, MyModule::FINE_PARAM, -100, 100, 0));

	labelWidget = new Label();
	labelWidget->box.pos = Vec(5, 215);
	//labelWidget->box.size = Vec(100, 50)
	addChild(labelWidget);

	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 365)));
}
