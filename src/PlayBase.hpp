#include "Template.hpp"

struct PlayBase : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		TRIG_INPUT,
		CV_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};
	enum CustomIds {
		C_CUSTOM,
		CS_CUSTOM,
		D_CUSTOM,
		DS_CUSTOM,
		E_CUSTOM,
		F_CUSTOM,
		FS_CUSTOM,
		G_CUSTOM,
		GS_CUSTOM,
		A_CUSTOM,
		AS_CUSTOM,
		RECT874_CUSTOM,
		B_CUSTOM,
		C2_CUSTOM,
		OCTDOWN_CUSTOM,
		TRANSUP_CUSTOM,
		OCTUP_CUSTOM,
		TRANSDOWN_CUSTOM,
		NUM_CUSTOMS
	};
	static Vec customs[NUM_CUSTOMS];

	PlayBase() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
};

struct PlayBaseWidget : ModuleWidget {
	PlayBaseWidget(PlayBase *m) : ModuleWidget(m) {
		setPanel(SVG::load(assetPlugin(plugin, "res/PlayBase.svg")));

		addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 365)));

		addInput(Port::create<PJ301MPort>(mm2px(Vec(6.531, 88.01)), Port::INPUT, module, PlayBase::TRIG_INPUT));
		addInput(Port::create<PJ301MPort>(mm2px(Vec(14.815, 88.01)), Port::INPUT, module, PlayBase::CV_INPUT));
}};

Vec PlayBase::customs[] = {
	mm2px(Vec(3.368, 12.097)),
	mm2px(Vec(14.815, 16.088)),
	mm2px(Vec(3.217, 20.983)),
	mm2px(Vec(14.74, 25.577)),
	mm2px(Vec(3.217, 29.343)),
	mm2px(Vec(3.217, 37.627)),
	mm2px(Vec(13.685, 41.769)),
	mm2px(Vec(3.368, 49.15)),
	mm2px(Vec(13.384, 53.894)),
	mm2px(Vec(3.594, 61.576)),
	mm2px(Vec(13.836, 64.815)),
	mm2px(Vec(3.368, 72.346)),
	mm2px(Vec(3.368, 72.346)),
	mm2px(Vec(3.217, 81.534)),
	mm2px(Vec(1.41, 94.487)),
	mm2px(Vec(18.748, 94.487)),
	mm2px(Vec(7.284, 94.638)),
	mm2px(Vec(12.941, 94.638)),
};
