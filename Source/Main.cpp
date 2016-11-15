/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"


MainContentComponent* createMainContentComponent();

//==============================================================================
class RectangleAudioAppApplication  : public JUCEApplication
{
public:
    //==============================================================================
    RectangleAudioAppApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        mainWindow = new MainWindow (getApplicationName());
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
     */
    
    class myViewport : public Viewport
    {
    public:
        myViewport(String name, int w, int h, int rW, int rH): Viewport(name), minWidth(w), minHeight(h), recommendedWidth(rW), recommendedHeight(rH)
        {
        }
        
        virtual void resized() override{
            Viewport::resized();
            getBounds().getWidth() < minWidth ? ((minWidth < recommendedWidth) ? width = minWidth : width = recommendedWidth) : width = getBounds().getWidth();
            getBounds().getHeight() < minHeight ? ((minHeight < recommendedHeight) ? height = minHeight : height = recommendedHeight) : height = getBounds().getHeight();
            
            getViewedComponent()->setBounds(0, 0, width, height);
            addAndMakeVisible(tooltipWindow);
        }
        /*
        virtual void visibleAreaChanged (const Rectangle<int>& newVisibleArea) override{
            getViewedComponent()->setBounds(getBounds());
        }*/
    private:
        int minWidth, minHeight;
        int recommendedWidth, recommendedHeight;
        int width, height;
        TooltipWindow tooltipWindow;
    };
    
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            
            MainContentComponent* window = createMainContentComponent();
            setResizable (true, false);
            setResizeLimits(30, 30, 10000, 10000);
            
            centreWithSize (getWidth(), getHeight());
            setVisible(true);
            
            int minWidth  = window->getMinSize().getWidth();
            int minHeight = window->getMinSize().getHeight();
            int recomWidth = window->getRecommendedSize().getWidth();
            int recomHeight = window->getRecommendedSize().getHeight();
            
            viewport = new myViewport(name, minWidth, minHeight, recomWidth, recomHeight);
            viewport->setViewedComponent(window);
            viewport->setSize(minWidth, minHeight);
            setContentOwned(viewport, true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        myViewport* viewport;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };
    
private:
    ScopedPointer<MainWindow> mainWindow;
    ScopedPointer<myViewport> viewport;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (RectangleAudioAppApplication)
