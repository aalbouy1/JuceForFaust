#include <math.h>
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"

using std::max;
using std::min;

/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2006"
license: "BSD"
name: "dbmeter"
version: "1.0"
Code generated with Faust 2.0.a51 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

#include <math.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
	
  private:
	
	int iConst8;
	int iConst7;
	int iConst6;
	int iConst5;
	int iConst4;
	int iConst3;
	int iConst2;
	int iConst1;
	int fSamplingFreq;
	float fRec0[2];
	float fRec1[2];
	float fRec2[2];
	float fRec3[2];
	float fRec4[2];
	float fRec5[2];
	float fRec6[2];
	float fRec7[2];
	float fConst0;
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT fVbargraph7;
	
  public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("license", "BSD");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("name", "dbmeter");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 8;
		
	}
	virtual int getNumOutputs() {
		return 8;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (80.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		iConst1 = 0;
		iConst2 = 0;
		iConst3 = 0;
		iConst4 = 0;
		iConst5 = 0;
		iConst6 = 0;
		iConst7 = 0;
		iConst8 = 0;
		
	}
	
	virtual void instanceResetUserInterface() {
		
	}
	
	virtual void instanceClear() {
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			fRec0[i0] = 0.0f;
			
		}
		for (int i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			fRec1[i1] = 0.0f;
			
		}
		for (int i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			fRec2[i2] = 0.0f;
			
		}
		for (int i3 = 0; (i3 < 2); i3 = (i3 + 1)) {
			fRec3[i3] = 0.0f;
			
		}
		for (int i4 = 0; (i4 < 2); i4 = (i4 + 1)) {
			fRec4[i4] = 0.0f;
			
		}
		for (int i5 = 0; (i5 < 2); i5 = (i5 + 1)) {
			fRec5[i5] = 0.0f;
			
		}
		for (int i6 = 0; (i6 < 2); i6 = (i6 + 1)) {
			fRec6[i6] = 0.0f;
			
		}
		for (int i7 = 0; (i7 < 2); i7 = (i7 + 1)) {
			fRec7[i7] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openHorizontalBox("8 channels dB meter");
		ui_interface->openVerticalBox("0");
		ui_interface->declare(&fVbargraph0, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffe607389c0", &fVbargraph0, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("1");
		ui_interface->declare(&fVbargraph1, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffe6073d0a0", &fVbargraph1, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("2");
		ui_interface->declare(&fVbargraph2, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffe60741780", &fVbargraph2, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("3");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffe60745f10", &fVbargraph3, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("4");
		ui_interface->declare(&fVbargraph4, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffe6074a750", &fVbargraph4, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("5");
		ui_interface->declare(&fVbargraph5, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffe6074f040", &fVbargraph5, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("6");
		ui_interface->declare(&fVbargraph6, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffe607539e0", &fVbargraph6, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("7");
		ui_interface->declare(&fVbargraph7, "unit", "dB");
		ui_interface->addVerticalBargraph("0x7ffe60758430", &fVbargraph7, -70.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* input3 = inputs[3];
		FAUSTFLOAT* input4 = inputs[4];
		FAUSTFLOAT* input5 = inputs[5];
		FAUSTFLOAT* input6 = inputs[6];
		FAUSTFLOAT* input7 = inputs[7];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fRec0[0] = max((fRec0[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp0))))));
			fVbargraph0 = FAUSTFLOAT(fRec0[0]);
			output0[i] = FAUSTFLOAT(iConst1);
			float fTemp1 = float(input1[i]);
			fRec1[0] = max((fRec1[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp1))))));
			fVbargraph1 = FAUSTFLOAT(fRec1[0]);
			output1[i] = FAUSTFLOAT(iConst2);
			float fTemp2 = float(input2[i]);
			fRec2[0] = max((fRec2[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp2))))));
			fVbargraph2 = FAUSTFLOAT(fRec2[0]);
			output2[i] = FAUSTFLOAT(iConst3);
			float fTemp3 = float(input3[i]);
			fRec3[0] = max((fRec3[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp3))))));
			fVbargraph3 = FAUSTFLOAT(fRec3[0]);
			output3[i] = FAUSTFLOAT(iConst4);
			float fTemp4 = float(input4[i]);
			fRec4[0] = max((fRec4[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp4))))));
			fVbargraph4 = FAUSTFLOAT(fRec4[0]);
			output4[i] = FAUSTFLOAT(iConst5);
			float fTemp5 = float(input5[i]);
			fRec5[0] = max((fRec5[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp5))))));
			fVbargraph5 = FAUSTFLOAT(fRec5[0]);
			output5[i] = FAUSTFLOAT(iConst6);
			float fTemp6 = float(input6[i]);
			fRec6[0] = max((fRec6[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp6))))));
			fVbargraph6 = FAUSTFLOAT(fRec6[0]);
			output6[i] = FAUSTFLOAT(iConst7);
			float fTemp7 = float(input7[i]);
			fRec7[0] = max((fRec7[1] - fConst0), min(10.0f, (20.0f * log10f(max(0.000316227757f, fabsf(fTemp7))))));
			fVbargraph7 = FAUSTFLOAT(fRec7[0]);
			output7[i] = FAUSTFLOAT(iConst8);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			
		}
		
	}

	
};


#endif
