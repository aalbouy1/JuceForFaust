/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "faust_layout.h"


// Select here the compiled DSP that you want to execute
#include "DSP files/noise.h"                  //OK
//#include "DSP files/kisana.h"                 //OK
//#include "DSP files/kisana - copie.h"         //OK
//#include "DSP Files/matrix.h"                 //OK
//#include "DSP files/karplus.h"                //OK
//#include "DSP Files/karplus32.h"              //OK
//#include "DSP Files/karplus_synth.h"          //OK
//#include "DSP Files/karplus32bis.h"           //OK
//#include "DSP Files/UITester.h"               //OK
//#include "DSP Files/cubic_distortion.h"       //OK
//#include "DSP Files/cubic_distortion-NumDisplay.h"   //OK
//#include "DSP Files/cubic_distortion-LED.h"   //OK
//#include "DSP Files/cubic_distortion-Horiz.h" //OK
//#include "DSP Files/tester2.h"                //OK

//#include "faust/dsp/poly-dsp.h"

std::list<GUI*> GUI::fGuiList;

class MainContentComponent   : public AudioAppComponent, private Timer
{
public:
    //==============================================================================
    MainContentComponent()
    {
        fDSP = new mydsp();
        
        //-----------------------------------------------
        // Polyphonic DSP built using a single DSP voice
        //-----------------------------------------------
        
        //fDSP = new mydsp_poly(fDSP.release(), 32, true);
        
        fDSP->buildUserInterface(&layout);
        
        addAndMakeVisible(layout);
        
        layout.init();
        
        recommendedSize = layout.getSize();
        setSize (recommendedSize.getWidth(), recommendedSize.getHeight());

        // specify the number of input and output channels that we want to open
        if(fDSP->getNumInputs() < 3 && fDSP->getNumOutputs() < 3){
            setAudioChannels (fDSP->getNumInputs(), fDSP->getNumOutputs());
        }
        startTimerHz(25);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void timerCallback() override
    {
        GUI::updateAllGuis();
    }
     
    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        fDSP->init(int(sampleRate));
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        const float* inputs[fDSP->getNumInputs()];
        for (int i = 0; i < fDSP->getNumInputs(); i++) {
            inputs[i] = bufferToFill.buffer->getReadPointer(i, bufferToFill.startSample);
        }
        
        float* outputs[fDSP->getNumOutputs()];
        for (int i = 0; i < fDSP->getNumOutputs(); i++) {
            outputs[i] = bufferToFill.buffer->getWritePointer(i, bufferToFill.startSample);
        }
        
        fDSP->compute(bufferToFill.numSamples, (float**)inputs, outputs);
    }

    void releaseResources() override
    {
        
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colour (Colours::lightblue));
    }

    void resized() override
    {
        std::cout<<std::endl<<"RESIZING"<<std::endl<<std::endl;
        layout.setSize(getLocalBounds());
        layout.setBounds(getLocalBounds());
    }

    Rectangle<int> getMinSize(){
        //return recommendedSize;
        return Rectangle<int>(0, 0, jmin(recommendedSize.getWidth(), screenWidth), jmin(recommendedSize.getHeight(), screenHeight));
    }

    Rectangle<int> getRecommendedSize(){
        return recommendedSize;
    }

private:
    Faust_layout layout;

    ScopedPointer<dsp> fDSP;

    Rectangle<int> recommendedSize;
    Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    int screenWidth  = r.getWidth();
    int screenHeight = r.getHeight();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
MainContentComponent* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
