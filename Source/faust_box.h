//
//  faust_box.h
//  RectangleTest
//
//  Created by Adrien Albouy on 14/10/2016.
//
//

#ifndef RectangleTest_faust_box_h
#define RectangleTest_faust_box_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "faust_layout.h"

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

#endif
