//
//  UI_Compnent.h
//  Rectangle AudioApp
//
//  Created by Adrien Albouy on 17/10/2016.
//
//

#ifndef Rectangle_AudioApp_UI_Component_h
#define Rectangle_AudioApp_UI_Component_h

#include "faust/gui/GUI.h"
#include "faust/gui/MetaDataUI.h"
#include "faust/gui/ValueConverter.h"

#include "faust_box.h"
#include "../JuceLibraryCode/JuceHeader.h"

enum componentType{
    HSlider,
    VSlider,
    NumEntry,
    Knob,
    RegularButton
};

struct uiComponent: public Component, uiItem
{
private:
    
    faustBox* parent;
    float vRatio, hRatio;
    int recomWidth, recomHeight;
    
public:
    Slider slider;
    TextButton button;
    
    faustBox* getParent(){
        return parent;
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
    
    uiComponent(GUI* gui, faustBox* par, FAUSTFLOAT* zone, int w, int h): uiItem(gui,zone), parent(par), recomWidth(w), recomHeight(h) {}
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
    bool horizontal;
    componentType type;
    
public:
    uiSlider(GUI* gui, faustBox* par, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT cur, FAUSTFLOAT step, String name, String unit, MetaDataUI::Scale scale, componentType kType) : uiComponent(gui, par, zone, w, h), sliderName(name), type(kType)
    {
        if (scale == MetaDataUI::kLog) 		{ fConverter = new LogValueConverter(min, max, min, max);   }
        else if (scale == MetaDataUI::kExp) { fConverter = new ExpValueConverter(min, max, min, max);   }
        else                                { fConverter = new LinearValueConverter(min, max, min, max);}
        
        switch(type){
            case HSlider:
                style = Slider::SliderStyle::LinearHorizontal;
                horizontal = true;
                break;
            case VSlider:
                style = Slider::SliderStyle::LinearVertical;
                slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                horizontal = false;
                break;
            case NumEntry:
                slider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_AutoDirection);
                style = Slider::SliderStyle::IncDecButtons;
                horizontal = true;
                break;
            case Knob:
                style = Slider::SliderStyle::Rotary;
                slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                horizontal = false;
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
        if(horizontal){
            label.setText(sliderName, dontSendNotification);
            label.attachToComponent(&slider, horizontal);
            addAndMakeVisible (label);
        }
    }
    
    virtual void paint(Graphics& g) override{
        /*g.setColour(Colours::darkblue);
        std::cout<<"Painting bounds : "<<getBounds().toString()<<std::endl;
        g.fillRect(getBounds());*/
    
        g.setColour (Colours::black);
        if(!horizontal){
            if(type == Knob) { g.drawText(sliderName, slider.getLocalBounds().withHeight(20), Justification::centredBottom); }
            else{ g.drawText(sliderName, slider.getLocalBounds().withHeight(25), Justification::centredBottom); }
        }
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
        if(horizontal){ x = getLocalBounds().reduced(3).getX() + 60; y = getLocalBounds().reduced(3).getY(); width = getLocalBounds().reduced(3).getWidth()-60; height = getLocalBounds().reduced(3).getHeight(); }
        else{ x = getLocalBounds().reduced(3).getX(); y = getLocalBounds().reduced(3).getY()+20; height = getLocalBounds().reduced(3).getHeight()-20; width = getLocalBounds().reduced(3).getWidth(); }
        slider.setBounds(x, y, width, height);
    }
};

struct uiButton: public uiComponent,
private juce::Button::Listener
{
private:
    
    String name;
    int x, y, width, height;
    componentType type;
    
public:
    uiButton(GUI* gui, faustBox* par, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, componentType kType) :  uiComponent(gui, par, zone, w, h), name(label), width(w), height(h), type(kType)
    {
        x = getLocalBounds().getX()+10;
        height = getLocalBounds().reduced(3).getHeight();
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
        height = jmin(kButtonHeight, getLocalBounds().reduced(3).getHeight());
        x = getLocalBounds().getX()+10;
        y = roundToInt((getLocalBounds().getHeight()-height)/2);
        button.setBounds(x, y, getLocalBounds().getWidth()-20, height);
    }
};

#endif
