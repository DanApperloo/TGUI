/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_TEXT_BOX_HPP
#define TGUI_TEXT_BOX_HPP


#include <TGUI/Widget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class Scrollbar;
    class TextBoxRenderer;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Text box widget
    ///
    /// Signals:
    ///     - TextChanged
    ///         * Optional parameter sf::String: current text in the text box
    ///         * Uses Callback member 'text'
    ///
    ///     - Inherited signals from Widget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API TextBox : public Widget
    {
    public:

        typedef std::shared_ptr<TextBox> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const TextBox> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        ///
        /// @param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox(const TextBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of assignment operator
        ///
        /// @param right  Instance to assign
        ///
        /// @return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBox& operator= (const TextBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the text box
        ///
        /// @param themeFileFilename  Filename of the theme file.
        /// @param section            The section in the theme file to read.
        ///
        /// @throw Exception when the theme file could not be opened.
        /// @throw Exception when the theme file did not contain the requested section with the needed information.
        /// @throw Exception when one of the images, described in the theme file, could not be loaded.
        ///
        /// When an empty string is passed as filename, the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static TextBox::Ptr create(const std::string& themeFileFilename = "", const std::string& section = "TextBox");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another text box
        ///
        /// @param textBox  The other text box
        ///
        /// @return The new text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static TextBox::Ptr copy(TextBox::ConstPtr textBox);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Reference to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<TextBoxRenderer> getRenderer() const
        {
            return std::static_pointer_cast<TextBoxRenderer>(m_renderer);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position  New position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the text box.
        ///
        /// This size does not include the borders.
        ///
        /// @param size  The new size of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the full size of the text box.
        ///
        /// This is the size including the borders.
        ///
        /// @return Full size of the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of the text box.
        ///
        /// @param text  New text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Appends some text to the text that was already in the text box.
        ///
        /// @param text  Text that will be added to the text that is already in the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text of the text box.
        ///
        /// @return  The text that is currently inside the text box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getText() const
        {
            return m_text;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text.
        ///
        /// @param size  The new text size.
        ///              The minimum text size is 8.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text.
        ///
        /// @return The current text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const
        {
            return m_textSize;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the maximum character limit.
        ///
        /// @param maxChars  The new character limit.
        ///                  Set it to 0 to disable the limit.
        ///
        /// This character limit is disabled by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumCharacters(unsigned int maxChars = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum character limit.
        ///
        /// @return The character limit.
        ///         The function will return 0 when there is no limit.
        ///
        /// There is no character limit by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximumCharacters() const
        {
            return m_maxChars;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the scrollbar from the text box (if there is one).
        ///
        /// When there are too many lines to fit in the text box then some lines will be removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Make the text box read-only or make it writable again
        ///
        /// @param readOnly  Should the text box be read-only?
        ///
        /// When the text box is read-only, you can no longer delete characters and type text.
        /// Selecting text, copying text and even calling the setText function will still work.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setReadOnly(bool readOnly = true)
        {
            m_readOnly = readOnly;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the transparency of the widget.
        ///
        /// @param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void keyPressed(const sf::Event::KeyEvent& event) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void textEntered(sf::Uint32 Key) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNotOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetFocused() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void widgetUnfocused() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will search after which character the caret should be placed. It will not change the caret position.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2u findCaretPosition(sf::Vector2f position);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Converts the two dimensional caret positions into a one dimensional position in the text.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::pair<unsigned int, unsigned int> findTextCaretPosition();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when you are selecting text.
        // It will find out which part of the text is selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void selectText(float posX, float posY);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes the selected characters. This function is called when pressing backspace, delete or a letter while there were
        // some characters selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deleteSelectedCharacters();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Rearrange the text inside the text box (by using word wrap).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rearrangeText(bool keepSelection);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will split the text into five pieces so that the text can be easily drawn.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelectionTexts();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When AnimationManager changes the elapsed time then this function is called.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<TextBox>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        sf::String   m_text;
        unsigned int m_textSize = 18;
        unsigned int m_lineHeight = 40;

        std::vector<sf::String> m_lines = std::vector<sf::String>{""}; // Did not compile in VS2013 with just braces

        // The maximum characters (0 by default, which means no limit)
        unsigned int m_maxChars = 0;

        // What is known about the visible lines?
        unsigned int m_topLine = 1;
        unsigned int m_visibleLines = 1;

        // Information about the selection
        sf::Vector2u m_selStart;
        sf::Vector2u m_selEnd;

        // Information about the caret
        sf::Vector2f m_caretPosition;
        bool m_caretVisible = true;

        sf::Text m_textBeforeSelection;
        sf::Text m_textSelection1;
        sf::Text m_textSelection2;
        sf::Text m_textAfterSelection1;
        sf::Text m_textAfterSelection2;

        std::vector<sf::FloatRect> m_selectionRects;

        // The scrollbar
        Scrollbar::Ptr m_scroll = Scrollbar::create();

        // Is there a possibility that the user is going to double click?
        bool m_possibleDoubleClick = false;

        bool m_readOnly = false;

        friend class TextBoxRenderer;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API TextBoxRenderer : public WidgetRenderer, public WidgetBorders, public WidgetPadding
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        ///
        /// @param textBox  The text box that is connected to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TextBoxRenderer(TextBox* textBox) : m_textBox{textBox} {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamically change a property of the renderer, without even knowing the type of the widget.
        ///
        /// This function should only be used when you don't know the type of the widget.
        /// Otherwise you can make a direct function call to make the wanted change.
        ///
        /// @param property  The property that you would like to change
        /// @param value     The new value that you like to assign to the property
        /// @param rootPath  Path that should be placed in front of any resource filename
        ///
        /// @throw Exception when the property doesn't exist for this widget.
        /// @throw Exception when the value is invalid for this property.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value, const std::string& rootPath = getResourcePath()) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background image
        ///
        /// When this image is set, the background color property will be ignored.
        ///
        /// Pass an empty string to unset the image, in this case the background color property will be used again.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundImage(const std::string& filename,
                                const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                                const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                                bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color that will be used inside the text box.
        ///
        /// @param backgroundColor  The new background color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& backgroundColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the text color that will be used inside the text box.
        ///
        /// @param textColor  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& textColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the text color of the selected text that will be used inside the text box.
        ///
        /// @param selectedTextColor  The new text color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextColor(const sf::Color& selectedTextColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color of the selected text that will be used inside the text box.
        ///
        /// @param selectedTextBackgroundColor  The new background color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextBackgroundColor(const sf::Color& selectedTextBackgroundColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the border color that will be used inside the text box.
        ///
        /// @param borderColor  The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& borderColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the color that will be used inside the text box for the blinking caret.
        ///
        /// @param caretColor  The color of the blinking caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretColor(const sf::Color& caretColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief This will change the width of the blinking caret.
        ///
        /// @param width  New width of the caret
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setCaretWidth(float width);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the font of the text.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// @param font  The new font
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(std::shared_ptr<sf::Font> font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the padding of the text box.
        ///
        /// This padding will be scaled together with the background image.
        /// If there is no background image, or when 9-slice scaling is used, the padding will be exactly what you pass here.
        ///
        /// @param padding  The padding width and height
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPadding(const Padding& padding) override;
        using WidgetPadding::setPadding;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the scrollbar of the text box.
        ///
        /// @param scrollbarThemeFileFilename  Filename of the theme file.
        /// @param section  The section to look for inside the theme file.
        ///
        /// @throw Exception when the theme file could not be opened.
        /// @throw Exception when the theme file did not contain the requested section with the needed information.
        /// @throw Exception when one of the images, described in the theme file, could not be loaded.
        ///
        /// When an empty string is passed as filename, the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setScrollbar(const std::string& scrollbarThemeFileFilename = "", const std::string& section = "Scrollbar");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the padding, which is possibly scaled with the background image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Padding getScaledPadding() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        TextBoxRenderer(const TextBoxRenderer&) = default;
        TextBoxRenderer& operator=(const TextBoxRenderer&) = delete;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        TextBox* m_textBox;

        float m_caretWidth = 2;

        Texture   m_backgroundTexture;

        sf::Color m_caretColor           = {  0,   0,   0};
        sf::Color m_backgroundColor      = {255, 255, 255};
        sf::Color m_selectedTextBgrColor = {  0, 110, 255};
        sf::Color m_borderColor          = {  0,   0,   0};

        friend class TextBox;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TEXT_BOX_HPP
