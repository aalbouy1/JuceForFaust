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
        
        if(findParentComponentOfClass<faustBox>() != nullptr){
            setPosition(r.getX() - getParentComponent()->getX(), r.getY() - getParentComponent()->getY());
            setTopLeftPosition(r.getX() - getParentComponent()->getX(), r.getY() - getParentComponent()->getY());
        }
        else{
            if(tabLayout){
                setPosition(r.getX()+1, r.getY()+30);
                setTopLeftPosition(r.getX()+1, r.getY()+30);
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
            uiComponent* tempComp = dynamic_cast<uiComponent*>(getChildComponent(i));
            if(tempComp != 0){
                if(vertical){
                    tempComp->setVRatio((float)tempComp->getRecommendedHeight()/(float)recommendedHeight);
                    tempComp->setHRatio((float)tempComp->getRecommendedWidth()/(float)recommendedWidth);
                    int heightToRemove = getSpaceToRemove(tempComp->getVRatio());
                    if(!(name.startsWith("0x")) && name.isNotEmpty() && i == 0){ tempComp->setCompSize(this->removeFromTop(heightToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempComp->setCompSize(this->removeFromTop(heightToRemove).reduced(3)); }
                }
                else{                    
                    tempComp->setVRatio((float)tempComp->getRecommendedHeight()/(float)recommendedHeight);
                    tempComp->setHRatio((float)tempComp->getRecommendedWidth()/(float)recommendedWidth);
                    int widthToRemove = getSpaceToRemove(tempComp->getHRatio());
                    if(!(name.startsWith("0x")) && name.isNotEmpty()){ tempComp->setCompSize(this->removeFromLeft(widthToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempComp->setCompSize(this->removeFromLeft(widthToRemove).reduced(3)); }
                }
            }
            else{
                faustBox* tempBox = dynamic_cast<faustBox*>(getChildComponent(i));
                if(vertical){
                    int heightToRemove = getSpaceToRemove(tempBox->vRatio);
                    if(!(name.startsWith("0x")) && name.isNotEmpty() && i == 0){ tempBox->setBoxSize(this->removeFromTop(heightToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempBox->setBoxSize(this->removeFromTop(heightToRemove).reduced(3)); }
                }
                else{
                    int widthToRemove = getSpaceToRemove(tempBox->hRatio);
                    if(!(name.startsWith("0x")) && name.isNotEmpty()){ tempBox->setBoxSize(this->removeFromLeft(widthToRemove).withTrimmedTop(11).reduced(3)); }
                    else{ tempBox->setBoxSize(this->removeFromLeft(widthToRemove).reduced(3)); }
                }
            }
        }
    }
    
    // Debug Output
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
        if      (order == 0){ col = Colours::white;}
        else if (order == 1){ col = Colours::lightgrey;}
        else if (order == 2){ col = Colours::grey; }
        else if (order == 3){ col = Colours::darkgrey; }
        g.setColour(col);
        g.fillRect(originalBounds);
      
        g.setColour(Colours::black);
        if(!name.startsWith("0x")){ g.drawText(name, originalBounds .withHeight(10), Justification::centred); }
    }

    ~faustBox(){
        int numChild = getNumChildComponents();
        std::cout<<"order : "<<order<<", numChilds : "<<numChild<<std::endl;
        for(int i = numChild-1; i>=0; i--){
            if(dynamic_cast<faustBox*> (getChildComponent(i)) != nullptr)
                delete dynamic_cast<faustBox*> (getChildComponent(i));
        }
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
