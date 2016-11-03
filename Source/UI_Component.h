//
//  UI_Compnent.h
//  Rectangle AudioApp
//
//  Created by Adrien Albouy on 17/10/2016.
//
//

#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "../JuceLibraryCode/JuceHeader.h"

#include "faust/gui/GUI.h"
#include "faust/gui/MetaDataUI.h"
#include "faust/gui/ValueConverter.h"

class faustBox;

enum sliderType{
    HSlider,
    VSlider,
    NumEntry,
    Knob
};

struct uiComponent: public Component, uiItem
{
    float vRatio, hRatio;
    int recomWidth, recomHeight;
    
    Slider slider;
    TextButton button;
    ToggleButton checkButton;
    
    void setCompSize(Rectangle<int> r){
        std::cout<<"New bounds of Component : {"<<r.toString()<<"}";
        std::cout<<", for parent : "<<getParentComponent()<<", "<<getParentComponent()->getBounds().toString()<<std::endl;
        std::cout<<"Ratios : "<<hRatio<<" "<<vRatio<<", Recommended Size : "<<recomWidth<<"x"<<recomHeight<<std::endl;
        Component::setSize(r.getWidth(), r.getHeight());
        setTopLeftPosition(r.getX() - getParentComponent()->getX(), r.getY() - getParentComponent()->getY());
    }
    
    float getHRatio(){
        return hRatio;
    }
    
    float getVRatio(){
        return vRatio;
    }
    
    int getRecommendedHeight(){
        return recomHeight;
    }
    
    int getRecommendedWidth(){
        return recomWidth;
    }
    
    void setVRatio(float ratio){
        vRatio = ratio;
    }
    
    void setHRatio(float ratio){
        hRatio = ratio;
    }
    
    virtual void paint(Graphics& g) = 0;
    virtual void resized() = 0;
    
    uiComponent(GUI* gui, FAUSTFLOAT* zone, int w, int h): uiItem(gui,zone), recomWidth(w), recomHeight(h)
    {
    }
};

struct uiSlider: public uiComponent,
private juce::Slider::Listener
{
private:
    
    Slider::SliderStyle style;
    Label label;
    String sliderName;
    ScopedPointer<ValueConverter> fConverter;
    int x, y, width, height;
    sliderType type;
    
public:
    uiSlider(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT cur, FAUSTFLOAT step, String name, String unit, MetaDataUI::Scale scale, sliderType kType) : uiComponent(gui, zone, w, h), sliderName(name), type(kType)
    {
        if (scale == MetaDataUI::kLog) 		{ fConverter = new LogValueConverter(min, max, min, max);   }
        else if (scale == MetaDataUI::kExp) { fConverter = new ExpValueConverter(min, max, min, max);   }
        else                                { fConverter = new LinearValueConverter(min, max, min, max);}
        
        switch(type){
            case HSlider:
                style = Slider::SliderStyle::LinearHorizontal;
                break;
            case VSlider:
                style = Slider::SliderStyle::LinearVertical;
                slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                break;
            case NumEntry:
                slider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_AutoDirection);
                style = Slider::SliderStyle::IncDecButtons;
                break;
            case Knob:
                style = Slider::SliderStyle::Rotary;
                slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                break;
                
            default:
                break;
        }
        addAndMakeVisible(slider);
        
        //Slider settings
        slider.setBounds(getBounds());
        slider.setRange(min, max, step);
        slider.setValue(fConverter->faust2ui(cur));
        slider.addListener(this);
        slider.setSliderStyle(style);
        slider.setTextValueSuffix(unit);
        
        //Label settings
        if(type == HSlider || type == NumEntry){
            label.setText(sliderName, dontSendNotification);
            label.attachToComponent(&slider, true);
            addAndMakeVisible (label);
        }
    }
    
    virtual void paint(Graphics& g) override{
        g.setColour (Colours::black);
        if(type == Knob || type == VSlider) { g.drawText(sliderName, slider.getLocalBounds(), Justification::centredTop); }
    }

    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        slider.setValue(fConverter->faust2ui(v));
    }

    void sliderValueChanged(Slider* slider) override
    {
        float value = slider->getValue();
        std::cout<<sliderName<<" : "<<value<<std::endl;
        modifyZone(value);
    }

    virtual void resized() override{
        std::cout<<sliderName<<", ";
        if(type == HSlider){
            x = getLocalBounds().reduced(3).getX() + 60; y = getLocalBounds().reduced(3).getY();
            width = getLocalBounds().reduced(3).getWidth()-60; height = getLocalBounds().reduced(3).getHeight();
        }
        else if(type == NumEntry){
            width = kNumEntryWidth-6; height = kNumEntryHeight-6;
            x = (getLocalBounds().reduced(3).getWidth()-width)/2; y = (getLocalBounds().reduced(3).getHeight()-height)/2;
        }
        else{
            x = getLocalBounds().reduced(3).getX(); y = getLocalBounds().reduced(3).getY()+10;
            height = getLocalBounds().reduced(3).getHeight()-20; width = getLocalBounds().reduced(3).getWidth();
        }
        slider.setBounds(x, y, width, height);
    }
};

struct uiButton: public uiComponent,
private juce::Button::Listener
{
private:
    
    String name;
    int x, y, width, height;
    
public:
    uiButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label) :  uiComponent(gui, zone, w, h), name(label), width(w), height(h)
    {
        x = getLocalBounds().getX()+10;
        width = kCheckButtonWidth;
        height = kCheckButtonHeight;
        y = roundToInt((getLocalBounds().getHeight()-height)/2);
        
        button.setButtonText(label);
        button.setBounds(x, y, width, height);
        button.addListener(this);
        
        addAndMakeVisible(button);
    }
    
    void buttonClicked (Button* button) override
    {
    }
    
    void buttonStateChanged (Button* button) override
    {
        if(button->isDown()) { modifyZone(1.0); }
        else { modifyZone(0.0); }
    }
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
    }
    
    virtual void paint(Graphics& g) override
    {
    }
    
    virtual void resized() override
    {
        x = getLocalBounds().getX()+10;
        height = getLocalBounds().reduced(3).getHeight();
        width = getLocalBounds().getWidth()-20;
        y = roundToInt((getLocalBounds().getHeight()-height)/2);
        button.setBounds(x, y, width, height);
    }
};

struct uiCheckButton: public uiComponent,
private juce::Button::Listener
{
private:
    
    String name;
    int x, y, width, height;
    
public:
    uiCheckButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label) :  uiComponent(gui, zone, w, h), name(label), width(w), height(h)
    {
        x = roundToInt(getLocalBounds().getX() + 10);
        y = roundToInt((getLocalBounds().getHeight()-kCheckButtonHeight)/2);
        
        checkButton.setButtonText(label);
        checkButton.setBounds(x, y, width, height);
        checkButton.addListener(this);
        
        addAndMakeVisible(checkButton);
    }
    
    void buttonClicked(Button* button)
    {
    }
    
    void buttonStateChanged (Button* button) override
    {
        if(button->isDown()) { modifyZone(1.0); }
        else { modifyZone(0.0); }
    }
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
    }
    
    
    
    virtual void paint(Graphics& g) override
    {
    }
    
    virtual void resized() override
    {
        std::cout<<"RESIZING CHECKBUTTON"<<std::endl;
        x = roundToInt(getLocalBounds().getX()+10);
        y = roundToInt((getLocalBounds().getHeight()-kCheckButtonHeight)/2);
        checkButton.setBounds(x, y, width, kCheckButtonHeight);
    }
};

class VUMeter  : public uiComponent,
public Timer
{
public:
    VUMeter (GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, FAUSTFLOAT mini, FAUSTFLOAT maxi, bool vert)
    : uiComponent(gui, zone, w, h), min(mini), max(maxi), vertical(vert)
    {
        level = 0;
        startTimer (50);
        
        // Set tresholds here, need to be included in [0;1]
        orangeTreshold = 0.75f;
        redTreshold = 0.9f;
    }
    
    void setLevel(){
        float rawLevel = *fZone;
        
        newLevel = (rawLevel-min)/(max-min);
        if(level > 1){ newLevel = 1; }
        else if(level < 0){ newLevel = 0; }
    }
    
    void timerCallback() override
    {
        if (isShowing())
        {
            setLevel();
            level = newLevel;
            repaint();
        }
        else
        {
            level = 0;
        }
    }
    
    void paint (Graphics& g) override
    {
        if(vertical){ drawVBargraph (g, getWidth(), getHeight(), (float) exp (log (level) / 3.0)); }
        else{ drawHBargraph (g, getWidth(), getHeight(), (float) exp (log (level) / 3.0)); }
        // (add a bit of a skew to make the level more obvious)
    }
    
    void resized() override{
    }
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
    }
    
private:
    float level, newLevel;
    float min, max;
    bool vertical;
    float orangeTreshold, redTreshold;
    
    void drawHBargraph(Graphics& g, int width, int height, float level){
        g.setColour(Colours::black);
        g.fillRect(0.0f, 0.0f, (float) width, (float) height);
        g.setColour(Colours::white);
        g.fillRect(1.0f, 1.0f, (float) width-2, (float) height-2);
        
        
        if(level > 1){ level = 1; }
        else if(level < 0){ level = 0; }
        
        if(level >= 0.0f && level <= 1.0f){
            g.setColour(Colours::green);
            g.fillRect(1.0f, 1.0f, (float) level*(width-2), (float) height-2);
            
            if(level > orangeTreshold){
                g.setColour(Colours::orange);
                g.fillRect((float) (orangeTreshold * (width-2)) + 1.0f, 1.0f, (float)(level-orangeTreshold) * (width - 2), (float) height-2);
            }
            if(level > redTreshold){
                g.setColour(Colours::red);
                g.fillRect((float) (redTreshold * (width-2)) + 1.0f, 1.0f, (float)(level-redTreshold) * (width - 2), (float) height-2);
            }
        }
    }
    
    void drawVBargraph(Graphics& g, int width, int height, float level){
        g.setColour(Colours::black);
        g.fillRect(0.0f, 0.0f, (float) width, (float) height);
        g.setColour(Colours::white);
        g.fillRect(1.0f, 1.0f, (float) width-2, (float) height-2);
        
        
        if(level > 1){ level = 1; }
        else if(level < 0){ level = 0; }
        
        if(level >= 0.0f && level <= 1.0f){
            g.setColour(Colours::green);
            g.fillRect(1.0f, (float) (1.0f-level)*(height-2) + 1.0f, (float) width-2, (float) level*(height-2));
            
            if(level > orangeTreshold){
                g.setColour(Colours::orange);
                g.fillRect(1.0f, (float) (1.0f-level) * (height-2) + 1.0f, (float) width-2, (float)(level-orangeTreshold) * (height - 2));
            }
            if(level > redTreshold){
                g.setColour(Colours::red);
                g.fillRect(1.0f, (float) (1.0f-level) * (height-2) + 1.0f, (float) width-2, (float)(level-redTreshold) * (height - 2));
            }
        }
    }
    
    // Another style
    void drawHorizontalLevelMeter (Graphics& g, int width, int height, float level)
    {
        g.setColour (Colours::white.withAlpha (0.7f));
        g.fillRoundedRectangle (0.0f, 0.0f, (float) width, (float) height, 3.0f);
        g.setColour (Colours::black.withAlpha (0.2f));
        g.drawRoundedRectangle (1.0f, 1.0f, width - 2.0f, height - 2.0f, 3.0f, 1.0f);
        
        const int totalBlocks = 7;
        const int numBlocks = roundToInt (totalBlocks * level);
        const float w = (width - 6.0f) / (float) totalBlocks;
        
        for (int i = 0; i < totalBlocks; ++i)
        {
            if (i >= numBlocks)
                g.setColour (Colours::lightgrey.withAlpha (0.6f));
            else{
                if(i < totalBlocks - 3){ g.setColour(Colours::green); }
                else if(i < totalBlocks - 1){ g.setColour(Colours::orange); }
                else{ g.setColour(Colours::red); }
            }
            
            g.fillRect (3.0f + i * w + w * 0.1f, 3.0f, w * 0.8f, height - 6.0f);
        }
    }
    
    void drawVerticalLevelMeter (Graphics& g, int width, int height, float level)
    {
        g.setColour (Colours::white.withAlpha (0.7f));
        g.fillRoundedRectangle (0.0f, 0.0f, (float) width, (float) height, 3.0f);
        g.setColour (Colours::black.withAlpha (0.2f));
        g.drawRoundedRectangle (1.0f, 1.0f, width - 2.0f, height - 2.0f, 3.0f, 1.0f);
        
        const int totalBlocks = 7;
        const int numBlocks = roundToInt (totalBlocks * level);
        const float h = (height - 6.0f) / (float) totalBlocks;
        
        for (int i = 0; i < totalBlocks; ++i)
        {
            if (i >= numBlocks)
                g.setColour (Colours::lightgrey.withAlpha (0.6f));
            else{
                if(i < totalBlocks - 3){ g.setColour(Colours::green); }
                else if(i < totalBlocks - 1){ g.setColour(Colours::orange); }
                else{ g.setColour(Colours::red); }
            }
            
            g.fillRect(3.0f, 3.0f + i * h + h * 0.1f, width - 6.0f, h * 0.8f);
        }
    }
};

#endif
