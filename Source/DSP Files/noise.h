#include <math.h>
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"

using std::max;
using std::min;

/* ------------------------------------------------------------
author: "Grame"
copyright: "(c)GRAME 2009"
license: "BSD"
name: "Noise"
version: "1.1"
Code generated with Faust 2.0.a51 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  



#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
	
  private:
	
	int fSamplingFreq;
	int iRec0[2];
	FAUSTFLOAT fVslider0;
	
  public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("copyright", "(c)GRAME 2009");
		m->declare("license", "BSD");
		m->declare("name", "Noise");
		m->declare("version", "1.1");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
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
		
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.20000000000000001f);
		
	}
	
	virtual void instanceClear() {
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			iRec0[i0] = 0;
			
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
        ui_interface->openHorizontalBox("0x11");
		ui_interface->openVerticalBox("0x00");
        ui_interface->declare(&fVslider0, "style", "knob");
        ui_interface->addVerticalSlider("Volume", &fVslider0, 0.200000003f, 0.0f, 1.0f, 0.001f);
        ui_interface->addHorizontalBargraph("0x", &fVslider0, 0.0f, 1.0f);
		ui_interface->closeBox();
        ui_interface->openVerticalBox("0x22");
        ui_interface->addVerticalBargraph("0x", &fVslider0, 0.0f, 1.0f);
        ui_interface->closeBox();
        ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (4.65661287e-10f * float(fVslider0));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = ((1103515245 * iRec0[1]) + 12345);
			output0[i] = FAUSTFLOAT((fSlow0 * float(iRec0[0])));
			iRec0[1] = iRec0[0];
			
		}
		
	}

	
};


#endif
