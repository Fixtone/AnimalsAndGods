#include "stdafx.h"
#include "../../Header/GUI/GUI3D/Customisation/MyStandardPanelColors.h"

MyStandardPanelColors::MyStandardPanelColors()
: Gui3D::PanelColors()
{
    // General
    transparent = Gorilla::rgb(0, 0, 0, 0);

    //Panel
    panelBackgroundSpriteName = "none";
    
    panelCursorSpriteName = "mousepointer";
    panelCursorSpriteSizeX = 12;
    panelCursorSpriteSizeY = 18;    
    
    panelGradientType = Gorilla::Gradient_NorthSouth;
    panelGradientColorStart = Gorilla::rgb(255, 0, 0, 255);
    panelGradientColorEnd = Gorilla::rgb(255, 255, 0, 255);
    panelBorder = Gorilla::rgb(120, 20, 120, 0);
    panelBorderSize = 1;    

    // Button
    buttonInactiveSpriteName = "buttonInactive";
    buttonOveredSpriteName = "buttonOvered";
    buttonNotOveredSpriteName = "buttonNotOvered";
    buttonClickedSpriteName = "buttonClicked";

    buttonBackgroundClickedGradientType = Gorilla::Gradient_NorthSouth;
    buttonBackgroundClickedGradientStart = Gorilla::rgb(255, 255, 255, 200);
    buttonBackgroundClickedGradientEnd = Gorilla::rgb(255, 255, 255, 170);

    buttonBackgroundOveredGradientType = Gorilla::Gradient_NorthSouth;
    buttonBackgroundOveredGradientStart = Gorilla::rgb(255, 255, 255, 128);
    buttonBackgroundOveredGradientEnd = Gorilla::rgb(255, 255, 255, 100);

    buttonBackgroundNotOveredGradientType = Gorilla::Gradient_NorthSouth;
    buttonBackgroundNotOveredGradientStart = Gorilla::rgb(255, 255, 255, 80);
    buttonBackgroundNotOveredGradientEnd = Gorilla::rgb(255, 255, 255, 50);

    buttonBackgroundInactiveGradientType = Gorilla::Gradient_NorthSouth;
    buttonBackgroundInactiveGradientStart = Gorilla::rgb(255, 255, 255, 15);
    buttonBackgroundInactiveGradientEnd = Gorilla::rgb(255, 255, 255, 5);

    buttonText = Gorilla::rgb(255, 255, 255, 255);
    buttonTextInactive = Gorilla::rgb(255, 255, 255, 70);
    buttonTextSize = 10;

    buttonBorder = Gorilla::rgb(70, 70, 70, 50);
    buttonBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
    buttonBorderInactive = Gorilla::rgb(70, 70, 70, 15);
    buttonBorderSize = 1;

    // Checkbox
    checkboxOveredBackgroundSpriteName = "checkboxOvered";
    checkboxNotOveredBackgroundSpriteName = "checkboxNotOvered";
    checkboxCheckedNotOveredBackgroundSpriteName = "checkboxCheckedNotOvered";
    checkboxCheckedOveredBackgroundSpriteName = "checkboxCheckedOvered"; 

    // Combobox
    comboboxButtonPreviousOveredSpriteName = "comboboxpreviouselementbuttonovered";
    comboboxButtonPreviousNotOveredSpriteName = "comboboxpreviouselementbuttonnotovered";
    comboboxButtonPreviousInactiveSpriteName = "comboboxpreviouselementbuttoninactive";

    comboboxButtonNextOveredSpriteName = "comboboxnextelementbuttonovered";
    comboboxButtonNextNotOveredSpriteName = "comboboxnextelementbuttonnotovered";
    comboboxButtonNextInactiveSpriteName = "comboboxnextelementbuttoninactive";

    comboboxBackgroundGradientType = Gorilla::Gradient_NorthSouth;
    comboboxBackgroundGradientStart = Gorilla::rgb(255, 255, 255, 0);
    comboboxBackgroundGradientEnd = Gorilla::rgb(255, 255, 255, 0);

    comboboxOveredElement = Gorilla::rgb(255, 255, 255, 100);
    comboboxNotOveredElement = Gorilla::rgb(255, 255, 255, 30);
    comboboxSelectedElement = Gorilla::rgb(120, 20, 120, 200);

    comboboxText = Ogre::ColourValue::White;
    comboboxTextSize = 10;

    comboboxBorder = Gorilla::rgb(70, 70, 70, 50);
    comboboxBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
    comboboxBorderSize = 0;

    // InlineSelector
    inlineselectorButtonPreviousOveredSpriteName = "inlineselectorPreviousButtonOvered";
    inlineselectorButtonPreviousNotOveredSpriteName = "inlineselectorPreviousButtonNotOvered";
    inlineselectorButtonPreviousInactiveSpriteName = "inlineselectorPreviousButtonInactive";

    inlineselectorButtonNextOveredSpriteName = "inlineselectorNextButtonOvered";
    inlineselectorButtonNextNotOveredSpriteName = "inlineselectorNextButtonNotOvered";
    inlineselectorButtonNextInactiveSpriteName = "inlineselectorNextButtonInactive";

    inlineselectorBackgroundGradientType = Gorilla::Gradient_NorthSouth;
    inlineselectorBackgroundGradientStart = transparent;
    inlineselectorBackgroundGradientEnd = transparent;

    inlineselectorText = Ogre::ColourValue::White;
    inlineselectorTextSize = 10;

    inlineselectorBorder = transparent;
    inlineselectorBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
    inlineselectorBorderSize = 1;

    // Listbox
    // same value as the combobox
    listboxButtonPreviousOveredSpriteName = comboboxButtonPreviousOveredSpriteName;
    listboxButtonPreviousNotOveredSpriteName = comboboxButtonPreviousNotOveredSpriteName;
    listboxButtonPreviousInactiveSpriteName = comboboxButtonPreviousInactiveSpriteName;

    listboxButtonNextOveredSpriteName = comboboxButtonNextOveredSpriteName;
    listboxButtonNextNotOveredSpriteName = comboboxButtonNextNotOveredSpriteName;
    listboxButtonNextInactiveSpriteName = comboboxButtonNextInactiveSpriteName;

    listboxBackgroundGradientType = comboboxBackgroundGradientType;
    listboxBackgroundGradientStart = comboboxBackgroundGradientStart;
    listboxBackgroundGradientEnd = comboboxBackgroundGradientEnd;

    listboxOveredElement = comboboxOveredElement;
    listboxNotOveredElement = comboboxNotOveredElement;
    listboxOveredSelectedElement = comboboxSelectedElement;
    listboxNotOveredSelectedElement = comboboxSelectedElement + Gorilla::rgb(0, 0, 0, -50);

    listboxText = comboboxText;
    listboxTextSize = 10;

    listboxBorder = comboboxBorder;
    listboxBorderHighlight = comboboxBorderHighlight;
    listboxBorderSize = comboboxBorderSize;

    // Scrollbar
    scrollbarCursorOveredSpriteName = "scrollbarOvered";
    scrollbarCursorNotOveredSpriteName = "scrollbarNotOvered";
    scrollbarCursorSelectedSpriteName = "scrollbarSelected";

    scrollbarBackgroundGradientType = Gorilla::Gradient_NorthSouth;
    scrollbarBackgroundGradientStart = Gorilla::rgb(255, 255, 255, 80);
    scrollbarBackgroundGradientEnd = Gorilla::rgb(255, 255, 255, 40);

    /*
    PURPLE
    scrollbarProgressbarGradientType = Gorilla::Gradient_WestEast;
    scrollbarProgressbarGradientStart = Gorilla::rgb(120, 20, 120, 40);
    scrollbarProgressbarGradientEnd = Gorilla::rgb(120, 20, 120, 80);
    */

    scrollbarProgressbarGradientType = Gorilla::Gradient_WestEast;
    scrollbarProgressbarGradientStart = Gorilla::rgb(0, 104, 0, 140);
    scrollbarProgressbarGradientEnd = Gorilla::rgb(0, 120, 0, 180);

    scrollbarText = Ogre::ColourValue::White;
    scrollbarTextSize = 10;

    /*
    PURPLE
    scrollbarBorder = Gorilla::rgb(70, 70, 70, 50);
    */
    scrollbarBorder = Gorilla::rgb(170, 170, 170, 150);
    scrollbarBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
    /*
    PURPLE
    scrollbarCursorBorder =  Gorilla::rgb(120, 20, 120, 150);
    */
    scrollbarCursorBorder =  Gorilla::rgb(0, 150, 0, 0);
    scrollbarBorderSize = 1;
    scrollbarCursorBorderSize = 1;

    // TextZone
    textzoneBackgroundOveredGradientType = Gorilla::Gradient_NorthSouth;
    textzoneBackgroundOveredGradientStart = Gorilla::rgb(255, 255, 255, 128);
    textzoneBackgroundOveredGradientEnd = Gorilla::rgb(255, 255, 255, 90);
    
    textzoneBackgroundNotOveredGradientType = Gorilla::Gradient_NorthSouth;
    textzoneBackgroundNotOveredGradientStart = Gorilla::rgb(255, 255, 255, 50);
    textzoneBackgroundNotOveredGradientEnd = Gorilla::rgb(255, 255, 255, 20);
    
    textzoneBackgroundSelectedGradientType = Gorilla::Gradient_NorthSouth;
    textzoneBackgroundSelectedGradientStart = Gorilla::rgb(200, 200, 200, 170);
    textzoneBackgroundSelectedGradientEnd = Gorilla::rgb(200, 200, 200, 140);

    textzoneText = Ogre::ColourValue::White;
    textzoneTextSize = 10;

    textzoneBorder = Gorilla::rgb(70, 70, 70, 50);
    textzoneBorderHighlight = Gorilla::rgb(255, 100, 100, 255);
    textzoneBorderSelected = Gorilla::rgb(255, 200, 200, 200);
    textzoneBorderSize = 1;

    // Caption
    captionBackgroundGradientType = Gorilla::Gradient_NorthSouth;
    captionBackgroundGradientStart = transparent;
    captionBackgroundGradientEnd = transparent;

    captionBorder = transparent;
    captionText = Ogre::ColourValue::White;
    captionTextSize = 10;
    captionBorderSize = 0;

    // ProgressBar
    progressbarBackgroundGradientType = Gorilla::Gradient_NorthSouth;
    progressbarBackgroundGradientStart = Gorilla::rgb(255, 255, 255, 50);
    progressbarBackgroundGradientEnd = Gorilla::rgb(255, 255, 255, 70);
    
    progressbarLoadingBarGradientType = Gorilla::Gradient_NorthSouth;
    progressbarLoadingBarGradientStart = Gorilla::rgb(120, 20, 120, 200);
    progressbarLoadingBarGradientEnd = Gorilla::rgb(120, 20, 120, 150);
    
    progressbarText = Ogre::ColourValue::White;
    progressbarTextSize = 10;
    
    progressbarBorder = Gorilla::rgb(70, 70, 70, 50);
    progressbarBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
    progressbarBorderSize = 1;
}