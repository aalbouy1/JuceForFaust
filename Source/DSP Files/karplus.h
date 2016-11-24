//----------------------------------------------------------
// name: "karplus32"
// version: "1.0"
// author: "Grame"
// license: "BSD"
// copyright: "(c)GRAME 2006"
//
// Code generated with Faust 0.9.73 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
/************************************************************************
 ************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 
 This is sample code. This file is provided as an example of minimal
 FAUST architecture file. Redistribution and use in source and binary
 forms, with or without modification, in part or in full are permitted.
 In particular you can create a derived work of this FAUST architecture
 and distribute that work under terms of your choice.
 
 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

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
 name: "karplus"
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
    float fVec1[512];
    float fRec0[3];
    float fVec0[2];
    float fRec2[2];
    FAUSTFLOAT fHslider0;
    FAUSTFLOAT fHslider1;
    FAUSTFLOAT fButton0;
    FAUSTFLOAT fHslider2;
    FAUSTFLOAT fHslider3;
    
public:
    
    void metadata(Meta* m) {
        m->declare("author", "Grame");
        m->declare("copyright", "(c)GRAME 2006");
        m->declare("delay.lib/name", "Faust Delay Library");
        m->declare("delay.lib/version", "0.0");
        m->declare("license", "BSD");
        m->declare("name", "karplus");
        m->declare("noise.lib/name", "Faust Noise Generator Library");
        m->declare("noise.lib/version", "0.0");
        m->declare("version", "1.0");
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
        fHslider0 = FAUSTFLOAT(0.10000000000000001f);
        fHslider1 = FAUSTFLOAT(0.5f);
        fButton0 = FAUSTFLOAT(0.0f);
        fHslider2 = FAUSTFLOAT(128.0f);
        fHslider3 = FAUSTFLOAT(128.0f);
        
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
        ui_interface->openVerticalBox("karplus");
        ui_interface->openVerticalBox("excitator");
        ui_interface->declare(&fHslider2, "unit", "f");
        ui_interface->addHorizontalSlider("excitation", &fHslider2, 128.0f, 2.0f, 512.0f, 1.0f);
        ui_interface->addButton("play",&fButton0);
        ui_interface->closeBox();
        ui_interface->addHorizontalSlider("level", &fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
        ui_interface->openVerticalBox("resonator");
        ui_interface->addHorizontalSlider("attenuation", &fHslider0, 0.100000001f, 0.0f, 1.0f, 0.00999999978f);
        ui_interface->declare(&fHslider3, "midi", "ctrl 7");
        ui_interface->declare(&fHslider3, "unit", "f");
        ui_interface->addHorizontalSlider("duration", &fHslider3, 128.0f, 2.0f, 512.0f, 1.0f);
        ui_interface->closeBox();
        ui_interface->closeBox();
        
    }
    
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
        FAUSTFLOAT* output0 = outputs[0];
        float fSlow0 = (0.5f * (1.0f - float(fHslider0)));
        float fSlow1 = (4.65661287e-10f * float(fHslider1));
        float fSlow2 = float(fButton0);
        float fSlow3 = (1.0f / float(fHslider2));
        int iSlow4 = (int((float(fHslider3) + -1.5f)) & 4095);
        for (int i = 0; (i < count); i = (i + 1)) {
            iRec1[0] = ((1103515245 * iRec1[1]) + 12345);
            fVec0[0] = fSlow2;
            fRec2[0] = ((float(((fSlow2 - fVec0[1]) > 0.0f)) + fRec2[1]) - (fSlow3 * float((fRec2[1] > 0.0f))));
            fVec1[(IOTA & 511)] = ((fSlow0 * (fRec0[1] + fRec0[2])) + (fSlow1 * float((iRec1[0] * (fRec2[0] > 0.0f)))));
            fRec0[0] = fVec1[((IOTA - iSlow4) & 511)];
            output0[i] = FAUSTFLOAT(fRec0[0]);
            iRec1[1] = iRec1[0];
            fVec0[1] = fVec0[0];
            fRec2[1] = fRec2[0];
            IOTA = (IOTA + 1);
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
            
        }
        
    }
    
    
};


#endif
