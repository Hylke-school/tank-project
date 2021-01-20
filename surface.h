// Template, UU version
// IGAD/NHTV/UU - Jacco Bikker - 2006-2019

#pragma once

namespace Tmpl8
{

#define REDMASK (0xff0000)
#define GREENMASK (0x00ff00)
#define BLUEMASK (0x0000ff)

typedef unsigned int Pixel; // unsigned int is assumed to be 32-bit, which seems a safe assumption.

inline Pixel add_blend(Pixel a_Color1, Pixel a_Color2)
{
    const unsigned int r = (a_Color1 & REDMASK) + (a_Color2 & REDMASK);
    const unsigned int g = (a_Color1 & GREENMASK) + (a_Color2 & GREENMASK);
    const unsigned int b = (a_Color1 & BLUEMASK) + (a_Color2 & BLUEMASK);
    const unsigned r1 = (r & REDMASK) | (REDMASK * (r >> 24));
    const unsigned g1 = (g & GREENMASK) | (GREENMASK * (g >> 16));
    const unsigned b1 = (b & BLUEMASK) | (BLUEMASK * (b >> 8));
    return (r1 + g1 + b1);
}

// subtractive blending
inline Pixel sub_blend(Pixel a_Color1, Pixel a_Color2)
{
    int red = (a_Color1 & REDMASK) - (a_Color2 & REDMASK);
    int green = (a_Color1 & GREENMASK) - (a_Color2 & GREENMASK);
    int blue = (a_Color1 & BLUEMASK) - (a_Color2 & BLUEMASK);
    if (red < 0) red = 0;
    if (green < 0) green = 0;
    if (blue < 0) blue = 0;
    return (Pixel)(red + green + blue);
}

// color scaling
inline Pixel scale_color(Pixel c, int s)
{
    const unsigned int rb = (((c & (REDMASK | BLUEMASK)) * s) >> 5) & (REDMASK | BLUEMASK);
    const unsigned int g = (((c & GREENMASK) * s) >> 5) & GREENMASK;
    return rb + g;
}

class Surface
{
    enum
    {
        OWNER = 1
    };

  public:
    // constructor / destructor
    Surface(int a_Width, int a_Height, Pixel* a_Buffer, int a_Pitch);
    Surface(int a_Width, int a_Height);
    Surface(const char* a_File);
    ~Surface();
    // member data access
    Pixel* get_buffer() { return m_Buffer; }
    void set_buffer(Pixel* a_Buffer) { m_Buffer = a_Buffer; }
    int get_width() { return m_Width; }
    int get_height() { return m_Height; }
    int get_pitch() { return m_Pitch; }
    void set_pitch(int a_Pitch) { m_Pitch = a_Pitch; }
    // Special operations
    void init_charset();
    void set_char(int c, const char* c1, const char* c2, const char* c3, const char* c4, const char* c5);
    void centre(const char* a_String, int y1, Pixel color);
    void print(const char* a_String, int x1, int y1, Pixel color);
    void clear(Pixel a_Color);
    void line(float x1, float y1, float x2, float y2, Pixel color);
    void plot(int x, int y, Pixel c);
    void load_image(const char* a_File);
    void copy_to(Surface* a_Dst, int a_X, int a_Y);
    void blend_copy_to(Surface* a_Dst, int a_X, int a_Y);
    void scale_color(unsigned int a_Scale);
    void box(int x1, int y1, int x2, int y2, Pixel color);
    void bar(int x1, int y1, int x2, int y2, Pixel color);
    void resize(Surface* a_Orig);

  private:
    // Attributes
    Pixel* m_Buffer;
    int m_Width, m_Height;
    int m_Pitch;
    int m_Flags;
    // Static attributes for the builtin font
    static char s_Font[51][5][6];
    static bool fontInitialized;
    int s_Transl[256];
};

class Sprite
{
  public:
    // Sprite flags
    enum
    {
        FLARE = (1 << 0),
        OPFLARE = (1 << 1),
        FLASH = (1 << 4),
        DISABLED = (1 << 6),
        GMUL = (1 << 7),
        BLACKFLARE = (1 << 8),
        BRIGHTEST = (1 << 9),
        RFLARE = (1 << 12),
        GFLARE = (1 << 13),
        NOCLIP = (1 << 14)
    };

    // Structors
    Sprite(Surface* a_Surface, unsigned int a_NumFrames);
    ~Sprite();
    // Methods
    void draw(Surface* a_Target, int a_X, int a_Y);
    void draw_scaled(int a_X, int a_Y, int a_Width, int a_Height, Surface* a_Target);
    void set_flags(unsigned int a_Flags) { m_Flags = a_Flags; }
    void set_frame(unsigned int a_Index) { m_CurrentFrame = a_Index; }
    unsigned int get_flags() const { return m_Flags; }
    int get_width() { return m_Width; }
    int get_height() { return m_Height; }
    Pixel* get_buffer() { return m_Surface->get_buffer(); }
    unsigned int frames() { return m_NumFrames; }
    Surface* get_surface() { return m_Surface; }
    void initialize_start_data();

  private:
    // Attributes
    int m_Width, m_Height, m_Pitch;
    unsigned int m_NumFrames;
    unsigned int m_CurrentFrame;
    unsigned int m_Flags;
    unsigned int** m_Start;
    Surface* m_Surface;
};

class Font
{
  public:
    Font(){};
    Font(const char* a_File, const char* a_Chars);
    ~Font();
    void print(Surface* a_Target, const char* a_Text, int a_X, int a_Y, bool clip = false);
    void centre(Surface* a_Target, const char* a_Text, int a_Y);
    int width(const char* a_Text);
    int height() { return m_Surface->get_height(); }
    void y_clip(int y1, int y2)
    {
        m_CY1 = y1;
        m_CY2 = y2;
    }

  private:
    Surface* m_Surface = nullptr;
    int* m_Offset = nullptr;
    int* m_Width = nullptr;
    int* m_Trans = nullptr;
    int m_Height = 0;
    int m_CY1 = 0;
    int m_CY2 = 0;
};

}; // namespace Tmpl8
