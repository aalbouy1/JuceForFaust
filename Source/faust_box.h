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

class faustBox : public Rectangle<int>, public Component
{
public:
    
    faustBox(bool vert, String boxName, int boxOrder, bool tab): order(boxOrder), name(boxName), vertical(vert), tabLayout(tab)
    {
        recommendedHeight = 0;
        recommendedWidth = 0;
        if(order == 0){ hRatio = 1; vRatio = 1; }
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
        
        Rectangle::setSize(r.getWidth(), r.getHeight());
        Component::setSize(r.getWidth(), r.getHeight());
        
        if(dynamic_cast<faustBox*>(getParentComponent()) != nullptr){
            setPosition(r.getX() - getParentComponent()->getX(), r.getY() - getParentComponent()->getY());
            setTopLeftPosition(r.getX() - getParentComponent()->getX(), r.getY() - getParentComponent()->getY());
        }
        else{
            if(tabLayout){
                setPosition(r.getX(), r.getY()+30);
                setTopLeftPosition(r.getX(), r.getY()+30);
            }
            else{
                setPosition(r.getX(), r.getY());
                setTopLeftPosition(r.getX(), r.getY());
            }
        }
        
        originalBounds = getLocalBounds();
    }
    
    void layoutComponents()
    {
        for(int i = 0; i<getNumChildComponents(); i++){
            uiComponent* comp = dynamic_cast<uiComponent*>(getChildComponent(i));
            if(comp != 0){
                if(vertical){
                    comp->setVRatio((float)comp->getRecommendedHeight()/(float)recommendedHeight);
                    comp->setHRatio((float)comp->getRecommendedWidth()/(float)recommendedWidth);
                    int heightToRemove = getSpaceToRemove(comp->getVRatio());
                    comp->setCompSize(this->removeFromTop(heightToRemove).reduced(3));
                }
                else{                    
                    comp->setVRatio((float)comp->getRecommendedHeight()/(float)recommendedHeight);
                    comp->setHRatio((float)comp->getRecommendedWidth()/(float)recommendedWidth);
                    int widthToRemove = getSpaceToRemove(comp->getHRatio());
                    comp->setCompSize(this->removeFromLeft(widthToRemove).reduced(3));
                }
            }
            else{
                faustBox* box = dynamic_cast<faustBox*>(getChildComponent(i));
                if(vertical){
                    int heightToRemove = getSpaceToRemove(box->vRatio);
                    if(!(name.startsWith("0x")) && !(name.isEmpty())){ box->setBoxSize(this->removeFromTop(heightToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ box->setBoxSize(this->removeFromTop(heightToRemove).reduced(3)); }
                }
                else{
                    int widthToRemove = getSpaceToRemove(box->hRatio);
                    if(!(name.startsWith("0x")) && !(name.isEmpty())){ box->setBoxSize(this->removeFromLeft(widthToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ box->setBoxSize(this->removeFromLeft(widthToRemove).reduced(3)); }
                }
            }
        }
    }
    
    void writeBox(){
        std::cout<<name<<" : "<<this<<std::endl;
        std::cout<<"order : "<<order<<", itemCount : "<<getNumChildComponents()<<", parentIndex : "<<getParentComponent()<<std::endl;
        std::cout<<"OriginalBounds : {"<<originalBounds.getX()<<", "<<originalBounds.getY()<<", "<<originalBounds.getWidth()<<", "<<originalBounds.getHeight()<<"}"<<std::endl;
        std::cout<<"Rect : {"<<toString()<<"}"<<std::endl;
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
        if(vertical){ return floor((float)originalBounds.getHeight()*ratio); }
        else{ return floor((float)originalBounds.getWidth()*ratio); }
    }
    
    void addChildBox(faustBox* box){
        addAndMakeVisible(box);
    }
    
    void addChildUiComponent(uiComponent* comp){
        addAndMakeVisible(comp);
    }
    
    void calculRecommendedSize(){
        for(int j = 0; j<getNumChildComponents(); j++){
            if(vertical){
                recommendedHeight += (getChildComponent(j)->Component::getHeight());
                recommendedWidth   = jmax(recommendedWidth, getChildComponent(j)->Component::getWidth());
            }
            else{
                recommendedWidth += (getChildComponent(j)->Component::getWidth());
                recommendedHeight = jmax(recommendedHeight, getChildComponent(j)->Component::getHeight());
            }
        }
        originalBounds = Rectangle<int>(Component::getY(), Component::getX(), recommendedWidth, recommendedHeight);
        Component::setSize(recommendedWidth, recommendedHeight);
    }
    
    void setRatio(){
        setHRatio();
        setVRatio();
        for(int i = 0; i<getNumChildComponents(); i++){
            if(dynamic_cast<faustBox*>(getChildComponent(i))!=nullptr){ dynamic_cast<faustBox*>(getChildComponent(i))->setRatio(); }
        }
    }
    
    void resized() override{
        if(order == 0){ setBoxSize(getLocalBounds()); }
        layoutComponents();
        writeBox();
    }

    void paint(Graphics& g) override
    {
        Colour col;
        if      (order == 0){ col = Colours::white;}
        else if (order == 1){ col = Colours::lightgrey;}
        else if (order == 2){ col = Colours::grey; }
        else if (order == 3){ col = Colours::darkgrey; }
        g.setColour(col);
        g.fillRect(originalBounds);
        
        g.setColour(Colours::black);
        if(!name.startsWith("0x")){ g.drawText(name, originalBounds .withHeight(10), Justification::centred); }
    }

    float hRatio, vRatio;
    int recommendedWidth, recommendedHeight;
    Rectangle<int> originalBounds;
    int order;
    String name;
    bool vertical;
    bool tabLayout;
};

#endif
