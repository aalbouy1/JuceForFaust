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
#define kHSliderHeight 60

#define kButtonWidth 100
#define kButtonHeight 30

#define kCheckButtonWidth 50
#define kCheckButtonHeight 50

#define kNumEntryWidth 100
#define kNumEntryHeight 50

#define kVBargraphWidth 110
#define kVBargraphHeight 250

#define kHBargraphWidth 350
#define kHBargraphHeight 110

#include "../JuceLibraryCode/JuceHeader.h"

#include "Faust_tabs.h"
#include "faust_box.h"
#include "UI_Component.h"
#include "MainComponent.h"
#include "faust_UI.h"

#include "faust/gui/GUI.h"
#include "faust/gui/MetaDataUI.h"

extern bool tabLayout;

struct Faust_layout: public GUI, public MetaDataUI, public Component
{
    Faust_layout()
    {
        boxNumber = 0;
        order = 0;
        tabLayout = false;
    }
    
    void setSize(Rectangle<int> r){
        window = r;
    }
    
    Rectangle<int> getSize(){
        if(tabLayout){ return Rectangle<int>(0, 0, curUI->getBoxAt(0)->recommendedWidth, curUI->getBoxAt(0)->recommendedHeight+30); }
        else { return Rectangle<int>(0, 0, curUI->getBoxAt(0)->recommendedWidth, curUI->getBoxAt(0)->recommendedHeight); }
    }

    virtual void openTabBox(const char* label){
        tabLayout = true;
    }
    
    virtual void openVerticalBox(const char* label){
        if(boxNumber == 0) {
            curUI = new Faust_UI();
            curUI->addBox(new faustBox(window, true, String(label), -1, boxNumber, order));
            if(String(label).isEmpty()) { tabName = "tab"; }
            else { tabName = String(label); }
        }
        else{
            currentBox->incItemCount();
            currentBox->child.add(boxNumber);
            previousIndex = getParentIndex(boxNumber, order-1);
            curUI->addBox(new faustBox(*currentBox, true, String(label), previousIndex, boxNumber, order));
        }
        
        currentBox = curUI->getBoxAt(boxNumber);
        addAndMakeVisible(currentBox);
        
        order++;
        boxNumber++;
    }
    
    virtual void openHorizontalBox(const char* label){
        if(boxNumber == 0) {
            curUI = new Faust_UI();
            curUI->addBox(new faustBox(window, false, String(label), -1, boxNumber, order));
            if(String(label).isEmpty()) { tabName = "tab"; }
            else { tabName = String(label); }
        }
        else{
            currentBox->incItemCount();
            currentBox->child.add(boxNumber);
            previousIndex = getParentIndex(boxNumber, order-1);
            curUI->addBox(new faustBox(*currentBox, false, String(label), previousIndex, boxNumber, order));
        }
        
        currentBox = curUI->getBoxAt(boxNumber);
        addAndMakeVisible(currentBox);

        order++;
        boxNumber++;
    }


    virtual void closeBox(){
        order--;
        if(order != -1){
            previousIndex = currentBox->parentIndex;
            currentBox = curUI->getBoxAt(previousIndex);
        }
        if(order == 0 && tabLayout){
            curUI->setupUI();
            tabs.addTabs(tabName, curUI);
            tabName.clear();
            addAndMakeVisible(tabs);
            boxNumber = 0;
        }
        else if(order == 0 && !tabLayout)
        {
            curUI->setupUI();
            addAndMakeVisible(curUI);
        }
    }

    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        if(currentBox->vertical){
            currentBox->recommendedHeight   += kHSliderHeight;
            currentBox->recommendedWidth    = jmax(currentBox->recommendedWidth, kHSliderWidth);
        }
        else{
            currentBox->recommendedWidth    += kHSliderWidth;
            currentBox->recommendedHeight   = jmax(currentBox->recommendedHeight, kHSliderHeight);
        }
        curUI->addComponent(new uiSlider(this, currentBox, zone, kHSliderWidth, kHSliderHeight, min, max, init, step, String(label), String(fUnit[zone]), getScale(zone), HSlider));
        
        currentBox->incItemCount();
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
            
            curUI->addComponent(new uiSlider(this, currentBox, zone, kVSliderWidth, kVSliderHeight, min, max, init, step, String(label), String(fUnit[zone]), getScale(zone), VSlider));
            
            currentBox->incItemCount();
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
        
        curUI->addComponent(new uiSlider(this, currentBox, zone, kKnobWidth, kKnobHeight, min, max, init, step, String(label), String(fUnit[zone]), getScale(zone), Knob));
        
        currentBox->incItemCount();
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
        
        curUI->addComponent(new uiButton(this, currentBox, zone, kButtonWidth, kButtonHeight, String(label), RegularButton));
        
        currentBox->incItemCount();
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
        currentBox->incItemCount();
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
        
        curUI->addComponent(new uiSlider(this, currentBox, zone, kVSliderWidth, kVSliderHeight, min, max, init, step, String(label), String(fUnit[zone]), getScale(zone), NumEntry));
        
        currentBox->incItemCount();
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
        currentBox->incItemCount();
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
        currentBox->incItemCount();
    }

    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value)
    {
        MetaDataUI::declare(zone, key, value);
    }

    int getParentIndex(int startIndex, int order){
        int index = startIndex-1;
        while(curUI->getBoxAt(index)->order != order){
            index--;
        }
        return index;
    }
    
    void resized(){
        if(tabLayout){ tabs.setBounds (getLocalBounds()); }
        else{ curUI->setBounds(getLocalBounds()); }
    }
    
    virtual ~Faust_layout() override{
        delete currentBox;
        delete curUI;
    }
    
    Faust_UI* curUI;
    Faust_tabs tabs;
    faustBox* currentBox;
    Rectangle<int> window;

    String tabName;
    int previousIndex;
    int order;
    int boxNumber;

};

#endif
