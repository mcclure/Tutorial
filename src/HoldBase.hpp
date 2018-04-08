#include "Template.hpp"

struct HoldBase : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		CONTROL_INPUT,
		IN1_INPUT,
		IN2_INPUT,
		IN3_INPUT,
		IN4_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};
	enum CustomIds {
		NUM_CUSTOMS
	};

	HoldBase() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
};

struct HoldBaseWidget : ModuleWidget {
	HoldBaseWidget(HoldBase *m) : ModuleWidget(m) {
		setPanel(SVG::load(assetPlugin(plugin, "res/HoldBase.svg")));

		addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 365)));

		addInput(Port::create<PJ301MPort>(mm2px(Vec(9.844, 10.365)), Port::INPUT, module, HoldBase::CONTROL_INPUT));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(3.443, 19.176)), Port::INPUT, module, HoldBase::IN1_INPUT));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(3.521, 27.476)), Port::INPUT, module, HoldBase::IN2_INPUT));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(3.521, 35.61)), Port::INPUT, module, HoldBase::IN3_INPUT));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(3.596, 43.969)), Port::INPUT, module, HoldBase::IN4_INPUT));

		addOutput(Port::create<PJ301MPort>(mm2px(Vec(15.423, 19.176)), Port::OUTPUT, module, HoldBase::OUT1_OUTPUT));
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(15.58, 27.476)), Port::OUTPUT, module, HoldBase::OUT2_OUTPUT));
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(15.279, 35.836)), Port::OUTPUT, module, HoldBase::OUT3_OUTPUT));
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(15.279, 43.743)), Port::OUTPUT, module, HoldBase::OUT4_OUTPUT));
}};
