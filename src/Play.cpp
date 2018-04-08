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

struct NoteButton : PB61303Button {
	PlayModule *parent;
	int offset;
	NoteButton(PlayModule *_parent, int _offset) : parent(_parent), offset(_offset) {}
	void onAction(EventAction &e) {
		// TODO
	}
};

struct PlayWidget : PlayBaseWidget {
	PlayWidget(PlayModule *m) : PlayBaseWidget(m) {
		const int NUM_NOTES = 13;
		PlayBase::CustomIds notes[NUM_NOTES] = {
			PlayBase::C_CUSTOM,
			PlayBase::CS_CUSTOM,
			PlayBase::D_CUSTOM,
			PlayBase::DS_CUSTOM,
			PlayBase::E_CUSTOM,
			PlayBase::F_CUSTOM,
			PlayBase::FS_CUSTOM,
			PlayBase::G_CUSTOM,
			PlayBase::GS_CUSTOM,
			PlayBase::A_CUSTOM,
			PlayBase::AS_CUSTOM,
			PlayBase::B_CUSTOM,
			PlayBase::C2_CUSTOM
		};
		for(int c = 0; c < NUM_NOTES; c++) {
			NoteButton *button = new NoteButton(m, c);
			button->box.pos = PlayBase::customs[notes[c]];
			addChild(button);
		}
	}
};

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelPlay = Model::create<PlayModule, PlayWidget>("Dryad Technology", "MiniPiano_1oct", "Play", OSCILLATOR_TAG);
