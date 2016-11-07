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
#define kCheckButtonHeight 30

#define kNumEntryWidth 100
#define kNumEntryHeight 50

#define kVBargraphWidth 80
#define kVBargraphHeight 250

#define kHBargraphWidth 350
#define kHBargraphHeight 50

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
        boxNumber = 0;
        order = 0;
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
        if(boxNumber == 0) {
            if(tabLayout){ tabName = String(label); label = nullptr; }
            currentBox = new faustBox(true, String(label), order, tabLayout);
            parentBox = nullptr;
            if(!tabLayout){ addAndMakeVisible(currentBox); }
        }
        else{
            parentBox = currentBox;
            currentBox = new faustBox(true, String(label), order, tabLayout);
            parentBox->addChildBox(currentBox);
        }
        
        order++;
        boxNumber++;
    }
    
    virtual void openHorizontalBox(const char* label){
        if(boxNumber == 0) {
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
        boxNumber++;
    }


    virtual void closeBox(){
        order--;
        currentBox->calculRecommendedSize();
        if(dynamic_cast<faustBox*>(currentBox->getParentComponent()) != 0){
            currentBox = parentBox;
            parentBox = currentBox->findParentComponentOfClass<faustBox>(); // Return comp parent of type 'faustBox'
        }
        if(tabLayout && order == 0/*dynamic_cast<faustBox*>(currentBox->getParentComponent()) != 0*/){
            std::cout<<"Adding Box "<<currentBox->name<<" to tab "<<tabName<<std::endl;
            tabs.addTabs(tabName, currentBox);
            tabName.clear();
            addAndMakeVisible(tabs);
            boxNumber = 0;
        }
    }

    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        if(isKnob(zone)){ addKnob(label, zone, init, min, max, step); }
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
        if(currentBox->vertical){
            currentBox->recommendedHeight   += kHBargraphHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kHBargraphWidth);
        }
        else{
            currentBox->recommendedWidth    += kHBargraphWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kHBargraphHeight);
        }
        currentBox->addChildUiComponent(new VUMeter (this, zone, kHBargraphWidth, kHBargraphHeight, String(label), min, max, String(fUnit[zone]), String(fTooltip[zone]), false));
        
    }
    
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        if(currentBox->vertical){
            currentBox->recommendedHeight   += kVBargraphHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kVBargraphWidth);
        }
        else{
            currentBox->recommendedWidth    += kVBargraphWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kVBargraphHeight);
        }
        currentBox->addChildUiComponent(new VUMeter (this, zone, kVBargraphWidth, kVBargraphHeight, String(label), min, max, String(fUnit[zone]), String(fTooltip[zone]), true));
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
    
    int order;
    int boxNumber; //Need ?
    faustBox* currentBox;
    faustBox* parentBox;
    bool tabLayout = false;
    Faust_tabs tabs;
    String tabName;

    Rectangle<int> window;
};

#endif
