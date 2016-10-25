//
//  faust_UI.h
//  Rectangle AudioApp
//
//  Created by Adrien Albouy on 24/10/2016.
//
//

#ifndef Rectangle_AudioApp_faust_UI_h
#define Rectangle_AudioApp_faust_UI_h

#include "../JuceLibraryCode/JuceHeader.h"

bool tabLayout;
int windowWidth;
int windowHeight;

struct Faust_UI: public Component
{
private:
    Array<faustBox*> boxes;
    Array<uiComponent*> components;
    
public:
    Faust_UI()
    {
    }
    
    ~Faust_UI(){
        for(int i = 0; i<boxes.size(); i++){
            delete boxes.operator[](i);
        }
    }
    
    faustBox* getBoxAt(int i){
        return boxes.operator[](i);
    }
    
    uiComponent* getComponentAt(int i){
        return components.operator[](i);
    }
    
    Array<uiComponent*> getComponents(){
        return components;
    }
    
    void addBox(faustBox* box){
        boxes.add(box);
    }
    
    void addComponent(uiComponent* comp){
        components.add(comp);
    }
    
    int getAmountOfBoxes(){
        return boxes.size();
    }
    
    int getAmountOfComponents(){
        return components.size();
    }
    
    void setVisibleComponents(){
        for(int i = 0; i<getAmountOfBoxes(); i++){
            addAndMakeVisible(getBoxAt(i));
        }
        for(int i = 0; i<getAmountOfComponents(); i++){
            addAndMakeVisible(getComponentAt(i));
        }
    }
    
    void layoutComponents(){
        std::cout<<"Resizing Components : ";
        for(int i = 0; i<getAmountOfComponents(); i++){
            int parentIndex = getComponentAt(i)->getParent()->index;
            if(getBoxAt(parentIndex)->vertical){
                int heightToRemove = getBoxAt(parentIndex)->getSpaceToRemove(getComponentAt(i)->getVRatio());
                getComponentAt(i)->setBounds(getBoxAt(parentIndex)->removeFromTop(heightToRemove).reduced(3));
            }
            else{
                int widthToRemove = getBoxAt(parentIndex)->getSpaceToRemove(getComponentAt(i)->getHRatio());
                getComponentAt(i)->setBounds(getBoxAt(parentIndex)->removeFromLeft(widthToRemove).reduced(3));
            }
        }
        std::cout<<std::endl;
    }
    
    void writeBoxes(){
        for (int i = 0; i<getAmountOfBoxes(); i++){
            std::cout<<getBoxAt(i)->name<<"("<<i<<")"<<std::endl;
            std::cout<<"order : "<<getBoxAt(i)->order<<", itemCount : "<<getBoxAt(i)->itemCount<<", parentIndex : "<<getBoxAt(i)->parentIndex<<std::endl;
            std::cout<<"Rect : {"<<getBoxAt(i)->originalBounds.getX()<<", "<<getBoxAt(i)->originalBounds.getY()<<", "<<getBoxAt(i)->originalBounds.getWidth()<<", "<<getBoxAt(i)->originalBounds.getHeight()<<"}"<<std::endl;
            std::cout<<"Recommended size : "<<getBoxAt(i)->recommendedWidth<<"x"<<getBoxAt(i)->recommendedHeight<<std::endl;
            std::cout<<"Ratios : "<<getBoxAt(i)->vRatio<<", "<<getBoxAt(i)->hRatio<<std::endl;
            std::cout<<"Childs : ";
            for(int j = 0; j<getBoxAt(i)->child.size(); j++){
                std::cout<<getBoxAt(i)->child.operator[](j)<<", ";
            }
            std::cout<<std::endl<<std::endl;
        }
    }
    
    void writeComponents(){
        for(int i = 0; i<getAmountOfComponents(); i++){
            std::cout<<"Components("<<i<<") : parentBounds "<<getComponentAt(i)->getParent()->toString()<<"; compBounds "<<getComponentAt(i)->getBounds().toString();
            std::cout<<"; Par index : "<<getComponentAt(i)->getParent()->index<<"; sliderBounds "<<getComponentAt(i)->slider.getBounds().toString()<<std::endl;
            std::cout<<"isVisble ? "<<getComponentAt(i)->slider.isVisible()<<"; compContained : "<<getComponentAt(i)->getParent()->Rectangle::contains(getComponentAt(i)->getBounds());
            std::cout<<", vRatio : "<<getComponentAt(i)->getVRatio()<<", hRatio : "<<getComponentAt(i)->getHRatio()<<std::endl<<std::endl;
        }
    }
    
    void calculRecommendedBoxSize(){
        int maxOrder = getHigherBoxOrder();
        std::cout<<"MaxOrder : "<<maxOrder<<std::endl;
        for(int curOrder = maxOrder-1; curOrder>=0; curOrder--){
            for(int i = 0; i<getAmountOfBoxes(); i++){
                if((getBoxAt(i)->order == curOrder) && !(getBoxAt(i)->child.isEmpty())){
                    for(int j = 0; j<getBoxAt(i)->child.size(); j++){
                        
                        int childIndex = getBoxAt(i)->child.operator[](j);
                        
                        if (getBoxAt(i)->vertical){
                            getBoxAt(i)->recommendedHeight += (getBoxAt(childIndex)->recommendedHeight);
                            getBoxAt(i)->recommendedWidth   = jmax(getBoxAt(i)->recommendedWidth, getBoxAt(childIndex)->recommendedWidth);
                        }
                        else{
                            getBoxAt(i)->recommendedWidth += (getBoxAt(childIndex)->recommendedWidth);
                            getBoxAt(i)->recommendedHeight = jmax(getBoxAt(i)->recommendedHeight, getBoxAt(childIndex)->recommendedHeight);
                        }
                    }
                }
            }
        }
        
    }
    
    void setRatio(){
        for(int i = 1; i<getAmountOfBoxes(); i++){
            int index = getBoxAt(i)->parentIndex;
            getBoxAt(i)->vRatio = (float)getBoxAt(i)->recommendedHeight/(float)getBoxAt(index)->recommendedHeight;
            getBoxAt(i)->hRatio = (float)getBoxAt(i)->recommendedWidth/(float)getBoxAt(index)->recommendedWidth;
        }
        for(int i = 0; i<getAmountOfComponents(); i++){
            int index = getComponentAt(i)->getParent()->index;
            getComponentAt(i)->setVRatio ((float)getComponentAt(i)->getRecommendedHeight()/(float)getBoxAt(index)->recommendedHeight);
            getComponentAt(i)->setHRatio ((float)getComponentAt(i)->getRecommendedWidth()/(float)getBoxAt(index)->recommendedWidth);
        }
    }
    
    int getHigherBoxOrder(){
        int order = 0;
        for(int i = 0; i<getAmountOfBoxes(); i++){
            order = jmax(order,getBoxAt(i)->order);
        }
        std::cout<<"HigherBoxOrder : "<<order<<std::endl;
        return order;
    }
    
    void layoutAllBoxes(){
        Rectangle<int> window = Rectangle<int>(0, 0, windowWidth, windowHeight);
        std::cout<<"Width x Height window : "<<windowWidth<<"x"<<windowHeight<<std::endl;
        
        getBoxAt(0)->setBounds(window.reduced(3));
        getBoxAt(0)->originalBounds = *getBoxAt(0);
        
        for (int i = 1; i<getAmountOfBoxes(); i++){
            int parentIndex = getBoxAt(i)->parentIndex;
            if(getBoxAt(parentIndex)->vertical){
                int heightToRemove = getBoxAt(parentIndex)->getSpaceToRemove(getBoxAt(i)->vRatio);
                getBoxAt(i)->setBounds(getBoxAt(parentIndex)->removeFromTop(heightToRemove).reduced(3));
                
                if(!(getBoxAt(parentIndex)->name.startsWith("0x")) && !(getBoxAt(parentIndex)->name.isEmpty()))
                    getBoxAt(i)->setBounds(getBoxAt(i)->withTrimmedTop(11));
                
                getBoxAt(i)->originalBounds = *getBoxAt(i);
            }
            else{
                int widthToRemove = getBoxAt(parentIndex)->getSpaceToRemove(getBoxAt(i)->hRatio);
                getBoxAt(i)->setBounds(getBoxAt(parentIndex)->removeFromLeft(widthToRemove).reduced(3));
                
                if(!(getBoxAt(parentIndex)->name.startsWith("0x")) && !(getBoxAt(parentIndex)->name.isEmpty()))
                    getBoxAt(i)->setBounds(getBoxAt(i)->withTrimmedTop(11));
                
                getBoxAt(i)->originalBounds = *getBoxAt(i);
            }
        }
    }
    
    void setupUI(){
        calculRecommendedBoxSize();
        setVisibleComponents();
        setRatio();
        layoutAllBoxes();
        writeBoxes();
        layoutComponents();
        writeComponents();
    }
    
    void resized() override{
        layoutAllBoxes();
        writeBoxes();
        layoutComponents();
        writeComponents();
    }
};


#endif
