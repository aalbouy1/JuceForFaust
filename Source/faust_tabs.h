//
//  Faust_tabs.h
//  Faust
//
//  Created by Adrien Albouy on 05/10/2016.
//
//

#ifndef Faust_Faust_tabs_h
#define Faust_Faust_tabs_h

#include "../JuceLibraryCode/JuceHeader.h"

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
        TabbedComponent::addTab(label, getRandomTabBackgroundColour(), comp, true);
        for(int i = 0; i<getNumChildComponents(); i++){
            faustBox* box = dynamic_cast<faustBox*>(getChildComponent(i));
            if(box !=0)
                std::cout<<"childs : "<<box->name<<", ";
        }
        std::cout<<std::endl;
    }
    
    int recommendedWidth, recommendedHeight;
    ScopedPointer<LookAndFeel> laf = new CustomLookAndFeel();
};

#endif
