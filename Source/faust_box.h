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

struct faustBox : public Rectangle<int>, public Component
{
public:
    faustBox(Rectangle<int> par, bool vert, String boxName, int parIndex, int fIndex, int boxOrder): order(boxOrder), name(boxName), vertical(vert), parentIndex(parIndex), index(fIndex)
    {
        itemCount = 0;
        recommendedHeight = 0;
        recommendedWidth = 0;
        if(order == 0){ hRatio = 1; vRatio = 1; }
    }
    
    void incItemCount(){
        itemCount++;
    }
    
    void setBounds(Rectangle<int> r){
        Rectangle::setSize(r.getWidth(), r.getHeight());
        setPosition(r.getX(), r.getY());
        Component::setBounds(r);
    }
    
    int getSpaceToRemove(float ratio){
        if(vertical){ return floor((float)originalBounds.getHeight()*ratio); }
        else{ return floor((float)originalBounds.getWidth()*ratio); }
    }
    
    int getParentIndex(){
        return parentIndex;
    }
    
    void resized() override{
        Component::setBounds(originalBounds);
    }
    
    void paint(Graphics& g) override
    {
        /*
        Colour col;
        if(order == 0)      { col = Colours::white;}
        else if(order == 1) { col = Colours::lightgrey;}
        else if(order == 2) { col = Colours::grey; }
        else if(order == 3) { col = Colours::darkgrey; }
        g.setColour(col);
        g.fillRect(originalBounds);
        */
        g.setColour(Colours::black);
        if(!name.startsWith("0x")){ g.drawText(name, originalBounds.withHeight(10), Justification::centred); }
    }

    float hRatio, vRatio;
    int recommendedWidth, recommendedHeight;
    Rectangle<int> originalBounds;
    int order;
    String name;
    int itemCount; // No need of it, just for writing box properties
    bool vertical;
    int parentIndex, index;
    Array<int> child;
};

#endif
