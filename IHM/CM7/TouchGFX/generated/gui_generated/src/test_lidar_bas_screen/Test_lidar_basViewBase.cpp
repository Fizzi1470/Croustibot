/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/test_lidar_bas_screen/Test_lidar_basViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <images/BitmapDatabase.hpp>

Test_lidar_basViewBase::Test_lidar_basViewBase() :
    buttonCallback(this, &Test_lidar_basViewBase::buttonCallbackHandler)
{
    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    fond.setPosition(0, 0, 800, 480);
    fond.setColor(touchgfx::Color::getColorFromRGB(99, 0, 59));
    add(fond);

    texte_menu_tests_lidar_1.setXY(672, 6);
    texte_menu_tests_lidar_1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    texte_menu_tests_lidar_1.setLinespacing(0);
    texte_menu_tests_lidar_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_WWBO));
    add(texte_menu_tests_lidar_1);

    bouton_retour.setXY(0, 420);
    bouton_retour.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_CONTENT_REPLY_50_50_E8F6FB_SVG_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_ACTION_DONE_50_50_E8F6FB_SVG_ID));
    bouton_retour.setIconXY(5, 5);
    bouton_retour.setAction(buttonCallback);
    add(bouton_retour);

    bouton_home.setXY(0, 0);
    bouton_home.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_ACTION_HOME_50_50_E8F6FB_SVG_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_ACTION_DONE_50_50_E8F6FB_SVG_ID));
    bouton_home.setIconXY(5, 5);
    bouton_home.setAction(buttonCallback);
    add(bouton_home);

    repere_polaire.setBitmap(touchgfx::Bitmap(BITMAP_REPERE_POLAIRE_ID));
    repere_polaire.setPosition(149, 0, 503, 480);
    repere_polaire.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    add(repere_polaire);

    image_lidar_bas.setBitmap(touchgfx::Bitmap(BITMAP_LIDAR1_ID));
    image_lidar_bas.setPosition(684, 70, 87, 80);
    image_lidar_bas.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    add(image_lidar_bas);
}

Test_lidar_basViewBase::~Test_lidar_basViewBase()
{

}

void Test_lidar_basViewBase::setupScreen()
{
    transitionBegins();
}

void Test_lidar_basViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &bouton_home)
    {
        //vers_home
        //When bouton_home clicked change screen to Home
        //Go to Home with no screen transition
        application().gotoHomeScreenNoTransition();
    }
    if (&src == &bouton_retour)
    {
        //vers_choix_tests
        //When bouton_retour clicked change screen to Choix_tests
        //Go to Choix_tests with no screen transition
        application().gotoChoix_testsScreenNoTransition();
    }
}

void Test_lidar_basViewBase::transitionBegins()
{
    //fonction_donnees_lidar_bas_avant
    //When screen transition begins call virtual function
    //Call donnees_lidar_bas_avant
    donnees_lidar_bas_avant();

    //fonction_donnees_lidar_bas_arriere
    //When screen transition begins call virtual function
    //Call donnees_lidar_bas_arriere
    donnees_lidar_bas_arriere();
}
