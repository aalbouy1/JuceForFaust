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
name: "karplus32"
version: "1.0"
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
	int IOTA;
	int iRec1[2];
	float fVec3[4096];
	float fVec4[4096];
	float fVec5[4096];
	float fVec6[4096];
	float fVec7[4096];
	float fVec8[4096];
	float fVec9[4096];
	float fVec10[4096];
	float fVec11[4096];
	float fVec12[4096];
	float fVec13[4096];
	float fVec14[4096];
	float fVec15[4096];
	float fVec16[4096];
	float fVec19[4096];
	float fVec20[4096];
	float fVec21[4096];
	float fVec22[4096];
	float fVec23[4096];
	float fVec24[4096];
	float fVec25[4096];
	float fVec26[4096];
	float fVec27[4096];
	float fVec28[4096];
	float fVec29[4096];
	float fVec30[4096];
	float fVec31[4096];
	float fVec32[4096];
	float fVec2[2048];
	float fVec18[2048];
	float fVec17[1024];
	float fVec1[512];
	float fRec0[3];
	float fRec3[3];
	float fRec4[3];
	float fRec5[3];
	float fRec6[3];
	float fRec7[3];
	float fRec8[3];
	float fRec9[3];
	float fRec10[3];
	float fRec11[3];
	float fRec12[3];
	float fRec13[3];
	float fRec14[3];
	float fRec15[3];
	float fRec16[3];
	float fRec17[3];
	float fRec18[3];
	float fRec19[3];
	float fRec20[3];
	float fRec21[3];
	float fRec22[3];
	float fRec23[3];
	float fRec24[3];
	float fRec25[3];
	float fRec26[3];
	float fRec27[3];
	float fRec28[3];
	float fRec29[3];
	float fRec30[3];
	float fRec31[3];
	float fRec32[3];
	float fRec33[3];
	float fVec0[2];
	float fRec2[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	
  public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Grame");
		m->declare("copyright", "(c)GRAME 2006");
		m->declare("license", "BSD");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It might be removed in future released.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "karplus32");
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
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(0.10000000000000001f);
		fHslider3 = FAUSTFLOAT(0.5f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(128.0f);
		fHslider5 = FAUSTFLOAT(128.0f);
		fHslider6 = FAUSTFLOAT(32.0f);
		
	}
	
	virtual void instanceClear() {
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			iRec1[i0] = 0;
			
		}
		for (int i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			fVec0[i1] = 0.0f;
			
		}
		for (int i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			fRec2[i2] = 0.0f;
			
		}
		IOTA = 0;
		for (int i3 = 0; (i3 < 512); i3 = (i3 + 1)) {
			fVec1[i3] = 0.0f;
			
		}
		for (int i4 = 0; (i4 < 3); i4 = (i4 + 1)) {
			fRec0[i4] = 0.0f;
			
		}
		for (int i5 = 0; (i5 < 2048); i5 = (i5 + 1)) {
			fVec2[i5] = 0.0f;
			
		}
		for (int i6 = 0; (i6 < 3); i6 = (i6 + 1)) {
			fRec3[i6] = 0.0f;
			
		}
		for (int i7 = 0; (i7 < 4096); i7 = (i7 + 1)) {
			fVec3[i7] = 0.0f;
			
		}
		for (int i8 = 0; (i8 < 3); i8 = (i8 + 1)) {
			fRec4[i8] = 0.0f;
			
		}
		for (int i9 = 0; (i9 < 4096); i9 = (i9 + 1)) {
			fVec4[i9] = 0.0f;
			
		}
		for (int i10 = 0; (i10 < 3); i10 = (i10 + 1)) {
			fRec5[i10] = 0.0f;
			
		}
		for (int i11 = 0; (i11 < 4096); i11 = (i11 + 1)) {
			fVec5[i11] = 0.0f;
			
		}
		for (int i12 = 0; (i12 < 3); i12 = (i12 + 1)) {
			fRec6[i12] = 0.0f;
			
		}
		for (int i13 = 0; (i13 < 4096); i13 = (i13 + 1)) {
			fVec6[i13] = 0.0f;
			
		}
		for (int i14 = 0; (i14 < 3); i14 = (i14 + 1)) {
			fRec7[i14] = 0.0f;
			
		}
		for (int i15 = 0; (i15 < 4096); i15 = (i15 + 1)) {
			fVec7[i15] = 0.0f;
			
		}
		for (int i16 = 0; (i16 < 3); i16 = (i16 + 1)) {
			fRec8[i16] = 0.0f;
			
		}
		for (int i17 = 0; (i17 < 4096); i17 = (i17 + 1)) {
			fVec8[i17] = 0.0f;
			
		}
		for (int i18 = 0; (i18 < 3); i18 = (i18 + 1)) {
			fRec9[i18] = 0.0f;
			
		}
		for (int i19 = 0; (i19 < 4096); i19 = (i19 + 1)) {
			fVec9[i19] = 0.0f;
			
		}
		for (int i20 = 0; (i20 < 3); i20 = (i20 + 1)) {
			fRec10[i20] = 0.0f;
			
		}
		for (int i21 = 0; (i21 < 4096); i21 = (i21 + 1)) {
			fVec10[i21] = 0.0f;
			
		}
		for (int i22 = 0; (i22 < 3); i22 = (i22 + 1)) {
			fRec11[i22] = 0.0f;
			
		}
		for (int i23 = 0; (i23 < 4096); i23 = (i23 + 1)) {
			fVec11[i23] = 0.0f;
			
		}
		for (int i24 = 0; (i24 < 3); i24 = (i24 + 1)) {
			fRec12[i24] = 0.0f;
			
		}
		for (int i25 = 0; (i25 < 4096); i25 = (i25 + 1)) {
			fVec12[i25] = 0.0f;
			
		}
		for (int i26 = 0; (i26 < 3); i26 = (i26 + 1)) {
			fRec13[i26] = 0.0f;
			
		}
		for (int i27 = 0; (i27 < 4096); i27 = (i27 + 1)) {
			fVec13[i27] = 0.0f;
			
		}
		for (int i28 = 0; (i28 < 3); i28 = (i28 + 1)) {
			fRec14[i28] = 0.0f;
			
		}
		for (int i29 = 0; (i29 < 4096); i29 = (i29 + 1)) {
			fVec14[i29] = 0.0f;
			
		}
		for (int i30 = 0; (i30 < 3); i30 = (i30 + 1)) {
			fRec15[i30] = 0.0f;
			
		}
		for (int i31 = 0; (i31 < 4096); i31 = (i31 + 1)) {
			fVec15[i31] = 0.0f;
			
		}
		for (int i32 = 0; (i32 < 3); i32 = (i32 + 1)) {
			fRec16[i32] = 0.0f;
			
		}
		for (int i33 = 0; (i33 < 4096); i33 = (i33 + 1)) {
			fVec16[i33] = 0.0f;
			
		}
		for (int i34 = 0; (i34 < 3); i34 = (i34 + 1)) {
			fRec17[i34] = 0.0f;
			
		}
		for (int i35 = 0; (i35 < 1024); i35 = (i35 + 1)) {
			fVec17[i35] = 0.0f;
			
		}
		for (int i36 = 0; (i36 < 3); i36 = (i36 + 1)) {
			fRec18[i36] = 0.0f;
			
		}
		for (int i37 = 0; (i37 < 2048); i37 = (i37 + 1)) {
			fVec18[i37] = 0.0f;
			
		}
		for (int i38 = 0; (i38 < 3); i38 = (i38 + 1)) {
			fRec19[i38] = 0.0f;
			
		}
		for (int i39 = 0; (i39 < 4096); i39 = (i39 + 1)) {
			fVec19[i39] = 0.0f;
			
		}
		for (int i40 = 0; (i40 < 3); i40 = (i40 + 1)) {
			fRec20[i40] = 0.0f;
			
		}
		for (int i41 = 0; (i41 < 4096); i41 = (i41 + 1)) {
			fVec20[i41] = 0.0f;
			
		}
		for (int i42 = 0; (i42 < 3); i42 = (i42 + 1)) {
			fRec21[i42] = 0.0f;
			
		}
		for (int i43 = 0; (i43 < 4096); i43 = (i43 + 1)) {
			fVec21[i43] = 0.0f;
			
		}
		for (int i44 = 0; (i44 < 3); i44 = (i44 + 1)) {
			fRec22[i44] = 0.0f;
			
		}
		for (int i45 = 0; (i45 < 4096); i45 = (i45 + 1)) {
			fVec22[i45] = 0.0f;
			
		}
		for (int i46 = 0; (i46 < 3); i46 = (i46 + 1)) {
			fRec23[i46] = 0.0f;
			
		}
		for (int i47 = 0; (i47 < 4096); i47 = (i47 + 1)) {
			fVec23[i47] = 0.0f;
			
		}
		for (int i48 = 0; (i48 < 3); i48 = (i48 + 1)) {
			fRec24[i48] = 0.0f;
			
		}
		for (int i49 = 0; (i49 < 4096); i49 = (i49 + 1)) {
			fVec24[i49] = 0.0f;
			
		}
		for (int i50 = 0; (i50 < 3); i50 = (i50 + 1)) {
			fRec25[i50] = 0.0f;
			
		}
		for (int i51 = 0; (i51 < 4096); i51 = (i51 + 1)) {
			fVec25[i51] = 0.0f;
			
		}
		for (int i52 = 0; (i52 < 3); i52 = (i52 + 1)) {
			fRec26[i52] = 0.0f;
			
		}
		for (int i53 = 0; (i53 < 4096); i53 = (i53 + 1)) {
			fVec26[i53] = 0.0f;
			
		}
		for (int i54 = 0; (i54 < 3); i54 = (i54 + 1)) {
			fRec27[i54] = 0.0f;
			
		}
		for (int i55 = 0; (i55 < 4096); i55 = (i55 + 1)) {
			fVec27[i55] = 0.0f;
			
		}
		for (int i56 = 0; (i56 < 3); i56 = (i56 + 1)) {
			fRec28[i56] = 0.0f;
			
		}
		for (int i57 = 0; (i57 < 4096); i57 = (i57 + 1)) {
			fVec28[i57] = 0.0f;
			
		}
		for (int i58 = 0; (i58 < 3); i58 = (i58 + 1)) {
			fRec29[i58] = 0.0f;
			
		}
		for (int i59 = 0; (i59 < 4096); i59 = (i59 + 1)) {
			fVec29[i59] = 0.0f;
			
		}
		for (int i60 = 0; (i60 < 3); i60 = (i60 + 1)) {
			fRec30[i60] = 0.0f;
			
		}
		for (int i61 = 0; (i61 < 4096); i61 = (i61 + 1)) {
			fVec30[i61] = 0.0f;
			
		}
		for (int i62 = 0; (i62 < 3); i62 = (i62 + 1)) {
			fRec31[i62] = 0.0f;
			
		}
		for (int i63 = 0; (i63 < 4096); i63 = (i63 + 1)) {
			fVec31[i63] = 0.0f;
			
		}
		for (int i64 = 0; (i64 < 3); i64 = (i64 + 1)) {
			fRec32[i64] = 0.0f;
			
		}
		for (int i65 = 0; (i65 < 4096); i65 = (i65 + 1)) {
			fVec32[i65] = 0.0f;
			
		}
		for (int i66 = 0; (i66 < 3); i66 = (i66 + 1)) {
			fRec33[i66] = 0.0f;
			
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
		ui_interface->openVerticalBox("karplus32");
		ui_interface->openVerticalBox("excitator");
		ui_interface->addHorizontalSlider("excitation (samples)", &fHslider4, 128.0f, 2.0f, 512.0f, 1.0f);
		ui_interface->addButton("play",&fButton0);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("noise generator");
		ui_interface->addHorizontalSlider("level", &fHslider3, 0.5f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("output volume", &fHslider0, 0.5f, 0.0f, 1.0f, 0.100000001f);
		ui_interface->openVerticalBox("resonator x32");
		ui_interface->addHorizontalSlider("attenuation", &fHslider2, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("detune", &fHslider6, 32.0f, 0.0f, 512.0f, 1.0f);
		ui_interface->addHorizontalSlider("duration (samples)", &fHslider5, 128.0f, 2.0f, 512.0f, 1.0f);
		ui_interface->addHorizontalSlider("polyphony", &fHslider1, 1.0f, 0.0f, 32.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = float(fHslider1);
		int iSlow2 = (fSlow1 > 0.0f);
		float fSlow3 = (0.5f * (1.0f - float(fHslider2)));
		float fSlow4 = (4.65661287e-10f * float(fHslider3));
		float fSlow5 = float(fButton0);
		float fSlow6 = (1.0f / float(fHslider4));
		float fSlow7 = float(fHslider5);
		int iSlow8 = (int((fSlow7 + -1.5f)) & 4095);
		int iSlow9 = (fSlow1 > 2.0f);
		float fSlow10 = float(fHslider6);
		int iSlow11 = (int(((fSlow7 + (2.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow12 = (fSlow1 > 4.0f);
		int iSlow13 = (int(((fSlow7 + (4.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow14 = (fSlow1 > 6.0f);
		int iSlow15 = (int(((fSlow7 + (6.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow16 = (fSlow1 > 8.0f);
		int iSlow17 = (int(((fSlow7 + (8.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow18 = (fSlow1 > 10.0f);
		int iSlow19 = (int(((fSlow7 + (10.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow20 = (fSlow1 > 12.0f);
		int iSlow21 = (int(((fSlow7 + (12.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow22 = (fSlow1 > 14.0f);
		int iSlow23 = (int(((fSlow7 + (14.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow24 = (fSlow1 > 16.0f);
		int iSlow25 = (int(((fSlow7 + (16.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow26 = (fSlow1 > 18.0f);
		int iSlow27 = (int(((fSlow7 + (18.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow28 = (fSlow1 > 20.0f);
		int iSlow29 = (int(((fSlow7 + (20.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow30 = (fSlow1 > 22.0f);
		int iSlow31 = (int(((fSlow7 + (22.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow32 = (fSlow1 > 24.0f);
		int iSlow33 = (int(((fSlow7 + (24.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow34 = (fSlow1 > 26.0f);
		int iSlow35 = (int(((fSlow7 + (26.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow36 = (fSlow1 > 28.0f);
		int iSlow37 = (int(((fSlow7 + (28.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow38 = (fSlow1 > 30.0f);
		int iSlow39 = (int(((fSlow7 + (30.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow40 = (fSlow1 > 1.0f);
		int iSlow41 = (int(((fSlow7 + fSlow10) + -1.5f)) & 4095);
		int iSlow42 = (fSlow1 > 3.0f);
		int iSlow43 = (int(((fSlow7 + (3.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow44 = (fSlow1 > 5.0f);
		int iSlow45 = (int(((fSlow7 + (5.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow46 = (fSlow1 > 7.0f);
		int iSlow47 = (int(((fSlow7 + (7.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow48 = (fSlow1 > 9.0f);
		int iSlow49 = (int(((fSlow7 + (9.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow50 = (fSlow1 > 11.0f);
		int iSlow51 = (int(((fSlow7 + (11.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow52 = (fSlow1 > 13.0f);
		int iSlow53 = (int(((fSlow7 + (13.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow54 = (fSlow1 > 15.0f);
		int iSlow55 = (int(((fSlow7 + (15.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow56 = (fSlow1 > 17.0f);
		int iSlow57 = (int(((fSlow7 + (17.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow58 = (fSlow1 > 19.0f);
		int iSlow59 = (int(((fSlow7 + (19.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow60 = (fSlow1 > 21.0f);
		int iSlow61 = (int(((fSlow7 + (21.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow62 = (fSlow1 > 23.0f);
		int iSlow63 = (int(((fSlow7 + (23.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow64 = (fSlow1 > 25.0f);
		int iSlow65 = (int(((fSlow7 + (25.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow66 = (fSlow1 > 27.0f);
		int iSlow67 = (int(((fSlow7 + (27.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow68 = (fSlow1 > 29.0f);
		int iSlow69 = (int(((fSlow7 + (29.0f * fSlow10)) + -1.5f)) & 4095);
		int iSlow70 = (fSlow1 > 31.0f);
		int iSlow71 = (int(((fSlow7 + (31.0f * fSlow10)) + -1.5f)) & 4095);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec1[0] = ((1103515245 * iRec1[1]) + 12345);
			fVec0[0] = fSlow5;
			fRec2[0] = ((float(((fSlow5 - fVec0[1]) > 0.0f)) + fRec2[1]) - (fSlow6 * float((fRec2[1] > 0.0f))));
			float fTemp0 = (fSlow4 * (float(iRec1[0]) * (float((fRec2[0] > 0.0f)) + 1.52587891e-05f)));
			fVec1[(IOTA & 511)] = ((fSlow3 * (fRec0[1] + fRec0[2])) + fTemp0);
			fRec0[0] = fVec1[((IOTA - iSlow8) & 511)];
			fVec2[(IOTA & 2047)] = (fTemp0 + (fSlow3 * (fRec3[1] + fRec3[2])));
			fRec3[0] = fVec2[((IOTA - iSlow11) & 2047)];
			fVec3[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec4[1] + fRec4[2])));
			fRec4[0] = fVec3[((IOTA - iSlow13) & 4095)];
			fVec4[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec5[1] + fRec5[2])));
			fRec5[0] = fVec4[((IOTA - iSlow15) & 4095)];
			fVec5[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec6[1] + fRec6[2])));
			fRec6[0] = fVec5[((IOTA - iSlow17) & 4095)];
			fVec6[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec7[1] + fRec7[2])));
			fRec7[0] = fVec6[((IOTA - iSlow19) & 4095)];
			fVec7[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec8[1] + fRec8[2])));
			fRec8[0] = fVec7[((IOTA - iSlow21) & 4095)];
			fVec8[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec9[1] + fRec9[2])));
			fRec9[0] = fVec8[((IOTA - iSlow23) & 4095)];
			fVec9[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec10[1] + fRec10[2])));
			fRec10[0] = fVec9[((IOTA - iSlow25) & 4095)];
			fVec10[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec11[1] + fRec11[2])));
			fRec11[0] = fVec10[((IOTA - iSlow27) & 4095)];
			fVec11[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec12[1] + fRec12[2])));
			fRec12[0] = fVec11[((IOTA - iSlow29) & 4095)];
			fVec12[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec13[1] + fRec13[2])));
			fRec13[0] = fVec12[((IOTA - iSlow31) & 4095)];
			fVec13[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec14[1] + fRec14[2])));
			fRec14[0] = fVec13[((IOTA - iSlow33) & 4095)];
			fVec14[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec15[1] + fRec15[2])));
			fRec15[0] = fVec14[((IOTA - iSlow35) & 4095)];
			fVec15[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec16[1] + fRec16[2])));
			fRec16[0] = fVec15[((IOTA - iSlow37) & 4095)];
			fVec16[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec17[1] + fRec17[2])));
			fRec17[0] = fVec16[((IOTA - iSlow39) & 4095)];
			output0[i] = FAUSTFLOAT((fSlow0 * ((((((((((((((((float(iSlow2) * fRec0[0]) + (float(iSlow9) * fRec3[0])) + (float(iSlow12) * fRec4[0])) + (float(iSlow14) * fRec5[0])) + (float(iSlow16) * fRec6[0])) + (float(iSlow18) * fRec7[0])) + (float(iSlow20) * fRec8[0])) + (float(iSlow22) * fRec9[0])) + (float(iSlow24) * fRec10[0])) + (float(iSlow26) * fRec11[0])) + (float(iSlow28) * fRec12[0])) + (float(iSlow30) * fRec13[0])) + (float(iSlow32) * fRec14[0])) + (float(iSlow34) * fRec15[0])) + (float(iSlow36) * fRec16[0])) + (float(iSlow38) * fRec17[0]))));
			fVec17[(IOTA & 1023)] = (fTemp0 + (fSlow3 * (fRec18[1] + fRec18[2])));
			fRec18[0] = fVec17[((IOTA - iSlow41) & 1023)];
			fVec18[(IOTA & 2047)] = (fTemp0 + (fSlow3 * (fRec19[1] + fRec19[2])));
			fRec19[0] = fVec18[((IOTA - iSlow43) & 2047)];
			fVec19[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec20[1] + fRec20[2])));
			fRec20[0] = fVec19[((IOTA - iSlow45) & 4095)];
			fVec20[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec21[1] + fRec21[2])));
			fRec21[0] = fVec20[((IOTA - iSlow47) & 4095)];
			fVec21[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec22[1] + fRec22[2])));
			fRec22[0] = fVec21[((IOTA - iSlow49) & 4095)];
			fVec22[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec23[1] + fRec23[2])));
			fRec23[0] = fVec22[((IOTA - iSlow51) & 4095)];
			fVec23[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec24[1] + fRec24[2])));
			fRec24[0] = fVec23[((IOTA - iSlow53) & 4095)];
			fVec24[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec25[1] + fRec25[2])));
			fRec25[0] = fVec24[((IOTA - iSlow55) & 4095)];
			fVec25[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec26[1] + fRec26[2])));
			fRec26[0] = fVec25[((IOTA - iSlow57) & 4095)];
			fVec26[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec27[1] + fRec27[2])));
			fRec27[0] = fVec26[((IOTA - iSlow59) & 4095)];
			fVec27[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec28[1] + fRec28[2])));
			fRec28[0] = fVec27[((IOTA - iSlow61) & 4095)];
			fVec28[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec29[1] + fRec29[2])));
			fRec29[0] = fVec28[((IOTA - iSlow63) & 4095)];
			fVec29[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec30[1] + fRec30[2])));
			fRec30[0] = fVec29[((IOTA - iSlow65) & 4095)];
			fVec30[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec31[1] + fRec31[2])));
			fRec31[0] = fVec30[((IOTA - iSlow67) & 4095)];
			fVec31[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec32[1] + fRec32[2])));
			fRec32[0] = fVec31[((IOTA - iSlow69) & 4095)];
			fVec32[(IOTA & 4095)] = (fTemp0 + (fSlow3 * (fRec33[1] + fRec33[2])));
			fRec33[0] = fVec32[((IOTA - iSlow71) & 4095)];
			output1[i] = FAUSTFLOAT((fSlow0 * ((((((((((((((((float(iSlow40) * fRec18[0]) + (float(iSlow42) * fRec19[0])) + (float(iSlow44) * fRec20[0])) + (float(iSlow46) * fRec21[0])) + (float(iSlow48) * fRec22[0])) + (float(iSlow50) * fRec23[0])) + (float(iSlow52) * fRec24[0])) + (float(iSlow54) * fRec25[0])) + (float(iSlow56) * fRec26[0])) + (float(iSlow58) * fRec27[0])) + (float(iSlow60) * fRec28[0])) + (float(iSlow62) * fRec29[0])) + (float(iSlow64) * fRec30[0])) + (float(iSlow66) * fRec31[0])) + (float(iSlow68) * fRec32[0])) + (float(iSlow70) * fRec33[0]))));
			iRec1[1] = iRec1[0];
			fVec0[1] = fVec0[0];
			fRec2[1] = fRec2[0];
			IOTA = (IOTA + 1);
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			
		}
		
	}

	
};


#endif
