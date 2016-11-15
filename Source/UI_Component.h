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

enum SliderType{
    HSlider,
    VSlider,
    NumEntry,
    Knob
};

enum VUMeterType{
    HVUMeter,
    VVUMeter,
    Led,
    NumDisplay
};

struct uiComponent: public Component, uiItem, SettableTooltipClient
{
    float vRatio, hRatio;
    int recomWidth, recomHeight;
    String tooltipText;
    
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
    
    uiComponent(GUI* gui, FAUSTFLOAT* zone, int w, int h, String tooltip): uiItem(gui,zone), recomWidth(w), recomHeight(h), tooltipText(tooltip)
    {
        std::cout<<"TOOLTIP : "<<tooltipText<<std::endl;
    }
};

class uiSlider: public uiComponent,
private juce::Slider::Listener
{
private:
    
    Slider::SliderStyle style;
    Label label;
    String sliderName;
    ScopedPointer<ValueConverter> fConverter;
    int x, y, width, height;
    SliderType type;
    Slider slider;
    
public:
    uiSlider(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT cur, FAUSTFLOAT step, String name, String unit, String tooltip, MetaDataUI::Scale scale, SliderType kType) : uiComponent(gui, zone, w, h, tooltip), sliderName(name), type(kType)
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
        if(tooltipText.isNotEmpty()){ slider.setTooltip(tooltipText); }
        
        //Label settings
        if(type == HSlider || type == NumEntry){
            label.setText(sliderName, dontSendNotification);
            label.attachToComponent(&slider, true);
            addAndMakeVisible (label);
            if(tooltipText.isNotEmpty()){ label.setTooltip(tooltipText); }
        }
    }
    
    virtual void paint(Graphics& g) override{
        g.setColour (Colours::black);
        if(type == Knob || type == VSlider) { g.drawText(sliderName, getParentComponent()->getLocalBounds().withTrimmedTop(9), Justification::centredTop); }
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
            x = getLocalBounds().reduced(3).getX(); y = getLocalBounds().reduced(3).getY()+15;
            height = getLocalBounds().reduced(3).getHeight()-25; width = getLocalBounds().reduced(3).getWidth();
        }
        slider.setBounds(x, y, width, height);
    }
};

class uiButton: public uiComponent,
private juce::Button::Listener
{
private:
    
    String name;
    int x, y, width, height;
    TextButton button;
    
public:
    uiButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, String tooltip) :  uiComponent(gui, zone, w, h, tooltip), name(label), width(w), height(h)
    {
        x = getLocalBounds().getX()+10;
        width = kCheckButtonWidth;
        height = kCheckButtonHeight;
        y = roundToInt((getLocalBounds().getHeight()-height)/2);
        
        button.setButtonText(label);
        button.setBounds(x, y, width, height);
        button.addListener(this);
        if(tooltipText.isNotEmpty()){ button.setTooltip(tooltipText); }
        
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

class uiCheckButton: public uiComponent,
private juce::Button::Listener
{
private:
    
    String name;
    int x, y, width, height;
    ToggleButton checkButton;
    
public:
    uiCheckButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, String tooltip) :  uiComponent(gui, zone, w, h, tooltip), name(label), width(w), height(h)
    {
        x = roundToInt(getLocalBounds().getX() + 10);
        y = roundToInt((getLocalBounds().getHeight()-kCheckButtonHeight)/2);
        
        if(tooltipText.isNotEmpty()){ setTooltip(tooltipText); }
        
        checkButton.setButtonText(label);
        checkButton.setBounds(x, y, width, height);
        checkButton.addListener(this);
        if(tooltipText.isNotEmpty()){ checkButton.setTooltip(tooltipText); }
        
        addAndMakeVisible(checkButton);
    }
    
    void buttonClicked(Button* button)
    {
    }
    
    void buttonStateChanged (Button* button) override
    {
        std::cout<<name<<" : "<<button->getToggleState()<<std::endl;
        modifyZone(button->getToggleState());
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

class VUMeter  : public uiComponent, public Timer
{
public:
    VUMeter (GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, FAUSTFLOAT mini, FAUSTFLOAT maxi, String unit, String tooltip, VUMeterType style, bool vert)
    : uiComponent(gui, zone, w, h, tooltip), min(mini), max(maxi), fStyle(style)
    {
        level = 0;
        startTimer (50);
        this->unit = unit;
        (unit == "dB") ? db = true : db = false;
        fScaleMin = dB2Scale(min);
        fScaleMax = dB2Scale(max);
        
        if(tooltipText.isNotEmpty()){ setTooltip(tooltipText); }
        if(fStyle != Led){ setupTextEditor(); }
    }
    
    void timerCallback() override
    {
        if (isShowing())
        {
            setLevel();
            repaint();
        }
        else
        {
            level = 0;
        }
    }
    
    void paint (Graphics& g) override
    {
        if(fStyle == Led){ drawLed (g, kLedWidth, kLedHeight, level); }
        else if(fStyle == NumDisplay){ drawNumDisplay(g, kNumDisplayWidth, kNumDisplayHeight, level); }
        else{
            if(db){
                if(fStyle == VVUMeter){ drawVBargraphDB (g, kVBargraphWidth/2 , getHeight(), level); }
                else{                   drawHBargraphDB (g, getWidth(), kHBargraphHeight, level); }
            }
        }
    }
    
    void resized() override{
        setTextEditorPos();
    }
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
    }
    
private:
    float level;
    float min, max;
    float fScaleMin, fScaleMax;
    bool db;
    VUMeterType fStyle;
    String unit;
    Label label;
    
    void setTextEditorPos(){
        if(fStyle == VVUMeter)        { label.setBounds((getWidth()-50)/2, getHeight()-22, 50, 20); }
        else if(fStyle == NumDisplay) { label.setBounds(getLocalBounds().getX(), (getLocalBounds().getHeight()-kNumDisplayHeight/2+11)/2, jmax(1,jmin(kNumDisplayWidth, getWidth())), kNumDisplayHeight/2); }
        //else                          { label.setBounds((getWidth()-75)/2, getHeight()-22, 75, 20); } // todo
    }
    
    void setupTextEditor(){
        setTextEditorPos();
        label.setEditable(false, false, false);
        label.setJustificationType(Justification::centred);
        label.setText(String((int)*fZone) + unit, dontSendNotification);
        if(tooltipText.isNotEmpty()){ label.setTooltip(tooltipText); }
        
        addAndMakeVisible(label);
    }
    
    void drawHBargraphDB(Graphics& g, int width, int height, float level){
        float x = (float)(getWidth()-width)/2;
        float y = (float)(getHeight()-height)/2;
        
        g.setColour(Colours::lightgrey);
        g.fillRect(x, y, (float) width, (float) height);
        g.setColour(Colours::black);
        g.fillRect(x+1.0f, y+1.0f, (float) width-2, (float) height-2);
        
        // Drawing Scale
        g.setFont(9.0f);
        g.setColour(Colours::white);
        for(int i = -10; i > min; i -= 10){ paintScale(g, i); }
        for(int i = -6; i < max; i += 3)  { paintScale(g, i); }
        
        int alpha = 200;
        
        g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
        g.fillRect(dB2x(min), y+1.0f, jmin(dB2x(level), dB2x(-10)), (float) height-2);
        
        if(dB2Scale(level) > dB2Scale(-10)){
            g.setColour(Colour((uint8)160, (uint8)220, (uint8)20, (uint8)alpha));
            g.fillRect(dB2x(-10), y+1.0f, jmin(dB2x(level)-dB2x(-10), dB2x(-6)-dB2x(-10)), (float) height-2);
        }
        if(dB2Scale(level) > dB2Scale(-6)){
            g.setColour(Colour((uint8)220, (uint8)220, (uint8)20, (uint8)alpha));
            g.fillRect(dB2x(-6), y+1.0f, jmin(dB2x(level)-dB2x(-6), dB2x(-3)-dB2x(-6)), (float) height-2);
        }
        if(dB2Scale(level) > dB2Scale(-3)){
            g.setColour(Colour((uint8)240, (uint8)160, (uint8)20, (uint8)alpha));
            g.fillRect(dB2x(-3), y+1.0f, jmin(dB2x(level)-dB2x(-3), dB2x(0)-dB2x(-3)), (float) height-2);
        }
        if(dB2Scale(level) > dB2Scale(0)){
            g.setColour(Colour((uint8)240,  (uint8)0, (uint8)20, (uint8)alpha));
            g.fillRect(dB2x(0), y+1.0f, jmin(dB2x(level)-dB2x(0), dB2x(max)-dB2x(0)), (float) height-2);
        }
    }
    
    void drawVBargraphDB(Graphics& g, int width, int height, float level){
        float x = (float)(getLocalBounds().getWidth()-width)/2;
        float y = (float) getLocalBounds().getHeight()-height+15;
        height -= 40;
        
        g.setColour(Colours::lightgrey);
        g.fillRect(x, y, (float) width, (float) height);
        g.setColour(Colours::black);
        g.fillRect(x+1.0f, y+1.0f, (float) width-2, (float) height-2);
        
        // Label window
        g.setColour(Colours::darkgrey);
        g.fillRect((getWidth()-50)/2-1, getHeight()-23, 52, 22);
        g.setColour(Colours::white.withAlpha(0.8f));
        g.fillRect((getWidth()-50)/2, getHeight()-22, 50, 20);
        
        // Drawing Scale
        g.setFont(9.0f);
        g.setColour(Colours::white);
        for(int i = -10; i > min; i -= 10){ paintScale(g, i); }
        for(int i = -6; i < max; i += 3)  { paintScale(g, i); }
        
        
        int alpha = 200;
        g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
        g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(-10)), (float) width-2, dB2y(min)-jmax(dB2y(level), dB2y(-10)));
        
        if(dB2Scale(level) > dB2Scale(-10)){
            g.setColour(Colour((uint8)160, (uint8)220, (uint8)20, (uint8)alpha));
            g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(-6)), (float) width-2, dB2y(-10)-jmax(dB2y(level), dB2y(-6)));
        }
        if(dB2Scale(level) > dB2Scale(-6)){
            g.setColour(Colour((uint8)220, (uint8)220, (uint8)20, (uint8)alpha));
            g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(-3)), (float) width-2, dB2y(-6)-jmax(dB2y(level), dB2y(-3)));
        }
        if(dB2Scale(level) > dB2Scale(-3)){
            g.setColour(Colour((uint8)240, (uint8)160, (uint8)20, (uint8)alpha));
            g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(0)), (float) width-2, dB2y(-3)-jmax(dB2y(level), dB2y(0)));
        }
        if(dB2Scale(level) > dB2Scale(0)){
            g.setColour(Colour((uint8)240,  (uint8)0, (uint8)20, (uint8)alpha));
            g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(max)), (float) width-2, dB2y(0)-jmax(dB2y(level), dB2y(max)));
        }
    }
    
    void drawLed(Graphics& g, int width, int height, float level){
        float x = (float) getLocalBounds().getX();
        float y = (float) getLocalBounds().getY();
        g.setColour(Colours::black);
        g.fillEllipse(x, y, kLedWidth, kLedHeight);
        if(db){
            int alpha = 200;
            g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
            if(dB2Scale(level) > dB2Scale(-10)){ g.setColour(Colour((uint8)160, (uint8)220, (uint8)20, (uint8)alpha)); }
            if(dB2Scale(level) > dB2Scale(-6)) { g.setColour(Colour((uint8)220, (uint8)220, (uint8)20, (uint8)alpha)); }
            if(dB2Scale(level) > dB2Scale(-3)) { g.setColour(Colour((uint8)240, (uint8)160, (uint8)20, (uint8)alpha)); }
            if(dB2Scale(level) > dB2Scale(0))  { g.setColour(Colour((uint8)240, (uint8)0,   (uint8)20, (uint8)alpha)); }
            
            g.fillEllipse(x+1, y+1, kLedWidth-2, kLedHeight-2);
        }
        else{
            g.setColour(Colours::red.withAlpha((float)level));
            g.fillEllipse(x+1, y+1, kLedWidth-2, kLedHeight-2);
        }
    }
    
    void drawNumDisplay(Graphics& g, int width, int height, float level){
        int x = getLocalBounds().getX();
        int y = (getLocalBounds().getHeight()-kNumDisplayHeight/2+11)/2;
        //Draw box
        g.setColour(Colours::darkgrey);
        g.fillRect(x, y, jmax(1,jmin(kNumDisplayWidth, getWidth())), kNumDisplayHeight/2);
        g.setColour(Colours::white.withAlpha(0.8f));
        g.fillRect(x+1, y+1, jmax(1,jmin(kNumDisplayWidth, getWidth()))-2, kNumDisplayHeight/2-2);
    }
    
    float dB2Scale(float dB)
    {
        float fScale = 1.0;
        
         if (dB < -60.0)
             fScale = (dB + 70.0) * 0.0025;
         else if (dB < -50.0)
             fScale = (dB + 60.0) * 0.005 + 0.025;
         else if (dB < -40.0)
             fScale = (dB + 50.0) * 0.0075 + 0.075;
         else if (dB < -30.0)
             fScale = (dB + 40.0) * 0.015 + 0.15;
         else if (dB < -20.0)
             fScale = (dB + 30.0) * 0.02 + 0.3;
         else if (dB < -0.001 || dB > 0.001)  /* if (dB < 0.0) */
             fScale = (dB + 20.0f) * 0.025 + 0.5;
        
        return fScale;
    }
    
    float dB2y(float dB)
    {
        FAUSTFLOAT s0 = fScaleMin;
        FAUSTFLOAT s1 = fScaleMax;
        FAUSTFLOAT sx = dB2Scale(dB);
        int    h = getHeight()-42;
        return (h - h*(s0-sx)/(s0-s1))+16;
    }
    
    float dB2x(float dB)
    {
        FAUSTFLOAT s0 = fScaleMin;
        FAUSTFLOAT s1 = fScaleMax;
        FAUSTFLOAT sx = dB2Scale(dB);
        int    w = getWidth()-2;
        return w - w*(s1-sx)/(s1-s0)+1;
    }
    
    void paintScale(Graphics& g, int num){
        if(fStyle == VVUMeter){
            Rectangle<int> r = Rectangle<int>((getWidth()-(kVBargraphWidth/2))/2, dB2y(num)-10, (kVBargraphWidth/2)-2, 20);
            g.drawText(String(num), r, Justification::centredRight, false);
        }
        else{
            Rectangle<int> r = Rectangle<int>(dB2x(num)-10,(getHeight()-kHBargraphHeight)/2 +1, 20, kHBargraphHeight-2);
            g.drawText(String(num), r, Justification::centredTop, false);
        }
    }
    
    void setLevel(){
        float rawLevel = *fZone;
        
        if(db){
            level = rawLevel;
            if(level > max)     { level = max; }
            else if(level < min){ level = min; }
        }
        else{
            level = (rawLevel-min)/(max-min);
            if(level > 1)       { level = 1; }
            else if(level < 0)  { level = 0; }
        }
        
        label.setText(String((int)rawLevel)+unit, dontSendNotification);
    }
};

#endif
