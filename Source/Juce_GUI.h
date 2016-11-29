//
//  faust_layout.h
//  RectangleTest
//
//  Created by Adrien Albouy on 14/10/2016.
//
//

#ifndef RectangleTest_faust_layout_h
#define RectangleTest_faust_layout_h

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#define kKnobWidth 150
#define kKnobHeight 150

#define kVSliderWidth 80
#define kVSliderHeight 250

#define kHSliderWidth 350
#define kHSliderHeight 50

#define kButtonWidth 100
#define kButtonHeight 50

#define kCheckButtonWidth 100
#define kCheckButtonHeight 40

#define kMenuWidth 100
#define kMenuHeight 50

#define kRadioButtonWidth 100
#define kRadioButtonHeight 55

#define kNumEntryWidth 100
#define kNumEntryHeight 50

#define kNumDisplayWidth 75
#define kNumDisplayHeight 50

#define kVBargraphWidth 60
#define kVBargraphHeight 250

#define kHBargraphWidth 350
#define kHBargraphHeight 50

#define kLedWidth 50
#define kLedHeight 50

#include "../JuceLibraryCode/JuceHeader.h"

#include "MainComponent.h"

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
    
    void paintScale(Graphics& g, float num){
        Rectangle<int> r;
        
        if(fStyle == VVUMeter){
            r = Rectangle<int>((getWidth()-(kVBargraphWidth/2))/2, dB2y(num)-10, (kVBargraphWidth/2)-2, 20);
            g.drawText(String(num), r, Justification::centredRight, false);
        }
        else {
            r = Rectangle<int>(dB2x(num)-10,(getHeight()-kHBargraphHeight/2)/2 +1, 20, (kHBargraphHeight/2)-2);
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




class faustBox : public Component
{
public:
    
    faustBox(bool vert, String boxName, int boxOrder, bool tab): fOrder(boxOrder), fName(boxName), isVertical(vert), tabLayout(tab)
    {
        recommendedHeight = 0;
        recommendedWidth = 0;
        if(fOrder == 0){ hRatio = 1; vRatio = 1; }
    }
    
    void setChildLookAndFeel(LookAndFeel* laf){
        for(int i = 0; i<getNumChildComponents(); i++){
            if(dynamic_cast<uiComponent*> (getChildComponent(i)) != nullptr)
                dynamic_cast<uiComponent*> (getChildComponent(i))->setCompLookAndFeel(laf);
            else{
                dynamic_cast<faustBox*>(getChildComponent(i))->setChildLookAndFeel(laf);
            }
        }
    }
    
    void setHRatio(){
        if(findParentComponentOfClass<faustBox>() != nullptr){
            hRatio = (float)recommendedWidth/(float)findParentComponentOfClass<faustBox>()->recommendedWidth;
        }
    }
    
    void setVRatio(){
        if(findParentComponentOfClass<faustBox>() != nullptr){
            vRatio = (float)recommendedHeight/(float)findParentComponentOfClass<faustBox>()->recommendedHeight;
        }
    }
    
    void setBoxSize(Rectangle<int> r){
        
        rect.setSize(r.getWidth(), r.getHeight());
        Component::setSize(r.getWidth(), r.getHeight());
        
        if(findParentComponentOfClass<faustBox>() != nullptr){
            rect.setPosition(r.getX() - getParentComponent()->getX(), r.getY() - getParentComponent()->getY());
            setTopLeftPosition(r.getX() - getParentComponent()->getX(), r.getY() - getParentComponent()->getY());
        }
        else{
            if(tabLayout){
                rect.setPosition(r.getX()+1, r.getY()+30);
                setTopLeftPosition(r.getX()+1, r.getY()+30);
            }
            else{
                rect.setPosition(r.getX(), r.getY());
                setTopLeftPosition(r.getX(), r.getY());
            }
        }
    }
    
    void layoutComponents()
    {
        for(int i = 0; i<getNumChildComponents(); i++){
            uiComponent* tempComp = dynamic_cast<uiComponent*>(getChildComponent(i));
            if(tempComp != 0){
                if(isVertical){
                    tempComp->setVRatio((float)tempComp->getRecommendedHeight()/(float)recommendedHeight);
                    tempComp->setHRatio((float)tempComp->getRecommendedWidth()/(float)recommendedWidth);
                    int heightToRemove = getSpaceToRemove(tempComp->getVRatio());
                    if(!(fName.startsWith("0x")) && fName.isNotEmpty() && i == 0){ tempComp->setCompSize(rect.removeFromTop(heightToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempComp->setCompSize(rect.removeFromTop(heightToRemove).reduced(3)); }
                }
                else{
                    tempComp->setVRatio((float)tempComp->getRecommendedHeight()/(float)recommendedHeight);
                    tempComp->setHRatio((float)tempComp->getRecommendedWidth()/(float)recommendedWidth);
                    int widthToRemove = getSpaceToRemove(tempComp->getHRatio());
                    if(!(fName.startsWith("0x")) && fName.isNotEmpty()){ tempComp->setCompSize(rect.removeFromLeft(widthToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempComp->setCompSize(rect.removeFromLeft(widthToRemove).reduced(3)); }
                }
            }
            else{
                faustBox* tempBox = dynamic_cast<faustBox*>(getChildComponent(i));
                if(isVertical){
                    int heightToRemove = getSpaceToRemove(tempBox->vRatio);
                    if(!(fName.startsWith("0x")) && fName.isNotEmpty() && i == 0){ tempBox->setBoxSize(rect.removeFromTop(heightToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempBox->setBoxSize(rect.removeFromTop(heightToRemove).reduced(3)); }
                }
                else{
                    int widthToRemove = getSpaceToRemove(tempBox->hRatio);
                    if(!(fName.startsWith("0x")) && fName.isNotEmpty()){ tempBox->setBoxSize(rect.removeFromLeft(widthToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempBox->setBoxSize(rect.removeFromLeft(widthToRemove).reduced(3)); }
                }
            }
        }
    }
    
    // Debug Output
    void writeBox(){
        std::cout<<fName<<" : "<<this<<std::endl;
        std::cout<<"order : "<<fOrder<<", itemCount : "<<getNumChildComponents()<<", parentIndex : "<<getParentComponent()<<std::endl;
        std::cout<<"Rect : {"<<rect.toString()<<"}"<<std::endl;
        std::cout<<"CompBounds : {"<<getBounds().toString()<<"}"<<std::endl;
        std::cout<<"Recommended size : "<<recommendedWidth<<"x"<<recommendedHeight<<std::endl;
        std::cout<<"Ratios : "<<vRatio<<", "<<hRatio<<std::endl;
        std::cout<<"isVisible ? "<<isVisible()<<std::endl;
        std::cout<<"Childs : ";
        for(int j = 0; j<getNumChildComponents(); j++){
            std::cout<<getChildComponent(j)<<", ";
        }
        std::cout<<std::endl<<std::endl;
    }
    
    int getSpaceToRemove(float ratio){
        if(isVertical){ return floor((float)getBounds().getHeight()*ratio); }
        else{ return floor((float)getBounds().getWidth()*ratio); }
    }
    
    void addChildBox(faustBox* box){
        addAndMakeVisible(box);
    }
    
    void addChildUiComponent(uiComponent* comp){
        addAndMakeVisible(comp);
    }
    
    void calculRecommendedSize(){
        for(int j = 0; j<getNumChildComponents(); j++){
            if(isVertical){
                recommendedHeight += (getChildComponent(j)->Component::getHeight());
                recommendedWidth   = jmax(recommendedWidth, getChildComponent(j)->Component::getWidth());
            }
            else{
                recommendedWidth += (getChildComponent(j)->Component::getWidth());
                recommendedHeight = jmax(recommendedHeight, getChildComponent(j)->Component::getHeight());
            }
        }
        Component::setSize(recommendedWidth, recommendedHeight);
    }
    
    void setRatio(){
        setHRatio();
        setVRatio();
        for(int i = 0; i<getNumChildComponents(); i++){
            if(dynamic_cast<faustBox*>(getChildComponent(i)) != nullptr){ dynamic_cast<faustBox*>(getChildComponent(i))->setRatio(); }
        }
    }
    
    void resized() override{
        setBoxSize(getLocalBounds());
        layoutComponents();
        writeBox();
    }
    
    void paint(Graphics& g) override
    {
        
         Colour col;
         if      (fOrder == 3){ col = Colours::white;}
         else if (fOrder == 2){ col = Colours::lightgrey;}
         else if (fOrder == 1){ col = Colours::grey; }
         else if (fOrder == 0){ col = Colours::darkgrey; }
         g.setColour(col);
         g.fillRect(getLocalBounds());
        
        g.setColour(Colours::black);
        if(!fName.startsWith("0x")){ g.drawText(fName, getLocalBounds() .withHeight(10), Justification::centred); }
    }
    
    ~faustBox(){
        int numChild = getNumChildComponents();
        std::cout<<"order : "<<fOrder<<", numChilds : "<<numChild<<std::endl;
        for(int i = numChild-1; i>=0; i--){
            if(dynamic_cast<faustBox*> (getChildComponent(i)) != nullptr)
                delete dynamic_cast<faustBox*> (getChildComponent(i));
        }
    }
    
    float hRatio, vRatio;
    int recommendedWidth, recommendedHeight;
    int fOrder;
    String fName;
    bool isVertical;
    bool tabLayout;
    Rectangle<int> rect;
};




class Faust_tabs  : public TabbedComponent
{
public:
    Faust_tabs()
    : TabbedComponent (TabbedButtonBar::TabsAtTop)
    {
        recommendedHeight = 0;
        recommendedWidth = 0;
    }
    
    void init(){
        for(int i = 0; i < getNumTabs(); i++){
            dynamic_cast<faustBox*>(getTabContentComponent(i))->setRatio();
            dynamic_cast<faustBox*>(getTabContentComponent(i))->setLookAndFeel(laf);
            recommendedHeight = jmax(recommendedHeight, dynamic_cast<faustBox*>(getTabContentComponent(i))->recommendedHeight);
            recommendedWidth = jmax(recommendedWidth, dynamic_cast<faustBox*>(getTabContentComponent(i))->recommendedWidth);
        }
    }
    
    static Colour getRandomTabBackgroundColour()
    {
        return Colour (Random::getSystemRandom().nextFloat(), 0.1f, 0.97f, 1.0f);
    }
    
    void addTabs(String label, Component* comp){
        TabbedComponent::addTab(label, Colours::darkgrey, comp, true);
        for(int i = 0; i<getNumChildComponents(); i++){
            faustBox* box = dynamic_cast<faustBox*>(getChildComponent(i));
            if(box !=0)
                std::cout<<"childs : "<<box->fName<<", ";
        }
        std::cout<<std::endl;
    }
    
    int recommendedWidth, recommendedHeight;
    ScopedPointer<LookAndFeel> laf = new CustomLookAndFeel();
};





struct Juce_GUI: public GUI, public MetaDataUI, public Component
{
    Juce_GUI()
    {
        order = 0;
        radioGroup = 0;
    }
    
    void setSize(Rectangle<int> r){
        window = r;
    }
    
    Rectangle<int> getSize(){
        if(!tabLayout){ return Rectangle<int>(0, 0, dynamic_cast<faustBox*>(getChildComponent(0))->recommendedWidth, dynamic_cast<faustBox*>(getChildComponent(0))->recommendedHeight); }
        else{ return Rectangle<int>(0, 0, dynamic_cast<Faust_tabs*>(getChildComponent(0))->recommendedWidth, dynamic_cast<Faust_tabs*>(getChildComponent(0))->recommendedHeight+30); }
    }

    virtual void openTabBox(const char* label){
        tabLayout = true;
    }
    
    virtual void openVerticalBox(const char* label){
        if(order == 0) {
            if(tabLayout){ tabName = String(label); label = nullptr; }
            currentBox = new faustBox(true,    String(label), order, tabLayout);
            parentBox = nullptr;
            if(!tabLayout){ addAndMakeVisible(currentBox); }
        }
        else{
            parentBox = currentBox;
            currentBox = new faustBox(true, String(label), order, tabLayout);
            parentBox->addChildBox(currentBox);
        }
        
        order++;
    }
    
    virtual void openHorizontalBox(const char* label){
        if(order == 0) {
            if(tabLayout){ tabName = String(label); label = nullptr; }
            currentBox = new faustBox(false, String(label), order, tabLayout);
            parentBox = nullptr;
            if(!tabLayout){ addAndMakeVisible(currentBox); }
        }
        else{
            parentBox = currentBox;
            currentBox = new faustBox(false, String(label), order, tabLayout);
            parentBox->addChildBox(currentBox);
        }
        
        order++;
    }


    virtual void closeBox(){
        order--;
        if(currentBox != nullptr)
            currentBox->calculRecommendedSize();
        if(dynamic_cast<faustBox*>(currentBox->getParentComponent()) != 0){
            currentBox = parentBox;
            parentBox = currentBox->findParentComponentOfClass<faustBox>(); // Return comp parent of type 'faustBox'
        }
        if(tabLayout && order == 0){
            std::cout<<"Adding Box "<<currentBox->fName<<" to tab "<<tabName<<std::endl;
            tabs.addTabs(tabName, currentBox);
            tabName.clear();
            addAndMakeVisible(tabs);
        }
    }

    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        if(isKnob(zone)){ addKnob(label, zone, init, min, max, step); }
        else if(isRadio(zone)){ addRadioButtons(label, zone, init, min, max, step, fRadioDescription[zone].c_str(), false); }
        else if(isMenu(zone)){ addMenu(label, zone, init, min, max, step, fMenuDescription[zone].c_str()); }
        else{
            if(currentBox->isVertical){
                currentBox->recommendedHeight   += kHSliderHeight;
                currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kHSliderWidth);
            }
            else{
                currentBox->recommendedWidth    += kHSliderWidth;
                currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kHSliderHeight);
            }
            
            currentBox->addChildUiComponent(new uiSlider(this, zone, kHSliderWidth, kHSliderHeight, min, max, init, step, String(label), String(fUnit[zone]), String(fTooltip[zone]),  getScale(zone), HSlider));
        }
    }
    
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step){
        if(isKnob(zone)){ addKnob(label, zone, init, min, max, step); }
        else if(isRadio(zone)){ addRadioButtons(label, zone, init, min, max, step, fRadioDescription[zone].c_str(), true); }
        else if(isMenu(zone)){ addMenu(label, zone, init, min, max, step, fMenuDescription[zone].c_str()); }
        else{
            if(currentBox->isVertical){
                currentBox->recommendedHeight   += kVSliderHeight;
                currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kVSliderWidth);
            }
            else{
                currentBox->recommendedWidth    += kVSliderWidth;
                currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kVSliderHeight);
            }
            
            currentBox->addChildUiComponent(new uiSlider(this, zone, kVSliderWidth, kVSliderHeight, min, max, init, step, String(label), String(fUnit[zone]), String(fTooltip[zone]),  getScale(zone), VSlider));
            
        }
    }
    
    void addMenu(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr){
        if(currentBox->isVertical){
            currentBox->recommendedHeight   += kMenuHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kMenuWidth);
        }
        else{
            currentBox->recommendedWidth    += kMenuWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kMenuHeight);
        }
        
        currentBox->addChildUiComponent(new uiMenu(this, zone, String(label), kMenuWidth, kMenuHeight, init, min, max, String(fTooltip[zone]), mdescr));
    }
    
    void addRadioButtons(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr, bool vert){
        vector<string> names;
        vector<double> values;
        parseMenuList(mdescr, names, values);
        int nbButtons = names.size();
        radioGroup++;
        
        if(currentBox->isVertical){
            if(vert){
                currentBox->recommendedHeight   += nbButtons * (kRadioButtonHeight - 25) + 25;
                currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kCheckButtonWidth);
            }
            else{
                currentBox->recommendedHeight   += kRadioButtonHeight;
                currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, nbButtons * kCheckButtonWidth);
            }
        }
        else{
            if(vert){
                currentBox->recommendedWidth    += kCheckButtonWidth;
                currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, nbButtons * (kRadioButtonHeight - 25) + 25);
            }
            else{
                currentBox->recommendedWidth    += nbButtons * kCheckButtonWidth;
                currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kRadioButtonHeight);
            }
        }
        
        if(vert){ currentBox->addChildUiComponent(new uiRadioButton(this, zone, String(label), kCheckButtonWidth, nbButtons * (kRadioButtonHeight - 25) + 25, init, min, max, true, names, values, String(fTooltip[zone]), mdescr, radioGroup));
        }
        else{
            currentBox->addChildUiComponent(new uiRadioButton(this, zone, String(label), kCheckButtonWidth, kRadioButtonHeight, init, min, max, false, names, values, String(fTooltip[zone]), mdescr, radioGroup));
        }
    }
    
    void addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step){
        if(currentBox->isVertical){
            currentBox->recommendedHeight   += kKnobHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kKnobWidth);
        }
        else{
            currentBox->recommendedWidth    += kKnobWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kKnobHeight);
        }
        
        currentBox->addChildUiComponent(new uiSlider(this, zone, kKnobWidth, kKnobHeight, min, max, init, step, String(label), String(fUnit[zone]), String(fTooltip[zone]),  getScale(zone), Knob));
        
    }
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone){
        if(currentBox->isVertical){
            currentBox->recommendedHeight   += kButtonHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kButtonWidth);
        }
        else{
            currentBox->recommendedWidth    += kButtonWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kButtonHeight);
        }
        
        currentBox->addChildUiComponent(new uiButton(this, zone, kButtonWidth, kButtonHeight, String(label), String(fTooltip[zone])));
        
    }

    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone){
        if(currentBox->isVertical){
            currentBox->recommendedHeight   += kCheckButtonHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kCheckButtonWidth);
        }
        else{
            currentBox->recommendedWidth    += kCheckButtonWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kCheckButtonHeight);
        }
        
        currentBox->addChildUiComponent(new uiCheckButton(this, zone, kCheckButtonWidth, kCheckButtonHeight, String(label), String(fTooltip[zone])));
    }

    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        if(currentBox->isVertical){
            currentBox->recommendedHeight   += kNumEntryHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kNumEntryWidth);
        }
        else{
            currentBox->recommendedWidth    += kNumEntryWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kNumEntryHeight);
        }
        
        currentBox->addChildUiComponent(new uiSlider(this, zone, kNumEntryWidth, kNumEntryHeight, min, max, init, step, String(label), String(fUnit[zone]), String(fTooltip[zone]),  getScale(zone), NumEntry));
        
    }

    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        if(isLed(zone)){ addLed(String(label), zone, min, max); }
        else if(isNumerical(zone)){ addNumericalDisplay(String(label), zone, min, max); }
        else{
            if(currentBox->isVertical){
                currentBox->recommendedHeight   += kHBargraphHeight;
                currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kHBargraphWidth);
            }
            else{
                currentBox->recommendedWidth    += kHBargraphWidth;
                currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kHBargraphHeight);
            }
            currentBox->addChildUiComponent(new VUMeter (this, zone, kHBargraphWidth, kHBargraphHeight, String(label), min, max, String(fUnit[zone]), String(fTooltip[zone]), HVUMeter, false));
        }
    }
    
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        if(isLed(zone)){ addLed(String(label), zone, min, max); }
        else if(isNumerical(zone)){ addNumericalDisplay(String(label), zone, min, max); }
        else{
            if(currentBox->isVertical){
                currentBox->recommendedHeight   += kVBargraphHeight;
                currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kVBargraphWidth);
            }
            else{
                currentBox->recommendedWidth    += kVBargraphWidth;
                currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kVBargraphHeight);
            }
            currentBox->addChildUiComponent(new VUMeter (this, zone, kVBargraphWidth, kVBargraphHeight, String(label), min, max, String(fUnit[zone]), String(fTooltip[zone]), VVUMeter, true));
        }
    }
    
    void addLed (String label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max){
        if(currentBox->isVertical){
            currentBox->recommendedHeight   += kLedHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kLedWidth);
        }
        else{
            currentBox->recommendedWidth    += kLedWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kLedHeight);
        }
        
        currentBox->addChildUiComponent(new VUMeter (this, zone, kLedWidth, kLedHeight, label, min, max, String(fUnit[zone]), String(fTooltip[zone]), Led, false));
    }
    
    void addNumericalDisplay(String label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max){
        if(currentBox->isVertical){
            currentBox->recommendedHeight   += kNumDisplayHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kNumDisplayWidth);
        }
        else{
            currentBox->recommendedWidth    += kNumDisplayWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kNumDisplayHeight);
        }
        
        currentBox->addChildUiComponent(new VUMeter (this, zone, kNumDisplayWidth, kNumDisplayHeight, label, min, max, String(fUnit[zone]), String(fTooltip[zone]), NumDisplay, false));
    }
    

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value)
    {
        MetaDataUI::declare(zone, key, value);
    }
    
    void init(){
        if(tabLayout){
            tabs.init();
        }
        else{
            dynamic_cast<faustBox*> (getChildComponent(0))->setRatio();
            dynamic_cast<faustBox*> (getChildComponent(0))->setBoxSize(getLocalBounds());
            dynamic_cast<faustBox*> (getChildComponent(0))->setChildLookAndFeel(laf);
        }
    }
    
    void resized(){
        if(tabLayout){ tabs.setBounds(getLocalBounds()); }
        else{ dynamic_cast<faustBox*> (getChildComponent(0))->setBoxSize(getLocalBounds()); }
    }
    
    ~Juce_GUI(){
        std::cout<<std::endl<<"Destructing boxes"<<std::endl;
        
        delete currentBox;
        if(parentBox != nullptr)
            delete parentBox;
    }
    
    int order;
    int radioGroup;
    faustBox* currentBox;
    faustBox* parentBox;
    bool tabLayout = false;
    Faust_tabs tabs;
    String tabName;
    ScopedPointer<LookAndFeel> laf = new CustomLookAndFeel();

    Rectangle<int> window;
};

#endif
