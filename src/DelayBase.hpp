#include "Template.hpp"

struct DelayBase : Module {
	enum ParamIds {
		COARSE_PARAM,
		FINE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		I_INPUT,
		SENDIN_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		O_OUTPUT,
		SENDOUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	DelayBase() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
};

void DelayBase::step() {
}

struct DelayBaseWidget : ModuleWidget {
	DelayBaseWidget(DelayBase *m) : ModuleWidget(m) {
		setPanel(SVG::load(assetPlugin(plugin, "res/DelayBase.svg")));

		addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 365)));

		addParam(ParamWidget::create<Davies1900hBlackKnob>(mm2px(Vec(3.443, 43.606)), module, DelayBase::COARSE_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<Davies1900hBlackKnob>(mm2px(Vec(15.423, 43.606)), module, DelayBase::FINE_PARAM, 0.0, 1.0, 0.0));

		addInput(Port::create<PJ301MPort>(mm2px(Vec(3.443, 19.176)), Port::INPUT, module, DelayBase::I_INPUT));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(3.521, 27.476)), Port::INPUT, module, DelayBase::SENDIN_INPUT));

		addOutput(Port::create<PJ301MPort>(mm2px(Vec(15.423, 19.176)), Port::OUTPUT, module, DelayBase::O_OUTPUT));
		addOutput(Port::create<PJ301MPort>(mm2px(Vec(15.58, 27.476)), Port::OUTPUT, module, DelayBase::SENDOUT_OUTPUT));
}};
