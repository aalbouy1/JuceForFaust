#include <math.h>
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"

using std::max;
using std::min;

/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2014"
license: "BSD"
name: "tester2"
version: "1.0"
Code generated with Faust 2.0.a51 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

#include <math.h>


class mydspSIG0 {
	
  private:
	
	int iRec0[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
		
	}
	int getNumOutputsmydspSIG0() {
		return 1;
		
	}
	int getInputRatemydspSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	int getOutputRatemydspSIG0(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	void instanceInitmydspSIG0(int samplingFreq) {
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			iRec0[i0] = 0;
			
		}
		
	}
	
	void fillmydspSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			output[i] = sinf((9.58738019e-05f * float((iRec0[0] + -1))));
			iRec0[1] = iRec0[0];
			
		}
		
	}
};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65537];

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
	
  private:
	
	int fSamplingFreq;
	int iRec3[3];
	float fRec2[3];
	float fRec1[2];
	float fRec4[2];
	float fRec5[2];
	float fRec6[2];
	FAUSTFLOAT fHslider0;
	float fConst0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	
  public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("copyright", "(c)GRAME 2014");
		m->declare("license", "BSD");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("miscoscillator.lib/name", "Faust Oscillator Library");
		m->declare("miscoscillator.lib/version", "0.0");
		m->declare("name", "tester2");
		m->declare("noise.lib/name", "Faust Noise Generator Library");
		m->declare("noise.lib/version", "0.0");
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
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
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(65537, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (1.0f / min(192000.0f, max(1.0f, float(fSamplingFreq))));
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(440.0f);
		fHslider2 = FAUSTFLOAT(-96.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			fRec1[i1] = 0.0f;
			
		}
		for (int i2 = 0; (i2 < 3); i2 = (i2 + 1)) {
			iRec3[i2] = 0;
			
		}
		for (int i3 = 0; (i3 < 3); i3 = (i3 + 1)) {
			fRec2[i3] = 0.0f;
			
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
		ui_interface->openVerticalBox("Stereo Audio Tester");
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("freq", &fHslider1, 440.0f, 40.0f, 20000.0f, 1.0f);
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("volume", &fHslider2, -96.0f, -96.0f, 0.0f, 1.0f);
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->declare(&fHslider0, "style", "menu{'white noise':0;'pink noise':1;'sine':2}");
		ui_interface->addHorizontalSlider("signal", &fHslider0, 0.0f, 0.0f, 2.0f, 1.0f);
		ui_interface->declare(&fHslider3, "4", "");
		ui_interface->declare(&fHslider3, "style", "radio{'none':0;'left':1;'right':2;'both':3}");
		ui_interface->addVerticalSlider("channel", &fHslider3, 0.0f, 0.0f, 3.0f, 1.0f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		int iSlow0 = int(float(fHslider0));
		int iSlow1 = (iSlow0 == 0);
		int iSlow2 = (iSlow0 == 1);
		float fSlow3 = (fConst0 * float(fHslider1));
		float fSlow4 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fHslider2))));
		int iSlow5 = int(float(fHslider3));
		int iSlow6 = ((iSlow5 & 1) != 0);
		int iSlow7 = ((iSlow5 & 2) != 0);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow3 + (fRec1[1] - floorf((fSlow3 + fRec1[1]))));
			float fTemp0 = (65536.0f * fRec1[0]);
			int iTemp1 = int(fTemp0);
			iRec3[0] = ((1103515245 * iRec3[1]) + 12345);
			fRec2[0] = (((2.30852802e-11f * float(iRec3[0])) + ((1.80116081f * fRec2[1]) + (6.90678287e-12f * float(iRec3[2])))) - ((0.802577376f * fRec2[2]) + (2.93626512e-11f * float(iRec3[1]))));
			fRec4[0] = (fSlow4 + (0.999000013f * fRec4[1]));
			float fTemp2 = ((iSlow1?(4.65661287e-10f * float(iRec3[0])):(iSlow2?fRec2[0]:(ftbl0mydspSIG0[iTemp1] + ((fTemp0 - floorf(fTemp0)) * (ftbl0mydspSIG0[(iTemp1 + 1)] - ftbl0mydspSIG0[iTemp1]))))) * fRec4[0]);
			fRec5[0] = ((fRec5[1] < float(iSlow6))?min((fRec5[1] + 0.000226757373f), float(iSlow6)):max((fRec5[1] + -0.000226757373f), float(iSlow6)));
			output0[i] = FAUSTFLOAT((fTemp2 * fRec5[0]));
			fRec6[0] = ((fRec6[1] < float(iSlow7))?min((fRec6[1] + 0.000226757373f), float(iSlow7)):max((fRec6[1] + -0.000226757373f), float(iSlow7)));
			output1[i] = FAUSTFLOAT((fTemp2 * fRec6[0]));
			fRec1[1] = fRec1[0];
			iRec3[2] = iRec3[1];
			iRec3[1] = iRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			
		}
		
	}

	
};


#endif
