#include <math.h>
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"

using std::max;
using std::min;

/* ------------------------------------------------------------
author: "Yann Orlarey"
name: "Kisana"
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
		
	}
	
	void fillmydspSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			output[i] = 0.0f;
			
		}
		
	}
};

mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
	
  private:
	
	int IOTA;
	int iConst0;
	int fSamplingFreq;
	int iVec70[2];
	int iVec68[2];
	int iVec66[2];
	int iVec64[2];
	int iVec62[2];
	int iVec60[2];
	int iVec58[2];
	int iVec56[2];
	int iVec54[2];
	int iVec52[2];
	int iVec50[2];
	int iVec48[2];
	int iVec46[2];
	int iVec44[2];
	int iVec42[2];
	int iVec40[2];
	int iVec38[2];
	int iVec36[2];
	int iVec34[2];
	int iVec32[2];
	int iVec30[2];
	int iRec33[2];
	int iVec29[2];
	int iVec27[2];
	int iRec30[2];
	int iVec26[2];
	int iVec24[2];
	int iVec22[2];
	int iVec20[2];
	int iVec18[2];
	int iVec16[2];
	int iVec14[2];
	int iVec12[2];
	int iVec10[2];
	int iVec8[2];
	int iVec6[2];
	int iVec3[2];
	int iRec6[2];
	int iVec2[2];
	int iRec4[2];
	int iRec3[2];
	int iVec1[2];
	int iVec0[2];
	int iRec2[2];
	int iRec1[2];
	float fVec28[512];
	float fVec61[512];
	float fVec69[512];
	float fVec31[256];
	float fVec37[256];
	float fVec45[256];
	float fVec49[256];
	float fVec53[256];
	float fVec57[256];
	float fVec63[256];
	float fVec71[256];
	float fVec5[128];
	float fVec7[128];
	float fVec9[128];
	float fVec33[128];
	float fVec39[128];
	float fVec41[128];
	float fVec47[128];
	float fVec51[128];
	float fVec55[128];
	float fVec59[128];
	float fVec65[128];
	float fVec11[64];
	float fVec13[64];
	float fVec15[64];
	float fVec17[64];
	float fVec19[64];
	float fVec35[64];
	float fVec43[64];
	float fVec67[64];
	float fVec21[32];
	float fVec23[32];
	float fVec25[32];
	float ftbl0[16];
	float ftbl1[16];
	float ftbl2[16];
	float ftbl3[16];
	float ftbl4[16];
	float fRec0[3];
	float fRec8[3];
	float fRec10[3];
	float fRec12[3];
	float fRec14[3];
	float fRec16[3];
	float fRec18[3];
	float fRec20[3];
	float fRec22[3];
	float fRec24[3];
	float fRec26[3];
	float fRec28[3];
	float fRec31[3];
	float fRec34[3];
	float fRec36[3];
	float fRec38[3];
	float fRec40[3];
	float fRec42[3];
	float fRec44[3];
	float fRec46[3];
	float fRec48[3];
	float fRec50[3];
	float fRec52[3];
	float fRec54[3];
	float fRec56[3];
	float fRec58[3];
	float fRec60[3];
	float fRec62[3];
	float fRec64[3];
	float fRec66[3];
	float fRec68[3];
	float fRec70[3];
	float fRec72[3];
	float fRec5[2];
	float fVec4[2];
	float fRec7[2];
	float fRec9[2];
	float fRec11[2];
	float fRec13[2];
	float fRec15[2];
	float fRec17[2];
	float fRec19[2];
	float fRec21[2];
	float fRec23[2];
	float fRec25[2];
	float fRec27[2];
	float fRec29[2];
	float fRec32[2];
	float fRec35[2];
	float fRec37[2];
	float fRec39[2];
	float fRec41[2];
	float fRec43[2];
	float fRec45[2];
	float fRec47[2];
	float fRec49[2];
	float fRec51[2];
	float fRec53[2];
	float fRec55[2];
	float fRec57[2];
	float fRec59[2];
	float fRec61[2];
	float fRec63[2];
	float fRec65[2];
	float fRec67[2];
	float fRec69[2];
	float fRec71[2];
	float fRec73[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	
  public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Yann Orlarey");
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
		m->declare("name", "Kisana");
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
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(16, ftbl0);
		iConst0 = int((0.166666672f * min(192000.0f, max(1.0f, float(fSamplingFreq)))));
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(16, ftbl1);
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(16, ftbl2);
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(16, ftbl3);
		sig0->instanceInitmydspSIG0(samplingFreq);
		sig0->fillmydspSIG0(16, ftbl4);
		deletemydspSIG0(sig0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(-20.0f);
		fVslider0 = FAUSTFLOAT(0.0f);
		fVslider1 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fVslider2 = FAUSTFLOAT(0.0f);
		fVslider3 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			iRec1[i0] = 0;
			
		}
		for (int i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			iRec2[i1] = 0;
			
		}
		for (int i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			iVec0[i2] = 0;
			
		}
		for (int i3 = 0; (i3 < 2); i3 = (i3 + 1)) {
			iVec1[i3] = 0;
			
		}
		for (int i4 = 0; (i4 < 2); i4 = (i4 + 1)) {
			iRec3[i4] = 0;
			
		}
		for (int i5 = 0; (i5 < 2); i5 = (i5 + 1)) {
			iRec4[i5] = 0;
			
		}
		for (int i6 = 0; (i6 < 2); i6 = (i6 + 1)) {
			iVec2[i6] = 0;
			
		}
		for (int i7 = 0; (i7 < 2); i7 = (i7 + 1)) {
			iRec6[i7] = 0;
			
		}
		for (int i8 = 0; (i8 < 2); i8 = (i8 + 1)) {
			iVec3[i8] = 0;
			
		}
		for (int i9 = 0; (i9 < 2); i9 = (i9 + 1)) {
			fRec5[i9] = 0.0f;
			
		}
		for (int i10 = 0; (i10 < 2); i10 = (i10 + 1)) {
			fVec4[i10] = 0.0f;
			
		}
		for (int i11 = 0; (i11 < 2); i11 = (i11 + 1)) {
			fRec7[i11] = 0.0f;
			
		}
		IOTA = 0;
		for (int i12 = 0; (i12 < 128); i12 = (i12 + 1)) {
			fVec5[i12] = 0.0f;
			
		}
		for (int i13 = 0; (i13 < 3); i13 = (i13 + 1)) {
			fRec0[i13] = 0.0f;
			
		}
		for (int i14 = 0; (i14 < 2); i14 = (i14 + 1)) {
			iVec6[i14] = 0;
			
		}
		for (int i15 = 0; (i15 < 2); i15 = (i15 + 1)) {
			fRec9[i15] = 0.0f;
			
		}
		for (int i16 = 0; (i16 < 128); i16 = (i16 + 1)) {
			fVec7[i16] = 0.0f;
			
		}
		for (int i17 = 0; (i17 < 3); i17 = (i17 + 1)) {
			fRec8[i17] = 0.0f;
			
		}
		for (int i18 = 0; (i18 < 2); i18 = (i18 + 1)) {
			iVec8[i18] = 0;
			
		}
		for (int i19 = 0; (i19 < 2); i19 = (i19 + 1)) {
			fRec11[i19] = 0.0f;
			
		}
		for (int i20 = 0; (i20 < 128); i20 = (i20 + 1)) {
			fVec9[i20] = 0.0f;
			
		}
		for (int i21 = 0; (i21 < 3); i21 = (i21 + 1)) {
			fRec10[i21] = 0.0f;
			
		}
		for (int i22 = 0; (i22 < 2); i22 = (i22 + 1)) {
			iVec10[i22] = 0;
			
		}
		for (int i23 = 0; (i23 < 2); i23 = (i23 + 1)) {
			fRec13[i23] = 0.0f;
			
		}
		for (int i24 = 0; (i24 < 64); i24 = (i24 + 1)) {
			fVec11[i24] = 0.0f;
			
		}
		for (int i25 = 0; (i25 < 3); i25 = (i25 + 1)) {
			fRec12[i25] = 0.0f;
			
		}
		for (int i26 = 0; (i26 < 2); i26 = (i26 + 1)) {
			iVec12[i26] = 0;
			
		}
		for (int i27 = 0; (i27 < 2); i27 = (i27 + 1)) {
			fRec15[i27] = 0.0f;
			
		}
		for (int i28 = 0; (i28 < 64); i28 = (i28 + 1)) {
			fVec13[i28] = 0.0f;
			
		}
		for (int i29 = 0; (i29 < 3); i29 = (i29 + 1)) {
			fRec14[i29] = 0.0f;
			
		}
		for (int i30 = 0; (i30 < 2); i30 = (i30 + 1)) {
			iVec14[i30] = 0;
			
		}
		for (int i31 = 0; (i31 < 2); i31 = (i31 + 1)) {
			fRec17[i31] = 0.0f;
			
		}
		for (int i32 = 0; (i32 < 64); i32 = (i32 + 1)) {
			fVec15[i32] = 0.0f;
			
		}
		for (int i33 = 0; (i33 < 3); i33 = (i33 + 1)) {
			fRec16[i33] = 0.0f;
			
		}
		for (int i34 = 0; (i34 < 2); i34 = (i34 + 1)) {
			iVec16[i34] = 0;
			
		}
		for (int i35 = 0; (i35 < 2); i35 = (i35 + 1)) {
			fRec19[i35] = 0.0f;
			
		}
		for (int i36 = 0; (i36 < 64); i36 = (i36 + 1)) {
			fVec17[i36] = 0.0f;
			
		}
		for (int i37 = 0; (i37 < 3); i37 = (i37 + 1)) {
			fRec18[i37] = 0.0f;
			
		}
		for (int i38 = 0; (i38 < 2); i38 = (i38 + 1)) {
			iVec18[i38] = 0;
			
		}
		for (int i39 = 0; (i39 < 2); i39 = (i39 + 1)) {
			fRec21[i39] = 0.0f;
			
		}
		for (int i40 = 0; (i40 < 64); i40 = (i40 + 1)) {
			fVec19[i40] = 0.0f;
			
		}
		for (int i41 = 0; (i41 < 3); i41 = (i41 + 1)) {
			fRec20[i41] = 0.0f;
			
		}
		for (int i42 = 0; (i42 < 2); i42 = (i42 + 1)) {
			iVec20[i42] = 0;
			
		}
		for (int i43 = 0; (i43 < 2); i43 = (i43 + 1)) {
			fRec23[i43] = 0.0f;
			
		}
		for (int i44 = 0; (i44 < 32); i44 = (i44 + 1)) {
			fVec21[i44] = 0.0f;
			
		}
		for (int i45 = 0; (i45 < 3); i45 = (i45 + 1)) {
			fRec22[i45] = 0.0f;
			
		}
		for (int i46 = 0; (i46 < 2); i46 = (i46 + 1)) {
			iVec22[i46] = 0;
			
		}
		for (int i47 = 0; (i47 < 2); i47 = (i47 + 1)) {
			fRec25[i47] = 0.0f;
			
		}
		for (int i48 = 0; (i48 < 32); i48 = (i48 + 1)) {
			fVec23[i48] = 0.0f;
			
		}
		for (int i49 = 0; (i49 < 3); i49 = (i49 + 1)) {
			fRec24[i49] = 0.0f;
			
		}
		for (int i50 = 0; (i50 < 2); i50 = (i50 + 1)) {
			iVec24[i50] = 0;
			
		}
		for (int i51 = 0; (i51 < 2); i51 = (i51 + 1)) {
			fRec27[i51] = 0.0f;
			
		}
		for (int i52 = 0; (i52 < 32); i52 = (i52 + 1)) {
			fVec25[i52] = 0.0f;
			
		}
		for (int i53 = 0; (i53 < 3); i53 = (i53 + 1)) {
			fRec26[i53] = 0.0f;
			
		}
		for (int i54 = 0; (i54 < 2); i54 = (i54 + 1)) {
			iVec26[i54] = 0;
			
		}
		for (int i55 = 0; (i55 < 2); i55 = (i55 + 1)) {
			iRec30[i55] = 0;
			
		}
		for (int i56 = 0; (i56 < 2); i56 = (i56 + 1)) {
			iVec27[i56] = 0;
			
		}
		for (int i57 = 0; (i57 < 2); i57 = (i57 + 1)) {
			fRec29[i57] = 0.0f;
			
		}
		for (int i58 = 0; (i58 < 512); i58 = (i58 + 1)) {
			fVec28[i58] = 0.0f;
			
		}
		for (int i59 = 0; (i59 < 3); i59 = (i59 + 1)) {
			fRec28[i59] = 0.0f;
			
		}
		for (int i60 = 0; (i60 < 2); i60 = (i60 + 1)) {
			iVec29[i60] = 0;
			
		}
		for (int i61 = 0; (i61 < 2); i61 = (i61 + 1)) {
			iRec33[i61] = 0;
			
		}
		for (int i62 = 0; (i62 < 2); i62 = (i62 + 1)) {
			iVec30[i62] = 0;
			
		}
		for (int i63 = 0; (i63 < 2); i63 = (i63 + 1)) {
			fRec32[i63] = 0.0f;
			
		}
		for (int i64 = 0; (i64 < 256); i64 = (i64 + 1)) {
			fVec31[i64] = 0.0f;
			
		}
		for (int i65 = 0; (i65 < 3); i65 = (i65 + 1)) {
			fRec31[i65] = 0.0f;
			
		}
		for (int i66 = 0; (i66 < 2); i66 = (i66 + 1)) {
			iVec32[i66] = 0;
			
		}
		for (int i67 = 0; (i67 < 2); i67 = (i67 + 1)) {
			fRec35[i67] = 0.0f;
			
		}
		for (int i68 = 0; (i68 < 128); i68 = (i68 + 1)) {
			fVec33[i68] = 0.0f;
			
		}
		for (int i69 = 0; (i69 < 3); i69 = (i69 + 1)) {
			fRec34[i69] = 0.0f;
			
		}
		for (int i70 = 0; (i70 < 2); i70 = (i70 + 1)) {
			iVec34[i70] = 0;
			
		}
		for (int i71 = 0; (i71 < 2); i71 = (i71 + 1)) {
			fRec37[i71] = 0.0f;
			
		}
		for (int i72 = 0; (i72 < 64); i72 = (i72 + 1)) {
			fVec35[i72] = 0.0f;
			
		}
		for (int i73 = 0; (i73 < 3); i73 = (i73 + 1)) {
			fRec36[i73] = 0.0f;
			
		}
		for (int i74 = 0; (i74 < 2); i74 = (i74 + 1)) {
			iVec36[i74] = 0;
			
		}
		for (int i75 = 0; (i75 < 2); i75 = (i75 + 1)) {
			fRec39[i75] = 0.0f;
			
		}
		for (int i76 = 0; (i76 < 256); i76 = (i76 + 1)) {
			fVec37[i76] = 0.0f;
			
		}
		for (int i77 = 0; (i77 < 3); i77 = (i77 + 1)) {
			fRec38[i77] = 0.0f;
			
		}
		for (int i78 = 0; (i78 < 2); i78 = (i78 + 1)) {
			iVec38[i78] = 0;
			
		}
		for (int i79 = 0; (i79 < 2); i79 = (i79 + 1)) {
			fRec41[i79] = 0.0f;
			
		}
		for (int i80 = 0; (i80 < 128); i80 = (i80 + 1)) {
			fVec39[i80] = 0.0f;
			
		}
		for (int i81 = 0; (i81 < 3); i81 = (i81 + 1)) {
			fRec40[i81] = 0.0f;
			
		}
		for (int i82 = 0; (i82 < 2); i82 = (i82 + 1)) {
			iVec40[i82] = 0;
			
		}
		for (int i83 = 0; (i83 < 2); i83 = (i83 + 1)) {
			fRec43[i83] = 0.0f;
			
		}
		for (int i84 = 0; (i84 < 128); i84 = (i84 + 1)) {
			fVec41[i84] = 0.0f;
			
		}
		for (int i85 = 0; (i85 < 3); i85 = (i85 + 1)) {
			fRec42[i85] = 0.0f;
			
		}
		for (int i86 = 0; (i86 < 2); i86 = (i86 + 1)) {
			iVec42[i86] = 0;
			
		}
		for (int i87 = 0; (i87 < 2); i87 = (i87 + 1)) {
			fRec45[i87] = 0.0f;
			
		}
		for (int i88 = 0; (i88 < 64); i88 = (i88 + 1)) {
			fVec43[i88] = 0.0f;
			
		}
		for (int i89 = 0; (i89 < 3); i89 = (i89 + 1)) {
			fRec44[i89] = 0.0f;
			
		}
		for (int i90 = 0; (i90 < 2); i90 = (i90 + 1)) {
			iVec44[i90] = 0;
			
		}
		for (int i91 = 0; (i91 < 2); i91 = (i91 + 1)) {
			fRec47[i91] = 0.0f;
			
		}
		for (int i92 = 0; (i92 < 256); i92 = (i92 + 1)) {
			fVec45[i92] = 0.0f;
			
		}
		for (int i93 = 0; (i93 < 3); i93 = (i93 + 1)) {
			fRec46[i93] = 0.0f;
			
		}
		for (int i94 = 0; (i94 < 2); i94 = (i94 + 1)) {
			iVec46[i94] = 0;
			
		}
		for (int i95 = 0; (i95 < 2); i95 = (i95 + 1)) {
			fRec49[i95] = 0.0f;
			
		}
		for (int i96 = 0; (i96 < 128); i96 = (i96 + 1)) {
			fVec47[i96] = 0.0f;
			
		}
		for (int i97 = 0; (i97 < 3); i97 = (i97 + 1)) {
			fRec48[i97] = 0.0f;
			
		}
		for (int i98 = 0; (i98 < 2); i98 = (i98 + 1)) {
			iVec48[i98] = 0;
			
		}
		for (int i99 = 0; (i99 < 2); i99 = (i99 + 1)) {
			fRec51[i99] = 0.0f;
			
		}
		for (int i100 = 0; (i100 < 256); i100 = (i100 + 1)) {
			fVec49[i100] = 0.0f;
			
		}
		for (int i101 = 0; (i101 < 3); i101 = (i101 + 1)) {
			fRec50[i101] = 0.0f;
			
		}
		for (int i102 = 0; (i102 < 2); i102 = (i102 + 1)) {
			iVec50[i102] = 0;
			
		}
		for (int i103 = 0; (i103 < 2); i103 = (i103 + 1)) {
			fRec53[i103] = 0.0f;
			
		}
		for (int i104 = 0; (i104 < 128); i104 = (i104 + 1)) {
			fVec51[i104] = 0.0f;
			
		}
		for (int i105 = 0; (i105 < 3); i105 = (i105 + 1)) {
			fRec52[i105] = 0.0f;
			
		}
		for (int i106 = 0; (i106 < 2); i106 = (i106 + 1)) {
			iVec52[i106] = 0;
			
		}
		for (int i107 = 0; (i107 < 2); i107 = (i107 + 1)) {
			fRec55[i107] = 0.0f;
			
		}
		for (int i108 = 0; (i108 < 256); i108 = (i108 + 1)) {
			fVec53[i108] = 0.0f;
			
		}
		for (int i109 = 0; (i109 < 3); i109 = (i109 + 1)) {
			fRec54[i109] = 0.0f;
			
		}
		for (int i110 = 0; (i110 < 2); i110 = (i110 + 1)) {
			iVec54[i110] = 0;
			
		}
		for (int i111 = 0; (i111 < 2); i111 = (i111 + 1)) {
			fRec57[i111] = 0.0f;
			
		}
		for (int i112 = 0; (i112 < 128); i112 = (i112 + 1)) {
			fVec55[i112] = 0.0f;
			
		}
		for (int i113 = 0; (i113 < 3); i113 = (i113 + 1)) {
			fRec56[i113] = 0.0f;
			
		}
		for (int i114 = 0; (i114 < 2); i114 = (i114 + 1)) {
			iVec56[i114] = 0;
			
		}
		for (int i115 = 0; (i115 < 2); i115 = (i115 + 1)) {
			fRec59[i115] = 0.0f;
			
		}
		for (int i116 = 0; (i116 < 256); i116 = (i116 + 1)) {
			fVec57[i116] = 0.0f;
			
		}
		for (int i117 = 0; (i117 < 3); i117 = (i117 + 1)) {
			fRec58[i117] = 0.0f;
			
		}
		for (int i118 = 0; (i118 < 2); i118 = (i118 + 1)) {
			iVec58[i118] = 0;
			
		}
		for (int i119 = 0; (i119 < 2); i119 = (i119 + 1)) {
			fRec61[i119] = 0.0f;
			
		}
		for (int i120 = 0; (i120 < 128); i120 = (i120 + 1)) {
			fVec59[i120] = 0.0f;
			
		}
		for (int i121 = 0; (i121 < 3); i121 = (i121 + 1)) {
			fRec60[i121] = 0.0f;
			
		}
		for (int i122 = 0; (i122 < 2); i122 = (i122 + 1)) {
			iVec60[i122] = 0;
			
		}
		for (int i123 = 0; (i123 < 2); i123 = (i123 + 1)) {
			fRec63[i123] = 0.0f;
			
		}
		for (int i124 = 0; (i124 < 512); i124 = (i124 + 1)) {
			fVec61[i124] = 0.0f;
			
		}
		for (int i125 = 0; (i125 < 3); i125 = (i125 + 1)) {
			fRec62[i125] = 0.0f;
			
		}
		for (int i126 = 0; (i126 < 2); i126 = (i126 + 1)) {
			iVec62[i126] = 0;
			
		}
		for (int i127 = 0; (i127 < 2); i127 = (i127 + 1)) {
			fRec65[i127] = 0.0f;
			
		}
		for (int i128 = 0; (i128 < 256); i128 = (i128 + 1)) {
			fVec63[i128] = 0.0f;
			
		}
		for (int i129 = 0; (i129 < 3); i129 = (i129 + 1)) {
			fRec64[i129] = 0.0f;
			
		}
		for (int i130 = 0; (i130 < 2); i130 = (i130 + 1)) {
			iVec64[i130] = 0;
			
		}
		for (int i131 = 0; (i131 < 2); i131 = (i131 + 1)) {
			fRec67[i131] = 0.0f;
			
		}
		for (int i132 = 0; (i132 < 128); i132 = (i132 + 1)) {
			fVec65[i132] = 0.0f;
			
		}
		for (int i133 = 0; (i133 < 3); i133 = (i133 + 1)) {
			fRec66[i133] = 0.0f;
			
		}
		for (int i134 = 0; (i134 < 2); i134 = (i134 + 1)) {
			iVec66[i134] = 0;
			
		}
		for (int i135 = 0; (i135 < 2); i135 = (i135 + 1)) {
			fRec69[i135] = 0.0f;
			
		}
		for (int i136 = 0; (i136 < 64); i136 = (i136 + 1)) {
			fVec67[i136] = 0.0f;
			
		}
		for (int i137 = 0; (i137 < 3); i137 = (i137 + 1)) {
			fRec68[i137] = 0.0f;
			
		}
		for (int i138 = 0; (i138 < 2); i138 = (i138 + 1)) {
			iVec68[i138] = 0;
			
		}
		for (int i139 = 0; (i139 < 2); i139 = (i139 + 1)) {
			fRec71[i139] = 0.0f;
			
		}
		for (int i140 = 0; (i140 < 512); i140 = (i140 + 1)) {
			fVec69[i140] = 0.0f;
			
		}
		for (int i141 = 0; (i141 < 3); i141 = (i141 + 1)) {
			fRec70[i141] = 0.0f;
			
		}
		for (int i142 = 0; (i142 < 2); i142 = (i142 + 1)) {
			iVec70[i142] = 0;
			
		}
		for (int i143 = 0; (i143 < 2); i143 = (i143 + 1)) {
			fRec73[i143] = 0.0f;
			
		}
		for (int i144 = 0; (i144 < 256); i144 = (i144 + 1)) {
			fVec71[i144] = 0.0f;
			
		}
		for (int i145 = 0; (i145 < 3); i145 = (i145 + 1)) {
			fRec72[i145] = 0.0f;
			
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
		ui_interface->openVerticalBox("Kisana");
		ui_interface->openHorizontalBox("Loops");
		ui_interface->openVerticalBox("loop");
		ui_interface->addVerticalSlider("level", &fVslider0, 0.0f, 0.0f, 6.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("loop48");
		ui_interface->declare(&fVslider2, "1", "");
		ui_interface->addVerticalSlider("note", &fVslider2, 0.0f, 0.0f, 11.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("loop60");
		ui_interface->declare(&fVslider3, "1", "");
		ui_interface->addVerticalSlider("note", &fVslider3, 0.0f, 0.0f, 11.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->openVerticalBox("loop72");
		ui_interface->declare(&fVslider1, "1", "");
		ui_interface->addVerticalSlider("note", &fVslider1, 0.0f, 0.0f, 11.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->addHorizontalSlider("master", &fHslider0, -20.0f, -60.0f, 0.0f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->addHorizontalSlider("timbre", &fHslider1, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = powf(10.0f, (0.0500000007f * float(fHslider0)));
		int iSlow1 = int(float(fVslider0));
		int iSlow2 = (float(iSlow1) <= 0.0f);
		int iSlow3 = int(float(fVslider1));
		int iSlow4 = (float(iSlow3) <= 0.0f);
		float fSlow5 = float(fHslider1);
		int iSlow6 = (fSlow5 <= 0.0f);
		int iSlow7 = int(float(fVslider2));
		int iSlow8 = (float(iSlow7) <= 0.0f);
		int iSlow9 = int(float(fVslider3));
		int iSlow10 = (float(iSlow9) <= 0.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec1[0] = ((1103515245 * iRec1[1]) + 12345);
			iRec2[0] = ((iRec2[1] + 1) % iConst0);
			int iTemp0 = (iRec2[0] == 0);
			iVec0[0] = iTemp0;
			iVec1[0] = iSlow1;
			iRec3[0] = (iVec0[1]?0:(abs((iSlow1 - iVec1[1])) + iRec3[1]));
			iRec4[0] = ((iTemp0 + iRec4[1]) % 15);
			ftbl0[((iTemp0 & ((iRec3[0] > 0) | iSlow2))?iRec4[0]:15)] = float(iSlow1);
			float fTemp1 = (float(iRec1[0]) * powf(10.0f, (0.0500000007f * (ftbl0[iRec4[0]] + -6.0f))));
			iVec2[0] = iSlow3;
			iRec6[0] = (iVec0[1]?0:(abs((iSlow3 - iVec2[1])) + iRec6[1]));
			ftbl1[((iTemp0 & ((iRec6[0] > 0) | iSlow4))?iRec4[0]:15)] = float(iSlow3);
			int iTemp2 = (fabsf((ftbl1[iRec4[0]] + -1.0f)) < 0.5f);
			iVec3[0] = iTemp2;
			fRec5[0] = ((fRec5[1] + float((float((iTemp2 - iVec3[1])) > 0.0f))) - (0.0118651045f * float((fRec5[1] > 0.0f))));
			fVec4[0] = fSlow5;
			fRec7[0] = (iVec0[1]?0.0f:(fabsf((fSlow5 - fVec4[1])) + fRec7[1]));
			ftbl2[((iTemp0 & ((fRec7[0] > 0.0f) | iSlow6))?iRec4[0]:15)] = fSlow5;
			float fTemp3 = (ftbl2[iRec4[0]] + 1.0f);
			float fTemp4 = (1.0f - ftbl2[iRec4[0]]);
			fVec5[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec5[0] > 0.0f)))) + (0.498352528f * ((fTemp3 * fRec0[1]) + (fTemp4 * fRec0[2]))));
			fRec0[0] = fVec5[((IOTA - 83) & 127)];
			int iTemp5 = (fabsf((ftbl1[iRec4[0]] + -2.0f)) < 0.5f);
			iVec6[0] = iTemp5;
			fRec9[0] = ((fRec9[1] + float((float((iTemp5 - iVec6[1])) > 0.0f))) - (0.0133181298f * float((fRec9[1] > 0.0f))));
			fVec7[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec9[0] > 0.0f)))) + (0.498531997f * ((fTemp3 * fRec8[1]) + (fTemp4 * fRec8[2]))));
			fRec8[0] = fVec7[((IOTA - 74) & 127)];
			int iTemp6 = (fabsf((ftbl1[iRec4[0]] + -3.0f)) < 0.5f);
			iVec8[0] = iTemp6;
			fRec11[0] = ((fRec11[1] + float((float((iTemp6 - iVec8[1])) > 0.0f))) - (0.0149490954f * float((fRec11[1] > 0.0f))));
			fVec9[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec11[0] > 0.0f)))) + (0.498691946f * ((fTemp3 * fRec10[1]) + (fTemp4 * fRec10[2]))));
			fRec10[0] = fVec9[((IOTA - 65) & 127)];
			int iTemp7 = (fabsf((ftbl1[iRec4[0]] + -4.0f)) < 0.5f);
			iVec10[0] = iTemp7;
			fRec13[0] = ((fRec13[1] + float((float((iTemp7 - iVec10[1])) > 0.0f))) - (0.0177775715f * float((fRec13[1] > 0.0f))));
			fVec11[(IOTA & 63)] = ((4.65661287e-10f * (fTemp1 * float((fRec13[0] > 0.0f)))) + (0.498899847f * ((fTemp3 * fRec12[1]) + (fTemp4 * fRec12[2]))));
			fRec12[0] = fVec11[((IOTA - 55) & 63)];
			int iTemp8 = (fabsf((ftbl1[iRec4[0]] + -5.0f)) < 0.5f);
			iVec12[0] = iTemp8;
			fRec15[0] = ((fRec15[1] + float((float((iTemp8 - iVec12[1])) > 0.0f))) - (0.0199546479f * float((fRec15[1] > 0.0f))));
			fVec13[(IOTA & 63)] = ((4.65661287e-10f * (fTemp1 * float((fRec15[0] > 0.0f)))) + (0.499019742f * ((fTemp3 * fRec14[1]) + (fTemp4 * fRec14[2]))));
			fRec14[0] = fVec13[((IOTA - 49) & 63)];
			int iTemp9 = (fabsf((ftbl1[iRec4[0]] + -6.0f)) < 0.5f);
			iVec14[0] = iTemp9;
			fRec17[0] = ((fRec17[1] + float((float((iTemp9 - iVec14[1])) > 0.0f))) - (0.0237302091f * float((fRec17[1] > 0.0f))));
			fVec15[(IOTA & 63)] = ((4.65661287e-10f * (fTemp1 * float((fRec17[0] > 0.0f)))) + (0.499175578f * ((fTemp3 * fRec16[1]) + (fTemp4 * fRec16[2]))));
			fRec16[0] = fVec15[((IOTA - 41) & 63)];
			float fTemp10 = (0.707106769f * fRec16[0]);
			int iTemp11 = (fabsf((ftbl1[iRec4[0]] + -7.0f)) < 0.5f);
			iVec16[0] = iTemp11;
			fRec19[0] = ((fRec19[1] + float((float((iTemp11 - iVec16[1])) > 0.0f))) - (0.0266362596f * float((fRec19[1] > 0.0f))));
			fVec17[(IOTA & 63)] = ((4.65661287e-10f * (fTemp1 * float((fRec19[0] > 0.0f)))) + (0.499265462f * ((fTemp3 * fRec18[1]) + (fTemp4 * fRec18[2]))));
			fRec18[0] = fVec17[((IOTA - 36) & 63)];
			int iTemp12 = (fabsf((ftbl1[iRec4[0]] + -8.0f)) < 0.5f);
			iVec18[0] = iTemp12;
			fRec21[0] = ((fRec21[1] + float((float((iTemp12 - iVec18[1])) > 0.0f))) - (0.0298981909f * float((fRec21[1] > 0.0f))));
			fVec19[(IOTA & 63)] = ((4.65661287e-10f * (fTemp1 * float((fRec21[0] > 0.0f)))) + (0.499345541f * ((fTemp3 * fRec20[1]) + (fTemp4 * fRec20[2]))));
			fRec20[0] = fVec19[((IOTA - 32) & 63)];
			int iTemp13 = (fabsf((ftbl1[iRec4[0]] + -9.0f)) < 0.5f);
			iVec20[0] = iTemp13;
			fRec23[0] = ((fRec23[1] + float((float((iTemp13 - iVec20[1])) > 0.0f))) - (0.0355551429f * float((fRec23[1] > 0.0f))));
			fVec21[(IOTA & 31)] = ((4.65661287e-10f * (fTemp1 * float((fRec23[0] > 0.0f)))) + (0.499449611f * ((fTemp4 * fRec22[2]) + (fTemp3 * fRec22[1]))));
			fRec22[0] = fVec21[((IOTA - 27) & 31)];
			int iTemp14 = (fabsf((ftbl1[iRec4[0]] + -10.0f)) < 0.5f);
			iVec22[0] = iTemp14;
			fRec25[0] = ((fRec25[1] + float((float((iTemp14 - iVec22[1])) > 0.0f))) - (0.0399092957f * float((fRec25[1] > 0.0f))));
			fVec23[(IOTA & 31)] = ((4.65661287e-10f * (fTemp1 * float((fRec25[0] > 0.0f)))) + (0.499509633f * ((fTemp3 * fRec24[1]) + (fTemp4 * fRec24[2]))));
			fRec24[0] = fVec23[((IOTA - 24) & 31)];
			int iTemp15 = (fabsf((ftbl1[iRec4[0]] + -11.0f)) < 0.5f);
			iVec24[0] = iTemp15;
			fRec27[0] = ((fRec27[1] + float((float((iTemp15 - iVec24[1])) > 0.0f))) - (0.0474604182f * float((fRec27[1] > 0.0f))));
			fVec25[(IOTA & 31)] = ((4.65661287e-10f * (fTemp1 * float((fRec27[0] > 0.0f)))) + (0.499587625f * ((fTemp3 * fRec26[1]) + (fTemp4 * fRec26[2]))));
			fRec26[0] = fVec25[((IOTA - 20) & 31)];
			iVec26[0] = iSlow7;
			iRec30[0] = (iVec0[1]?0:(abs((iSlow7 - iVec26[1])) + iRec30[1]));
			ftbl3[((iTemp0 & ((iRec30[0] > 0) | iSlow8))?iRec4[0]:15)] = float(iSlow7);
			int iTemp16 = (fabsf((ftbl3[iRec4[0]] + -3.0f)) < 0.5f);
			iVec27[0] = iTemp16;
			fRec29[0] = ((fRec29[1] + float((float((iTemp16 - iVec27[1])) > 0.0f))) - (0.00373727386f * float((fRec29[1] > 0.0f))));
			fVec28[(IOTA & 511)] = ((4.65661287e-10f * (fTemp1 * float((fRec29[0] > 0.0f)))) + (0.494788289f * ((fTemp3 * fRec28[1]) + (fTemp4 * fRec28[2]))));
			fRec28[0] = fVec28[((IOTA - 266) & 511)];
			iVec29[0] = iSlow9;
			iRec33[0] = (iVec0[1]?0:(abs((iSlow9 - iVec29[1])) + iRec33[1]));
			ftbl4[((iTemp0 & ((iRec33[0] > 0) | iSlow10))?iRec4[0]:15)] = float(iSlow9);
			int iTemp17 = (fabsf((ftbl4[iRec4[0]] + -3.0f)) < 0.5f);
			iVec30[0] = iTemp17;
			fRec32[0] = ((fRec32[1] + float((float((iTemp17 - iVec30[1])) > 0.0f))) - (0.00747454772f * float((fRec32[1] > 0.0f))));
			fVec31[(IOTA & 255)] = ((4.65661287e-10f * (fTemp1 * float((fRec32[0] > 0.0f)))) + (0.49738732f * ((fTemp3 * fRec31[1]) + (fTemp4 * fRec31[2]))));
			fRec31[0] = fVec31[((IOTA - 132) & 255)];
			float fTemp18 = (fRec28[0] + fRec31[0]);
			int iTemp19 = (fabsf((ftbl3[iRec4[0]] + -11.0f)) < 0.5f);
			iVec32[0] = iTemp19;
			fRec35[0] = ((fRec35[1] + float((float((iTemp19 - iVec32[1])) > 0.0f))) - (0.0118651045f * float((fRec35[1] > 0.0f))));
			fVec33[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec35[0] > 0.0f)))) + (0.498352528f * ((fTemp3 * fRec34[1]) + (fTemp4 * fRec34[2]))));
			fRec34[0] = fVec33[((IOTA - 83) & 127)];
			int iTemp20 = (fabsf((ftbl4[iRec4[0]] + -11.0f)) < 0.5f);
			iVec34[0] = iTemp20;
			fRec37[0] = ((fRec37[1] + float((float((iTemp20 - iVec34[1])) > 0.0f))) - (0.0237302091f * float((fRec37[1] > 0.0f))));
			fVec35[(IOTA & 63)] = ((4.65661287e-10f * (fTemp1 * float((fRec37[0] > 0.0f)))) + (0.499175578f * ((fTemp3 * fRec36[1]) + (fTemp4 * fRec36[2]))));
			fRec36[0] = fVec35[((IOTA - 41) & 63)];
			float fTemp21 = (fRec34[0] + fRec36[0]);
			int iTemp22 = (fabsf((ftbl3[iRec4[0]] + -6.0f)) < 0.5f);
			iVec36[0] = iTemp22;
			fRec39[0] = ((fRec39[1] + float((float((iTemp22 - iVec36[1])) > 0.0f))) - (0.00593255227f * float((fRec39[1] > 0.0f))));
			fVec37[(IOTA & 255)] = ((4.65661287e-10f * (fTemp1 * float((fRec39[0] > 0.0f)))) + (0.496710479f * ((fTemp3 * fRec38[1]) + (fTemp4 * fRec38[2]))));
			fRec38[0] = fVec37[((IOTA - 167) & 255)];
			int iTemp23 = (fabsf((ftbl4[iRec4[0]] + -6.0f)) < 0.5f);
			iVec38[0] = iTemp23;
			fRec41[0] = ((fRec41[1] + float((float((iTemp23 - iVec38[1])) > 0.0f))) - (0.0118651045f * float((fRec41[1] > 0.0f))));
			fVec39[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec41[0] > 0.0f)))) + (0.498352528f * ((fTemp3 * fRec40[1]) + (fTemp4 * fRec40[2]))));
			fRec40[0] = fVec39[((IOTA - 83) & 127)];
			float fTemp24 = (0.707106769f * (fRec38[0] + fRec40[0]));
			int iTemp25 = (fabsf((ftbl3[iRec4[0]] + -9.0f)) < 0.5f);
			iVec40[0] = iTemp25;
			fRec43[0] = ((fRec43[1] + float((float((iTemp25 - iVec40[1])) > 0.0f))) - (0.00888878573f * float((fRec43[1] > 0.0f))));
			fVec41[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec43[0] > 0.0f)))) + (0.497802079f * ((fTemp3 * fRec42[1]) + (fTemp4 * fRec42[2]))));
			fRec42[0] = fVec41[((IOTA - 111) & 127)];
			int iTemp26 = (fabsf((ftbl4[iRec4[0]] + -9.0f)) < 0.5f);
			iVec42[0] = iTemp26;
			fRec45[0] = ((fRec45[1] + float((float((iTemp26 - iVec42[1])) > 0.0f))) - (0.0177775715f * float((fRec45[1] > 0.0f))));
			fVec43[(IOTA & 63)] = ((4.65661287e-10f * (fTemp1 * float((fRec45[0] > 0.0f)))) + (0.498899847f * ((fTemp3 * fRec44[1]) + (fTemp4 * fRec44[2]))));
			fRec44[0] = fVec43[((IOTA - 55) & 63)];
			float fTemp27 = (fRec42[0] + fRec44[0]);
			int iTemp28 = (fabsf((ftbl3[iRec4[0]] + -5.0f)) < 0.5f);
			iVec44[0] = iTemp28;
			fRec47[0] = ((fRec47[1] + float((float((iTemp28 - iVec44[1])) > 0.0f))) - (0.00498866197f * float((fRec47[1] > 0.0f))));
			fVec45[(IOTA & 255)] = ((4.65661287e-10f * (fTemp1 * float((fRec47[0] > 0.0f)))) + (0.496090502f * ((fTemp3 * fRec46[1]) + (fTemp4 * fRec46[2]))));
			fRec46[0] = fVec45[((IOTA - 199) & 255)];
			int iTemp29 = (fabsf((ftbl4[iRec4[0]] + -5.0f)) < 0.5f);
			iVec46[0] = iTemp29;
			fRec49[0] = ((fRec49[1] + float((float((iTemp29 - iVec46[1])) > 0.0f))) - (0.00997732393f * float((fRec49[1] > 0.0f))));
			fVec47[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec49[0] > 0.0f)))) + (0.498041421f * ((fTemp3 * fRec48[1]) + (fTemp4 * fRec48[2]))));
			fRec48[0] = fVec47[((IOTA - 99) & 127)];
			float fTemp30 = (fRec46[0] + fRec48[0]);
			int iTemp31 = (fabsf((ftbl3[iRec4[0]] + -8.0f)) < 0.5f);
			iVec48[0] = iTemp31;
			fRec51[0] = ((fRec51[1] + float((float((iTemp31 - iVec48[1])) > 0.0f))) - (0.00747454772f * float((fRec51[1] > 0.0f))));
			fVec49[(IOTA & 255)] = ((4.65661287e-10f * (fTemp1 * float((fRec51[0] > 0.0f)))) + (0.49738732f * ((fTemp3 * fRec50[1]) + (fTemp4 * fRec50[2]))));
			fRec50[0] = fVec49[((IOTA - 132) & 255)];
			int iTemp32 = (fabsf((ftbl4[iRec4[0]] + -8.0f)) < 0.5f);
			iVec50[0] = iTemp32;
			fRec53[0] = ((fRec53[1] + float((float((iTemp32 - iVec50[1])) > 0.0f))) - (0.0149490954f * float((fRec53[1] > 0.0f))));
			fVec51[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec53[0] > 0.0f)))) + (0.498691946f * ((fTemp3 * fRec52[1]) + (fTemp4 * fRec52[2]))));
			fRec52[0] = fVec51[((IOTA - 65) & 127)];
			float fTemp33 = (fRec50[0] + fRec52[0]);
			int iTemp34 = (fabsf((ftbl3[iRec4[0]] + -7.0f)) < 0.5f);
			iVec52[0] = iTemp34;
			fRec55[0] = ((fRec55[1] + float((float((iTemp34 - iVec52[1])) > 0.0f))) - (0.00665906491f * float((fRec55[1] > 0.0f))));
			fVec53[(IOTA & 255)] = ((4.65661287e-10f * (fTemp1 * float((fRec55[0] > 0.0f)))) + (0.497068316f * ((fTemp3 * fRec54[1]) + (fTemp4 * fRec54[2]))));
			fRec54[0] = fVec53[((IOTA - 149) & 255)];
			int iTemp35 = (fabsf((ftbl4[iRec4[0]] + -7.0f)) < 0.5f);
			iVec54[0] = iTemp35;
			fRec57[0] = ((fRec57[1] + float((float((iTemp35 - iVec54[1])) > 0.0f))) - (0.0133181298f * float((fRec57[1] > 0.0f))));
			fVec55[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec57[0] > 0.0f)))) + (0.498531997f * ((fTemp3 * fRec56[1]) + (fTemp4 * fRec56[2]))));
			fRec56[0] = fVec55[((IOTA - 74) & 127)];
			float fTemp36 = (fRec54[0] + fRec56[0]);
			int iTemp37 = (fabsf((ftbl3[iRec4[0]] + -4.0f)) < 0.5f);
			iVec56[0] = iTemp37;
			fRec59[0] = ((fRec59[1] + float((float((iTemp37 - iVec56[1])) > 0.0f))) - (0.00444439286f * float((fRec59[1] > 0.0f))));
			fVec57[(IOTA & 255)] = ((4.65661287e-10f * (fTemp1 * float((fRec59[0] > 0.0f)))) + (0.495613843f * ((fTemp3 * fRec58[1]) + (fTemp4 * fRec58[2]))));
			fRec58[0] = fVec57[((IOTA - 224) & 255)];
			int iTemp38 = (fabsf((ftbl4[iRec4[0]] + -4.0f)) < 0.5f);
			iVec58[0] = iTemp38;
			fRec61[0] = ((fRec61[1] + float((float((iTemp38 - iVec58[1])) > 0.0f))) - (0.00888878573f * float((fRec61[1] > 0.0f))));
			fVec59[(IOTA & 127)] = ((4.65661287e-10f * (fTemp1 * float((fRec61[0] > 0.0f)))) + (0.497802079f * ((fTemp3 * fRec60[1]) + (fTemp4 * fRec60[2]))));
			fRec60[0] = fVec59[((IOTA - 111) & 127)];
			float fTemp39 = (fRec58[0] + fRec60[0]);
			int iTemp40 = (fabsf((ftbl3[iRec4[0]] + -2.0f)) < 0.5f);
			iVec60[0] = iTemp40;
			fRec63[0] = ((fRec63[1] + float((float((iTemp40 - iVec60[1])) > 0.0f))) - (0.00332953245f * float((fRec63[1] > 0.0f))));
			fVec61[(IOTA & 511)] = ((4.65661287e-10f * (fTemp1 * float((fRec63[0] > 0.0f)))) + (0.494153798f * ((fTemp3 * fRec62[1]) + (fTemp4 * fRec62[2]))));
			fRec62[0] = fVec61[((IOTA - 299) & 511)];
			int iTemp41 = (fabsf((ftbl4[iRec4[0]] + -2.0f)) < 0.5f);
			iVec62[0] = iTemp41;
			fRec65[0] = ((fRec65[1] + float((float((iTemp41 - iVec62[1])) > 0.0f))) - (0.00665906491f * float((fRec65[1] > 0.0f))));
			fVec63[(IOTA & 255)] = ((4.65661287e-10f * (fTemp1 * float((fRec65[0] > 0.0f)))) + (0.497068316f * ((fTemp3 * fRec64[1]) + (fTemp4 * fRec64[2]))));
			fRec64[0] = fVec63[((IOTA - 149) & 255)];
			float fTemp42 = (fRec62[0] + fRec64[0]);
			int iTemp43 = (fabsf((ftbl3[iRec4[0]] + -10.0f)) < 0.5f);
			iVec64[0] = iTemp43;
			fRec67[0] = ((fRec67[1] + float((float((iTemp43 - iVec64[1])) > 0.0f))) - (0.00997732393f * float((fRec67[1] > 0.0f))));
			fVec65[(IOTA & 127)] = ((0.498041421f * ((fRec66[1] * fTemp3) + (fRec66[2] * fTemp4))) + (4.65661287e-10f * (fTemp1 * float((fRec67[0] > 0.0f)))));
			fRec66[0] = fVec65[((IOTA - 99) & 127)];
			int iTemp44 = (fabsf((ftbl4[iRec4[0]] + -10.0f)) < 0.5f);
			iVec66[0] = iTemp44;
			fRec69[0] = ((fRec69[1] + float((float((iTemp44 - iVec66[1])) > 0.0f))) - (0.0199546479f * float((fRec69[1] > 0.0f))));
			fVec67[(IOTA & 63)] = ((4.65661287e-10f * (fTemp1 * float((fRec69[0] > 0.0f)))) + (0.499019742f * ((fTemp4 * fRec68[2]) + (fTemp3 * fRec68[1]))));
			fRec68[0] = fVec67[((IOTA - 49) & 63)];
			float fTemp45 = (fRec66[0] + fRec68[0]);
			int iTemp46 = (fabsf((ftbl3[iRec4[0]] + -1.0f)) < 0.5f);
			iVec68[0] = iTemp46;
			fRec71[0] = ((fRec71[1] + float((float((iTemp46 - iVec68[1])) > 0.0f))) - (0.00296627614f * float((fRec71[1] > 0.0f))));
			fVec69[(IOTA & 511)] = ((4.65661287e-10f * (fTemp1 * float((fRec71[0] > 0.0f)))) + (0.493442565f * ((fTemp3 * fRec70[1]) + (fTemp4 * fRec70[2]))));
			fRec70[0] = fVec69[((IOTA - 336) & 511)];
			int iTemp47 = (fabsf((ftbl4[iRec4[0]] + -1.0f)) < 0.5f);
			iVec70[0] = iTemp47;
			fRec73[0] = ((fRec73[1] + float((float((iTemp47 - iVec70[1])) > 0.0f))) - (0.00593255227f * float((fRec73[1] > 0.0f))));
			fVec71[(IOTA & 255)] = ((4.65661287e-10f * (fTemp1 * float((fRec73[0] > 0.0f)))) + (0.496710479f * ((fTemp3 * fRec72[1]) + (fTemp4 * fRec72[2]))));
			fRec72[0] = fVec71[((IOTA - 167) & 255)];
			float fTemp48 = (fRec70[0] + fRec72[0]);
			output0[i] = FAUSTFLOAT((fSlow0 * ((1.5f * (((((((((((0.977008402f * fRec0[0]) + (0.929320395f * fRec8[0])) + (0.879049063f * fRec10[0])) + (0.825722814f * fRec12[0])) + (0.768706143f * fRec14[0])) + fTemp10) + (0.639602125f * fRec18[0])) + (0.564076066f * fRec20[0])) + (0.4767313f * fRec22[0])) + (0.369274467f * fRec24[0])) + (0.213200718f * fRec26[0]))) + ((0.879049063f * fTemp18) + ((0.213200718f * fTemp21) + (fTemp24 + ((0.4767313f * fTemp27) + ((0.768706143f * fTemp30) + ((0.564076066f * fTemp33) + ((0.639602125f * fTemp36) + ((0.825722814f * fTemp39) + ((0.929320395f * fTemp42) + ((0.369274467f * fTemp45) + (0.977008402f * fTemp48))))))))))))));
			output1[i] = FAUSTFLOAT((fSlow0 * ((1.5f * ((((((fTemp10 + ((((0.4767313f * fRec10[0]) + ((0.213200718f * fRec0[0]) + (0.369274467f * fRec8[0]))) + (0.564076066f * fRec12[0])) + (0.639602125f * fRec14[0]))) + (0.768706143f * fRec18[0])) + (0.825722814f * fRec20[0])) + (0.879049063f * fRec22[0])) + (0.929320395f * fRec24[0])) + (0.977008402f * fRec26[0]))) + ((0.4767313f * fTemp18) + ((0.977008402f * fTemp21) + (fTemp24 + ((0.879049063f * fTemp27) + ((0.639602125f * fTemp30) + ((0.825722814f * fTemp33) + ((0.768706143f * fTemp36) + ((0.564076066f * fTemp39) + ((0.369274467f * fTemp42) + ((0.213200718f * fTemp48) + (0.929320395f * fTemp45))))))))))))));
			iRec1[1] = iRec1[0];
			iRec2[1] = iRec2[0];
			iVec0[1] = iVec0[0];
			iVec1[1] = iVec1[0];
			iRec3[1] = iRec3[0];
			iRec4[1] = iRec4[0];
			iVec2[1] = iVec2[0];
			iRec6[1] = iRec6[0];
			iVec3[1] = iVec3[0];
			fRec5[1] = fRec5[0];
			fVec4[1] = fVec4[0];
			fRec7[1] = fRec7[0];
			IOTA = (IOTA + 1);
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			iVec6[1] = iVec6[0];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			iVec8[1] = iVec8[0];
			fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			iVec10[1] = iVec10[0];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			iVec12[1] = iVec12[0];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			iVec14[1] = iVec14[0];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			iVec16[1] = iVec16[0];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			iVec18[1] = iVec18[0];
			fRec21[1] = fRec21[0];
			fRec20[2] = fRec20[1];
			fRec20[1] = fRec20[0];
			iVec20[1] = iVec20[0];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			iVec22[1] = iVec22[0];
			fRec25[1] = fRec25[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			iVec24[1] = iVec24[0];
			fRec27[1] = fRec27[0];
			fRec26[2] = fRec26[1];
			fRec26[1] = fRec26[0];
			iVec26[1] = iVec26[0];
			iRec30[1] = iRec30[0];
			iVec27[1] = iVec27[0];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			iVec29[1] = iVec29[0];
			iRec33[1] = iRec33[0];
			iVec30[1] = iVec30[0];
			fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			iVec32[1] = iVec32[0];
			fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			iVec34[1] = iVec34[0];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			iVec36[1] = iVec36[0];
			fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			iVec38[1] = iVec38[0];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			iVec40[1] = iVec40[0];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			iVec42[1] = iVec42[0];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			iVec44[1] = iVec44[0];
			fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			iVec46[1] = iVec46[0];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			iVec48[1] = iVec48[0];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			iVec50[1] = iVec50[0];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			iVec52[1] = iVec52[0];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			iVec54[1] = iVec54[0];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			iVec56[1] = iVec56[0];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			iVec58[1] = iVec58[0];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			iVec60[1] = iVec60[0];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			iVec62[1] = iVec62[0];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			iVec64[1] = iVec64[0];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			iVec66[1] = iVec66[0];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			iVec68[1] = iVec68[0];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			iVec70[1] = iVec70[0];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			
		}
		
	}

	
};


#endif
