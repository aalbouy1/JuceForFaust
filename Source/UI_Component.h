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

class uiComponent: public Component, public uiItem, public SettableTooltipClient
{
public:
    
    float vRatio, hRatio;
    int recomWidth, recomHeight;
    String fTooltipText;
    
    uiComponent(GUI* gui, FAUSTFLOAT* zone, int w, int h, String tooltip): uiItem(gui,zone), recomWidth(w), recomHeight(h), fTooltipText(tooltip)
    {
        std::cout<<"TOOLTIP : "<<fTooltipText<<std::endl;
    }
    
    // Debug output
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
    virtual void setCompLookAndFeel(LookAndFeel* laf) = 0;
};

class uiSlider: public uiComponent,
private juce::Slider::Listener
{
private:
    
    Slider::SliderStyle fStyle;
    Label fLabel;
    String fName;
    ScopedPointer<ValueConverter> fConverter;
    int x, y, width, height;
    SliderType fType;
    Slider fSlider;
    
public:
    uiSlider(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT cur, FAUSTFLOAT step, String name, String unit, String tooltip, MetaDataUI::Scale scale, SliderType type) : uiComponent(gui, zone, w, h, tooltip), fName(name), fType(type)
    {
        if (scale == MetaDataUI::kLog) 		{
            fConverter = new LogValueConverter(min, max, min, max);
            fSlider.setSkewFactor(0.5);
        }
        else if (scale == MetaDataUI::kExp) {
            fConverter = new ExpValueConverter(min, max, min, max);
            fSlider.setSkewFactor(2.0);
        }
        else { fConverter = new LinearValueConverter(min, max, min, max);}
        
        switch(fType){
            case HSlider:
                fStyle = Slider::SliderStyle::LinearHorizontal;
                break;
            case VSlider:
                fStyle = Slider::SliderStyle::LinearVertical;
                fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                break;
            case NumEntry:
                fSlider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_AutoDirection);
                fStyle = Slider::SliderStyle::IncDecButtons;
                break;
            case Knob:
                fStyle = Slider::SliderStyle::Rotary;
                fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                break;
                
            default:
                break;
        }
        addAndMakeVisible(fSlider);
        
        //Slider settings
        fSlider.setBounds(getBounds());
        fSlider.setRange(min, max, step);
        fSlider.setValue(fConverter->faust2ui(cur));
        fSlider.addListener(this);
        fSlider.setSliderStyle(fStyle);
        fSlider.setTextValueSuffix(unit);
        if(fTooltipText.isNotEmpty()){ fSlider.setTooltip(fTooltipText); }
        
        //Label settings
        if(fType == HSlider || fType == NumEntry){
            fLabel.setText(fName, dontSendNotification);
            fLabel.attachToComponent(&fSlider, true);
            addAndMakeVisible (fLabel);
            if(fTooltipText.isNotEmpty()){ fLabel.setTooltip(fTooltipText); }
        }
    }
    
    virtual void paint(Graphics& g) override{
        g.setColour (Colours::black);
        if(fType == VSlider || fType == Knob) { g.drawText(fName, getLocalBounds(), Justification::centredTop); }
        //else if(type == Knob) { g.drawText(sliderName, getLocalBounds(), Justification::centredTop); }
    }

    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        fSlider.setValue(fConverter->faust2ui(v));
    }

    void sliderValueChanged(Slider* slider) override
    {
        float value = slider->getValue();
        std::cout<<fName<<" : "<<value<<std::endl;
        modifyZone(value);
    }

    virtual void setCompLookAndFeel(LookAndFeel* laf){
        fSlider.setLookAndFeel(laf);
    }

    virtual void resized() override{
        std::cout<<fName<<", ";
        if(fType == HSlider){
            x = getLocalBounds().reduced(3).getX() + 60; y = getLocalBounds().reduced(3).getY();
            width = getLocalBounds().reduced(3).getWidth()-60; height = getLocalBounds().reduced(3).getHeight();
        }
        else if(fType == NumEntry){
            width = kNumEntryWidth-10; height = kNumEntryHeight-15;
            x = (getLocalBounds().reduced(3).getWidth()-width)/2; y = (getLocalBounds().reduced(3).getHeight()-height)/2;
        }
        else{
            x = getLocalBounds().reduced(3).getX(); y = getLocalBounds().reduced(3).getY()+11;
            height = getLocalBounds().reduced(3).getHeight()-12; width = getLocalBounds().reduced(3).getWidth();
        }
        fSlider.setBounds(x, y, width, height);
    }
};

class uiButton: public uiComponent,
private juce::Button::Listener
{
private:
    
    String fName;
    int x, y, width, height;
    TextButton fButton;
    
public:
    uiButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, String tooltip) :  uiComponent(gui, zone, w, h, tooltip), fName(label), width(w), height(h)
    {
        x = getLocalBounds().getX()+10;
        width = kCheckButtonWidth;
        height = kCheckButtonHeight;
        y = (getLocalBounds().getHeight()-height)/2;
        
        fButton.setButtonText(label);
        fButton.setBounds(x, y, width, height);
        fButton.addListener(this);
        if(fTooltipText.isNotEmpty()){ fButton.setTooltip(fTooltipText); }
        
        addAndMakeVisible(fButton);
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
    
    virtual void setCompLookAndFeel(LookAndFeel* laf){
        fButton.setLookAndFeel(laf);
    }
    
    virtual void paint(Graphics& g) override
    {
    }
    
    virtual void resized() override
    {
        x = getLocalBounds().getX()+10;
        width = getLocalBounds().getWidth()-20;
        height = jmin(getLocalBounds().getHeight(), kButtonHeight);
        y = (getLocalBounds().getHeight()-height)/2;
        fButton.setBounds(x, y, width, height);
    }
};

class uiCheckButton: public uiComponent,
private juce::Button::Listener
{
public:
    
    String fName;
    int x, y, width, height;
    ToggleButton fCheckButton;
    
    uiCheckButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, String label, String tooltip) : uiComponent(gui, zone, w, h, tooltip), fName(label), width(w), height(h)
    {
        x = getLocalBounds().getX() + 10;
        y = (getLocalBounds().getHeight()-height)/2;
        
        if(fTooltipText.isNotEmpty()){ setTooltip(fTooltipText); }
        
        fCheckButton.setButtonText(label);
        fCheckButton.setBounds(x, y, width, height);
        fCheckButton.addListener(this);
        if(fTooltipText.isNotEmpty()){ fCheckButton.setTooltip(fTooltipText); }
        
        addAndMakeVisible(fCheckButton);
    }
    
    void buttonClicked(Button* button)
    {
        std::cout<<fName<<" : "<<button->getToggleState()<<std::endl;
        modifyZone(button->getToggleState());
    }
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
    }
    
    virtual void setCompLookAndFeel(LookAndFeel* laf){
        fCheckButton.setLookAndFeel(laf);
    }
    
    virtual void paint(Graphics& g) override
    {
    }
    
    virtual void resized() override
    {
        std::cout<<"RESIZING CHECKBUTTON"<<std::endl;
        x = getLocalBounds().getX();
        y = getLocalBounds().getY();
        fCheckButton.setBounds(x, y, jmin(getLocalBounds().getWidth(), width), jmin(getLocalBounds().getHeight(), height));
    }
};

class uiMenu: public uiComponent,
private juce::ComboBox::Listener
{
private:
    ComboBox fComboBox;
    String fName;
    int x, y, width, height;
    int nbItem;
    vector<double> fValues;
    
public:
    uiMenu(GUI* gui, FAUSTFLOAT* zone, String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, String tooltip, const char* mdescr) : uiComponent(gui, zone, w, h, tooltip), fName(label), width(w), height(h)
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
        std::cout<<fName<<" : "<<cb->getSelectedId() - 1<<std::endl;
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
    
    virtual void setCompLookAndFeel(LookAndFeel* laf){
        fComboBox.setLookAndFeel(laf);
    }
    
    virtual void resized(){
        fComboBox.setBounds(1, getLocalBounds().getY() + 15, getWidth()-2, height/2);
    }
    
    virtual void paint(Graphics& g){
        g.setColour(Colours::black);
        g.drawText(fName, getLocalBounds().withHeight(getLocalBounds().getHeight()/2), Justification::centredTop);
    }
};


class uiRadioButton: public uiComponent,
private juce::Button::Listener
{
private:
    String name;
    int x, y, width, height;
    int nbButtons;
    bool isVertical;
    OwnedArray<ToggleButton> fButtons;
    vector<double> fValues;
    
public:
    uiRadioButton(GUI* gui, FAUSTFLOAT* zone, String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, bool vert, vector<string>& names, vector<double>& values, String tooltip, const char* mdescr, int radioGroupID) : uiComponent(gui, zone, w, h, tooltip), name(label), width(w), height(h), isVertical(vert)
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
                    
                    if(fTooltipText.isNotEmpty()){ tb->setTooltip(fTooltipText); }
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
        if(isVertical){ vRatio = ratio * nbButtons; }
        else{ vRatio = ratio; }
    }
    
    void setHRatio(float ratio) override
    {
        if(!isVertical){ hRatio = ratio * nbButtons; }
        else{ hRatio = ratio; }
    }
    
    virtual void setCompLookAndFeel(LookAndFeel* laf){
        for(int i = 0; i<nbButtons; i++)
            fButtons[i]->setLookAndFeel(laf);
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
        isVertical ? height = (getLocalBounds().getHeight()-25) / nbButtons : width = getLocalBounds().getWidth() / nbButtons;
        
        for(int i = 0; i < nbButtons; i++){
            if(isVertical){ fButtons.operator[](i)->setBounds(0, i * height + 25, 100, height); }
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
    : uiComponent(gui, zone, w, h, tooltip), fMin(mini), fMax(maxi), fStyle(style), fName(label)
    {
        fLevel = 0;
        startTimer (50);
        this->fUnit = unit;
        (unit == "dB") ? db = true : db = false;
        if(db){
            fScaleMin = dB2Scale(fMin);
            fScaleMax = dB2Scale(fMax);
        }
        (!(fName.startsWith("0x")) && fName.isNotEmpty()) ? isBargraphNameShown = true : isBargraphNameShown = false;
        if(fTooltipText.isNotEmpty()){ setTooltip(fTooltipText); }
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
            fLevel = 0;
        }
    }
    
    virtual void setCompLookAndFeel(LookAndFeel* laf){ }
    
    void paint (Graphics& g) override
    {
        if     (fStyle == Led)       { drawLed (g, kLedWidth/2, kLedHeight/2, fLevel); }
        else if(fStyle == NumDisplay){ drawNumDisplay(g, kNumDisplayWidth, kNumDisplayHeight/2, fLevel); }
        else if(fStyle == VVUMeter)  { drawVBargraph(g, kVBargraphWidth/2 , getHeight(), fLevel, db); }
        else                         { drawHBargraph (g, getWidth(), kHBargraphHeight/2, fLevel, db); }
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
    float fLevel;
    float fMin, fMax;
    float fScaleMin, fScaleMax;
    bool db;
    VUMeterType fStyle;
    String fUnit;
    Label fLabel;
    String fName;
    bool isBargraphNameShown;
    
    void setTextEditorPos(){
        if     (fStyle == VVUMeter)   { fLabel.setBounds((getWidth()-50)/2, getHeight()-22, 50, 20); }
        else if(fStyle == HVUMeter)   { isBargraphNameShown ? fLabel.setBounds(63, (getHeight()-20)/2, 50, 20) : fLabel.setBounds(3, (getHeight()-20)/2, 50, 20); }
        else if(fStyle == NumDisplay) { fLabel.setBounds(getLocalBounds().getX(), getLocalBounds().getY(), jmax(1,jmin(kNumDisplayWidth, getWidth()))-2, jmax(1,jmin(kNumDisplayHeight/2, getHeight()))-2); }
        // LED Label ?
    }
    
    void setupTextEditor(){
        setTextEditorPos();
        fLabel.setEditable(false, false, false);
        fLabel.setJustificationType(Justification::centred);
        fLabel.setText(String((int)*fZone) + fUnit, dontSendNotification);
        if(fTooltipText.isNotEmpty()){ fLabel.setTooltip(fTooltipText); }
        
        addAndMakeVisible(fLabel);
    }
    
    void drawHBargraph(Graphics& g, int width, int height, float level, bool dB){
        float x;
        float y = (float)(getHeight()-height)/2;
        if(isBargraphNameShown){
            x = 120;
            width -= x;
            
            // VUMeter Name
            g.setColour(Colours::black);
            g.drawText(fName, 0, y, 60, height, Justification::centredRight);
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
        for(int i = -10; i > fMin; i -= 10){ paintScale(g, i); }
        for(int i = -6; i < fMax; i += 3)  { paintScale(g, i); }
        
        int alpha = 200;
        
        g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
        g.fillRect(dB2x(fMin), y+1.0f, jmin(dB2x(level)-dB2x(fMin), dB2x(-10)-dB2x(fMin)), (float) height-2);
        
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
            g.fillRect(dB2x(0), y+1.0f, jmin(dB2x(level)-dB2x(0), dB2x(fMax)-dB2x(0)), (float) height-2);
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
            g.drawText(fName, getLocalBounds(), Justification::centredTop);
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
        for(int i = -10; i > fMin; i -= 10){ paintScale(g, i); }
        for(int i = -6; i < fMax; i += 3)  { paintScale(g, i); }
        
        
        int alpha = 200;
        g.setColour(Colour((uint8)40, (uint8)160, (uint8)40, (uint8)alpha));
        g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(-10)), (float) width-2, dB2y(fMin)-jmax(dB2y(level), dB2y(-10)));
        
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
            g.fillRect(x+1.0f, jmax(dB2y(level), dB2y(fMax)), (float) width-2, dB2y(0)-jmax(dB2y(level), dB2y(fMax)));
        }
    }
    
    void drawVBargraphLin(Graphics& g, int x, int width, float level){
        int alpha = 200;
        Colour c = juce::Colour((uint8)255, (uint8)165, (uint8)0, (uint8)alpha);
        
        g.setColour(c.brighter());
        g.fillRect(x+1.0f, jmax(lin2y(level), lin2y(0.2f)), (float) width-2, lin2y(fMin)-jmax(lin2y(level), lin2y(0.2f)));
        
        if(level > 0.2f){
            g.setColour(c);
            g.fillRect(x+1.0f, jmax(lin2y(level), lin2y(0.9f)), (float) width-2, lin2y(0.2f)-jmax(lin2y(level), lin2y(0.9f)));
        }
        
        if(level > 0.9f){
            g.setColour(c.darker());
            g.fillRect(x+1.0f, jmax(lin2y(level), lin2y(fMax)), (float) width-2, lin2y(0.9)-jmax(lin2y(level), lin2y(fMax)));
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
        if(isBargraphNameShown){ h = getHeight()-42; treshold = 16; }
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
            fLevel = rawLevel;
            if(fLevel > fMax)     { fLevel = fMax; }
            else if(fLevel < fMin){ fLevel = fMin; }
        }
        else{
            fLevel = (rawLevel-fMin)/(fMax-fMin);
            if(fLevel > 1)       { fLevel = 1; }
            else if(fLevel < 0)  { fLevel = 0; }
        }
        
        fLabel.setText(String((int)rawLevel)+fUnit, dontSendNotification);
    }
};

#endif
