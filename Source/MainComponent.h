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
//#include "DSP files/noise.h"
//#include "DSP files/kisana.h"
//#include "DSP Files/matrix.h"
//#include "DSP files/karplus.h"
//#include "DSP Files/karplus32.h"
//#include "DSP Files/karplus32bis.h"
#include "DSP Files/UITester.h"
//#include "DSP Files/cubic_distortion.h"

std::list<GUI*> GUI::fGuiList;
extern int windowWidth;
extern int windowHeight;

class MainContentComponent   : public AudioAppComponent, private Timer
{
public:
    //==============================================================================
    MainContentComponent()
    {
        fDSP = new mydsp();
        
        fDSP->buildUserInterface(&layout);
        addAndMakeVisible(layout);
        
        recommendedSize = layout.getSize();
        
        windowWidth = recommendedSize.getWidth();
        windowHeight = recommendedSize.getHeight();
        setSize (windowWidth, windowHeight);

        // specify the number of input and output channels that we want to open
        //setAudioChannels (fDSP->getNumInputs(), fDSP->getNumOutputs());
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
        windowWidth = getLocalBounds().getWidth();
        windowHeight = getLocalBounds().getHeight();
        layout.setSize(getLocalBounds());
        layout.setBounds(getLocalBounds());
    }

    Rectangle<int> getMinSize(){
        return recommendedSize;
    }

private:
    Faust_layout layout;
    ScopedPointer<mydsp> fDSP;

    Rectangle<int> recommendedSize;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
MainContentComponent* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
