#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


struct DrawingFontParams
{
    float                  height         = 10.0;
    int                    escapement     = 0;
    int                    orientation    = 0;
    int                    weight         = 400;
    int                    fontStyleFlags = 0;
    ssq::sqstring          fontFace       = _SC("Courier");

    DrawingFontParams() {}

    DrawingFontParams(float h, int e, int o, int w, int fsf, const ssq::sqstring &fface)
    : height        (h)
    , escapement    (e)
    , orientation   (o)
    , weight        (w)
    , fontStyleFlags(fsf)
    , fontFace      (fface)
    {}

    DrawingFontParams(const FontParamsT<ssq::sqstring> &fp)
    : height        (floatToFloat(fp.height))
    , escapement    (fp.escapement )
    , orientation   (fp.orientation)
    , weight        ((int)fp.weight)
    , fontStyleFlags((int)fp.fontStyleFlags)
    , fontFace      (fp.fontFace)
    {}

    DrawingFontParams(const DrawingFontParams&) = default;
    DrawingFontParams(DrawingFontParams&&) = default;


    operator marty_draw_context::FontParamsT<ssq::sqstring>() const
    {
        marty_draw_context::FontParamsT<ssq::sqstring> fpRes;

        fpRes.height          = (DrawCoord::value_type)height;
        fpRes.escapement      = escapement ;
        fpRes.orientation     = orientation;
        fpRes.weight          = (FontWeight)weight;
        fpRes.fontStyleFlags  = (FontStyleFlags)fontStyleFlags;
        fpRes.fontFace        = fontFace;
        //fpRes.

        return fpRes;
    }

    static
    marty_simplesquirrel::ClassInfo getClassInfo(const std::string &clsName = "FontParams")
    {
        auto clsInfo = marty_simplesquirrel::ClassInfo(clsName);

        clsInfo.addConstructor("integer|float|string height, Drawing.FontWeight weight, Drawing.FontStyleFlags fontStyleFlags, string fontFace");

        clsInfo.addMember("float height");
        clsInfo.addMember("Drawing.FontWeight weight");
        clsInfo.addMember("Drawing.FontStyleFlags fontStyleFlags");
        clsInfo.addMember("string fontFace");

        return clsInfo;
    }


    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("FontParams"))
    {
        auto cls = vm.addClass( className.c_str()
                              , []( ssq::Object h, ssq::Object w, ssq::Object style, ssq::Object face )
                                {
                                    float         height_         = marty_simplesquirrel::fromObjectConvertHelper<float>(h, _SC("height"));
                                    // int           escapement     = 0;
                                    // int           orientation    = 0;
                                    int           weight_         = marty_simplesquirrel::fromObjectConvertHelper<int>(w, _SC("weight"));
                                    int           fontStyleFlags_ = marty_simplesquirrel::fromObjectConvertHelper<int>(style, _SC("style"));
                                    ssq::sqstring fontFace_       = marty_simplesquirrel::fromObjectConvertHelper<ssq::sqstring>(face , _SC("face"));

                                    return new DrawingFontParams(height_, 0, 0, weight_, fontStyleFlags_, fontFace_);
                                }
                              , true // release
                              );

        //auto cls = vm.addClass( className.c_str(), []() { return new DrawingFontParams(); }, true /* release */ );

        cls.addVar(_SC("height")             , &DrawingFontParams::height        );
        //cls.addVar(_SC("escapement")         , &DrawingFontParams::escapement    );
        //cls.addVar(_SC("orientation")        , &DrawingFontParams::orientation   );
        cls.addVar(_SC("weight")             , &DrawingFontParams::weight        );
        cls.addVar(_SC("fontStyleFlags")     , &DrawingFontParams::fontStyleFlags);
        cls.addVar(_SC("fontFace")           , &DrawingFontParams::fontFace      );

        return cls;
    }

    //ssq::sqstring fromObjectConvertHelper<ssq::sqstring>(ssq::Object &o, const SQChar *paramName)

}; // struct DrawingFontParams



} // namespace simplesquirrel {
} // namespace marty_draw_context {
