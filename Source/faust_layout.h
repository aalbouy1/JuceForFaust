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

#include "UI_Component.h"
#include "faust_box.h"
#include "faust_tabs.h"
#include "MainComponent.h"

#include "faust/gui/GUI.h"
#include "faust/gui/MetaDataUI.h"

struct Faust_layout: public GUI, public MetaDataUI, public Component
{
    Faust_layout()
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
            //std::cout<<"Adding Box "<<currentBox->name<<" to tab "<<tabName<<std::endl;
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
            if(currentBox->vertical){
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
            if(currentBox->vertical){
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
        if(currentBox->vertical){
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
        
        if(currentBox->vertical){
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
        if(currentBox->vertical){
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
        if(currentBox->vertical){
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
        if(currentBox->vertical){
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
        if(currentBox->vertical){
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
            if(currentBox->vertical){
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
            if(currentBox->vertical){
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
        if(currentBox->vertical){
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
        if(currentBox->vertical){
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
        }
    }
    
    void resized(){
        if(tabLayout){ tabs.setBounds(getLocalBounds()); }
        else{ dynamic_cast<faustBox*> (getChildComponent(0))->setBoxSize(getLocalBounds()); }
    }
    
    ~Faust_layout(){
        delete currentBox;
        delete parentBox;
    }
    
    int order;
    int radioGroup;
    faustBox* currentBox;
    faustBox* parentBox;
    bool tabLayout = false;
    Faust_tabs tabs;
    String tabName;

    Rectangle<int> window;
};

#endif
