# panel2source.py
# for exporting SVG panels to VCV plugin source files
# Version: 1
# Support contact email: /dev/null
# License: CC-BY-SA on the single line below preceded by a stackoverflow link. Otherwise CC0


import sys
import os
import re
import xml.etree.ElementTree


help = """usage: python panel2source.py SVGFILE > source.cpp

This hacky script converts an .svg panel file to a C++ source file to create VCV module.

The panel must be set up in a very specific way using Inkscape.
1. Create a layer called "widgets". You may make it invisible when saving. This script will still read them.
2. In that layer, create a rectangle for every widget. Set the fill color accordingly. Alpha is ignored.
	- params: red #ff0000
	- inputs: green #00ff00
	- outputs: blue #0000ff
	- lights: magenta #ff00ff
3. The top-left position of the rectangle is what matters. Size doesn't, however you may want to match it to the size of the widget for alignment purposes.
4. Set the ID of the element with the enum the widget will refer to, excluding _PARAM, etc.
5. Run the script, and an entire C++ file will be generated on stdout which is a better starting point than nothing at all.
"""

def eprint(*args, **kwargs):
	print(*args, file=sys.stderr, **kwargs)

if len(sys.argv) < 2:
	eprint(help)
	exit()

def slugize(name):
	if name[0].isdigit():
		return "_" + name
	return name

dpi = 75
scale = 1
# scale = dpi / 25.4
filename = sys.argv[1]

basename = os.path.basename(filename)
slug = slugize(os.path.splitext(basename)[0])
eprint("slug: %s" % slug)


tree = xml.etree.ElementTree.parse(filename)

root = tree.getroot()
width = root.get('width')
height = root.get('height')
# width = float(re.findall('[\d.]+', width)[0])
# height = float(re.findall('[\d.]+', height)[0])
# width *= dpi
# height *= dpi
# hp = round(width / 15)
eprint("width: %s" % width)
eprint("height: %s" % height)
# eprint("hp: %d" % hp)


# Find widgets in tree

params = []
inputs = []
outputs = []
lights = []

groups = root.findall(".//{http://www.w3.org/2000/svg}g")
eprint("Found %d groups" % len(groups))
for group in groups:
	label = group.get("{http://www.inkscape.org/namespaces/inkscape}label")
	if label is None:
		label = group.get('id')
	if label == 'widgets':
		rects = group.findall(".//{http://www.w3.org/2000/svg}rect")
		eprint("Found %d rects in layer called widgets" % len(rects))
		for rect in rects:
			label = rect.get('{http://www.inkscape.org/namespaces/inkscape}label')
			if label is None:
				label = rect.get('id')
			id = slugize(label).upper()
			style = rect.get('style')
			color_match = re.search(r'fill:\s*#(.{6})\s*;', style)
			if color_match:
				color = color_match.group(1)
				# Source: https://stackoverflow.com/a/29643643 . 
				color_triplet = tuple(int(color[i:i+2], 16) for i in (0, 2 ,4))
			else:
				color_match = re.search(r'fill:\s*rgb\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)\s*;', style)
				if color_match:
					color_triplet = (int(color_match.group(1)), int(color_match.group(2)), int(color_match.group(3)))
			if color_triplet:
				x = float(rect.get('x')) * scale
				y = float(rect.get('y')) * scale
				x = round(x, 3)
				y = round(y, 3)
				widget = {'id': id, 'x': x, 'y': y, 'color': color_triplet}
				eprint(widget)
				if color_triplet == (255, 0, 0): # Red
					params.append(widget)
				if color_triplet == (0, 255, 0): # Green
					inputs.append(widget)
				if color_triplet == (0, 0, 255): # Blue
					outputs.append(widget)
				if color_triplet == (255, 0, 255): # Magenta
					lights.append(widget)

params = sorted(params, key=lambda widget: widget['y'])
inputs = sorted(inputs, key=lambda widget: widget['y'])
outputs = sorted(outputs, key=lambda widget: widget['y'])
lights = sorted(lights, key=lambda widget: widget['y'])


# Print output

print("""\
#include "Template.hpp"

struct %s : Module {\
""" % (slug))

# Params
print("	enum ParamIds {")
for w in params:
	print("		%s_PARAM," % w['id'])
print("		NUM_PARAMS")
print("	};")

# Inputs
print("	enum InputIds {")
for w in inputs:
	print("		%s_INPUT," % w['id'])
print("		NUM_INPUTS")
print("	};")

# Outputs
print("	enum OutputIds {")
for w in outputs:
	print("		%s_OUTPUT," % w['id'])
print("		NUM_OUTPUTS")
print("	};")

# Lights
print("	enum LightIds {")
for w in lights:
	print("		%s_LIGHT," % w['id'])
print("		NUM_LIGHTS")
print("	};")


print("""
	%s() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
};

void %s::step() {
}

struct %sWidget : ModuleWidget {
	%sWidget(%s *m) : ModuleWidget(m) {
		setPanel(SVG::load(assetPlugin(plugin, "res/%s")));

		addChild(Widget::create<ScrewSilver>(Vec(15, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(15, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 30, 365)));\
""" % (slug, slug, slug, slug, slug, basename))


# Params
if len(params) > 0:
	print("")
for w in params:
	print("		addParam(createParam<Davies1900hBlackKnob>(mm2px(Vec(%g, %g)), module, %s::%s_PARAM, 0.0, 1.0, 0.0));" % (w['x'], w['y'], slug, w['id']))

# Inputs
if len(inputs) > 0:
	print("")
for w in inputs:
	print("		addInput(createInput<PJ301MPort>(mm2px(Vec(%g, %g)), module, %s::%s_INPUT));" % (w['x'], w['y'], slug, w['id']))

# Outputs
if len(outputs) > 0:
	print("")
for w in outputs:
	print("		addOutput(createOutput<PJ301MPort>(mm2px(Vec(%g, %g)), module, %s::%s_OUTPUT));" % (w['x'], w['y'], slug, w['id']))

# Lights
if len(lights) > 0:
	print("")
for w in lights:
	print("		addChild(createLight<RedLight>(mm2px(Vec(%g, %g)), module, %s::%s_LIGHT));" % (w['x'], w['y'], slug, w['id']))


print("}};")
