#include "Template.hpp"

struct PlayBase : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
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
	Vec custom[NUM_CUSTOMS] = {
		mm2px(Vec(3.217, 14.356)),
		mm2px(Vec(14.664, 18.348)),
		mm2px(Vec(3.066, 23.243)),
		mm2px(Vec(14.589, 27.837)),
		mm2px(Vec(3.066, 31.602)),
		mm2px(Vec(3.066, 39.887)),
		mm2px(Vec(13.535, 44.029)),
		mm2px(Vec(3.217, 51.409)),
		mm2px(Vec(13.233, 56.154)),
		mm2px(Vec(3.443, 63.835)),
		mm2px(Vec(13.685, 67.074)),
		mm2px(Vec(3.217, 74.605)),
		mm2px(Vec(3.217, 74.605)),
		mm2px(Vec(3.066, 83.793)),
		mm2px(Vec(1.41, 94.487)),
		mm2px(Vec(18.748, 94.487)),
		mm2px(Vec(7.284, 94.638)),
		mm2px(Vec(12.941, 94.638)),
	};

	PlayBase() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
};

struct PlayBaseWidget : ModuleWidget {
	PlayBaseWidget(PlayBase *m) : ModuleWidget(m) {
		setPanel(SVG::load(assetPlugin(plugin, "res/PlayBase.svg")));

		addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 365)));
}};
