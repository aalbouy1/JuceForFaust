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
        tempBox = findParentComponentOfClass<faustBox>();
        if(tempBox != nullptr){
            hRatio = (float)recommendedWidth/(float)tempBox->recommendedWidth;
        }
        tempBox = nullptr;
    }
    
    void setVRatio(){
        tempBox = findParentComponentOfClass<faustBox>();
        if(tempBox != nullptr){
            vRatio = (float)recommendedHeight/(float)tempBox->recommendedHeight;
        }
        tempBox = nullptr;
    }
    
    void setBoxSize(Rectangle<int> r){
        
        Rectangle::setSize(r.getWidth(), r.getHeight());
        Component::setSize(r.getWidth(), r.getHeight());
        
        tempParentBox = dynamic_cast<faustBox*>(getParentComponent());
        if(tempParentBox != nullptr){
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
        tempParentBox = nullptr;
        originalBounds = getLocalBounds();
    }
    
    void layoutComponents()
    {
        for(int i = 0; i<getNumChildComponents(); i++){
            tempComp = dynamic_cast<uiComponent*>(getChildComponent(i));
            if(tempComp != 0){
                if(vertical){
                    tempComp->setVRatio((float)tempComp->getRecommendedHeight()/(float)recommendedHeight);
                    tempComp->setHRatio((float)tempComp->getRecommendedWidth()/(float)recommendedWidth);
                    int heightToRemove = getSpaceToRemove(tempComp->getVRatio());
                    tempComp->setCompSize(this->removeFromTop(heightToRemove).reduced(3));
                }
                else{                    
                    tempComp->setVRatio((float)tempComp->getRecommendedHeight()/(float)recommendedHeight);
                    tempComp->setHRatio((float)tempComp->getRecommendedWidth()/(float)recommendedWidth);
                    int widthToRemove = getSpaceToRemove(tempComp->getHRatio());
                    tempComp->setCompSize(this->removeFromLeft(widthToRemove).reduced(3));
                }
            }
            else{
                tempBox = dynamic_cast<faustBox*>(getChildComponent(i));
                if(vertical){
                    int heightToRemove = getSpaceToRemove(tempBox->vRatio);
                    if(!(name.startsWith("0x")) && !(name.isEmpty())){ tempBox->setBoxSize(this->removeFromTop(heightToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempBox->setBoxSize(this->removeFromTop(heightToRemove).reduced(3)); }
                }
                else{
                    int widthToRemove = getSpaceToRemove(tempBox->hRatio);
                    if(!(name.startsWith("0x")) && !(name.isEmpty())){ tempBox->setBoxSize(this->removeFromLeft(widthToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempBox->setBoxSize(this->removeFromLeft(widthToRemove).reduced(3)); }
                }
                tempBox = nullptr;
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
            tempBox = dynamic_cast<faustBox*>(getChildComponent(i));
            if(tempBox != nullptr){ tempBox->setRatio(); }
            tempBox = nullptr;
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

    ~faustBox() {
        if(tempBox != nullptr)
            delete tempBox;
        if(tempParentBox != nullptr)
            delete tempParentBox;
    }

    float hRatio, vRatio;
    int recommendedWidth, recommendedHeight;
    Rectangle<int> originalBounds;
    int order;
    String name;
    bool vertical;
    bool tabLayout;
    faustBox* tempBox;
    faustBox* tempParentBox;
    uiComponent* tempComp;
};

#endif
