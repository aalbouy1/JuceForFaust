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
    
    virtual void setVRatio(float ratio){
        vRatio = ratio;
    }
    
    virtual void setHRatio(float ratio){
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
        if (scale == MetaDataUI::kLog) 		{
            fConverter = new LogValueConverter(min, max, min, max);
            slider.setSkewFactor(0.5);
        }
        else if (scale == MetaDataUI::kExp) {
            fConverter = new ExpValueConverter(min, max, min, max);
            slider.setSkewFactor(2.0);
        }
        else { fConverter = new LinearValueConverter(min, max, min, max);}
        
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
        if(type == VSlider || type == Knob) { g.drawText(sliderName, getLocalBounds(), Justification::centredTop); }
        //else if(type == Knob) { g.drawText(sliderName, getLocalBounds(), Justification::centredTop); }
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
            width = kNumEntryWidth-10; height = kNumEntryHeight-15;
            x = (getLocalBounds().reduced(3).getWidth()-width)/2; y = (getLocalBounds().reduced(3).getHeight()-height)/2;
        }
        else{
            x = getLocalBounds().reduced(3).getX(); y = getLocalBounds().reduced(3).getY()+11;
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
        y = (getLocalBounds().getHeight()-height)/2;
        
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
        y = (getLocalBounds().getHeight()-height)/2;
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
    uiCheckButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, String tooltip) : uiComponent(gui, zone, w, h, tooltip), name(label), width(w), height(h)
    {
        x = getLocalBounds().getX() + 10;
        y = (getLocalBounds().getHeight()-height)/2;
        
        if(tooltipText.isNotEmpty()){ setTooltip(tooltipText); }
        
        checkButton.setButtonText(label);
        checkButton.setBounds(x, y, width, height);
        checkButton.addListener(this);
        if(tooltipText.isNotEmpty()){ checkButton.setTooltip(tooltipText); }
        
        addAndMakeVisible(checkButton);
    }
    
    void buttonClicked(Button* button)
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
        x = getLocalBounds().getX();
        y = getLocalBounds().getY();
        checkButton.setBounds(x, y, jmin(getLocalBounds().getWidth(), width), jmin(getLocalBounds().getHeight(), height));
    }
};

class uiMenu: public uiComponent,
private juce::ComboBox::Listener
{
private:
    ComboBox fComboBox;
    String name;
    int x, y, width, height;
    int nbItem;
    vector<double> fValues;
    
public:
    uiMenu(GUI* gui, FAUSTFLOAT* zone, String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, String tooltip, const char* mdescr) : uiComponent(gui, zone, w, h, tooltip), name(label), width(w), height(h)
    {
        //Init ComboBox parameters
        fComboBox.setEditableText(false);
        fComboBox.setJustificationType(Justification::centred);
        fComboBox.addListener(this);
        addAndMakeVisible(fComboBox);
        
        vector<string>  names;
        vector<double>  values;
        
        if (parseMenuList(mdescr, names, values)) {
            
            int     defaultitem = -1;
            double  mindelta = FLT_MAX;
            
            for (int i = 0; i < names.size(); i++) {
                double v = values[i];
                if ( (v >= lo) && (v <= hi) ) {
                    
                    // It is a valid value : add corresponding menu item
                    fComboBox.addItem(String(names[i].c_str()), v+1);
                    fValues.push_back(v);
                    
                    // Check if this item is a good candidate to represent the current value
                    double delta = fabs(cur-v);
                    if (delta < mindelta) {
                        mindelta = delta;
                        defaultitem = fComboBox.getNumItems();
                    }
                }
            }
            // check the best candidate to represent the current value
            if (defaultitem > -1) { fComboBox.setSelectedItemIndex(defaultitem); }
        }
        
        *fZone = cur;
    }
    
    void comboBoxChanged (ComboBox* cb) override
    {
        std::cout<<name<<" : "<<cb->getSelectedId() - 1<<std::endl;
        modifyZone(cb->getSelectedId() - 1);
    }
    
    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        
        // search closest value
        int             defaultitem = -1;
        double          mindelta = FLT_MAX;
        
        for (unsigned int i=0; i<fValues.size(); i++) {
            double delta = fabs(fValues[i]-v);
            if (delta < mindelta) {
                mindelta = delta;
                defaultitem = i;
            }
        }
        if (defaultitem > -1) { fComboBox.setSelectedItemIndex(defaultitem); }
    }
    
    virtual void resized(){
        fComboBox.setBounds(1, getLocalBounds().getY() + 15, getWidth()-2, height/2);
    }
    
    virtual void paint(Graphics& g){
        g.setColour(Colours::black);
        g.drawText(name, getLocalBounds().withHeight(getLocalBounds().getHeight()/2), Justification::centredTop);
    }
};


class uiRadioButton: public uiComponent,
private juce::Button::Listener
{
private:
    String name;
    int x, y, width, height;
    int nbButtons;
    bool vertical;
    OwnedArray<ToggleButton> fButtons;
    vector<double> fValues;
    
public:
    uiRadioButton(GUI* gui, FAUSTFLOAT* zone, String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, bool vert, vector<string>& names, vector<double>& values, String tooltip, const char* mdescr, int radioGroupID) : uiComponent(gui, zone, w, h, tooltip), name(label), width(w), height(h), vertical(vert)
    {
        x = getLocalBounds().getX() + 10;
        y = (getLocalBounds().getHeight()-kCheckButtonHeight)/2;
        
        {
            ToggleButton*   defaultbutton = 0;
            double          mindelta = FLT_MAX;
            
            nbButtons = names.size();
            for(int i = 0; i < nbButtons; i++){
                double v = values[i];
                
                if ((v >= lo) && (v <= hi)) {
                    
                    // It is a valid value included in slider's range
                    ToggleButton* tb = new ToggleButton(names[i]);
                    addAndMakeVisible(tb);
                    tb->setRadioGroupId (radioGroupID);
                    tb->addListener(this);
                    fValues.push_back(v);
                    fButtons.add(tb);
                    
                    if(tooltipText.isNotEmpty()){ tb->setTooltip(tooltipText); }
                    // Check if this item is a good candidate to represent the current value
                    double delta = fabs(cur-v);
                    if (delta < mindelta) {
                        mindelta = delta;
                        defaultbutton = tb;
                    }
                }
            }
            // check the best candidate to represent the current value
            if (defaultbutton) { defaultbutton->setToggleState (true, dontSendNotification); }
        }
    }
    
    void setVRatio(float ratio) override
    {
        if(vertical){ vRatio = ratio * nbButtons; }
        else{ vRatio = ratio; }
    }
    
    void setHRatio(float ratio) override
    {
        if(!vertical){ hRatio = ratio * nbButtons; }
        else{ hRatio = ratio; }
    }
    
    virtual void reflectZone()
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        
        // select closest value
        int             defaultitem = -1;
        double          mindelta = FLT_MAX;
        
        for (unsigned int i=0; i<fValues.size(); i++) {
            double delta = fabs(fValues[i]-v);
            if (delta < mindelta) {
                mindelta = delta;
                defaultitem = i;
            }
        }
        if (defaultitem > -1) { fButtons.operator[](defaultitem)->setToggleState (true, dontSendNotification); }
    }
    
    virtual void resized(){
        vertical ? height = (getLocalBounds().getHeight()-25) / nbButtons : width = getLocalBounds().getWidth() / nbButtons;
        for(int i = 0; i < nbButtons; i++){
            if(vertical){ fButtons.operator[](i)->setBounds(0, i * height + 25, 100, height); }
            else{ fButtons.operator[](i)->setBounds(i * width, 25, width, 30); }
        }
    }
    virtual void paint(Graphics& g){
        g.setColour(Colours::black);
        g.drawText(name, getLocalBounds().withHeight(25), Justification::centredTop);
    }
    
    void buttonClicked(Button* button)
    {
        ToggleButton* checkButton = dynamic_cast<ToggleButton*>(button);
        std::cout<<name<<" : "<<fButtons.indexOf(checkButton)<<std::endl;
        
        modifyZone(fButtons.indexOf(checkButton));
    }
};

class VUMeter  : public uiComponent, public Timer
{
public:
    VUMeter (GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, FAUSTFLOAT mini, FAUSTFLOAT maxi, String unit, String tooltip, VUMeterType style, bool vert)
    : uiComponent(gui, zone, w, h, tooltip), min(mini), max(maxi), fStyle(style), name(label)
    {
        level = 0;
        startTimer (50);
        this->unit = unit;
        (unit == "dB") ? db = true : db = false;
        if(db){
            fScaleMin = dB2Scale(min);
            fScaleMax = dB2Scale(max);
        }
        (!(name.startsWith("0x")) && name.isNotEmpty()) ? isBargraphNameShown = true : isBargraphNameShown = false;
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
        if     (fStyle == Led)       { drawLed (g, kLedWidth/2, kLedHeight/2, level); }
        else if(fStyle == NumDisplay){ drawNumDisplay(g, kNumDisplayWidth, kNumDisplayHeight/2, level); }
        else if(fStyle == VVUMeter)  { drawVBargraph(g, kVBargraphWidth/2 , getHeight(), level, db); }
        else                         { drawHBargraph (g, getWidth(), kHBargraphHeight/2, level, db); }
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
    String name;
    bool isBargraphNameShown;
    
    void setTextEditorPos(){
        if     (fStyle == VVUMeter)   { label.setBounds((getWidth()-50)/2, getHeight()-22, 50, 20); }
        else if(fStyle == HVUMeter)   { isBargraphNameShown ? label.setBounds(63, (getHeight()-20)/2, 50, 20) : label.setBounds(3, (getHeight()-20)/2, 50, 20); }
        else if(fStyle == NumDisplay) { label.setBounds(getLocalBounds().getX(), getLocalBounds().getY(), jmax(1,jmin(kNumDisplayWidth, getWidth()))-2, jmax(1,jmin(kNumDisplayHeight/2, getHeight()))-2); }
        // LED Label ?
    }
    
    void setupTextEditor(){
        setTextEditorPos();
        label.setEditable(false, false, false);
        label.setJustificationType(Justification::centred);
        label.setText(String((int)*fZone) + unit, dontSendNotification);
        if(tooltipText.isNotEmpty()){ label.setTooltip(tooltipText); }
        
        addAndMakeVisible(label);
    }
    
    void drawHBargraph(Graphics& g, int width, int height, float level, bool dB){
        float x;
        float y = (float)(getHeight()-height)/2;
        if(isBargraphNameShown){
            x = 120;
            width -= x;
            
            // VUMeter Name
            g.setColour(Colours::black);
            g.drawText(name, 0, y, 60, height, Justification::centredRight);
        }
        else{
            x = 60;
            width -= x;
        }
        
        // VUMeter Background
        g.setColour(Colours::lightgrey);
        g.fillRect(x, y, (float) width, (float) height);
        g.setColour(Colours::black);
        g.fillRect(x+1.0f, y+1.0f, (float) width-2, (float) height-2);
        
        // Label Window
        g.setColour(Colours::darkgrey);
        g.fillRect((int)x-58, (getHeight()-22)/2, 52, 22);
        g.setColour(Colours::white.withAlpha(0.8f));
        g.fillRect((int)x-57, (getHeight()-20)/2, 50, 20);
        
        dB ? drawHBargraphDB(g, y, height, level) : drawHBargraphLin(g, x, y, width, height, level);
    }
    
    void drawHBargraphDB(Graphics& g, int y, int height, float level){
        
        // Drawing Scale
        g.setFont(9.0f);
        g.setColour(Colours::white);
        for(int i = -10; i > min; i -= 10){ paintScale(g, i); }
        for(int i = -6; i < max; i += 3)  { paintScale(g, i); }
        
        int alpha = 200;
        
        g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
        g.fillRect(dB2x(min), y+1.0f, jmin(dB2x(level)-dB2x(min), dB2x(-10)-dB2x(min)), (float) height-2);
        
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
    
    void drawHBargraphLin(Graphics& g, int x, int y, int width, int height, float level){
        
        int alpha = 200;
        Colour c = juce::Colour((uint8)255, (uint8)165, (uint8)0, (uint8)alpha);
        
        g.setColour(c.brighter());
        g.fillRect(x+1.0f, y+1.0f, jmin(level*(width-2), 0.2f*(width-2)), (float) height-2);
        
        if(level > 0.2f){
            g.setColour(c);
            g.fillRect(x+1.0f + 0.2f*(width-2), y+1.0f, jmin((level-0.2f) * (width-2), (0.9f-0.2f) * (width-2)), (float) height-2);
        }
        if(level > 0.9f){
            g.setColour(c.darker());
            g.fillRect(x+1.0f + 0.9f*(width-2), y+1.0f, jmin((level-0.9f) * (width-2), (1.0f-0.9f) * (width-2)), (float) height-2);
        }
    }
    
    void drawVBargraph(Graphics& g, int width, int height, float level, bool dB){
        float x = (float)(getLocalBounds().getWidth()-width)/2;
        float y;
        if(isBargraphNameShown) {
            y = (float) getLocalBounds().getHeight()-height+15;
            height -= 40;
            
            // VUMeter Name
            g.setColour(Colours::black);
            g.drawText(name, getLocalBounds(), Justification::centredTop);
        }
        else{ y = (float) getLocalBounds().getHeight()-height; height -= 25; }
        
        // VUMeter Background
        g.setColour(Colours::lightgrey);
        g.fillRect(x, y, (float) width, (float) height);
        g.setColour(Colours::black);
        g.fillRect(x+1.0f, y+1.0f, (float) width-2, (float) height-2);
        
        // Label window
        g.setColour(Colours::darkgrey);
        g.fillRect(jmax((getWidth()-50)/2, 0), getHeight()-23, jmin(getWidth(), 50), 22);
        g.setColour(Colours::white.withAlpha(0.8f));
        g.fillRect(jmax((getWidth()-48)/2, 1), getHeight()-22, jmin(getWidth()-2, 48), 20);
        
        dB ? drawVBargraphDB(g, x, width, level) : drawVBargraphLin(g, x, width, level);
    }
    
    void drawVBargraphDB(Graphics& g, int x, int width, float level){
        
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
    
    void drawVBargraphLin(Graphics& g, int x, int width, float level){
        int alpha = 200;
        Colour c = juce::Colour((uint8)255, (uint8)165, (uint8)0, (uint8)alpha);
        
        g.setColour(c.brighter());
        g.fillRect(x+1.0f, jmax(lin2y(level), lin2y(0.2f)), (float) width-2, lin2y(min)-jmax(lin2y(level), lin2y(0.2f)));
        
        if(level > 0.2f){
            g.setColour(c);
            g.fillRect(x+1.0f, jmax(lin2y(level), lin2y(0.9f)), (float) width-2, lin2y(0.2f)-jmax(lin2y(level), lin2y(0.9f)));
        }
        
        if(level > 0.9f){
            g.setColour(c.darker());
            g.fillRect(x+1.0f, jmax(lin2y(level), lin2y(max)), (float) width-2, lin2y(0.9)-jmax(lin2y(level), lin2y(max)));
        }
    }
    
    void drawLed(Graphics& g, int width, int height, float level){
        width  -= 2;
        height -= 2;
        float x = (float) (getLocalBounds().getWidth() - width)/2;
        float y = (float) (getLocalBounds().getHeight() - height)/2;
        g.setColour(Colours::black);
        g.fillEllipse(x, y, width, height);
        if(db){
            int alpha = 200;
            g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
            if(dB2Scale(level) > dB2Scale(-10)){ g.setColour(Colour((uint8)160, (uint8)220, (uint8)20, (uint8)alpha)); }
            if(dB2Scale(level) > dB2Scale(-6)) { g.setColour(Colour((uint8)220, (uint8)220, (uint8)20, (uint8)alpha)); }
            if(dB2Scale(level) > dB2Scale(-3)) { g.setColour(Colour((uint8)240, (uint8)160, (uint8)20, (uint8)alpha)); }
            if(dB2Scale(level) > dB2Scale(0))  { g.setColour(Colour((uint8)240, (uint8)0,   (uint8)20, (uint8)alpha)); }
            
            g.fillEllipse(x+1, y+1, width-2, height-2);
        }
        else{
            g.setColour(Colours::red.withAlpha((float)level));
            g.fillEllipse(x+1, y+1, width-2, height-2);
        }
    }
    
    void drawNumDisplay(Graphics& g, int width, int height, float level){
        int x = getLocalBounds().getX();
        int y = getLocalBounds().getY();
        height -= 5;
        
        //Draw box
        g.setColour(Colours::darkgrey);
        g.fillRect(x, y, jmax(1,jmin(kNumDisplayWidth, getWidth())), jmax(1,jmin(height, getHeight())));
        g.setColour(Colours::white.withAlpha(0.8f));
        g.fillRect(x+1, y+1, jmax(1,jmin(kNumDisplayWidth, getWidth()))-2, jmax(1,jmin(height, getHeight()))-2);
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
        int h;
        int treshold;
        if(isBargraphNameShown){ h = getHeight()-32; treshold = 16; }
        else{ h = getHeight()-27; treshold = 1; }
        return (h - h*(s0-sx)/(s0-s1)) + treshold;
    }
    
    float lin2y(float level){
        int h;
        int treshold;
        if(isBargraphNameShown){ h = getHeight()-32; treshold = 16; }
        else{ h = getHeight()-27; treshold = 1; }
        return h * (1 - level) + treshold;
    }
    
    float dB2x(float dB)
    {
        FAUSTFLOAT s0 = fScaleMin;
        FAUSTFLOAT s1 = fScaleMax;
        FAUSTFLOAT sx = dB2Scale(dB);
        int w;
        int treshold;
        if(isBargraphNameShown){ w = getWidth()-122; treshold = 120; }
        else{ w = getWidth()-62; treshold = 60; }
        return treshold + w - w*(s1-sx)/(s1-s0)+1;
    }
    
    void paintScale(Graphics& g, int num){
        if(fStyle == VVUMeter){
            Rectangle<int> r = Rectangle<int>((getWidth()-(kVBargraphWidth/2))/2, dB2y(num)-10, (kVBargraphWidth/2)-2, 20);
            g.drawText(String(num), r, Justification::centredRight, false);
        }
        else{
            Rectangle<int> r = Rectangle<int>(dB2x(num)-10,(getHeight()-kHBargraphHeight/2)/2 +1, 20, (kHBargraphHeight/2)-2);
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
