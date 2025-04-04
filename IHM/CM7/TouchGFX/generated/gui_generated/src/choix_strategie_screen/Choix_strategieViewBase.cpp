/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/choix_strategie_screen/Choix_strategieViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Choix_strategieViewBase::Choix_strategieViewBase() :
    buttonCallback(this, &Choix_strategieViewBase::buttonCallbackHandler)
{
    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    fond.setPosition(0, 0, 800, 480);
    fond.setColor(touchgfx::Color::getColorFromRGB(99, 0, 59));
    add(fond);

    bouton_retour.setXY(0, 420);
    bouton_retour.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_CONTENT_REPLY_50_50_E8F6FB_SVG_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_ACTION_DONE_50_50_E8F6FB_SVG_ID));
    bouton_retour.setIconXY(5, 5);
    bouton_retour.setAction(buttonCallback);
    add(bouton_retour);

    texte_mode_competition.setXY(607, 10);
    texte_mode_competition.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    texte_mode_competition.setLinespacing(0);
    texte_mode_competition.setTypedText(touchgfx::TypedText(T___SINGLEUSE_ZH0S));
    add(texte_mode_competition);

    texte_choix_strategie.setXY(178, 48);
    texte_choix_strategie.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    texte_choix_strategie.setLinespacing(0);
    texte_choix_strategie.setTypedText(touchgfx::TypedText(T___SINGLEUSE_T2NW));
    add(texte_choix_strategie);

    bloc_possibilites.setPosition(30, 111, 743, 300);
    bouton_strat_5.setXY(403, 119);
    bouton_strat_5.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID));
    bouton_strat_5.setLabelText(touchgfx::TypedText(T___SINGLEUSE_32QX));
    bouton_strat_5.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_5.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_5.setAction(buttonCallback);
    bloc_possibilites.add(bouton_strat_5);

    bouton_strat_6.setXY(403, 220);
    bouton_strat_6.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID));
    bouton_strat_6.setLabelText(touchgfx::TypedText(T___SINGLEUSE_5T8D));
    bouton_strat_6.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_6.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_6.setAction(buttonCallback);
    bloc_possibilites.add(bouton_strat_6);

    bouton_strat_4.setXY(403, 18);
    bouton_strat_4.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID));
    bouton_strat_4.setLabelText(touchgfx::TypedText(T___SINGLEUSE_R6WV));
    bouton_strat_4.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_4.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_4.setAction(buttonCallback);
    bloc_possibilites.add(bouton_strat_4);

    bouton_strat_3.setXY(30, 220);
    bouton_strat_3.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID));
    bouton_strat_3.setLabelText(touchgfx::TypedText(T___SINGLEUSE_1C0D));
    bouton_strat_3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_3.setAction(buttonCallback);
    bloc_possibilites.add(bouton_strat_3);

    bouton_strat_2.setXY(30, 119);
    bouton_strat_2.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID));
    bouton_strat_2.setLabelText(touchgfx::TypedText(T___SINGLEUSE_GRQ1));
    bouton_strat_2.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_2.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_2.setAction(buttonCallback);
    bloc_possibilites.add(bouton_strat_2);

    bouton_strat_1.setXY(30, 18);
    bouton_strat_1.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_MEDIUM_ROUND_DISABLED_ID));
    bouton_strat_1.setLabelText(touchgfx::TypedText(T___SINGLEUSE_XFJD));
    bouton_strat_1.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_strat_1.setAction(buttonCallback);
    bloc_possibilites.add(bouton_strat_1);

    add(bloc_possibilites);

    bouton_home.setXY(0, 0);
    bouton_home.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_TINY_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_ACTION_HOME_50_50_E8F6FB_SVG_ID), touchgfx::Bitmap(BITMAP_ICON_THEME_IMAGES_ACTION_DONE_50_50_E8F6FB_SVG_ID));
    bouton_home.setIconXY(5, 5);
    bouton_home.setAction(buttonCallback);
    add(bouton_home);

    bouton_valider.setXY(572, 420);
    bouton_valider.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_SMALL_ROUND_DISABLED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_60_SMALL_ROUND_DISABLED_ID));
    bouton_valider.setLabelText(touchgfx::TypedText(T___SINGLEUSE_6K80));
    bouton_valider.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_valider.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    bouton_valider.setVisible(false);
    bouton_valider.setAction(buttonCallback);
    add(bouton_valider);
}

Choix_strategieViewBase::~Choix_strategieViewBase()
{

}

void Choix_strategieViewBase::setupScreen()
{

}

void Choix_strategieViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &bouton_home)
    {
        //vers_home
        //When bouton_home clicked change screen to Home
        //Go to Home with no screen transition
        application().gotoHomeScreenNoTransition();
    }
    if (&src == &bouton_strat_1)
    {
        //changement_couleur_bouton_strat_1
        //When bouton_strat_1 clicked change label colors of bouton_strat_1
        //Set label colors on bouton_strat_1. Released color - R:235, G:30, B:30, Pressed color - R:0, G:0, B:0
        bouton_strat_1.setLabelColor(touchgfx::Color::getColorFromRGB(235, 30, 30));
        bouton_strat_1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(0, 0, 0));
        bouton_strat_1.invalidate();
        //affichage_bouton_valider_1
        //When bouton_strat_1 clicked show bouton_valider
        //Show bouton_valider
        bouton_valider.setVisible(true);
        bouton_valider.invalidate();
        //changement_couleur_1_2
        //When bouton_strat_1 clicked change label colors of bouton_strat_2
        //Set label colors on bouton_strat_2. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_2.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.invalidate();
        //changement_couleur_1_3
        //When bouton_strat_1 clicked change label colors of bouton_strat_3
        //Set label colors on bouton_strat_3. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.invalidate();
        //changement_couleur_1_4
        //When bouton_strat_1 clicked change label colors of bouton_strat_4
        //Set label colors on bouton_strat_4. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_4.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.invalidate();
        //changement_couleur_1_5
        //When bouton_strat_1 clicked change label colors of bouton_strat_5
        //Set label colors on bouton_strat_5. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_5.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.invalidate();
        //changement_couleur_1_6
        //When bouton_strat_1 clicked change label colors of bouton_strat_6
        //Set label colors on bouton_strat_6. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_6.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_6.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_6.invalidate();
        //fonction_strat_1
        //When bouton_strat_1 clicked call virtual function
        //Call strategie_1
        strategie_1();
    }
    if (&src == &bouton_strat_2)
    {
        //changement_couleur_bouton_strat_2
        //When bouton_strat_2 clicked change label colors of bouton_strat_2
        //Set label colors on bouton_strat_2. Released color - R:235, G:30, B:30, Pressed color - R:0, G:0, B:0
        bouton_strat_2.setLabelColor(touchgfx::Color::getColorFromRGB(235, 30, 30));
        bouton_strat_2.setLabelColorPressed(touchgfx::Color::getColorFromRGB(0, 0, 0));
        bouton_strat_2.invalidate();
        //affichage_bouton_valider_2
        //When bouton_strat_2 clicked show bouton_valider
        //Show bouton_valider
        bouton_valider.setVisible(true);
        bouton_valider.invalidate();
        //changement_couleur_2_1
        //When bouton_strat_2 clicked change label colors of bouton_strat_1
        //Set label colors on bouton_strat_1. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_1.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.invalidate();
        //changement_couleur_2_3
        //When bouton_strat_2 clicked change label colors of bouton_strat_3
        //Set label colors on bouton_strat_3. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.invalidate();
        //changement_couleur_2_4
        //When bouton_strat_2 clicked change label colors of bouton_strat_4
        //Set label colors on bouton_strat_4. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_4.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.invalidate();
        //changement_couleur_2_5
        //When bouton_strat_2 clicked change label colors of bouton_strat_5
        //Set label colors on bouton_strat_5. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_5.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.invalidate();
        //changement_couleur_2_6
        //When bouton_strat_2 clicked change label colors of bouton_strat_6
        //Set label colors on bouton_strat_6. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_6.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_6.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_6.invalidate();
        //fonction_strat_2
        //When bouton_strat_2 clicked call virtual function
        //Call strategie_2
        strategie_2();
    }
    if (&src == &bouton_strat_3)
    {
        //changement_couleur_bouton_strat_3
        //When bouton_strat_3 clicked change label colors of bouton_strat_3
        //Set label colors on bouton_strat_3. Released color - R:235, G:30, B:30, Pressed color - R:0, G:0, B:0
        bouton_strat_3.setLabelColor(touchgfx::Color::getColorFromRGB(235, 30, 30));
        bouton_strat_3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(0, 0, 0));
        bouton_strat_3.invalidate();
        //affichage_bouton_valider_3
        //When bouton_strat_3 clicked show bouton_valider
        //Show bouton_valider
        bouton_valider.setVisible(true);
        bouton_valider.invalidate();
        //changement_couleur_3_1
        //When bouton_strat_3 clicked change label colors of bouton_strat_1
        //Set label colors on bouton_strat_1. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_1.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.invalidate();
        //changement_couleur_3_2
        //When bouton_strat_3 clicked change label colors of bouton_strat_2
        //Set label colors on bouton_strat_2. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_2.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.invalidate();
        //changement_couleur_3_4
        //When bouton_strat_3 clicked change label colors of bouton_strat_4
        //Set label colors on bouton_strat_4. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_4.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.invalidate();
        //changement_couleur_3_5
        //When bouton_strat_3 clicked change label colors of bouton_strat_5
        //Set label colors on bouton_strat_5. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_5.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.invalidate();
        //changement_couleur_3_6
        //When bouton_strat_3 clicked change label colors of bouton_strat_6
        //Set label colors on bouton_strat_6. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_6.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_6.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_6.invalidate();
        //fonction_strat_3
        //When bouton_strat_3 clicked call virtual function
        //Call strategie_3
        strategie_3();
    }
    if (&src == &bouton_strat_4)
    {
        //changement_couleur_bouton_strat_4
        //When bouton_strat_4 clicked change label colors of bouton_strat_4
        //Set label colors on bouton_strat_4. Released color - R:235, G:30, B:30, Pressed color - R:0, G:0, B:0
        bouton_strat_4.setLabelColor(touchgfx::Color::getColorFromRGB(235, 30, 30));
        bouton_strat_4.setLabelColorPressed(touchgfx::Color::getColorFromRGB(0, 0, 0));
        bouton_strat_4.invalidate();
        //affichage_bouton_valider_4
        //When bouton_strat_4 clicked show bouton_valider
        //Show bouton_valider
        bouton_valider.setVisible(true);
        bouton_valider.invalidate();
        //changement_couleur_4_1
        //When bouton_strat_4 clicked change label colors of bouton_strat_1
        //Set label colors on bouton_strat_1. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_1.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.invalidate();
        //changement_couleur_4_2
        //When bouton_strat_4 clicked change label colors of bouton_strat_2
        //Set label colors on bouton_strat_2. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_2.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.invalidate();
        //changement_couleur_4_3
        //When bouton_strat_4 clicked change label colors of bouton_strat_3
        //Set label colors on bouton_strat_3. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.invalidate();
        //changement_couleur_4_5
        //When bouton_strat_4 clicked change label colors of bouton_strat_5
        //Set label colors on bouton_strat_5. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_5.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.invalidate();
        //fonction_strat_4
        //When bouton_strat_4 clicked call virtual function
        //Call strategie_4
        strategie_4();
    }
    if (&src == &bouton_strat_5)
    {
        //changement_couleur_bouton_strat_5
        //When bouton_strat_5 clicked change label colors of bouton_strat_5
        //Set label colors on bouton_strat_5. Released color - R:235, G:30, B:30, Pressed color - R:0, G:0, B:0
        bouton_strat_5.setLabelColor(touchgfx::Color::getColorFromRGB(235, 30, 30));
        bouton_strat_5.setLabelColorPressed(touchgfx::Color::getColorFromRGB(0, 0, 0));
        bouton_strat_5.invalidate();
        //affichage_bouton_valider_5
        //When bouton_strat_5 clicked show bouton_valider
        //Show bouton_valider
        bouton_valider.setVisible(true);
        bouton_valider.invalidate();
        //changement_couleur_5_1
        //When bouton_strat_5 clicked change label colors of bouton_strat_1
        //Set label colors on bouton_strat_1. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_1.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.invalidate();
        //changement_couleur_5_2
        //When bouton_strat_5 clicked change label colors of bouton_strat_2
        //Set label colors on bouton_strat_2. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_2.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.invalidate();
        //changement_couleur_5_3
        //When bouton_strat_5 clicked change label colors of bouton_strat_3
        //Set label colors on bouton_strat_3. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.invalidate();
        //changement_couleur_5_4
        //When bouton_strat_5 clicked change label colors of bouton_strat_4
        //Set label colors on bouton_strat_4. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_4.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.invalidate();
        //changement_couleur_5_6
        //When bouton_strat_5 clicked change label colors of bouton_strat_6
        //Set label colors on bouton_strat_6. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_6.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_6.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_6.invalidate();
        //fonction_strat_5
        //When bouton_strat_5 clicked call virtual function
        //Call strategie_5
        strategie_5();
    }
    if (&src == &bouton_retour)
    {
        //vers_home_2
        //When bouton_retour clicked change screen to Home
        //Go to Home with no screen transition
        application().gotoHomeScreenNoTransition();
    }
    if (&src == &bouton_strat_6)
    {
        //changement_couleur_6_1
        //When bouton_strat_6 clicked change label colors of bouton_strat_1
        //Set label colors on bouton_strat_1. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_1.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_1.invalidate();
        //changement_couleur_6_2
        //When bouton_strat_6 clicked change label colors of bouton_strat_2
        //Set label colors on bouton_strat_2. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_2.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_2.invalidate();
        //changement_couleur_6_3
        //When bouton_strat_6 clicked change label colors of bouton_strat_3
        //Set label colors on bouton_strat_3. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_3.invalidate();
        //changement_couleur_6_4
        //When bouton_strat_6 clicked change label colors of bouton_strat_4
        //Set label colors on bouton_strat_4. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_4.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_4.invalidate();
        //changement_couleur_6_5
        //When bouton_strat_6 clicked change label colors of bouton_strat_5
        //Set label colors on bouton_strat_5. Released color - R:255, G:255, B:255, Pressed color - R:255, G:255, B:255
        bouton_strat_5.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
        bouton_strat_5.invalidate();
        //changement_couleur_bouton_strat_6
        //When bouton_strat_6 clicked change label colors of bouton_strat_6
        //Set label colors on bouton_strat_6. Released color - R:235, G:30, B:30, Pressed color - R:0, G:0, B:0
        bouton_strat_6.setLabelColor(touchgfx::Color::getColorFromRGB(235, 30, 30));
        bouton_strat_6.setLabelColorPressed(touchgfx::Color::getColorFromRGB(0, 0, 0));
        bouton_strat_6.invalidate();
        //fonction_strat_6
        //When bouton_strat_6 clicked call virtual function
        //Call strategie_6
        strategie_6();
        //affichage_bouton_valider_6
        //When bouton_strat_6 clicked show bouton_valider
        //Show bouton_valider
        bouton_valider.setVisible(true);
        bouton_valider.invalidate();
    }
    if (&src == &bouton_valider)
    {
        //vers_robot_pret
        //When bouton_valider clicked change screen to Robot_pret
        //Go to Robot_pret with no screen transition
        application().gotoRobot_pretScreenNoTransition();
        //fonction_valider_strat
        //When bouton_valider clicked call virtual function
        //Call valider_strat
        valider_strat();
    }
}
